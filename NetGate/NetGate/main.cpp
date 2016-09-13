// NetGate.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CServerPool.h"
#include "CListenAccept.h"

void start();

int _tmain(int argc, _TCHAR* argv[])
{
	start();
	return 0;
}

void start()
{
	CServerPool::CreateInstance(5);
	CServerPool *pServ = CServerPool::GetInstance();
	CConnectionMgr::CreateInstance(pServ);
	CListenAccept *pAccept = new CListenAccept(pServ,5678);
	pAccept->start();


	pServ->Run();


}

