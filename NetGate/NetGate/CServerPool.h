#ifndef CSERVERPOOL_H
#define CSERVERPOOL_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <vector>

using namespace boost;
using namespace boost::asio;
typedef boost::shared_ptr<boost::asio::io_service>  ioService_sptr;

class CServerPool : public boost::noncopyable
{
public:
	static void CreateInstance(const int size)
	{
		if (!sm_pInstance)
		{
			sm_pInstance = new CServerPool(size);
		}
	}
	static CServerPool * GetInstance()
	{
		assert(sm_pInstance);
		return sm_pInstance;
	}


	ioService_sptr  GetService();
	int				   GetServiceSize();
	void				   Run();

private:
	static CServerPool *sm_pInstance;

	CServerPool(const int servSize);
	~CServerPool();


private:
	std::vector<ioService_sptr>		m_vecService;
	std::vector<boost::shared_ptr<boost::asio::io_service::work>>		m_vecServiceWork;
	std::vector<boost::shared_ptr<boost::thread>>			m_vecServThreadPool;

	int											m_serUserIndex;




};








#endif // !CSERVERPOOL_H
