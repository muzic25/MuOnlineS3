// RaklionUtil.h: interface for the CRaklionUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAKLIONUTIL_H__47AA316A_7F8C_4B70_B823_4B6393D65A37__INCLUDED_)
#define AFX_RAKLIONUTIL_H__47AA316A_7F8C_4B70_B823_4B6393D65A37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRaklionUtil  
{
public:
	CRaklionUtil();
	virtual ~CRaklionUtil();

	void NotifyRaklionChangeState(int iState, int iDetailState);
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
	void SendDataRaklionTimeAttackEvent(int iIndex, BYTE btFlag, int iClearTime);

};

//static CRaklionUtil g_RaklionUtil;

#endif // !defined(AFX_RAKLIONUTIL_H__47AA316A_7F8C_4B70_B823_4B6393D65A37__INCLUDED_)
