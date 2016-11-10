#ifndef ILLUSIONTEMPLEPROCESS_H
#define ILLUSIONTEMPLEPROCESS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_FLOOR_DATA 5
#define MAX_FLOOR_USER 10
#define MAX_STATUE_MONSTER 2
#define MAX_FLOOR_MONSTER 40
#define ILLUSIONTEMPLE_INVALID_INDEX -1

#define MAP_INDEX_ILLUSIONTEMPLE 45
#define MAP_INDEX_ILLUSIONTEMPLE_MIN 45

struct ILLUSIONTEMPLE_START_TIME
{
	int m_iHour;	// 0
	int m_iMinute;	// 4
};

static const int g_IllusionTemple_Default_Exp[MAX_FLOOR_DATA+1] =
{
	300000,//IllusionTemple1
	340000,//IllusionTemple2
	380000,//IllusionTemple3
	420000,//IllusionTemple4
	460000,//IllusionTemple5
	500000 //IllusionTemple6
};

static const int g_IllusionTemple_unk0[MAX_FLOOR_DATA+1] =
{
	50000,//IllusionTemple1
	60000,//IllusionTemple2
	70000,//IllusionTemple3
	80000,//IllusionTemple4
	90000,//IllusionTemple5
	100000 //IllusionTemple6
};

static const int g_IllusionTemple_unk1[MAX_FLOOR_DATA+1] =
{
	600, //IllusionTemple1
	1200,//IllusionTemple2
	1800,//IllusionTemple3
	2400,//IllusionTemple4
	3000,//IllusionTemple5
	3500 //IllusionTemple6
};

static const int g_IllusionTemple_unk2[MAX_FLOOR_DATA+1] =
{
	1200,//IllusionTemple1
	2400,//IllusionTemple2
	3600,//IllusionTemple3
	4800,//IllusionTemple4
	6000,//IllusionTemple5
	7200 //IllusionTemple6
};

static const int g_IllusionTemple_Team_Players[MAX_FLOOR_DATA] =
{
	10,//1 Player
	20,//2 Players
	30,//3 Players
	40,//4 Players
	50 //5 Players
};

struct _ILLUSIONTEMPLE_USER_DATA
{
	int m_UserIndex; //0x200 Unused
};

struct _ILLUSIONTEMPLE_FLOOR_DATA
{
	int m_iTeamPlayerIndex;	//aIndex 0x20
	BYTE m_btTeamJoinSide;	//Team Mask 0x24
	BYTE m_btKillCountPoint;	//KillCount Point 0x25
	DWORD m_dwShieldSpellTime;	//Shield Spell Time 0x28
	DWORD m_dwRestrictionSpellTime;	//Stern Spell Time 0x2C
	BYTE m_btUserKillCount;	//User Kill Count 0x30
	BYTE m_btMonsterRewardKillCount;	//Monster KillCount Reward Count 0x31
	BYTE m_btPlayerRewardKillCount;	//Player KillCount Reward Count 0x32
	BYTE m_btUsedKillCountPoint;	//Used KillCount Point 0x33
	__int64 m_i64ExpReward;	//Exp Reward 0x38 0x3C
	DWORD m_dwRankingPoint;	//Ranking Point 0x40
	BOOL m_bDropReward;	//Is Drop Reward 0x40
	BYTE m_btPosNDur; //Ticket Position & Durability 0x44

	_ILLUSIONTEMPLE_FLOOR_DATA()
	{
		m_iTeamPlayerIndex = -1;
		m_btPosNDur = -1;
	}
};

struct _ILLUSIONTEMPLE_STATUE_DATA
{
	int m_iStatueIndex;
	short m_sStatuePosition;
};

struct _ILLUSIONTEMPLE_MONSTER_DATA
{
	int m_iMonsterIndex;
	short m_sMonsterPosition;
};

struct _ILLUSIONTEMPLE_BARRIER
{
	PBMSG_HEAD2 h;
	BYTE m_btFloorIndex;
	BYTE m_btState;
};

struct PMSG_ANNOUNCE_BALL_PLAYER
{
	PBMSG_HEAD2 h;
	short m_sIndex;
	char chCharacter[10];
};

struct _ILLUSIONTEMPLE_RANKING_DATA
{
	PBMSG_HEAD2 h;
	BYTE m_btYellowTeamScore;
	BYTE m_btBlueTeamScore;
	BYTE m_btEnteredUserCount;
};

struct _ILLUSIONTEMPLE_PLAYER_RANK_DATA
{
	char szCharacterName[10];
	BYTE m_btMapNumber;
	BYTE m_btTeamJoinSide;
	BYTE m_btClass;
	DWORD m_dwExpReward;
};

struct PMSG_APPLY_SKILL_STATE
{
	PBMSG_HEAD2 h;
	
	BYTE m_btType;

	BYTE m_btSkillIDH;
	BYTE m_btSkillIDL;

	WORD m_wIndex;
	WORD m_wTargetIndex;
};

struct PMSG_CANCEL_SKILL_STATE
{
	PBMSG_HEAD2 h;
	
	BYTE m_btSkillIDH;
	BYTE m_btSkillIDL;

	WORD m_wTargetIndex;
};

struct PMSG_ILLUSIONTEMPLE_RANKING_UPDATE
{
	PBMSG_HEAD h;
	short aIndex;
	char AccountID[11];
	char Name[11];
	WORD ServerCode;
	int iIllusionIndex;
	int iDbClass;
	int iLevel;
	bool IsWinner;
	int iPcBang; //???
	DWORD RankingPoint;
};

struct PMSG_ILLUSIONTEMPLE_TEAMINFO_HEAD
{
	PBMSG_HEAD2 h;					// 0x00
	WORD		m_wTimer;				// 0x04
	WORD		m_waIndex;				// 0x06	[Leader index?]
	BYTE		m_btPositionX;			// 0x08
	BYTE		m_btPositionY;			// 0x09
	BYTE		m_btRelicsTeamScore;	// 0x0A
	BYTE		m_btIllusionRelicsScore;// 0x0B
	BYTE		m_btTeam;				// 0x0C [change name]
	BYTE		m_btCount;
};

struct PMSG_ILLUSIONTEMPLE_TEAMINFO_MEMBERDATA
{
	WORD	m_waIndex;		// 0x00
	BYTE	m_btMapNumber;	// 0x02
	BYTE	m_btPositionX;	// 0x03
	BYTE	m_btPositionY;	// 0x04
};

class CIllusionTempleProcess  //78 functions
{
public:
	CIllusionTempleProcess();
	virtual ~CIllusionTempleProcess();
	void Init(int FloorIndex);
	void InitFloorData(int aIndex);
	void Run(int iTick);
	void ProcState_Closed(int iTick);
	void ProcState_Waiting(int iTick);
	void ProcState_Playing(int iTick);
	void ProcState_Playend(int iTick);
	void SetState(BYTE State);
	BYTE GetState();
	void SetState_NONE();
	void SetState_READY();
	void SetState_PLAYING();
	void SetState_END();
	void CheckSync();
	BOOL LeaveBattleUser(int aIndex);
	int GetFloorIndex(int aIndex);
	BOOL AddBattleUser(int aIndex, BYTE pos, BYTE pos_dur);
	void RemoveInvalid();
	BYTE CheckLeftMinutesBeforeOpen();
	BYTE RemainTime();
	void NpcStatueProc(LPOBJ lpObj, LPOBJ lpTargetObj);
	void NpcAlliedPedestalProc(LPOBJ lpObj, LPOBJ lpTargetObj);
	void NpcRelicsPedestalProc(LPOBJ lpObj, LPOBJ lpTargetObj);
	int FindItemBallPosition(int aIndex);
	void DeleteRelicsItem(LPOBJ lpObj);
	void DropRelicsItem(int iIndex);
	void UnlockTeamPedestal(int aIndex, BYTE pos);
	void GCSendPlayerRelicsCarrier(LPOBJ lpObj);
	void TestBattleScene();
	void SetNPCPosition(int Class, int Position);
	void SetMonsterPosition(int Class, int Position);
	void ClearMonstersData();
	void CreateNPCStatus();
	void CreateNPC();
	void CreateMonsterToBattle();
	void ClearAllBattleObjects();
	void SetNpcStatueRegen();
	void RegenNPCStatus();
	void SetBattleMonstersReady();
	void SendNoticeToAll(LPSTR lpszMsg);
	void OperateMiniMapWork(BYTE btTeam);
	void NotifyTempleInfo(BYTE btState, int aIndex);
	BYTE GetUserJoinSide(int aIndex);
	BYTE AddKillPointToUser(int aIndex, BYTE btPoint);
	BYTE RemoveKillPointFromUser(int aIndex, BYTE btPoint);
	BYTE GetKillCountPointFromUser(int aIndex);
	BOOL UpdateKillCountPointFromUser(int aIndex, BYTE btPoint);
	void ResetUserKillCountPoint();
	void IncreaseUserKillCount(int aIndex);
	void IncreaseMonsterKillCount(int aIndex);
	void ResetAllKillCount();
	void IncreaseTeamPlayerReward(int aIndex);
	void ResetPlayerReward();
	void IncreaseUsedKillCount(int aIndex);
	void ResetUserUsedKillCount();
	void RunningSkill(int aIndex, WORD skill, int aTargetIndex, BYTE btDir);
	void SkillSecondProc(LPOBJ lpObj);
	void GCIllusionTempleSkillCancel(LPOBJ lpObj, WORD skill);
	BOOL ShieldSpell(LPOBJ lpObj);
	BOOL RestrictionSpell(LPOBJ lpObj, LPOBJ lpTargetObj);
	BOOL PursuitSpell(LPOBJ lpObj);
	BOOL ShieldClashSpell(LPOBJ lpObj, LPOBJ lpTargetObj);
	void GCIllusionTempleSkillApply(int aIndex, int aTargetIndex, WORD skill, BYTE btUseType);
	void ResetAndClearSkills(LPOBJ lpObj);
	void CalcSendRewardEXP();
	void DropRewardItem(int aIndex);
	int CheckEnterItemPosition(int aIndex, float Durability);
	int CheckEnterItemPosition(int aIndex);
	void DropMonsterItem(LPOBJ lpObj);
	void SendAllUserAnyMsg(LPBYTE lpMsg, int iSize);
	int LevelUp(int iUserIndex, int iAddExp);
	BYTE GetRemainTime();
	void LockTimeCheckSync(){this->m_bTimeCheckSync = TRUE;}
	BOOL GetTimeCheckSync(){return this->m_bTimeCheckSync;}
	BOOL GetOpenStatus(){return this->m_bOpenStatus;}
	BYTE GetEnteredUserCount(){return this->m_iEnteredUserCount;}
	int GetBallPlayerIndex(){return this->m_iBallPlayerIndex;}
	BOOL CheckShieldSpellTime(int aIndex);
	BOOL CheckRestrictionSpellTime(int aIndex);
	void SendRewardScore();
public:
	CRITICAL_SECTION	m_cs;

	_ILLUSIONTEMPLE_FLOOR_DATA m_FloorData[MAX_FLOOR_USER];
	_ILLUSIONTEMPLE_USER_DATA m_UserData[MAX_FLOOR_USER];

	int					m_iEnteredUserCount;

	BYTE				m_btFloorIndex;

	BYTE				m_btState;

	_ILLUSIONTEMPLE_STATUE_DATA m_StatueData[MAX_STATUE_MONSTER];

	int					m_iYellowPedestalIndex;
	short				m_sYellowPedestalPosition;

	int					m_iBluePedestalIndex;
	short				m_sBluePedestalPosition;

	_ILLUSIONTEMPLE_MONSTER_DATA m_MonsterData[MAX_FLOOR_MONSTER];

	BOOL				m_bOpenStatus;

	int					m_iStatueRegenTickCount; //should be DWORD

	int					m_iLeftMinutesBeforeOpen;
	int					m_iEventBattleTimer;

	int					m_iCloseTickCount; //should be DWORD
	int					m_iOpenTickCount; //should be DWORD

	int					m_iLeftMinutesBeforeEnd;

	BOOL				m_bIllusionTempleEventEnded;
	BOOL				m_bMsgBeforeEnterTemple;
	BOOL				m_bMsgBeforeEnterBattle;

	int					m_iBallPlayerIndex;

	BYTE				m_btAllowedRegPedestal;

	BYTE				m_btBallInventoryPosition;

	int					m_iStatueCount;
	int					m_iMonsterCount;

	int					m_iYellowTeamUserCount;
	int					m_iBlueTeamUserCount;

	BYTE				m_btYellowTeamScore;
	BYTE				m_btBlueTeamScore;

	BYTE				m_btWinnerTeam;

	BYTE				m_btYellowTeamClassCount[MAX_TYPE_PLAYER];
	BYTE				m_btBlueTeamClassCount[MAX_TYPE_PLAYER];

	BOOL				m_bTimeCheckSync;

	BOOL				m_bScoreRankSet;
};

extern std::list<ILLUSIONTEMPLE_START_TIME> m_listIllusionTempleOpenTime;

#endif