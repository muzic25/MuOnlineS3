#include "StdAfx.h"
#include "RaklionUtil.h"

CRaklionUtil::CRaklionUtil()
{
}

CRaklionUtil::~CRaklionUtil()
{
}


struct PMSG_ANS_RAKLION_STATE_CHANGE
{
	PBMSG_HEAD2 h;	// C1:D1:12
	BYTE btState;	// 4
	BYTE btDetailState;	// 5
};

void CRaklionUtil::NotifyRaklionChangeState(int iState, int iDetailState)
{
	PMSG_ANS_RAKLION_STATE_CHANGE pMsg ={0};

	PHeadSubSetB((LPBYTE)&pMsg, 0xD1, 0x12, sizeof(pMsg));
	pMsg.btState = iState;
	pMsg.btDetailState = iDetailState;

	//if ( iState == 1 )
		//this->algo
	//else
		//this->algo
}


struct PMSG_ANS_RAKLION_BATTLE_RESULT
{
	PBMSG_HEAD2 h;	// C1:D1:13
	BYTE btResult;	// 4
};

void CRaklionUtil::NotifyRaklionSuccessValue(int iSuccessValue)
{
	PMSG_ANS_RAKLION_BATTLE_RESULT pMsg ={0};
	PHeadSubSetB((LPBYTE)&pMsg, 0xD1, 0x13, sizeof(pMsg));
	pMsg.btResult = iSuccessValue;

	// this -> algo
}

/*
	
	void NotifyRaklionEntranceReqResult(int iIndex, int iResult);
	void NotifyRaklionSuccessValue(int iSuccessValue);
	void NotifyRaklionCurrentState(int iIndex, int iState, int iDetailState);
	void NotifyRaklionBattleTime(int iBattleTime);
	void NotifyRaklionWideAreaAttack(int iIndex, int iTargetIndex, int iSkillType);
	void NotifyRaklionUserMonsterCount(int iMonsterCount, int iUserCount);
	void __cdecl SendMsgRaklionBattleUser(LPSTR lpszMsg, ...);
	void SendDataRaklionBattleUser(LPBYTE lpMsg, int iSize);
	void __cdecl SendMsgKauturuBossMapUser(LPSTR lpszMsg, ...);
	void SendDataRaklionBossMapUser(unsigned char* lpMsg, int iSize);
	void __cdecl SendMsgKauturuMapUser(char* lpszMsg, ...);
	void SendDataRaklionMapUser(unsigned char* lpMsg, int iSize);
	void __cdecl SendMsgAllUser(LPSTR lpszMsg, ...);
	void SendDataAllUser(unsigned char* lpMsg, int iSize);
	void __cdecl SendMsgToUser(int iIndex, char* lpszMsg, ...);
	void SendDataToUser(int iIndex, unsigned char* lpMsg, int iSize);
	void __cdecl SendRaklionChattingMsg(int iIndex, char* lpszMsg, ...);
	void SendDataRaklionTimeAttackEvent(int iIndex, BYTE btFlag, int iClearTime);*/