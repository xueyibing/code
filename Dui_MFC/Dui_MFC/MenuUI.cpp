#include "StdAfx.h"
#include "MenuUI.h"

CMenuElementUI::CMenuElementUI()
	:m_bHaveExtend(false)
	,m_bExtendMenuShow(false)
{
	
}


void CMenuElementUI::Notify(TNotifyUI& msg)
{
	TRACE("Notify");
	if (msg.sType == DUI_MSGTYPE_KEYEVENT)
	{
		OnShortKeyEvent(msg);

	}

}

void CMenuElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if( _tcscmp(pstrName, _T("extendmenu")) == 0 ) 
	{
		m_bHaveExtend = true;
		m_ExtendMenuName = pstrValue;
	}else if (_tcscmp(pstrName, _T("command")) == 0)
	{
		m_MenuCmd = pstrValue;
	}
	else if (_tcscmp(pstrName, _T("shortkey")) == 0)
	{
		m_ShortKey = pstrValue;
	}

	CListContainerElementUI::SetAttribute(pstrName,pstrValue);
}


LPVOID CMenuElementUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("MenuItem")) == 0 ) 
		return static_cast<CMenuElementUI*>(this);
	return CListContainerElementUI::GetInterface(pstrName);
}


void CMenuElementUI::SetMenuOwner(CMenuUI* owner)
{
	m_pMenuOwner = owner;
}

void CMenuElementUI::DoEvent(TEventUI& event)
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
		if( m_pOwner != NULL ) m_pOwner->DoEvent(event);
		else CContainerUI::DoEvent(event);
		return;
	}

	if( event.Type == UIEVENT_DBLCLICK )
	{
		if( IsEnabled() ) {
			Activate();
			Invalidate();
		}
		return;
	}
	if( event.Type == UIEVENT_KEYDOWN && IsEnabled() )
	{
		if( event.chKey == VK_RETURN )
		{
			Activate();
			Invalidate();
			return;
		}
	}
	if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_RBUTTONDOWN )
	{
		if( IsEnabled() )
		{
         // m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
		  Select();
		  Invalidate();
		}
		return;
	}
	if( event.Type == UIEVENT_BUTTONUP ) 
	{
		if( IsEnabled() ){
			m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
			if (m_pMenuOwner)
			{
				m_pMenuOwner->OnMenuItemClick(this);
			}
		}
		return;
	}
	if( event.Type == UIEVENT_MOUSEMOVE )
	{
		return;
	}
	if( event.Type == UIEVENT_MOUSEENTER )
	{
		if( IsEnabled() ) {
			m_uButtonState |= UISTATE_HOT;
			if (m_pMenuOwner)
			{
				m_pMenuOwner->OnItemHover(this);
			}
			Invalidate();
		}
		return;
	}
	if( event.Type == UIEVENT_MOUSELEAVE )
	{
		if( (m_uButtonState & UISTATE_HOT) != 0 ) {
			m_uButtonState &= ~UISTATE_HOT;
			if (m_pMenuOwner)
			{
				m_pMenuOwner->OnItemLeave(this);
			}
			Invalidate();
		}
		return;
	}
}


void CMenuElementUI::ShowSubMenu()
{
	int x = this->GetX()+m_pMenuOwner->GetWidth();
	int y = this->GetY()-3;
	int interval = m_pMenuOwner->GetMenuBuilder()->GetMenuContainer()->GetInterval();

	// �����Ӳ˵��ڳ�����ʾ��ʱ��λ��
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(m_pExtendMenu->GetMenuWnd()->GetHWND(), MONITOR_DEFAULTTONEAREST), &oMonitor);
	RECT rcArea = oMonitor.rcWork;

	POINT p = {x+interval,y};
	ClientToScreen(m_pManager->GetPaintWindow(),&p);
	int width = m_pExtendMenu->GetFixedWidth();
	if (p.x+width>rcArea.right)
	{
		p.x = p.x-this->GetWidth() - m_pExtendMenu->GetFixedWidth();
		p.x-= 2*interval;
	}

	m_pExtendMenu->ShowMenu(p);
	m_bExtendMenuShow = true;
}



void CMenuElementUI::HideSubMenu()
{
	if (m_bHaveExtend&&m_bExtendMenuShow==true)
	{
		m_pExtendMenu->HideMenu();
		SetExtenMenuShow(false);
		m_pExtendMenu->SetCurItem(NULL);
	}
}

void CMenuElementUI::OnShortKeyEvent(TNotifyUI& msg)
{
	if (!m_ShortKey.IsEmpty())
	{
		if (msg.wParam == (WPARAM)m_ShortKey.GetAt(0))
		{
			if (IsEnabled()) 
			{
				if (m_bHaveExtend)
				{
					m_pMenuOwner->OnItemHover(this);
				}
				else
				{
					m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
					if (m_pMenuOwner)
					{
						m_pMenuOwner->OnMenuItemClick(this);
					}
				}
			}
		}
	}
}

void CMenuElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	CContainerUI::DoPaint(hDC, rcPaint);
}




bool CMenuElementUI::IsHaveExtend()
{
	return m_bHaveExtend;
}


bool CMenuElementUI::IsExtendMenuShow()
{
	return m_bExtendMenuShow;
}

void CMenuElementUI::SetExtenMenuShow(bool b)
{
	m_bExtendMenuShow = b;
}

CDuiString CMenuElementUI::GetExtendMenuName()
{
	return m_ExtendMenuName;
}

void CMenuElementUI::SetExtendMenu(CMenuUI* pMenu)
{
	m_pExtendMenu = pMenu;
}

CMenuUI* CMenuElementUI::GetExtendMenu()
{
	return m_pExtendMenu;
}


CDuiString   CMenuElementUI::GetMenuCmd()
{
	return m_MenuCmd;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
LPVOID CStaticMenuElementUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("StaticMenuItem")) == 0 ) return static_cast<CStaticMenuElementUI*>(this);
	return CListContainerElementUI::GetInterface(pstrName);
}

void CStaticMenuElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
	return CContainerUI::DoPaint(hDC,rcPaint);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/




CMenuWnd::CMenuWnd(void)
	:m_pMenui(NULL)
{
}


CMenuWnd::~CMenuWnd(void)
{

}

LPCTSTR CMenuWnd::GetWindowClassName() const
{
	return L"MenuWndCls";
}

LRESULT CMenuWnd::OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}


LRESULT CMenuWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LPRECT pRect=NULL;

	if ( wParam == TRUE)
	{
		LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
		pRect=&pParam->rgrc[0];
	}
	else
	{
		pRect=(LPRECT)lParam;
	}

	if ( ::IsZoomed(m_hWnd))
	{	// ���ʱ�����㵱ǰ��ʾ�����ʺϿ��߶�
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		CDuiRect rcWork = oMonitor.rcWork;
		CDuiRect rcMonitor = oMonitor.rcMonitor;
		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		pRect->right = pRect->left + rcWork.GetWidth();
		pRect->bottom = pRect->top + rcWork.GetHeight();
		return WVR_REDRAW;
	}

	return 0;
}


void CMenuWnd::OnFinalMessage(HWND hWnd)
{
	delete this;
}


LRESULT CMenuWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	if (uMsg==WM_CREATE)
	{
		m_pm.Init(m_hWnd);
	}else if (uMsg == WM_MOUSEACTIVATE)
	{
		return MA_NOACTIVATE;
	}else if (uMsg == WM_CLOSE)
	{
		UnBindControl(m_pm.GetRoot());
	}else if (uMsg==WM_MOUSEMOVE)
	{
		//MessageBox(0,0,0,0);
	}else if (uMsg==WM_RBUTTONDOWN)
	{
		return lRes;
	}else if (uMsg==WM_LBUTTONDOWN)
	{
		//MessageBox(0,L"����������",0,0);
	}else if (uMsg==WM_KEYDOWN)
	{
		if (m_pMenui)
		{
			if (wParam==VK_LEFT)
			{
				m_pMenui->OnVkLeft();
			}else if (wParam==VK_RIGHT)
			{
				m_pMenui->OnVkRight();
			}else if (wParam==VK_UP)
			{
				m_pMenui->OnVkUp();
			}else if (wParam==VK_DOWN)
			{
				m_pMenui->OnVkDown();
			}else if (wParam==VK_RETURN)
			{
				m_pMenui->OnVkReturn();
			}
			else
			{
				m_pm.SendNotify(NULL, DUI_MSGTYPE_KEYEVENT, wParam, lParam);
			}

		}

	}

	if (!bHandled)
	{
		return lRes;
	}
	// 		}else if (uMsg==WM_PAINT)
	// 		{
	// 			if (m_PaintManager.OnPaint(uMsg, wParam, lParam, lRes))
	// 				return lRes;
	// 		}

	if(m_pm.MessageHandler(uMsg,wParam,lParam,lRes))
		return lRes;


	return CWindowWnd::HandleMessage(uMsg,wParam,lParam);
}


void CMenuWnd::BindControl(CControlUI* pControl)
{
	ASSERT(pControl);
	m_pm.SetUnfocusPaintWindow(true);
	m_pm.AttachDialog(pControl,false);
	m_pm.AddFont(_T("����"), 12, false, false,false);
}


void CMenuWnd::UnBindControl(CControlUI* pControl)
{
	pControl->SetManager(NULL,NULL);
}


void CMenuWnd::ShowMenuWnd(bool b)
{
	ShowWindow(b,false);
}


void CMenuWnd::AddNotifier(INotifyUI* pNotify)
{
	m_pm.AddNotifier(pNotify);
}
void CMenuWnd::SetMenuOwner(CMenuUI* pOwner){
	m_pMenui = pOwner;
}

void CMenuWnd::SetBktrans(bool b)
{
	m_pm.SetBackgroundTransparent(b);
}
/************************************************************************/
/*																									 */
/************************************************************************/
inline void MenuWndClose(CMenuWnd* p)
{
	p->SendMessage(WM_CLOSE,0,0);
}

void CMenuUI::OnMenuItemClick(CControlUI* pControl)
{
	CMenuElementUI* pMenuItem = static_cast<CMenuElementUI*>(pControl->GetInterface(_T("MenuItem")));
	if (pMenuItem)
	{
		SKILL_ASSERT(m_pMenuBuilder);
		if (!pMenuItem->IsHaveExtend())
		{
			m_pMenuBuilder->ExitMenu(pMenuItem->GetMenuCmd());
			CMenuElementUI *menuel = static_cast<CMenuElementUI*>(pControl);
			CDuiString cmd = menuel->GetMenuCmd();
			COperageHandle::GetInstance()->HandleMenuCmd(cmd);
		}

	}
	else
	{

	}


}

void CMenuUI::AddNotify(INotifyUI* pNotify)
{
	m_pMenuWnd->AddNotifier(pNotify);
}

void CMenuUI::Notify(TNotifyUI& msg)
{
	
	if (msg.sType == _T("windowinit"))
	{
	}
	else  if (msg.sType == _T("itemclick"))
	{
	}
	else if (msg.sType == _T("click"))
	{
		TRACE("click\n");
	}
	else if (msg.sType == DUI_MSGTYPE_KEYEVENT)
	{
		int c = GetCount();
		for (int i = 0; i < GetCount();++i)
		{
			CControlUI* p = GetItemAt(i);
			CMenuElementUI* pme = static_cast<CMenuElementUI*>(p->GetInterface(_T("MenuItem")));
			if (pme != NULL )
			{
				//pme->OnShortKeyEvent(msg);
			}
		}
	}
}

CMenuUI::CMenuUI()
	:m_bMajor(false)
	,m_bSubMenuShow(false)
	,m_pCurSubMenu(NULL)
	,m_pMenuBuilder(NULL)
	,m_pCurItem(NULL)
	,m_pSuperMenu(NULL)
{
	GetHeader()->SetVisible(false);
	m_pMenuWnd = new CMenuWnd;
	//m_pMenuWnd.reset(pMenuWnd,MenuWndClose);
}

CMenuUI::~CMenuUI()
{
	MenuWndClose(m_pMenuWnd);
}

void CMenuUI::InitMenu(HWND ownerWnd)
{
	m_pMenuWnd->Create(ownerWnd,L"Menu",WS_POPUP,WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TOOLWINDOW);
	m_pMenuWnd->BindControl(this);
	m_pMenuWnd->AddNotifier(this);
	m_pMenuWnd->SetMenuOwner(this);
}


LPVOID CMenuUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, _T("Menu")) == 0 ) return static_cast<CMenuUI*>(this);

	return CListUI::GetInterface(pstrName);
}

void CMenuUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if( _tcscmp(pstrName, _T("major")) == 0 ) 
	{
		if (_tcscmp(pstrValue, _T("true")) == 0 ) m_bMajor = true;   
	}else if(_tcscmp(pstrName, _T("bktrans")) == 0)
	{
		if (_tcscmp(pstrValue, _T("true")) == 0 ) m_pMenuWnd->SetBktrans(true);
	}


	CListUI::SetAttribute(pstrName,pstrValue);
}

bool CMenuUI::Add(CControlUI* pControl)
{
	CMenuElementUI* pMenuItem = static_cast<CMenuElementUI*>(pControl->GetInterface(_T("MenuItem")));
	if( pMenuItem != NULL ) {
		pMenuItem->SetMenuOwner(this);
	}
	return CListUI::Add(pControl);
}

void CMenuUI::ShowMenu(POINT p)
{ 
	m_pMenuBuilder->SetActiveMenu(this);
	::MoveWindow(*m_pMenuWnd,p.x,p.y,this->GetFixedWidth(),this->GetFixedHeight(),false);
	m_pMenuWnd->ShowMenuWnd(true);
}

void CMenuUI::HideMenu()
{
	if (!IsMajor())
	{
		SKILL_ASSERT(m_pSuperMenu);
		m_pMenuBuilder->SetActiveMenu(m_pSuperMenu);
		m_pMenuWnd->ShowMenuWnd(false);
	}

    if (m_pCurItem)
    {
		m_pCurItem->HideSubMenu();
	
    }
}

void CMenuUI::SetSuperMenu(CMenuUI* p)
{
	m_pSuperMenu = p;
}
void CMenuUI::OnItemHover(CControlUI* pControl)
{
	CMenuElementUI* pMenuItem = static_cast<CMenuElementUI*>(pControl->GetInterface(_T("MenuItem")));
	
	if (pMenuItem==NULL) return;
	SetCurItem(pMenuItem);
	ShowSubMenu(pMenuItem);
}

void CMenuUI::OnItemLeave(CControlUI* pControl)
{
	CMenuElementUI* pMenuItem = static_cast<CMenuElementUI*>(pControl->GetInterface(_T("MenuItem")));

	if (pMenuItem==NULL) return;


	if (!pMenuItem->IsExtendMenuShow())
	{
		OnItemUnHot(pMenuItem);
		m_pCurItem = NULL;
	}

}


void CMenuUI::OnItemHot(CMenuElementUI* pMenuItem)
{
	CLabelUI* pControl = (CLabelUI*)m_pManager->FindSubControlByName(pMenuItem, L"menu_label");
	pMenuItem->SetBkColor(0xffb8b8b8);
	pControl->SetTextColor(0xffffffff);

	CControlUI* pIco = m_pManager->FindSubControlByName(pMenuItem, L"ico");
	CControlUI* pIcoHover = m_pManager->FindSubControlByName(pMenuItem, L"ico_hover");

	if (pIco&&pIcoHover)
	{
		pIco->SetVisible(false);
		pIcoHover->SetVisible(true);
	}

	CControlUI* pExtend = m_pManager->FindSubControlByName(pMenuItem, L"extend");
	CControlUI* pExtend_Hover = m_pManager->FindSubControlByName(pMenuItem, L"extend_hover");

	if (pExtend&&pExtend_Hover)
	{
		pExtend->SetVisible(false);
		pExtend_Hover->SetVisible(true);
	}

}

void CMenuUI::OnItemUnHot(CMenuElementUI* pMenuItem)
{
	CLabelUI* pControl = (CLabelUI*)m_pManager->FindSubControlByName(pMenuItem, L"menu_label");
	pMenuItem->SetBkColor(0x00ffffff);
	pControl->SetTextColor(0xffffffff);
	CControlUI* pIco = m_pManager->FindSubControlByName(pMenuItem, L"ico");
	CControlUI* pIcoHover = m_pManager->FindSubControlByName(pMenuItem, L"ico_hover");
	if (pIco&&pIcoHover)
	{
		pIco->SetVisible(true);
		pIcoHover->SetVisible(false);
	}

	CControlUI* pExtend = m_pManager->FindSubControlByName(pMenuItem, L"extend");
	CControlUI* pExtend_Hover = m_pManager->FindSubControlByName(pMenuItem, L"extend_hover");

	if (pExtend&&pExtend_Hover)
	{
		pExtend->SetVisible(true);
		pExtend_Hover->SetVisible(false);
	}
}


CMenuElementUI* CMenuUI::GetCurItem()
{
	return m_pCurItem;
}
void CMenuUI::SetCurItem(CMenuElementUI* pMenuItem)
{
	if (pMenuItem==NULL||!pMenuItem->IsEnabled())
	{
		m_pCurItem = pMenuItem;
		return;
	}
	m_pCurItem = pMenuItem;

	OnItemHot(pMenuItem);
	for (int i=0;i<GetCount();i++)
	{
		CControlUI* p = GetItemAt(i);
		CMenuElementUI* pc = static_cast<CMenuElementUI*>(p->GetInterface(_T("MenuItem")));
		if (pc==NULL) continue;
		if (pMenuItem==pc)
		{

		}else{

			OnItemUnHot(pc);
		}
	}
}



void CMenuUI::ShowSubMenu(CMenuElementUI* pMenuItem)
{
	if (pMenuItem==NULL) return;
	for (int i=0;i<GetCount();i++)
	{
		CControlUI* p = GetItemAt(i);
		CMenuElementUI* pc = static_cast<CMenuElementUI*>(p->GetInterface(_T("MenuItem")));
		if (pc==NULL) continue;
		if (pMenuItem==pc)
		{

		}
		else
		{
			if (pc->IsExtendMenuShow())
			{
				pc->HideSubMenu();
			}
		}
	}

	m_pCurItem = pMenuItem;
	if (m_pCurItem->IsHaveExtend())
	{
		if(!m_pCurItem->IsExtendMenuShow())
		{
			m_pCurItem->ShowSubMenu();
		}
		m_bSubMenuShow = true;
		m_pCurSubMenu = m_pCurItem->GetExtendMenu();
		
	}else{
		m_bSubMenuShow = false;
		m_pCurSubMenu = NULL;
	}

}




CMenuElementUI* CMenuUI::GetNextItem()
{
	int index = -1;
	if (m_pCurItem!=NULL)
	{
		index = GetItemIndex(m_pCurItem);
	}

	for (int i=index+1;i<GetCount();i++)
	{
		CControlUI* p = GetItemAt(i);
		CMenuElementUI* pc = static_cast<CMenuElementUI*>(p->GetInterface(_T("MenuItem")));
		if (pc==NULL) continue;

		return pc;
	}
	m_pCurItem=NULL;
	return GetNextItem();
}

CMenuElementUI* CMenuUI::GetPrevItem()
{
	int index = GetCount();
	if (m_pCurItem!=NULL)
	{
		index = GetItemIndex(m_pCurItem);
	}

	for (int i=index-1;i>=0;i--)
	{
		CControlUI* p = GetItemAt(i);
		CMenuElementUI* pc = static_cast<CMenuElementUI*>(p->GetInterface(_T("MenuItem")));
		if (pc==NULL) continue;

		return pc;
	}
	m_pCurItem=NULL;
	return GetPrevItem();
}



bool  CMenuUI::IsMajor()
{
	return m_bMajor;
}

bool CMenuUI::IsExtenMenuShow()
{
	return m_bSubMenuShow;
}

CMenuUI* CMenuUI::GetCurExtendMenu()
{
	return m_pCurSubMenu;
}

void CMenuUI::SetMenuBuilder(CMenuBuilder* p)
{
	m_pMenuBuilder = p;
}

CMenuBuilder* CMenuUI::GetMenuBuilder()
{
	return m_pMenuBuilder;
}

HWND CMenuUI::GetHandle()
{
	return m_pMenuWnd->GetHWND();
}

CMenuWnd* CMenuUI::GetMenuWnd()
{
	return m_pMenuWnd;
}

void CMenuUI::OnVkLeft()
{
	if(IsMajor()) return;
	SKILL_ASSERT(m_pSuperMenu);
	CMenuElementUI* p = m_pSuperMenu->GetCurItem();
	if (p)
	{
		p->HideSubMenu();
	}
}


void CMenuUI::OnVkRight()
{
	ShowSubMenu(m_pCurItem);
	if (m_pCurSubMenu)
	{
		m_pCurSubMenu->SetCurItem(m_pCurSubMenu->GetNextItem());
	}
}

void CMenuUI::OnVkUp()
{
	CMenuElementUI* p= GetPrevItem();
	SetCurItem(p);
}

void CMenuUI::OnVkDown()
{
	CMenuElementUI* p= GetNextItem();
	SetCurItem(p);
}

void CMenuUI::OnVkReturn()
{
	if (m_pCurItem)
	{
		SKILL_ASSERT(m_pMenuBuilder);
		if (!m_pCurItem->IsHaveExtend())
		{
			m_pMenuBuilder->ExitMenu(m_pCurItem->GetMenuCmd());
		}else{
			ShowSubMenu(m_pCurItem);
			if (m_pCurSubMenu)
			{
				m_pCurSubMenu->SetCurItem(m_pCurSubMenu->GetNextItem());
			}
		}
	}else{

	}
}
/************************************************************************/
/*                                                                      */
/************************************************************************/


CMenuContainer::CMenuContainer()
	:m_nInterval(0)
	,m_bKeyEvent(false)
{

}


void CMenuContainer::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if( _tcscmp(pstrName, _T("interval")) == 0 ) 
	{
		LPTSTR pstr = NULL;
		m_nInterval = _tcstol(pstrValue, &pstr, 10); 
	}else if (_tcscmp(pstrName, _T("keyevent")) == 0)
	{
		 if (_tcscmp(pstrValue, _T("true")) == 0) m_bKeyEvent = true;
	}
	

	CContainerUI::SetAttribute(pstrName,pstrValue);
}

int CMenuContainer::GetInterval()
{
	return m_nInterval;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

void CMenuBuilder::LoadFromXml(LPCTSTR xmlName)
{
	CDialogBuilder* pBuiler = new CDialogBuilder();
	m_menus = static_cast<CMenuContainer*>(pBuiler->Create(xmlName,NULL,this));

	int count = m_menus->GetCount();
	for (int i=0;i<count;i++)
	{
		CControlUI* pControl = m_menus->GetItemAt(i);
		CMenuUI* pMenu = static_cast<CMenuUI*>(pControl->GetInterface(_T("Menu")));
		pMenu->InitMenu(NULL);
		pMenu->SetMenuBuilder(this);
		if(pMenu->IsMajor()) 
		{
			SKILL_ASSERT(!m_pActiveMenu);
			m_pActiveMenu = pMenu;
		}
		for (int j=0;j<pMenu->GetCount();j++)
		{
			CControlUI* pControl = pMenu->GetItemAt(j);
			CMenuElementUI* pMenuItem = static_cast<CMenuElementUI*>(pControl->GetInterface(_T("MenuItem")));
			
			if( pMenuItem != NULL ) 
			{
				pMenu->AddNotify(pMenuItem);
				if ( pMenuItem->IsHaveExtend())
				{
					CMenuUI* pSubMenu = FindMenuByName(pMenuItem->GetExtendMenuName());
					SKILL_ASSERT(pSubMenu);
					pMenuItem->SetExtendMenu(pSubMenu);
					pSubMenu->SetSuperMenu(pMenu);
				
				}		
			}
		}
	}

	m_bMenusExsit = true;
}




CMenuUI* CMenuBuilder::FindMenuByName(LPCTSTR pName)
{
	for (int i=0;i<m_menus->GetCount();i++)
	{
		CControlUI* pControl = m_menus->GetItemAt(i);
		CMenuUI* pMenu = static_cast<CMenuUI*>(pControl->GetInterface(_T("Menu")));
		ASSERT(pMenu!=NULL);
		if (_tcscmp(pMenu->GetName(),pName)==0)
		{
			return pMenu;
		}
	}

	return NULL;
}

CControlUI* CMenuBuilder::CreateControl(LPCTSTR pstrClass)
{
	if (_tcscmp(pstrClass,_T("Menu"))==0)
	{
		return new CMenuUI;
	}else if(_tcscmp(pstrClass,_T("MenuItem"))==0)
	{
		return new CMenuElementUI;
	}else if (_tcscmp(pstrClass,_T("StaticMenuItem"))==0)
	{
		return new CStaticMenuElementUI;
	}
	else if(_tcscmp(pstrClass,_T("MenuContainer"))==0)
	{
		return new CMenuContainer;
	}
	else if (_tcscmp(pstrClass, L"MyMenu") == 0)
	{
		return new CMenuUI;
	}
	return NULL;

}


void CMenuBuilder::DestroyMenu()
{
	SKILL_ASSERT(m_bMenusExsit);
	if (m_bMenusExsit)
	{
		delete m_menus;
		m_bMenusExsit = false;
	}

}

LPCTSTR CMenuBuilder::TrackPopupMenu(HWND hwndParent,int x,int y)
{
	int nRet(-1);
	m_menuRet.bExit = false;
	m_menuRet.command = _T("null");
	m_hWndOwner = hwndParent;
	LoadFromXml(m_xmlName);

	// �������˵��ڳ�����ʾ��ʱ��λ��
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(m_pActiveMenu->GetMenuWnd()->GetHWND(), MONITOR_DEFAULTTONEAREST), &oMonitor);
	RECT rcArea = oMonitor.rcWork;

	if (x+m_pActiveMenu->GetFixedWidth()>rcArea.right)
	{
		x = rcArea.right - m_pActiveMenu->GetFixedWidth();
	}

	if (y+m_pActiveMenu->GetFixedHeight()>rcArea.bottom)
	{
		y =y - m_pActiveMenu->GetFixedHeight();
        if(y<rcArea.top)
		{
			y = rcArea.bottom - m_pActiveMenu->GetFixedHeight();
		}

	}

	POINT p = {x,y};
	m_pActiveMenu->ShowMenu(p);
	RunMenu();
	m_hWndOwner = NULL;
	m_pActiveMenu = NULL;
	return m_menuRet.command;
}

bool CMenuBuilder::IsMenuWnd(HWND hwnd)
{
	int count = m_menus->GetCount();
	for (int i=0;i<count;i++)
	{
		CControlUI* pControl = m_menus->GetItemAt(i);
		CMenuUI* pMenu = static_cast<CMenuUI*>(pControl->GetInterface(_T("Menu")));
		SKILL_ASSERT(pMenu);

		if (pMenu->GetMenuWnd()->GetHWND()==hwnd)
		{
			return true;
		}
	}
	return false;
}

int CMenuBuilder::RunMenu()
{
	
	int nRet(-1);
	BOOL bMenuDestroyed(FALSE);
	BOOL bMsgQuit(FALSE);
	while(TRUE)
	{

		if(m_menuRet.bExit)
		{
			nRet = 0;
			break;
		}

		if(GetForegroundWindow() != m_hWndOwner)
		{
			break;
		}
		BOOL bInterceptOther(FALSE);
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_KEYDOWN
				|| msg.message == WM_SYSKEYDOWN
				|| msg.message == WM_KEYUP
				|| msg.message == WM_SYSKEYUP
				|| msg.message == WM_CHAR
				|| msg.message == WM_IME_CHAR)
			{
				//transfer the message to menu window
				if (m_menus->IsKeyEvent())
				{
					SKILL_ASSERT(m_pActiveMenu->GetMenuWnd()->GetHWND());
					msg.hwnd = m_pActiveMenu->GetMenuWnd()->GetHWND();
				}
			}
			else if(msg.message == WM_LBUTTONDOWN
				|| msg.message  == WM_RBUTTONDOWN
				|| msg.message  == WM_NCLBUTTONDOWN
				|| msg.message  == WM_NCRBUTTONDOWN
				||msg.message   ==WM_LBUTTONDBLCLK)
			{
				//click on other window
				if(!IsMenuWnd(msg.hwnd))
				{
					DestroyMenu();
					//Ϊ�˺Ͳ˵��ٴεĵ�����Ϣͬ��
					::PostMessage(msg.hwnd,msg.message,msg.wParam,msg.lParam);
					bInterceptOther = true;
					bMenuDestroyed = TRUE;

				}
			}else if (msg.message == WM_LBUTTONUP
				||msg.message==WM_RBUTTONUP
				||msg.message==WM_NCLBUTTONUP
				||msg.message==WM_NCRBUTTONUP
				||msg.message==WM_CONTEXTMENU)
			{
				if(!IsMenuWnd(msg.hwnd))
				{
					//��ֹ�˵�ͬʱ�������
					::PostMessage(msg.hwnd,msg.message,msg.wParam,msg.lParam);
					break;
				}
			}
			else if(msg.message == WM_QUIT)
			{
				bMsgQuit = TRUE;
			}

			//���طǲ˵����ڵ�MouseMove��Ϣ
			if (msg.message == WM_MOUSEMOVE)
			{
				if (!IsMenuWnd(msg.hwnd))
				{
					bInterceptOther=TRUE;
				}
			}

			if (!bInterceptOther)
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}

		}
		else
		{
			MsgWaitForMultipleObjects (0, 0, 0, 10, QS_ALLINPUT);
		}

		if(bMenuDestroyed) break;

		if(bMsgQuit)
		{
			PostQuitMessage(msg.wParam);
			break;
		}
	}

	if(!bMenuDestroyed)
	{
		DestroyMenu();
	}
	return nRet;
}


void CMenuBuilder::ExitMenu(LPCTSTR cmd)
{
	m_menuRet.bExit = true;
	m_menuRet.command = cmd;
}

void CMenuBuilder::SetActiveMenu(CMenuUI* pMenu)
{
	m_pActiveMenu = pMenu;
}

CMenuContainer* CMenuBuilder::GetMenuContainer()
{
	return m_menus;
}

CMenuBuilder::CMenuBuilder(CDuiString xml)
:m_pActiveMenu(NULL)
, m_xmlName(xml)
, m_bMenusExsit(false)
{
}


CMenuBuilder::~CMenuBuilder(void)
{
}