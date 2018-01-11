#pragma once

struct COUPON_EVENT_ITEM
{
	BYTE m_btIndex;
	BYTE m_btItemCodeType;
	BYTE m_btItemCodeIndex;
	BYTE m_btItemLevel;
	BYTE m_btItemDur;
};

class CouponEventItem
{
public:
	CouponEventItem();
	~CouponEventItem();

	BOOL Load(char * lpszFileName);

	int GetItemNum(BYTE btItemIndex, BYTE * btItemLevel, BYTE * btItemDur);

private:
	std::vector<COUPON_EVENT_ITEM> m_vtCoupon_Event_Item;
};
extern CouponEventItem g_CouponEventItemLIst;
