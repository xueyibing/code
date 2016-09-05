#include "stdafx.h"
#include "CConfigReader.h"

using namespace rapidxml;

CConfigReader* CConfigReader::m_pInstance = NULL;
CConfigReader* CONFIG = CConfigReader::GetInstance();

CConfigReader * CConfigReader::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CConfigReader();
	}
	return m_pInstance;
}

bool CConfigReader::Initialize(const string& strFilePath)
{
	m_strFilePath = strFilePath;
	bool is_success = true;
	try
	{
		m_fdoc = new rapidxml::file<>(strFilePath.c_str());
		m_doc.parse<0>(m_fdoc->data());//此函数可能抛出异常
		m_root = m_doc.first_node();

		for (rapidxml::xml_node<>* node=m_root; node; node = node->next_sibling())
		{
			string nodename = node->name();
			if (nodename == "Window")
				ReadRect(node);
		}
	}
	catch (exception& e)
	{
		std::cout << "read xml error:" << e.what() << std::endl;
		is_success = false;
	}
	//释放节点内存
	//m_doc.clear();
	return is_success;
}

bool CConfigReader::Finitialize()
{
	xml_document<> doc;
	xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(rot);

	xml_node<>* winNode = doc.allocate_node(node_element, "Window", "information");
	xml_node<>* RectNode = doc.allocate_node(node_element, "Rect", NULL);

	doc.append_node(winNode);
	winNode->append_node(RectNode);

	string x = std::to_string(WindowRect.x);
	RectNode->append_attribute(m_doc.allocate_attribute("x", x.c_str()));

	string y = std::to_string(WindowRect.y);
	RectNode->append_attribute(m_doc.allocate_attribute("y", y.c_str()));

	string width = std::to_string(WindowRect.width);
	RectNode->append_attribute(m_doc.allocate_attribute("width", width.c_str()));

	string height = std::to_string(WindowRect.height);
	RectNode->append_attribute(m_doc.allocate_attribute("height", height.c_str()));

	std::ofstream out(m_strFilePath.c_str(), ios::out);
	if (out)
	{
		out << doc;
		out.close();
		return true;
	}
	else
	{
		out.close();
		return false;
	}

}

void CConfigReader::SaveRectConfig()
{
	for (rapidxml::xml_node<>* root = m_root; root; root = root->next_sibling())
	{
		string nodename = root->name();
		if (nodename == "Window")
		{
			rapidxml::xml_node<>* node = root->first_node();
			for (; node; node = node->next_sibling())
			{
				string nodename = node->name();
				if (nodename == "Rect")
				{
					node->remove_attribute(node->first_attribute("x"));
					node->remove_attribute(node->first_attribute("y"));
					node->remove_attribute(node->first_attribute("width"));
					node->remove_attribute(node->first_attribute("height"));
					string c = std::to_string(WindowRect.width);

					node->append_attribute(m_doc.allocate_attribute("x", std::to_string(WindowRect.x).c_str()));
					node->append_attribute(m_doc.allocate_attribute("y", std::to_string(WindowRect.y).c_str()));
					node->append_attribute(m_doc.allocate_attribute("width", std::to_string(WindowRect.width).c_str()));
					node->append_attribute(m_doc.allocate_attribute("height", "200"));
				}
			}
		}
	}
}

void CConfigReader::ReadRect(void* lp)
{
	if (!lp)
		throw string("root pointer is null");
	rapidxml::xml_node<>* root = (rapidxml::xml_node<>*)(lp);
	rapidxml::xml_node<>* node = root->first_node();
	for (; node; node = node->next_sibling())
	{
		string nodename = node->name();
		if (nodename == "Rect")
		{
			WindowRect.x = std::stoi(node->first_attribute("x")->value());
			WindowRect.y = std::stoi(node->first_attribute("y")->value());
			WindowRect.width = std::stoi(node->first_attribute("width")->value());
			WindowRect.height = std::stoi(node->first_attribute("height")->value());
		}
	}
}


