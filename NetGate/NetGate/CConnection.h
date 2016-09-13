#ifndef CCONNECTION_H
#define CCONNECTION_H


#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>


typedef  boost::asio::ip::tcp::socket tcp_socket;

class CConnection
{
public:
	CConnection(boost::asio::io_service &serv);
	~CConnection();

	void Start();
	void Close();

	void PostRead();
	void PostWrite();

	void OnReadDone(boost::system::error_code code, std::size_t size);
	void OnWriteDone(boost::system::error_code code, std::size_t size);

	tcp_socket	*GetSocket();

private:
	tcp_socket			m_socket;
	boost::array<char, 1024>	m_readBuff;
	boost::array<char, 1024>	m_sendBuff;


};




#endif