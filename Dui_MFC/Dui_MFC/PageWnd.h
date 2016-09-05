#ifndef MENUWND_H
#define MENUWND_H

// �������HWND�Ŀؼ���ʾ��CControlUI����
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