// ProbabilityItemBag.h: interface for the CProbabilityItemBag class.
//
//////////////////////////////////////////////////////////////////////
#ifndef PROBABILITYITEMBAG_H
#define PROBABILITYITEMBAG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapClass.h"
#include "user.h"
#include "zzzitem.h"
#include "ItemBagEx.h"

#define MAX_PROBABILITY_ITEMBAG_ATTR 150

class CProbabilityItemBagAttrEx : public CItemBagAttrEx
{
public:
	CProbabilityItemBagAttrEx() //season 4.5 changed
	{
		this->m_issetitem = 0; //nice fix from 77 :)
	};

	BYTE m_issetitem;
};

class CProbabilityItemBag
{

public:
	CProbabilityItemBag();
	virtual ~CProbabilityItemBag();

	void Init(LPSTR name);
	void LoadItem(LPSTR script_file);
	BOOL SortItem(int n);
	BOOL DropNewYearLuckMonsterReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	BOOL DropGMPresentBoxReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	BOOL DropIllusionTempleEventReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	BOOL DropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	void DropSetItem(int aIndex, int itemnum, BYTE btMapNumber, int cX, int cY);
	int DropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY, int * iDropZen);


private:
	int GetBagCount(){return this->m_iBagObjectCount;}
	char * GetEventName();
	int IsEnableEventItemDrop(int aIndex);
	BYTE GetLevel(int n);
private:

	BOOL m_bLoad;	// 4
	char m_sEventName[255];	// 8
	int m_iEventItemType;	// 108
	int m_iEventItemLevel;	// 10C
	int m_iDropZen;	// 110
	int m_iEventItemDropRate;	// 114
	int m_iItemDropRate;	// 118
	int m_iExItemDropRate;	// 11C
	int m_iBagObjectCount;	// 120
	CItemBagDropMapInfo DropMapInfo[MAX_NUMBER_MAP];	// 124
	CProbabilityItemBagAttrEx BagObject[MAX_PROBABILITY_ITEMBAG_ATTR];	// 1CF
	int m_iEventItemDropRateEx[20];	// 680
	int m_iDropRatePerItemCount[20];	// 6D0
	int m_iRateKindCount;	// 720
};

#endif