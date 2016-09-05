#include "stdafx.h"
#include "MfcPage.h"

QMemDC::QMemDC(CDC* dc, CRect rc)
{
	dcSrc = dc;
	rect = rc;
	// �����ڴ�DC
	CreateCompatibleDC(dc);
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	SelectObject(bmp);
}

void QMemDC::Apply()
{
	// ���ڴ�DC���Ƶ��豸DC��
	dcSrc->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), this, 0, 0, SRCCOPY);
}

// QCtrl

CMfcPage::CMfcPage()
{
	isMouseIn = false;
	isPressed = false;
	// ע��ؼ���
	szClassName = AfxRegisterWndClass(0);

	//���캯��

}

CMfcPage::~CMfcPage()
{

}

bool CMfcPage::Create(CWnd* pParent, CRect rc, CString text, DWORD id /* = 0 */, DWORD style /* = WS_VISIBLE|WS_CHILD */)
{
	// ��̬�����ؼ�
	BOOL ret = CWnd::CreateEx(0, szClassName, text, style, rc, pParent, id);
	return ret ? true : false;
}

void CMfcPage::PostClickEvent()
{
	// �ú��������򸸴��ڷ��� ���� ��Ϣ
	CWnd* parent = GetParent();
	if (parent != NULL)
	{
		WPARAM wp = MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED);
		LPARAM lp = (LPARAM)m_hWnd;
		parent->PostMessage(WM_COMMAND, wp, lp);
	}
}

BEGIN_MESSAGE_MAP(CMfcPage, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()	// ����Ϣϵͳ����������Ƿ���
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_BN_CLICKED(12345, OnIconbut0)
END_MESSAGE_MAP()

// �����������Ƴ���Ϣ��Ҫ�����Լ�����
void CMfcPage::OnMouseMove(UINT nFlags, CPoint point)
{
	// ֻ��������һ�ν���ʱ�����
	if (!isMouseIn)
	{
		isMouseIn = true;

		TRACKMOUSEEVENT evt = { sizeof(evt), TME_LEAVE, m_hWnd, 0 };
		TrackMouseEvent(&evt);

		OnMouseHover(0, CPoint());
	}
}

void CMfcPage::OnMouseHover(UINT nFlags, CPoint point)
{
	// ������
	Invalidate();
}

void CMfcPage::OnMouseLeave()
{
	// ����뿪
	isMouseIn = false;
	isPressed = false;
	Invalidate();
}

void CMfcPage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// ��갴��
	isPressed = true;
	Invalidate();
}

void CMfcPage::OnLButtonUp(UINT nFlags, CPoint point)
{
	// ����ɿ�
	if (isPressed)
	{
		isPressed = false;
		Invalidate();

		PostClickEvent();
	}
}

BOOL CMfcPage::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// ��ֹ������������ֹ��˸
}

void CMfcPage::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	// ����˫���棬��ֹ��˸
	QMemDC mdc(&dc, rc);
	// ˢ����
	COLORREF bkgnd = RGB(255, 255, 255);
	if (isMouseIn)
	{
		if (isPressed)
			bkgnd = RGB(250, 0, 0);
		else
			bkgnd = RGB(180, 0, 0);
	}
	mdc.FillSolidRect(&rc, bkgnd);
	// ������������
	CFont font;
	font.CreatePointFont(110, _T("����"));	// 11�����壬�ò�����ʵ���������10���Ĺ�ϵ
	mdc.SelectObject(font);
	// ��ȡ����
	CString text;
	GetWindowText(text);
	// ������������
	mdc.SetBkMode(TRANSPARENT);
	mdc.SetTextColor(RGB(0, 0, 0));
	// �����ı�
	DWORD style = DT_SINGLELINE | DT_VCENTER | DT_CENTER;	// �ı���ʽ������+ˮƽ����+��ֱ����
	mdc.DrawText(text, -1, &rc, style);	// �����ı���ʾ��ʽ�ɲο��ٶȰٿ�DrawText˵��
	// ʹ������Ч
	mdc.Apply();
}




void CMfcPage::OnIconbut0()
{
	::SendMessage(this->GetParent()->GetSafeHwnd(), WM_COUNT_MSG,0,0);
//	this->GetParent()->SendMessage(WM_COUNT_MSG, 0, 0);

}

int CMfcPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_btn = new CButton();
	m_btn->Create(_T("��duilib����ܵ�\"�ļ�\"��ť,��Ϊ\"xxx\""), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(50, 50, 300, 50), this, 12345);
	m_btn->ShowWindow(SW_SHOWNORMAL);
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


