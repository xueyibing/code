
// Dui_MFCDlg.h : ͷ�ļ�
//

#pragma once
#include "MainWindow.h"

// CDui_MFCDlg �Ի���
class CDui_MFCDlg : public CDialog
{
// ����
public:
	CDui_MFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DUI_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


private:
	CMainWindow  m_mainWindow;
};
