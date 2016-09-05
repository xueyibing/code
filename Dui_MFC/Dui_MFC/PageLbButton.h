#pragma once



class CPageLbButton : public CButtonUI
{
public:
	CPageLbButton();
	~CPageLbButton();

	void DoEvent(TEventUI& event);

	void SetChoosed(const bool& b);
private:
	bool isPInRect(const POINT&p, const CRect&r);

	CButtonUI *m_closeBtn;

	CRect m_closeRect;

private:

	bool m_isSelected;
	bool m_isInClose;


};
