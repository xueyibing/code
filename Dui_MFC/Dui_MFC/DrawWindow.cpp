#include "stdafx.h"
#include "DrawWindow.h"

CDrawWindow::CDrawWindow()
{

}

CDrawWindow::~CDrawWindow()
{

}

LPCTSTR CDrawWindow::GetWindowClassName() const
{
	return _T("DrawWindow");
}

void CDrawWindow::Init(const CDuiString &xml, CPaintManagerUI *parent)
{
//	m_pm.Init(m_hWnd);



}

void CDrawWindow::Show(POINT pos)
{

}

void CDrawWindow::Notify(TNotifyUI& msg)
{

}

LRESULT CDrawWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CDrawWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	CDialogBuilder builder;
	pRoot = builder.Create(_T("drawWindow.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot&&"Failded To Parse Xml");
	m_pm.Init(m_hWnd);
	m_pm.SetUnfocusPaintWindow(true);
	m_pm.AttachDialog(pRoot);



//	TImageInfo* img = m_pm.AddImage(_T("icon.png"));
	return NULL;
}

CDrawWCallBack::CDrawWCallBack()
{

}

CDrawWCallBack::~CDrawWCallBack(void)
{

}

DuiLib::CControlUI* CDrawWCallBack::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}
