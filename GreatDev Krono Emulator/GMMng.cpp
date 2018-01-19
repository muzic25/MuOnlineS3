#include "stdafx.h"
#include "GMMng.h"
#include "LogToFile.h"
#include "logproc.h"
#include "GameMain.h"
#include "protocol.h"
#include "winutil.h"
#include "MoveCommand.h"
#include "GuildClass.h"
#include "TNotice.h"
#include "BattleSoccerManager.h"
#include "giocp.h"
#include "Kanturu.h"
#include "SkillAdditionInfo.h"
#include "GmSystem.h"
// GS-N 0.99.60T 0x004F0110
//	GS-N	1.00.18	JPN	0x00519F60	-	Completed

//Added Review by Hermex
#include "DSProtocol.h"

//CLogToFile KUNDUN_GM_LOG("KUNDUN_EVENT_GM_LOG", ".\\LOG", 1);
CGMMng cManager;

CGMMng::CGMMng()
{
	this->ManagerInit();
}

CGMMng::~CGMMng()
{
	return;
}

void CGMMng::Init()
{
	this->cCommand.Init();
	this->cCommand.Add(lMsg.Get(MSGGET(11, 184)), 100);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 185)), 101);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 186)), 102);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 187)), 103);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 188)), 105);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 189)), 104);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 190)), 106);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 191)), 108);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 192)), 112);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 193)), 111);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 194)), 109);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 195)), 110);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 196)), 390); // /make command

	this->cCommand.Add(lMsg.Get(MSGGET(11, 197)), 201);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 198)), 200);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 199)), 202);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 200)), 203);


	this->cCommand.Add(lMsg.Get(MSGGET(11, 204)), 100);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 205)), 101);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 206)), 102);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 207)), 103);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 208)), 105);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 209)), 104);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 210)), 106);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 211)), 108);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 212)), 112);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 213)), 111);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 214)), 109);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 215)), 110);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 217)), 201);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 218)), 200);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 219)), 202);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 220)), 203);	 

	this->cCommand.Add(lMsg.Get(MSGGET(11, 201)), 214);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 202)), 215);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 203)), 216);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 221)), 214);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 222)), 215);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 223)), 216);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 7)), 218);
	/*// KUNDUN Commands
	this->cCommand.Add("/ÄïµÐ»óÅÂ", 320);	// #translation 
	this->cCommand.Add("/ÄïµÐÇÇ", 321);	// #translation 
	this->cCommand.Add("/ÄïµÐÈ¸º¹·®", 322);	// #translation 
	this->cCommand.Add("/ÄïµÐÃÊ´çÈ¸º¹·®", 323);	// #translation 
	this->cCommand.Add("/ÄïµÐÈ¸º¹½Ã°£", 324);	// #translation 

	// KANTURU Commands
	this->cCommand.Add("/KanturuReady", 369);
	this->cCommand.Add("/KanturuBattleMaya", 370);
	this->cCommand.Add("/¸¶¾ß¸ó½ºÅÍ1", 371);	// #translation 
	this->cCommand.Add("/¸¶¾ß1", 372);	// #translation 
	this->cCommand.Add("/¸¶¾ß¸ó½ºÅÍ2", 373);	// #translation 
	this->cCommand.Add("/¸¶¾ß2", 374);	// #translation 
	this->cCommand.Add("/¸¶¾ß¸ó½ºÅÍ3", 375);	// #translation 
	this->cCommand.Add("/¸¶¾ß3", 376);	// #translation 
	this->cCommand.Add("/¸¶¾ß3¼º°ø", 377);	// #translation 
	this->cCommand.Add(lMsg.Get(MSGGET(13, 60)), 378);	// "/»÷°ÜÂêÑÅÉúÃüÌå"
	this->cCommand.Add("/¸¶¾ß½ÇÆÐ", 379);	// #translation 
	this->cCommand.Add("/KanturuBattleNightmare", 380);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 61)), 381);	// "/»÷°ÜÖäÔ¹Ä§Íõ"
	this->cCommand.Add("/³ªÀÌÆ®¸Þ¾î½ÇÆÐ", 382);	// #translation 
	this->cCommand.Add("/KanturuTower", 383);
	this->cCommand.Add("/KanturuTowerOpen", 384);
	this->cCommand.Add("/KanturuTowerClose", 385);
	this->cCommand.Add("/KanturuEnd", 386);		*/

	this->cCommand.Add(lMsg.Get(MSGGET(13, 57)), 387);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 58)), 388);
	this->cCommand.Add(lMsg.Get(MSGGET(13, 59)), 389);

	this->cCommand.Add(lMsg.Get(MSGGET(11, 183)), 217);	// Fire Cracker Effect	// #translation 
	//Custom commands
	this->cCommand.Add(lMsg.Get(MSGGET(11, 0)), 391);	// PostMsg
	this->cCommand.Add(lMsg.Get(MSGGET(11, 1)), 392);	// ClearPkCommand
	this->cCommand.Add(lMsg.Get(MSGGET(11, 2)), 393);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 3)), 394);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 4)), 395);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 5)), 396);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 6)), 397);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 8)), 398);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 9)), 399);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 10)), 400);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 11)), 401);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 12)), 402);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 13)), 403);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 14)), 404);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 15)), 405);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 16)), 406);
	this->cCommand.Add(lMsg.Get(MSGGET(11, 17)), 407);
	this->WatchTargetIndex = -1;
}


void CGMMng::ManagerInit()
{
	for ( int n = 0;n<MAX_GAME_MASTER ; n++ )
	{
		this->ManagerIndex[n] = -1;
	}
}


int CGMMng::ManagerAdd(char* name, int aIndex)
{
	for ( int n=0 ; n<MAX_GAME_MASTER ; n++ )
	{
		if ( this->ManagerIndex[n] == -1 )
		{
			strcpy(this->szManagerName[n], name);
			this->ManagerIndex[n] = aIndex;
			return n;
		}
	}

	return -1;
}


void CGMMng::ManagerDel(char* name)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++)
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			if ( strcmp(this->szManagerName[n], name) == 0 )
			{
				this->ManagerIndex[n] = -1;
				break;
			}
		}
	}
}


void CGMMng::ManagerSendData(LPSTR szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCServerMsgStringSend(szMsg, this->ManagerIndex[n], 0);
		}
	}
}

void CGMMng::DataSend(unsigned char* szMsg, int size)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			::DataSend(this->ManagerIndex[n], szMsg, size);
		}
	}
}


void CGMMng::BattleInfoSend(char* Name1, BYTE score1, char* Name2, BYTE score2)
{
	for ( int n=0;n<MAX_GAME_MASTER;n++ )
	{
		if ( this->ManagerIndex[n] != -1 )
		{
			GCGoalSend(this->ManagerIndex[n], Name1, score1, Name2, score2);
		}
	}
}


int CGMMng::GetCmd(char* szCmd)
{
	for ( int n	=0; n< MAX_GM_COMMAND ; n++ )
	{
		if ( this->cCommand.nCmdCode[n] > 0 )
		{
			if ( stricmp(szCmd, this->cCommand.szCmd[n]) == 0 )
			{
				return this->cCommand.nCmdCode[n];
			}
		}
	}

	return 0;
}



char* CGMMng::GetTokenString()
{
	char seps[2] = " ";
	return strtok(0, seps);
}


int CGMMng::GetTokenNumber()
{
	char seps[2] = " ";
	char * szToken = strtok(0, seps);

	if ( szToken != NULL )
	{
		return atoi(szToken);
	}

	return 0;
}

void ServerMsgSend(LPOBJ lpObj,int Type,char Sender[20],const char*Message,...)
{
	char szBuffer[1024];
	va_list pArguments;
	va_start(pArguments,Message);
	vsprintf(szBuffer,Message,pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*)malloc(200);
	memset(Packet,0x00,200);
	*Packet = 0xC1;
	if(Type)*(Packet+2)=0x02;
	else *(Packet+2)=0x00;
	memcpy((Packet+3),Sender,strlen(Sender));
	memcpy((Packet+13),szBuffer,strlen(szBuffer));
	int Len = (strlen(szBuffer)+0x13);
	*(Packet+1)=Len;
	if(!lpObj)DataSendAll(Packet,Len);
	else if(lpObj->Connected)
	DataSend(lpObj->m_Index,Packet,Len);
	free(Packet);
}

int CGMMng::ManagementProc(LPOBJ lpObj, char* szCmd, int aIndex)
{
	char seps[2] = " ";
	char * szCmdToken;
	char string[256];
	char szId[20];
	char * pId = szId;
	int len = strlen(szCmd);
	int command_number;

	if ( len < 1 || len > 250 )
	{
		return 0;
	}

	memset(szId, 0, sizeof(szId));
	strcpy(string, szCmd);
	szCmdToken = strtok(string, seps);
	command_number = this->GetCmd(szCmdToken);

	switch (command_number)
	{
	case 217:	//116:
	{
		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "FIRECRACK.");
		int x = lpObj->X;
		int y = lpObj->Y;
		PMSG_SERVERCMD pMsg;

		PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x40, sizeof(pMsg));
		pMsg.CmdType = 0;

		for (int i = 0; i < 15; i++)
		{
			pMsg.X = x + (rand() % 5) * 2 - 4;
			pMsg.Y = y + (rand() % 5) * 2 - 4;
			MsgSendV2(lpObj, (UCHAR*)&pMsg, sizeof(pMsg));
			::DataSend(lpObj->m_Index, (UCHAR*)&pMsg, sizeof(pMsg));
		}
	}
	break;

	case 216:	//115:
	{
		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{
			return 0;
		}

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		LPOBJ lpTargetObj = gObjFind(pId);

		if (lpTargetObj == NULL)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]	[ %s ]	[ %s ] / Target : [%s][%s] : %s ",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
			lpTargetObj->Name, "User Watching");

		char szTemp[256];

		if (this->WatchTargetIndex == lpTargetObj->m_Index)
		{
			this->WatchTargetIndex = -1;

			wsprintf(szTemp, "%s : You can not watch yourself", lpTargetObj->Name);	// #translation
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		}
		else
		{
			wsprintf(szTemp, "%s : Watching User", lpTargetObj->Name);	// #translation
			GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
			this->WatchTargetIndex = lpTargetObj->m_Index;
		}
	}
	break;

	case 218:
	{
		char Msg[100];

		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{	
			return 0;
		}

		if (!GMSystem.IsCommand(lpObj, COMMAND_STATS))
		{
			GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
			return 0;
		}

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		LPOBJ lpTargetObj = gObjFind(pId);

		if (lpTargetObj == NULL)
		{
			sprintf(Msg, "[Status] User %s Offline", pId);
			GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
			return 0;
		}

		sprintf(Msg, "IP Address: %s", lpTargetObj->Ip_addr);
		GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		sprintf(Msg, "Account: %s | Character: %s", lpTargetObj->AccountID, lpTargetObj->Name);
		GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		sprintf(Msg, "Level: %d | Zen: %d | Resets: %d", lpTargetObj->Level, lpTargetObj->Money, 0); //Need toadd resets
		GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		sprintf(Msg, "Map: %d(%d,%d)", lpTargetObj->MapNumber, lpTargetObj->X, lpTargetObj->Y);
		GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		sprintf(Msg, "[Status][GM] %s get your status!", lpObj->Name);
		GCServerMsgStringSend(Msg, lpTargetObj->m_Index, 1);
	}
	break;

	case 215:	//114:
	{
		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{
			return 0;
		}

		if (!GMSystem.IsCommand(lpObj, COMMAND_TRACE))
		{
			GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
			return 0;
		}


		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int map;
		int iX;
		int iY;
		LPOBJ lpTargetObj = gObjFind(pId);
		int iIndex;

		if (lpTargetObj == NULL)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
			lpTargetObj->Name, "User Tracking");
		map = lpTargetObj->MapNumber;
		iX = lpTargetObj->X;
		iY = lpTargetObj->Y;
		iIndex = lpObj->m_Index;

		if (iIndex >= 0)
		{
			gObjTeleport(iIndex, map, iX, iY);
		}
	}
	break;

	case 214:	//113:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"User Stat (connection)");

		int lc151 = 0;
		int lc152 = 400;
		int iTokenNumber = this->GetTokenNumber();

		if (iTokenNumber > 0)
		{
			lc151 = iTokenNumber;
		}

		int iTokenNumber2 = this->GetTokenNumber();

		if (iTokenNumber2 > 0)
		{
			lc152 = iTokenNumber2;
		}

		gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
	}
	break;

	case 100:	//100:
	{
		if ((lpObj->AuthorityCode & 4) != 4)
		{
			return 0;
		}

		if (!GMSystem.IsCommand(lpObj, COMMAND_DISK))
		{
			GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
			return 0;
		}

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int iTargetIndex = gObjGetIndex(pId);


		if (iTargetIndex >= 0)
		{
			LPOBJ lpTargetObj = gObjFind(pId);

			if (lpTargetObj == NULL)
			{
				return 0;
			}

			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
				lpTargetObj->Name, "User Disconnect");
			LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
			CloseClient(iTargetIndex);
		}
	}
	break;

	case 112:	//108:
	{
		if ((lpObj->AuthorityCode & 4) != 4)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"Guild Disconnect");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		_GUILD_INFO_STRUCT * lpGuild = Guild.SearchGuild(pId);
		int iIndex;

		if (lpGuild != NULL)
		{
			for (int i = 0; i < MAX_USER_GUILD; i++)
			{
				if (lpGuild->Index[i] >= 0)
				{
					iIndex = lpGuild->Index[i];

					if (iIndex >= 0)
					{
						LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
						CloseClient(iIndex);
					}
				}
			}
		}
	}
	break;

	case 101:	//101:
	{
		pId = this->GetTokenString();
		
		if (pId != NULL)
		{
			int lc165 = -1;
			int lc166 = 0;
			int lc167 = 0;

			if (lpObj->Teleport != 0)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			if ((lpObj->m_IfState.use) != 0)
			{
				if (lpObj->m_IfState.type == 3)
				{
					lpObj->TargetShopNumber = -1;
					lpObj->m_IfState.type = 0;
					lpObj->m_IfState.use = 0;
				}
			}

			if (lpObj->m_IfState.use > 0)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			if (gObj[aIndex].IsInBattleGround != false)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(6, 68)), lpObj->m_Index, 1);
				return 0;
			}

			if (lpObj->m_PK_Level >= 6)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(4, 101)), lpObj->m_Index, 1);
				return 0;
			}


			BOOL bPlayerKiller = FALSE; //Season 2.5 add-on

			if (gObj[aIndex].PartyNumber >= 0) //Season 2.5 add-on
			{
				if (gParty.GetPkLevel(gObj[aIndex].PartyNumber) >= 5)
				{
					bPlayerKiller = TRUE;
				}
			}
			else if (gObj[aIndex].m_PK_Level >= 5)
			{
				bPlayerKiller = TRUE;
			}

			if (bPlayerKiller == TRUE)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(4, 101)), lpObj->m_Index, 1);
				return 0;
			}

			gMoveCommand.Move(lpObj, pId);
		}
	}
	break;

	case 108:	//104:
	{
		if ((lpObj->AuthorityCode & 8) != 8)
		{
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
			lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
			"Guild SetPosition");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return 0;
		}

		int iTokenNumber1 = this->GetTokenNumber();
		int iTokenNumber2 = this->GetTokenNumber();
		int iTokenNumber3 = this->GetTokenNumber();
		_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(pId);
		int iIndex;

		if (lpGuild != NULL)
		{
			for (int i = 0; i < MAX_USER_GUILD; i++)
			{
				if (lpGuild->Index[i] >= 0)
				{
					iIndex = lpGuild->Index[i];
					gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2++, iTokenNumber3);
				}
			}
		}
	}
	break;

	case 109:	//105:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Start BattleSoccer");

			BattleSoccerGoalStart(0);
		}
	}
	break;

	case 110:	//106:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,
				"Stop BattleSoccer");

			BattleSoccerGoalEnd(0);
		}
		else
		{
			if (gObj[aIndex].lpGuild != NULL)
			{
				if (gObj[aIndex].lpGuild->WarType == 1)
				{
					strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]);
				}
			}
		}
	}

	break;

	case 111:	//107:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, "End GuildWar");

			char * szGuild = this->GetTokenString();

			if (szGuild != NULL)
			{
				GCManagerGuildWarEnd(szGuild);
			}
		}
		else
		{
			if (gObj[aIndex].lpGuild != NULL && gObj[aIndex].lpGuild->lpTargetGuildNode != NULL)
			{
				if (strcmp(gObj[aIndex].Name, gObj[aIndex].lpGuild->Names[0]) == 0)
				{
					if (gObj[aIndex].lpGuild->BattleGroundIndex >= 0 && gObj[aIndex].lpGuild->WarType == 1)
					{
						::gObjAddMsgSendDelay(&gObj[aIndex], 7, aIndex, 10000, 0);

						char szTemp[100];

						wsprintf(szTemp, lMsg.Get(MSGGET(4, 129)), gObj[aIndex].lpGuild->Names[0]);
						::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild, szTemp, 1);
						::GCServerMsgStringSendGuild(gObj[aIndex].lpGuild->lpTargetGuildNode, szTemp, 1);
					}
				}
			}
		}
	}
	break;

	case 104:	//102:
	{

		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{
			return 0;
		}

		if (!GMSystem.IsCommand(lpObj, COMMAND_BANCHAT))
		{
			GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "Ban Chatting");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return FALSE;
		}

		int Index = ::gObjGetIndex(pId);

		if (Index >= 0)
		{
			gObj[Index].Penalty |= 2;
		}

	}
	break;

	case 106:	//103:
	{
		if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
		{
			return 0;
		}

		if ((lpObj->AuthorityCode & 32) != 32)
		{
			return FALSE;
		}

		if (!GMSystem.IsCommand(lpObj, COMMAND_UNBANCHAT))
		{
			GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
			return 0;
		}

		LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "Free Ban-Chatting");

		pId = this->GetTokenString();

		if (pId == NULL)
		{
			return FALSE;
		}

		int Index = ::gObjGetIndex(pId);

		if (Index >= 0)
		{
			gObj[Index].Penalty &= ~2;
		}
	}
	break;

	case 200:	//109:
	{
		pId = this->GetTokenString();

		if (pId != NULL)
		{
			if (strlen(pId) >= 1)
			{
				::GCGuildWarRequestResult(pId, aIndex, 0);
			}
		}
	}

	break;

	case 202:	//111:
	{
		if ((lpObj->Authority & 2) == 2)
		{
			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
				lpObj->Name, "Set GuildWar");

			pId = this->GetTokenString();

			if (pId != NULL)
			{
				char * Rival = this->GetTokenString();

				if (Rival != NULL)
				{
					if (strlen(pId) >= 1)
					{
						if (strlen(Rival) >= 1)
						{
							::GCManagerGuildWarSet(pId, Rival, 1);
						}
					}
				}
			}
		}
		else
		{
			if (Configs.gEnableBattleSoccer != FALSE)
			{
				pId = this->GetTokenString();

				if (pId != NULL)
				{
					if (strlen(pId) >= 1)
					{
						::GCGuildWarRequestResult(pId, aIndex, 1);
					}
				}
			}
		}
	}

	break;

	case 201:	//110:
	{
		//	gObjBillRequest(&gObj[aIndex]);
	}
	break;

	case 203:	//112:
	{
		pId = this->GetTokenString();

		if (pId != NULL)
		{
			BOOL bState;

			if (strcmp(pId, "on") == 0)
			{
				bState = TRUE;
			}
			else if (strcmp(pId, "off") == 0)
			{
				bState = FALSE;
			}

			if (bState >= FALSE && bState <= TRUE)
			{
				::gObjSetTradeOption(aIndex, bState);
				::gObjSetDuelOption(aIndex, bState);
			}
		}
	}
	break;
	case 320:	//117:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return FALSE;
		}

		LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "BOSS HP STATUS");	// #translation Require Translation

		for (int n = 0; n < MAX_VIEWPORT; n++)
		{
			if (lpObj->VpPlayer[n].state != 0)
			{
				if (lpObj->VpPlayer[n].type == OBJ_MONSTER)
				{
					if (lpObj->VpPlayer[n].number >= 0)
					{
						LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

						if (lpTarget->Class == 275)
						{
							TNotice pNotice(1);

							pNotice.SendToUser(lpObj->m_Index, "Kundun HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); //Require Translation
							pNotice.SendToUser(lpObj->m_Index, "Kundun HP time = %d Recover = %d Recovery Time = %d", Configs.giKundunRefillHPSec, Configs.giKundunRefillHP, Configs.giKundunRefillHPTime);	// Require Translation
						}
					}
				}
			}
		}

	}
	break;

	case 321:	//118:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return FALSE;
		}

		LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "BOSS HP CHANGE");	// Require Translation

		int iLife = this->GetTokenNumber();

		for (int n = 0; n < MAX_VIEWPORT; n++)
		{
			if (lpObj->VpPlayer[n].state != FALSE)
			{
				if (lpObj->VpPlayer[n].type == OBJ_MONSTER)
				{
					if (lpObj->VpPlayer[n].number >= 0)
					{
						LPOBJ lpTarget = &gObj[lpObj->VpPlayer[n].number];

						if (lpTarget->Class == 275)
						{
							if (iLife <= 5000)
							{
								iLife = 5000;
							}

							if (iLife > lpTarget->MaxLife)
							{
								iLife = lpTarget->MaxLife;
							}

							lpTarget->Life = iLife;

							TNotice pNotice(1);

							pNotice.SendToUser(lpObj->m_Index, "BOSS HP = %7.0f / %7.0f", lpTarget->Life, lpTarget->MaxLife); //Require Translation
						}
					}
				}
			}
		}
	}
	break;
#pragma message ("Translate start here!")
	case 322:	//119:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return FALSE;
		}

		LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "ÄïµÐHPÈ¸º¹·®¼³Á¤");	// Require Translation

		int RefillHP = this->GetTokenNumber();

		if (RefillHP <= 0 || RefillHP > 5000000)
		{
			return 0;
		}

		Configs.giKundunRefillHP = RefillHP;

		TNotice pNotice(0);

		pNotice.SendToUser(lpObj->m_Index, "ÄïµÐ HP ÃÊ´çÈ¸º¹·® = %d È¸º¹·® = %d È¸º¹½Ã°£ = %d", Configs.giKundunRefillHPSec, Configs.giKundunRefillHP, Configs.giKundunRefillHPTime);	// Require Translation

	}

	break;

	case 323:	//120:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return FALSE;
		}

		LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "ÄïµÐHPÃÊ´çÈ¸º¹·®¼³Á¤");	// Require Translation

		int RefillHPSec = this->GetTokenNumber();

		if (RefillHPSec <= 0 || RefillHPSec > 10000)
		{
			return 0;
		}

		Configs.giKundunRefillHPSec = RefillHPSec;

		TNotice pNotice(0);

		pNotice.SendToUser(lpObj->m_Index, "ÄïµÐ HP ÃÊ´çÈ¸º¹·® = %d È¸º¹·® = %d È¸º¹½Ã°£ = %d",
			Configs.giKundunRefillHPSec, Configs.giKundunRefillHP, Configs.giKundunRefillHPTime);	// Require Translation

	}

	break;

	case 324:	//121:
	{
		if ((lpObj->Authority & 2) != 2)
		{
			return FALSE;
		}

		LogAddTD("[KUNDUN] Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] : %s", lpObj->Ip_addr, lpObj->AccountID,
			lpObj->Name, "ÄïµÐHPÈ¸º¹½Ã°£¼³Á¤");	// Require Translation

		int RefillHPTime = this->GetTokenNumber();

		if (RefillHPTime < 0 || RefillHPTime > 60000)
		{
			return 0;
		}

		Configs.giKundunRefillHPTime = RefillHPTime;

		TNotice pNotice(0);

		pNotice.SendToUser(lpObj->m_Index, "ÄïµÐ HP ÃÊ´çÈ¸º¹·® = %d È¸º¹·® = %d È¸º¹½Ã°£ = %d", Configs.giKundunRefillHPSec, Configs.giKundunRefillHP, Configs.giKundunRefillHPTime);	// Require Translation
#pragma message ("Translate end here")
	}
	break;
	case 369:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 0);
		break;
	case 370:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 1);
		break;
	case 371:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 2);
		break;
	case 372:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 3);
		break;
	case 373:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 4);
		break;
	case 374:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 5);
		break;
	case 375:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 6);
		break;
	case 376:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 7);
		break;
	case 377:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 8);
		break;
	case 378:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 9);
		break;
	case 379:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 10);
		break;
	case 380:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 11);
		break;
	case 381:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 12);
		break;
	case 382:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 13);
		break;
	case 383:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 14);
		break;
	case 384:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 15);
		break;
	case 385:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 16);
		break;
	case 386:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 17);
		break;
	case 387:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 18);
		break;
	case 388:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 19);
		break;
	case 389:
		g_Kanturu.OperateGmCommand(lpObj->m_Index, 20);
		break;
	
		case 390:
		{
			if (Configs.Drop == 0)
			{
				return 0;
			}

			if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_DROP))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			int type, index,ItemLevel,ItemSkill,ItemLuck,ItemOpt,ItemExc,ItemAncient;
			type = GetTokenNumber();
			index = GetTokenNumber();
			ItemLevel = GetTokenNumber();
			ItemSkill = GetTokenNumber();
			ItemLuck = GetTokenNumber();
			ItemOpt = GetTokenNumber();
			ItemExc = GetTokenNumber();
			ItemAncient = GetTokenNumber();
		
			if (index < 0 ||
				(type  < 0 || type  > 15) ||
				(ItemLevel < 0 || ItemLevel > 13) ||
				(ItemOpt   < 0 || ItemOpt   > 7) ||
				(ItemLuck  < 0 || ItemLuck  > 1) ||
				(ItemSkill < 0 || ItemSkill > 1) ||
				(ItemExc   < 0 || ItemExc   > 63) ||
				(ItemAncient   < 0 || ItemAncient   > 40))
			{
				GCServerMsgStringSend("Invalid Item.", lpObj->m_Index, 1);
				return 0;
			}


			if( (type >= 0 && type <= 15) )
			{
				int Item = ItemGetNumberMake( type, index);
				ItemSerialCreateSend(aIndex, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y, Item,ItemLevel,0,ItemSkill,ItemLuck,ItemOpt,-1,ItemExc,ItemAncient);
			}

		}
		break;
		case 391:
		{
			if (Configs.CmdPostEnabled == 1)
			{

				if (lpObj->Level < Configs.CmdPostLevel)
				{
					char levelmsg[100];
					sprintf(levelmsg, "[Global]: to use /post you need level %d ", Configs.CmdPostLevel);
					GCServerMsgStringSend(levelmsg, aIndex, 1);
					return FALSE;
				}

				if (lpObj->Money < Configs.CmdPostMoney)
				{
					GCServerMsgStringSend(lMsg.Get(MSGGET(14, 67)), aIndex, 1);
					return FALSE;
				}
	
				lpObj->Money -= Configs.CmdPostMoney;
				GCMoneySend(lpObj->m_Index, lpObj->Money);

				/*
				char Message[255];
				sprintf(Message, " <Post> %s",(char*)szCmd+strlen("/post"));

				char szBuffer[1024];
				va_list pArguments;
				va_start(pArguments,Message);
				vsprintf(szBuffer,Message,pArguments);
				va_end(pArguments);
				BYTE *Packet;
				Packet = (BYTE*)malloc(200);
				memset(Packet,0x00,200);
				*Packet = 0xC1;
				if(1)*(Packet+2)=0x02;
				else *(Packet+2)=0x00;
				memcpy((Packet+3),lpObj->Name,strlen(lpObj->Name));
				memcpy((Packet+13),szBuffer,strlen(szBuffer));
				int Len = (strlen(szBuffer)+0x13);
				*(Packet+1)=Len;
				if(!lpObj)DataSendAll(Packet,Len);
				else
				if(lpObj->Connected)
				::DataSend(lpObj->m_Index,Packet,Len);
				free(Packet);*/
				/*switch (Configs.CmdPostColor)
				{
				case 0:
					//wsprintf(szTemp, "[POST] %s:%s", lpObj->Name, (char*)szCmd + strlen(szCmdToken));
					ServerMsgSend(0, 1, lpObj->Name, "[POST]%s", (char*)szCmd + strlen("/post"));
					//this->MessageAll(2, 1, lpObj->Name, szTemp);
					break;
				case 1:
					//wsprintf(szTemp, "~[POST] %s:%s", lpObj->Name, (char*)szCmd + strlen(szCmdToken));
					ServerMsgSend(0, 1, lpObj->Name, "~[POST]%s", (char*)szCmd + strlen("/post"));
					//this->MessageAll(2, 1, lpObj->Name, szTemp);
					break;
				case 2:
					//wsprintf(szTemp, "@[POST] %s:%s", lpObj->Name, (char*)szCmd + strlen(szCmdToken));
					ServerMsgSend(0, 1, lpObj->Name, "@[POST]%s", (char*)szCmd + strlen("/post"));
					//this->MessageAll(2, 1, lpObj->Name, szTemp);
					break;
				}*/

				if (Configs.CmdPostAF > 0)
				{
					if (lpObj->aFloodPostCmd != 0)
					{
						GCServerMsgStringSend("You must wait before use post command again", lpObj->m_Index, 1);
						return FALSE;
					}
					lpObj->aFloodPostCmd = Configs.CmdPostAF;
				}

				ServerMsgSend(0, 1, lpObj->Name, "[POST]%s", (char*)szCmd + strlen("/post"));

				char timeStr[9];
				_strtime(timeStr);
				char iPostLog[200];
				sprintf(iPostLog, "%s [%s]: <Post> %s", timeStr, lpObj->Name, (char*)szCmd + strlen("/post"));
				LogAddC(3, iPostLog);
				return TRUE;
			}
		}
		break;
		case 392:
		{
			if (Configs.PkClearEnabled == 0)
			{
				return 0;
			}


			if (Configs.PkClearOnlyForGm == 1)
			{
				if ((lpObj->Authority & 2) != 2 && (lpObj->Authority & 0x20) != 0x20)
				{
					return 0;
				}
			}
			if (lpObj->Level < Configs.PkClearLevelReq)
			{
				char levelmsg[100];
				sprintf(levelmsg, "[Global]: to use /post you need level %d ", Configs.CmdPostLevel);
				GCServerMsgStringSend(levelmsg, aIndex, 1);
				return FALSE;
			}

			if (lpObj->Money < Configs.PkClearPriceZen)
			{
				GCServerMsgStringSend(lMsg.Get(MSGGET(14, 67)), aIndex, 1);
				return FALSE;
			}

			if (lpObj->m_PK_Level <= 3)
			{
				char Msg[100] = "You're not PK!";
				GCServerMsgStringSend(Msg, aIndex, 1);
				return TRUE;
			}
			else if (lpObj->Money < lpObj->m_PK_Level * Configs.PkClearPriceZen)
			{
				char Msg[100] = "You do not have enough Zen!";
				GCServerMsgStringSend(Msg, aIndex, 1);
				return TRUE;
			}
			else if (lpObj->Money >= lpObj->m_PK_Level * Configs.PkClearPriceZen)
			{
				lpObj->Money -= lpObj->m_PK_Level * Configs.PkClearPriceZen;
				GCMoneySend(lpObj->m_Index, lpObj->Money);
				lpObj->m_PK_Level = 3;
				GCPkLevelSend(lpObj->m_Index, 3);
				char Msg[100] = "PK status removed.";
				GCServerMsgStringSend(Msg, aIndex, 1);

				char timeStr[9];
				_strtime(timeStr);
				char LinhaLog[200];
				sprintf(LinhaLog, "%s [PK SYSTEM CMD][%s][%s] PK clear success.", timeStr, lpObj->AccountID, lpObj->Name);
				LogAddC(7, LinhaLog);
			}
			return TRUE;
		}
			break;
		case 393:
		{
			if (Configs.AddPointEnabled == 0)
			{
				return 0;
			}

			int Pontos;
			Pontos = GetTokenNumber();
			if(Pontos == NULL)
			{
				GCServerMsgStringSend("[CmdAdd]: syntax error",lpObj->m_Index,1);
				return FALSE;
			}
			if(lpObj->LevelUpPoint < Pontos || Pontos < 1)
			{
				GCServerMsgStringSend("[CmdAdd]: not enough points.",lpObj->m_Index,1);
				return FALSE;
			}
			if((Pontos + lpObj->Strength) > Configs.g_CharMaxStat)
			{
				GCServerMsgStringSend("[CmdAdd]: Cant add more than 32767!.",lpObj->m_Index,1);
				return FALSE;
			}
			lpObj->LevelUpPoint -= Pontos;
			lpObj->Strength += Pontos;
			char Msg[100];
			sprintf(Msg, "[CmdAdd]: Points added [%d] to strength.", Pontos);
			GCServerMsgStringSend(Msg,lpObj->m_Index,1);
			gObjCalCharacter(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);

			if (Pontos > 200)
			{
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			else
			{
				BYTE lpMsg[5] = { 0xC1,0x05,0xF3,0x06,0x00 };
				for (UINT i = 0; i < Pontos; i++)
				{
					CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index);
				}
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}

			return TRUE;
		}
			break;
		case 394:
		{
			if (Configs.AddPointEnabled == 0)
			{
				return 0;
			}

			int Pontos;
			Pontos = GetTokenNumber();
			if(Pontos == NULL)
			{
				GCServerMsgStringSend("[CmdAdd]: syntax error.",lpObj->m_Index,1);
				return FALSE;
			}
			if(lpObj->LevelUpPoint < Pontos || Pontos < 1)
			{
				GCServerMsgStringSend("[CmdAdd]: add more than 0 points.",lpObj->m_Index,1);
				return FALSE;
			}
			if((Pontos + lpObj->Dexterity) > Configs.g_CharMaxStat)
			{
				char Msg[100];
				sprintf(Msg, "[CmdAdd]: Cant add more than %d!.", Configs.g_CharMaxStat);
				GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
				return FALSE;
			}

			lpObj->LevelUpPoint -= Pontos;
			lpObj->Dexterity += Pontos;
			char Msg[100];
			sprintf(Msg, "[CmdAdd]: Points added [%d] to Agility.", Pontos);
			GCServerMsgStringSend(Msg,lpObj->m_Index,1);
			gObjCalCharacter(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
			GCManaSend(lpObj->m_Index, lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
			if (Pontos > 200)
			{
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			else
			{
				BYTE lpMsg[5] = { 0xC1,0x05,0xF3,0x06,0x01 };
				for (UINT i = 0; i < Pontos; i++)
				{
					CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index);
				}
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			return TRUE;
		}
			break;
		case 395:
		{
			if (Configs.AddPointEnabled == 0)
			{
				return 0;
			}

			int Pontos;
			Pontos = GetTokenNumber();
			if(Pontos == NULL)
			{
				GCServerMsgStringSend("[CmdAdd]: syntax error.",lpObj->m_Index,1);
				return FALSE;
			}
			if(lpObj->LevelUpPoint < Pontos || Pontos < 1)
			{
				GCServerMsgStringSend("[CmdAdd]: Add more than 0 points",lpObj->m_Index,1);
				return FALSE;
			}
			if((Pontos + lpObj->Vitality) > Configs.g_CharMaxStat)
			{
				char Msg[100];
				sprintf(Msg, "[CmdAdd]: Cant add more than %d!.", Configs.g_CharMaxStat);
				GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
				return FALSE;
			}
			lpObj->LevelUpPoint -= Pontos;
			lpObj->Vitality += Pontos;
			char Msg[100];
			sprintf(Msg, "[CmdAdd]: Added [%d] points on vitality.", Pontos);
			GCServerMsgStringSend(Msg,lpObj->m_Index,1);
			gObjCalCharacter(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
			GCManaSend(lpObj->m_Index, lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
			if (Pontos > 200)
			{
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			else
			{
				BYTE lpMsg[5] = { 0xC1,0x05,0xF3,0x06,0x02 };
				for (UINT i = 0; i < Pontos; i++)
				{
					CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index);
				}
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			return TRUE;
		}
			break;
		case 396:
		{
			if (Configs.AddPointEnabled == 0)
			{
				return 0;
			}

			int Pontos;
			Pontos = GetTokenNumber();
			if(Pontos == NULL)
			{
				GCServerMsgStringSend("[CmdAdd]: Syntax error.",lpObj->m_Index,1);
				return FALSE;
			}
			if(lpObj->LevelUpPoint < Pontos || Pontos < 1)
			{
				GCServerMsgStringSend("[CmdAdd]: add more than 0 point.",lpObj->m_Index,1);
				return FALSE;
			}
			if((Pontos + lpObj->Energy) > Configs.g_CharMaxStat)
			{
				char Msg[100];
				sprintf(Msg, "[CmdAdd]: Cant add more than %d!.", Configs.g_CharMaxStat);
				GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
				return FALSE;
			}
			lpObj->LevelUpPoint -= Pontos;
			lpObj->Energy += Pontos;
			char Msg[100];
			sprintf(Msg, "[CmdAdd]: Added [%d] points on Energy.", Pontos);
			GCServerMsgStringSend(Msg,lpObj->m_Index,1);
			gObjCalCharacter(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
			GCManaSend(lpObj->m_Index, lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
			if (Pontos > 200)
			{
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			else
			{
				BYTE lpMsg[5] = { 0xC1,0x05,0xF3,0x06,0x03 };
				for (UINT i = 0; i < Pontos; i++)
				{
					CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index);
				}
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			return TRUE;
		}
			break;
		case 397:
		{
			if (Configs.AddPointEnabled == 0)
			{
				return 0;
			}

			if(lpObj->DbClass !=64)
			{
				GCServerMsgStringSend("[CmdAdd]: Only Dark Lord Can use /addcmd.",lpObj->m_Index,1);
				return FALSE;
			}

			int Pontos;
			Pontos = GetTokenNumber();
			if(Pontos == NULL)
			{
				GCServerMsgStringSend("[CmdAdd]: Syntax error",lpObj->m_Index,1);
				return FALSE;
			}
			if(lpObj->LevelUpPoint < Pontos || Pontos < 1)
			{
				GCServerMsgStringSend("[CmdAdd]: cant add - point.",lpObj->m_Index,1);
				return FALSE;
			}
			if((Pontos + lpObj->Leadership) > Configs.g_CharMaxStat)
			{
				char Msg[100];
				sprintf(Msg, "[CmdAdd]: Cant add more than %d!.", Configs.g_CharMaxStat);
				GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
				return FALSE;
			}
			lpObj->LevelUpPoint -= Pontos;
			lpObj->Leadership += Pontos;
			char Msg[100];
			sprintf(Msg, "[CmdAdd]: [%d] points added to command.", Pontos);
			GCServerMsgStringSend(Msg,lpObj->m_Index,1);
			gObjCalCharacter(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
			GCManaSend(lpObj->m_Index, lpObj->MaxMana + lpObj->AddMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
			
			if (Pontos > 200)
			{
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			else
			{
				BYTE lpMsg[5] = { 0xC1,0x05,0xF3,0x06,0x04 };
				for (UINT i = 0; i < Pontos; i++)
				{
					CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index);
				}
				GCLevelUpMsgSend(lpObj->m_Index, 0);
			}
			return TRUE;
		}
		break;

		case 398:
		{
			if (Configs.BanChar == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 4) != 4)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_BANPLAYER))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int iTargetIndex = gObjGetIndex(pId);


			if (iTargetIndex >= 0)
			{
				LPOBJ lpTargetObj = gObjFind(pId);

				if (lpTargetObj == NULL)
				{
					return 0;
				}

				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s][%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, lpTargetObj->AccountID,
					lpTargetObj->Name, "User Ban");
				LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
				GJSetStatusBan(pId, 1, 1);
				CloseClient(iTargetIndex);
			}
			else
			{
				LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s] : %s",
					lpObj->Ip_addr, lpObj->AccountID, lpObj->Name,pId, "User Ban");
				LogAdd(lMsg.Get(MSGGET(1, 191)), pId);
				GJSetStatusBan(pId, 1, 1);
			}
			
		}
		break;

		case 399:
		{
			if (Configs.BanChar == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 4) != 4)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_BANPLAYER))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			LogAddTD("Use GM Command -> [ %s ]\t[ %s ]\t[ %s ] / Target : [%s]: %s",
				lpObj->Ip_addr, lpObj->AccountID, lpObj->Name, pId, "User UnBan");
			GJSetStatusBan(pId, 1, 0);
		}
		break;
		case 400://Skin
		{
			if (Configs.SkinEnabled == 0)
			{
				return 0;
			}

			if (Configs.SkinOnlyForGm)
			{
				if ((lpObj->AuthorityCode & 32) != 32)
				{
					return 0;
				}

				if (!GMSystem.IsCommand(lpObj, COMMAND_SKIN))
				{
					GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
					return 0;
				}

				pId = this->GetTokenString();

				if (pId == NULL)
				{
					return 0;
				}

				int NumSkin = 0;
				NumSkin = GetTokenNumber();

				int Index = gObjGetIndex(pId);
				LPOBJ tObj = &gObj[Index];
				gObj[Index].m_Change = NumSkin;
				gObjViewportListProtocolCreate(tObj);
				char Msg[100];
				sprintf(Msg, "[Skin] You successfully change %s Skin.", gObj[Index].Name);
				GCServerMsgStringSend(Msg, lpObj->m_Index, 1);

			}
			else
			{
				if((lpObj->AuthorityCode & 32) == 32 && GMSystem.IsCommand(lpObj, COMMAND_SKIN))
				{ 
					pId = this->GetTokenString();

					if (pId == NULL)
					{
						return 0;
					}

					int NumSkin = 0;
					NumSkin = GetTokenNumber();

					int Index = gObjGetIndex(pId);
					LPOBJ tObj = &gObj[Index];
					gObj[Index].m_Change = NumSkin;
					gObjViewportListProtocolCreate(tObj);
					char Msg[100];
					sprintf(Msg, "[Skin] You successfully change %s Skin.", gObj[Index].Name);
					GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
				}
				else
				{

					if (lpObj->Level < Configs.SkinLevelReq)
					{
						char levelmsg[100];
						sprintf(levelmsg, "[Global]: to use /post you need level %d ", Configs.CmdPostLevel);
						GCServerMsgStringSend(levelmsg, aIndex, 1);
						return FALSE;
					}

					if (lpObj->Money < Configs.SkinPriceZen)
					{
						GCServerMsgStringSend(lMsg.Get(MSGGET(14, 67)), aIndex, 1);
						return FALSE;
					}

					int NumSkin = 0;
					NumSkin = GetTokenNumber();

					if (NumSkin == 0)
					{
						lpObj->m_Change = -1;
						gObjViewportListProtocolCreate(lpObj);
					}
					else
					{
						lpObj->m_Change = NumSkin;
						gObjViewportListProtocolCreate(lpObj);
					}

					lpObj->Money -= Configs.SkinPriceZen;
					GCMoneySend(lpObj->m_Index, lpObj->Money);

					GCServerMsgStringSend("[Skin] Your Skin successfully changed!", lpObj->m_Index, 1);
				}
			}
		}
		break;
		case 401:
		{
			if (Configs.SetZen == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_SETZEN))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int Value = 0;
			Value = GetTokenNumber();

			if (Value < 0 || Value > 2000000000)
			{
				GCServerMsgStringSend("[SetZen] Value can't be less than 0 and more than 2000000000!", lpObj->m_Index, 1);
				return 0;
			}

			int Index = gObjGetIndex(pId);
			gObj[Index].Money = Value;
			GCMoneySend(Index, Value);

			char Msg[100];
			sprintf(Msg, "[SetZen] You sucsessfully changed %s zen.", gObj[Index].Name);
			GCServerMsgStringSend(Msg, lpObj->m_Index, 1);

			//char Msg[100];
			sprintf(Msg, "[SetZen] Your zen was changed to %d by %s.", Value, lpObj->Name);
			GCServerMsgStringSend(Msg, Index, 1);
		}
		break;
		case 402:
		{
			if (Configs.Time == 0)
			{
				return 0;
			}

			SYSTEMTIME t;
			GetLocalTime(&t);
			char Msg[100];
			sprintf(Msg, "Server Date & Time : %02d:%02d:%02d %02d-%02d-%02d.",
				t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
			GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		}
		break;
		case 403:
		{
			if (Configs.Online == 0)
			{
				return 0;
			}

			int totGMs = 0;
			int totPlayers = 0;
			for (short i = OBJMAX - OBJMAXUSER; i< OBJMAX; i++)
			{
				if (gObj[i].Connected == PLAYER_PLAYING)
				{
					if (gObj[i].Authority == 8 || gObj[i].Authority == 32)
					{
						totGMs++;
					}
					if (gObj[i].Authority == 0)
					{
						totPlayers++;
					}
				}
			}

			char Msg[100];
			sprintf(Msg, "[ONLINE]: %d Player(s), %d GM(s)", totPlayers, totGMs);
			GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		}
		break;
		case 404:
		{
			if (Configs.SetPK == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_SETPK))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			pId = this->GetTokenString();

			if (pId == NULL)
			{
				return 0;
			}

			int PkLevel = 0;
			PkLevel = GetTokenNumber();

			int Index = gObjGetIndex(pId);
			gObj[Index].m_PK_Level = PkLevel;
			GCPkLevelSend(Index, PkLevel);

			char Msg[100];
			sprintf(Msg, "[SetPK] You sucsessfully changed %s PK Level. PKLevel: %d", gObj[Index].Name, PkLevel);
			GCServerMsgStringSend(Msg, lpObj->m_Index, 1);
		}
		break;
		case 405:
		{
			if (Configs.Reload == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_RELOAD))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			int NumberReload;
			NumberReload = GetTokenNumber();

			switch (NumberReload)
			{
			case 0:
			{
				ShopDataLoad();
				GCServerMsgStringSend("[Reload] Shops Reloaded.", lpObj->m_Index, 1);
				LogAddTD("[Reload] Shops Reloaded.");
				break;
			}
			case 1:
			{

				break;
			}
			case 2:
			{

				break;
			}
			case 3:
			{
				GMSystem.LoadIniConfig(".\\GMSystem.txt");
				GCServerMsgStringSend("[Reload] GMSystem Reloaded.", lpObj->m_Index, 1);
				LogAddTD("[Reload] GMSystem Reloaded.");
				break;
			}
			case 4:
			{
				break;
			}
			case 5:
			{
				break;
			}
			case 6:
			{
				break;
			}
			default:
			{
				GCServerMsgStringSend("[Reload] Usage: /reload <Number>.", lpObj->m_Index, 1);
				break;
			}
			}
		}
		break;
		case 406:
		{
			if (Configs.Gmove == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_MOVE))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			pId = this->GetTokenString();

			int Map = 0;
			Map = GetTokenNumber();
			BYTE x = 0,	y = 0;
			x = GetTokenNumber();
			y = GetTokenNumber();

			short TargetIndex = gObjGetIndex(pId);

			gObjTeleport(TargetIndex, Map, x, y);

		}
		break;
		case 407:
		{
			if (Configs.GG == 0)
			{
				return 0;
			}

			if ((lpObj->AuthorityCode & 32) != 32)
			{
				return 0;
			}

			if (!GMSystem.IsCommand(lpObj, COMMAND_GG))
			{
				GCServerMsgStringSend("You can't use this command.", lpObj->m_Index, 1);
				return 0;
			}

			char *sztemp;

			sztemp = this->GetTokenString();

			char pBuffer[MAX_CHAT_LEN];
			sprintf(pBuffer, "[%s] %s", lpObj->Name, sztemp);

			for (int n = OBJ_STARTUSERINDEX; n < OBJMAX; n++)
			{
				if (gObj[n].Connected >= PLAYER_PLAYING)
				{
					GCServerMsgStringSend(pBuffer, n, 0);
				}
			}
		}
		break;
	}
	return 0;
}

void CGMMng::GetInfinityArrowMPConsumption(LPOBJ lpObj)
{
	MsgOutput(lpObj->m_Index, "Infinity Arrow MP Consumption [+0:%d] [+1:%d] [+2:%d]",
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1(),
		g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2());
}

void CGMMng::ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus0(iValue);
	MsgOutput(lpObj->m_Index, "ÀÎÇÇ´ÏÆ¼ ¾Ö·Î¿ì MP ¼Ò¸ð·® º¯°æ(+0) : %d",iValue);

}	

void CGMMng::ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus1(iValue);
	MsgOutput(lpObj->m_Index, "ÀÎÇÇ´ÏÆ¼ ¾Ö·Î¿ì MP ¼Ò¸ð·® º¯°æ(+1) : %d",iValue);

}

void CGMMng::ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetInfinityArrowMPConsumptionPlus2(iValue);
	MsgOutput(lpObj->m_Index, "ÀÎÇÇ´ÏÆ¼ ¾Ö·Î¿ì MP ¼Ò¸ð·® º¯°æ(+2) : %d",iValue);

}

void CGMMng::SetInfinityArrowTime(LPOBJ lpObj, int iValue)
{
	if ( lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1 )
	{
		lpObj->m_iMuseElfInfinityArrowSkillTime = iValue;
		MsgOutput(lpObj->m_Index, "ÀÎÇÇ´ÏÆ¼ ¾Ö·Î¿ì ½Ã°£ °­Á¦ ¼³Á¤ : %dÃÊ", iValue);
	}
	else
	{
		MsgOutput(lpObj->m_Index, "220·¹º§ ÀÌ»ó ¹ÂÁî¿¤ÇÁ¸¸ »ç¿ë°¡´ÉÇÕ´Ï´Ù.");
	}
}

void CGMMng::ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue)
{
	g_SkillAdditionInfo.SetFireScreamExplosionAttackDistance(iValue);
	MsgOutput(lpObj->m_Index, "ÆÄÀÌ¾î½ºÅ©¸² ´õºíµ¥¹ÌÁö Æø¹ß°Å¸® º¯°æ:%d", iValue);
}
