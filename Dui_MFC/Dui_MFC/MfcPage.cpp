#include "stdafx.h"
#include "MfcPage.h"

QMemDC::QMemDC(CDC* dc, CRect rc)
{
	dcSrc = dc;
	rect = rc;
	// 创建内存DC
	CreateCompatibleDC(dc);
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	SelectObject(bmp);
}

void QMemDC::Apply()
{
	// 将内存DC绘制到设备DC上
	dcSrc->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), this, 0, 0, SRCCOPY);
}

// QCtrl

CMfcPage::CMfcPage()
{
	isMouseIn = false;
	isPressed = false;
	// 注册控件类
	szClassName = AfxRegisterWndClass(0);

	//构造函数

}

CMfcPage::~CMfcPage()
{

}

bool CMfcPage::Create(CWnd* pParent, CRect rc, CString text, DWORD id /* = 0 */, DWORD style /* = WS_VISIBLE|WS_CHILD */)
{
	// 动态创建控件
	BOOL ret = CWnd::CreateEx(0, szClassName, text, style, rc, pParent, id);
	return ret ? true : false;
}

void CMfcPage::PostClickEvent()
{
	// 该函数用来向父窗口发送 单击 消息
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
	ON_WM_MOUSEHOVER()	// 此消息系统并不会给我们发送
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_BN_CLICKED(12345, OnIconbut0)
END_MESSAGE_MAP()

// 鼠标进入和鼠标移出消息需要我们自己监听
void CMfcPage::OnMouseMove(UINT nFlags, CPoint point)
{
	// 只处理鼠标第一次进入时的情况
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
	// 鼠标进入
	Invalidate();
}

void CMfcPage::OnMouseLeave()
{
	// 鼠标离开
	isMouseIn = false;
	isPressed = false;
	Invalidate();
}

void CMfcPage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 鼠标按下
	isPressed = true;
	Invalidate();
}

void CMfcPage::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 鼠标松开
	if (isPressed)
	{
		isPressed = false;
		Invalidate();

		PostClickEvent();
	}
}

BOOL CMfcPage::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;	// 阻止擦除背景，防止闪烁
}

void CMfcPage::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	// 采用双缓存，防止闪烁
	QMemDC mdc(&dc, rc);
	// 刷背景
	COLORREF bkgnd = RGB(255, 255, 255);
	if (isMouseIn)
	{
		if (isPressed)
			bkgnd = RGB(250, 0, 0);
		else
			bkgnd = RGB(180, 0, 0);
	}
	mdc.FillSolidRect(&rc, bkgnd);
	// 设置文字字体
	CFont font;
	font.CreatePointFont(110, _T("宋体"));	// 11号字体，该参数与实际字体号有10倍的关系
	mdc.SelectObject(font);
	// 获取文字
	CString text;
	GetWindowText(text);
	// 设置文字属性
	mdc.SetBkMode(TRANSPARENT);
	mdc.SetTextColor(RGB(0, 0, 0));
	// 绘制文本
	DWORD style = DT_SINGLELINE | DT_VCENTER | DT_CENTER;	// 文本格式：单行+水平居中+垂直居中
	mdc.DrawText(text, -1, &rc, style);	// 更多文本显示格式可参考百度百科DrawText说明
	// 使绘制生效
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
	m_btn->Create(_T("将duilib主框架的\"文件\"按钮,改为\"xxx\""), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(50, 50, 300, 50), this, 12345);
	m_btn->ShowWindow(SW_SHOWNORMAL);
	// TODO:  在此添加您专用的创建代码

	return 0;
}


