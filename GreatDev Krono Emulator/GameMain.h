// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
//------------------------------------------
// GameMain.h
//------------------------------------------

#ifndef GAMEMAIN_H
#define	GAMEMAIN_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wsJoinServerCli.h"
#include "wsGameServer.h"
#include "DirPath.h"
#include "MapClass.h"
#include "NSerialCheck.h"
#include "classdef.h"
#include "CLoginCount.h"
#include "DragonEvent.h"
#include "AttackEvent.h"
#include "WzUdp.h"
#include "WhisperCash.h"
#include "DbSave.h"
#include "SimpleModulus.h"
#include "MonsterAttr.h"
#include "MonsterSetBase.h"
#include "PartyClass.h"
#include "ItemBagEx.h"
#include "ProbabilityItemBag.h"

#define FIRST_PATH "..\\Data\\"

#define COMMONSERVER_MAINSECTION "GameServerInfo"
#define COMMONSERVER_FILE "Commonserver.cfg"

struct PMSG_FRIEND_STATE
{
	PBMSG_HEAD h;	// C1:C4
	char Name[10];	// 3
	BYTE State;	// D
};

enum MU_EVENT_TYPE {
	MU_EVENT_ALL = 0x0,
	MU_EVENT_DEVILSQUARE = 0x1,
	MU_EVENT_BLOODCASTLE = 0x2,
	MU_EVENT_ATTACKEVENTTROOP = 0x3,
	MU_EVENT_GOLDENTROOP = 0x4,
	MU_EVENT_WHITEMAGETROOP = 0x5,
	MU_EVENT_LOVEPANGPANG = 0x6,
	MU_EVENT_FIRECRACKER = 0x7,
	MU_EVENT_MEDALION = 0x8,
	MU_EVENT_XMASSTAR = 0x9,
	MU_EVENT_HEARTOFLOVE = 0xa,
	MU_EVENT_SAY_HAPPYNEWYEAR = 0xb,
	MU_EVENT_SAY_MERRYXMAS = 0xc,
	MU_EVENT_CHAOSCASTLE = 0xd,
	MU_EVENT_CHRISTMAS_RIBBONBOX = 0xe,
	MU_EVENT_VALENTINESDAY_CHOCOLATEBOX = 0xf,
	MU_EVENT_WHITEDAY_CANDYBOX = 0x10,
	MU_EVENT_ILLUSION = 0x11,
};

enum MU_ETC_TYPE {
	MU_ETC_ALL = 0x0,
	MU_ETC_CREATECHARACTER = 0x1,
	MU_ETC_GUILD = 0x2,
	MU_ETC_TRADE = 0x3,
	MU_ETC_USECHAOSBOX = 0x4,
	MU_ETC_PERSONALSHOP = 0x5,
	MU_ETC_PKITEMDROP = 0x6,
	MU_ETC_ITEMDROPRATE = 0x7,
	MU_ETC_SPEEDHACK = 0x8,
	MU_ETC_GAMEGUARD = 0x9,
};


extern BOOL JoinServerConnected;
extern BOOL DataServerConnected;
extern BOOL GameServerCreated;
extern BOOL DevilSquareEventConnect;
extern BOOL IsDevilSquareEventConnected;
extern BOOL EventChipServerConnect;
extern BOOL IsEventChipServerConnected;
extern CDragonEvent * DragonEvent;
extern CAttackEvent * AttackEvent;
extern CItemBag * LuckboxItemBag;
extern CItemBag * Mon55;
extern CItemBag * Mon53;
extern CItemBagEx * StarOfXMasItemBag;
extern CItemBag * FireCrackerItemBag;
extern CItemBag * HeartOfLoveItemBag;
extern CItemBag * GoldMedalItemBag;
extern CItemBag * SilverMedalItemBag;
extern CItemBag * EventChipItemBag;
extern CItemBag * GoldGoblenItemBag;
extern CItemBag * TitanItemBag;
extern CItemBag * GoldDerconItemBag;
extern CItemBag * DevilLizardKingItemBag;
extern CItemBag * KanturItemBag;
extern CItemBag * RingEventItemBag;
extern CItemBag * FriendShipItemBag;
extern CItemBag * DarkLordHeartItemBag;
extern CItemBagEx * KundunEventItemBag; 
extern CItemBagEx * CastleHuntZoneBossItemBag;
extern CItemBagEx * CastleItemMixItemBag; 
extern CItemBagEx * HiddenTreasureBoxItemBag;
extern CItemBagEx * RedRibbonBoxEventItemBag;
extern CItemBagEx * GreenRibbonBoxEventItemBag;
extern CItemBagEx * BlueRibbonBoxEventItemBag;
extern CItemBagEx * PinkChocolateBoxEventItemBag;
extern CItemBagEx * RedChocolateBoxEventItemBag;
extern CItemBagEx * BlueChocolateBoxEventItemBag;
extern CItemBagEx * LightPurpleCandyBoxEventItemBag;
extern CItemBagEx * VermilionCandyBoxEventItemBag;
extern CItemBagEx * DeepBlueCandyBoxEventItemBag;
extern CItemBagEx * GMBoxEventItemBag;
extern CItemBagEx * CrywolfDarkElfItemBag;
extern CItemBagEx * CrywolfBossMonsterItemBag;
extern CItemBagEx * KanturuMayaHandItemBag;
extern CItemBagEx * KanturuNightmareItemBag;
extern CItemBagEx * HallowinDayEventItemBag;
extern CItemBag * RingOfHeroBoxItemBag;
extern CProbabilityItemBag * NewYearLuckyPouchItemBag; //test
extern CProbabilityItemBag * GMPresentBoxItemBag; //test
extern CProbabilityItemBag * IllusionTemple1ItemBag; //test
extern CProbabilityItemBag * IllusionTemple2ItemBag; //test
extern CProbabilityItemBag * IllusionTemple3ItemBag; //test
extern CItemBagEx  * LeoItemBag;
extern CItemBagEx  * LukeItemBag;
extern CwsGameServer wsGServer;	// line : 213GameServer
extern wsJoinServerCli wsJServerCli;	// line : 214 Join Server
extern wsJoinServerCli wsDataCli;	// line : 215 DataServer
extern wsJoinServerCli wsExDbCli;	// line : 239 Extra DataBase Server
extern wsJoinServerCli wsRServerCli;	// line : 244 Ranking Server
extern wsJoinServerCli wsEvenChipServerCli; // line : 246 EVENT_MU2003
extern CDirPath gDirPath;	// line : 248 Directory Path
extern MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager
extern CMonsterAttr gMAttr;	// line 250
extern CMonsterSetBase gMSetBase;	// line 251
extern classdef DCInfo;	// line 252:
extern CWhisperCash WhisperCash;	// line 253
extern PartyClass gParty;	// line 254
extern CDbSave gDbSave;	// line 255
extern WzUdp gUdpSoc;	// line 256
extern WzUdp gUdpSocCE;	// line 258
extern WzUdp gUdpSocCER;	// line 259
extern WzUdp gUdpSocCRank;	// line 261
extern WzUdp gUdpSocCRankR;	//line 262
extern CGuildClass Guild;	// line 265
extern CMsg lMsg;	// line 324
extern NSerialCheck gNSerialCheck[OBJMAX];	// line 326
extern CLoginCount gLCount[3];	// line 329
extern DWORD  gLevelExperience[MAX_CHAR_LEVEL + 1];
extern CSimpleModulus g_SimpleModulusCS;	// line 751
extern CSimpleModulus g_SimpleModulusSC;	// line 752
extern char gMapName[MAX_NUMBER_MAP][255];
extern char g_szMapName[MAX_NUMBER_MAP][32];
extern char szAuthKey[20];
extern BOOL GSInfoSendFlag;

struct CConfigs {

public:
 BOOL SpeedHackPlayerBlock;
 BOOL bCanConnectMember;
 int  gServerType;
 int  gPartition;
 BOOL gApplyHeroSystem;
 int  gSpeedHackPenalty;
 BOOL gEnableEventNPCTalk;
 BOOL gEnableServerDivision;
 BOOL gEvent1;
 int  gMonsterHp;
 BOOL gMerryXMasNpcEvent;
 BOOL gHappyNewYearNpcEvent;
 int  gEvent1ItemDropTodayCount;
 int  gLanguage;
 BOOL gChaosEvent;
 char gChaosEventServerIp[20];
 char gHackLogServerIp[20];
 char gStalkProtocolId[11];
 BOOL gNonPK;
 BOOL gPkLimitFree;
 BOOL gXMasEvent;
 BOOL gFireCrackerEvent;
 BOOL gHeartOfLoveEvent;
 BOOL gMedalEvent;
 BOOL gEventChipEvent;
 BOOL gDevilSquareEvent;
 BOOL gWriteSkillLog;
 BOOL g_bStoneItemDrop;
 BOOL g_bDoRingEvent;
 BOOL g_bEventManagerOn;
 int  g_iKundunMarkDropRate;
 int  g_iMarkOfTheLord;
 int g_iJapan1StAnivItemDropRate;
 int  g_iDarkLordHeartDropRate;
 int  g_iDarkLordHeartOffEventRate;
 int g_iMysteriousBeadDropRate1;
 int g_iMysteriousBeadDropRate2;
 int g_iHiddenTreasureBoxOfflineRate;
 BOOL bIsIgnorePacketSpeedHackDetect;
 BOOL gIsKickDetecHackCountLimit;
 BOOL gTamaJJangEvent;
 int gAppearTamaJJang;
 int gTamaJJangTime;
 BOOL gIsItemDropRingOfTransform;
 BOOL gIsEledoradoEvent;
 BOOL gDoPShopOpen;
 BOOL gWriteChatLog;
 BOOL gDisconnectHackUser;
 int g_iBlockKanturuMapEnter;
 int g_iBlockCastleSiegeMapEnter;

 int  GameServerPort;
 int  JoinServerPort;
 int  DataServerPort;
 int  DataServer2Port;
 int  ExDbPort;
 int  RankingServerPort;
 int  EventServerPort;
 int  UDP;
 char ExDbIP[256];
 char DataServerIp2[256];
 char DataServerIp[256];
 char JoinServerIp[256];
 char RankingServerIP[256];
 char EventServerIP[256];
 char szGameServerExeSerial[24];
 char szServerName[50];
 char szKorItemTextFileName[256];
 char szKorSkillTextFileName[256];
 char szItemTextFileName[256];
 char szSkillTextFileName[256];
 char szQuestTextFileName[256];
 char szMoveReqFileName[256]; 

 BOOL gIsDropDarkLordItem;
 int  gSleeveOfLordDropRate;
 int  gSleeveOfLordDropLevel;
 int  gSoulOfDarkHorseDropRate;
 int  gSoulOfDarkHorseropLevel;
 int  gSoulOfDarkSpiritDropRate;
 int  gSoulOfDarkSpiritDropLevel;
 float gDarkSpiritAddExperience;
 BOOL gIsDropGemOfDefend;
 int  gGemOfDefendDropRate;
 int  gGemOfDefendDropLevel;
 int  g_iUseCharacterAutoRecuperationSystem;
 int  g_iCharacterRecuperationMaxLevel;
 int g_iServerGroupGuildChatting;
 int g_iServerGroupUnionChatting;
 BOOL g_bRibbonBoxEvent;
 int g_iRedRibbonBoxDropLevelMin;
 int g_iRedRibbonBoxDropLevelMax;
 int g_iRedRibbonBoxDropRate;
 int g_iRedRibbonBoxDropZenRate;
 int g_iRedRibbonBoxDropZen;
 int g_iGreenRibbonBoxDropLevelMin;
 int g_iGreenRibbonBoxDropLevelMax;
 int g_iGreenRibbonBoxDropRate;
 int g_iGreenRibbonBoxDropZenRate;
 int g_iGreenRibbonBoxDropZen;
 int g_iBlueRibbonBoxDropLevelMin;
 int g_iBlueRibbonBoxDropLevelMax;
 int g_iBlueRibbonBoxDropRate;
 int g_iBlueRibbonBoxDropZenRate;
 int g_iBlueRibbonBoxDropZen;
 BOOL g_bChocolateBoxEvent;
 int g_iPinkChocolateBoxDropLevelMin;
 int g_iPinkChocolateBoxDropLevelMax;
 int g_iPinkChocolateBoxDropRate;
 int g_iPinkChocolateBoxDropZenRate;
 int g_iPinkChocolateBoxDropZen;
 int g_iRedChocolateBoxDropLevelMin;
 int g_iRedChocolateBoxDropLevelMax;
 int g_iRedChocolateBoxDropRate;
 int g_iRedChocolateBoxDropZenRate;
 int g_iRedChocolateBoxDropZen;
 int g_iBlueChocolateBoxDropLevelMin;
 int g_iBlueChocolateBoxDropLevelMax;
 int g_iBlueChocolateBoxDropRate;
 int g_iBlueChocolateBoxDropZenRate;
 int g_iBlueChocolateBoxDropZen;
 BOOL g_bCandyBoxEvent;
 int g_iLightPurpleCandyBoxDropLevelMin;
 int g_iLightPurpleCandyBoxDropLevelMax;
 int g_iLightPurpleCandyBoxDropRate;
 int g_iLightPurpleCandyBoxDropZenRate;
 int g_iLightPurpleCandyBoxDropZen;
 int g_iVermilionCandyBoxDropLevelMin;
 int g_iVermilionCandyBoxDropLevelMax;
 int g_iVermilionCandyBoxDropRate;
 int g_iVermilionCandyBoxDropZenRate;
 int g_iVermilionCandyBoxDropZen;
 int g_iDeepBlueCandyBoxDropLevelMin;
 int g_iDeepBlueCandyBoxDropLevelMax;
 int g_iDeepBlueCandyBoxDropRate;
 int g_iDeepBlueCandyBoxDropZenRate;
 int g_iDeepBlueCandyBoxDropZen;
 BOOL g_bFenrirStuffItemDrop;
 int g_iFenrirStuff_01_DropLv_Min;
 int g_iFenrirStuff_01_DropLv_Max;
 int g_iFenrirStuff_01_DropMap;
 int g_iFenrirStuff_01_DropRate;
 int g_iFenrirStuff_02_DropLv_Min;
 int g_iFenrirStuff_02_DropLv_Max;
 int g_iFenrirStuff_02_DropMap;
 int g_iFenrirStuff_02_DropRate;
 int g_iFenrirStuff_03_DropLv_Min;
 int g_iFenrirStuff_03_DropLv_Max;
 int g_iFenrirStuff_03_DropMap;
 int g_iFenrirStuff_03_DropRate;
 int g_iFenrirRepairRate;
 int g_iFenrirDefaultMaxDurSmall;
 int g_iFenrirElfMaxDurSmall;
 int g_iFenrir_01Level_MixRate;
 int g_iFenrir_02Level_MixRate;
 int g_iFenrir_03Level_MixRate;
 BOOL g_bCrywolfMonsterDarkElfItemDrop;
 int g_iCrywolfMonsterDarkElfItemDropRate;
 int g_iCrywolfMonsterDarkElfDropZenRate;
 int g_iCrywolfMonsterDarkElfDropZen;
 BOOL g_bCrywolfBossMonsterItemDrop;
 int g_iCrywolfBossMonsterItemDropRate;
 int g_iCrywolfBossMonsterDropZenRate;
 int g_iCrywolfBossMonsterDropZen;
 int g_iCrywolfApplyMvpBenefit;
 int g_iCrywolfApplyMvpPenalty;
 int g_iSkillDistanceCheck;
 int g_iSkillDistanceCheckTemp;
 int g_iSkillDistanceKick;
 int g_iSkillDistanceKickCount;
 int g_iSkillDiatanceKickCheckTime;
 BOOL g_bKanturuMayaHandItemDrop;
 int g_iKanturuMayaHandItemDropRate;
 int g_iKanturuMayaHandDropZenRate;
 int g_iKanturuMayaHandDropZen;
 BOOL g_bKanturuNightmareItemDrop;
 int g_iKanturuNightmareItemDropRate;
 int g_iKanturuNightmareDropZenRate;
 int g_iKanturuNightmareDropZen;
 BOOL g_bKanturuSpecialItemDropOn;
 int g_iKanturuMoonStoneDropRate;
 int g_iKanturuJewelOfHarmonyDropRate;
 BOOL g_bHallowinDayEventOn;
 int g_iHallowinDayEventItemDropRate;
 int g_iHallowinDayEventJOLBlessDropRate;
 int g_iHallowinDayEventJOLAngerDropRaTe;
 int g_iHallowinDayEventJOLScreamDropRate;
 int g_iHallowinDayEventJOLFoodDropRate;
 int g_iHallowinDayEventJOLDrinkDropRate;
 int g_iHallowinDayEventJOLPolymorphRingDropRate;
 int g_iShadowPhantomMaxLevel;

//extern DWORD dwgCheckSum[MAX_CHECKSUM_KEY];

 char connectserverip[20];
 int  connectserverport;
 short gGameServerCode;
 int  gPkTime;
 BOOL g_bCastleGuildDestoyLimit;
 int  gItemNumberCount;
 BOOL gStalkProtocol;
 DWORD  gAttackEventRegenTime;
 int  gYear;
 BOOL gOnlyFireCrackerEffectUse;
 int  g_iRingOrcKillGiftRate;
 int  g_iRingDropGiftRate;

 int  gEledoradoGoldGoblenItemDropRate;
 int  gEledoradoTitanItemDropRate;
 int  gEledoradoGoldDerconItemDropRate;
 int  gEledoradoDevilLizardKingItemDropRate;
 int  gEledoradoDevilTantarosItemDropRate;
 int  gEledoradoGoldGoblenExItemDropRate;
 int  gEledoradoTitanExItemDropRate;
 int  gEledoradoGoldDerconExItemDropRate;
 int  gEledoradoDevilLizardKingExItemDropRate;
 int  gEledoradoDevilTantarosExItemDropRate;
 int  giKundunRefillHPSec;
 int  giKundunRefillHP;
 int  giKundunRefillHPTime;
 int  giKundunHPLogSaveTime;

// BOOL gUseNPGGChecksum;

 int g_ShieldSystemOn;
 int g_iDamageDevideToSDRate;
 int g_iDamageDevideToHPRate;
 float g_fSuccessAttackRateOption;
 int g_iSDChargingOption;
 int g_iConstNumberOfShieldPoint;
 int g_ShieldAutoRefillOn;
 int g_ShieldAutoRefillOnSafeZone;
 int g_PKLevelIncreaseOff;
 int g_CompoundPotionDropOn;
 int g_iCompoundPotionLv1DropRate;
 int g_iCompoundPotionLv2DropRate;
 int g_iCompoundPotionLv3DropRate;
 int g_iCompoundPotionLv1DropLevel;
 int g_iCompoundPotionLv2DropLevel;
 int g_iCompoundPotionLv3DropLevel;
 BOOL g_bShieldComboMissOptionOn;
 int g_iShieldPotionLv1MixSuccessRate;
 int g_iShieldPotionLv1MixMoney;
 int g_iShieldPotionLv2MixSuccessRate;
 int g_iShieldPotionLv2MixMoney;
 int g_iShieldPotionLv3MixSuccessRate;
 int g_iShieldPotionLv3MixMoney;
 int g_iShieldGageConstA;
 int g_iShieldGageConstB;

 char szGameServerVersion[12]; 
 int g_iCastleItemMixLimit; 

 char szClientVersion[8];
 BOOL bCanTrade;
 BOOL bCanChaosBox;
 BOOL bCanWarehouseLock;
 int  MapMinUserLevel[MAX_NUMBER_MAP];
 BOOL gEnableBattleSoccer;
 int  gLootingTime;
 int  gPkItemDrop;
 int  gItemDropPer;
 int  gEvent1ItemDropTodayMax;
 int  gEvent1ItemDropTodayPercent;
 char gCountryName[20];
 int  gCharacterDeleteMinLevel;
 BOOL gCreateCharacter;
 BOOL gGuildCreate;
 BOOL gGuildDestroy;
 int  gGuildCreateLevel;
 BOOL gItemSerialCheck;
 float  gAddExperience;
 int  g_XMasEvent_StarOfXMasDropRate;
 int  g_XMasEvent_ItemDropRateForStarOfXMas;
 int  gFireCrackerDropRate;
 int  g_ItemDropRateForgFireCracker;
 int  gHeartOfLoveDropRate;
 int  g_ItemDropRateForgHeartOfLove;
 int  gGoldMedalDropRate;
 int  gSilverMedalDropRate;
 int  g_ItemDropRateForGoldMedal;
 int  g_ItemDropRateForSilverMedal;
 int  gBoxOfGoldDropRate;
 int  g_ItemDropRateForBoxOfGold;
 int  g_EventChipDropRateForBoxOfGold;
 int  gEyesOfDevilSquareDropRate;
 int  gKeyOfDevilSquareDropRate;
 int  gDQChaosSuccessRateLevel1;
 int  gDQChaosSuccessRateLevel2;
 int  gDQChaosSuccessRateLevel3;
 int  gDQChaosSuccessRateLevel4;
 int  gDQChaosSuccessRateLevel5;
 int  gDQChaosSuccessRateLevel6;
 int  gDQChaosSuccessRateLevel7;
 BOOL g_bBloodCastle;
 int  g_iBloodCastle_StartHour;
 int  g_iStoneDropRate;
 int  g_iAngelKingsPaperDropRate;
 int  g_iBloodBoneDropRate;
 BOOL g_bChaosCastle;
 DWORD  gAttackSpeedTimeLimit;
 DWORD  gHackCheckCount;
 float gDecTimePerAttackSpeed;
 int  gMinimumAttackSpeedTime;
 int  gDetectedHackKickCount;
 int gTamaJJangKeepTime;
 int gTamaJJangDisappearTime;
 int gTamaJJangDisappearTimeRandomRange;
 BOOL gItemDropRingOfTransform;
 int  gQuestNPCTeleportTime;
 DWORD  gEledoradoGoldGoblenRegenTime;
 DWORD  gEledoradoTitanRegenTime;
 DWORD  gEledoradoGoldDerconRegenTime;
 DWORD  gEledoradoDevilLizardKingRegenTime;
 DWORD  gEledoradoDevilTantarosRegenTime;
 int  gZenDurationTime;
 int gMonsterHPAdjust;
 BOOL gEnableCheckPenetrationSkill;


 BOOL gIsDropSetItemInCastleHuntZone;
 int gSetItemInCastleHuntZoneDropRate;
 int gSetItemInCastleHuntZoneDropLevel;
 BOOL g_bDoCastleDeepEvent;
 int g_iRateJewelOfLuck;
 int g_iRateJewelOfExc;
 int g_iRateJewelOfMyst;

};
extern CConfigs Configs;

//------------------------------------------
// GameMain.cpp Functions - Prototypes List - Completed
//------------------------------------------
void gSetDate();
BOOL gJoomin15Check(char* szJN);
BOOL gJoominCheck(char* szJN, int iLimitAge);
void GameMainInit(HWND hWnd);
int GetWarehouseUsedHowMuch(int UserLevel, BOOL IsLock);
void GraphPaint(HWND hWnd);
void GameMonsterAllAdd();
void GameMonsterAllCloseAndReLoad();
void GameMainFree();
BOOL GMJoinServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GMRankingServerConnect(char* RankingServer, DWORD wMsg);
BOOL GMEventChipServerConnect(char* ServerIP, DWORD wMsg);
BOOL GMDataServerConnect(char* ConnectServer, DWORD wMsg);
BOOL ExDataServerConnect(char* ConnectServer, DWORD wMsg);
BOOL GameMainServerCreate(DWORD sMsg, DWORD cMsg);
void GMServerMsgProc( WPARAM wParam, LPARAM lParam);
void GMClientMsgProc( WPARAM wParam, LPARAM lParam);
void GMJoinClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMRankingClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMEventChipClientMsgProc(WPARAM wParam, LPARAM lParam);
void ExDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void GMDataClientMsgProc(WPARAM wParam, LPARAM lParam);
void ReadServerInfo();
void ReadCommonServerInfo();
void GameServerInfoSendStop();
void GameServerInfoSendStart();
void GameServerInfoSend();
//void CheckSumFileLoad(char *szCheckSum);
void LoadItemBag();
void SetMapName();
int GetEventFlag();
void ReadEventInfo(MU_EVENT_TYPE eEventType);
void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType);
void LoadCustomJewel(char *filename);
#endif