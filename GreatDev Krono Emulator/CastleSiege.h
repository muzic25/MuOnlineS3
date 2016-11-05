#ifndef CASTLESIEGE_H
#define CASTLESIEGE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 
using namespace std;

#include "protocol.h"

#define CS_MAX_UPGRADE 3

#define CASTLESIEGE_DATALOAD_1 1
#define CASTLESIEGE_DATALOAD_2 2
#define CASTLESIEGE_DATALOAD_3 3
#define CASTLESIEGE_DATALOAD_4 4

#define CASTLESIEGE_STATE_NONE -1
#define CASTLESIEGE_STATE_IDLE_1 0
#define CASTLESIEGE_STATE_REGSIEGE 1
#define CASTLESIEGE_STATE_IDLE_2 2
#define CASTLESIEGE_STATE_REGMARK 3
#define CASTLESIEGE_STATE_IDLE_3 4
#define CASTLESIEGE_STATE_NOTIFY 5
#define CASTLESIEGE_STATE_READYSIEGE 6
#define CASTLESIEGE_STATE_STARTSIEGE 7
#define CASTLESIEGE_STATE_ENDSIEGE 8
#define CASTLESIEGE_STATE_ENDCYCLE 9

struct PMSG_SENDMINIMAPDATA
{
	unsigned char btX;
	unsigned char btY;
};



struct _CS_SCHEDULE_DATA
{
public:
	_CS_SCHEDULE_DATA();
	virtual ~_CS_SCHEDULE_DATA();

	void Clear();
public:
	BOOL m_bIN_USE;
	int m_iSTATE;
	int m_iADD_DAY;
	int m_iADD_HOUR;
	int m_iADD_MIN;
	int m_iGAP_SEC;

};



struct _CS_NPC_DATA
{
	_CS_NPC_DATA();
	virtual ~_CS_NPC_DATA();
	void Clear();
	void SetBaseValue();

/* this+0x4 */ BOOL m_bIN_USE;
/* this+0x8 */ int m_iNPC_NUM;
/* this+0xC */ int m_iNPC_INDEX;
/* this+0x10 */ BOOL m_bNPC_DBSAVE;
/* this+0x14 */ int m_iNPC_SIDE;
/* this+0x18 */ int m_iNPC_OBJINDEX;
/* this+0x1C */ int m_iNPC_DF_LEVEL;
/* this+0x20 */ int m_iNPC_RG_LEVEL;
/* this+0x24 */ int m_iNPC_MAXHP;
/* this+0x28 */ int m_iNPC_HP;
/* this+0x2C */ int m_iNPC_SX;
/* this+0x30 */ int m_iNPC_SY;
/* this+0x34 */ int m_iNPC_DX;
/* this+0x38 */ int m_iNPC_DY;
/* this+0x3C */ int m_iNPC_DIR;
/* this+0x40 */ int m_iNPC_BASE_DF_LEVEL;
/* this+0x44 */ int m_iNPC_BASE_RG_LEVEL;
/* this+0x48 */ int m_iNPC_BASE_MAXHP;
/* this+0x4C */ int m_iNPC_BASE_HP;
/* this+0x50 */ int m_iNPC_BASE_SX;
/* this+0x54 */ int m_iNPC_BASE_SY;
/* this+0x58 */ int m_iNPC_BASE_DX;
/* this+0x5C */ int m_iNPC_BASE_DY;
/* this+0x60 */ int m_iNPC_BASE_DIR;
/* this+0x64 */ int m_iCS_GATE_LEVER_INDEX;
/* this+0x68 */ int m_iNPC_LIVE;
/* this+0x6C */ int m_iNPC_AUTH;

	union
	{
		struct
		{
		/* this+0x70 */ unsigned char m_btCsNpcExistVal1;
		/* this+0x71 */ unsigned char m_btCsNpcExistVal2;
		/* this+0x72 */ unsigned char m_btCsNpcExistVal3;
		/* this+0x73 */ unsigned char m_btCsNpcExistVal4;
		};
		/* this+0x70 */ int m_iCsNpcExistVal;
	};
};

struct _CS_REG_GUILD_DATA
{
public:
	_CS_REG_GUILD_DATA();
	virtual ~_CS_REG_GUILD_DATA();

	void Clear();
	/*_CS_REG_GUILD_DATA & operator = (_CS_REG_GUILD_DATA & __that)
	{
		this->m_bIN_USE = __that.m_bIN_USE;
		this->m_strGuildName = __that.m_strGuildName;
		this->m_iRegMarkCount = __that.m_iRegMarkCount;
		this->m_iGuildMemberCount = __that.m_iGuildMemberCount;
		this->m_iGuildMasterLevel = __that.m_iGuildMasterLevel;
		this->m_iSeqNum = __that.m_iSeqNum;
		this->m_i64TotolScore = __that.m_i64TotolScore;

		return *this;
	};*/

public:
	BOOL m_bIN_USE;
	std::string m_strGuildName;
	int m_iRegMarkCount;
	int m_iGuildMemberCount;
	int m_iGuildMasterLevel;
	int m_iSeqNum;
	__int64 m_i64TotolScore;
};

struct _CS_TOTAL_GUILD_DATA
{
	_CS_TOTAL_GUILD_DATA();
	virtual ~_CS_TOTAL_GUILD_DATA();

	void Clear();

	BOOL m_bIN_USE;
	int m_iCsGuildID;
	BOOL m_bGuildInvolved;
};

struct _CS_MINIMAP_DATA
{
	_CS_MINIMAP_DATA();
	virtual ~_CS_MINIMAP_DATA();
	void Clear();

	int m_iGuildMasterIndex;
	char m_szGuildName[16];
	int m_iMiniMapPointCount;
	PMSG_SENDMINIMAPDATA m_stMiniMapPoint[1000];
};

class CCastleSiege
{
// Class Constructor / Destructor
public:
	CCastleSiege();
	virtual ~CCastleSiege();

// Class member functions
public:
	void Clear();
	int Ready(int iMapSvrGroup);
	int LoadPreFixData(char * lpszFileName);
	int LoadData(char * lpszFileName);
	int DataRequest();
	int Init();
	void Run();
	void GetStateDate(int iCastleSiegeState, SYSTEMTIME* st);
	static bool ScheduleStateCompFunc(_CS_SCHEDULE_DATA & A,_CS_SCHEDULE_DATA & B);
	int GetDataLoadState(){ return m_iCastleDataLoadState;}
	void SetDataLoadState(int iDataLoadState){ m_iCastleDataLoadState = iDataLoadState;}
	void SetDbDataLoadOK(BOOL bDbDataLoadOK) { m_bDbDataLoadOK = bDbDataLoadOK;}
	int FirstCreateDbNPC();
	int SetCastleInitData(CSP_ANS_CSINITDATA * lpMsg);
	int SetCastleNpcData(CSP_CSINITDATA * lpMsg,int iCOUNT);
	int CheckSync();
	void GetNextDay(_SYSTEMTIME * st, int iAfterDay, int iAfterHour, int iAfterMin, int iAfterSec);
	int GetStateGapSec(int iCastleSiegeState);
	void SetState(int iCastleSiegeState,int bSetRemainMsec);
	void SetState_NONE(int bSetRemainMsec);
	void SetState_IDLE_1(int bSetRemainMsec);
	void SetState_REGSIEGE(int bSetRemainMsec);
	void SetState_IDLE_2(int bSetRemainMsec);
	void SetState_REGMARK(int bSetRemainMsec);
	void SetState_IDLE_3(int bSetRemainMsec);
	void SetState_NOTIFY(int bSetRemainMsec);
	void SetState_READYSIEGE(int bSetRemainMsec);
	void SetState_STARTSIEGE(int bSetRemainMsec);
	void SetState_ENDSIEGE(int bSetRemainMsec);
	void SetState_ENDCYCLE(int bSetRemainMsec);
	void ProcState_NONE();
	void ProcState_IDLE_1();
	void ProcState_REGSIEGE();
	void ProcState_IDLE_2();
	void ProcState_REGMARK();
	void ProcState_IDLE_3();
	void ProcState_NOTIFY();
	void ProcState_READYSIEGE();
	void ProcState_STARTSIEGE();
	void ProcState_ENDSIEGE();
	void ProcState_ENDCYCLE();
	int GetCastleState(){return m_iCastleSiegeState;}
	SYSTEMTIME GetCastleLeftSiegeDate() {	return m_tmLeftCastleSiegeDate;};
	int CalcCastleLeftSiegeDate();
	int GetCastleStateTerm(SYSTEMTIME & tmStateStartDate,SYSTEMTIME & tmStateEndDate);
	int GetCurRemainSec();
	void ClearDbNPC();
	void ClearNonDbNPC();
	void ClearNonDbNPC_MidWin();
	void ClearAllNPC();
	void CreateDbNPC();
	void CreateNonDbNPC(int bDelFirst);
	int CheckAddDbNPC(int iIndex, int iNpcType, int iNpcIndex, BYTE & btResult);
	int AddDbNPC(int iNpcType, int iNpcIndex);
	int RepairDbNPC(int iNpcType, int iNpcIndex, int iNpcHP, int iNpcMaxHP);
	int PayForUpgradeDbNpc(int iIndex, int iNpcType, int iNpcIndex, int iNpcUpType, int iNpcUpValue, int iNpcUpIndex);
	int UpgradeDbNPC(int iIndex, int iNpcType, int iNpcIndex, int iNpcUpType, int iNpcUpValue, int iNpcUpIndex);
	int UpgradeDbNPC_DFLEVEL(int iNpcType, int iNpcIndex, int iNpcDfLevel);
	int UpgradeDbNPC_RGLEVEL(int iNpcType, int  iNpcIndex, int iNpcRgLevel);
	int UpgradeDbNPC_MAXHP(int iNpcType, int iNpcIndex, int iNpcMaxHP);
	void StoreDbNpc();
	int DelNPC(int iIndex, int iNpcType, int iMonsterExistVal, int bDbSave);
	void SendNpcStateList(int iIndex, int iNpcType);
	int GetNpcData(int iNpcType, int iNpcIndex,_CS_NPC_DATA &pRetNpcData);
	void AdjustDbNpcLevel();
	void SendCsGateStateViewPort(int iGateIndex, BYTE btOperate);
	void CreateAllCsGateLever();
	int CreateCsGateLever(int iX, int iY);
	int LinkCsGateLever(int iLeverIndex, int iGateIndex);
	int CheckLeverAlive(int iLeverIndex);
	int CheckCsGateAlive(int iGateIndex);
	void CheckCsDbNpcAlive();
	void SetCrownIndex(int iIndex){m_iCrownIndex = iIndex;}
	void NotifyCrownState(BYTE btState);
	int GetRegCrownAvailable(){return m_bRegCrownAvailable;}
	void SetRegCrownAvailable(int bRegCrownAvailable){m_bRegCrownAvailable = bRegCrownAvailable;}
	BOOL GetCastleTowerAccessable(){ return m_bCastleTowerAccessable;}
	void SetCastleTowerAccessable(BOOL bTowerAccessable) { m_bCastleTowerAccessable = bTowerAccessable;}
	int DelGemOfDefend(int iIndex, int iNeedGemOfDefend);
	void SetTaxRate(int iTaxType, int iTaxRate);
	int CheckCastleHasMoney(__int64 i64CastleMoney);
	__int64 GetCastleMoney();
	void SetCastleMoney(__int64 i64CastleMoney);
	void ResetCastleTaxInfo();
	void SetIsSiegeGuildList(BOOL bIsSiegGuildList) { m_btIsSiegeGuildList = bIsSiegGuildList;}
	void SendCastleStateSync();
	int GetDbNpcCreated() {return m_bDbNpcCreated;}
	void SetDbNpcCreated(BOOL bDbNpcCreated) { m_bDbNpcCreated = bDbNpcCreated;}
	int CheckGuildOwnCastle(char * lpszGuildName);
	void ResetCastleCycle();
	void SetGateBlockState(int iX, int iY, int iGateState);
	LPSTR GetCastleOwnerGuild(){return m_szCastleOwnerGuild;}
	BOOL GetHuntZoneEnter(){ return m_bEnterHuntZone;};
	void SetHuntZoneEnter(BOOL bEnterHuntZone){m_bEnterHuntZone = bEnterHuntZone;};
	/*int GetTaxRateChaos();
	int GetTaxRateStore();
	int GetTaxHuntZone();*/
	void CheckBuildCsGuildInfo();
	void SetCalcRegGuildList(CSP_CALCREGGUILDLIST * lpMsg, int iCOUNT);
	void MakeCsTotalGuildInfo(CSP_CSGUILDUNIONINFO * lpMsg, int iCOUNT);
	void SaveCsTotalGuildInfo();
	void SetCsTotalGuildInfo(CSP_CSLOADTOTALGUILDINFO * lpMsg, int iCOUNT);
	int GetCsJoinSide(char * lpszGuildName, BYTE & btCsJoinSide, bool & bCsGuildInvolved);
	void SetAllUserCsJoinSide();
	void ResetAllUserCsJoinSide();
	void NotifySelfCsJoinSide(int iIndex);
	int OperateGate(int iNpcIndex, int bOpenType);
	int OperateGate(int iObjIndex, int iMonsterExistVal, int bOpenType);
	int CheckAttackGuildExist();
	int CheckCastleOwnerMember(int iIndex);
	int CheckCastleOwnerUnionMember(int iIndex);
	int CheckGuardianStatueExist();
	void ChangeWinnerGuild(int iCsJoinSide);
	int CheckMiddleWinnerGuild();
	int CheckCastleSiegeResult();
	int CheckUnionGuildMaster(int iIndex);
	void SetCrownUserIndex(int iIndex);
	int GetCrownUserIndex(){return m_iCastleCrownAccessUser;}
	void ResetCrownUserIndex(){m_iCastleCrownAccessUser=-1;}
	int GetCrownAccessUserX(){return m_btCastleCrownAccessUserX;}
	int GetCrownAccessUserY(){return m_btCastleCrownAccessUserY;}
	void SetCrownAccessUserX(BYTE iX){m_btCastleCrownAccessUserX = iX;}
	void SetCrownAccessUserY(BYTE iY){m_btCastleCrownAccessUserY = iY;}
	void SetCrownSwitchUserIndex(int iMonsterClass, int iIndex);
	int GetCrownSwitchUserIndex(int iMonsterClass);
	void ResetCrownSwitchUserIndex(int iMonsterClass);
	void SetCrownAccessTickCount();
	void ResetCrownAccessTickCount();
	int CheckOverlapCsMarks(int iIndex);
	int GetCsAttkGuildList(PMSG_CSATTKGUILDLIST * lpMsgBody, int & iCount);
	int CheckTeleportMagicAxisY(int iStartY, int iTargetX, int iTargetY);
	void NotifyCsSelfLeftTime(int iIndex);
	void CheckReviveNonDbNPC();
	void CheckReviveGuardianStatue();
	void ReSpawnAllUser();
	void ReSpawnEnemyUser(int bRefreshOwnerUser);
	void NotifyAllUserCsStartState(BYTE btStartState);
	void NotifyAllUserCsProgState(BYTE btProgState, char * lpszGuildName);
	void ClearCastleTowerBarrier();
	void SetAllCastleGateState(int bOpenType);
	void AddMiniMapDataReqUser(int iIndex);
	void DelMiniMapDataReqUser(int iIndex);
	void OperateMiniMapWork();
	void SendMapServerGroupMsg(char *  lpszMsg);
	void SendAllUserAnyData(BYTE * lpMsg, int iSize);
	void SendAllUserAnyMsg(char *  lpMsg, int iSize);
	void SendCsUserAnyData(BYTE * lpMsg, int iSize);
	void SendCsUserAnyMsg(char * lpszMsg);
	bool RegGuildScoreCompFunc(_CS_REG_GUILD_DATA & A, _CS_REG_GUILD_DATA & B) const;
	void OperateGmCommand(int iIndex, int iGmCommand, void * lpParam);
	void CreateDbNPC_INS();
	void SavePcRoomUserList();

	DWORD GetCrownAccessTickCount(){return m_dwCrownAccessTime;}
	void NotifyCrownSwitchInfo(int iIndex);


  /*<thisrel this+0x8>*/ /*|0x4|*/ BOOL m_bCastleSiegeEnable;
  /*<thisrel this+0xc>*/ /*|0x4|*/ BOOL m_bFileDataLoadOK;
  /*<thisrel this+0x10>*/ /*|0x4|*/ BOOL m_bDbDataLoadOK;
  /*<thisrel this+0x14>*/ /*|0x4|*/ BOOL m_bDoRun;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_iMapSvrGroup;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_iCastleDataLoadState;
  /*<thisrel this+0x20>*/ /*|0x4|*/ DWORD m_dwDbDataLoadTickCount;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_iCastleSiegeCycle;
  /*<thisrel this+0x28>*/ /*|0x4|*/ int m_iCastleSiegeState;
  /*<thisrel this+0x2c>*/ /*|0x10|*/ SYSTEMTIME m_tmSiegeEndSchedule;
  /*<thisrel this+0x3c>*/ /*|0x4|*/ BOOL m_bFixCastleCycleStartDate;
  /*<thisrel this+0x40>*/ /*|0x10|*/ SYSTEMTIME m_tmFixCastleCycleStartDate;
  /*<thisrel this+0x50>*/ /*|0x4|*/ int m_iFixCastleSpecificState;
  /*<thisrel this+0x54>*/ /*|0x4|*/ BOOL m_bFixCastleStateStartDate;
  /*<thisrel this+0x58>*/ /*|0x10|*/ SYSTEMTIME m_tmFixCastleStateStartDate;
  /*<thisrel this+0x68>*/ /*|0x4|*/ int m_iCS_REMAIN_MSEC;
  /*<thisrel this+0x6c>*/ /*|0x4|*/ int m_iCS_TICK_COUNT;
  /*<thisrel this+0x70>*/ /*|0x10|*/ SYSTEMTIME m_tmStateStartDate;
  /*<thisrel this+0x80>*/ /*|0x10|*/ SYSTEMTIME m_tmLeftCastleSiegeDate;
  /*<thisrel this+0x90>*/ /*|0x4|*/ DWORD m_dwNPC_DBSAVE_TICK_COUNT;
  /*<thisrel this+0x94>*/ /*|0x4|*/ DWORD m_dwCALC_LEFTSIEGE_TICK_COUNT;
  /*<thisrel this+0x98>*/ /*|0x4|*/ DWORD m_dwEVENT_MSG_TICK_COUNT;
  /*<thisrel this+0x9c>*/ /*|0x4|*/ DWORD m_dwCHECK_GATE_ALIVE_COUNT;
  /*<thisrel this+0xa0>*/ /*|0x4|*/ DWORD m_dwCS_JOINSIDE_REFRESH_TICK_COUNT;
  /*<thisrel this+0xa4>*/ /*|0x4|*/ DWORD m_dwCS_JOINSIDE_REFRESH_TOTAL_COUNT;
  /*<thisrel this+0xa8>*/ /*|0x4|*/ DWORD m_dwCS_MINIMAP_SEND_TICK_COUNT;
  /*<thisrel this+0xac>*/ /*|0x4|*/ DWORD m_dwCS_LEFTTIME_TICK_COUNT;
  /*<thisrel this+0xb0>*/ /*|0x4|*/ DWORD m_dwCS_STARTTIME_TICK_COUNT;
  /*<thisrel this+0xb4>*/ /*|0x10|*/ SYSTEMTIME m_tmStartDate;
  /*<thisrel this+0xc4>*/ /*|0x10|*/ SYSTEMTIME m_tmEndDate;
  /*<thisrel this+0xd4>*/ /*|0x1|*/ unsigned char m_btIsSiegeGuildList;
  /*<thisrel this+0xd5>*/ /*|0x1|*/ unsigned char m_btIsSiegeEnded;
  /*<thisrel this+0xd6>*/ /*|0x1|*/ unsigned char m_btIsCastleOccupied;
  /*<thisrel this+0xd7>*/ /*|0x10|*/ char m_szCastleOwnerGuild[16];
  /*<thisrel this+0xe8>*/ /*|0x8|*/ __int64 m_i64CastleMoney;
  /*<thisrel this+0xf0>*/ /*|0x4|*/ int m_iTaxRateChaos;
  /*<thisrel this+0xf4>*/ /*|0x4|*/ int m_iTaxRateStore;
  /*<thisrel this+0xf8>*/ /*|0x4|*/ int m_iTaxHuntZone;
  /*<thisrel this+0xfc>*/ /*|0x4|*/ BOOL m_bEnterHuntZone;
  /*<thisrel this+0x100>*/ /*|0x10|*/ vector<_CS_SCHEDULE_DATA> m_vtScheduleData;
  /*<thisrel this+0x110>*/ /*|0x18|*/ CRITICAL_SECTION m_critScheduleData;
  /*<thisrel this+0x128>*/ /*|0x10|*/ vector<_CS_NPC_DATA> m_vtNpcData;
  /*<thisrel this+0x138>*/ /*|0x18|*/ CRITICAL_SECTION m_critNpcData;
  /*<thisrel this+0x150>*/ /*|0x4|*/ BOOL m_bDbNpcCreated;
  /*<thisrel this+0x154>*/ /*|0x10|*/ map<string,_CS_TOTAL_GUILD_DATA> m_mapCsBasicGuildInfo;
  /*<thisrel this+0x164>*/ /*|0x18|*/ CRITICAL_SECTION m_critCsBasicGuildInfo;
  /*<thisrel this+0x17c>*/ /*|0x10|*/ map<string, _CS_TOTAL_GUILD_DATA> m_mapCsTotalGuildInfo;
  /*<thisrel this+0x18c>*/ /*|0x18|*/ CRITICAL_SECTION m_critCsTotalGuildInfo;
  /*<thisrel this+0x1a4>*/ /*|0x4|*/ BOOL m_bCsBasicGuildInfoLoadOK;
  /*<thisrel this+0x1a8>*/ /*|0x4|*/ BOOL m_bCsTotalGuildInfoLoadOK;
  /*<thisrel this+0x1ac>*/ /*|0x10|*/ map<int,_CS_MINIMAP_DATA > m_mapMiniMapData;
  /*<thisrel this+0x1bc>*/ /*|0x18|*/ CRITICAL_SECTION m_critCsMiniMap;
  /*<thisrel this+0x1d4>*/ /*|0x10|*/ vector<int> m_vtMiniMapReqUser;
  /*<thisrel this+0x1e4>*/ /*|0x4|*/ BOOL m_bCastleTowerAccessable;
  /*<thisrel this+0x1e8>*/ /*|0x4|*/ BOOL m_bRegCrownAvailable;
  /*<thisrel this+0x1ec>*/ /*|0x4|*/ int m_iCrownIndex;
  /*<thisrel this+0x1f0>*/ /*|0x4|*/ int m_iCastleCrownAccessUser;
  /*<thisrel this+0x1f4>*/ /*|0x1|*/ unsigned char m_btCastleCrownAccessUserX;
  /*<thisrel this+0x1f5>*/ /*|0x1|*/ unsigned char m_btCastleCrownAccessUserY;
  /*<thisrel this+0x1f8>*/ /*|0x4|*/ int m_iCastleSwitchAccessUser1;
  /*<thisrel this+0x1fc>*/ /*|0x4|*/ int m_iCastleSwitchAccessUser2;
  /*<thisrel this+0x200>*/ /*|0x4|*/ DWORD m_dwCrownAccessTime;
  /*<thisrel this+0x204>*/ /*|0x10|*/ char m_szMiddleWinnerGuild[16];  
}; 

extern CCastleSiege g_CastleSiege;

static int g_iNpcUpDfLevel_CGATE[CS_MAX_UPGRADE][0x3] = {
	1,	2,	3000000,
	2,	3,	3000000,
	3,	4,	3000000
};

static int g_iNpcUpDfLevel_CSTATUE[CS_MAX_UPGRADE][0x3] = {
	1,	3,	3000000,
	2,	5,	3000000,
	3,	7,	3000000,
};

static int g_iNpcUpMaxHP_CGATE[0x3][CS_MAX_UPGRADE] = {
	800000,		2,	1000000,
	1500000,	3,	1000000,
	3000000,	4,	1000000,
};

static int g_iNpcUpMaxHP_CSTATUE[CS_MAX_UPGRADE][0x3] = {
	750000,		3,	1000000,
	1300000,	5,	1000000,
	2500000,	7,	1000000
};

static int g_iNpcUpRgLevel_CSTATUE[CS_MAX_UPGRADE][0x3] = {
	1,	3,	5000000,
	2,	5,	5000000,
	3,	7,	5000000
};


static int g_iCsUserReSpawnArea[0x3][0x4] = {
	35,		17,		144,	48,
	74,		144,	115,	154,
	35,		11,		144,	48
};

static int g_iNpcDefense_CGATE[CS_MAX_UPGRADE + 1] = {
	100, 180, 300, 520
};
static int g_iNpcDefense_CSTATUE[CS_MAX_UPGRADE + 1] = {
	80, 180, 340, 550
}; 

#endif