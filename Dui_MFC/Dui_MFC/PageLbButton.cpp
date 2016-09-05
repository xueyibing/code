#include "stdafx.h"
#include "PageLbButton.h"

CPageLbButton::CPageLbButton()
:m_isSelected(false),
m_isInClose(false)
{
	SetMaxWidth(120);
	SetBkImage(_T("..\\images\\titlebtnNormal.png"));

	SetTextColor(0x000000);
}

CPageLbButton::~CPageLbButton()
{

}


void CPageLbButton::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND) {
		if (m_pParent != NULL) m_pParent->DoEvent(event);
		else CButtonUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_MOUSEENTER)
	{
		if (IsEnabled())
		{
			if (m_isSelected)
			{
				SetBkImage(_T("..\\images\\titlebtnChosed_n.png"));
				SetTextColor(0xffffff);
			}
			else
			{
				SetBkImage(_T("..\\images\\titlebtnHover_n.png"));
				SetTextColor(0xffffff);
			}
			Invalidate();
		}
		return;
	}
	if (event.Type == UIEVENT_MOUSELEAVE)
	{
		if (IsEnabled())
		{
			if (m_isSelected)
			{
				SetBkImage(_T("..\\images\\titlebtnChosed_n.png"));
				SetTextColor(0xffffff);
			}
			else
			{
				SetBkImage(_T("..\\images\\titlebtnNormal.png"));
				SetTextColor(0x000000);
			}
			Invalidate();
		}
		return;
	}
	if (event.Type == UIEVENT_MOUSEMOVE)
	{
		POINT mouse_pt = { event.ptMouse.x, event.ptMouse.y };
		POINT this_pt = { GetPos().left, GetPos().top };
		POINT to_pt = { mouse_pt.x - this_pt.x, mouse_pt.y - this_pt.y };
		if (isPInRect(to_pt,m_closeRect))
		{
			if (m_isInClose == false)
			{
				m_isInClose = true;
				if (m_isSelected)
				{
					SetBkImage(_T("..\\images\\titlebtnChose_cc.png"));
					SetTextColor(0xffffff);
				}
				else
				{
					SetBkImage(_T("..\\images\\titlebtnHover_cc.png"));
					SetTextColor(0xffffff);
				}
			}
		}
		else
		{
			if (m_isInClose == true)
			{
				m_isInClose = false;
				if (m_isSelected)
				{
					SetBkImage(_T("..\\images\\titlebtnChosed_n.png"));
					SetTextColor(0xffffff);
				}
				else
				{
					SetBkImage(_T("..\\images\\titlebtnHover_n.png"));
					SetTextColor(0xffffff);
				}
			}

		}

		Invalidate();
	}
	if (event.Type == UIEVENT_BUTTONUP)
	{
		POINT mouse_pt = { event.ptMouse.x, event.ptMouse.y };
		POINT this_pt = { GetPos().left, GetPos().top };
		POINT to_pt = { mouse_pt.x - this_pt.x, mouse_pt.y - this_pt.y };
		if (isPInRect(to_pt, m_closeRect))
		{
		

			m_pManager->SendNotify(this, DUI_MSGTYPE_BUTTON_CLOSEPAGE, event.wParam, event.lParam);
			return;
		}
		else
		{
			m_isSelected = true;
			SetBkImage(_T("..\\images\\titlebtnChosed_n.png"));
			SetTextColor(0xffffff);
		}
	}

	CButtonUI::DoEvent(event);
}

void CPageLbButton::SetChoosed(const bool& b)
{
	m_isSelected = b;
	if (b)
	{
		SetBkImage(_T("..\\images\\titlebtnChosed_n.png"));
		SetTextColor(0xffffff);
	}
	else
	{
		SetBkImage(_T("..\\images\\titlebtnNormal.png"));
		SetTextColor(0x000000);
	}

	Invalidate();
}

bool CPageLbButton::isPInRect(const POINT&p, const CRect&r)
{

	m_closeRect.left = GetWidth() - GetHeight();
	m_closeRect.top = 0;
	m_closeRect.right = GetWidth();
	m_closeRect.bottom = GetHeight();

	if (p.x > m_closeRect.left && p.x<m_closeRect.right && p.y>m_closeRect.top && p.y < m_closeRect.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

