#pragma once

#include <map>

enum WindowId
{
	e_MainWind = 0,
};

class CWindowManager
{
public:

	static CWindowManager *GetInstance();

	~CWindowManager();

	//����duilib��������mfc����
	void SetBaseMfcHwnd(HWND h);

	//��ô���ľ��
	HWND GetWinHwnd(WindowId wid);

	//��ô����ָ��
	CWindowWnd *GetWindPtr(WindowId wid);

	void	RegistWinHwnd(WindowId wid,HWND h);

private:
	CWindowWnd* CreateWnd(WindowId wid);
	void Init();
	CWindowManager();
	CDuiString GetCurFullPathStr();

private:

	typedef std::map<WindowId, HWND>::iterator HwndMapIter_t;
	std::map<WindowId, HWND>		m_windowHwndMap;

	typedef std::map<WindowId, CWindowWnd*>::iterator PtrMapIter_t;
	std::map<WindowId, CWindowWnd*>		m_windowPtrMap;

	HWND m_mfcBaseHwnd;


private:
	static CWindowManager* m_pInstance;
};


