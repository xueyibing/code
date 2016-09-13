#include "CServerPool.h"

CServerPool * CServerPool::sm_pInstance = nullptr;
CServerPool::CServerPool(const int servSize)
:m_serUserIndex(0)
{
	for (size_t i = 0; i < servSize; i++)
	{
		ioService_sptr newServ(new boost::asio::io_service);
		m_vecService.push_back(newServ);
		boost::shared_ptr<boost::asio::io_service::work> wsptr(new boost::asio::io_service::work(*newServ));
		m_vecServiceWork.push_back(wsptr);

	}


}

CServerPool::~CServerPool()
{

}

ioService_sptr CServerPool::GetService()
{
	if (m_serUserIndex >= m_vecService.size())
	{
		m_serUserIndex = 0;
	}
	return m_vecService[m_serUserIndex++];
}

void CServerPool::Run()
{
	for (size_t i = 0; i < m_serUserIndex; i++)
	{
		m_vecService[i]->run();
		shared_ptr<boost::thread> t(new boost::thread(boost::bind(&boost::asio::io_service::run, m_vecService[i])));
		m_vecServThreadPool.push_back(t);
	}
}

int CServerPool::GetServiceSize()
{
	return m_vecService.size();
}
