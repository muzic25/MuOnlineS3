#include "StdAfx.h"

CouponEventItem g_CouponEventItemLIst;

CouponEventItem::CouponEventItem()
{
}

CouponEventItem::~CouponEventItem()
{
	this->m_vtCoupon_Event_Item.clear();
}

BOOL CouponEventItem::Load(char *lpszFileName)
{
	if (!lpszFileName)
	{
		LogAddTD("[EventItemList.txt] - File load error : File Name Error");
		return FALSE;
	}

	SMDFile = fopen(lpszFileName, "r");
	if (!SMDFile)
	{
		MsgBox("[DOTH] Info file Load Fail [%s]", lpszFileName);
		return FALSE;
	}

	int type = -1;

	while (1)
	{
		SMDToken Token = GetToken();
		if (Token == 2)
		{
			break;
		}

		type = TokenNumber;

		while (1)
		{
			if (type == 0)
			{
				Token = GetToken();

				if (!strcmp("end", TokenString))
				{
					break;
				}

				COUPON_EVENT_ITEM pCoupon_Event_Item; // [sp+4Ch] [bp-14h]@11
				pCoupon_Event_Item.m_btIndex = TokenNumber;
				Token = GetToken();
				pCoupon_Event_Item.m_btItemCodeType = TokenNumber;
				Token = GetToken();
				pCoupon_Event_Item.m_btItemCodeIndex = TokenNumber;
				Token = GetToken();
				pCoupon_Event_Item.m_btItemLevel = TokenNumber;
				Token = GetToken();
				pCoupon_Event_Item.m_btItemDur = TokenNumber;
				this->m_vtCoupon_Event_Item.push_back(pCoupon_Event_Item);
			}
		}
	}
	fclose(SMDFile);
	return TRUE;
}

int CouponEventItem::GetItemNum(BYTE btItemIndex, BYTE *btItemLevel, BYTE *btItemDur)
{
	for (std::vector<COUPON_EVENT_ITEM>::iterator it2 = this->m_vtCoupon_Event_Item.begin(); it2 != this->m_vtCoupon_Event_Item.end(); it2++)
	{
		if (it2->m_btIndex == btItemIndex)
		{
			BYTE btItemCodeIndex = it2->m_btItemCodeIndex;
			BYTE btItemCodeType = it2->m_btItemCodeType;
			*btItemLevel = it2->m_btItemLevel;
			*btItemDur = it2->m_btItemDur;
			return ItemGetNumberMake(btItemCodeType, btItemCodeIndex);
		}
	}
	return -1;
}