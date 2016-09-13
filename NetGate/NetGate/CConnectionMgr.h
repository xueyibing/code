#ifndef CCONNECTIONMGR_H
#define CCONNECTIONMGR_H

#include "CConnection.h"
#include "CServerPool.h"
#include <vector>

typedef boost::shared_ptr<CConnection> cconection_ptr;

class CConnectionMgr : public boost::noncopyable
{
public:
	static  void CreateInstance(CServerPool *serv);
	static  CConnectionMgr*	GetInstance();

	cconection_ptr GetOneConnection();

private:
	static CConnectionMgr*	sm_pInstance;
	CConnectionMgr(CServerPool *servp);
	~CConnectionMgr();


	std::vector<boost::shared_ptr<CConnection>>		m_vecConnection;
	CServerPool		*m_pServerPool;

};





#endif