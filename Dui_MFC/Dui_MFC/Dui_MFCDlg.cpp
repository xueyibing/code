
// Dui_MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dui_MFC.h"
#include "Dui_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDui_MFCDlg 对话框



CDui_MFCDlg::CDui_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDui_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDui_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDui_MFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CDui_MFCDlg 消息处理程序

BOOL CDui_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//配置文件初始化
	if (!CONFIG->Initialize("./cfg.xml"))
	{
		return -1;
	}

	CWindowManager::GetInstance();
	CWindowManager::GetInstance()->SetBaseMfcHwnd(this->GetSafeHwnd());
	CMainWindow *pMainWindow =static_cast<CMainWindow*>(CWindowManager::GetInstance()->GetWindPtr(e_MainWind));
	MoveWindow(CONFIG->WindowRect.x, CONFIG->WindowRect.y, CONFIG->WindowRect.width, CONFIG->WindowRect.height);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDui_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDui_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

