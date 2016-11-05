#ifndef CHAOSBOX_H
#define CHAOSBOX_H
/*
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000*/

#include "protocol.h"
#include "zzzitem.h"

void ChaosEventProtocolCore(BYTE protoNum, unsigned char* aRecv, int aLen);

#define CHAOS_BOX_RANGE(x) (((x)<0)?FALSE:((x)>CHAOS_BOX_SIZE-1)?FALSE:TRUE )

enum CHAOS_TYPE
{
	CHAOS_TYPE_DEFAULT = 0x1,
	CHAOS_TYPE_DEVILSQUARE = 0x2,
	CHAOS_TYPE_UPGRADE_10 = 0x3,
	CHAOS_TYPE_UPGRADE_11 = 0x4,
	CHAOS_TYPE_UPGRADE_12 = 0x16,
	CHAOS_TYPE_UPGRADE_13 = 0x17,
	CHAOS_TYPE_DINORANT = 0x5,
	CHAOS_TYPE_FRUIT = 0x6,
	CHAOS_TYPE_SECOND_WING = 0x7,
	CHAOS_TYPE_BLOODCATLE = 0x8,
	CHAOS_TYPE_FIRST_WING = 0xb,
	CHAOS_TYPE_SETITEM = 0xc,
	CHAOS_TYPE_DARKHORSE = 0xd,
	CHAOS_TYPE_DARKSPIRIT = 0xe,
	CHAOS_TYPE_CLOAK = 0x18,
	CHAOS_TYPE_BLESS_POTION = 0xf,
	CHAOS_TYPE_SOUL_POTION = 0x10,
	CHAOS_TYPE_LIFE_STONE = 0x11,
	CHAOS_TYPE_CASTLE_ITEM = 0x12,
	CHAOS_TYPE_HT_BOX = 0x14,
	CHAOS_TYPE_FENRIR_01 = 0x19,
	CHAOS_TYPE_FENRIR_02 = 0x1a,
	CHAOS_TYPE_FENRIR_03 = 0x1b,
	CHAOS_TYPE_FENRIR_04 = 0x1c,
	CHAOS_TYPE_COMPOUNDPOTION_LV1 = 0x1e,
	CHAOS_TYPE_COMPOUNTPOTION_LV2 = 0x1f,
	CHAOS_TYPE_COMPOUNTPOTION_LV3 = 0x20,
	CHAOS_TYPE_JEWELOFHARMONY_PURITY = 0x21,
	CHAOS_TYPE_JEWELOFHARMONY_MIX_SMELTINGITEM = 0x22,
	CHAOS_TYPE_JEWELOFHARMONY_RESTORE_ITEM = 0x23,
	CHAOS_TYPE_380_OPTIONITEM = 0x24,
	CHAOS_TYPE_LOTTERY_MIX = 0x25,
	CHAOS_TYPE_CONDOR_MIX = 0x26,
	CHAOS_TYPE_3RDWINGS_MIX = 0x27
};

enum CHAOS_TYPE_MSG
{
	CB_ERROR					= 0x0,
	CB_SUCCESS					= 0x1,
	CB_NOT_ENOUGH_ZEN			= 0x2,
	CB_LOW_LEVEL_USER			= 0x4,
	CB_USER_CLASS_LOW_LEVEL		= 0x9,
	CB_NO_BC_CORRECT_ITEMS		= 0xA,

	/*Нерабочие*/
	CB_TOO_MANY_ITEMS			= 0x3,
	CB_LACKING_MIX_ITEMS		= 0x6,
	CB_INCORRECT_MIX_ITEMS		= 0x7,
	CB_INVALID_ITEM_LEVEL		= 0x8,
	CB_BC_NOT_ENOUGH_ZEN		= 0xB,
	CB_SHARM_OF_BOX_MSG			= 0xF0
};

struct sChaosMixConf
{
	DWORD ChaosWeapon;
	DWORD FirstWings;
	DWORD SecondWings;
	DWORD CapeOfLord;
	DWORD Condor;
	DWORD ThirdWings;
	DWORD DarkHourse;
	DWORD DarkRaven;
	DWORD Dinorant;

	//Devil Squate Tickets
	DWORD DevilSquare[8];

	//Blood CastleTickets 
	DWORD BloodCastle[8];

	//Illusion Temple Tickets 
	DWORD Illusion[6];

	//Upgrate Level Items 
	DWORD PlusLevel10;
	DWORD PlusLevel11;
	DWORD PlusLevel12;
	DWORD PlusLevel13;
	DWORD AddLuckItems;

	DWORD BlessPotion;
	DWORD SoulPotion;
	DWORD Fruit;
	DWORD LifeStone;

	DWORD FenrirLvl1;
	DWORD FenrirLvl2;
	DWORD FenrirLvl3;
	DWORD FenrirLvl4;

	DWORD ShieldPotionLvl1;
	DWORD ShieldPotionLvl2;
	DWORD ShieldPotionLvl3;
};

struct sDivInFormula
{
	int DivChaosWeapon;
	int DivFirstWings;
	int MainDivSecondWings;
	int SubDivSecondWings;
	int DivCondor;
	int DivThirdWings;
	int FisrtDivFenrir4;
	int SecondDivFenrir4;
};

struct CB_PMSG_REQ_PRESENT_RESULT
{
	PBMSG_HEAD h;
	char AccountId[10];	// 3
	char GameId[10];	// D
	int Sequence;	// 18
	char present;	// 1C
	char presentname[50];	// 1D
	int Seq_present;	// 50
};

struct PMSG_CHAOSMIXRESULT
{
	PBMSG_HEAD h;	// C1:86
	BYTE Result;	// 3
	BYTE ItemInfo[MAX_ITEM_INFO];	// 4
};

struct CBUPS_ITEMPRIZESEND	// Confirmed size
{
	PHEADB PHeader;
	char szAccountID[10];
	char szCharName[10];
	int iGameServerCode;
	BYTE btResult;
	int unk20;

};

class cChaosBox
{
public:
	cChaosBox();
	~cChaosBox();

	void CBUPR_ItemRequestRecv( CB_PMSG_REQ_PRESENT_RESULT * lpMsg);

	void LoadConfigs();
	/*Функция инициализации*/
	BOOL ChaosBoxInit(LPOBJ lpObj);
	BOOL ChaosBoxClear(LPOBJ lpObj);
	void MessageDataSend(LPOBJ lpObj,CHAOS_TYPE_MSG TypeMsg);

	
	DWORD GetBuyMoneyItems(LPOBJ lpObj, BOOL ActiveOld,short StartType, short EndType);
	BOOL AddSuccessCharmSystem(LPOBJ lpObj);

	BYTE GetItemLevel(LPOBJ lpObj,short Type);
	BYTE GetItemCount(LPOBJ lpObj);
	BYTE GetDurability(LPOBJ lpObj,short Type);

	BYTE CheckChaosItems(LPOBJ lpObj,short TypeItem);
	BYTE CheckChaosItems(LPOBJ lpObj,short StartType,short EndType,BYTE MinLvl,BOOL CheckExc,BOOL CheckAnc);

	BOOL DecZenChaosSystem(LPOBJ lpObj,DWORD StartZen);

	/*Методы для варки итемов*/
	
	void DefaultMix(LPOBJ lpObj);
	void DevilSqueareMix(LPOBJ lpObj);
	void UpgradeItemLevel(LPOBJ lpObj, BYTE MixType);
	void DinorantMix(LPOBJ lpObj);
	void FruitMix(LPOBJ lpObj);
	void SecondWingsMix(LPOBJ lpObj);
	void BloodCastleTicketMix(LPOBJ lpObj);
	void FirstWingsMix(LPOBJ lpObj);
	//void SetItemMix(LPOBJ lpObj);
	void BlessPoitonMix(LPOBJ lpObj);
	void SoulPotionMix(LPOBJ lpObj);
	void LifeStoneMix(LPOBJ lpObj);
	void CastleItemMix(LPOBJ lpObj);
	void HTBoxMix(LPOBJ lpObj);
	
	void IllusionTicketMix(LPOBJ lpObj);
	void CondorMix(LPOBJ lpObj);
	void ThirdWingsMix(LPOBJ lpObj);

	void DlPetChaosMix(LPOBJ lpObj, int ModeMix);

	void FenrirMixPart1(LPOBJ lpObj);
	void FenrirMixPart2(LPOBJ lpObj);
	void FenrirMixPart3(LPOBJ lpObj);
	void FenrirMixPart4(LPOBJ lpObj);

	void ShieldPotionMix(LPOBJ lpObj,int MixType);

	int GetExcOpt(int amount);

	sChaosMixConf ConfRates;
	sChaosMixConf ConfCostZen;
	sDivInFormula DivValues;
	BYTE SecondWingsExcRate;
	BYTE SecondWingsMaxOpt;
	BYTE ThirdWingsExcRate;
	BYTE ThirdWingsMaxOpt;
};

extern cChaosBox ChaosBox;

#endif