#include "StdAfx.h"
#include "NpcTalk.h"

BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	int npcnum = lpNpc->Class;

	if ( npcnum < 0 )
	{
		return FALSE;
	}

	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	if ( npcnum == 229 ) // Marlon
	{
		gQeustNpcTeleport.TalkRefAdd();
		lpObj->TargetShopNumber = npcnum;
	}

	if (npcnum == 258 && NpcCouponEvent(lpNpc, lpObj))
	{
		return TRUE;
	}

	if ( NpcQuestCheck(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

	switch ( npcnum )
	{ 
		case 367:
			if ( NpcMainatenceMachine ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 259:
			if ( NpcReira ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 254:
			if ( NpcFasi ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 241:
			if ( NpcGuildMasterTalk( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		
		case 239:
			if ( NpcBattleAnnouncer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 249:
			if ( NpcRolensiaGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 238:
			if ( NpcChaosGoblelin( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 237:
			if ( NpcRusipher( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 253:
			if ( NpcPosionGirl( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		
		case 245:
			if ( NpcDeviasWizard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 247:
			if ( NpcDeviasGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 240:
			if ( NpcWarehouse( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 226:
			if ( NpcDarkSpiritTrainer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 242:
			if ( NpcNoriaRara( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 244:
			if ( NpcDeviasMadam( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 236:
			if ( NpcEventChipNPC( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 234:
			if ( NpcServerDivision( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 232:
			if ( NpcAngelKing( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 233:
			if ( NpcAngelMessanger( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 255:
			if ( NpcRolensiaMadam( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 250:
			if ( NpcRoadMerchant( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 246:
			if ( NpcDeviasWeapon( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 251:
			if ( NpcRorensiaSmith( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 243:
			if ( NpcNoriJangIn( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 256:
			if ( NpcJewelMixDealer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 221:
			if ( NpcSiegeMachine_Attack( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 222:
			if ( NpcSiegeMachine_Defense( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 223:
			if ( NpcElderCircle( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 224:
			if ( NpcCastleGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 219:
			if ( NpcCastleGateLever( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 216:
			if ( NpcCastleCrown( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 217:
		case 218:
			if ( NpcCastleSwitch( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 257:
			if ( NpcShadowPhantom( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 368:
		case 369:
		case 370:
			if ( g_kJewelOfHarmonySystem.NpcJewelOfHarmony( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 371:
			if (NpcWhiteAngelEvent(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 375:
			if ( NpcChaosCardMaster( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 376:
			if (NpcPamelaSupplier(lpNpc, lpObj) == TRUE) //376 1 "Pamela the Supplier"
			{
				return TRUE;
			}
			break;
		case 377:
			if (NpcAngelaSupplier(lpNpc, lpObj) == TRUE) //377 1 "Angela the Supplier"
			{
				return TRUE;
			}
			break;
		case 379:
			if (NpcFireworkGirl(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 385:
			if (NpcIllusionMirage(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 380:
			if (NpcIllusionStatue(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 383:
			if (NpcIllusionYellowPedestal(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 384:
			if (NpcIllusionBluePedestal(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 414:
			if (NpcThansgivingEvent(lpNpc, lpObj) == TRUE)
			{
				return TRUE;
			}
			break;


		default: break;		
	}

	return FALSE;
} 
BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj)
{
	g_KanturuEntranceNPC.NotifyEntranceInfo(lpObj->m_Index);
	return TRUE;
}


BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj)
{ 

	return 0;
}


BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gLanguage != 0)
	{
		if (Configs.gDevilSquareEvent != FALSE)
		{
			GCServerCmd(lpObj->m_Index, 1, 6, 0);
		}
	}

	if ( lpObj->m_PK_Level > 4 )
	{
		int hour = 0;
		int min = 0;

		if ( lpNpc->TargetNumber != lpObj->m_Index )
		{
			if ( gObjGetPkTime(lpObj, hour, min) == TRUE )
			{
				char szTemp[100];

				wsprintf(szTemp, lMsg.Get(MSGGET(4, 79)), hour, min);

				ChatTargetSend(lpNpc, szTemp, lpObj->m_Index);

				lpNpc->TargetNumber = lpObj->m_Index;

				/*if ( gPkLimitFree == FALSE )
				{
					return TRUE;
				}*/
			}
		}
		else if (Configs.gPkLimitFree == FALSE)
		{
			int numbertext = rand() % 3;

			switch ( numbertext )
			{
				case 0:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 98)), lpObj->m_Index);
					break;

				case 1:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 99)), lpObj->m_Index);
					break;

				case 2:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 100)), lpObj->m_Index);
					break;
			}

			lpNpc->TargetNumber = -1;	// Apply Deathway Fix, change 0 to -1;
			return TRUE;
		}
	}

	return FALSE;
}




BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gGuildCreate == FALSE)
	{
		ChatTargetSend(lpNpc, "서버분할 기간에는 길드를 생성할수가 없습니다", lpObj->m_Index);
		return TRUE;
	}

	if ( lpObj->GuildNumber > 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 116)), lpObj->m_Index);
		return TRUE;
	}

	int capacity = gObjGuildMasterCapacityTest(lpObj);

	if ( capacity == 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 117)), lpObj->m_Index);
	}
	else if ( capacity == 2 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 118)), lpObj->m_Index);
	}
	else
	{
		GCGuildMasterQuestionSend(lpObj->m_Index);
	}

	return TRUE;
}




BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gLanguage != 0)
	{
	
	}
	else if (Configs.gEnableEventNPCTalk != FALSE)
	{
		GCServerCmd(lpObj->m_Index, 4, 0, 0);
	}

	return TRUE;
}





BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj)
{
	gUserFindDevilSquareKeyEyes(lpObj->m_Index);

	return FALSE;
}



BOOL g_bUseLotterySystem = TRUE;


BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_bUseLotterySystem == FALSE )
		return FALSE;

	if (Configs.bCanChaosBox == TRUE)
	{
		if ( lpObj->m_IfState.use > 0 )
			return FALSE;

		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
				lpObj->AccountID, lpObj->Name);

			GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x15;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 7;

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start",
			lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}




BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gDevilSquareEvent == FALSE)
	{
		return TRUE;
	}


	int aIndex = lpObj->m_Index;

	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	if ( gUserFindDevilSquareInvitation(aIndex) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 2 ,0);
	}
	else if ( g_DevilSquare.GetState() == 1 )
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x04;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 12;
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 3, 0);
	}

	return TRUE;
}




BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcFireworkGirl(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}



BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}



BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return TRUE;
}



BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}


BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}



BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gLanguage != 0)
	{
	
	}
	else if (Configs.gEnableEventNPCTalk != FALSE)
	{
		GCServerCmd(lpObj->m_Index, 4, 2, 0);
	}

	return FALSE;
}


BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gLanguage != 0)
	{
	
	}
	else if (Configs.gEnableEventNPCTalk != FALSE)
	{
		GCServerCmd(lpObj->m_Index, 4, 1, 0);
	}

	return FALSE;
}


struct PMSG_REQ_VIEW_EC_MN
{
	PBMSG_HEAD h;	// C1:01
	int iINDEX;	// 4
	char szUID[11];	// 8
};


BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}
	
	if ( lpNpc->MapNumber == 0 )
	{
		PMSG_REQ_VIEW_EC_MN pMsgTha;

		PHeadSetB((LPBYTE)&pMsgTha, 0x01, sizeof(pMsgTha));
		pMsgTha.iINDEX = lpObj->m_Index;
		strcpy(pMsgTha.szUID, lpObj->AccountID);
		pEventObj = lpNpc;

		DataSendEventChip((char*)&pMsgTha, sizeof(pMsgTha));
		
		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}


	if (lpNpc->MapNumber == 3)
	{
		PMSG_REQ_VIEW_EC_MN pMsgTha;

		PHeadSetB((LPBYTE)&pMsgTha, 0x05, sizeof(pMsgTha));
		pMsgTha.iINDEX = lpObj->m_Index;
		strcpy(pMsgTha.szUID, lpObj->AccountID);
		pEventObj = lpNpc;

		DataSendEventChip((char*)&pMsgTha, sizeof(pMsgTha));

		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	/*if (lpNpc->MapNumber == 3)
	{
		PMSG_EVENTCHIPINFO Result;

		PHeadSetB((LPBYTE)&Result, 0x94, sizeof(Result));
		Result.Type = 1;

		DataSend(lpObj->m_Index, (LPBYTE)&Result, Result.h.size);

		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}*/


	if ( lpNpc->MapNumber == 2 )
	{
		PMSG_EVENTCHIPINFO Result;

		PHeadSetB((LPBYTE)&Result, 0x94, sizeof(Result));
		Result.Type = 2;
		
		DataSend(lpObj->m_Index, (LPBYTE)&Result, Result.h.size);

		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	return FALSE;
}



BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}




BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_QuestInfo.NpcTalk(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

	return FALSE;
}




BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.gEnableServerDivision == FALSE)
	{
		return TRUE;
	}

	if ( lpObj->lpGuild != NULL )
	{
		GCServerCmd(lpObj->m_Index, 6, 0, 0);
		return TRUE;
	}

	lpObj->m_IfState.type = 11;
	lpObj->m_IfState.state = 0;
	lpObj->m_IfState.use = 1;

	return FALSE;
}



BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj)
{
	int iITEM_LEVEL = 0;

	if ( (  (lpObj->m_cBloodCastleIndex < 0)?FALSE:(lpObj->m_cBloodCastleIndex > MAX_BLOOD_CASTLE_LEVEL-1)?FALSE:TRUE ) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

	LogAddTD("[Blood Castle] (%d) [%s][%s] Talk to Angel King",
		lpObj->m_cBloodCastleIndex+1, lpObj->AccountID, lpObj->Name);

	if ( g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_bBC_REWARDED != false )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if ( g_BloodCastle.GetCurrentState(lpObj->m_cBloodCastleIndex) != 2 || g_BloodCastle.CheckPlayStart(lpObj->m_cBloodCastleIndex) == false)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

	if ( lpObj->m_bBloodCastleComplete == true)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if ( iITEM_LEVEL = iITEM_LEVEL = CHECK_LIMIT( g_BloodCastle.CheckQuestItem(lpObj->m_Index), 3)  )
	{
		if ( lpNpc->m_cBloodCastleIndex != lpObj->m_cBloodCastleIndex )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		if ( g_BloodCastle.CheckUserBridgeMember(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == false )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		g_BloodCastle.SetUserState(lpObj->m_Index, 2);
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Party = lpObj->PartyNumber;
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Index = lpObj->m_Index;
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName, lpObj->Name, 10);
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID, lpObj->AccountID, 10);
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName[10] = 0;	// Zero String terminated
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID[10] = 0;	// Zero String Terminated
		
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Castle Door [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID,
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_CharName);
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Saint Status [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID,	// #error Correct this
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Status_CharName);
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Win Quest [%s][%s]",
			lpObj->m_cBloodCastleIndex+1, g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID,
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName);

		if ( g_BloodCastle.SetBridgeWinner(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);

				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
		}
		else
		{
			LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Winner Already Exist !!",
				lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);

			return FALSE;
		}

		g_BloodCastle.SearchUserDeleteQuestItem(lpObj->m_Index);
	}
	else
	{
		if ( g_BloodCastle.CheckUserWinnerParty(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);

				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register",
					lpNpc->MapNumber-10, lpObj->AccountID, lpObj->Name);
			}

			return FALSE;
		}

		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
	}
	
	return FALSE;
}



BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	int iIndex = lpObj->m_Index;

	if ( gObj[iIndex].m_PK_Level >= 4 )
	{
		GCServerCmd(iIndex, 0x39, 0, 0);
		return TRUE;
	}

	int iITEM_LEVEL = 0;

	iITEM_LEVEL = g_BloodCastle.CheckEnterItem(lpObj->m_Index);

	if ( iITEM_LEVEL != 0 )
	{
		if ( iITEM_LEVEL != 10 && g_BloodCastle.CheckEnterLevel(lpObj->m_Index, iITEM_LEVEL-1) )
		{
			if ( g_BloodCastle.CheckEnterFreeTicket(lpObj->m_Index) == true )
			{
				iITEM_LEVEL = 10;
			}
		}

		if ( iITEM_LEVEL == 10 )
		{
			for (int i=0;i<MAX_CLOACK_LEVEL;i++)
			{
				if ( g_BloodCastle.CheckEnterLevel(lpObj->m_Index, i) == FALSE )
				{
					iITEM_LEVEL = i;
				}
			}
		}

		if ( g_BloodCastle.GetCurrentState(iITEM_LEVEL-1) == BC_STATE_CLOSED && g_BloodCastle.CheckCanEnter(iITEM_LEVEL-1) != false )
		{
			PMSG_TALKRESULT pMsg;

			pMsg.h.c = 0xC3;
			pMsg.h.headcode = 0x30;
			pMsg.h.size = sizeof(pMsg);
			pMsg.result = 0x06;

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			lpObj->m_IfState.use = 1;
			lpObj->m_IfState.type = 12;
		}
		else
		{
			GCServerCmd(lpObj->m_Index, 1, 0x14, 0);
		}
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 0x15, 0);
	}

	return FALSE;
}




BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}





BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}




BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.bCanChaosBox == TRUE)
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		
		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed",
				lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4, 194)), lpObj->m_Index, 1);

			return TRUE;
		}

		lpObj->m_IfState.type = 13;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;
		
		pMsg.result = 0x07;
		lpObj->bIsChaosMixCompleted = false;
		pMsg.level1 = Configs.gDQChaosSuccessRateLevel1;
		pMsg.level2 = Configs.gDQChaosSuccessRateLevel2;
		pMsg.level3 = Configs.gDQChaosSuccessRateLevel3;
		pMsg.level4 = Configs.gDQChaosSuccessRateLevel4;
		pMsg.level5 = Configs.gDQChaosSuccessRateLevel5;
		pMsg.level6 = Configs.gDQChaosSuccessRateLevel6;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		GCAnsCsMapSvrTaxInfo(lpObj->m_Index, 1, g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index));
		gObjInventoryTrans(lpObj->m_Index);

		LogAddTD("[%s][%s] Open Chaos Box", lpObj->AccountID, lpObj->Name);
		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}





BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (Configs.bCanChaosBox == TRUE)
	{
		if ( (lpObj->m_IfState.use) > 0 )
		{
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x09;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 12;

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);

	}

	return TRUE;
}



struct PMSG_ANS_USE_WEAPON_INTERFACE
{
	PBMSG_HEAD2 h;	// C1:B7:00
	BYTE btResult;	// 4
	BYTE btWeaponType;	// 5
	BYTE btObjIndexH;	// 6
	BYTE btObjIndexL;	// 7
};


BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 1;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 15;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}



BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 2;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 16;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}




BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj) //GS-CS Decompiled 100%
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}
	 
	if(g_CastleSiege.GetCastleState() == 7) //Good
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 85))), lpObj->m_Index);
		return TRUE;
	}

	 //0001:001d2150       _strcmp                    005d3150 f   libcmt:strcmp.obj

	if(strcmp(lpObj->GuildName, "") == 0 ) //Good
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 86))), lpObj->m_Index);
		return TRUE;
	}

	if(g_CastleSiege.CheckGuildOwnCastle(lpObj->GuildName)) //Good
	{
		if( lpObj->GuildStatus != 128 )
		{
			if ( lpObj->GuildStatus != 64 )
			{
				ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 86))), lpObj->m_Index);
				return TRUE;
			}
		}
	} 

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0C;

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;
	 
	pMsg.level1 = 0;
	pMsg.level2 = 0;
	pMsg.level3 = 0;
	pMsg.level4 = 0;
	pMsg.level5 = 0;
	pMsg.level6 = 0;

	if (Configs.bCanChaosBox == TRUE) //Good
	{
		lpObj->m_IfState.type = 7;

		lpObj->bIsChaosMixCompleted = false;
		lpObj->m_bCsGuildInvolved = false; //Good

		pMsg.level1 = 1; //Good

		GCAnsCsMapSvrTaxInfo(lpObj->m_Index, 1, g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index));
		gObjInventoryTrans(lpObj->m_Index);

		LogAddTD("[%s][%s] Open Chaos Box", lpObj->AccountID, lpObj->Name);
		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	} 

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	return TRUE;
}





BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj) //GS-CS Decompiled 100%
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}
	 
	if(g_CastleSiege.GetCastleState() == 7)
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 87))), lpObj->m_Index);
		return TRUE;
	} 

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0D;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;


	return TRUE;
}




BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj) //GS-CS Decompiled 100%
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}
	 
	BOOL bControlEnable = 0;
	BYTE btResult = 0;
	int iGateIndex = -1;

	if(g_CastleSiege.GetCastleState() == 7)
	{
		if(lpObj->m_btCsJoinSide != TRUE)
		{
			btResult = 4;
			bControlEnable = FALSE;
		}
		else
		{
			bControlEnable = TRUE;
		}
	}
	else
	{
		if(!g_CastleSiege.CheckCastleOwnerMember(lpObj->m_Index))
		{
			if(!g_CastleSiege.CheckCastleOwnerUnionMember(lpObj->m_Index))
			{
				btResult = 4;
				bControlEnable = FALSE;
			}
			else
			{
				bControlEnable = TRUE;
			}
		}
	}

	if(bControlEnable != FALSE)
	{
		if(g_CastleSiege.CheckLeverAlive(lpNpc->m_Index) == TRUE)
		{
			if(g_CastleSiege.CheckCsGateAlive(lpNpc->m_iCsGateLeverLinkIndex) == TRUE)
			{
				btResult = 1;
				iGateIndex = lpNpc->m_iCsGateLeverLinkIndex;
			}
			else
			{
				btResult = 2;
			}
		}
	}
	else
	{
		btResult = 3;
	}

	GCAnsCsGateState(lpObj->m_Index,btResult,iGateIndex);

	if(btResult != 1)
	{
		return TRUE;
	}

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;
	 

	return TRUE;
}





BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj) //GS-CS Decompiled 100%
{ 
	if ( gObjIsConnected(lpObj->m_Index) == FALSE ) //Good
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() != 7) //Good
	{
		return TRUE;
	}
	
	if(lpObj->m_btCsJoinSide < 2 || lpObj->m_bCsGuildInvolved == FALSE )
	{
		return TRUE;
	}

	if(g_CastleSiege.CheckUnionGuildMaster(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if((lpObj->Y - lpNpc->Y) > 3 || (lpObj->X - lpNpc->X) > 3)
	{
		return TRUE;
	}

	if(g_CastleSiege.GetRegCrownAvailable() == FALSE )
	{
		return TRUE;
	}

	int iUserIndex = g_CastleSiege.GetCrownUserIndex();

	if(gObjIsConnected(iUserIndex) == FALSE )
	{
		int iSwitchIndex1 = g_CastleSiege.GetCrownSwitchUserIndex(217);
		int iSwitchIndex2 = g_CastleSiege.GetCrownSwitchUserIndex(218);

		if(gObjIsConnected(iSwitchIndex1) == FALSE || gObjIsConnected(iSwitchIndex2) == FALSE )
		{
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName);
			return TRUE;
		}

		if(lpObj->m_btCsJoinSide != gObj[iSwitchIndex1].m_btCsJoinSide || lpObj->m_btCsJoinSide != gObj[iSwitchIndex2].m_btCsJoinSide)
		{
			GCAnsCsAccessCrownState(lpObj->m_Index,4);
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s) (S1:%s/%s)(S2:%s/%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName,gObj[iSwitchIndex1].Name,gObj[iSwitchIndex1].GuildName,gObj[iSwitchIndex2].Name,gObj[iSwitchIndex2].GuildName);
			return TRUE;
		}
		else
		{
			GCAnsCsAccessCrownState(lpObj->m_Index,0);
			//g_CastleSiege.SetCrownUserIndex(lpObj->m_Index);
			g_CastleSiege.SetCrownAccessUserX(lpObj->X);
			g_CastleSiege.SetCrownAccessUserY(lpObj->Y);
			//g_CastleSiege.SetCrownAccessTickCount();
			g_CastleSiege.NotifyAllUserCsProgState(0,lpObj->GuildName);
			LogAddTD("[CastleSiege] [%s][%s] Start to Register Castle Crown (GUILD:%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName);
		}
	}
	else if(lpObj->m_Index != iUserIndex)
	{
		GCAnsCsAccessCrownState(lpObj->m_Index,3);
	}

	return TRUE; 
}




BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj) //GS-CS Decompiled 100%
{ 
	if(gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() != 7)
	{
		return TRUE;
	}
	
	if(lpObj->m_btCsJoinSide < 2)
	{
		return TRUE;
	}

	if((lpObj->Y - lpNpc->Y) > 3 || (lpObj->X - lpNpc->X) > 3)
	{
		return TRUE;
	}

	if(g_CastleSiege.CheckGuardianStatueExist())
	{
		MsgOutput(lpObj->m_Index,lMsg.Get(MSGGET(6, 200)));
		return TRUE;
	}

	int iUserIndex = g_CastleSiege.GetCrownSwitchUserIndex(lpNpc->Class);

	if(!gObjIsConnected(iUserIndex))
	{
		GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,-1,1);
		g_CastleSiege.SetCrownSwitchUserIndex(lpNpc->Class,lpObj->m_Index);
		LogAddTD("[CastleSiege] [%s][%s] Start to Push Castle Crown Switch (GUILD:%s) - CS X:%d/Y:%d",lpObj->AccountID,lpObj->Name,lpObj->GuildName,lpNpc->X,lpNpc->Y);
	}
	else if(lpObj->m_Index != iUserIndex)
	{
		GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,iUserIndex,2);
	}

	return TRUE; 
}



BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if (lpObj->Level > Configs.g_iShadowPhantomMaxLevel)
	{
		GCServerCmd(lpObj->m_Index, 0x0D, 0, 0);
		
		return TRUE;
	}

	
	lpObj->m_iSkillNPCHelpTime = GetTickCount();
	lpObj->m_iSkillNPCDefense = lpObj->Level / 5 + 50;	// FORMULA
	lpObj->m_iSkillNPCAttack = lpObj->Level / 3 + 45;	// FORMULA
								  
	lpObj->m_ViewSkillState |= 0x2000000;

	GCStateInfoSend(lpObj, 1, 0x2000000);	 

	return TRUE;
}

BOOL NpcPamelaSupplier(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL NpcAngelaSupplier(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}
	return FALSE;
}

//Illusion Maybe Comes Now

BOOL NpcIllusionStatue(LPOBJ lpNpc, LPOBJ lpObj) //identical gs-cs 56
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcStatueUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionYellowPedestal(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcAlliedUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionBluePedestal(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcRelicsUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionMirage(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcMirageUser(lpNpc, lpObj);

	return TRUE;
}


BOOL NpcCouponEvent(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ((lpObj->m_IfState.use) > 0)
	{
		return TRUE;
	}

	EGReqPossiblePCBangCouponEvent(lpObj->m_Index);
	return TRUE;
}

BOOL NpcWhiteAngelEvent(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ((lpObj->m_IfState.use) > 0)
	{
		return TRUE;
	}

	GEReqCheckWhiteAngelGetItem(lpObj->m_Index);
	
	return TRUE;
}


BOOL NpcThansgivingEvent(LPOBJ lpNpc, LPOBJ lpObj)
{

	if (gObjIsConnected(lpObj->m_Index) == FALSE)
	{
		return TRUE;
	}

	if (lpObj->m_IfState.use != 0)
	{
		return TRUE;
	}

	BYTE Buff[4] = { 0xC3, 0x04, 0x30, 0x19 };
	DataSend(lpObj->m_Index, Buff, Buff[1]);

	/*PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x19;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	*/
	return TRUE;

}
