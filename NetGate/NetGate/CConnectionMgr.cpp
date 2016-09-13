#include "CConnectionMgr.h"

CConnectionMgr *CConnectionMgr::sm_pInstance = nullptr;

CConnectionMgr::CConnectionMgr(CServerPool *servp)
{
	m_pServerPool = servp;

}

CConnectionMgr::~CConnectionMgr()
{

}

void CConnectionMgr::CreateInstance(CServerPool *serv)
{
	if (!sm_pInstance)
	{
		sm_pInstance = new CConnectionMgr(serv);
	}
}
CConnectionMgr* CConnectionMgr::GetInstance()
{
	return sm_pInstance;
}

cconection_ptr CConnectionMgr::GetOneConnection()
{
	cconection_ptr conn(new CConnection(*m_pServerPool->GetService()));
	m_vecConnection.push_back(conn);
	return conn;
}



