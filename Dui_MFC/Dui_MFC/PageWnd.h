#ifndef MENUWND_H
#define MENUWND_H

// 将带句柄HWND的控件显示到CControlUI上面
class CWndUI : public CControlUI
{
public:
	CWndUI() : m_hWnd(NULL){}
	~CWndUI(){}


	virtual void SetInternVisible(bool bVisible = true);
	virtual void SetPos(RECT rc);

	BOOL Attach(HWND hWndNew);
	HWND Detach();
	HWND GetHwnD();

protected:
	HWND m_hWnd;
};

#endif