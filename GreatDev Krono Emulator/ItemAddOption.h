// ItemAddOption.h: interface for the CItemAddOption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMADDOPTION_H__96FEC421_39C3_40DD_9D47_EE1D86DD8A21__INCLUDED_)
#define AFX_ITEMADDOPTION_H__96FEC421_39C3_40DD_9D47_EE1D86DD8A21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ITEM_ADD_OPTION	100

#include "user.h"

typedef struct ITEMEFFECT
{
	WORD wOptionType;	// 0
	WORD wEffectType1;	// 2
	WORD wEffectType2;	// 4
	int iItemNumber;	// 8
	int iItemType;	// C
	int iItemIndex;	// 10
	int iEffectValue1;	// 14
	int iEffectValue2;	// 18
	int iEffectValidTime;	// 1C

} ITEMEFFECT, * LPITEMEFFECT;

class CItemAddOption
{

public:

	CItemAddOption();
	virtual ~CItemAddOption();

	void Load(PCHAR chFileName);
	void Initialize();
	LPITEMEFFECT GetCurrentEffectType(LPOBJ lpObj);
	bool PrevSetItemLastEffectForHallowin(LPOBJ lpObj);
	bool NextSetItemLastEffectForHallowin(LPOBJ lpObj);
	void SendItemUse(LPOBJ lpObj, int iItemNumber, int iOptionType, int iEffectType, int iEffectValue, int iValidTime);
	bool SetItemEffect(LPOBJ lpObj, int iItemNumber, int iItemUseTime);
	bool ClearItemEffect(LPOBJ lpObj, int iEffectOption);
	bool SearchItemEffectType(int iItemNumber, int* iEffectType1, int* iEffectType2);

private:

	LPITEMEFFECT _SearchItemEffect(int iItemNumber);
	bool _SetItemEffect(LPOBJ lpObj, int iEffectType, int iEffectValue);
	bool _ClearItemEffect(LPOBJ lpObj, int iEffectOption, int iOptionType, int iEffectType, int iEffectValue);
	
private:

	ITEMEFFECT m_ItemAddOption[MAX_ITEM_ADD_OPTION];
};

extern CItemAddOption g_ItemAddOption;

#endif // !defined(AFX_ITEMADDOPTION_H__96FEC421_39C3_40DD_9D47_EE1D86DD8A21__INCLUDED_)
