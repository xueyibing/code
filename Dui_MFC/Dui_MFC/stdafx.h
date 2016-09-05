
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // �Ƴ��Ի����е� MFC �ؼ�֧��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include "..\thirdLib\duilib\DuiLib\UIlib.h"
#include "MenuUI.h"
#include "Handle.h"
#include "PageLbButton.h"
#include "CConfigReader.h"
#include "WindowManager.h"
#include <iostream>


#define WM_COUNT_MSG WM_USER+100  
#define WM_NEWFILE_MSG WM_USER+101

#define DUI_MSGTYPE_BUTTON_CLOSEPAGE       (_T("closepage"))
#define DUI_MSGTYPE_KEYEVENT       (_T("keyevent"))

#if USE(DuiLib)

#define  CRect DuiLib::CRect

#define  CPoint DuiLib::CPoint

#define  CSize DuiLib::CSize

#else

#define CRect ::CRect

#define  CPoint ::CPoint

#define  CSize ::CSize

#endif

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\thirdLib\\duilib\\Lib\\DuiLib_d.lib")
#   else
#       pragma comment(lib, "..\\thirdLib\\duili\\Lib\\DuiLib.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\thirdLib\\duilib\\Lib\\DuiLib_d.lib")
#   else
#       pragma comment(lib, "..\\thirdLib\\duilib\\Lib\\DuiLib.lib")
#   endif
#endif

#define SKILL_ASSERT(expression) assert(expression)







