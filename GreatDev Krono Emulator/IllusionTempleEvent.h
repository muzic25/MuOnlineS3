#ifndef ILLUSIONTEMPLEEVENT_H
#define ILLUSIONTEMPLEEVENT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <list>
#include "user.h"
#include "IllusionTempleProcess.h"

extern int g_iIllusionTempleEvent;
extern int g_iOldScrollDropRate;
extern int g_iCovenantOfIllusionDropRate;
extern int g_iUseMaxLevelIllusionTemple;
extern int g_iSaveIllusionTempleRankingPoint;
extern int g_iIllusionTempleRewardPercent;
extern int g_iIllusionTempleMinUseSkillCnt;
extern int g_iIllusionTempleRewardPercentMaster;

#define IT_MAP_RANGE(mapnumber) ( ((mapnumber) < MAP_INDEX_ILLUSION_TEMPLE1)?FALSE:((mapnumber) > MAP_INDEX_ILLUSION_TEMPLE6 )?FALSE:TRUE )
#define IT_TICKET_RANGE(x) ( ((x)<0)?FALSE:((x)>MAX_FLOOR_DATA)?FALSE:TRUE  )

extern int m_i_IT_PlayTime;
extern int m_i_IT_OpenTime;
extern int m_i_IT_CloseTime;
extern int m_i_IT_RestTime;
extern int m_i_IT_WaitTime;
extern int m_i_IT_MinPlayer;

struct PMSG_SEND_ILLUSION_ENTER_RESULT
{
	PBMSG_HEAD2 h;
	BYTE btResult;
};

struct PMSG_REQ_ILLUSIONTEMPLE_ENTER
{
	PBMSG_HEAD h;
	char AccountID[10];
	char CharacterName[10];
	int ServerCode;
	int Index;
	
	int InventoryTicketPos;
	int Level;
	int FloorIndex;
};

struct PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT
{
	PBMSG_HEAD h;
	char AccountID[10];
	char CharacterName[10];
	int ServerCode;
};

struct PMSG_ANS_ILLUSIONTEMPLE_ENTER_RESULT
{
	PBMSG_HEAD h;
	char AccountID[10];
	char CharacterName[10];
	int ServerCode; //18
	int Index; //1C
	int IsEntered; //20
	int iPos; //24
	int TicketLevel; //28
	int FloorIndex; //2C
};

struct PMSG_MIRAGE_ENTRANCE_INFO
{
	PBMSG_HEAD2 h;
	BYTE btIllusionState[MAX_FLOOR_DATA+1];
};

struct PMSG_ANS_ILLUSIONTEMPLE_ENTERCOUNT
{
	PBMSG_HEAD h;
	char AccountID[10];	// 3
	char GameID[10];	// D
	int ServerCode;	// 18
	int iObjIndex;	// 1C
	int iLeftCount;	// 20
};

struct PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT
{
	PBMSG_HEAD h;	// C1:0B
	char AccountID[10];	// 3
	char GameID[10];	// D
	int ServerCode;	// 18
	int iObjIndex;	// 1C
};


class CIllusionTempleEvent
{
public:
	CIllusionTempleEvent();
	virtual ~CIllusionTempleEvent();

	BOOL Init();
	BOOL ReadCommonServerInfo();
	BOOL Load(LPSTR lpszFileName);
	void Run();
	void SetRegPedestal(BYTE btMapNumber, int aIndex, BYTE pos);
	void SetRelicsCarrierViewState(LPOBJ lpObj);
	BOOL IllusionTempleAddUser(int aIndex, BYTE FloorIndex, BYTE TicketPos);
	BOOL EGReqIllusionTempleEnter(int aIndex, BYTE FloorIndex, BYTE TicketPos, int Level);
	void EGAnsIllusionTempleEnter(PMSG_ANS_ILLUSIONTEMPLE_ENTER_RESULT * lpMsg);
	void EGSetIllusionTempleEnterCount(LPOBJ lpObj);
	BOOL BattleDeleteUser(int aIndex, BYTE MapNumber);
	BOOL CheckEnterLevel(int aIndex, int TicketLevel);
	void SetNpcStatueUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj);
	void SetNpcAlliedUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj);
	void SetNpcRelicsUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj);
	void SetNpcMirageUser(LPOBJ lpObj, LPOBJ lpTargetObj);
	void SetDeleteRelicsItem(BYTE MapNumber, LPOBJ lpObj);
	void SearchUserDropQuestItem(BYTE btMapNumber, int aIndex);
	void OperateGMCommand(int iCommand, BYTE btMapNumber);
	BYTE GetState(BYTE btMapNumber);
	void CreateNPCPosition(BYTE MapNumber, int Class, int Position);
	void CreateMonsterPosition(BYTE MapNumber, int Class, int Position);
	void AllObjReset();
	BYTE GetUserJoinSide(BYTE MapNumber, int aIndex);
	void SetNpcStatueRegen(BYTE MapNumber);
	void TicketChaosMix(LPOBJ lpObj);
	BYTE IllusionTempleChaosMix(int arg1, int arg2, int arg3);
	BOOL CheckChoasMixItem(int arg1);
	BYTE SetKillCount(int aIndex, BYTE btMapNumber, BYTE btObjType);
	BYTE RemoveKillPointFromUser(int aIndex, BYTE MapNumber, BYTE KillPoint);
	void RunningSkill(int aIndex, int aTargetIndex, WORD skill);
	void SkillProc(LPOBJ lpObj);
	void ResetAndClearSkills(LPOBJ lpObj);
	void DeathSetShield(LPOBJ lpObj);
	void IncUsedKillCount(int aIndex, BYTE MapNumber);
	void SetEntranceNpcIndex(int arg1);
	void NotifyTempleEntranceInfo();
	BOOL CheckWearingMOPH(int iUserIndex);
	BOOL CheckPolymorphItem(int iItemCode);
	BOOL CheckTeleport(int aIndex);
	void SearchNDropMonsterItem(LPOBJ lpObj);
	void GiveItemReward(int arg1);
	BYTE GetRemainTime();
	BOOL GetShieldSpellStatus(int aIndex, BYTE MapNumber);
	BOOL GetRestrictionSpellStatus(int aIndex, BYTE MapNumber);
	int GetEnterLevel(int aIndex);
	int CheckLuckyTalisman(int aIndex);
	void EGReqIllusionTempleEnterCount(int iIndex);
	void EGAnsIllusionTempleEnterCount(PMSG_ANS_ILLUSIONTEMPLE_ENTERCOUNT* lpMsg);
private:
	CIllusionTempleProcess	m_IllusionTempleProcess[MAX_FLOOR_DATA+1];
	int m_iEntranceNpcIndex;
};

extern CIllusionTempleEvent g_IllusionTempleEvent;

#endif