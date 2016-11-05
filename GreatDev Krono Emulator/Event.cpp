#include "StdAfx.h"
#include "Event.h"

void EventChipEventProtocolCore(BYTE protoNum, LPBYTE aRecv, int aLen)
{
#if (TRACE_PROTOCOL==1)
	LogAddHeadHex("EVENT_SERVER", aRecv, aLen);
#endif

	switch ( protoNum )
	{
		case 0x01:
			EGRecvEventChipInfo((PMSG_ANS_VIEW_EC_MN *)aRecv);
			break;
		case 0x02:
			EGResultRegEventChip((PMSG_ANS_REGISTER_EVENTCHIP *)aRecv);
			break;
		case 0x03:
			EGRecvRegMutoNum((PMSG_ANS_REGISTER_MUTONUM *)aRecv);
			break;
		case 0x04:
			EGRecvChangeRena((PMSG_ANS_RESET_EVENTCHIP *)aRecv);
			break;
		case 0x05:
			EGRecvStoneInfo((PMSG_ANS_VIEW_STONES *)aRecv);
			break;
		case 0x06:
			EGRecvRegStone((PMSG_ANS_REGISTER_STONES *)aRecv);
			break;
		case 0x07:
			EGRecvDeleteStone((PMSG_ANS_DELETE_STONES *)aRecv);
			break;
		case 0x09:
			EGRecvChangeStones((PMSG_ANS_RESET_EVENTCHIP *)aRecv);
			break;
		case 0x08:
			EGRecv2AnvRegSerial((PMSG_ANS_2ANIV_SERIAL *)aRecv);
			break;
		case 0x10:
			EGRecvRegRingGift((PMSG_ANS_REG_RINGGIFT *)aRecv);
			break;
		case 0x15:
			EGAnsRegCCOfflineGift((PMSG_ANS_REG_CC_OFFLINE_GIFT *)aRecv);
			break;
		case 0x16:
			EGAnsRegDLOfflineGift((PMSG_ANS_REG_DL_OFFLINE_GIFT *)aRecv);
			break;
		case 0x17:
			EGAnsRegHTOfflineGift((PMSG_ANS_REG_HT_OFFLINE_GIFT *)aRecv);
			break;
	}
}


void DataSendEventChip(PCHAR pMsg, int size)
{
	if ( IsEventChipServerConnected == FALSE && ::EventChipServerConnect != FALSE )
	{
		wsEvenChipServerCli.Close();
		wsEvenChipServerCli.CreateSocket(ghWnd);
		if ( GMEventChipServerConnect(::gEventChipServerIp, WM_GM_EVENTCHIP_CLIENT_MSG_PROC) == FALSE )
		{
			IsEventChipServerConnected = FALSE;
			LogAddTD("Can not connect EventChip Server");

			return;
		}

		::IsEventChipServerConnected = TRUE;

	}

	if ( ::IsEventChipServerConnected != FALSE && ::EventChipServerConnect != FALSE )
	{
		::wsEvenChipServerCli.DataSend((char *)pMsg, size);
	}
}


void EledoradoBoxOpenEven(LPOBJ lpObj, int boxtype,int addlevel,int money)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;
	int ItemDropRate = 0;
	int ExItemDropRate = 0;
	CItemBag * EledoradoBox = NULL;

	switch ( boxtype )
	{
		case 8:
			EledoradoBox = ::GoldGoblenItemBag;
			ItemDropRate = ::gEledoradoGoldGoblenItemDropRate;
			ExItemDropRate = ::gEledoradoGoldGoblenExItemDropRate;
			break;

		case 9:
			EledoradoBox = ::TitanItemBag;
			ItemDropRate = ::gEledoradoTitanItemDropRate;
			ExItemDropRate = ::gEledoradoTitanExItemDropRate;
			break;

		case 10:
			EledoradoBox = ::GoldDerconItemBag;
			ItemDropRate = ::gEledoradoGoldDerconItemDropRate;
			ExItemDropRate = ::gEledoradoGoldDerconExItemDropRate;
			break;

		case 11:
			EledoradoBox = ::DevilLizardKingItemBag;
			ItemDropRate = ::gEledoradoDevilLizardKingItemDropRate;
			ExItemDropRate = ::gEledoradoDevilLizardKingExItemDropRate;
			break;

		case 12:
			EledoradoBox = ::KanturItemBag;
			ItemDropRate = ::gEledoradoDevilTantarosItemDropRate;
			ExItemDropRate = ::gEledoradoDevilTantarosExItemDropRate;
			break;
	}

	if ( EledoradoBox == NULL )
	{
		return;
	}

	if ( EledoradoBox->GetBagCount() > 0 )
	{
		if ( (rand() % 100) < ItemDropRate )
		{
			int NormalItemCount = EledoradoBox->GetNormalItemCount();
			int ExItemCount = EledoradoBox->GetExItemCount();

			if ( (rand() % 100 ) < ExItemDropRate )
			{
				DropItemNum = rand() % ExItemCount + NormalItemCount;
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;
				level = 0;
				type = ItemGetNumberMake(EledoradoBox->GetType(DropItemNum), EledoradoBox->GetIndex(DropItemNum));
				Option1 = 1;
				Option2 = rand() % 2;

				if ( Option2 == 0 || Option1  == 0 )
				{
					if ( (rand() % 5 ) < 1 )
					{
						Option3 = 3;
					}
					else
					{
						Option3 = rand() % 3;
					}
				}

				ExOption = NewOptionRand(0);

				if ( type == ITEMGET(12,15) ||
					 type == ITEMGET(14,13) ||
					 type == ITEMGET(14,14) )
				{
					Option1 = 0;
					Option2 = 0;
					Option3 = 0;
					level = 0;
					ExOption = 0;
				}

				if ( type == ITEMGET(13,0) ||
					 type == ITEMGET(13,1) ||
					 type == ITEMGET(13,2) ||
					 type == ITEMGET(13,8) ||
					 type == ITEMGET(13,9) ||
					 type == ITEMGET(13,12) ||
					 type == ITEMGET(13,13) )
				{
					level = 0;
				}
			}
			else
			{
				DropItemNum = rand() % NormalItemCount;
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;

				if ( addlevel != 0 )
				{
					level = EledoradoBox->GetLevel(DropItemNum) + rand()% addlevel;
				}
				else
				{
					level = EledoradoBox->GetLevel(DropItemNum);
				}

				type = ItemGetNumberMake(EledoradoBox->GetType(DropItemNum), EledoradoBox->GetIndex(DropItemNum));

				Option1 = rand() % 2;
				Option2 = rand() % 2;

				if ( Option2 == 0 || Option1  == 0 )
				{
					if ( (rand() % 5 ) < 1 )
					{
						Option3 = 3;
					}
					else
					{
						Option3 = rand() % 3;
					}
				}

				if ( type == ITEMGET(12,15) ||
					 type == ITEMGET(14,13) ||
					 type == ITEMGET(14,14) ||
					 type == ITEMGET(14,16))
				{
					Option1 = 0;
					Option2 = 0;
					Option3 = 0;
					level = 0;
					ExOption = 0;
				}

				if ( type == ITEMGET(13,0) ||
					 type == ITEMGET(13,1) ||
					 type == ITEMGET(13,2) ||
					 type == ITEMGET(13,8) ||
					 type == ITEMGET(13,9) ||
					 type == ITEMGET(13,12) ||
					 type == ITEMGET(13,13) )
				{
					level = 0;
				}
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index,
				ExOption, 0);

			CItem NewItem;
			NewItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, CURRENT_DB_VERSION);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Eledorado Box] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, NewItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(money, x, y);
}




void EventChipOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;

	if ( (rand()%100) < ::g_EventChipDropRateForBoxOfGold )
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;
		type = ItemGetNumberMake(14, 21);
		::ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, 0, 0);
		LogAdd("EventChip Event ItemDrop Rena");

		return;
	}

	if ( LuckboxItemBag == NULL )
	{
		return;
	}

	if ( LuckboxItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%20) < ::g_ItemDropRateForBoxOfGold )
		{
			DropItemNum = rand() % LuckboxItemBag->GetBagCount();
			dur = 0;
			x = lpObj->X;
			y = lpObj->Y;
			level = LuckboxItemBag->GetLevel(DropItemNum) + rand() % 2;

			type = ItemGetNumberMake(LuckboxItemBag->GetType(DropItemNum), LuckboxItemBag->GetIndex(DropItemNum));

			Option1 = rand() % 2;
			Option2 = rand() % 2;

			if ( Option2 == 0 || Option1  == 0 )
			{
				if ( (rand() % 5 ) < 1 )
				{
					Option3 = 3;
				}
				else
				{
					Option3 = rand() % 3;
				}
			}

			if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14) )
			{
				Option1 = 0;
				Option2 = 0;
				Option3 = 0;
				level = 0;
				ExOption = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y,
				type, level, dur, Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);

			PMSG_SERVERCMD pMsg;

			PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x40, sizeof(pMsg));
			pMsg.CmdType = 2;
			pMsg.X = x;
			pMsg.Y = y;

			MsgSendV2(lpObj, (LPBYTE)&pMsg, sizeof(pMsg));
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, sizeof(pMsg));

			CItem NewItem;
			NewItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, CURRENT_DB_VERSION);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Event Chip] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, NewItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;


		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(1000, x, y);
}



	
void GoldMedalOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;
	int ExOption=0;

	if ( !GoldMedalItemBag )
		return;

	if ( GoldMedalItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%20) < g_ItemDropRateForGoldMedal )
		{
			DropItemNum = rand()%GoldMedalItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;
			level = GoldMedalItemBag->GetLevel(DropItemNum) + rand()%4;
			type = ItemGetNumberMake(GoldMedalItemBag->GetType(DropItemNum), GoldMedalItemBag->GetIndex(DropItemNum));
			Option1 = rand()%2;
			Option2 = rand()%2;

			if ( !Option2 || !Option1 )
			{
				if ( (rand()%5) <1 )
					Option3 = 3;
				else
					Option3 = rand()%3;
			}

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
				ExOption=0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);

			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 2;
			ServerCmd.X = x;
			ServerCmd.Y = y;

			MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Gold Medal] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(100000, x, y);
}



void SilverMedalOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;
	int ExOption=0;

	if ( !SilverMedalItemBag )
		return;

	if ( SilverMedalItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%20) < g_ItemDropRateForSilverMedal )
		{
			DropItemNum = rand()%SilverMedalItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;
			level = SilverMedalItemBag->GetLevel(DropItemNum) + rand()%4;
			type = ItemGetNumberMake(SilverMedalItemBag->GetType(DropItemNum), SilverMedalItemBag->GetIndex(DropItemNum));
			Option1 = rand()%2;
			Option2 = rand()%2;

			if ( !Option2 || !Option1 )
			{
				if ( (rand()%5) <1 )
					Option3 = 3;
				else
					Option3 = rand()%3;
			}

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
				ExOption=0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 2;
			ServerCmd.X = x;
			ServerCmd.Y = y;

			MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Silver Medal] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(100000, x, y);
}




void HeartOfLoveOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;

	if ( !HeartOfLoveItemBag )
		return;

	if ( HeartOfLoveItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%20) < g_ItemDropRateForgHeartOfLove )
		{
			DropItemNum = rand()%HeartOfLoveItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;

			if ( gLanguage == 0 )
			{
				level = HeartOfLoveItemBag->GetLevel(DropItemNum) + rand()%2;
			}
			else
			{
				level = HeartOfLoveItemBag->GetLevel(DropItemNum) + rand()%5;
			}

			type = ItemGetNumberMake(HeartOfLoveItemBag->GetType(DropItemNum), HeartOfLoveItemBag->GetIndex(DropItemNum));
			Option1 = rand()%2;
			Option2 = rand()%2;

			if ( !Option2 || !Option1 )
			{
				if ( (rand()%5) <1 )
					Option3 = 3;
				else
					Option3 = rand()%3;
			}

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 0;
			ServerCmd.X = x;
			ServerCmd.Y = y;

			MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Heart Of Love] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(1004, x, y);
}




void FireCrackerOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;

	if ( gOnlyFireCrackerEffectUse )
	{
		PMSG_SERVERCMD ServerCmd;

		PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
		ServerCmd.CmdType = 0;
		ServerCmd.X = lpObj->X;
		ServerCmd.Y = lpObj->Y;

		MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

		return;
	}

	if ( !FireCrackerItemBag )
		return;

	if ( FireCrackerItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%10) < g_ItemDropRateForgFireCracker )
		{
			DropItemNum = rand()%FireCrackerItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;
			
			if ( gLanguage == 0 )
			{
				level = FireCrackerItemBag->GetLevel(DropItemNum) + rand()%2;
			}
			else
			{
				level = FireCrackerItemBag->GetLevel(DropItemNum) + rand()%5;
			}
			
			type = ItemGetNumberMake(FireCrackerItemBag->GetType(DropItemNum), FireCrackerItemBag->GetIndex(DropItemNum));
			Option1 = rand()%2;
			Option2 = rand()%2;

			if ( !Option2 || !Option1 )
			{
				if ( (rand()%5) <1 )
					Option3 = 3;
				else
					Option3 = rand()%3;
			}

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 0;
			ServerCmd.X = x;
			ServerCmd.Y = y;

			MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Fire Cracker] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(2004, x, y);
}


void StarOfXMasOpenEven(LPOBJ lpObj)
{
	StarOfXMasItemBag->DropItem(lpObj->m_Index);
}

void FireworksOpenEven(LPOBJ lpObj)
{
			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 0;
			ServerCmd.X = lpObj->X;
			ServerCmd.Y = lpObj->Y;

			MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

}


void RingEventItemBoxOpen(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;

	if ( RingEventItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%10) < 9 )
		{
			DropItemNum = rand()%RingEventItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;

			int rnd = rand() % 100;

			if ( rnd < 5 )
				level = 9;
			else if ( rnd < 20 )
				level = 8;
			else if ( rnd < 50 )
				level = 7;
			else 
				level = 6;

			type = ItemGetNumberMake(RingEventItemBag->GetType(DropItemNum), RingEventItemBag->GetIndex(DropItemNum));
			Option1 = 1;
			Option2 = rand()%2;

			if ( (rand()%5) <1 )
				Option3 = 3;
			else
				Option3 = rand()%3;

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Ring Event](%d,%d,%d) ItemDrop : Item:%s %d Level:%d op1:%d op2:%d op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(100000, x, y);
}


void FriendShipItemBoxOpen(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;

	if ( RingEventItemBag->GetBagCount() > 0 )	// #error Chagne to FriendShipItemBag
	{
		if ( true )
		{
			DropItemNum = rand()%RingEventItemBag->GetBagCount();	// #error Chagne to FriendShipItemBag
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;

			int rnd = rand() % 100;

			if ( rnd < 5 )
				level = 9;
			else if ( rnd < 20 )
				level = 8;
			else if ( rnd < 50 )
				level = 7;
			else 
				level = 6;

			type = ItemGetNumberMake(RingEventItemBag->GetType(DropItemNum), RingEventItemBag->GetIndex(DropItemNum));	// #error Chagne to FriendShipItemBag
			Option1 = 1;
			Option2 = rand()%2;

			if ( (rand()%5) <1 )
				Option3 = 3;
			else
				Option3 = rand()%3;

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][FriendShip Ring Event](%d,%d,%d) ItemDrop : Item:%s %d Level:%d op1:%d op2:%d op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}
}




void DarkLordHeartItemBoxOpen(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;
	int DropItemRate = 0;

	if ( ((DWORD)rand()%60000) < (DWORD)g_iDarkLordHeartOffEventRate )	
	{
		if ( lpObj->Level > 100 )
		{
			return;
		}

		EGReqRegDLOfflineGift(lpObj->m_Index);
	}
	
	if ( DarkLordHeartItemBag->GetBagCount() > 0 )
	{
	
		DropItemNum = rand()%DarkLordHeartItemBag->GetBagCount();
		DropItemRate = DarkLordHeartItemBag->GetOp1(DropItemNum);

		if ( (rand()%100) < DropItemRate && lpObj->Level <= 100 )
		{
			level = DarkLordHeartItemBag->GetLevel(DropItemNum);
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;
			
			type = ItemGetNumberMake(DarkLordHeartItemBag->GetType(DropItemNum), DarkLordHeartItemBag->GetIndex(DropItemNum));
			Option1 = ((rand()%100)>=70)?0:1;
			Option2 = ((rand()%100)>=10)?0:1;
			int rnd = rand()%20;

			if ( rnd < 1 )
				Option3 = 3;
			else if ( rnd < 5 )
				Option3 = 2;
			else if ( rnd < 9 )
				Option3 = 1;
			else
				Option3 = 0;

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop][Darklord Heart] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}
	}

	x = lpObj->X;
	y = lpObj->Y;
	MapC[lpObj->MapNumber].MoneyItemDrop(10000, x, y);
}




void HiddenTreasureBoxItemBoxOpen(LPOBJ lpObj)
{
	CItem objTempItem;
	int nItemIndex;

	if ( HiddenTreasureBoxItemBag->PickItem(objTempItem, nItemIndex) == FALSE )
	{
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] Item Pick Failed - Data Error",
			lpObj->AccountID, lpObj->Name);

		MapC[lpObj->MapNumber].MoneyItemDrop(200000, lpObj->X, lpObj->Y);
		return;
	}

	int iItemSuccessRate = HiddenTreasureBoxItemBag->GetMinLevel(nItemIndex);

	if ( (rand()%100) < iItemSuccessRate )
	{
		objTempItem.m_Level = 0;

		if ( objTempItem.m_Option1 )
			objTempItem.m_Option1 = rand()%2;

		if ( objTempItem.m_Option2 )
			objTempItem.m_Option2 = rand()%2;

		if ( objTempItem.m_Option3 )
			if ( (rand()%5) <1 )
				objTempItem.m_Option3 = 3;
			else
				objTempItem.m_Option3 = rand()%3;

		if ( objTempItem.m_NewOption )
		{
			objTempItem.m_NewOption = NewOptionRand(objTempItem.m_Level);
			objTempItem.m_Option1 = 1;
			objTempItem.m_Option2 = 0;
		}


		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y, objTempItem.m_Type, objTempItem.m_Level, objTempItem.m_Durability,
			objTempItem.m_Option1, objTempItem.m_Option2, objTempItem.m_Option3, lpObj->m_Index, objTempItem.m_NewOption, 0);

		BYTE NewOption[MAX_EXOPTION_SIZE];
		ItemIsBufExOption(NewOption, &objTempItem);

		LogAddTD("[Hidden TreasureBox Event] [%s][%s] Event ItemDrop : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d exop:[%d,%d,%d,%d,%d,%d]",
			lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y,
			ItemAttribute[objTempItem.m_Type].Name, objTempItem.m_Type,
			objTempItem.m_Level, objTempItem.m_Option1, objTempItem.m_Option2,
			objTempItem.m_Option3, NewOption[0], NewOption[1], NewOption[2], NewOption[3], NewOption[4], NewOption[5]);
	}
	else
	{
		int money = 200000;
		MapC[lpObj->MapNumber].MoneyItemDrop(money, lpObj->X, lpObj->Y);

		LogAddTD("[Hidden TreasureBox Event] [%s][%s] Event ZenDrop : %d : (%d)(%d/%d)",
			lpObj->AccountID, lpObj->Name, money, lpObj->MapNumber, lpObj->X, lpObj->Y);
	}
}


void RedRibbonBoxOpen(LPOBJ lpObj)
{
	RedRibbonBoxEventItemBag->DropRedRibbonBoxEventItem(lpObj->m_Index);
}


void GreenRibbonBoxOpen(LPOBJ lpObj)
{
	GreenRibbonBoxEventItemBag->DropGreenRibbonBoxEventItem(lpObj->m_Index);
}


void BlueRibbonBoxOpen(LPOBJ lpObj)
{
	BlueRibbonBoxEventItemBag->DropBlueRibbonBoxEventItem(lpObj->m_Index);
}


void PinkChocolateBoxOpen(LPOBJ lpObj)
{
	PinkChocolateBoxEventItemBag->DropPinkChocolateBoxEventItem(lpObj->m_Index);
}


void RedChocolateBoxOpen(LPOBJ lpObj)
{
	RedChocolateBoxEventItemBag->DropRedChocolateBoxEventItem(lpObj->m_Index);
}


void BlueChocolateBoxOpen(LPOBJ lpObj)
{
	BlueChocolateBoxEventItemBag->DropBlueChocolateBoxEventItem(lpObj->m_Index);
}


void LightPurpleCandyBoxOpen(LPOBJ lpObj)
{
	LightPurpleCandyBoxEventItemBag->DropLightPurpleCandyBoxEventItem(lpObj->m_Index);
}


void VermilionCandyBoxOpen(LPOBJ lpObj)
{
	VermilionCandyBoxEventItemBag->DropVermilionCandyBoxEventItem(lpObj->m_Index);
}


void DeepBlueCandyBoxOpen(LPOBJ lpObj)
{
	DeepBlueCandyBoxEventItemBag->DropDeepBlueCandyBoxEventItem(lpObj->m_Index);
}


void KundunEventItemBoxOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	KundunEventItemBag->DropKundunEventItem(lpObj->m_Index, btMapNumber, cX, cY);
}



void HallowinDayEventItemBoxOpen(LPOBJ lpObj)
{
	HallowinDayEventItemBag->DropHallowinEventItem(lpObj);
}

 
void CastleHuntZoneBossRewardOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	CastleHuntZoneBossItemBag->DropCastleHuntZoneBossReward(lpObj->m_Index, btMapNumber, cX, cY);
} 

void CrywolfDarkElfItemBagOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	CrywolfDarkElfItemBag->DropCrywolfDarkElfItem(lpObj->m_Index, btMapNumber, cX, cY);
}


void CrywolfBossMonsterItemBagOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	CrywolfBossMonsterItemBag->DropCrywolfBossMonsterItem(lpObj->m_Index, btMapNumber, cX, cY);
}
 
void KanturuMayaHandItemBagOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	KanturuMayaHandItemBag->DropKanturuMayaHandItem(lpObj->m_Index, btMapNumber, cX, cY);
}


void KanturuNightmareItemBagOpen(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	KanturuNightmareItemBag->DropKanturuNightmareItem(lpObj->m_Index, btMapNumber, cX, cY);
} 
 
void LuckyBoxOpenEven(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;


	if ( !LuckboxItemBag )
		return;

	if ( LuckboxItemBag->GetBagCount() > 0 )
	{
		if ( (rand()%10)<2 )
		{
			DropItemNum = rand()%LuckboxItemBag->GetBagCount();
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;
			level = LuckboxItemBag->GetLevel(DropItemNum) + rand()%2;
			type = ItemGetNumberMake(LuckboxItemBag->GetType(DropItemNum), LuckboxItemBag->GetIndex(DropItemNum));
			Option1 = rand()%2;
			Option2 = rand()%2;

			if ( (rand()%5) <1 )
				Option3 = 3;
			else
				Option3 = rand()%2+1;

			if ( type == ITEMGET(12,15) ||
				 type == ITEMGET(14,13) ||
				 type == ITEMGET(14,14) )
			{
				Option1=0;
				Option2=0;
				Option3=0;
				level = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, lpObj->m_Index, 0, 0);

			CItem EventItem;

			EventItem.Convert(type, Option1, Option2, Option3, 0, 1, 0, 3);

			LogAddTD("[%s][%s][Lucky Box Item Drop] : (%d)(X:%d/Y:%d) Item:%s(%d) Level:%d Op1:%d Op2:%d Op3:%d",
				lpObj->AccountID, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, EventItem.GetName(),
				type, level, Option1, Option2, Option3);

			return;
		}	
	}

	for(int n=0;n<(rand()%4+3);n++)
	{
		x = lpObj->X-2;
		y = lpObj->Y-2;
		x+= rand()%3;
		y+= rand()%3;
		MapC[lpObj->MapNumber].MoneyItemDrop(1000, x, y);
	}
}



BOOL AttackEvent53BagOpen(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;


	if ( !Mon53 )
		return FALSE;

	if ( Mon53->GetBagCount() > 0 )
	{
	
		DropItemNum = rand()%Mon53->GetBagCount();
		dur=0;
		x = lpObj->X;
		y = lpObj->Y;
		level = Mon53->GetLevel(DropItemNum);
		type = ItemGetNumberMake(Mon53->GetType(DropItemNum), Mon53->GetIndex(DropItemNum));

		if ( (rand()%100)<6)
			Option1 = 1;
		
		if ( (rand()%100)<4)
			Option2 = 1;

		int rnd1;
		int rnd2 = rand() % 3;
		rnd1 = rand() % 100;

		switch ( rnd2 )
		{
			case 0:
				if ( rnd1 < 4 )
					Option3 = 3;
				break;
			case 1:
				if ( rnd1 < 8 )
					Option3 = 2;
				break;
			case 2:
				if ( rnd1 < 12 )
					Option3 = 1;
				break;
		}

		if ( type == ITEMGET(12,15) ||
			 type == ITEMGET(14,13) ||
			 type == ITEMGET(14,14) )
		{
			Option1=0;
			Option2=0;
			Option3=0;
			level = 0;
		}

		if ( type == ITEMGET(13,0) ||
			 type == ITEMGET(13,1) ||
			 type == ITEMGET(13,2) ||
			 type == ITEMGET(13,8) ||
			 type == ITEMGET(13,9) ||
			 type == ITEMGET(13,12) ||
			 type == ITEMGET(13,13) )
		{
			level = 0;
		}

		int iMaxHitIndex = gObjMonsterTopHitDamageUser(lpObj);

		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, iMaxHitIndex, 0, 0);

		LogAdd("Event ItemDrop(53) : Item:%d Level:%d op1:%d op2:%d op3:%d",
			type, level, Option1, Option2, Option3);

		return TRUE;
	}

	return FALSE;
}



BOOL AttackEvent55BagOpen(LPOBJ lpObj)
{
	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	int DropItemNum;


	if ( !Mon55 )
		return FALSE;

	if ( Mon55->GetBagCount() > 0 )
	{
	
		DropItemNum = rand()%Mon55->GetBagCount();
		dur=0;
		x = lpObj->X;
		y = lpObj->Y;
		level = Mon55->GetLevel(DropItemNum) + rand() % 2;
		type = ItemGetNumberMake(Mon55->GetType(DropItemNum), Mon55->GetIndex(DropItemNum));

		if ( (rand()%100)<6)
			Option1 = 1;
		
		if ( (rand()%100)<4)
			Option2 = 1;

		int rnd1;
		int rnd2 = rand() % 3;
		rnd1 = rand() % 100;

		switch ( rnd2 )
		{
			case 0:
				if ( rnd1 < 4 )
					Option3 = 3;
				break;
			case 1:
				if ( rnd1 < 8 )
					Option3 = 2;
				break;
			case 2:
				if ( rnd1 < 12 )
					Option3 = 1;
				break;
		}

		if ( type == ITEMGET(12,15) ||
			 type == ITEMGET(14,13) ||
			 type == ITEMGET(14,14) )
		{
			Option1=0;
			Option2=0;
			Option3=0;
			level = 0;
		}

		if ( type == ITEMGET(13,0) ||
			 type == ITEMGET(13,1) ||
			 type == ITEMGET(13,2) ||
			 type == ITEMGET(13,8) ||
			 type == ITEMGET(13,9) ||
			 type == ITEMGET(13,12) ||
			 type == ITEMGET(13,13) )
		{
			level = 0;
		}

		int iMaxHitIndex = gObjMonsterTopHitDamageUser(lpObj);

		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, iMaxHitIndex, 0, 0);

		LogAdd("Event ItemDrop(55) : Item:%d Level:%d op1:%d op2:%d op3:%d",
			type, level, Option1, Option2, Option3);

		return TRUE;
	}

	return FALSE;
}




#pragma warning ( disable : 4101 )
void EGRecvEventChipInfo(PMSG_ANS_VIEW_EC_MN * aRecv)
{
	LPOBJ lpObj = &gObj[aRecv->iINDEX];

	PMSG_EVENTCHIPINFO eventchipeventinfo;
	char msg[255];

	PHeadSetB((LPBYTE)&eventchipeventinfo, 0x94, sizeof(eventchipeventinfo));
	eventchipeventinfo.Type = 0;
	eventchipeventinfo.ChipCount = aRecv->nEVENT_CHIPS;
	lpObj->EventChipCount = aRecv->nEVENT_CHIPS;
	lpObj->MutoNumber = aRecv->iMUTO_NUM;

	DataSend(lpObj->m_Index, (LPBYTE)&eventchipeventinfo, eventchipeventinfo.h.size);

	lpObj->UseEventServer = FALSE;
}
#pragma warning ( default : 4101 )



void EGResultRegEventChip(PMSG_ANS_REGISTER_EVENTCHIP * aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;
	LPOBJ lpObj;
	int aIndex;

	PHeadSetB((LPBYTE)&Result, 0x95, sizeof(Result));
	lpObj = &gObj[aRecv->iINDEX];
	aIndex = aRecv->iINDEX;

	if ( aRecv->bSUCCESS == FALSE )
	{
		Result.ChipCount = -1;
		LogAddTD("[EventChip] [%s][%s] RegEventServer Fail (RegEventchip) %d",
			lpObj->AccountID, lpObj->Name, aRecv->Pos);

	}
	else
	{
		Result.ChipCount = aRecv->nEVENT_CHIPS;
		gObjInventoryDeleteItem(aIndex, aRecv->Pos);
		GCInventoryItemDeleteSend(aIndex, aRecv->Pos, 1);

		LogAddTD("[EventChip] [%s][%s] Delete EventChip (%d)",
			lpObj->AccountID, lpObj->Name, aRecv->Pos);
	}

	Result.Type = 0;

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;
}




void EGRecvRegMutoNum( PMSG_ANS_REGISTER_MUTONUM* aRecv)
{
	LPOBJ lpObj;
	int aIndex;
	

	lpObj = &gObj[aRecv->iINDEX];
	aIndex = aRecv->iINDEX;

	PMSG_GETMUTONUMBER_RESULT Result;

	PHeadSetB((LPBYTE)&Result, 0x96, sizeof(Result));
	
	if ( gObjFind10EventChip(aIndex) == FALSE )
	{
		Result.MutoNum[0] = -1;
		Result.MutoNum[1] = 0;
		Result.MutoNum[2] = 0;

		DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

		lpObj->UseEventServer = FALSE;

		return;
	}

	gObjDelete10EventChip(aIndex);
	Result.MutoNum[0] = aRecv->iMUTO_NUM / 1000000;
	Result.MutoNum[1] = aRecv->iMUTO_NUM / 1000 - aRecv->iMUTO_NUM / 1000000 * 1000;
	Result.MutoNum[2] = aRecv->iMUTO_NUM % 1000;
	lpObj->MutoNumber = aRecv->iMUTO_NUM;
	
	LogAddTD("[EventChip] [%s][%s] Make MutoNumber %d,%d,%d",
		lpObj->AccountID, lpObj->Name, 
		Result.MutoNum[0], Result.MutoNum[1], Result.MutoNum[2]);

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);
	lpObj->UseEventServer = FALSE;
}



void EGRecvChangeRena( PMSG_ANS_RESET_EVENTCHIP* aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;
	LPOBJ lpObj;
	int aIndex;

	PHeadSetB((LPBYTE)&Result, 0x95, sizeof(Result));
	lpObj = &gObj[aRecv->iINDEX];
	aIndex = aRecv->iINDEX;

	if ( aRecv->bSUCCESS != FALSE )
	{
		lpObj->Money += lpObj->EventChipCount * 3000;
		GCMoneySend(aIndex, lpObj->Money);

		LogAddTD("[EventChip] [%s][%s] ChangeRena AddMoney(%d)",
			lpObj->AccountID, lpObj->Name, lpObj->EventChipCount * 3000);
	}
	else
	{
		LogAddTD("[EventChip] [%s][%s] ChangeRena Fail",
			lpObj->AccountID, lpObj->Name);
	}

	Result.ChipCount = 0;
	lpObj->EventChipCount = 0;

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;
}



LPOBJ pEventObj;

void EGRecvStoneInfo( PMSG_ANS_VIEW_STONES* aRecv)
{
	LPOBJ lpObj = &gObj[aRecv->iINDEX];

	PMSG_EVENTCHIPINFO Result;
	
	PHeadSetB((LPBYTE)&Result, 0x94, sizeof(Result));

	if ( aRecv->bSUCCESS )
		lpObj->iStoneCount = aRecv->iStoneCount;
	else
		lpObj->iStoneCount = 0;

	lpObj->MutoNumber = 0;
	Result.Type = 3;
	Result.ChipCount = aRecv->iStoneCount;

	DataSend(lpObj->m_Index, (LPBYTE)&Result, Result.h.size);

	char msg[128];
	wsprintf(msg, lMsg.Get(MSGGET(4, 153)), Result.ChipCount);
	ChatTargetSend(pEventObj, msg, lpObj->m_Index);
}



void EGRecvRegStone( PMSG_ANS_REGISTER_STONES* aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;
	LPOBJ lpObj;
	int aIndex;
	

	PHeadSetB((LPBYTE)&Result, 0x95, sizeof(Result));
	lpObj = &gObj[aRecv->iINDEX];
	aIndex = aRecv->iINDEX;

	if ( aRecv->bSUCCESS != FALSE )
	{
		Result.ChipCount = aRecv->iStoneCount;
		gObjInventoryDeleteItem(aIndex, aRecv->iPosition);
		GCInventoryItemDeleteSend(aIndex, aRecv->iPosition, 1);

		LogAddTD("[Stone] [%s][%s] Delete Stones",
			lpObj->AccountID, lpObj->Name);
	}
	else
	{
		Result.ChipCount = -1;
		
		LogAddTD("[Stone] [%s][%s] RegEventServer Fail (Stones : %d)",
			lpObj->AccountID, lpObj->Name, aRecv->iStoneCount);
	}

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;
}



void EGRecvDeleteStone( PMSG_ANS_DELETE_STONES* aRecv)
{
	return;
}



void EGRecvChangeStones( PMSG_ANS_RESET_EVENTCHIP* aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;
	LPOBJ lpObj;
	int aIndex;
	

	PHeadSetB((LPBYTE)&Result, 0x95, sizeof(Result));
	lpObj = &gObj[aRecv->iINDEX];
	aIndex = aRecv->iINDEX;

	if ( aRecv->bSUCCESS != FALSE )
	{
		lpObj->Money += lpObj->iStoneCount * 3000;
		GCMoneySend(aIndex, lpObj->Money);

		LogAddTD("[Stones] [%s][%s] ChangeRena AddMoney(%d)",
			lpObj->AccountID, lpObj->Name, lpObj->iStoneCount*3000);
	}
	else
	{
		LogAddTD("[Stones] [%s][%s] ChangeRena Fail",
			lpObj->AccountID, lpObj->Name);
	}

	Result.ChipCount = 0;
	lpObj->iStoneCount = 0;

	DataSend(aIndex, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;
}


struct PMSG_ANS_2ANV_LOTTO_EVENT
{
	PBMSG_HEAD h;	// C1:9D
	BYTE btIsRegistered;	// 3
	char szGIFT_NAME[64];	// 4
};



#define GIFT_2ANV_MAP	235
#define MAX_GIFT_2ANV	50
#define GIFT_2ANV_RANGE(x)  ( (((x))<0)?FALSE:(((x))>MAX_GIFT_2ANV-1)?FALSE:TRUE )


BOOL g_bRingEventItemTextLoad = FALSE;
char g_sz2ANV_GIFT_NAME[MAX_GIFT_2ANV][64];

void EGRecv2AnvRegSerial( PMSG_ANS_2ANIV_SERIAL* aRecv)
{
	PMSG_ANS_2ANV_LOTTO_EVENT Result;

	PHeadSetB((LPBYTE)&Result, 0x9D, sizeof(Result));

	if ( !OBJMAX_RANGE(aRecv->iINDEX))
	{
		LogAddTD("[Mu_2Anv_Event] Error : Index is out of bound [%d]", aRecv->iINDEX);
		return;
	}

	if ( gObj[aRecv->iINDEX].Connected <= PLAYER_LOGGED )
	{
		LogAddTD("[Mu_2Anv_Event] Error : Index is out of bound [%d]", aRecv->iINDEX);
		return;
	}

	Result.szGIFT_NAME[0] = 0;

	if ( aRecv->btIsRegistered == FALSE )
	{
		Result.btIsRegistered = FALSE;
		
		if ( !GIFT_2ANV_RANGE(aRecv->iGiftNumber-1) )
		{
			LogAddTD("[Mu_2Anv_Event] Error : Gift Index is out of bound [%d]", aRecv->iGiftNumber);
			Result.btIsRegistered = 2;
		}

		if ( gObj[aRecv->iINDEX].Connected > PLAYER_LOGGED )
		{
			PMSG_SERVERCMD ServerCmd;

			PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
			ServerCmd.CmdType = 0;
			ServerCmd.X = gObj[aRecv->iINDEX].X;
			ServerCmd.Y = gObj[aRecv->iINDEX].Y;

			MsgSendV2(&gObj[aRecv->iINDEX], (LPBYTE)&ServerCmd, sizeof(ServerCmd));
			DataSend(aRecv->iINDEX, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
		}

		if ( g_bRingEventItemTextLoad )
		{
			strcpy(Result.szGIFT_NAME, g_sz2ANV_GIFT_NAME[aRecv->iGiftNumber-1]);
		}

		switch ( aRecv->iGiftNumber )
		{
			case 1:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 13),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 13)].Name);
				}
				break;
			case 2:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 14),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 14)].Name);
				}
				break;
			case 3:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 15),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 15)].Name);
				}
				break;
			case 4:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 5:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					3, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, "Heart of Love");
				}
				break;
			case 6:
				gObj[aRecv->iINDEX].Money += 500000;
				GCMoneySend(aRecv->iINDEX, gObj[aRecv->iINDEX].Money);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, "500,000 Zen");
				}
				break;
			case 7:
				gObj[aRecv->iINDEX].Money += 50000;
				GCMoneySend(aRecv->iINDEX, gObj[aRecv->iINDEX].Money);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, "50,000 Zen");
				}
				break;
			case 8:	case 9:	case 10:
				gObj[aRecv->iINDEX].Money += 30000;
				GCMoneySend(aRecv->iINDEX, gObj[aRecv->iINDEX].Money);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, "30,000 Zen");
				}
				break;
			case 11:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 19),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 11)].Name);	// #error Change 11 to 19
				}
				break;
			case 12:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 18),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 18)].Name);
				}
				break;
			case 13:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 17),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 17)].Name);
				}
				break;
			case 14:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 16),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 16)].Name);
				}
				break;
			case 15:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 14),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 14)].Name);
				}
				break;
			case 16:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 13),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 13)].Name);
				}
				break;
			case 17:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(12, 12),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(12, 12)].Name);
				}
				break;
			case 18:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(13, 2),
					0, 255, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(13, 2)].Name);
				}
				break;
			case 19:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(13, 3),
					0, 255, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(13, 2)].Name);	// #error Change 2 to 3
				}
				break;
			case 20:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 16),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 16)].Name);
				}
				break;
			case 21:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(13, 0),
					0, 255, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(13, 0)].Name);
				}
				break;
			case 22:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(13, 1),
					0, 255, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(13, 1)].Name);
				}
				break;
			case 23:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					1, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 24:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					9, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 25:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					10, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 26:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 19),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 19)].Name);
				}
				break;
			case 27:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 19),
					1, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 19)].Name);
				}
				break;
			case 28:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 19),
					2, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 19)].Name);
				}
				break;
			case 29:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 19),
					3, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 19)].Name);
				}
				break;
			case 30:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 19),
					4, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 19)].Name);
				}
				break;
			case 31:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					2, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 32:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 20),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 20)].Name);
				}
				break;
			case 33:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 22),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 22)].Name);
				}
				break;
			case 34:	case 35:	case 36:	case 37:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(13, 15),
					aRecv->iGiftNumber - 34, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(13, 15)].Name);
				}
				break;
			case 38:	case 39:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					aRecv->iGiftNumber - 27, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 40:	case 41:	case 42:	case 43:	case 44:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 20),
					aRecv->iGiftNumber - 39, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 20)].Name);
				}
				break;
			case 45:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 11),
					8, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 11)].Name);
				}
				break;
			case 46:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 41),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 41)].Name);
				}
				break;
			case 47:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 42),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 42)].Name);
				}
				break;
			case 48:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 44),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 44)].Name);
				}
				break;
			case 49:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 43),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 43)].Name);
				}
				break;
			case 50:
				ItemSerialCreateSend(gObj[aRecv->iINDEX].m_Index, GIFT_2ANV_MAP, 
					gObj[aRecv->iINDEX].X, gObj[aRecv->iINDEX].Y,
					ItemGetNumberMake(14, 31),
					0, 0, 0, 0, 0,
					aRecv->iINDEX,
					0, 0);

				if ( g_bRingEventItemTextLoad == FALSE )
				{
					strcpy(Result.szGIFT_NAME, ItemAttribute[ITEMGET(14, 31)].Name);
				}
				break;
			default:
				LogAddTD("[Mu_2Anv_Event] Error : iGiftNumber is Out of Boud [%d]", aRecv->iGiftNumber);
				break;
		}
	}
	else if ( aRecv->btIsRegistered == 1 ||
			  aRecv->btIsRegistered == 2 ||
			  aRecv->btIsRegistered == 3 ||
			  aRecv->btIsRegistered == 4 ||
			  aRecv->btIsRegistered == 5 )
	{
		Result.btIsRegistered = aRecv->btIsRegistered;
	}
	else
	{
		Result.btIsRegistered = 4;
		LogAddTD("[Mu_2Anv_Event] Error : Result Value is Wrong [%d]", aRecv->btIsRegistered);
	}

	LogAddTD("[Mu_2Anv_Event] Register Serial Result : %d [%s][%s]",
		aRecv->btIsRegistered, gObj[aRecv->iINDEX].AccountID, gObj[aRecv->iINDEX].Name);

	DataSend(aRecv->iINDEX, (LPBYTE)&Result, Result.h.size);

	gObj[aRecv->iINDEX].UseEventServer = FALSE;
}


static const char g_szRingEventOfflineGift[4][32] = { "100µ· ¹Â¹ÝÁö",
													  "10µ· ¹Â¹ÝÁö",
													  "5µ· ¹Â¹ÝÁö",
													  "2µ· ¹Â¹ÝÁö"};
															



void EGRecvRegRingGift( PMSG_ANS_REG_RINGGIFT* aRecv)
{
	gObj[aRecv->iINDEX].UseEventServer = FALSE;

	if ( gObjIsConnected(aRecv->iINDEX) == FALSE )
		return;

	if ( strcmp(aRecv->szUID, gObj[aRecv->iINDEX].AccountID))
		return;

	if ( aRecv->btIsRegistered == 1 )
	{
		if ( CHECK_LIMIT(aRecv->btGiftKind-1, 4) )
		{
			char szTemp[256];
			wsprintf(szTemp, "%s´Ô ²²¼­ %s¿¡ ´çÃ·µÇ¼Ì½À´Ï´Ù.",
				gObj[aRecv->iINDEX].Name, g_szRingEventOfflineGift[aRecv->btGiftKind-1]);

			AllSendServerMsg(szTemp);

			LogAddTD("[Ring Event] [%s][%s] Register Succeeded Result:%d, Gift:%d",
				gObj[aRecv->iINDEX].AccountID, gObj[aRecv->iINDEX].Name,
				aRecv->btIsRegistered, aRecv->btGiftKind);
		}
		else
		{
			LogAddTD("[Ring Event] [%s][%s] Register Failed Result:%d, Gift:%d (out of bound, 1~4)",
				gObj[aRecv->iINDEX].AccountID, gObj[aRecv->iINDEX].Name,
				aRecv->btIsRegistered, aRecv->btGiftKind);
		}

		return;
	}

	LogAddTD("[Ring Event] [%s][%s] Register Failed Result : %d",
		gObj[aRecv->iINDEX].AccountID, gObj[aRecv->iINDEX].Name,
		aRecv->btIsRegistered);

	if ( gObjIsConnected(aRecv->iINDEX) == TRUE )
	{
		MapC[gObj[aRecv->iINDEX].MapNumber].MoneyItemDrop(100000, (BYTE)gObj[aRecv->iINDEX].X, (BYTE)gObj[aRecv->iINDEX].Y);
	}
}



struct PMSG_REQ_BLOODCASTLE_ENTERCOUNT
{
	PBMSG_HEAD h;	// C1:0B
	char AccountID[10];	// 3
	char GameID[10];	// D
	int ServerCode;	// 18
	int iObjIndex;	// 1C
};



void EGReqBloodCastleEnterCount(int iIndex)
{
	if ( !gObjIsConnected(iIndex) )
		return;

	PMSG_REQ_BLOODCASTLE_ENTERCOUNT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x0B;
	pMsg.h.size = sizeof(pMsg);
	memcpy(pMsg.AccountID, gObj[iIndex].AccountID, 10);
	memcpy(pMsg.GameID, gObj[iIndex].Name, 10);
	pMsg.ServerCode = gGameServerCode / 20;
	pMsg.iObjIndex = iIndex;

	if ( !IsDevilSquareEventConnected && !DevilSquareEventConnect )
	{
		wsRServerCli.Close();
		wsRServerCli.CreateSocket(ghWnd);

		if ( !GMRankingServerConnect(gDevilSquareEventServerIp, WM_GM_RANKING_CLIENT_MSG_PROC) )
		{
			IsDevilSquareEventConnected = 0;
			LogAddTD("Can not connect Ranking Server");
			return;
		}

		IsDevilSquareEventConnected = TRUE;
	}

	if ( !DevilSquareEventConnect && IsDevilSquareEventConnected )
	{
		wsRServerCli.DataSend((PCHAR)&pMsg, pMsg.h.size);
	}
}


struct PMSG_ANS_CL_ENTERCOUNT
{
	PBMSG_HEAD h;	// C1:9F
	BYTE btEventType;	// 3
	BYTE btLeftEnterCount;	// 4
};


void EGAnsBloodCastleEnterCount( PMSG_ANS_BLOODCASTLE_ENTERCOUNT* lpMsg)
{
	if ( !lpMsg)
		return;

	if ( !gObjIsConnected(lpMsg->iObjIndex))
		return;

	char szAccountID[11] = {0};
	char szName[11] = {0};
	memcpy(szAccountID, lpMsg->AccountID, 10);
	memcpy(szName, lpMsg->GameID, 10);

	if ( strcmp(gObj[lpMsg->iObjIndex].AccountID, szAccountID) ||
		 strcmp(gObj[lpMsg->iObjIndex].Name, szName) )
		 return;

	PMSG_ANS_CL_ENTERCOUNT pMsgSend;

	pMsgSend.h.c = 0xC1;
	pMsgSend.h.headcode = 0x9F;
	pMsgSend.h.size = sizeof(pMsgSend);
	pMsgSend.btEventType = 2;
	pMsgSend.btLeftEnterCount = lpMsg->iLeftCount;

	DataSend(lpMsg->iObjIndex, (LPBYTE)&pMsgSend, sizeof(pMsgSend));
}




struct PMSG_REQ_REG_CC_OFFLINE_GIFT
{
	PBMSG_HEAD h;	// C1:15
	int iINDEX;	// 4
	char szUID[11];	// 8
	WORD wServerCode;	// 14
	char szNAME[11];	// 16
};


void EGReqRegCCOfflineGift(int iIndex)
{
	if ( !gObjIsConnected(iIndex) )
		return;

	PMSG_REQ_REG_CC_OFFLINE_GIFT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x15;
	pMsg.h.size = sizeof(pMsg);
	memcpy(pMsg.szUID, gObj[iIndex].AccountID, 11);
	memcpy(pMsg.szNAME, gObj[iIndex].Name, 11);
	pMsg.wServerCode = gGameServerCode / 20;
	pMsg.iINDEX = iIndex;
	pMsg.szUID[10] = 0;
	pMsg.szNAME[10] = 0;

	DataSendEventChip((PCHAR)&pMsg, sizeof(pMsg));
}




void EGAnsRegCCOfflineGift( PMSG_ANS_REG_CC_OFFLINE_GIFT* lpMsg)
{
	if ( !lpMsg)
		return;

	if ( !lpMsg->iResultCode )
		return;

	char szAccountID[11] = {0};
	char szName[11] = {0};
	char szGIFT_NAME[50] = {0};
	memset(szAccountID, 0, sizeof(szAccountID));
	memset(szName, 0, sizeof(szName));
	memset(szGIFT_NAME, 0, sizeof(szGIFT_NAME));
	memcpy(szAccountID, lpMsg->szUID, sizeof(szAccountID));
	memcpy(szName, lpMsg->szNAME, sizeof(szName));
	memcpy(szGIFT_NAME, lpMsg->szGIFT_NAME, sizeof(szGIFT_NAME));
	szAccountID[10] = 0;
	szName[10] = 0;
	szGIFT_NAME[49] = 0;
	char szText[256] = {0};

	wsprintf(szText, lMsg.Get(MSGGET(6,74)), szName, szGIFT_NAME);
	AllSendServerMsg(szText);

	LogAddTD("[Chaos Castle] [%s][%s] Success to Register OffLine Gift (GIFT:%s)",
		szAccountID, szName, szGIFT_NAME);
}





struct PMSG_REQ_REG_DL_OFFLINE_GIFT
{
	PBMSG_HEAD h;	// C1:16
	int iINDEX;	// 4
	char szUID[11];	// 8
	WORD wServerCode;	// 14
	char szNAME[11];	// 16
};


void EGReqRegDLOfflineGift(int iIndex)
{
	if ( !gObjIsConnected(iIndex) )
		return;

	PMSG_REQ_REG_DL_OFFLINE_GIFT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x16;
	pMsg.h.size = sizeof(pMsg);
	memcpy(pMsg.szUID, gObj[iIndex].AccountID, 11);
	memcpy(pMsg.szNAME, gObj[iIndex].Name, 11);
	pMsg.wServerCode = gGameServerCode / 20;
	pMsg.iINDEX = iIndex;
	pMsg.szUID[10] = 0;
	pMsg.szNAME[10] = 0;

	DataSendEventChip((PCHAR)&pMsg, sizeof(pMsg));
}




void EGAnsRegDLOfflineGift( PMSG_ANS_REG_DL_OFFLINE_GIFT* lpMsg)
{
	if ( !lpMsg)
		return;

	if ( !lpMsg->iResultCode )
		return;

	char szAccountID[11] = {0};
	char szName[11] = {0};
	char szGIFT_NAME[50] = {0};
	memset(szAccountID, 0, sizeof(szAccountID));
	memset(szName, 0, sizeof(szName));
	memset(szGIFT_NAME, 0, sizeof(szGIFT_NAME));
	memcpy(szAccountID, lpMsg->szUID, sizeof(szAccountID));
	memcpy(szName, lpMsg->szNAME, sizeof(szName));
	memcpy(szGIFT_NAME, lpMsg->szGIFT_NAME, sizeof(szGIFT_NAME));
	szAccountID[10] = 0;
	szName[10] = 0;
	szGIFT_NAME[49] = 0;
	char szText[256] = {0};

	wsprintf(szText, "[´ÙÅ©·Îµå ±â³ä ÀÌº¥Æ®] %s ´Ô²²¼­ %s °æÇ°¿¡ ´çÃ·µÇ¼Ì½À´Ï´Ù.", szName, szGIFT_NAME);
	AllSendServerMsg(szText);

	LogAddTD("[DarkLord Heart Event] [%s][%s] Success to Register OffLine Gift (GIFT:%s)",
		szAccountID, szName, szGIFT_NAME);
}



struct PMSG_REQ_REG_HT_OFFLINE_GIFT
{
	PBMSG_HEAD h;	// C1:17
	int iINDEX;	// 4
	char szUID[11];	// 8
	WORD wServerCode;	// 14
	char szNAME[11];	// 16
};

void EGReqRegHTOfflineGift(int iIndex)
{
	if ( !gObjIsConnected(iIndex) )
		return;

	PMSG_REQ_REG_HT_OFFLINE_GIFT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x17;
	pMsg.h.size = sizeof(pMsg);
	memcpy(pMsg.szUID, gObj[iIndex].AccountID, 11);
	memcpy(pMsg.szNAME, gObj[iIndex].Name, 11);
	pMsg.wServerCode = gGameServerCode / 20;
	pMsg.iINDEX = iIndex;
	pMsg.szUID[10] = 0;
	pMsg.szNAME[10] = 0;

	DataSendEventChip((PCHAR)&pMsg, sizeof(pMsg));
}




void EGAnsRegHTOfflineGift( PMSG_ANS_REG_HT_OFFLINE_GIFT* lpMsg)
{
	if ( !lpMsg)
		return;

	if ( !lpMsg->iResultCode )
	{
		if ( gObjIsConnected(lpMsg->iINDEX))
		{
			LPOBJ lpObj = &gObj[lpMsg->iINDEX];

			MapC[lpObj->MapNumber].MoneyItemDrop(1000000, lpObj->X, lpObj->Y);
		}
		return;
	}

	char szAccountID[11] = {0};
	char szName[11] = {0};
	char szGIFT_NAME[50] = {0};
	memset(szAccountID, 0, sizeof(szAccountID));
	memset(szName, 0, sizeof(szName));
	memset(szGIFT_NAME, 0, sizeof(szGIFT_NAME));
	memcpy(szAccountID, lpMsg->szUID, sizeof(szAccountID));
	memcpy(szName, lpMsg->szNAME, sizeof(szName));
	memcpy(szGIFT_NAME, lpMsg->szGIFT_NAME, sizeof(szGIFT_NAME));
	szAccountID[10] = 0;
	szName[10] = 0;
	szGIFT_NAME[49] = 0;
	char szText[256] = {0};

	wsprintf(szText, "[¼û°ÜÁø º¸¹°»óÀÚ ÀÌº¥Æ®] %s ´Ô²²¼­ %s °æÇ°¿¡ ´çÃ·µÇ¼Ì½À´Ï´Ù.", szName, szGIFT_NAME);
	AllSendServerMsg(szText);

	LogAddTD("[Hidden TreasureBox Event] [%s][%s] Success to Register OffLine Gift (GIFT:%s)",
		szAccountID, szName, szGIFT_NAME);
}




void Japan1StAnivBoxOpen(LPOBJ lpObj, int iBoxLevel)
{
	PMSG_SERVERCMD ServerCmd;

	PHeadSubSetB((LPBYTE)&ServerCmd, 0xF3, 0x40, sizeof(ServerCmd));
	ServerCmd.CmdType = 0;
	ServerCmd.X = lpObj->X;
	ServerCmd.Y = lpObj->Y;

	MsgSendV2(lpObj, (LPBYTE)&ServerCmd, sizeof(ServerCmd));
	DataSend(lpObj->m_Index, (LPBYTE)&ServerCmd, sizeof(ServerCmd));

	srand(time(NULL));

	float dur;
	int type;
	int level;
	int x;
	int y;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum;
	int ExOption = 0;
	int iMinLevel = 0;
	int iAddLevel = 0;
	int iItemDropRate = 30;
	int iDropMoney = 50000;
	CItemBag * Japan1StAnivBox = NULL;

	switch ( iBoxLevel )
	{
		case 1:
			Japan1StAnivBox = GoldGoblenItemBag;
			iMinLevel = 5;
			iAddLevel = 2;
			break;
		case 2:
			Japan1StAnivBox = TitanItemBag;
			iMinLevel = 4;
			iAddLevel = 2;
			break;
		case 3:
			Japan1StAnivBox = GoldDerconItemBag;
			iMinLevel = 4;
			iAddLevel = 2;
			break;
		case 4:
			Japan1StAnivBox = DevilLizardKingItemBag;
			iMinLevel = 4;
			iAddLevel = 1;
			break;
		case 5:
			Japan1StAnivBox = KanturItemBag;
			iMinLevel = 4;
			iAddLevel = 0;
			break;
	}

	if ( (rand()%100) < iItemDropRate )
	{
		if ( Japan1StAnivBox->GetBagCount() > 0 )
		{
			int NormalItemCount = Japan1StAnivBox->GetNormalItemCount();
			int ExItemCount = Japan1StAnivBox->GetExItemCount();
			DropItemNum = rand()%NormalItemCount;
			dur=0;
			x = lpObj->X;
			y = lpObj->Y;

			if ( iAddLevel )
				level = iMinLevel + rand() % iAddLevel;
			else
				level = iMinLevel;

			type = ItemGetNumberMake(Japan1StAnivBox->GetType(DropItemNum), Japan1StAnivBox->GetIndex(DropItemNum));

			Option1 = rand() % 2;
			Option2 = rand() % 2;

			if ( Option2 == 0 || Option1  == 0 )
			{
				if ( (rand() % 5 ) < 1 )
				{
					Option3 = 3;
				}
				else
				{
					Option3 = rand() % 3;
				}
			}

			if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14) || type == ITEMGET(14,16) )
			{
				Option1 = 0;
				Option2 = 0;
				Option3 = 0;
				level = 0;
				ExOption = 0;
			}

			if ( type == ITEMGET(13,0) ||
				 type == ITEMGET(13,1) ||
				 type == ITEMGET(13,2) ||
				 type == ITEMGET(13,8) ||
				 type == ITEMGET(13,9) ||
				 type == ITEMGET(13,12) ||
				 type == ITEMGET(13,13) )
			{
				level = 0;
			}

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y,
				type, level, dur, Option1, Option2, Option3, lpObj->m_Index, ExOption, 0);

			LogAddTD("[Japan1StAnivBox] BoxLevel-%d Event ItemDrop : Item:%d Level:%d op1:%d op2:%d op3:%d ex:%d",
				iBoxLevel, type, level, Option1, Option2, Option3, ExOption);

			return;
		}
	}
	else
	{
		MapC[lpObj->MapNumber].MoneyItemDrop(iDropMoney*iBoxLevel, lpObj->X, lpObj->Y);
	}
}





