#include "CConnection.h"


CConnection::CConnection(boost::asio::io_service &serv)
:m_socket(serv)
{
}

CConnection::~CConnection()
{

}

void CConnection::Start()
{
	PostRead();
}

void CConnection::Close()
{
	m_socket.close();
}

void CConnection::PostRead()
{
	m_socket.async_read_some(boost::asio::buffer(m_readBuff), 
		boost::bind(&CConnection::OnReadDone, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

}

void CConnection::PostWrite()
{
	m_socket.async_write_some(boost::asio::buffer(m_sendBuff),
		boost::bind(&CConnection::OnWriteDone, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void CConnection::OnReadDone(boost::system::error_code code, std::size_t size)
{
	int a = 0;

}

void CConnection::OnWriteDone(boost::system::error_code code, std::size_t size)
{
	int a = 0;
}

tcp_socket *CConnection::GetSocket()
{
	return &m_socket;
}

