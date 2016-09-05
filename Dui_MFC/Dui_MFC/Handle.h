#pragma once


class COperageHandle
{
public:
	static COperageHandle *GetInstance();

	void	HandleMenuCmd(const CDuiString& cmd );

private:
	COperageHandle();
	~COperageHandle();

	void newFile();

	static COperageHandle *m_pInstance;


};

