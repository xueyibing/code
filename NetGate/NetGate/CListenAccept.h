#ifndef CLISTENACCEPT_H
#define CLISTENACCEPT_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "CServerPool.h"
#include "CConnection.h"
#include "CConnectionMgr.h"

typedef		boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_sptr;


class CListenAccept : public boost::noncopyable
{
public:
	CListenAccept(CServerPool *serPool, unsigned short port);
	~CListenAccept();

	void start();

	void PostAccept(acceptor_sptr accept);

	void OnAcceptDone(boost::system::error_code code, acceptor_sptr accept, cconection_ptr conn);


private:

	boost::asio::ip::tcp::endpoint		m_endPort;

	std::vector<acceptor_sptr>		m_vecAccpet;

};


#endif