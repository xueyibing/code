#ifndef QCTRL_H
#define QCTRL_H
#include <afxwin.h>
#include"atltypes.h"



class QMemDC :	// 我把双缓存封装到类中，这样就方便多了
	public CDC
{
private:
	CDC* dcSrc;
	CRect rect;
	CBitmap bmp;
public:
	QMemDC(CDC* dc, CRect rc);
	void Apply();
};

class CMfcPage :
	public CWnd
{
protected:
	CString szClassName;
	bool isMouseIn;
	bool isPressed;
public:
	CMfcPage();
	~CMfcPage();
	bool Create(CWnd* pParent, CRect rc, CString text, DWORD id = 0, DWORD style = WS_VISIBLE | WS_CHILD);
protected:
	void PostClickEvent();
protected:
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	afx_msg void OnMouseHover(UINT nFlags,CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnIconbut0();
public:
	DECLARE_MESSAGE_MAP()


private:
	CButton	*m_btn;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#endif