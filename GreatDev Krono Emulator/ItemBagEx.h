#ifndef ITEMBAGEX_H
#define ITEMBAGEX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ItemBag.h"
#include "MapClass.h"
#include "user.h"
#include "zzzitem.h"

class CItemBagAttrEx
{

public:

	CItemBagAttrEx()	// line : 26
	{
		this->m_type = 0;
		this->m_index = 0;
		this->m_minLevel = 0;
		this->m_maxLevel = 0;
		this->m_isskill = 0;
		this->m_isluck = 0;
		this->m_isoption = 0;
		this->m_isexitem = 0;
	}	// line : 36

	BYTE m_type;	// 0
	BYTE m_index;	// 1
	BYTE m_minLevel;	// 2
	BYTE m_maxLevel;	// 3
	BYTE m_isskill;	// 4
	BYTE m_isluck;	// 5
	BYTE m_isoption;	// 6
	BYTE m_isexitem;	// 7

};

class CItemBagDropMapInfo
{

public:

	CItemBagDropMapInfo()	// line : 46
	{
		this->Init();
	};	// line : 49

	void Init()	// line : 52
	{
		this->m_bIsDrop = false;
		this->m_MinMonsterLevel = 0;
		this->m_MaxMonsterLevel = 0;
	};	// line : 56

	BYTE m_bIsDrop;	// 0
	BYTE m_MinMonsterLevel;	// 1
	BYTE m_MaxMonsterLevel;	// 2

};


class CItemBagEx
{

public:

	CItemBagEx();
	virtual ~CItemBagEx();

	void Init(LPSTR name);
	void LoadItem(LPSTR script_file);
	int DropEventItem(int aIndex);
	int DropItem(int aIndex);
	int DropRedRibbonBoxEventItem(int aIndex);
	int DropGreenRibbonBoxEventItem(int aIndex);
	int DropBlueRibbonBoxEventItem(int aIndex);
	int DropPinkChocolateBoxEventItem(int aIndex);
	int DropRedChocolateBoxEventItem(int aIndex);
	int DropBlueChocolateBoxEventItem(int aIndex);
	int DropLightPurpleCandyBoxEventItem(int aIndex);
	int DropVermilionCandyBoxEventItem(int aIndex);
	int DropDeepBlueCandyBoxEventItem(int aIndex);
	int DropKundunEventItem(int aIndex, BYTE btMapNumber,BYTE cX, BYTE cY);
	int DropCrywolfDarkElfItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	BOOL DropGMBoxEventItem(int aIndex);
	int DropCrywolfBossMonsterItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	int DropKanturuMayaHandItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	int DropKanturuNightmareItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	int DropPCBangRevitalizationEventItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY);
	int DropHallowinEventItem(LPOBJ lpObj); 
	int DropCastleHuntZoneBossReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY); 
	BYTE GetMinLevel(int n);
	BYTE GetMaxLevel(int n);
	int PickItem(CItem& objItem, int& nItemIndex);

private:

	int GetBagCount(){return this->m_iBagObjectCount;}
	int IsEnableEventItemDrop(int aIndex);
	BYTE GetLevel(int n);
	//unsigned char __thiscall IsSkill(int);
	//unsigned char __thiscall IsLuck(int);
	//unsigned char __thiscall IsOption(int);

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
	CItemBagAttrEx BagObject[MAX_ITEMBAG_ATTR];	// 19C
};

#endif