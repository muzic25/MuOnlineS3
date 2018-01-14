//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "IllusionTempleEvent.h"
#include "IllusionTempleProcess.h"
#include "GameMain.h"
#include "logproc.h"
#include "readscript.h"
#include "winutil.h"
#include "GameServer.h"
#include "CastleSiegeSync.h"
#include "CrywolfSync.h"
#include "DSProtocol.h"
#include "Event.h"
#include "DevilSquare.h"

int g_iIllusionTempleEvent = 1;
int g_iOldScrollDropRate = 0;
int g_iCovenantOfIllusionDropRate = 0;
int g_iUseMaxLevelIllusionTemple = 0;
int g_iSaveIllusionTempleRankingPoint = 0;
int g_iIllusionTempleRewardPercent = 100;
int g_iIllusionTempleMinUseSkillCnt = 3;
int g_iIllusionTempleRewardPercentMaster = 100;

int m_i_IT_PlayTime;
int m_i_IT_OpenTime;
int m_i_IT_CloseTime;
int m_i_IT_RestTime;
int m_i_IT_WaitTime;

CIllusionTempleEvent g_IllusionTempleEvent;

CIllusionTempleEvent::CIllusionTempleEvent()
{

}

CIllusionTempleEvent::~CIllusionTempleEvent()
{
	
}

BOOL CIllusionTempleEvent::Init()
{
	for(int i = 0; i < MAX_FLOOR_DATA+1; i++)
	{
		this->m_IllusionTempleProcess[i].Init(i);
	}
	return TRUE;
}

BOOL CIllusionTempleEvent::ReadCommonServerInfo()
{
	this->Load(gDirPath.GetNewPath("\\Events\\IllusionTemple.dat"));
	g_iIllusionTempleEvent = GetPrivateProfileInt("GameServerInfo","IllusionTempleEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iOldScrollDropRate = GetPrivateProfileInt("GameServerInfo","OldScrollDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCovenantOfIllusionDropRate = GetPrivateProfileInt("GameServerInfo","CovenantOfIllusionDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iUseMaxLevelIllusionTemple = GetPrivateProfileInt("GameServerInfo","UseMaxLevelIllusionTemple",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSaveIllusionTempleRankingPoint = GetPrivateProfileInt("GameServerInfo","SaveIllusionTempleRankingPoint",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iIllusionTempleRewardPercent = GetPrivateProfileInt("GameServerInfo","IllusionTempleRewardPercent",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iIllusionTempleMinUseSkillCnt = GetPrivateProfileInt("GameServerInfo","IllusionTempleMinUseSkillCnt",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iIllusionTempleRewardPercentMaster = GetPrivateProfileInt("GameServerInfo","IllusionTempleRewardPercentMaster",0, gDirPath.GetNewPath("commonserver.cfg")); //season4 add-on
	return TRUE;
}

BOOL CIllusionTempleEvent::Load(LPSTR lpszFileName)
{
	SMDFile = fopen(lpszFileName, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("[Illusion Temple] Info file Load Fail [%s]", lpszFileName);
		return false;
	}

	int Token;
	int type;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		type = TokenNumber;

		while ( true )
		{
			if ( type == 0 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				m_i_IT_OpenTime = TokenNumber;

				Token = GetToken();
				m_i_IT_WaitTime = TokenNumber;

				Token = GetToken();
				m_i_IT_PlayTime = TokenNumber;

				Token = GetToken();
				m_i_IT_RestTime = TokenNumber;
			}
			else if ( type == 1 )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				ILLUSIONTEMPLE_START_TIME Schedule;

				Schedule.m_iHour = TokenNumber;

				Token = GetToken();
				Schedule.m_iMinute = TokenNumber;

				m_listIllusionTempleOpenTime.push_back(Schedule);
			}
		}
	}

	fclose(SMDFile);
	LogAdd("%s file load!", lpszFileName);

	return true;
}

void CIllusionTempleEvent::Run()
{
	if(g_iIllusionTempleEvent == 0)
	{
		return;
	}

	int loc2 = GetTickCount();
	int loc3 = 0;
	int i;

	if(this->m_IllusionTempleProcess[0].GetRemainTime() == 10 && this->m_IllusionTempleProcess[0].GetTimeCheckSync() == 0)
	{
		loc3 = 1;
		this->m_IllusionTempleProcess[0].LockTimeCheckSync();
	}

	for(i = 0; i < MAX_FLOOR_DATA+1; i++)
	{
		if(loc3 == 1)
		{
			this->m_IllusionTempleProcess[i].CheckSync();
		}
		this->m_IllusionTempleProcess[i].Run(loc2);
	}
}

void CIllusionTempleEvent::SetRegPedestal(BYTE btMapNumber, int aIndex, BYTE pos)
{
	if( CHECK_LIMIT( (btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}
	this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].UnlockTeamPedestal(aIndex, pos);
}

void CIllusionTempleEvent::SetRelicsCarrierViewState(LPOBJ lpObj)
{
	if( CHECK_LIMIT( (lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}
	this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GCSendPlayerRelicsCarrier(lpObj);
}

BOOL CIllusionTempleEvent::IllusionTempleAddUser(int aIndex, BYTE FloorIndex, BYTE TicketPos)
{
	if(g_iIllusionTempleEvent == 0 )
	{
		return FALSE;
	}

	LPOBJ lpObj;
	PMSG_SEND_ILLUSION_ENTER_RESULT pResult;
	BOOL bPlayerKiller;
	int loc6;
	int loc7;
	int loc8;
	PMSG_PARTYDELUSER pMsg;
	int loc10;

	if(CHECK_LIMIT( (FloorIndex), MAX_FLOOR_DATA+1) == FALSE)
	{
		return FALSE;
	}

	lpObj = &gObj[aIndex];
	PHeadSubSetB((LPBYTE)&pResult, 0xBF, 0x00, sizeof(pResult));
	pResult.btResult = 0;

	if(lpObj->Type != 1 || lpObj->Connected <= PLAYER_LOGGED)
	{
		return FALSE;
	}

	if ( lpObj->m_IfState.use != 0 && lpObj->m_IfState.type != 12 )
	{
		return FALSE;
	}

	if ( lpObj->m_bPShopOpen == true )
	{
		::CGPShopReqClose(lpObj->m_Index);
	}

	bPlayerKiller = FALSE;
#pragma message ("Need Check PKLEVEL")
	if(lpObj->PartyNumber >= 0)
	{
		/*if( (gParty.GetPkLevel(lpObj->PartyNumber)) >= 5)
		{
			bPlayerKiller = TRUE;
		}	*/
	}
	else if( lpObj->m_PK_Level >= 4 )
	{
		bPlayerKiller = TRUE;
	}

	if(bPlayerKiller == TRUE)
	{
		pResult.btResult = 7;
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
		return FALSE;
	}

	if(this->CheckWearingMOPH(aIndex) != FALSE)
	{
		pResult.btResult = 8;
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
		return FALSE;
	}

	if(this->m_IllusionTempleProcess[FloorIndex].GetState() != 0 || this->m_IllusionTempleProcess[FloorIndex].GetOpenStatus() == FALSE)
	{
		pResult.btResult = 2;
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
		return FALSE;
	}

	if(gObj[aIndex].pInventory[TicketPos].IsItem() == TRUE)
	{
		if(gObj[aIndex].pInventory[TicketPos].m_Type == ITEMGET(13,51))
		{
			loc6 = gObj[aIndex].pInventory[TicketPos].m_Level;
			loc7 = gObj[aIndex].pInventory[TicketPos].m_Number;

			if(CHECK_LIMIT( loc6-1, MAX_FLOOR_DATA+1 ) == 0 && gObj[aIndex].pInventory[TicketPos].m_Durability != 1.0f)
			{
				pResult.btResult = 1;
				DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
				return FALSE;
			}
		}
		else if(gObj[aIndex].pInventory[TicketPos].m_Type == ITEMGET(13,61))
	{
			loc7 = gObj[aIndex].pInventory[TicketPos].m_Number;
			loc6 = this->GetEnterLevel(aIndex);
			
			if(loc6 <= 0)
			{
				pResult.btResult = 1;
				DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
				return FALSE;
			}
		}
		else
		{
			pResult.btResult = 1;
			DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
			return FALSE;
		}
	}
	else
	{
		pResult.btResult = 1;
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
		return FALSE;
	}
	
	if(this->EGReqIllusionTempleEnter(aIndex, FloorIndex, TicketPos, loc6) != FALSE)
	{
		return TRUE;
	}

	if(this->CheckEnterLevel(aIndex, loc6) == FALSE)
	{
		pResult.btResult = 3;
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);
		return FALSE;
	}

	this->m_IllusionTempleProcess[loc6-1].RemoveInvalid();

	loc8 = this->m_IllusionTempleProcess[loc6-1].AddBattleUser(aIndex, FloorIndex, TicketPos);

	if(loc8 == 1)
	{
		if(lpObj->PartyNumber >= 0)
		{
			loc10 = gParty.GetIndex(lpObj->PartyNumber, lpObj->m_Index, lpObj->DBNumber);

			if(loc10 >= 0)
			{
				pMsg.Number = loc10;
				CGPartyDelUser(&pMsg, lpObj->m_Index);
			}
		}

		if(lpObj->pInventory[TicketPos].m_Type == ITEMGET(13,51) )
		{
			lpObj->pInventory[TicketPos].m_Durability = 0;
			GCItemDurSend(lpObj->m_Index, TicketPos, lpObj->pInventory[TicketPos].m_Durability, 0);
		}
		else if(lpObj->pInventory[TicketPos].m_Type == ITEMGET(13,61) && lpObj->pInventory[TicketPos].m_Durability > 0.0f)
		{
			lpObj->pInventory[TicketPos].m_Durability -= 1.0f;
			GCItemDurSend(lpObj->m_Index, TicketPos, lpObj->pInventory[TicketPos].m_Durability, 0);
		}

		LogAddTD("[Illusion Temple] (%d) EnterUser: (%s)(%s) class:%d (Serial:%u).", loc6, lpObj->AccountID, lpObj->Name, lpObj->DbClass, lpObj->pInventory[TicketPos].m_Number); //season4 changed
		DataSend(aIndex,(LPBYTE)&pResult,pResult.h.size);

		gObjMoveGate(lpObj->m_Index,loc6+141);
	}

	this->m_IllusionTempleProcess[FloorIndex].NotifyTempleInfo(0, lpObj->m_Index);
	this->NotifyTempleEntranceInfo();

#if(DEBUG_IT == 1)
	GCServerMsgStringSend("CIllusionTempleEvent::IllusionTempleAddUser", lpObj->m_Index, 0);
#endif

	return TRUE;
}

BOOL CIllusionTempleEvent::EGReqIllusionTempleEnter(int aIndex, BYTE FloorIndex, BYTE TicketPos, int Level)
{
	if(DevilSquareEventConnect != 0) //season4 changed
	{
		return FALSE;
	}

	PMSG_REQ_ILLUSIONTEMPLE_ENTER pMsg;

	PHeadSetB((LPBYTE)&pMsg, 0x12, sizeof(pMsg));

	memcpy(pMsg.AccountID, gObj[aIndex].AccountID, 10);
	memcpy(pMsg.CharacterName, gObj[aIndex].Name, 10);

	pMsg.ServerCode = Configs.gGameServerCode;
	pMsg.Index = aIndex;
	pMsg.InventoryTicketPos = TicketPos;
	pMsg.Level = Level;
	pMsg.FloorIndex = FloorIndex;
	
	DataSendRank((char *)&pMsg, pMsg.h.size); //season4 changed

	return TRUE;
}

void CIllusionTempleEvent::EGAnsIllusionTempleEnter(PMSG_ANS_ILLUSIONTEMPLE_ENTER_RESULT * lpMsg)
{
	if( CHECK_LIMIT( (lpMsg->FloorIndex), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	if( OBJMAX_RANGE(lpMsg->Index) == FALSE )
	{
		return;
	}

	if( CHECK_LIMIT( (lpMsg->iPos), 75+1) == FALSE )
	{
		return;
	}

	LPOBJ lpObj = &gObj[lpMsg->Index];
	BYTE loc3 = lpMsg->FloorIndex;
	int loc4 = 0;
	PMSG_SEND_ILLUSION_ENTER_RESULT pMsg;


	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x00, sizeof(pMsg));
	pMsg.btResult = 0;

	int loc6;
	int loc7;

	if(lpMsg->IsEntered == 0)
	{
		pMsg.btResult = 5;
		DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(this->m_IllusionTempleProcess[loc3].GetState() != 0 || this->m_IllusionTempleProcess[loc3].GetOpenStatus() == FALSE)
	{
		pMsg.btResult = 2;
		DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(lpObj->pInventory[lpMsg->iPos].IsItem() == TRUE)
	{
		if(lpObj->pInventory[lpMsg->iPos].m_Type == ITEMGET(13,51))
		{
			loc6 = lpObj->pInventory[lpMsg->iPos].m_Level;
			loc7 = lpObj->pInventory[lpMsg->iPos].m_Number;

			if(CHECK_LIMIT( loc6-1, MAX_FLOOR_DATA+1 ) == 0 && lpObj->pInventory[lpMsg->iPos].m_Durability != 1.0f)
			{
				pMsg.btResult = 1;
				DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
				return;
			}
		}

		if(lpObj->pInventory[lpMsg->iPos].m_Type == ITEMGET(13,61) && lpObj->pInventory[lpMsg->iPos].m_Durability > 0.0f) //fix the webzen bug
		{
			loc7 = lpObj->pInventory[lpMsg->iPos].m_Number;
			loc4 = this->GetEnterLevel(lpObj->m_Index);
			
			if(loc4 <= 0)
			{
				pMsg.btResult = 3;
				DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
				return;
			}
			else
			{
				loc6 = loc4;
			}
		}
		else
		{
			pMsg.btResult = 1;
			DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
			return;
		}
	}
	else
	{
		pMsg.btResult = 1;
		DataSend(lpMsg->Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(this->CheckEnterLevel(lpMsg->Index, loc6) == FALSE)
	{
		pMsg.btResult = 3;
		DataSend(lpMsg->Index,(LPBYTE)&pMsg,pMsg.h.size);
		return;
	}

	this->m_IllusionTempleProcess[loc6-1].RemoveInvalid();

	int loc8 = this->m_IllusionTempleProcess[loc6-1].AddBattleUser(lpMsg->Index, loc3, lpMsg->iPos);

	PMSG_PARTYDELUSER pPartyMsg;

	if(loc8 == 1)
	{
		if(lpObj->PartyNumber >= 0)
		{
			int loc10 = gParty.GetIndex(lpObj->PartyNumber, lpObj->m_Index, lpObj->DBNumber);

			if(loc10 >= 0) //ebp28
			{
				
				pPartyMsg.Number = loc10; //Index
				CGPartyDelUser(&pPartyMsg, lpObj->m_Index);
			}
		}

		if(loc4 != 0)
		{
			lpObj->pInventory[lpMsg->iPos].m_Durability -= 1.0f;
			GCItemDurSend(lpObj->m_Index, lpMsg->iPos, lpObj->pInventory[lpMsg->iPos].m_Durability, 0);
		}
		else
		{
			lpObj->pInventory[lpMsg->iPos].m_Durability = 0;
			GCItemDurSend(lpObj->m_Index, lpMsg->iPos, lpObj->pInventory[lpMsg->iPos].m_Durability, 0);
		}

		LogAddTD("[Illusion Temple] (%d) EnterUser: (%s)(%s) class:%d (Serial:%u).", loc6, lpObj->AccountID, lpObj->Name, lpObj->DbClass, lpObj->pInventory[lpMsg->iPos].m_Number); //season4 changed
		DataSend(lpMsg->Index,(LPBYTE)&pMsg,pMsg.h.size);

		gObjMoveGate(lpObj->m_Index,loc6+141);
	}
	else
	{
		pMsg.btResult = 4;
		DataSend(lpMsg->Index,(LPBYTE)&pMsg,pMsg.h.size);
		return;
	}

	this->m_IllusionTempleProcess[loc3].NotifyTempleInfo(0, lpMsg->Index);
	this->NotifyTempleEntranceInfo();
	this->EGSetIllusionTempleEnterCount(lpObj);

#if(DEBUG_IT == 1)
	GCServerMsgStringSend("CIllusionTempleEvent::EGAnsIllusionTempleEnter", lpObj->m_Index, 0);
#endif
}

void CIllusionTempleEvent::EGSetIllusionTempleEnterCount(LPOBJ lpObj)
{
	PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg, 0x13, sizeof(pMsg));

	memcpy(pMsg.AccountID, lpObj->AccountID, 10);
	memcpy(pMsg.CharacterName, lpObj->Name, 10);
	pMsg.ServerCode = Configs.gGameServerCode;
	
	DataSendRank((char *)&pMsg, pMsg.h.size); //season4 changed
}

BOOL CIllusionTempleEvent::BattleDeleteUser(int aIndex, BYTE MapNumber)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return FALSE;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].LeaveBattleUser(aIndex);
	this->NotifyTempleEntranceInfo();

	return TRUE;
}

BOOL CIllusionTempleEvent::CheckEnterLevel(int aIndex, int TicketLevel)
{
	int loc2 = -1;

	if( gObj[aIndex].Level < 220 )
	{
		loc2 = -1;
	}
	else if( gObj[aIndex].Level < 271 )
	{
		loc2 = 0;
	}
	else if( gObj[aIndex].Level < 321 )
	{
		loc2 = 1;
	}
	else if( gObj[aIndex].Level < 351 )
	{
		loc2 = 2;
	}
	else if( gObj[aIndex].Level < 381 )
	{
		loc2 = 3;
	}
	else if( gObj[aIndex].Level < 400 )
	{
		loc2 = 4;
	}
	else if( gObj[aIndex].Level == 400 && gObj[aIndex].ChangeUP3rd == 0)
	{
		loc2 = 4;
	}
	else if( gObj[aIndex].Level == 400 && gObj[aIndex].ChangeUP3rd != 0)
	{
		if(g_iUseMaxLevelIllusionTemple != 0)
		{
			loc2 = 5;
		}
		else
		{
			loc2 = 4;
		}
	}
	else
	{
		loc2 = -1;
	}

	if(loc2+1 == TicketLevel)
	{
		return TRUE;
	}
	return FALSE;
}

void CIllusionTempleEvent::SetNpcStatueUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].NpcStatueProc(lpObj, lpTargetObj);
}

void CIllusionTempleEvent::SetNpcAlliedUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].NpcAlliedPedestalProc(lpObj, lpTargetObj);
}

void CIllusionTempleEvent::SetNpcRelicsUser(BYTE MapNumber, LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].NpcRelicsPedestalProc(lpObj, lpTargetObj);
}

void CIllusionTempleEvent::SetNpcMirageUser(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(lpTargetObj->m_IfState.use != 0 && lpTargetObj->m_IfState.type != 12)
	{
		return;
	}

	if(lpTargetObj->m_PK_Level >= 4)
	{
		GCServerMsgStringSend(lMsg.Get(3400), lpTargetObj->m_Index, 1); //Player Killer are not allowed to enter Illusion Temple Event
		return;
	}

	int loc2 = -1;

	if( lpTargetObj->Level < 220 )
	{
		loc2 = -1;
	}
	else if( lpTargetObj->Level < 271 )
	{
		loc2 = 0;
	}
	else if( lpTargetObj->Level < 321 )
	{
		loc2 = 1;
	}
	else if( lpTargetObj->Level < 351 )
	{
		loc2 = 2;
	}
	else if( lpTargetObj->Level < 381 )
	{
		loc2 = 3;
	}
	else if( lpTargetObj->Level < 400 )
	{
		loc2 = 4;
	}
	else if( lpTargetObj->Level == 400 && lpTargetObj->ChangeUP3rd == 0)
	{
		loc2 = 4;
	}
	else if( lpTargetObj->Level == 400 && lpTargetObj->ChangeUP3rd != 0)
	{
		if( g_iUseMaxLevelIllusionTemple != 0 )
		{
			loc2 = 5;
		}
		else
		{
			loc2 = 4;
		}
	}
	else
	{
		loc2 = -1;
	}

	if(IT_TICKET_RANGE(loc2) == 0)
	{
		GCServerMsgStringSend(lMsg.Get(3401), lpTargetObj->m_Index, 1); //Your level is not enough to enter Illusion Temple Event
		return;
	}

	int loc3 = this->m_IllusionTempleProcess[loc2].CheckEnterItemPosition(lpTargetObj->m_Index); //season 3.0 changed

	if(loc3 == -1)
	{
		GCServerMsgStringSend(lMsg.Get(3402), lpTargetObj->m_Index, 1); //You do not have Blood Scroll or the durability is broken to enter Illusion Temple Event
		return;
	}

	if(this->m_IllusionTempleProcess[loc2].GetState() != 0)
	{
		GCServerMsgStringSend(lMsg.Get(3403), lpTargetObj->m_Index, 1); //Illusion Temple Event is not Open Yet!
		return;
	}

	if(this->m_IllusionTempleProcess[loc2].GetState() != 0 || this->m_IllusionTempleProcess[loc2].GetOpenStatus() == FALSE)
	{
		GCServerMsgStringSend(lMsg.Get(3404), lpTargetObj->m_Index, 1); //This is not the appropriate time
		return;
	}

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x14;

	pMsg.level1 = this->m_IllusionTempleProcess[loc2].CheckLeftMinutesBeforeOpen();
	pMsg.level2 = this->m_IllusionTempleProcess[loc2].GetEnteredUserCount();

	DataSend(lpTargetObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
}

void CIllusionTempleEvent::SetDeleteRelicsItem(BYTE MapNumber, LPOBJ lpObj) // -> Unused
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].DeleteRelicsItem(lpObj);
}

void CIllusionTempleEvent::SearchUserDropQuestItem(BYTE btMapNumber, int aIndex)
{
	if( CHECK_LIMIT( (btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].DropRelicsItem(aIndex);
}
 
void CIllusionTempleEvent::OperateGMCommand(int iCommand, BYTE btMapNumber) //unused
{
	return;
	switch ( iCommand )
	{
		case 1:
			if ( this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() == 0 )
			{
				this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetState(1);
			}
			break;

		case 2:
			if ( this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() == 1 )
			{
				this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetState(2);
			}
			break;

		case 3:
			if ( this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() == 2 )
			{
				this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetState(3);
			}
			break;
	}
}

BYTE CIllusionTempleEvent::GetState(BYTE btMapNumber)
{
	return this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState();
}

void CIllusionTempleEvent::CreateNPCPosition(BYTE MapNumber, int Class, int Position)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetNPCPosition(Class, Position);
}

void CIllusionTempleEvent::CreateMonsterPosition(BYTE MapNumber, int Class, int Position)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetMonsterPosition(Class, Position);
}

void CIllusionTempleEvent::AllObjReset()
{
	for(int i = 0; i < MAX_FLOOR_DATA+1; i++)
	{
		this->m_IllusionTempleProcess[i].ClearMonstersData();
	}
}

BYTE CIllusionTempleEvent::GetUserJoinSide(BYTE MapNumber, int aIndex)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return -1;
	}
	return this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetUserJoinSide(aIndex);
}

void CIllusionTempleEvent::SetNpcStatueRegen(BYTE MapNumber)
{
	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SetNpcStatueRegen();
}

void CIllusionTempleEvent::TicketChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	int aIndex;
	int ebp18;
	int iRET_VAL;

	aIndex = lpObj->m_Index;
	ebp18 = 0;
	iRET_VAL = this->CheckChoasMixItem(aIndex);
	ebp18 = this->CheckLuckyTalisman(aIndex);

	if(ebp18 > 10)
	{
		iRET_VAL = 15;
	}

	if ( IT_MAP_RANGE((iRET_VAL+(MAP_INDEX_ILLUSIONTEMPLE_MIN-1))) != FALSE )
	{
		if(this->IllusionTempleChaosMix(aIndex, iRET_VAL, ebp18) == FALSE)
		{
			lpObj->ChaosLock = FALSE;
		}
		return;
	}

	switch ( iRET_VAL )
	{
		case 9:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 10:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 11:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 12:
			pMsg.Result = CB_INVALID_ITEM_LEVEL	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 13:
			pMsg.Result = CB_BC_NOT_ENOUGH_ZEN	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 14:
			pMsg.Result = CB_USER_CLASS_LOW_LEVEL	;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;
		case 15:
			pMsg.Result = 0xF0;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			break;
		default:
			lpObj->ChaosLock = FALSE;
	}
}	  

BYTE CIllusionTempleEvent::IllusionTempleChaosMix(int arg1, int arg2, int arg3)
{
	if( OBJMAX_RANGE(arg1) == FALSE )
	{
		return FALSE;
	}

	if ( IT_MAP_RANGE((arg2+(MAP_INDEX_ILLUSIONTEMPLE_MIN-1))) == FALSE )
	{
		return FALSE;
	}

	int loc2 = 0;

	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	gObj[arg1].ChaosLock = TRUE;
	LogAddTD("[Illusion Temple] 피의 두루마리 Mix Chaos Mix Start (Account:%s, Name:%s, Level:%d)", gObj[arg1].AccountID, gObj[arg1].Name, arg2);

	char szTemp[17];
	wsprintf(szTemp, "피의 두루마리 Mix,%d", arg2);

	LogChaosItem(&gObj[arg1], szTemp);

	int iMIX_SUCCESS_RATE = g_iIT_ChoasMixSuccessRate[arg2-1]; //loc11

	if ( iMIX_SUCCESS_RATE < 0 || iMIX_SUCCESS_RATE > 100 )
	{
		DataSend(arg1, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[Illusion Temple] 피의 두루마리 Mix Chaos Mix Failed - MixRate Out of Bound (Account:%s, Name:%s, Level:%d)", gObj[arg1].AccountID, gObj[arg1].Name, arg2);
		return FALSE;
	}

	if ( g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit )
	{
		iMIX_SUCCESS_RATE += g_CrywolfSync.GetPlusChaosRate();
	}

	int iMIX_NEED_MONEY = g_iIT_ChoasMixMoney[arg2-1]; //loc12

	int iChaosTaxMoney = (int)((__int64)(iMIX_NEED_MONEY) * (__int64)(g_CastleSiegeSync.GetTaxRateChaos(arg1)) / (__int64)100); //loc13

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iMIX_NEED_MONEY += iChaosTaxMoney;

	if ( iMIX_NEED_MONEY <  0 )
	{
		DataSend(arg1, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[Illusion Temple] 피의 두루마리 Mix Chaos Mix Failed - MixMoney < 0 (Account:%s, Name:%s, Level:%d)",	gObj[arg1].AccountID, gObj[arg1].Name, arg2);
		return FALSE;
	}

	if ( (gObj[arg1].Money - iMIX_NEED_MONEY) < 0 )
	{
		pMsg.Result = CB_BC_NOT_ENOUGH_ZEN;
		DataSend(arg1, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[Illusion Temple] 피의 두루마리 Mix Chaos Mix Failed - Not Enough Money (Account:%s, Name:%s, Level:%d)",	gObj[arg1].AccountID, gObj[arg1].Name, arg2);
		return FALSE;
	}

	gObj[arg1].Money -= iMIX_NEED_MONEY;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(arg1, gObj[arg1].Money);

	iMIX_SUCCESS_RATE += arg3; //season 3.0 moved

	if ( (rand()%100) < iMIX_SUCCESS_RATE )	// Success (season 3.0 changed)
	{
		int item_num = ITEMGET(13,51);	// Blood Scroll loc14
		ItemSerialCreateSend(arg1, -1, 0, 0, item_num, arg2, 0, 0, 0, 0, -1, 0, 0);
		LogAddTD("[피의 두루마리 Mix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",	gObj[arg1].AccountID, gObj[arg1].Name, iMIX_SUCCESS_RATE, gObj[arg1].Money, iMIX_NEED_MONEY, arg3);
	}
	else
	{
		ChaosBoxInit(&gObj[arg1]);
		GCUserChaosBoxSend(&gObj[arg1], 0);
		DataSend(arg1, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[피의 두루마리 Mix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d", gObj[arg1].AccountID, gObj[arg1].Name, iMIX_SUCCESS_RATE, gObj[arg1].Money, iMIX_NEED_MONEY, arg3);
		return FALSE;
	}

	::gObjInventoryCommit(arg1);
	return TRUE;
}
	   
BOOL CIllusionTempleEvent::CheckChoasMixItem(int arg1)
{
	if( OBJMAX_RANGE(arg1) == FALSE )
	{
		return FALSE;
	}

	int loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc11
	{
		if ( gObj[arg1].pChaosBox[n].IsItem() == TRUE )
		{
			if( gObj[arg1].pChaosBox[n].m_Type == ITEMGET(12,15))
			{
				loc3 = 1;
			}
			else if( gObj[arg1].pChaosBox[n].m_Type == ITEMGET(13,49))
			{
				int loc12 = gObj[arg1].pChaosBox[n].m_Level;
				loc7++;
				loc4 = 1; //IsItem??
				loc8 = loc12;
			}
			else if( gObj[arg1].pChaosBox[n].m_Type == ITEMGET(13,50))
			{
				int loc13 = gObj[arg1].pChaosBox[n].m_Level;
				loc7++;
				loc5 = 1; //IsItem??
				loc9 = loc13;
			}
			else if( gObj[arg1].pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				loc10+= gObj[arg1].pChaosBox[n].m_Durability;
			}
			else
			{
				loc6 = 1; //invalid
			}
		}
	}

	if(loc6 != 0)
	{
		return 8;
	}

	if(loc4 == 0 && loc5 == 0)
	{
		return FALSE;
	}

	if(loc4 == 0 || loc5 == 0)
	{
		return 11;
	}

	if(loc7 > 2)
	{
		return 12;
	}

	if(loc8 != loc9)
	{
		return 9;
	}

	if(IT_TICKET_RANGE(loc8-1) == FALSE)
	{
		return 9;
	}

	if(IT_TICKET_RANGE(loc9-1) == FALSE)
	{
		return 9;
	}

	if(loc3 == 0)
	{
		return 10;
	}

	if(gObj[arg1].Level < 10)
	{
		return 14;
	}

	if(loc3 != 0 && loc4 != 0 && loc5 != 0)
	{
		return loc8;
	}

	return FALSE;
}

BYTE CIllusionTempleEvent::SetKillCount(int aIndex, BYTE btMapNumber, BYTE btObjType)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return FALSE;
	}

	if( CHECK_LIMIT( (btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return FALSE;
	}

	BYTE loc2 = 0;

	if(btObjType == 1)
	{
		this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].IncreaseUserKillCount(aIndex);
		loc2 = 5;
	}
	else
	{
		this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].IncreaseMonsterKillCount(aIndex);
		loc2 = 2;
	}

	return this->m_IllusionTempleProcess[btMapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].AddKillPointToUser(aIndex, loc2);
}

BYTE CIllusionTempleEvent::RemoveKillPointFromUser(int aIndex, BYTE MapNumber, BYTE KillPoint) //Unused
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return FALSE;
	}

	if( CHECK_LIMIT( (MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN), MAX_FLOOR_DATA+1) == FALSE )
	{
		return FALSE;
	}

	return this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].RemoveKillPointFromUser(aIndex, KillPoint);
}

void CIllusionTempleEvent::RunningSkill(int aIndex, WORD skill, int aTargetIndex, BYTE dis)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return;
	}

	if(IT_MAP_RANGE(gObj[aIndex].MapNumber) == FALSE)
	{
		return;
	}

	this->m_IllusionTempleProcess[gObj[aIndex].MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].RunningSkill(aIndex, skill, aTargetIndex, dis);
}

void CIllusionTempleEvent::SkillProc(LPOBJ lpObj)
{
	this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].SkillSecondProc(lpObj);
}

void CIllusionTempleEvent::ResetAndClearSkills(LPOBJ lpObj)
{
	this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].ResetAndClearSkills(lpObj);
}

void CIllusionTempleEvent::DeathSetShield(LPOBJ lpObj)
{
	if( OBJMAX_RANGE(lpObj->m_Index) == FALSE )
	{
		return;
	}

	if(IT_MAP_RANGE(lpObj->MapNumber) == FALSE || this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() != 2)
	{
		return;
	}

	this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].ShieldSpell(lpObj);
}

void CIllusionTempleEvent::IncUsedKillCount(int aIndex, BYTE MapNumber) //Unused
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return;
	}

	if( IT_MAP_RANGE(MapNumber) == FALSE || this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() != 2)
	{
		return;
	}

	this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].IncreaseUsedKillCount(aIndex);
}

void CIllusionTempleEvent::SetEntranceNpcIndex(int aIndex)
{
	this->m_iEntranceNpcIndex = aIndex;
}

void CIllusionTempleEvent::NotifyTempleEntranceInfo()
{
	if(this->m_IllusionTempleProcess[1].GetState() == 0)
	{
		if(this->m_IllusionTempleProcess[1].GetOpenStatus() == TRUE)
		{
			PMSG_MIRAGE_ENTRANCE_INFO pMsg;

			PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x03, sizeof(pMsg));
			pMsg.btIllusionState[0] = this->m_IllusionTempleProcess[0].GetEnteredUserCount();
			pMsg.btIllusionState[1] = this->m_IllusionTempleProcess[1].GetEnteredUserCount();
			pMsg.btIllusionState[2] = this->m_IllusionTempleProcess[2].GetEnteredUserCount();
			pMsg.btIllusionState[3] = this->m_IllusionTempleProcess[3].GetEnteredUserCount();
			pMsg.btIllusionState[4] = this->m_IllusionTempleProcess[4].GetEnteredUserCount();

			if(g_iUseMaxLevelIllusionTemple == 0)
			{
				pMsg.btIllusionState[5] = this->m_IllusionTempleProcess[5].GetEnteredUserCount();
			}
			else
			{
				pMsg.btIllusionState[5] = 0;
			}

			MsgSendV2(&gObj[this->m_iEntranceNpcIndex],(LPBYTE)&pMsg,pMsg.h.size);
		}
	}
}

BOOL CIllusionTempleEvent::CheckWearingMOPH(int iUserIndex)
{
	if (  gObjIsConnected(iUserIndex) == FALSE )
	{
		return FALSE;
	}

	if ( gObj[iUserIndex].pInventory[10].IsItem()  )
	{
		if ( gObj[iUserIndex].pInventory[10].m_Type == ITEMGET(13,10) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[10].m_Type == ITEMGET(13,39) ) 
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[10].m_Type == ITEMGET(13,40) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[10].m_Type == ITEMGET(13,41) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[10].m_Type == ITEMGET(13,68) ) //season4 add-on
		{
			return TRUE;
		}
	}

	if ( gObj[iUserIndex].pInventory[11].IsItem() )
	{
		if ( gObj[iUserIndex].pInventory[11].m_Type == ITEMGET(13,10) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[11].m_Type == ITEMGET(13,39) ) 
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[11].m_Type == ITEMGET(13,40) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[11].m_Type == ITEMGET(13,41) )
		{
			return TRUE;
		}

		if ( gObj[iUserIndex].pInventory[11].m_Type == ITEMGET(13,68) ) //season4 add-on
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CIllusionTempleEvent::CheckPolymorphItem(int iItemCode)
{
	int loc2 = 0;

	switch(iItemCode)
	{
		case ITEMGET(13,10):
		case ITEMGET(13,39):
		case ITEMGET(13,40):
		case ITEMGET(13,41):
		case ITEMGET(13,68): //season4 add-on
			loc2 = 1;
			break;
	}

	return loc2;
}

BOOL CIllusionTempleEvent::CheckTeleport(int aIndex)
{
	if (  gObjIsConnected(aIndex) == FALSE )
	{
		return FALSE;
	}

	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return FALSE;
	}

	if(IT_MAP_RANGE(gObj[aIndex].MapNumber) == FALSE || this->m_IllusionTempleProcess[gObj[aIndex].MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetState() != 2)
	{
		return FALSE;
	}

	if(aIndex == this->m_IllusionTempleProcess[gObj[aIndex].MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].GetBallPlayerIndex())
	{
		return TRUE;
	}

	return FALSE;
}

void CIllusionTempleEvent::SearchNDropMonsterItem(LPOBJ lpObj)
{
	if(IT_MAP_RANGE(lpObj->MapNumber) == FALSE)
	{
		return;
	}

	this->m_IllusionTempleProcess[lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].DropMonsterItem(lpObj);
}

void CIllusionTempleEvent::GiveItemReward(int arg1)
{
	if(IT_MAP_RANGE(gObj[arg1].MapNumber) == FALSE)
	{
		return;
	}

	this->m_IllusionTempleProcess[gObj[arg1].MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].DropRewardItem(arg1);
}

BYTE CIllusionTempleEvent::GetRemainTime()
{
	BYTE loc2 = 0;

	if(g_iIllusionTempleEvent != 0)
	{
		loc2 = this->m_IllusionTempleProcess[0].RemainTime();
	}
	else
	{
		loc2 = 0;
	}
	
	return loc2;
}

BOOL CIllusionTempleEvent::GetShieldSpellStatus(int aIndex, BYTE MapNumber)
{
	if(IT_MAP_RANGE(MapNumber) == FALSE)
	{
		return FALSE;
	}
	return this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].CheckShieldSpellTime(aIndex);
}

BOOL CIllusionTempleEvent::GetRestrictionSpellStatus(int aIndex, BYTE MapNumber)
{
	if(IT_MAP_RANGE(MapNumber) == FALSE)
	{
		return FALSE;
	}
	return this->m_IllusionTempleProcess[MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN].CheckRestrictionSpellTime(aIndex);
}

int CIllusionTempleEvent::GetEnterLevel(int aIndex)
{
	int loc2 = 0; //?? weird

	LPOBJ lpObj = &gObj[aIndex];

	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	if( lpObj->Level < 220 ) return 0;
	if( lpObj->Level < 271 ) return 1;
	if( lpObj->Level < 321 ) return 2;
	if( lpObj->Level < 351 ) return 3;
	if( lpObj->Level < 381 ) return 4;
	if( lpObj->Level < 400 ) return 5;
	if( lpObj->Level == 400 && lpObj->ChangeUP3rd == 0 ) return 5;
	if( lpObj->Level == 400 && lpObj->ChangeUP3rd != 0 ){ if( g_iUseMaxLevelIllusionTemple != 0 ){ return 6;}else{ return 5;}}

	return -1;
}

int CIllusionTempleEvent::CheckLuckyTalisman(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	LPOBJ lpObj = &gObj[aIndex];
	int loc3 = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc4
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				loc3+= lpObj->pChaosBox[n].m_Durability;
			}
		}
	}
	return loc3;
}

void CIllusionTempleEvent::EGReqIllusionTempleEnterCount(int iIndex)
{
	if (  gObjIsConnected(iIndex) == FALSE )
	{
		return;
	}

	PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x14;
	pMsg.h.size = sizeof(pMsg);
	memcpy(pMsg.AccountID, gObj[iIndex].AccountID, 10);
	memcpy(pMsg.GameID, gObj[iIndex].Name, 10);
	pMsg.ServerCode = Configs.gGameServerCode / 20;
	pMsg.iObjIndex = iIndex;

	DataSendRank((char*)&pMsg, pMsg.h.size); //season4 changed
}

void CIllusionTempleEvent::EGAnsIllusionTempleEnterCount(PMSG_ANS_ILLUSIONTEMPLE_ENTERCOUNT* lpMsg) //???Send statistics to main.exe on Key T???
{
	if ( !lpMsg)
		return;

	if ( !gObjIsConnected(lpMsg->iObjIndex))
		return;

	char szAccountID[11] = {0};
	char szName[11] = {0};
	memcpy(szAccountID, lpMsg->AccountID, 10);
	memcpy(szName, lpMsg->GameID, 10);

	if ( strcmp(gObj[lpMsg->iObjIndex].AccountID, szAccountID) || strcmp(gObj[lpMsg->iObjIndex].Name, szName) )
		 return;

	PMSG_ANS_CL_ENTERCOUNT pMsgSend;

	pMsgSend.h.c = 0xC1;
	pMsgSend.h.headcode = 0x9F;
	pMsgSend.h.size = sizeof(pMsgSend);
	pMsgSend.btEventType = 3;
	pMsgSend.btLeftEnterCount = lpMsg->iLeftCount;

	DataSend(lpMsg->iObjIndex, (LPBYTE)&pMsgSend, sizeof(pMsgSend));
}