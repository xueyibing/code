#include "CListenAccept.h"

CListenAccept::CListenAccept(CServerPool *serPool, unsigned short port)
:m_endPort(boost::asio::ip::tcp::v4(),port)
{
	for (size_t i = 0; i < serPool->GetServiceSize(); i++)
	{
		acceptor_sptr accept(new boost::asio::ip::tcp::acceptor(*serPool->GetService()));
		accept->open(m_endPort.protocol());
		accept->set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		accept->bind(m_endPort);
		accept->listen();
		m_vecAccpet.push_back(accept);
	}
}

CListenAccept::~CListenAccept()
{

}

void CListenAccept::start()
{
	for (size_t i = 0; i < m_vecAccpet.size(); i++)
	{
		PostAccept(m_vecAccpet.at(i));
	}
}

void CListenAccept::PostAccept(acceptor_sptr accept)
{
	cconection_ptr conn = CConnectionMgr::GetInstance()->GetOneConnection();
	accept->async_accept(*conn->GetSocket(),
		boost::bind(&CListenAccept::OnAcceptDone, this, 
		boost::asio::placeholders::error,accept,conn)
			);

}

void CListenAccept::OnAcceptDone(boost::system::error_code code, acceptor_sptr accept, cconection_ptr conn)
{
	conn->Start();
	PostAccept(accept);

}
