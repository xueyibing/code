
// Dui_MFCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dui_MFC.h"
#include "Dui_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDui_MFCDlg �Ի���



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


// CDui_MFCDlg ��Ϣ�������

BOOL CDui_MFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//�����ļ���ʼ��
	if (!CONFIG->Initialize("./cfg.xml"))
	{
		return -1;
	}

	CWindowManager::GetInstance();
	CWindowManager::GetInstance()->SetBaseMfcHwnd(this->GetSafeHwnd());
	CMainWindow *pMainWindow =static_cast<CMainWindow*>(CWindowManager::GetInstance()->GetWindPtr(e_MainWind));
	MoveWindow(CONFIG->WindowRect.x, CONFIG->WindowRect.y, CONFIG->WindowRect.width, CONFIG->WindowRect.height);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDui_MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDui_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

