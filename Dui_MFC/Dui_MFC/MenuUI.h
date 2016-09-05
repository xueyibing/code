#ifndef  __UIMENU__
#define __UIMENU__
#include "..\thirdLib\duilib\DuiLib\UIlib.h"

using namespace DuiLib;

struct MenuReturn
{
	bool    bExit;
	CDuiString command;
};

class CStaticMenuElementUI :public CListContainerElementUI
{
public:
	LPVOID GetInterface(LPCTSTR pstrName);
	void DoPaint(HDC hDC, const RECT& rcPaint);
};

class CMenuBuilder;
class CMenuUI;
class CMenuWnd;
class CMenuContainer;

class CMenuElementUI : public CListContainerElementUI, public INotifyUI
{
public:
	CMenuElementUI();
	void Notify(TNotifyUI& msg);
	//��ʼ��
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	LPVOID GetInterface(LPCTSTR pstrName);
	void SetMenuOwner(CMenuUI* owner);
	void SetExtendMenu(CMenuUI* pMenu);
	//��ȡ����
	CDuiString GetExtendMenuName();
	CMenuUI* GetExtendMenu();
	CDuiString GetMenuCmd();
	bool IsHaveExtend();
	bool IsExtendMenuShow();
	//��������
	void SetExtenMenuShow(bool b);
    //��Ӧ�¼�
	void DoEvent(TEventUI& event);
	void DoPaint(HDC hDC, const RECT& rcPaint);
	//����
	void ShowSubMenu();
	void HideSubMenu();
	void OnShortKeyEvent(TNotifyUI& msg);

protected:
	CDuiString      m_ExtendMenuName;        //�Ӳ˵�name
	CDuiString      m_MenuCmd;                   //�˵�����
	CDuiString      m_ShortKey;					  //��ݼ�
	CMenuUI*        m_pMenuOwner;               //�˵�Owner
	CMenuUI*        m_pExtendMenu;              //�Ӳ˵�
	bool            m_bHaveExtend;               //�Ƿ����Ӳ˵�
	bool            m_bExtendMenuShow;       //�Ӳ˵��Ƿ���ʾ��
};



class CMenuUI :public CListUI,public INotifyUI
{
public:
	CMenuUI();
	~CMenuUI();
	LPVOID GetInterface(LPCTSTR pstrName);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetSuperMenu(CMenuUI* pSuper);
	void SetMenuBuilder(CMenuBuilder* pMenuTree);
	CMenuBuilder* GetMenuBuilder();
	HWND GetHandle();

	void InitMenu(HWND ownerWnd);
	bool Add(CControlUI* pControl);

	bool IsMajor();
	bool IsExtenMenuShow();
	CMenuUI* GetCurExtendMenu();
	CMenuWnd* GetMenuWnd();
		
	void ShowMenu(POINT p);
	void HideMenu();
	void OnItemHover(CControlUI* pControl);
	void OnItemLeave(CControlUI* pControl);
	void OnMenuItemClick(CControlUI* pControl);
	void AddNotify(INotifyUI* pNotify);

	void Notify(TNotifyUI& msg);

	virtual void OnItemHot(CMenuElementUI* pMenuItem);
	virtual void OnItemUnHot(CMenuElementUI* pMenuItem);

	void SetCurItem(CMenuElementUI* pMenuItem);
    CMenuElementUI* GetCurItem();

	void ShowSubMenu(CMenuElementUI* pMenuItem);
	CMenuElementUI* GetNextItem();
	CMenuElementUI* GetPrevItem();

	//��Ӧ�����¼�
	void OnVkLeft();
	void OnVkRight();
	void OnVkUp();
	void OnVkDown();
	void OnVkReturn();

protected:
	bool            m_bMajor;
	bool            m_bSubMenuShow;
	CMenuUI*    m_pCurSubMenu;
	CMenuWnd* m_pMenuWnd;
	CMenuBuilder*   m_pMenuBuilder;
	CMenuElementUI*  m_pCurItem;
	CMenuUI*		m_pSuperMenu;
};

class CMenuBuilder : public IDialogBuilderCallback
{
public:
	CMenuBuilder(CDuiString xml);
	~CMenuBuilder(void);
	CControlUI* CreateControl(LPCTSTR pstrClass);
	LPCTSTR TrackPopupMenu(HWND hwndParent, int x, int y);
	void DestroyMenu();
	bool IsMenuWnd(HWND hwnd);
	int   RunMenu();
	void ExitMenu(LPCTSTR cmd);
	void SetActiveMenu(CMenuUI* pMenu);
	CMenuContainer* GetMenuContainer();
protected:
	void LoadFromXml(LPCTSTR xmlName);
	CMenuUI* FindMenuByName(LPCTSTR pName);

	CDuiString					m_xmlName;
	HWND							m_hWndOwner;
	CMenuUI*                    m_pActiveMenu;
	CMenuContainer*         m_menus;
	bool								 m_bMenusExsit;
	MenuReturn                  m_menuRet;

};

class CMenuWnd :public CWindowWnd
{
public:
	CMenuWnd(void);
	~CMenuWnd(void);

	virtual LPCTSTR GetWindowClassName() const;
	LRESULT OnNcActivate(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void BindControl(CControlUI* pControl);
	void UnBindControl(CControlUI* pControl);
	void ShowMenuWnd(bool b);
	void AddNotifier(INotifyUI* pNotify);
	void SetMenuOwner(CMenuUI* pOwner);
	void SetBktrans(bool b);


protected:
	CPaintManagerUI			m_pm;
	CMenuUI*					m_pMenui;


};


class CMenuContainer : public CContainerUI
{
public:
	CMenuContainer();
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	int GetInterval();
	bool IsKeyEvent()
	{
		return m_bKeyEvent;
	}
protected:
	int  m_nInterval;
	bool m_bKeyEvent;
};






#endif