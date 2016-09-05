#pragma once

class CDrawWCallBack : public IDialogBuilderCallback
{
public:
	CDrawWCallBack();
	~CDrawWCallBack(void);
	CControlUI* CreateControl(LPCTSTR pstrClass);
};

class CDrawWindow : public CWindowWnd
{
public:
	CDrawWindow();
	~CDrawWindow();

	virtual LPCTSTR GetWindowClassName() const;

	void Init(const CDuiString &xml,CPaintManagerUI *parent = NULL);
	
	void Show(POINT pos);

	void Notify(TNotifyUI& msg);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	CPaintManagerUI m_pm;

	
private:
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CControlUI* pRoot;

};

