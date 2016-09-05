
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 移除对话框中的 MFC 控件支持

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


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







