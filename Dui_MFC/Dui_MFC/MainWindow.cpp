
#include "stdafx.h"
#include "MainWindow.h"
#include "MfcPage.h"
#include "DrawWindow.h"

CMainWindow::CMainWindow() 
{
	m_scintillaMode = ::LoadLibrary(_T("SciLexer.dll"));
};


LPCTSTR CMainWindow::GetWindowClassName() const
{
	return _T("MainWindow");
};

UINT CMainWindow::GetClassStyle() const
{
	return CS_DBLCLKS;
};

void CMainWindow::OnFinalMessage(HWND /*hWnd*/)
{
	RECT r;
	::GetWindowRect(CWindowManager::GetInstance()->GetWinHwnd(e_MainWind), &r);

	CONFIG->WindowRect.x = r.left;
	CONFIG->WindowRect.y = r.top;
	CONFIG->WindowRect.width = r.right - r.left;
	CONFIG->WindowRect.height = r.bottom - r.top;
	CONFIG->Finitialize();
//	delete this;
};

void CMainWindow::Init()
{
 	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));

	m_fileBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("fileBtn")));
	m_viewBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("viewBtn")));
	m_insetBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("insetBtn")));
	m_chartBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("chartBtn")));
	m_toolBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("toolBtn")));
	m_windowBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("windowBtn")));
	m_helpBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("helpBtn")));
	m_labelFenceLy = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("labelFenceLy")));
	m_pageLy = static_cast<CHorizontalLayoutUI*>(m_pm.FindControl(_T("pageLy")));
	m_newPageBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("newPage")));

	m_toolnewBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("toolnewBtn")));
	m_toolopenBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("toolopenBtn")));

	m_pageLy->SetAutoDestroy(false);
	m_labelFenceLy->SetAutoDestroy(false);

}

void CMainWindow::OnPrepare(TNotifyUI& msg)
{

}

void CMainWindow::OnFileMenuShow(TNotifyUI& msg)
{
 	RECT rcClient = m_fileBtn->GetPos();
 	POINT pt = { rcClient.left, rcClient.bottom };
 	::ClientToScreen(*this, &pt);
 	m_fileMenu = new CMenuBuilder(L"fileMenus.xml");
 	m_fileMenu->TrackPopupMenu(*this, pt.x, pt.y);

}

void CMainWindow::OnViewMenuShow(TNotifyUI& msg)
{
	RECT rcClient = m_viewBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_viewMenu = new CMenuBuilder(L"viewMenus.xml");
	m_viewMenu->TrackPopupMenu(*this, pt.x, pt.y);

}

void CMainWindow::OnInsetMenuShow(TNotifyUI& msg)
{
	RECT rcClient = m_insetBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_insetMenu = new CMenuBuilder(L"insetMenus.xml");
	m_insetMenu->TrackPopupMenu(*this, pt.x, pt.y);
}

void CMainWindow::OnChartMenuShow(TNotifyUI& msg)
{
	RECT rcClient = m_chartBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_chartMenu = new CMenuBuilder(L"chartMenus.xml");
	m_chartMenu->TrackPopupMenu(*this, pt.x, pt.y);
}

void CMainWindow::OnToolMenuShow(TNotifyUI& msg)
{

// 	CDrawWindow *dw = new CDrawWindow();
// 	HDC hdc = dw->m_pm.GetPaintDC();
// 	SetBkColor(hdc, RGB(100, 0, 100));
// 	dw->Create(NULL, _T("DW"), WS_VISIBLE, WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW, 50, 50, 500, 500);
// 	::ShowWindow(*dw, SW_SHOW);


	RECT rcClient = m_toolBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_toolMenu = new CMenuBuilder(L"toolMenus.xml");
	m_toolMenu->TrackPopupMenu(*this, pt.x, pt.y);
}

void CMainWindow::OnWindowMenuShow(TNotifyUI& msg)
{
	RECT rcClient = m_windowBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_windowMenu = new CMenuBuilder(L"windowMenus.xml");
	m_windowMenu->TrackPopupMenu(*this, pt.x, pt.y);
}

void CMainWindow::OnHelpMenuShow(TNotifyUI& msg)
{
	RECT rcClient = m_helpBtn->GetPos();
	POINT pt = { rcClient.left, rcClient.bottom };
	::ClientToScreen(*this, &pt);
	m_helpMenu = new CMenuBuilder(L"helpMenus.xml");
	m_helpMenu->TrackPopupMenu(*this, pt.x, pt.y);
}

void CMainWindow::newFile(const CDuiString& name/*=L"" */)
{
	CDuiString filename = name;
	if (name == _T(""))
	{
		filename.Append(_T("Page"));
		filename.Append(std::to_wstring(m_pageNameVec.size()).c_str());
	}

	//创建标题按钮
	CPageLbButton *newBtn = new CPageLbButton();
	newBtn->SetText(filename);

	//创建主题窗口
	CWndUI *newUI = new CWndUI();
	CMfcPage *mfcw = new CMfcPage();
	mfcw->CreateEx(0,
		AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW, LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH), 0),
		filename,
		WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		50, 50, 500, 500,
		m_pm.GetPaintWindow(),
		NULL,
		NULL);
	HWND newWnd = mfcw->GetSafeHwnd();
	newUI->Attach(newWnd);

	m_pageLy->RemoveAll();
	m_pageLy->Add(newUI);
	m_labelFenceLy->AddAt(newBtn, m_labelFenceLy->GetCount()-1);

	//添加到vetcor
	m_wndUiVec.push_back(newUI);
	m_btnVec.push_back(newBtn);
	m_pageNameVec.push_back(filename);

	::ShowWindow(newWnd, SW_SHOW);
	clearAllPageTitleState();
	newBtn->SetChoosed(true);
	showPageByName(filename);

}

void CMainWindow::showPageByName(const CDuiString& name)
{
	m_pageLy->RemoveAll();
	for each (CWndUI* var in m_wndUiVec)
	{
		::ShowWindow(var->GetHwnD(), HIDE_WINDOW);
	}
	for (size_t i = 0; i < m_pageNameVec.size(); i++)
	{
		if (m_pageNameVec.at(i) == name)
		{
			m_pageLy->Add(m_wndUiVec.at(i));
			::ShowWindow(m_wndUiVec.at(i)->GetHwnD(), SW_SHOW);
		}
	}
}

void CMainWindow::showPageByBtn(TNotifyUI&msg)
{
	CControlUI *sender = msg.pSender;
	m_pageLy->RemoveAll();
	for each (CWndUI* var in m_wndUiVec)
	{
		::ShowWindow(var->GetHwnD(), HIDE_WINDOW);
	}
	std::vector<CButtonUI*>::iterator iter = std::find(m_btnVec.begin(), m_btnVec.end(), sender);
	for (size_t i = 0; i < m_btnVec.size(); i++)
	{
		if (m_btnVec.at(i) == sender)
		{
			if (msg.sType == DUI_MSGTYPE_BUTTON_CLOSEPAGE)
			{
				::ShowWindow(m_wndUiVec.at(i)->GetHwnD(), HIDE_WINDOW);
				m_pageLy->RemoveAll();
				delete m_wndUiVec.at(i);
				m_wndUiVec.erase(m_wndUiVec.begin()+i);

				m_labelFenceLy->RemoveAt(i);
				delete m_btnVec.at(i);
				m_btnVec.erase(m_btnVec.begin() + i);

				m_pageNameVec.erase(m_pageNameVec.begin()+i);
				if (!m_pageNameVec.empty())
				{
					showPageByName(m_pageNameVec.back());
				}
			}
			else
			{
				static_cast<CPageLbButton*>(m_btnVec.at(i))->SetChoosed(true);
				m_pageLy->Add(m_wndUiVec.at(i));
				::ShowWindow(m_wndUiVec.at(i)->GetHwnD(), SW_SHOW);
			}
		}
		else
		{
			static_cast<CPageLbButton*>(m_btnVec.at(i))->SetChoosed(false);
		}
	}
}



void CMainWindow::clearAllPageTitleState()
{
	for (size_t i = 0; i < m_btnVec.size(); i++)
	{
		static_cast<CPageLbButton*>(m_btnVec.at(i))->SetChoosed(false);
	}
}

void CMainWindow::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
		OnPrepare(msg);
	else if (msg.sType == DUI_MSGTYPE_BUTTON_CLOSEPAGE)
	{
		showPageByBtn(msg);
		return;
	}
	else if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pCloseBtn)
			return PostQuitMessage(0);

		else if (msg.pSender == m_pMinBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pMaxBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			return;
		}
		else if (msg.pSender == m_pRestoreBtn)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			return;
		}
		else if (msg.pSender == m_fileBtn)
		{
			OnFileMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_viewBtn)
		{
			OnViewMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_insetBtn)
		{
			OnInsetMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_chartBtn)
		{
			OnChartMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_toolBtn)
		{
			OnToolMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_windowBtn)
		{
			OnWindowMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_helpBtn)
		{
			OnHelpMenuShow(msg);
			return;
		}
		else if (msg.pSender == m_newPageBtn
			|| msg.pSender == m_toolnewBtn)
		{
			newFile();
			return;
		}
		else
		{
			showPageByBtn(msg);
		}
	}
}



LRESULT CMainWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return 0;
}


void CMainWindow::Create(const CDuiString& xml)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(xml.GetData(), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();

}

LRESULT CMainWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CMainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}

LRESULT CMainWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CMainWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMainWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMainWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("TextUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CMainWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		RECT rc = { rcWnd.left, rcWnd.top + szRoundCorner.cx, rcWnd.right, rcWnd.bottom };
		HRGN hRgn1 = ::CreateRectRgnIndirect(&rc);
		HRGN hRgn2 = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom - szRoundCorner.cx, szRoundCorner.cx, szRoundCorner.cy);
		::CombineRgn(hRgn1, hRgn1, hRgn2, RGN_OR);
		::SetWindowRgn(*this, hRgn1, TRUE);
		::DeleteObject(hRgn1);
		::DeleteObject(hRgn2);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CMainWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right;
	lpMMI->ptMaxSize.y = rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CMainWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(true);
		}
		else {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;
}

LRESULT CMainWindow::OnNewFile(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	newFile();
	return 0;
}

LRESULT CMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	case WM_NEWFILE_MSG:  lRes = OnNewFile(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}



