#include "stdafx.h"

// GS-N 0.99.60T 0x0047C360 - Completed
//	GS-N	1.00.18	JPN	0x00493D40	-	Completed

int iJewelofChaos = ITEMGET(12, 15);
int iJewelofBless = ITEMGET(14, 13);
int iJewelofSoul = ITEMGET(14, 14);
int iJewelofCreation = ITEMGET(14, 22);
int iBundleofBless = ITEMGET(12, 30);
int iBundleofSoul = ITEMGET(12, 31);
int iCondorFeather = ITEMGET(13, 53);
int iCondorFlame = ITEMGET(13, 52);
int iWingofStorm = ITEMGET(12, 36);
int iWingofEternal = ITEMGET(12, 37);
int iWingofIllusion = ITEMGET(12, 38);
int iWingofRuin = ITEMGET(12, 39);
int iCapeofLord = ITEMGET(12, 40);
int iWingofDimension = ITEMGET(12, 43);
int i3rdWingLuckRate = 50;



BOOL ChaosBoxCheck(LPOBJ lpObj)
{
	if ( lpObj->pChaosBox == NULL )
	{
		return false;
	}

	return true;
}

BOOL ChaosBoxInit(LPOBJ lpObj)
{
	int n;

	if ( lpObj->pChaosBox != NULL )
	{
		for (n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBox[n].Clear();
		}

		for (n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBoxMap[n] = -1;
		}
		return true;
	}

	lpObj->pChaosBox = new CItem[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBox == NULL )
	{
		return false;
	}

	lpObj->pChaosBoxMap = new unsigned char[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBoxMap == NULL )
	{
		delete lpObj->pChaosBox;
		return false;
	}

	for (n=0;n<CHAOS_BOX_SIZE;n++)
	{
		lpObj->pChaosBoxMap[n] = -1;
	}

	return true;
}



BOOL ChaosBoxItemDown(LPOBJ lpObj)
{
	if ( lpObj->pChaosBox == NULL )
	{
		return FALSE;
	}

	for (int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,14))
		{
			lpObj->pChaosBox[n].Clear();
		}
		else
		{
			int op = lpObj->pChaosBox[n].m_Option1;

			if ( op > 0 )
			{
				if ( (rand() % 2) == 0 )
				{
					op--;
				}
			}

			lpObj->pChaosBox[n].m_Option1 = op;
			op = lpObj->pChaosBox[n].m_Option3;

			if ( op > 0 )
			{
				if ( (rand() % 2) == 0 )
				{
					op--;
				}
			}

			lpObj->pChaosBox[n].m_Option3 = op;

			if ( lpObj->pChaosBox[n].m_Level > 0 )
			{
				lpObj->pChaosBox[n].m_Level = rand() % lpObj->pChaosBox[n].m_Level;
			}

			float dur = ItemGetDurability(lpObj->pChaosBox[n].m_Type, lpObj->pChaosBox[n].m_Level, lpObj->pChaosBox[n].IsExtItem(), lpObj->pChaosBox[n].IsSetItem());
			
			lpObj->pChaosBox[n].m_Durability =  dur * lpObj->pChaosBox[n].m_Durability / lpObj->pChaosBox[n].m_BaseDurability;
			lpObj->pChaosBox[n].Convert(lpObj->pChaosBox[n].m_Type, lpObj->pChaosBox[n].m_Option1,
				lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, lpObj->pChaosBox[n].m_NewOption,
				lpObj->pChaosBox[n].m_SetOption, lpObj->pChaosBox[n].m_ItemOptionEx, CURRENT_DB_VERSION);
		}
	}

	return TRUE;
}



int ChaosBoxMix(LPOBJ lpObj, int & Result2)
{
	BYTE ExOption[8];
	int ChaosDiamond = 0;
	int ChaosItems = 0;

	if ( lpObj->pChaosBox == NULL )
	{
		return 0;
	}

	int value = 0;
	int add = 0;
	int nv = 0;	// NEW VALUE
	Result2 = 0;
	lpObj->ChaosSuccessRate = 0;
	lpObj->ChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			lpObj->pChaosBox[n].OldValue();
			add = 0;
			nv = 0;

			if ( lpObj->pChaosBox[n].m_Level >= MIN_CHAOS_ITEM_LEVEL && (lpObj->pChaosBox[n].m_Option3 *4) >= MIN_CHAOS_ITEM_LEVEL )
			{
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				add = 1;

				if ( lpObj->pChaosBox[n].m_Type == ITEMGET(2,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(4,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(5,7) )	// Chaos Items
				{
					Result2 = 1;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				ChaosDiamond++;
				add = 1;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )	// Jewel of Bless, Jewel of Soul
			{
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				add = 1;
			} 

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,14) ) // Loch Feather
			{
				return FALSE;
			}


			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}

			if ( add != 0  )
			{
				ChaosItems++;
			}

			ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);
			LogAdd("[%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%d][%d][%d] Ex:[%d,%d,%d,%d,%d,%d,%d]",
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(),
				lpObj->pChaosBox[n].m_Level, lpObj->pChaosBox[n].m_Option1,
				lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3,
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability,
				nv, ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5],
				ExOption[6], lpObj->pChaosBox[n].m_SetOption);
		



		}
	}

	if ( ChaosDiamond == 0 )
	{
		value = 0;	// 0% of success
	}

	if ( ChaosItems < 2 )
	{
		value = 0;// 0% of success
	}

	if ( iCharmOfLuckCount > 10 )
		return FALSE;


	
	lpObj->ChaosSuccessRate = value / 20000;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	if ( lpObj->ChaosSuccessRate  > 100 )
	{
		lpObj->ChaosSuccessRate = Configs.ChaosWeaponMixRate;
	}

	lpObj->ChaosMoney = lpObj->ChaosSuccessRate * Configs.ChaosWeaponMixCost;	// Required Money to MIX anc createe a Chaos Item

	LogAddTD("[%s][%s] CBMix need Zen : %d SuccessRate : %d, CharmRate : %d",
		lpObj->AccountID, lpObj->Name, lpObj->ChaosMoney, 
		lpObj->ChaosSuccessRate, iCharmOfLuckCount);
	return value;
}



struct CB_PMSG_REQ_PRESENT
{
	PBMSG_HEAD h;	// C1:01
	char AccountId[10];	// 3
	char GameId[10];	// D
	int Sequence;	// 18
};


void CBUPS_ItemRequest(int aIndex, char* AccountId, char* Name)
{
	LogAddTD("[DevilSquare] 이벤트 경품 요청 [%s][%s]", AccountId, Name);	// #warning Translation

	CB_PMSG_REQ_PRESENT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x01;
	pMsg.h.size = sizeof(pMsg);
	pMsg.Sequence = aIndex;
	memcpy(pMsg.AccountId, AccountId, sizeof(pMsg.AccountId));
	memcpy(pMsg.GameId, Name, sizeof(pMsg.GameId));

	gUdpSocCE.SendData((LPBYTE)&pMsg, pMsg.h.size);
}




void ChaosEventProtocolCore(BYTE protoNum, unsigned char* aRecv, int aLen)
{
	#ifdef TRACE_PROTOCOL
		LogAddHeadHex("CHAOS_EVENT", aRecv, aLen);
	#endif

	switch ( protoNum )
	{
		case 0x01:
			//CBUPR_ItemRequestRecv( (CB_PMSG_REQ_PRESENT_RESULT *)aRecv);
			break;
	}
}



struct PMSG_PRIZE_INFO
{
	PBMSG_HEAD h;
	char AccountID[10];	// 3
	char GameID[10];	// D
	int servernumber;	// 18
	char present;	// 1C
	int Seq_present;	// 20
};



void CBUPR_ItemRequestRecv( CB_PMSG_REQ_PRESENT_RESULT * lpMsg)
{
	LPOBJ lpObj;
	char szId[11];
	char szName[11];
	char szPresentName[51];
	int aIndex;
	PMSG_PRIZE_INFO pMsg;

	szId[10] = 0;
	szName[10] = 0;
	memset(szPresentName, 0, sizeof(szPresentName));
	memcpy(szId, lpMsg->AccountId, sizeof(lpMsg->AccountId));
	memcpy(szName, lpMsg->GameId, sizeof(lpMsg->GameId));
	memcpy(szPresentName, lpMsg->presentname, sizeof(lpMsg->presentname));
	aIndex = lpMsg->Sequence;

	if (gObjIsConnectedGP(aIndex) == FALSE )
	{
		LogAddC(2, "error-L3 [%s][%d]", __FILE__, __LINE__);
		return;
	}

	lpObj = &gObj[aIndex];

	if ( strcmp(szId, lpObj->AccountID) != 0 )
	{
		LogAddC(2, "error-L3 [%s][%d][%s == %s]", __FILE__, __LINE__, szId, lpObj->AccountID);
		return;
	}

	if ( strcmp(szName, lpObj->Name) != 0 )
	{
		LogAddC(2, "error-L3 [%s][%d]", __FILE__, __LINE__);
		return;
	}

	if ( lpMsg->present != -1 )
	{
		char szTemp[256]="";

		wsprintf(szTemp, lMsg.Get(MSGGET(6, 65)), szName, szPresentName);
		AllSendServerMsg(szTemp);

		pMsg.h.c = 0xC1;
		pMsg.h.headcode = 0x02;
		pMsg.h.size = sizeof(pMsg);
		pMsg.present = lpMsg->present;
		pMsg.Seq_present = lpMsg->Seq_present;
		pMsg.servernumber = Configs.gGameServerCode;
		memcpy(pMsg.AccountID, lpMsg->AccountId, sizeof(pMsg.AccountID));
		memcpy(pMsg.GameID, lpMsg->GameId, sizeof(pMsg.GameID));

		gUdpSocCE.SendData((LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DevilSquare] Present Prize Notice %d(%s) %d %s %s",
			lpMsg->present, szPresentName, lpMsg->Seq_present, szId, szName);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, 0x1FF, 0, 255, 0, 0, 0, -1, 0, 0);
		lpObj->Money -= 10000;
		GCMoneySend(lpObj->m_Index, lpObj->Money);

		PMSG_CHAOSMIXRESULT pMsg;

		PHeadSetB((LPBYTE)&pMsg, 0x86, sizeof(pMsg));
		pMsg.Result = 5;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
	else
	{
		int in = ITEMGET(14,19); // Devil Square Invitation
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, in, 0, 0, 0, 0, 0, -1, 0, 0);
		lpObj->Money -= 10000;
		GCMoneySend(lpObj->m_Index, lpObj->Money);
		lpObj->ChaosLock = FALSE;

		LogAddTD("[DevilSquare] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, lpObj->ChaosMoney);
	}
}






int  CheckDevilSquareItem(LPOBJ lpObj, int & eventitemcount, int & itemlevel)
{
	BOOL bChaoseGem = FALSE;
	BOOL bEyeOfDevil = FALSE;
	BOOL bKeyOfDevil = FALSE;
	eventitemcount = 0;
	BOOL FoundOtherItem = FALSE;
	int level = -1;
	BOOL bLevelCheck = FALSE;
	int iCharmOfLuckCount = 0;
	BOOL bCharmOfLuckOver = FALSE;

	LogAdd("[DevilSquare] Search DevilSquareItem");

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// Chaos
			{
				bChaoseGem = TRUE;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,17) )	// Eye
			{
				eventitemcount +=1;
				bEyeOfDevil = TRUE;

				if ( level != lpObj->pChaosBox[n].m_Level )
				{
					if ( level == -1 )
					{
						level = lpObj->pChaosBox[n].m_Level;
					}
					else
					{
						bLevelCheck = TRUE;
					}
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,18) )	// Key
			{
				eventitemcount +=1;
				bKeyOfDevil = TRUE;

				if ( level != lpObj->pChaosBox[n].m_Level )
				{
					if ( level == -1 )
					{
						level = lpObj->pChaosBox[n].m_Level;
					}
					else
					{
						bLevelCheck = TRUE;
					}
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;

				if ( iCharmOfLuckCount > 10 )
				{
					bCharmOfLuckOver = TRUE;
				}
			}
			else
			{
				FoundOtherItem = TRUE;
			}
		}
	}

	itemlevel = level;
	lpObj->ChaosSuccessRate = iCharmOfLuckCount;

	if ( FoundOtherItem != FALSE )
	{
		LogAdd("[DevilSquare] Other DQItems Found");
		return 0;
	}

	if ( bLevelCheck != FALSE )
	{
		LogAdd("[DevilSquare] DiffLevel DQItems Found");
		return 3;
	}

	if ( bCharmOfLuckOver == TRUE )
	{
		LogAdd("[DevilSquare] Charm Of Luck Count Over");
		return 4;
	}

	if ( bChaoseGem != FALSE && bEyeOfDevil != FALSE && bKeyOfDevil != FALSE )
	{
		LogDQChaosItem(lpObj);
		return 1;
	}

	if ( bEyeOfDevil != FALSE && bKeyOfDevil != FALSE )
	{
		LogDQChaosItem(lpObj);
		return 2;
	}

	LogAdd("[DevilSquare] DQItems Not Found");

	return 0;
}





void LogDQChaosItem(LPOBJ lpObj)
{
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n] );

			LogAddTD("[DevilSquare,%d] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%d][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380Ex[%d] HO:[%d,%d]",
				lpObj->pChaosBox[n].m_Level,
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6],
				lpObj->pChaosBox[n].m_SetOption, lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]),
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]));
		}
	}
}






BOOL DevilSquareEventChaosMix(LPOBJ lpObj, BOOL bCheckType, int iItemLevel)
{
	BOOL fail = TRUE;
	int aIndex = lpObj->m_Index;
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;

	LogAddTD("[DevilSquare] Chaos Mix Start");
	INT nChaosNeedMoney = 0;
	int iCharmOfLuckCount = 0;
	iCharmOfLuckCount = lpObj->ChaosSuccessRate;

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		lpObj->ChaosLock = FALSE;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	switch ( iItemLevel )
	{
		case 0:
			lpObj->ChaosSuccessRate = 60;
			nChaosNeedMoney = 100000;
			break;

		case 1:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel1;
			nChaosNeedMoney = 100000;
			break;

		case 2:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel2;
			nChaosNeedMoney = 200000;
			break;

		case 3:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel3;
			nChaosNeedMoney = 400000;
			break;

		case 4:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel4;
			nChaosNeedMoney = 700000;
			break;

		case 5:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel5;
			nChaosNeedMoney = 1100000;
			break;

		case 6:
			lpObj->ChaosSuccessRate = Configs.gDQChaosSuccessRateLevel6;
			nChaosNeedMoney = 1600000;
			break;

		default:
			LogAdd("[DevilSquare] [%s][%s] Invalid DQItem Level [%d]",
				lpObj->AccountID, lpObj->Name, iItemLevel);

			pMsg.Result = CB_INVALID_ITEM_LEVEL;
			DataSend(aIndex, (BYTE *)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			return 1;
			break;
	}

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( (lpObj->Money - nChaosNeedMoney) < 0 )
	{
		LogAddTD("[DevilSquare] [%s][%s] CBMix Not Enough Money [%d] need zen [%d]",
			lpObj->AccountID, lpObj->Name, lpObj->Money, nChaosNeedMoney);
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(aIndex, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return 1;

	}

	if ( g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit )
	{	
		lpObj->ChaosSuccessRate += g_CrywolfSync.GetPlusChaosRate();
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int iRate = rand() % 100;

	if ( bCheckType == TRUE )
	{
		if ( iRate < lpObj->ChaosSuccessRate )
		{
			int DevilInv = ITEMGET(14,19);	// Devil Ticket
			ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, DevilInv, iItemLevel, 0, 0, 0, 0, -1, 0, 0);
			fail = FALSE;
		}
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

#if (FOREIGN_GAMESERVER==1)
	if ( szAuthKey[17] != AUTHKEY17 )
	{
		::DestroyGIocp();
	}
#endif

	if ( fail == TRUE )
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		DataSend(aIndex, (BYTE *)&pMsg, pMsg.h.size);

		LogAddTD("[DevilSquare,%d] [%s][%s] CBMix Fail %d Money : %d-%d", iItemLevel,
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney);
		lpObj->ChaosLock = FALSE;
	}
	else
	{
		LogAddTD("[DevilSquare,%d] [%s][%s] CBMix Success Rate:%d Money : %d", iItemLevel,
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			nChaosNeedMoney);
	}

	::gObjInventoryCommit(lpObj->m_Index);

	return TRUE;
}




void LogPlusItemLevelChaosItem(LPOBJ lpObj, int iPlusMixLevel)
{
	int iMixLevel = 0;
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);

			if ( iPlusMixLevel == 3 )
				iMixLevel = 1;
			else if ( iPlusMixLevel == 4 )
				iMixLevel = 2;
			else if ( iPlusMixLevel == 22 )
				iMixLevel = 3;
			else if ( iPlusMixLevel == 23 )
				iMixLevel = 4;

			LogAddTD("[PlusItemLevel,%d] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%d][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380Ex:[%d] HO:[%d,%d]", iMixLevel,
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6], lpObj->pChaosBox[n].m_SetOption,
				lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]),	// #error Cahnge to GetItemStrengthenOption
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]));	// #error Cahnge to GetItemOptionLevel
		}
	}
}





void LogChaosItem(LPOBJ lpObj, LPSTR sLogType)
{
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);

			LogAddTD("[%s] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%d][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380:[%d] HO:[%d,%d]",
				sLogType, lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6], lpObj->pChaosBox[n].m_SetOption,
				lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]),
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]));
		}
	}
}






BOOL PlusItemLevelChaosMix(LPOBJ lpObj, int mixType)
{
	int ChaosGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int Plus9ItemCount = 0;
	int Plus10ItemCount = 0;
	int PlusItemPos = -1;
	int OtherItemFound = 0;
	int Plus11ItemCount = 0;
	int Plus12ItemCount = 0;
	int ExtraBlessGemCount = 0;
	int ExtraSoulGemCount = 0;
	int iCharmOfLuckCount = 0;
	BYTE btItemLuckValue = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChaosGemCount++;
			}
			else if (  lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if (  lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 9 )
			{
				Plus9ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 10 )
			{
				Plus10ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 11 )
			{
				Plus11ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 12 )
			{
				Plus12ItemCount++;
				PlusItemPos = n;
			}
			else
			{
				OtherItemFound ++;
			}
		}
	}

	if ( iCharmOfLuckCount > 10 )
	{
		PMSG_CHAOSMIXRESULT pResult;

		PHeadSetB((LPBYTE)&pResult, 0x86, sizeof(pResult));

		LogAddTD("[PlusItemLevel] [%s][%s] CBMix Charm of luck over 10% (%d)",
			lpObj->AccountID, lpObj->Name, iCharmOfLuckCount);

		pResult.Result = 0xF0;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->ChaosLock = FALSE;

		return 0;
	}



	if ( OtherItemFound != FALSE )
	{
		return FALSE;
	}

	lpObj->ChaosMoney = 0;
	int MixType = 0;

	if ( Plus9ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 1 && SoulGemCount == 1 && Plus10ItemCount == 0 && Plus11ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 3;
		lpObj->ChaosMoney = Configs.PlusLevel10_Cost;
		ExtraBlessGemCount = BlessGemCount - 1;
		ExtraSoulGemCount = SoulGemCount - 1;
	}
	else if ( Plus10ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 2 && SoulGemCount == 2 && Plus9ItemCount == 0 && Plus11ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 4;
		lpObj->ChaosMoney = Configs.PlusLevel11_Cost;
		ExtraBlessGemCount = BlessGemCount - 2;
		ExtraSoulGemCount = SoulGemCount - 2;
	}
	else if ( Plus11ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 3 && SoulGemCount == 3 && Plus9ItemCount == 0 && Plus10ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 22;
		lpObj->ChaosMoney = Configs.PlusLevel12_Cost;
		ExtraBlessGemCount = BlessGemCount - 3;
		ExtraSoulGemCount = SoulGemCount - 3;
	}
	else if ( Plus12ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 4 && SoulGemCount == 4 && Plus9ItemCount == 0 && Plus10ItemCount == 0 && Plus11ItemCount == 0 )
	{
		MixType = 23;
		lpObj->ChaosMoney = Configs.PlusLevel13_Cost;
		ExtraBlessGemCount = BlessGemCount - 4;
		ExtraSoulGemCount = SoulGemCount - 4;
	}

	if ( MixType != mixType )
	{
		MixType = 0;
	}

	if ( MixType == 0 )
	{
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;
	::LogPlusItemLevelChaosItem(lpObj, MixType);
	LogAddTD("[PlusItemLevel] Chaos Mix Start");

	int iChaosTaxMoney = (int)((__int64)lpObj->ChaosMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	lpObj->ChaosMoney += iChaosTaxMoney;

	if ( lpObj->ChaosMoney < 0 )
	{
		lpObj->ChaosMoney = 0;
	}

	if ( lpObj->Money < lpObj->ChaosMoney )
	{
		LogAddTD("[PlusItemLevel] [%s][%s] CBMix Not Enough Money [%d] need zen [%d]",
			lpObj->AccountID, lpObj->Name, lpObj->Money, lpObj->ChaosMoney);
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		
		return TRUE;
	}


	lpObj->Money -= lpObj->ChaosMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( lpObj->pChaosBox[PlusItemPos].m_Level == 9 )
	{
		lpObj->ChaosSuccessRate = Configs.PlusLevel10;
	}
	else if ( lpObj->pChaosBox[PlusItemPos].m_Level == 10 )
	{
		lpObj->ChaosSuccessRate = Configs.PlusLevel11;
	}
	else if ( lpObj->pChaosBox[PlusItemPos].m_Level == 11 )
	{
		lpObj->ChaosSuccessRate = Configs.PlusLevel12;
	}
	else if ( lpObj->pChaosBox[PlusItemPos].m_Level == 12 )
	{
		lpObj->ChaosSuccessRate = Configs.PlusLevel13;
	}

	if ( lpObj->pChaosBox[PlusItemPos].m_Option2 != FALSE )	// if Have Luck
	{
		lpObj->ChaosSuccessRate += Configs.AddLuckItems;
	}

	if ( lpObj->ChaosSuccessRate > 75 )
	{
		lpObj->ChaosSuccessRate = 75;
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	btItemLuckValue = lpObj->pChaosBox[PlusItemPos].m_Option2;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		lpObj->pChaosBox[PlusItemPos].m_Level++;
		pMsg.Result = CB_SUCCESS;

		CItem Item;

		float Dur = ItemGetDurability(lpObj->pChaosBox[PlusItemPos].m_Type, lpObj->pChaosBox[PlusItemPos].m_Level,
			lpObj->pChaosBox[PlusItemPos].IsExtItem(), lpObj->pChaosBox[PlusItemPos].IsSetItem());

		Item.m_Level = lpObj->pChaosBox[PlusItemPos].m_Level;
		Item.m_Durability = Dur * lpObj->pChaosBox[PlusItemPos].m_Durability / lpObj->pChaosBox[PlusItemPos].m_BaseDurability;
		Item.m_JewelOfHarmonyOption = lpObj->pChaosBox[PlusItemPos].m_JewelOfHarmonyOption;

		Item.Convert(lpObj->pChaosBox[PlusItemPos].m_Type, lpObj->pChaosBox[PlusItemPos].m_Option1, lpObj->pChaosBox[PlusItemPos].m_Option2,
			lpObj->pChaosBox[PlusItemPos].m_Option3, lpObj->pChaosBox[PlusItemPos].m_NewOption, 
			lpObj->pChaosBox[PlusItemPos].m_SetOption, lpObj->pChaosBox[PlusItemPos].m_ItemOptionEx, CURRENT_DB_VERSION);

		Item.m_Number = lpObj->pChaosBox[PlusItemPos].m_Number;

		ItemByteConvert(pMsg.ItemInfo, Item);
		ChaosBoxInit(lpObj);
		::gObjChaosBoxInsertItemPos(lpObj->m_Index, Item, 0, -1);
		gObjChaosItemSet(lpObj->m_Index, 0, 1);

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		if ( btItemLuckValue )
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Success %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate+5, lpObj->Money,
				lpObj->ChaosMoney, Item.m_Level, iCharmOfLuckCount);
		}
		else
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Success %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
				lpObj->ChaosMoney, Item.m_Level, iCharmOfLuckCount);
		}
	}
	else
	{
		int FailLevel = lpObj->pChaosBox[PlusItemPos].m_Level+1;
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		if ( btItemLuckValue )
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Fail %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate+5, lpObj->Money,
				lpObj->ChaosMoney, FailLevel, iCharmOfLuckCount);
		}
		else
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Fail %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
				lpObj->ChaosMoney, FailLevel, iCharmOfLuckCount);
		}
	}

	lpObj->ChaosLock = FALSE;
	return TRUE;
}






BOOL PegasiaChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int UniriaCount = 0;
	int ChoasGemCount = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,2) && lpObj->pChaosBox[n].m_Durability == 255.0f )	// Uniria
			{
				UniriaCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos Gem
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
		}
	}

	if ( UniriaCount != 10 || ChoasGemCount != 1 )
	{
		lpObj->ChaosLock = FALSE;
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		return 0;
	}

	int nChaosNeedMoney = Configs.DinorantMixCost;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	LogChaosItem(lpObj, "DinorantMix");
	LogAddTD("[DinorantMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.DinorantMixRate;	// Succes Rate for Dinorant
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money -= nChaosNeedMoney;

	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		int Dinorant = ITEMGET(13,3);
		int Option3 = 0;

		if ( (rand()% 100) < 30 )
		{
			Option3 = 1 <<  ((rand()%3)) ;

			if ( (rand()%5) == 0 )
			{
				Option3 |= 1 << (rand()%3);
			}
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Dinorant, 0, 255, 1, 0, Option3, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[DinorantMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		return TRUE;
	}
	else
	{
		ChaosBoxInit(lpObj);	// Errase Chaos Box
		GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		LogAddTD("[DinorantMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
		return FALSE;
	}
}






BOOL CircleChaosMix(LPOBJ lpObj)	// Fruits
{
	lpObj->ChaosLock = TRUE;

	int CreatureGemCount = 0;
	int ChoasGemCount = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )	// Jewel of Creation
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos Gem
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
		}
	}

	if ( CreatureGemCount != 1 || ChoasGemCount != 1 )
	{
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		return 1;
	}

	if ( lpObj->Level < 10 )
	{
		pMsg.Result = CB_LOW_LEVEL_USER;

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	int nChaosNeedMoney = Configs.FruitMixCost;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	LogChaosItem(lpObj, "CircleMix");
	LogAddTD("[CircleMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.FruitMixRate;	// Succes Rate for Fruit
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money -= nChaosNeedMoney;

	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		int Fruit = ITEMGET(13,15);	// Fruit
		int FruitType;
		int RandonValue = rand() % 100;

		if ( RandonValue < 30 )
		{
			FruitType = 0;
		}
		else if ( RandonValue < 55 )
		{
			FruitType = 1;
		}
		else if ( RandonValue < 75 )
		{
			FruitType = 2;
		}
		else if ( RandonValue < 95 )
		{
			FruitType = 3;
		}
		else
		{
			FruitType = 4;
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Fruit, FruitType, 255, 1, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[CircleMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		return TRUE;
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		LogAddTD("[CircleMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;

		return FALSE;
	}
}



BOOL WingChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int WingCount = 0;
	int ChoasGemCount = 0;
	int LokesFeathersCount = 0;
	int WingIndex = -1;
	int iChaosMoney = 0;
	int iWingChaosMoney = 0;
	int iSleeveOfLord = 0;
	int iCharmOfLuckCount = 0;
	int WingLvl2Count = 0;
	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( (lpObj->pChaosBox[n].m_Type >= ITEMGET(12,3) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,6)) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,30) )	
			{
				lpObj->ChaosLock = FALSE;

				return FALSE;
			}
			if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(12,0) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,2) || lpObj->pChaosBox[n].m_Type  >= ITEMGET(12,3) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,30))
			{
				WingCount++;
				WingIndex = n;
				iWingChaosMoney = lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,14) ) // Feather
			{
				if ( lpObj->pChaosBox[n].m_Level == 0 ) // Feather
				{
					LokesFeathersCount++;
				}
				else	// Crst of Monarch
				{
					iSleeveOfLord ++;
				}
			}

			else if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(12,3) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,30))
			{
				WingLvl2Count++; // if lvl2 wing is present
			}

			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].IsExtItem() != FALSE )
			{
				if ( lpObj->pChaosBox[n].m_Level >= 4 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
		}
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	

	if ( iSleeveOfLord == 1 )
	{
		if ( WingCount != 1 || ChoasGemCount != 1 || LokesFeathersCount != 0 )
		{
			lpObj->ChaosLock = FALSE;
			pMsg.Result = CB_INCORRECT_MIX_ITEMS;
			DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
			return FALSE;
		}
	}
	else if ( LokesFeathersCount == 1 )
	{
		if ( WingCount != 1 || ChoasGemCount != 1 || iSleeveOfLord != 0 )
		{
			pMsg.Result = CB_INCORRECT_MIX_ITEMS;
			DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;

			return FALSE;
		}
	}
	else
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		return FALSE;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}

	if ( WingLvl2Count = WingLvl2Count == 1)
	{
		if(WingLvl2Count != 1 || ChoasGemCount != 1)
		{
			pMsg.Result = CB_INCORRECT_MIX_ITEMS;
			DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			return FALSE;
		}
	}

	int nChaosNeedMoney = Configs.WingsLvl2MixCost;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	CItem * pWing = &lpObj->pChaosBox[WingIndex];
	lpObj->ChaosSuccessRate = (DWORD)((DWORD)iWingChaosMoney / (DWORD)4000000);
	lpObj->ChaosSuccessRate += iChaosMoney / 40000;

	if ( lpObj->ChaosSuccessRate == 0 )
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return FALSE;
	}

	LogChaosItem(lpObj, "WingMix,2");
	LogAddTD("[WingMix] Chaos Mix Start");

	if ( iSleeveOfLord == 1 )
	{
		if ( lpObj->ChaosSuccessRate > Configs.WingsLvl2MixRate)
		{
			lpObj->ChaosSuccessRate = Configs.WingsLvl2MixRate;
		}
	}
	else if ( LokesFeathersCount == 1 )
	{
		if ( lpObj->ChaosSuccessRate > Configs.WingsLvl2MixRate)
		{
			lpObj->ChaosSuccessRate = Configs.WingsLvl2MixRate;
		}
	}
	else if ( lpObj->ChaosSuccessRate > Configs.WingsLvl2MixRate)
	{
		lpObj->ChaosSuccessRate = Configs.WingsLvl2MixRate;
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money  -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int iWingLevel = 0;
		int iItemType;
		int iItemSubType;

		if ( iSleeveOfLord != 0 )
		{
			iItemType = 13;
			iItemSubType = 30;
		}
		else if (WingLvl2Count != 0)
		{
			iItemType = 12;
			iItemSubType = 36;
		}
		else
		{
			iItemType = 12;
			iItemSubType = rand()%4 + 3;
		}

		int iWingNum = ITEMGET(iItemType, iItemSubType);
		int iOption1 = 0;
		int iOption2 = 0;
		int iOption3 = 0;

		if ( (rand()%5) == 0 )
		{
			iOption1 = 1;
		}

		int iRandomValue = rand() % 100;
		int iRandomValue2 = rand() % 3;

		switch ( iRandomValue2 )
		{
			case 0:
				if ( iRandomValue < 4 )
				{
					iOption2 = 3;	// +12
				}
				break;

			case 1:
				if ( iRandomValue < 10 )
				{
					iOption2 = 2;	// +8
				}
				break;

			case 2:
				if ( iRandomValue < 20 )
				{
					iOption2 = 1;	// +4;
				}
		}

		//int ExOption;

		if ( iSleeveOfLord != FALSE )
		{
			if ( (rand()%5) == 0 )
			{
				iOption3 = 1 << (rand()%4);
			}
				iOption3 |= 0x20;
		}
		else
		{
			if ( (rand()%5) == 0 )
			{
				iOption3 = 1 << (rand()%3);
			}

			if ( (rand()%2) != 0 )
			{
				iOption3 |= 0x20;
			}
		
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, iWingNum, iWingLevel, 0, 0, iOption1, iOption2, -1, iOption3, 0);
		::gObjInventoryCommit(lpObj->m_Index);
		::LogAddTD("[WingMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		return TRUE;
	}
	else
	{
		for (int n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBox[n].Clear();
		}

		GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		::LogAddTD("[WingMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		
		lpObj->ChaosLock = FALSE;

		return FALSE;
	}
}


BOOL IsCondorItemCheck(int iItemCode) //identical gs-cs 56
{
	if (iItemCode == iCondorFeather || iItemCode == iCondorFlame)
	{
		return TRUE;
	}
	return FALSE;
}

//Identical gs-cs 56
BOOL CheckLevel2WingItem(int iItemCode) //func_5d83b0
{
	if (iItemCode == ITEMGET(12, 3) ||
		iItemCode == ITEMGET(12, 4) ||
		iItemCode == ITEMGET(12, 5) ||
		iItemCode == ITEMGET(12, 6) ||
		iItemCode == ITEMGET(13, 30)) //season3 addon
	{
		return TRUE;
	}
	return FALSE;
}

//func_005d8410
BOOL CheckLevel3WingItem(int iItemCode)
{
	if (iItemCode == iWingofStorm ||
		iItemCode == iWingofEternal ||
		iItemCode == iWingofIllusion ||
		iItemCode == iWingofRuin ||
		iItemCode == iCapeofLord ||
		iItemCode == iWingofDimension)
	{
		return TRUE;
	}
	return FALSE;
}

//func_005d8480
BOOL CheckItemCondition(CItem * lpItem, short Level, BYTE Op1, BYTE Op2, BYTE Op3, BYTE SetOption, BYTE NewOption) //identical gs-cs 56
{
	if (lpItem == NULL) { return FALSE; }
	if (Level != FALSE) { if (lpItem->m_Level < Level) { return FALSE; } }
	if (Op1 != FALSE) { if (lpItem->m_Option1 < Op1) { return FALSE; } }
	if (Op2 != FALSE) { if (lpItem->m_Option2 < Op2) { return FALSE; } }
	if (Op3 != FALSE) { if (lpItem->m_Option3 < Op3) { return FALSE; } }
	if (SetOption != FALSE) { if (!lpItem->m_SetOption) { return FALSE; } }
	if (NewOption != FALSE) { if (!lpItem->m_NewOption) { return FALSE; } }
	return TRUE;
}


void ThirdWingMix1(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for (int n = 0; n<CHAOS_BOX_SIZE; n++) //loc14
	{
		if (lpObj->pChaosBox[n].IsItem() == TRUE)
		{
			if (CheckLevel2WingItem(lpObj->pChaosBox[n].m_Type) != FALSE)
			{
				if (CheckItemCondition(&lpObj->pChaosBox[n], 9, 0, 0, 1, 0, 0) != FALSE)
				{
					loc2++;
				}
			}
			else if (CheckItemCondition(&lpObj->pChaosBox[n], 7, 0, 0, 1, 1, 0) != FALSE)
			{
				loc3++;
				loc8 += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if (lpObj->pChaosBox[n].m_Type == iJewelofChaos)
			{
				loc4++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iBundleofSoul)
			{
				loc5++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iJewelofCreation)
			{
				loc6++;
			}
			else if (lpObj->pChaosBox[n].m_Type == ITEMGET(14, 53))
			{
				loc10 += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				loc7++;
			}
		}
	}

	if (loc10 > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if (loc2 != 1 || loc3 < 1 || loc4 != 1 || loc5 != 1 || loc6 != 1 || loc7 > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel1_Mix");
	LogAddTD("[ThirdWing Mix][Level 01] Chaos Mix Start");

	if (loc8 > 0)
	{
		lpObj->ChaosSuccessRate = loc8 / Configs.CondorMixCost;
	}

	if (lpObj->ChaosSuccessRate > Configs.CondorMixRate)
	{
		lpObj->ChaosSuccessRate = Configs.CondorMixRate;
	}
	else if (lpObj->ChaosSuccessRate < 1)
	{
		lpObj->ChaosSuccessRate = 1;
	}

	loc9 = lpObj->ChaosSuccessRate * Configs.CondorMixCost;

	lpObj->ChaosSuccessRate += loc10;

	//loc9 = lpObj->ChaosSuccessRate * 200000; //why double? maybe inside some if

	int iChaosTaxMoney = (int)((__int64)loc9 * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if (iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	loc9 += iChaosTaxMoney;

	if (loc9 < 0)
	{
		loc9 = 0;
	}

	if (lpObj->Money < loc9)
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= loc9;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ((rand() % 100) < lpObj->ChaosSuccessRate)
	{
		int type = ITEMGET(13, 53);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type, level, dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ThirdWing Mix][Level 01] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, loc9, loc10);
	}
	else
	{
		ThirdWingMixItemDown(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ThirdWing Mix][Level 01] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, loc9, loc10);
		lpObj->ChaosLock = FALSE;
	}
}

//func_5d8c70
void ThirdWingMix2(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;
	int loc11 = 0;
	int loc12 = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for (int n = 0; n<CHAOS_BOX_SIZE; n++) //loc16
	{
		if (lpObj->pChaosBox[n].IsItem() == TRUE)
		{
			if (CheckItemCondition(&lpObj->pChaosBox[n], 7, 0, 0, 1, 0, 1) != FALSE)
			{
				loc2++;
				loc10 += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if (lpObj->pChaosBox[n].m_Type == iCondorFeather)
			{
				loc3++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iCondorFlame)
			{
				loc4++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iJewelofChaos)
			{
				loc5++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iBundleofBless)
			{
				loc7++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iBundleofSoul)
			{
				loc6++;
			}
			else if (lpObj->pChaosBox[n].m_Type == iJewelofCreation)
			{
				loc8++;
			}
			else if (lpObj->pChaosBox[n].m_Type == ITEMGET(14, 53))
			{
				loc12 += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				loc9++;
			}
		}
	}

	if (loc12 > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if (loc2 < 1 || loc3 != 1 || loc4 != 1 || loc5 != 1 || loc7 != 1 || loc6 != 1 || loc8 != 1 || loc9 > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel2_Mix");
	LogAddTD("[ThirdWing Mix][Level 02] Chaos Mix Start");

	if (loc10 > 0)
	{
		lpObj->ChaosSuccessRate = loc10 / 3000000;
	}

	if (lpObj->ChaosSuccessRate > Configs.WingsLvl3MixRate)
	{
		lpObj->ChaosSuccessRate = Configs.WingsLvl3MixRate;
	}
	else if (lpObj->ChaosSuccessRate < 1)
	{
		lpObj->ChaosSuccessRate = 1;
	}

	loc11 = lpObj->ChaosSuccessRate * Configs.WingsLvl3MixCost;

	lpObj->ChaosSuccessRate += loc12;

	//loc11 = lpObj->ChaosSuccessRate * 200000;

	int iChaosTaxMoney = (int)((__int64)loc11 * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if (iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	loc11 += iChaosTaxMoney;

	if (loc11 < 0)
	{
		loc11 = 0;
	}

	if (lpObj->Money < loc11)
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= loc11;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ((rand() % 100) < lpObj->ChaosSuccessRate)
	{
		int loc18 = rand() % 6;
		int loc19 = 0;

		if (loc18 == 0)
		{
			loc19 = iWingofStorm;
		}
		else if (loc18 == 1)
		{
			loc19 = iWingofEternal;
		}
		else if (loc18 == 2)
		{
			loc19 = iWingofIllusion;
		}
		else if (loc18 == 3)
		{
			loc19 = iWingofRuin;
		}
		else if (loc18 == 4)
		{
			loc19 = iCapeofLord;
		}
		else if (loc18 == 5)
		{
			loc19 = iWingofDimension;
		}

		int loc20 = 0;
		int loc21 = 0;

		if ((rand() % 1000) <= i3rdWingLuckRate)
		{
			loc21 = 1;
		}

		int loc22 = 0;
		int loc23 = 0;
		int loc24 = rand() % 2;
		int loc25;
		int loc26;
		int loc27;
		int loc28;
		int loc29;

		switch (loc24)
		{
		case 0:
			loc25 = rand() % 1000;
			if (loc25 < 400)
			{
				loc23 |= 0x10;
			}
			break;

		case 1:
			loc25 = rand() % 1000;
			if (loc24 < 300)
			{
				loc23 |= 0x20;
			}
			break;
		}

		loc26 = rand() % 4;
		loc27 = rand() % 1000;
		loc22 = 0;

		switch (loc26)
		{
		case 1:
		{
			if (loc27 < 120)
			{
				loc22 = 1;
			}
		}
		break;

		case 2:
		{
			if (loc27 < 60)
			{
				loc22 = 2;
			}
		}
		break;

		case 3:
		{
			if (loc27 < 30)
			{
				loc22 = 3;
			}
		}
		break;
		}

		loc28 = rand() % 4;
		loc29 = rand() % 1000;

		switch (loc28)
		{
		case 0:
		{
			if (loc29 < 40)
			{
				loc23 |= 1;
			}
		}
		break;
		case 1:
		{
			if (loc29 < 20)
			{
				loc23 |= 2;
			}
		}
		break;

		case 2:
		{
			if (loc29 < 70)
			{
				loc23 |= 4;
			}
		}
		break;
		case 3:
		{
			if (loc29 < 70)
			{
				loc23 |= 8;
			}
		}
		break;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, loc19, 0, 0, loc20, loc21, loc22, -1, loc23, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ThirdWing Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, loc11, loc12);
	}
	else
	{
		ThirdWingMixItemDown(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ThirdWing Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, loc11, loc12);
		lpObj->ChaosLock = FALSE;
	}
}

//005D95E0   /> \55                            PUSH EBP
void ThirdWingMixItemDown(LPOBJ lpObj)
{
	if (lpObj->pChaosBox == NULL)
	{
		return;
	}

	for (int n = 0; n<CHAOS_BOX_SIZE; n++) //loc2
	{
		if (lpObj->pChaosBox[n].IsItem() == TRUE)
		{
			if (CheckLevel2WingItem(lpObj->pChaosBox[n].m_Type) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else if (CheckItemCondition(&lpObj->pChaosBox[n], 0, 0, 0, 0, 1, 0) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else if (CheckItemCondition(&lpObj->pChaosBox[n], 0, 0, 0, 0, 0, 1) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else
			{
				lpObj->pChaosBox[n].Clear();
			}
		}
	}
}

//005D97A0   /> \55                            PUSH EBP
void ThirdWingMixItemDown2(CItem * lpItem)
{
	if (lpItem == NULL)
	{
		return;
	}

	if ((rand() % 2) < 1)
	{
		lpItem->m_Level -= 2;
	}
	else
	{
		lpItem->m_Level -= 3;
	}

	lpItem->m_Option3 = 0;
	lpItem->Convert(lpItem->m_Type, lpItem->m_Option1, lpItem->m_Option2, lpItem->m_Option3, lpItem->m_NewOption, lpItem->m_SetOption, lpItem->m_ItemOptionEx,3);
}

void DefaultChaosMix(LPOBJ lpObj)
{
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int aIndex = lpObj->m_Index;
	BOOL fail = TRUE;
	int MixResult2;
	lpObj->ChaosLock = TRUE;

	if ( ChaosBoxMix(lpObj, MixResult2) == 0 )
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(aIndex, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	int iChaosTaxMoney = (int)((__int64)lpObj->ChaosMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)Configs.WingsLvl1MixCost);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	lpObj->ChaosMoney += iChaosTaxMoney;

	if ( lpObj->ChaosMoney < 0 )
	{
		lpObj->ChaosMoney = 0;
	}

	if ( lpObj->Money < lpObj->ChaosMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(aIndex, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;


	}
	else 
	{
		if ( lpObj->ChaosSuccessRate > 0 )
		{
			if ( lpObj->ChaosSuccessRate >= Configs.WingsLvl1MixRate)
			{
				lpObj->ChaosSuccessRate = Configs.WingsLvl1MixRate;
			}

			if ( (rand()%100) <= (lpObj->ChaosSuccessRate-1) ) 
			{
				fail = FALSE;
				pMsg.Result = CB_SUCCESS;

				int Level = rand()%5;
				int Option1 = 0;
				int Option2 = 0;
				int Option3 = 0;

				if ( (rand()%100)< (lpObj->ChaosSuccessRate/5 + 6) )
				{
					Option1 = 1;
				}

				if ( (rand()%100)< (lpObj->ChaosSuccessRate/5 + 4) )
				{
					Option2 = 1;
				}

				int OpProb;
				int OpType = rand()%3;
				OpProb = rand()%100;

				switch ( OpType )
				{
					case 0:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 4) ) 
						{
							Option3 = 3;
						}
						break;

					case 1:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 8) ) 
						{
							Option3 = 2;
						}
						break;

					case 2:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 12) ) 
						{
							Option3 = 1;
						}
						break;
				}

				if ( MixResult2 == TRUE )
				{
					int WingType = rand()%3;
					int WingNum = 0;

					if ( WingType == 0 )
					{
						WingNum = ITEMGET(12,0);
					}
					else if ( WingType == 1 )
					{
						WingNum = ITEMGET(12,1);
					}
					else if ( WingType == 2 )
					{
						WingNum = ITEMGET(12,2);
					}

					::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, WingNum, 0, 255, Option1, Option2, Option3, -1, 0, 0);
				}
				else
				{
					int ChaosItemType = rand()%3;
					int ChaosItemNum = 0;

					if ( ChaosItemType == 0 )	// Chaos Dragon Axe
					{
						ChaosItemNum = ITEMGET(2,6);
					}
					else if ( ChaosItemType == 1 )	// Chaos Nature Bow
					{
						ChaosItemNum = ITEMGET(4,6);
					}
					else if ( ChaosItemType == 2 )	// Chaos Lighting Staff
					{
						ChaosItemNum = ITEMGET(5,7);
					}

					::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ChaosItemNum, Level, 255, Option1, Option2, Option3, -1, 0, 0);
				}
			}
		}


		lpObj->Money -= lpObj->ChaosMoney;
		g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
		GCMoneySend(lpObj->m_Index, lpObj->Money);

		if ( fail == TRUE )
		{
			ChaosBoxItemDown(lpObj);
			GCUserChaosBoxSend(lpObj, 0);
			DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
			LogAddTD("[%s][%s] CBMix Fail %d Money : %d-%d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
				lpObj->Money, lpObj->ChaosMoney);
			lpObj->ChaosLock = FALSE;
		}
		else
		{
			LogAddTD("[%s][%s] CBMix Success Rate:%d Money : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
				lpObj->ChaosMoney);
		}

		if (Configs.gChaosEvent != FALSE )
		{
			CBUPS_ItemRequest(lpObj->m_Index, lpObj->AccountID, lpObj->Name);
		}
	}

	::gObjInventoryCommit(lpObj->m_Index);
}




void DevilSquareItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	if (Configs.gDevilSquareEvent != FALSE )
	{
		PMSG_CHAOSMIXRESULT pMsg;
		PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
		pMsg.Result = CB_ERROR;
		int aIndex = lpObj->m_Index;
		int eventitemcount;
		int itemlevel;
		int Ret = ::CheckDevilSquareItem(lpObj, eventitemcount, itemlevel);

		if ( Ret != FALSE )
		{
			if ( Ret == 3 )
			{
				pMsg.Result = CB_INCORRECT_MIX_ITEMS;
				DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] DiffLevel Devil's Key or Eyes [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;

				return;
			}
			
			if ( Ret == 2 )
			{
				pMsg.Result = CB_INCORRECT_MIX_ITEMS;
				DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Not Found Chaos Gem [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;
				
				return;
			}

			if ( Ret == 4 )
			{
				pMsg.Result = 0xF0;
				DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Charm Of Luck Over 10% [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;
				
				return;
			}

			
			if ( eventitemcount > 2 )
			{
				pMsg.Result = CB_TOO_MANY_ITEMS;
				DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Too many Devil's Key or Eyes [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;

				return;
			}

			if ( lpObj->Level < 10 )
			{
				pMsg.Result = CB_LOW_LEVEL_USER;
				DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;

				return;
			}

			::DevilSquareEventChaosMix(lpObj, Ret, itemlevel);
			return;
		}
		
		if ( eventitemcount > 1 )
		{
			pMsg.Result = CB_LACKING_MIX_ITEMS;
			DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;

			return;
		}
	}

	lpObj->ChaosLock = FALSE;
}







void BloodCastleItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	
	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	int aIndex = lpObj->m_Index;

	int iRET_VAL = g_BloodCastle.CheckChoasMixItem(aIndex);

	if ( BC_MAP_RANGE((iRET_VAL+(MAP_INDEX_BLOODCASTLE1-1))) != FALSE )
	{
		if ( g_BloodCastle.BloodCastleChaosMix(aIndex, iRET_VAL) == false )
		{
			lpObj->ChaosLock = FALSE;
		}

		return;
	}

	switch ( iRET_VAL )
	{
		case 9:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 10:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 11:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 12:
			pMsg.Result = CB_INVALID_ITEM_LEVEL	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 13:
			pMsg.Result = CB_BC_NOT_ENOUGH_ZEN	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 14:
			pMsg.Result = CB_USER_CLASS_LOW_LEVEL	;
			DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;
		case 15:
			pMsg.Result = 0xF0;
			DataSend(aIndex, (BYTE*)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			break;
		default:
			lpObj->ChaosLock = FALSE;
	}

}




void SetItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int MetalOfAncientCount = 0;
	int MixItemCount = 0;
	int MixSetItemIndex = 0;
	int iMixItemChaosMoney = 0;
	int iChaosMoney = 0;
	int iMetalOfAncientItemLevel = -1;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;

				if ( BlessGemCount > 3 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;

				if ( SoulGemCount > 3 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Level >= 6 && lpObj->pChaosBox[n].IsExtItem() != FALSE)
			{
				if ( gSetItemOption.IsSetItem(lpObj->pChaosBox[n].m_Type) != FALSE )
				{
					MixItemCount++;
					MixSetItemIndex = n;
					iMixItemChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
			else if ( ((lpObj->pChaosBox[n].m_Type >= ITEMGET(13,8) && lpObj->pChaosBox[n].m_Type < ITEMGET(13,14)) || (lpObj->pChaosBox[n].m_Type >= ITEMGET(13,20) && lpObj->pChaosBox[n].m_Type < ITEMGET(13,28) ) ) && ( lpObj->pChaosBox[n].m_Option3 >= 2  && lpObj->pChaosBox[n].m_Level >= 3 ) )	
			{
				if ( gSetItemOption.IsSetItem(lpObj->pChaosBox[n].m_Type ) != FALSE )
				{
					MixItemCount++;
					MixSetItemIndex = n;
					iMixItemChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,27) ) // Ancien Metal, Apply Deathway Fix here
			{
				MetalOfAncientCount++;
				iMetalOfAncientItemLevel = lpObj->pChaosBox[n].m_Level;
			}
			else
			{
				DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;
			}
		}
	}


	if ( ChoasGemCount < 1 || BlessGemCount < 3 || SoulGemCount < 3 || MetalOfAncientCount != 1 || MixItemCount != 1 )
	{
		DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "SetItemMix");
	LogAddTD("[SetItemMix] Chaos Mix Start");

	if ( gSetItemOption.CheckMixContition(lpObj->pChaosBox[MixSetItemIndex].m_Type, iMetalOfAncientItemLevel ) == FALSE )
	{
		DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->ChaosSuccessRate = iMixItemChaosMoney / 40000;
	lpObj->ChaosSuccessRate = iChaosMoney / 400000;

	if ( lpObj->ChaosSuccessRate > 80 )
	{
		lpObj->ChaosSuccessRate = 80;
	}

	int nChaosNeedMoney = (lpObj->ChaosSuccessRate - 50 ) * 1000000;

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	int setoption = gSetItemOption.MakeSetOption(lpObj->pChaosBox[MixSetItemIndex].m_Type, iMetalOfAncientItemLevel);

	if ( setoption == 0 )
	{
		pMsg.Result = CB_ERROR;
		DataSend(lpObj->m_Index, (BYTE*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		lpObj->pChaosBox[MixSetItemIndex].m_SetOption = setoption;

		if ( (rand()%100 ) < 80 )
		{
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption |= 4;
		}
		else
		{
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption |= 8;
		}

		pMsg.Result = CB_SUCCESS;
		CItem Item;

		float Dur = ItemGetDurability(lpObj->pChaosBox[MixSetItemIndex].m_Type, lpObj->pChaosBox[MixSetItemIndex].m_Level,
			lpObj->pChaosBox[MixSetItemIndex].IsExtItem(), lpObj->pChaosBox[MixSetItemIndex].IsSetItem());

		Item.m_Level = lpObj->pChaosBox[MixSetItemIndex].m_Level;
		Item.m_Durability = Dur * lpObj->pChaosBox[MixSetItemIndex].m_Durability / lpObj->pChaosBox[MixSetItemIndex].m_BaseDurability;
		Item.m_JewelOfHarmonyOption = lpObj->pChaosBox[MixSetItemIndex].m_JewelOfHarmonyOption;

		Item.Convert(lpObj->pChaosBox[MixSetItemIndex].m_Type, lpObj->pChaosBox[MixSetItemIndex].m_Option1, lpObj->pChaosBox[MixSetItemIndex].m_Option2,
			lpObj->pChaosBox[MixSetItemIndex].m_Option3, lpObj->pChaosBox[MixSetItemIndex].m_NewOption, 
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption, lpObj->pChaosBox[MixSetItemIndex].m_ItemOptionEx, CURRENT_DB_VERSION);

		Item.m_Number = lpObj->pChaosBox[MixSetItemIndex].m_Number;

		ItemByteConvert(pMsg.ItemInfo, Item);
		ChaosBoxInit(lpObj);
		::gObjChaosBoxInsertItemPos(lpObj->m_Index, Item, 0, -1);
		gObjChaosItemSet(lpObj->m_Index, 0, 1);

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		LogAddTD("[SetItemMix] [%s][%s] CBMix Success %d Money : %d-%d (SetName:%s)", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, lpObj->ChaosMoney, gSetItemOption.GetSetOptionName(lpObj->pChaosBox[MixSetItemIndex].m_Type, setoption));
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);

		LogAddTD("[SetItemMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
			nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}



void DarkHorseChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int CreatureGemCount = 0;
	int SoulOfDarkHorse = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int iCharmOfLuckCount = 0;
	int iInvalidItemCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )	// Creation
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// SUPE CHOAS HAHAHA
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,31) && lpObj->pChaosBox[n].m_Level == 0 )	// Spirit
			{
				SoulOfDarkHorse++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
			

		}
	}

	if ( ChoasGemCount != 1 || BlessGemCount != 5 || SoulGemCount != 5 || CreatureGemCount != 1 || SoulOfDarkHorse != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return ;
	}

	LogChaosItem(lpObj, "DarkHorseMix");
	LogAddTD("[DarkHorseMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.DarkHorseMixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int nChaosNeedMoney = Configs.DarkHorseMixCost;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int Level = 0;
		int ItemType = 13;
		int ItemSubType = 4;
		int ItemNum = ITEMGET(ItemType, ItemSubType);
		int Option1 = 0;
		int Option2 = 0;
		int Option3 = 0;

		int Add = 0;

		if ( (rand()%100) < (lpObj->ChaosSuccessRate/5+6) )
		{
			Add = 1;
		}

		if ( (rand()%5) == 0 )
		{
			Option1 = 1;
		}

		int lc22 = rand()%100;	
		int lc23 = rand()%3;
		//int lc24 = lc23;

		switch ( lc23 )
		{
			case 0:
				if ( lc22 <  4 )
				{
					Option2 = 3;
				}
				break;

			case 1:
				if ( lc22 <  10 )
				{
					Option2 = 2;
				}
				break;

			case 2:
				if ( lc22 <  20 )
				{
					Option2 = 1;
				}
				break;
		}

		::PetItemSerialCreateSend(lpObj->m_Index, -2, 0, 0, ItemNum, Level, 0,Add,  Option1, Option2, -1, 0, 0); 
		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[DarkHorseMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[DarkHorseMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
	}
}






void DarkSpiritChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int CreatureGemCount = 0;
	int SoulOfSpirit = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int iCharmOfLuckCount = 0;
	int iInvalidItemCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )	// Creation
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// SUPE CHOAS HAHAHA
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,31) && lpObj->pChaosBox[n].m_Level == 1 )	// Spirit
			{
				SoulOfSpirit++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( ChoasGemCount != 1 || BlessGemCount != 2 || SoulGemCount != 2 || CreatureGemCount != 1 || SoulOfSpirit != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return ;
	}

	LogChaosItem(lpObj, "DarkSpiritMix");
	LogAddTD("[DarkSpiritMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.DarkRavenMixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int nChaosNeedMoney = Configs.DarkRavenMixCost;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int Level = 0;
		int ItemType = 13;
		int ItemSubType = 5;
		int ItemNum = ITEMGET(ItemType, ItemSubType);
		int Option1 = 0;
		int Option2 = 0;
		int Option3 = 0;

		int Add = 0;

		if ( (rand()%100) < (lpObj->ChaosSuccessRate/5+6) )
		{
			Add = 1;
		}

		if ( (rand()%5) == 0 )
		{
			Option1 = 1;
		}

		int lc22 = rand()%100;	
		int lc23 = rand()%3;
//		int lc24 = lc23;

		switch ( lc23 )
		{
			case 0:
				if ( lc22 <  4 )
				{
					Option2 = 3;
				}
				break;

			case 1:
				if ( lc22 <  10 )
				{
					Option2 = 2;
				}
				break;

			case 2:
				if ( lc22 <  20 )
				{
					Option2 = 1;
				}
				break;
		}

		::PetItemSerialCreateSend(lpObj->m_Index, -2, 0, 0, ItemNum, Level, 0, Add, Option1, Option2, -1, 0, 0); 
		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[DarkSpiritMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[DarkSpiritMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
	}
}







void BlessPotionChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iBlessGemCount = 0;
	int iChaosMoney = 0;
	int iInvalidItemCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				iBlessGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iBlessGemCount == 0 )
		return;

	if ( iInvalidItemCount > 0 )
		return;

	if ( iBlessGemCount > 25 )
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "BlessPotionMix");
	LogAddTD("[BlessPotionMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = 100;

	int nChaosNeedMoney = 100000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int ItemNum = ITEMGET(14,7);
		int Level = 0;
		int Dur = iBlessGemCount * 10;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, Level, Dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}



void SoulPotionChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iSoulGemCount = 0;
	int iChaosMoney = 0;
	int iInvalidItemCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				iSoulGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iSoulGemCount == 0 )
		return;

	if ( iInvalidItemCount > 0 )
		return;

	if ( iSoulGemCount > 25 )
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "SoulPotionMix");
	LogAddTD("[SoulPotionMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.SoulPotionMixRate;

	int nChaosNeedMoney = Configs.SoulPotionMixCost;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int ItemNum = ITEMGET(14,7);
		int Level = 1;
		int Dur = iSoulGemCount * 10;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, Level, Dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Success %d Money : %d-%d",	// #error Change to SoulPotionMix
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[SoulPotionMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}





void LifeStoneChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iChoasGemCount = 0;
	int iBlessGemCount = 0;
	int iSoulGemCount = 0;
	int iProtectionGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				iBlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				iSoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,31) )	// Guardian Jewel
			{
				iProtectionGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// Habla pe super CHOAS
			{
				iChoasGemCount++;
			}
			else 
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iChoasGemCount != 1 || iBlessGemCount != 5 || iSoulGemCount != 5 || iProtectionGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "LifeStoneMix");
	LogAddTD("[LifeStoneMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = Configs.StoneMixRate;

	int nChaosNeedMoney = Configs.StoneMixCost;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,11) , 1, 0, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[LifeStoneMix] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[LifeStoneMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}






void HiddenTreasureBoxItemMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iBlueCrystal = 0;
	int iRedCrystal = 0;
	int iBlackCrystal = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,26) )
			{
				switch ( lpObj->pChaosBox[n].m_Level )
				{
					case 1:
						iRedCrystal++;
						break;
					case 2:
						iBlueCrystal++;
						break;
					case 3:
						iBlackCrystal++;
						break;
				}
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	int iCrystalMixType = -1;

	if ( iInvalidItemCount == 0 )
	{
		if ( iBlueCrystal == 7 )
		{
			if ( iRedCrystal == 0 && iBlackCrystal == 0 )
			{
				iCrystalMixType = 0;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iRedCrystal == 5 )
		{
			if ( iBlueCrystal == 0 && iBlackCrystal == 0 )
			{
				iCrystalMixType = 1;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iBlackCrystal == 3 )
		{
			if ( iRedCrystal == 0 && iBlueCrystal == 0 )
			{
				iCrystalMixType = 2;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iBlueCrystal == 1 && iRedCrystal == 1 && iBlackCrystal == 1 )
		{
			{
				iCrystalMixType = 3;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else
		{
			LogAddTD("[Hidden TreasureBox Event] [%s][%s] Item Mix Failed",
				lpObj->AccountID, lpObj->Name);
		
			DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
		}
	}
	else
	{
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] Item Mix Failed",
			lpObj->AccountID, lpObj->Name);
	
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}


	LogChaosItem(lpObj, "Hidden TreasureBox Mix");
	LogAddTD("[Hidden TreasureBox Event] [%s][%s] Chaos Mix Start",
		lpObj->AccountID, lpObj->Name);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		switch ( iCrystalMixType )
		{
			case 0:	case 1:	case 2:
				ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 4, 1, 0, 0, 0, -1, 0, 0);
				break;
			case 3:
				ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 5, 1, 0, 0, 0, -1, 0, 0);
				break;
			default:
				LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Failed - iCrystalMixType is wrong : %d",
					lpObj->AccountID, lpObj->Name, iCrystalMixType);
				DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;
				return;
		}

		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Success:%d Type:%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, iCrystalMixType);
	}
	else
	{
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Fail Rate:%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate);

		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;
	}

	lpObj->ChaosLock = FALSE;
}





void Fenrir_01Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iStuffCount_02 = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,32) )
			{
				iStuffCount_01 += lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,33) )
			{
				iStuffCount_02 += lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 20 || iStuffCount_02 != 20 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_01Level_Mix");
	LogAddTD("[Fenrir Mix][Level 01] Chaos Mix Start");

	lpObj->ChaosSuccessRate = Configs.g_iFenrir_01Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 0;	// #error Set the Correct price before call the CstleSyegeTributes

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,35);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , level, dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 01] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 01] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}


void Fenrir_02Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iStuffCount_02 = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,34) )
			{
				iStuffCount_01 += lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,35) )
			{
				iStuffCount_02 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 10 || iStuffCount_02 != 5 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_02Level_Mix");
	LogAddTD("[Fenrir Mix][Level 02] Chaos Mix Start");

	lpObj->ChaosSuccessRate = Configs.g_iFenrir_02Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 0;	// #error Set the Correct price before call the CstleSyegeTributes

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,36);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , level, dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}




void Fenrir_03Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iLifeGemCount = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,36) )
			{
				iStuffCount_01 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iLifeGemCount ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 1 || iLifeGemCount != 3 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_03Level_Mix");
	LogAddTD("[Fenrir Mix][Level 03] Chaos Mix Start");

	lpObj->ChaosSuccessRate = Configs.g_iFenrir_03Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 10000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,37);
		int level = 0;
		int dur = 255;
		int op1 = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , level, dur, op1, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 03] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 03] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}


void Fenrir_04Upgrade_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iLifeGemCount = 0;
	int iChaosGemCount = 0;
	int iAttackStuffCount = 0;
	int iDefendStuffCount = 0;
	int iAttackStuffPrice = 0;
	int iDefendStuffPrice = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	BOOL bFenrirDamageInc = FALSE;
	BOOL bFenrirDamageDec = FALSE;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,37) )
			{
				iStuffCount_01 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iLifeGemCount ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(0,0) &&
					  lpObj->pChaosBox[n].m_Type < ITEMGET(6,0) &&
					  lpObj->pChaosBox[n].m_Level >= 4 &&
					  lpObj->pChaosBox[n].m_Option3 >= 1)
			{
				iAttackStuffCount++;
				iAttackStuffPrice += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(6,0) &&
					  lpObj->pChaosBox[n].m_Type < ITEMGET(12,0) &&
					  lpObj->pChaosBox[n].m_Level >= 4 &&
					  lpObj->pChaosBox[n].m_Option3 >= 1)
			{
				iDefendStuffCount++;
				iDefendStuffPrice += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 1 || iLifeGemCount != 5 || iChaosGemCount != 1 || ( iAttackStuffCount == 0 && iDefendStuffCount == 0 ) || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iAttackStuffCount > 0 )
	{
		bFenrirDamageInc = TRUE;
		iChaosMoney = iAttackStuffPrice;
	}

	if ( iDefendStuffCount > 0 )
	{
		bFenrirDamageDec = TRUE;
		iChaosMoney = iDefendStuffPrice;
	}

	if ( bFenrirDamageInc && bFenrirDamageDec )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( !bFenrirDamageInc && !bFenrirDamageDec )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_04Level_Mix");
	LogAddTD("[Fenrir Mix][Level 04] Chaos Mix Start");

	int nChaosNeedMoney = 10000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( iChaosMoney > 1000000 )
		iChaosMoney = 1000000;

	lpObj->ChaosSuccessRate = iChaosMoney * 100 / 1000000;

	if ( lpObj->ChaosSuccessRate > 79 )
		lpObj->ChaosSuccessRate = 79;

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,37);
		int level = 0;
		int dur = 255;
		int op1 = 1;
		int nop = 0;

		if ( bFenrirDamageInc )
		{
			nop |= 1;
		}

		if ( bFenrirDamageDec )
		{
			nop |= 2;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , level, dur, op1, 0, 0, -1, nop, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 04] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 04] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}




void ShieldPotionLv1_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	if (Configs.g_ShieldSystemOn == FALSE )
		return;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,3) )
			{
				iHealthPotionCount+=lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = Configs.g_iShieldPotionLv1MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv1 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv1 Mix] - Mix Start");
	
	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate <  Configs.g_iShieldPotionLv1MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,35);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv1 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv1 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, Configs.g_iShieldPotionLv1MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}




void ShieldPotionLv2_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,38) )
			{
				iHealthPotionCount+=lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = Configs.g_iShieldPotionLv2MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	
	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv2 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv2 Mix] - Mix Start");

	GCMoneySend(lpObj->m_Index, lpObj->Money);
	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate < Configs.g_iShieldPotionLv2MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,36);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv2 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv2 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, Configs.g_iShieldPotionLv2MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}


void ShieldPotionLv3_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,39) )
			{
				iHealthPotionCount+=lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = Configs.g_iShieldPotionLv3MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	
	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv3 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv3 Mix] - Mix Start");

	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate <  Configs.g_iShieldPotionLv3MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,37);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv3 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (UCHAR*)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv3 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, Configs.g_iShieldPotionLv3MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}




void LotteryItemMix(LPOBJ lpObj)
{
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	int iLotteryItemCount = 0;
	int iInvalidItemCount = 0;
	int iItemHeight = 0;
	int iItemWidth = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,54) )
			{
				iLotteryItemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iLotteryItemCount > 1 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "CashLottery");
	iItemHeight = 4;
	iItemWidth = 2;

	if ( !CheckInventoryEmptySpace(lpObj, iItemHeight, iItemWidth))
	{
		pMsg.Result = 0xF1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	CItem LotteryItem;

	if ( g_CashLotterySystem.GetItem(&LotteryItem) == -1 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		LogAddTD("[ChaosMix][LotteryItemMix] Lottery Item Mix Failed. Can't Get Item from List.");

		return;
	}

	ItemSerialCreateSend(lpObj->m_Index, 255, 0, 0, LotteryItem.m_Type,
		LotteryItem.m_Level, LotteryItem.m_Durability,
		LotteryItem.m_Option1, LotteryItem.m_Option2, LotteryItem.m_Option3,
		lpObj->m_Index, LotteryItem.m_NewOption, 0);

	gObjInventoryCommit(lpObj->m_Index);

	LogAddTD("[ChaosMix][ChaosCardMix] Chaos Card Item Mix Success [%s][%s]",
		lpObj->AccountID, lpObj->Name);

	BYTE btExOption[MAX_EXOPTION_SIZE];

	ItemIsBufExOption(btExOption, &LotteryItem);
	
	LogAddTD("[CashShop][ChaosCardMix] - User(ID:%s,Name:%s) Item(Name:%s,Type:%d,Level:%d,Dur:%d,Skill:%d,Luck:%d,AddOption:%d,Ex:(%d,%d,%d,%d,%d,%d))",
		lpObj->AccountID, lpObj->Name, ItemAttribute[LotteryItem.m_Type].Name,
		LotteryItem.m_Type, LotteryItem.m_Level, (int)LotteryItem.m_Durability,
		LotteryItem.m_Option1, LotteryItem.m_Option2, LotteryItem.m_Option3,
		btExOption[0], btExOption[1], btExOption[2], btExOption[3], btExOption[4], btExOption[5]);
}
