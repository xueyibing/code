#include "stdafx.h"
#include "PageWnd.h"

void CWndUI::SetInternVisible(bool bVisible /*= true*/)
{
	__super::SetInternVisible(bVisible);
	::ShowWindow(m_hWnd, bVisible);
}

void CWndUI::SetPos(RECT rc)
{
	__super::SetPos(rc);
	::SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CWndUI::Attach(HWND hWndNew)
{
	if (!::IsWindow(hWndNew))
	{
		return FALSE;
	}

	m_hWnd = hWndNew;
	return TRUE;
}

HWND CWndUI::Detach()
{
	HWND hWnd = m_hWnd;
	m_hWnd = NULL;
	return hWnd;
}

HWND CWndUI::GetHwnD()
{
	return m_hWnd;
}

