
// Dui_MFC.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Dui_MFC.h"
#include "Dui_MFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDui_MFCApp

BEGIN_MESSAGE_MAP(CDui_MFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDui_MFCApp ����

CDui_MFCApp::CDui_MFCApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDui_MFCApp ����

CDui_MFCApp theApp;


// CDui_MFCApp ��ʼ��

BOOL CDui_MFCApp::InitInstance()
{

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	AfxEnableControlContainer();

 	// ��׼��ʼ��
 	// ���δʹ����Щ���ܲ�ϣ����С
 	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
 	// ����Ҫ���ض���ʼ������
 	// �������ڴ洢���õ�ע�����
 	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
 	// �����޸�Ϊ��˾����֯��
  	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
  
  	CDui_MFCDlg dlg;
  	m_pMainWnd = &dlg;
  	INT_PTR nResponse = dlg.DoModal();
  	if (nResponse == IDOK)
  	{
  		// TODO:  �ڴ˷��ô����ʱ��
  		//  ��ȷ�������رնԻ���Ĵ���
  	}
  	else if (nResponse == IDCANCEL)
  	{
  		// TODO:  �ڴ˷��ô����ʱ��
  		//  ��ȡ�������رնԻ���Ĵ���
  	}
  	else if (nResponse == -1)
  	{
  		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
  	}







 
 	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
 	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

