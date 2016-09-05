#include "stdafx.h"
#include "Handle.h"

COperageHandle* COperageHandle::m_pInstance = NULL;

COperageHandle * COperageHandle::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new COperageHandle();
	}
	return m_pInstance;
}

void COperageHandle::HandleMenuCmd(const CDuiString& cmd)
{
	if (cmd.Compare(L"newFile") == 0)
		newFile();
}

COperageHandle::~COperageHandle()
{

}

void COperageHandle::newFile()
{
	HWND h = CWindowManager::GetInstance()->GetWinHwnd(e_MainWind);
	if (h)
	{
		::PostMessage(h, WM_NEWFILE_MSG, 0, 0);
	}

	return;
}

COperageHandle::COperageHandle()
{

}
