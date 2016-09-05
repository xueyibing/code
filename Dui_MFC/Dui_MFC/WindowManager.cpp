#include "stdafx.h"
#include "WindowManager.h"
#include "MainWindow.h"
CWindowManager* CWindowManager::m_pInstance = NULL;

CWindowManager * CWindowManager::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CWindowManager();
	}
	return m_pInstance;
}

CWindowManager::~CWindowManager()
{

}


void CWindowManager::SetBaseMfcHwnd(HWND h)
{
	m_mfcBaseHwnd = h;
}

HWND CWindowManager::GetWinHwnd(WindowId wid)
{
	HWND hReturn = NULL;
	HwndMapIter_t iter = m_windowHwndMap.find(wid);
	if (iter != m_windowHwndMap.end())
	{
		hReturn = iter->second;
		return hReturn;
	}
	else
	{
		return NULL;
	}

}


DuiLib::CWindowWnd * CWindowManager::GetWindPtr(WindowId wid)
{

	CWindowWnd* hReturn = NULL;
	PtrMapIter_t iter = m_windowPtrMap.find(wid);
	if (iter != m_windowPtrMap.end())
	{
		hReturn = iter->second;
	}
	else
	{
		hReturn = CreateWnd(wid);
	}
	return hReturn;
}

void CWindowManager::RegistWinHwnd(WindowId wid, HWND h)
{
	m_windowHwndMap.insert(std::make_pair(wid, h));

}

CWindowWnd* CWindowManager::CreateWnd(WindowId wid)
{
	if (wid == e_MainWind)
	{
		ASSERT(m_mfcBaseHwnd);
		CMainWindow *mainWindow = new CMainWindow();
		::SetWindowLongPtr(m_mfcBaseHwnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(mainWindow));
		mainWindow->Subclass(m_mfcBaseHwnd);
		mainWindow->Create(_T("mainWindow.xml"));
		HWND h = mainWindow->GetHWND();
		m_windowHwndMap.insert(std::make_pair(wid, h));
		m_windowPtrMap.insert(std::make_pair(wid, mainWindow));

		return mainWindow;
	}

	return NULL;
}

void CWindowManager::Init()
{
	CPaintManagerUI::SetResourcePath(GetCurFullPathStr() + _T("skin\\config\\"));
	
}

CWindowManager::CWindowManager()
:m_mfcBaseHwnd(NULL)
{
	Init();
}

DuiLib::CDuiString CWindowManager::GetCurFullPathStr()
{
	TCHAR exeFullPath[MAX_PATH]; // MAX_PATH在WINDEF.h中定义了，等于260  
	memset(exeFullPath, 0, MAX_PATH);
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	std::wstring exePath = exeFullPath;

	int index = exePath.find_last_of('\\');
	exePath = exePath.substr(0, index + 1);

	return exePath.c_str();
}