#pragma once


#include <string>
#include <vector>
#include "..\thirdLib\rapidxml\rapidxml_utils.hpp"
#include "..\thirdLib\rapidxml\rapidxml.hpp"
#include "..\thirdLib\rapidxml\rapidxml_print.hpp"
using namespace std;

//地址二元组
typedef struct STWindowRect
{
	int x;
	int y;
	int width;
	int height;

}STWindowRect;


class CConfigReader
{
public:

	static CConfigReader *GetInstance();
	bool Initialize(const string& strFilePath);
	bool Finitialize();

	void SaveRectConfig();

public:
	STWindowRect		WindowRect;

private:
	void ReadRect(void* lp);

	rapidxml::xml_document<>   m_doc;
	rapidxml::xml_node<>* m_root;
	rapidxml::file<> *m_fdoc;
	string  m_strFilePath;

	static CConfigReader* m_pInstance;

};

extern CConfigReader* CONFIG;