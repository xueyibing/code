
// Dui_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDui_MFCApp: 
// �йش����ʵ�֣������ Dui_MFC.cpp
//

class CDui_MFCApp : public CWinApp
{
public:
	CDui_MFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDui_MFCApp theApp;