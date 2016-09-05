#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>
#include <objbase.h>
#include <zmouse.h>
#include <exdisp.h>
#include "stdafx.h"
#include "PageWnd.h"

#include "MenuUI.h"
#include <map>


#define WM_ADDLISTITEM WM_USER + 50

class CMainWindow : public CWindowWnd, public INotifyUI
{
public:
	CMainWindow();

	void Create(const CDuiString& xml);
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);
	void Init();
	void OnPrepare(TNotifyUI& msg);
	void Notify(TNotifyUI& msg);

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNewFile(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	CPaintManagerUI m_pm;

private:
	void OnFileMenuShow(TNotifyUI& msg);
	void OnViewMenuShow(TNotifyUI& msg);
	void OnInsetMenuShow(TNotifyUI& msg);
	void OnChartMenuShow(TNotifyUI& msg);
	void OnToolMenuShow(TNotifyUI& msg);
	void OnWindowMenuShow(TNotifyUI& msg);
	void OnHelpMenuShow(TNotifyUI& msg);

	void newFile(const CDuiString& name=_T("") );
	void showPageByName(const CDuiString& name);
	void showPageByBtn(TNotifyUI&msg);
	void clearAllPageTitleState();



private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pMinBtn;
	CButtonUI* m_pRestoreBtn;
	
	//标题栏按钮
	CButtonUI* m_fileBtn;
	CButtonUI* m_viewBtn;
	CButtonUI* m_insetBtn;
	CButtonUI* m_chartBtn;
	CButtonUI* m_toolBtn;
	CButtonUI* m_windowBtn;
	CButtonUI* m_helpBtn;

	//工具栏按钮
	CButtonUI* m_toolnewBtn;
	CButtonUI* m_toolopenBtn;

	CButtonUI* m_newPageBtn;


	//菜单
	CMenuBuilder	*m_fileMenu;
	CMenuBuilder	*m_viewMenu;
	CMenuBuilder	*m_insetMenu;
	CMenuBuilder	*m_chartMenu;
	CMenuBuilder	*m_toolMenu;
	CMenuBuilder	*m_windowMenu;
	CMenuBuilder	*m_helpMenu;

	CHorizontalLayoutUI  *m_labelFenceLy;
	CHorizontalLayoutUI  *m_pageLy;
	HMODULE m_scintillaMode;

	std::vector<CWndUI*> m_wndUiVec;
	std::vector<CButtonUI*> m_btnVec;
	std::vector<CDuiString> m_pageNameVec;
};

#endif