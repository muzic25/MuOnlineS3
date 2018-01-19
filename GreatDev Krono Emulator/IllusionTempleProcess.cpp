//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "IllusionTempleEvent.h"
#include "IllusionTempleProcess.h"
#include "GameMain.h"
#include "logproc.h"
#include "winutil.h"
#include "protocol.h"
#include "DSprotocol.h"
#include "JewelOfHarmonySystem.h"
#include "TNotice.h"
#include "ChaosCastle.h"
#include "BloodCastle.h"
#include "Event.h"

std::list<ILLUSIONTEMPLE_START_TIME> m_listIllusionTempleOpenTime;

CIllusionTempleProcess::CIllusionTempleProcess(): m_btFloorIndex(-1), m_btState(0), m_iOpenTickCount(0), m_iStatueCount(0), m_iMonsterCount(0) 
{
	InitializeCriticalSection(&this->m_cs);

	this->m_iEventBattleTimer = -1;

	this->ClearMonstersData();
}

CIllusionTempleProcess::~CIllusionTempleProcess()
{
	DeleteCriticalSection(&this->m_cs);
}

void CIllusionTempleProcess::Init(int FloorIndex)
{
	if(this->m_btFloorIndex == (BYTE)-1)
	{
		this->m_btFloorIndex = FloorIndex;
	}
	
	int i;
	for(i = 0; i < MAX_FLOOR_USER; i++ )
	{
		this->InitFloorData(i);
	}

	this->m_iCloseTickCount = GetTickCount();
	this->m_iBallPlayerIndex = -1;
	this->m_btBallInventoryPosition = (BYTE)-1;
	this->m_btAllowedRegPedestal = (BYTE)-1;
	this->m_iYellowTeamUserCount = 0;
	this->m_iBlueTeamUserCount = 0;
	this->m_btYellowTeamScore = 0;
	this->m_btBlueTeamScore = 0;
	this->m_iStatueRegenTickCount = -1;
	this->m_btWinnerTeam = (BYTE)-1;
	this->m_bOpenStatus = FALSE;
	this->m_iEventBattleTimer = -1;
	this->m_bIllusionTempleEventEnded = FALSE;
	this->m_bMsgBeforeEnterTemple = FALSE;
	this->m_bMsgBeforeEnterBattle = FALSE;
	this->m_iLeftMinutesBeforeEnd = 0;

	this->ResetUserKillCountPoint();

	this->CheckSync();

	this->m_bTimeCheckSync = FALSE;

	for( i = 0; i < MAX_TYPE_PLAYER; i++ )
	{
		this->m_btYellowTeamClassCount[i] = 0;
		this->m_btBlueTeamClassCount[i] = 0;
	}

	this->m_bScoreRankSet = FALSE;
}

void CIllusionTempleProcess::InitFloorData(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	this->m_UserData[aIndex].m_UserIndex = 0;

	this->m_FloorData[aIndex].m_dwShieldSpellTime = 0;

	this->m_FloorData[aIndex].m_dwRestrictionSpellTime = 0;
	this->m_FloorData[aIndex].m_iTeamPlayerIndex = -1;
	this->m_FloorData[aIndex].m_btTeamJoinSide = (BYTE)-1;
	this->m_FloorData[aIndex].m_btUserKillCount = 0;
	this->m_FloorData[aIndex].m_btMonsterRewardKillCount = 0;
	this->m_FloorData[aIndex].m_btPlayerRewardKillCount = 0;
	this->m_FloorData[aIndex].m_btUsedKillCountPoint = 0;

	this->m_FloorData[aIndex].m_i64ExpReward = 0;
	this->m_FloorData[aIndex].m_dwRankingPoint = 0;

	this->m_FloorData[aIndex].m_bDropReward = 0;
}

void CIllusionTempleProcess::CheckSync() 
{
	std::list<ILLUSIONTEMPLE_START_TIME>::iterator it;
	ILLUSIONTEMPLE_START_TIME WebzenVar1;
	ILLUSIONTEMPLE_START_TIME WebzenVar2;
	int BaseTime = 0;
	int CheckTime = 0;
	DWORD CurrentTime = 0;
	
	tm * today;
	time_t ltime;

	int loc12;
	int loc13;

	if(m_listIllusionTempleOpenTime.size() == 0)
	{
		MsgBox("Error : Illusion Temple StartTime size is 0");
		return;
	}

	time(&ltime);
	today = localtime(&ltime);

	
	CurrentTime = (today->tm_hour * 60) + today->tm_min;
	WebzenVar1 = *m_listIllusionTempleOpenTime.begin();

	for( it = m_listIllusionTempleOpenTime.begin(); it != m_listIllusionTempleOpenTime.end(); ++it )
	{
		WebzenVar2 = *it;
		BaseTime = (WebzenVar1.m_iHour * 60) + WebzenVar1.m_iMinute;
		CheckTime =	(WebzenVar2.m_iHour * 60) + WebzenVar2.m_iMinute;

		if( BaseTime == CheckTime )
		{
			if( CurrentTime < CheckTime )
			{
				WebzenVar2 = *it;
				break;
			}
			continue;
		}
		
		if( CurrentTime >= BaseTime && CurrentTime < CheckTime )
		{
			break;
		}
		else
		{
			WebzenVar1 = *it;
		}
	}

	for(loc12 = 2;loc12--;)
	{
		if(it == m_listIllusionTempleOpenTime.end())
		{
			it = m_listIllusionTempleOpenTime.begin();

			WebzenVar2 = (*it);
		}

		CheckTime = WebzenVar2.m_iHour*60+WebzenVar2.m_iMinute;

		if(today->tm_hour <= WebzenVar2.m_iHour)
		{
			this->m_iLeftMinutesBeforeOpen = CheckTime - CurrentTime;
		}
		else
		{
			this->m_iLeftMinutesBeforeOpen = 1440-CurrentTime+CheckTime;
		}

		if(this->m_iLeftMinutesBeforeOpen <= m_i_IT_OpenTime)
		{
			it++;

			if(it != m_listIllusionTempleOpenTime.end())
			{
				WebzenVar2 = (*it);
			}
		}
		else
		{
			break;
		}
	}

	loc13 = GetTickCount();
	this->m_iOpenTickCount = loc13 + (60000 - (today->tm_sec * 1000));

	LogAddTD("[Illusion Temple] (%d) Sync Open Time. [%d]min remain", this->m_btFloorIndex+1, this->m_iLeftMinutesBeforeOpen);
}

void CIllusionTempleProcess::Run(int iTick) 
{
	BYTE State = this->m_btState;

	switch ( State )
	{	
		case 0:	this->ProcState_Closed(iTick);		break;
		case 1:	this->ProcState_Waiting(iTick);		break;
		case 2:	this->ProcState_Playing(iTick);		break;
		case 3: this->ProcState_Playend(iTick);		break;
	}
}

void CIllusionTempleProcess::ProcState_Closed(int iTick) 
{
	int loc2 = iTick - this->m_iCloseTickCount;

	if(this->m_iOpenTickCount < iTick)
	{
		this->m_iLeftMinutesBeforeOpen--;
		this->m_iOpenTickCount = iTick + 60000;

		if(this->m_iLeftMinutesBeforeOpen <= m_i_IT_OpenTime)
		{
			if(this->m_iLeftMinutesBeforeOpen > 0)
			{
				if(this->m_btFloorIndex == 0)
				{
					PMSG_NOTICE pNotice;
					TNotice::MakeNoticeMsgEx(&pNotice, 0, lMsg.Get(3394), this->m_iLeftMinutesBeforeOpen);
					this->SendAllUserAnyMsg((LPBYTE)&pNotice, pNotice.h.size);
				}
			}
		}
	}

	if(loc2 >= 1000)
	{
		if(this->m_iEventBattleTimer > 0)
		{
			this->m_iEventBattleTimer -= loc2;
		}

		this->m_iCloseTickCount = iTick;

		if(this->m_iLeftMinutesBeforeOpen <= m_i_IT_OpenTime+1)
		{
			if(this->m_iEventBattleTimer == -1)
			{
				this->m_iEventBattleTimer = 1000 * ( (m_i_IT_OpenTime+1) * 60);
			}
		}

		if(this->m_iLeftMinutesBeforeOpen <= m_i_IT_OpenTime)
		{
			if(this->m_iEventBattleTimer > 5000)
			{
				if(this->m_bOpenStatus == FALSE)
				{
					this->m_bOpenStatus = TRUE;
				}
			}
		}

		if(this->m_iEventBattleTimer <= 30000 && this->m_iEventBattleTimer > 0)
		{
			if(this->m_btFloorIndex == 0)
			{
				if(this->m_bMsgBeforeEnterTemple == FALSE)
				{
					this->m_bMsgBeforeEnterTemple = TRUE;

					PMSG_SET_DEVILSQUARE pMsg;

					PHeadSetB((LPBYTE)&pMsg, 0x92, sizeof(pMsg));
					pMsg.Type = 14;

					for (int i= OBJ_STARTUSERINDEX;i<OBJMAX;i++)
					{
						if ( gObj[i].Connected == PLAYER_PLAYING && gObj[i].Type == OBJ_USER)
						{
							if ( BC_MAP_RANGE(gObj[i].MapNumber) == FALSE )
							{
								if ( CC_MAP_RANGE(gObj[i].MapNumber) == FALSE )
								{
									DataSend(i, (LPBYTE)&pMsg, pMsg.h.size);
								}
							}
						}
					}
				}
			}
		}

		if(this->m_iEventBattleTimer <= 5000)
		{
			if(this->m_bOpenStatus == TRUE)
			{
				this->m_bOpenStatus = FALSE;

				if(this->m_btFloorIndex == 0)
				{
					PMSG_NOTICE pNotice;
					TNotice::MakeNoticeMsgEx(&pNotice, 0, lMsg.Get(3395));
					this->SendAllUserAnyMsg((LPBYTE)&pNotice, pNotice.h.size);
				}
			}
		}
	}


	if(this->m_iLeftMinutesBeforeOpen <= 0)
	{
		if(this->m_iEventBattleTimer <= 0)
		{
			this->m_bOpenStatus = FALSE;

			this->RemoveInvalid();

			if(this->m_iEnteredUserCount < m_i_IT_MinPlayer) //UserCount
			{
				for( int n = 0; n < MAX_FLOOR_USER; n++ )
				{
					if( this->m_FloorData[n].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[n].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
					{
						if( gObj[this->m_FloorData[n].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
						{
							int loc142 = this->m_FloorData[n].m_btPosNDur;

							if(loc142 > -1)
							{
								if(gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Type == ITEMGET(13,51))
								{
									gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Durability = 1.0f;
									GCItemDurSend(gObj[this->m_FloorData[n].m_iTeamPlayerIndex].m_Index, loc142,  gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Durability, 0);
								}
								else if(gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Type == ITEMGET(13,61))
								{
									gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Durability += 1.0f;
									GCItemDurSend(gObj[this->m_FloorData[n].m_iTeamPlayerIndex].m_Index, loc142,  gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Durability, 0);
								}

								LogAddTD("[Illusion Temple] (%d) Payback to User (%s)(%s) 피의 두루마리 (Serial:%u)", this->m_btFloorIndex+1, gObj[this->m_FloorData[n].m_iTeamPlayerIndex].AccountID, gObj[this->m_FloorData[n].m_iTeamPlayerIndex].Name, gObj[this->m_FloorData[n].m_iTeamPlayerIndex].pInventory[loc142].m_Number);
							}
							else
							{
								LogAddTD("[Illusion Temple] (%d) Payback to User Failed (%s)(%s) Scroll Not Found", this->m_btFloorIndex+1, gObj[this->m_FloorData[n].m_iTeamPlayerIndex].AccountID, gObj[this->m_FloorData[n].m_iTeamPlayerIndex].Name);
							}
							gObjMoveGate(this->m_FloorData[n].m_iTeamPlayerIndex, 22); //Devias
						}
					}
				}

				LogAddTD("[Illusion Temple] (%d) Failed to Start Illusion Temple (UserCount: %d)", this->m_btFloorIndex+1, this->m_iEnteredUserCount);
				this->SetState(3);
				return;
			}
			
			int loc143 = 0;
			int loc144 = -1;
			int loc145 = -1;

			char szTemp0[256];
			sprintf(szTemp0,"[Illusion Temple] (%d) [AlliedTeam] ", this->m_btFloorIndex+1);

			char szTemp1[256];
			sprintf(szTemp1,"[Illusion Temple] (%d) [IllusiondTeam] ", this->m_btFloorIndex+1);

			for( int loc274 = 0; loc274 < MAX_FLOOR_USER; loc274++)
			{
				if( this->m_FloorData[loc274].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].m_iIllusionTempleIndex == loc274)
				{
					if( gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class >= MAX_TYPE_PLAYER || gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class < 0)
					{
						continue;
					}

					int loc275 = this->m_FloorData[loc274].m_btPosNDur; //season 3.0 changed

					if(loc275 > -1)
					{
						if(gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].pInventory[loc275].m_Durability <= 0.0f) //season 3.0 add-on
						{
							if(gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].pInventory[loc275].m_Type == ITEMGET(13,51))
							{
								gObjInventoryDeleteItem(this->m_FloorData[loc274].m_iTeamPlayerIndex, loc275);
								GCInventoryItemDeleteSend(this->m_FloorData[loc274].m_iTeamPlayerIndex, loc275, 0);
							}
							else if(gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].pInventory[loc275].m_Type == ITEMGET(13,61))
							{
								if(gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].pInventory[loc275].m_Durability <= 0.0f)
								{
									gObjInventoryDeleteItem(this->m_FloorData[loc274].m_iTeamPlayerIndex, loc275);
									GCInventoryItemDeleteSend(this->m_FloorData[loc274].m_iTeamPlayerIndex, loc275, 0);
								}
							}
						}
					}

					if(this->m_btYellowTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class] == this->m_btBlueTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class])
					{
						if(this->m_iYellowTeamUserCount == this->m_iBlueTeamUserCount)
						{
							this->m_FloorData[loc274].m_btTeamJoinSide = rand()%2;
						}
						else if(this->m_iYellowTeamUserCount > this->m_iBlueTeamUserCount)
						{
							this->m_FloorData[loc274].m_btTeamJoinSide = 1;
						}
						else
						{
							this->m_FloorData[loc274].m_btTeamJoinSide = 0;
						}
					}
					else if(this->m_btYellowTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class] < this->m_btBlueTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class])
					{
						if(this->m_iYellowTeamUserCount > this->m_iBlueTeamUserCount)
						{
							this->m_FloorData[loc274].m_btTeamJoinSide = 1;
						}
						else
						{
							this->m_FloorData[loc274].m_btTeamJoinSide = 0;
						}
					}
					else if(this->m_iYellowTeamUserCount < this->m_iBlueTeamUserCount)
					{
						this->m_FloorData[loc274].m_btTeamJoinSide = 0;
					}
					else
					{
						this->m_FloorData[loc274].m_btTeamJoinSide = 1;
					}

					if(this->m_FloorData[loc274].m_btTeamJoinSide == 0)
					{
						this->m_FloorData[loc274].m_btTeamJoinSide = 0; //wtf??
						this->m_btYellowTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class]++;

						if(loc144 == -1 && gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber < 0)
						{
							loc144 = gParty.Create(this->m_FloorData[loc274].m_iTeamPlayerIndex, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].DBNumber, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Level);

							if(loc144 == -1)
							{
								LogAddTD("[Illusion Temple] (%d) Party Create Error, (Team: %d)", this->m_btFloorIndex+1, this->m_FloorData[loc274].m_btTeamJoinSide);	
							}
							gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber = loc144;
						}
						else
						{
							int loc276 = gParty.Add(loc144, this->m_FloorData[loc274].m_iTeamPlayerIndex, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].DBNumber, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Level);

							if(loc276 >= 0)
							{
								gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber = loc144;
							}
							else
							{
								LogAddTD("[Illusion Temple] (%d) Party Add Error, (Team: %d)", this->m_btFloorIndex+1, this->m_FloorData[loc274].m_btTeamJoinSide);
							}
						}

						gObjMoveGate(this->m_FloorData[loc274].m_iTeamPlayerIndex, this->m_btFloorIndex+148); //Temple
						gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].m_Change = 404; //"MU Allies"
						gObjViewportListProtocolCreate(&gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex]);

						this->m_iYellowTeamUserCount++;
						loc143++;

						int loc277 = strlen(szTemp0);

						sprintf(&szTemp0[loc277],"(%s),(%s) ",gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].AccountID,gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Name);
					}
					else
					{
						this->m_FloorData[loc274].m_btTeamJoinSide = 1;

						this->m_btBlueTeamClassCount[gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Class]++;

						if(loc145 == -1 && gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber < 0)
						{
							loc145 = gParty.Create(this->m_FloorData[loc274].m_iTeamPlayerIndex, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].DBNumber, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Level);

							if(loc145 == -1)
							{
								LogAddTD("[Illusion Temple] (%d) Party Create Error, (Team: %d)", this->m_btFloorIndex+1, this->m_FloorData[loc274].m_btTeamJoinSide);	
							}

							gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber = loc145;
						}
						else
						{
							int loc278 = gParty.Add(loc145, this->m_FloorData[loc274].m_iTeamPlayerIndex, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].DBNumber, gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Level);

							if(loc278 >= 0)
							{
								gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].PartyNumber = loc145;
							}
							else
							{
								LogAddTD("[Illusion Temple] (%d) Party Add Error, (Team: %d)", this->m_btFloorIndex+1, this->m_FloorData[loc274].m_btTeamJoinSide);
							}
						}

						gObjMoveGate(this->m_FloorData[loc274].m_iTeamPlayerIndex, this->m_btFloorIndex+154); //Temple
						gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].m_Change = 405; //"Illusion Sorcerer"
						gObjViewportListProtocolCreate(&gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex]);

						this->m_iBlueTeamUserCount++;
						loc143++;

						int loc279 = strlen(szTemp1);

						sprintf(&szTemp1[loc279],"(%s),(%s) ",gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].AccountID,gObj[this->m_FloorData[loc274].m_iTeamPlayerIndex].Name);
					}
				}
			}

			CGPartyListAll(loc144);
			CGPartyListAll(loc145);

			this->SetState(1);

			LogAddTD("[Illusion Temple] (%d) Allied Team 법사(%d),기사(%d), 요정(%d), 마검사(%d), 다크로드(%d)", this->m_btFloorIndex+1, this->m_btYellowTeamClassCount[0], this->m_btYellowTeamClassCount[1], this->m_btYellowTeamClassCount[2], this->m_btYellowTeamClassCount[3], this->m_btYellowTeamClassCount[4]);

			LogAddTD(szTemp0);

			LogAddTD("[Illusion Temple] (%d) Illusion Team 법사(%d),기사(%d), 요정(%d), 마검사(%d), 다크로드(%d)", this->m_btFloorIndex+1, this->m_btBlueTeamClassCount[0], this->m_btBlueTeamClassCount[1], this->m_btBlueTeamClassCount[2], this->m_btBlueTeamClassCount[3], this->m_btBlueTeamClassCount[4]);

			LogAddTD(szTemp1);
		}
	}
}

void CIllusionTempleProcess::ProcState_Waiting(int iTick) 
{
	int loc2 = iTick - this->m_iCloseTickCount;

	if(loc2 >= 1000)
	{
		this->m_iEventBattleTimer -= loc2;
		this->m_iCloseTickCount = iTick;

		if(this->m_iEventBattleTimer <= 30000)
		{
			if(this->m_iEventBattleTimer > 0)
			{
				if(this->m_bMsgBeforeEnterBattle == FALSE)
				{
					this->m_bMsgBeforeEnterBattle = TRUE;

					PMSG_SET_DEVILSQUARE pMsg;

					PHeadSetB((LPBYTE)&pMsg, 0x92, sizeof(pMsg));
					pMsg.Type = 15;

					for( int i = 0; i < MAX_FLOOR_USER; i++ )
					{
						if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
						{
							if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
							{
								DataSend(this->m_FloorData[i].m_iTeamPlayerIndex, (LPBYTE)&pMsg, pMsg.h.size);
							}
						}
					}
				}
			}
		}
	}

	if(this->m_iEnteredUserCount == 0)
	{
		this->SetState(3);
		return;
	}

	if(this->m_iEventBattleTimer <= 0)
	{
		this->SetState(2);
		this->OperateMiniMapWork(0);
		this->OperateMiniMapWork(1);
	}
}

void CIllusionTempleProcess::ProcState_Playing(int iTick) 
{
	int loc2 = iTick - this->m_iCloseTickCount;

	if(loc2 >= 1000)
	{
		this->m_iEventBattleTimer -= loc2;
		this->m_iCloseTickCount = iTick;

		if(this->m_iEventBattleTimer > 0)
		{
			this->OperateMiniMapWork(0);
			this->OperateMiniMapWork(1);
		}

		if(this->m_iStatueRegenTickCount != -1 && this->m_iStatueRegenTickCount < iTick)
		{
			this->RegenNPCStatus();
		}
	}

	if(this->m_iEnteredUserCount == 0)
	{
		this->SetState(3);
		return;
	}

	if(this->m_iEventBattleTimer <= 0 || this->m_btYellowTeamScore >= 7 || this->m_btBlueTeamScore >= 7 || this->m_iYellowTeamUserCount == 0 || this->m_iBlueTeamUserCount == 0)
	{
		if(this->m_btYellowTeamScore >= 7 || this->m_btBlueTeamScore >= 7)
		{
			if(this->m_iEventBattleTimer <= 0)
			{
				this->m_iLeftMinutesBeforeEnd = 0;
			}
			else
			{
				this->m_iLeftMinutesBeforeEnd = this->m_iEventBattleTimer / 1000;
			}
		}

		this->OperateMiniMapWork(0); //A-Team
		this->OperateMiniMapWork(1); //B-Team

		this->SetState(3);
	}
}

void CIllusionTempleProcess::ProcState_Playend(int iTick) 
{
	int loc2 = iTick - this->m_iCloseTickCount;

	if(loc2 >= 1000)
	{
		this->m_iEventBattleTimer -= loc2;
		this->m_iCloseTickCount = iTick;

		if(this->m_iEventBattleTimer <= 1000 * (m_i_IT_RestTime * 60) - 3000)
		{
			if(this->m_iEventBattleTimer > 0)
			{
				if(this->m_bIllusionTempleEventEnded == FALSE)
				{
					this->m_bIllusionTempleEventEnded = TRUE;

					for( int i = 0; i < MAX_FLOOR_USER; i++ )
					{
						if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
						{
							if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
							{
								if(this->m_FloorData[i].m_btTeamJoinSide == 0)
								{
									gObjMoveGate(this->m_FloorData[i].m_iTeamPlayerIndex, this->m_btFloorIndex + 148); //Battle Map Scene
								}
								else if(this->m_FloorData[i].m_btTeamJoinSide == 1)
								{
									gObjMoveGate(this->m_FloorData[i].m_iTeamPlayerIndex, this->m_btFloorIndex + 154); //Battle Map Scene
								}

								gObjSetPosition(this->m_FloorData[i].m_iTeamPlayerIndex, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].X, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Y);
							}
						}
					}

					if(this->m_iBallPlayerIndex >= 0 && this->m_btBallInventoryPosition >= 0)
					{
						if(gObj[this->m_iBallPlayerIndex].pInventory[this->m_btBallInventoryPosition].m_Type == ITEMGET(14,64))
						{
							::gObjInventoryDeleteItem(this->m_iBallPlayerIndex, this->m_btBallInventoryPosition);
							::GCInventoryItemDeleteSend(this->m_iBallPlayerIndex, this->m_btBallInventoryPosition, 0);

							this->m_iBallPlayerIndex = -1;
							this->m_btBallInventoryPosition = (BYTE)-1;
							this->m_btAllowedRegPedestal = (BYTE)-1;
						}
					}

					this->CalcSendRewardEXP();
				}
			}
		}
	}

	if(this->m_iEventBattleTimer <= 1000 * (m_i_IT_RestTime * 60) - 6000)
	{
		if(this->m_iEventBattleTimer > 0)
		{
			if(this->m_bIllusionTempleEventEnded == TRUE)
			{
				if(this->m_bScoreRankSet == FALSE)
				{
					this->SendRewardScore();
					this->m_bScoreRankSet = TRUE;
				}
			}
		}
	}

	if(this->m_iEventBattleTimer <= 0)
	{
		this->SetState(0);
	}
}

void CIllusionTempleProcess::SetState(BYTE State) 
{
	this->m_btState = State;

	switch( State )
	{
		case 0: //Closed waiting for Open
			this->SetState_NONE();
			break;
		case 1: //Playing (inside temple before battle)
			this->SetState_READY();
			break;
		case 2: //Battle of 15 minutes
			this->SetState_PLAYING();
			break;
		case 3: //After Battle (Score waiting minutes)
			this->SetState_END();
			break;
	}
}

BYTE CIllusionTempleProcess::GetState()
{
	return this->m_btState;
}

void CIllusionTempleProcess::SetState_NONE() 
{
	this->NotifyTempleInfo(0,-1);

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY )
		{
			if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED )
			{
				if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
				{
					gObjMoveGate(this->m_FloorData[i].m_iTeamPlayerIndex, 22); //Devias
#if(DEBUG_IT == 1)
				GCServerMsgStringSend("CIllusionTempleProcess::SetState_NONE()", this->m_FloorData[i].m_iTeamPlayerIndex, 0);
#endif
				}
			}
		}
	}
	this->Init(this->m_btFloorIndex);
}

void CIllusionTempleProcess::SetState_READY() 
{
	this->m_iEventBattleTimer = 1000 * (m_i_IT_WaitTime * 60);

	this->NotifyTempleInfo(1,-1);

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
			{
				::GCSendIllusionTempleKillCount(this->m_FloorData[i].m_iTeamPlayerIndex, 10); //10 Points
#if(DEBUG_IT == 1)
				GCServerMsgStringSend("CIllusionTempleProcess::SetState_READY()", this->m_FloorData[i].m_iTeamPlayerIndex, 0);
#endif
			}
		}
	}
}

void CIllusionTempleProcess::SetState_PLAYING() 
{
	this->m_iEventBattleTimer = 1000 * (m_i_IT_PlayTime * 60);

	this->CreateNPCStatus();
	this->CreateNPC();
	this->CreateMonsterToBattle();
	this->SetNpcStatueRegen();
	this->NotifyTempleInfo(2,-1);

#if(DEBUG_IT == 1)
	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
			{
				GCServerMsgStringSend("CIllusionTempleProcess::SetState_PLAYING()", this->m_FloorData[i].m_iTeamPlayerIndex, 0);
			}
		}
	}
#endif
}

void CIllusionTempleProcess::SetState_END()
{
	this->m_iEventBattleTimer = 1000 * (m_i_IT_RestTime * 60);

	this->NotifyTempleInfo(3,-1);

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == (this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE) )
			{
				if(this->m_FloorData[i].m_dwShieldSpellTime > 0)
				{
					this->m_FloorData[i].m_dwShieldSpellTime = 0;
					//gObjRemoveBuffEffect(&gObj[this->m_FloorData[i].m_iTeamPlayerIndex], AT_ILLUSION_SHIELD_SPELL); //season 3.0 add-on
					this->GCIllusionTempleSkillCancel(&gObj[this->m_FloorData[i].m_iTeamPlayerIndex], 210);
				}

				if(this->m_FloorData[i].m_dwRestrictionSpellTime > 0)
				{
					this->m_FloorData[i].m_dwRestrictionSpellTime = 0;
					//gObjRemoveBuffEffect(&gObj[this->m_FloorData[i].m_iTeamPlayerIndex], AT_ILLUSION_RESTRICTION_SPELL); //season 3.0 add-on
					this->GCIllusionTempleSkillCancel(&gObj[this->m_FloorData[i].m_iTeamPlayerIndex], 211);
				}
#if(DEBUG_IT == 1)
				GCServerMsgStringSend("CIllusionTempleProcess::SetState_END()", this->m_FloorData[i].m_iTeamPlayerIndex, 0);
#endif
			}
		}
	}

	this->ClearAllBattleObjects();
}

BOOL CIllusionTempleProcess::AddBattleUser(int aIndex, BYTE pos, BYTE pos_dur)
{
	int loc2;
	int loc3;

	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if(this->GetState() >= 1)
	{
		return FALSE;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		LogAddTD("Enter Error: IllusionTempleIndex Fail");
		return FALSE;
	}

	loc2 = this->FindItemBallPosition(aIndex);

	if(loc2 >= 0)
	{
		if( gObj[aIndex].pInventory[loc2].m_Type == ITEMGET(14,64) ) //Ball
		{
			::gObjInventoryDeleteItem(aIndex, loc2);
			::GCInventoryItemDeleteSend(aIndex, loc2, 0);
		}
	}

	loc3 = 0;

	EnterCriticalSection(&this->m_cs);

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex == OBJ_EMPTY )
		{
			this->m_FloorData[i].m_iTeamPlayerIndex = aIndex;
			this->m_iEnteredUserCount++;
			gObj[aIndex].m_iIllusionTempleIndex = i;
			loc3 = 1;
			this->m_FloorData[i].m_btPosNDur = pos_dur; //webzen fix for ticket durability
			break;
		}
	}

	LeaveCriticalSection(&this->m_cs);

	return loc3;
}

BOOL CIllusionTempleProcess::LeaveBattleUser(int aIndex) 
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	EnterCriticalSection(&this->m_cs);

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(aIndex == this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex)
		{
			_ILLUSIONTEMPLE_FLOOR_DATA * FloorData = &this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex];

			if(FloorData->m_btPosNDur > -1)
			{
				CItem * lpItem = &gObj[aIndex].pInventory[FloorData->m_btPosNDur];

				if(lpItem != NULL)
				{
					if(lpItem->IsItem() == TRUE)
					{
						if(lpItem->m_Durability < 1.0f)
						{
							gObjInventoryDeleteItem(aIndex, FloorData->m_btPosNDur);
							GCInventoryItemDeleteSend(aIndex, FloorData->m_btPosNDur, 0);
						}
					}
				}
			}

			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_dwShieldSpellTime > 0)
			{
				this->GCIllusionTempleSkillCancel(&gObj[aIndex], 210);
			}

			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_dwRestrictionSpellTime > 0)
			{
				this->GCIllusionTempleSkillCancel(&gObj[aIndex], 211);
			}

			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide == 0)
			{
				this->m_iYellowTeamUserCount--;
			}
			else if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide == 1)
			{
				this->m_iBlueTeamUserCount--;
			}

			this->InitFloorData(gObj[aIndex].m_iIllusionTempleIndex);

			gObj[aIndex].m_iIllusionTempleIndex = -1;

			this->m_iEnteredUserCount--;

			LogAddTD("[Illusion Temple] (%d) LeaveUser: (%s)(%s)", this->m_btFloorIndex+1, gObj[aIndex].AccountID, gObj[aIndex].Name);
		}
	}

	LeaveCriticalSection(&this->m_cs);

	if(gObj[aIndex].PartyNumber >= 0)
	{
		PMSG_PARTYDELUSER pMsg;

		int Index = gParty.GetIndex(gObj[aIndex].PartyNumber, gObj[aIndex].m_Index, gObj[aIndex].DBNumber);

		if(Index >= 0)
		{
			pMsg.Number = Index;
			CGPartyDelUser(&pMsg, gObj[aIndex].m_Index);
		}
	}

	gObj[aIndex].m_Change = -1;
	gObjViewportListProtocolCreate(&gObj[aIndex]);

	return TRUE;
}

int CIllusionTempleProcess::GetFloorIndex(int aIndex) //Identical (Unused)
{
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
	if( lpObj->Level <= 400 && lpObj->ChangeUP3rd == 0) return 5;
	if( lpObj->Level == 400 && lpObj->ChangeUP3rd != 0){ if(g_iUseMaxLevelIllusionTemple != 0){	return 5;}else{return 5;}};
	return -1;
}

void CIllusionTempleProcess::RemoveInvalid() 
{
	EnterCriticalSection(&m_cs);

	this->m_iEnteredUserCount = 0;

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY )
		{
			if( gObjIsConnected(this->m_FloorData[i].m_iTeamPlayerIndex) == FALSE )
			{
				gObj[this->m_FloorData[i].m_iTeamPlayerIndex].m_iIllusionTempleIndex = ILLUSIONTEMPLE_INVALID_INDEX;
				InitFloorData(i);
			}
			else if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber != (MAP_INDEX_ILLUSIONTEMPLE + this->m_btFloorIndex) )
			{
				gObj[this->m_FloorData[i].m_iTeamPlayerIndex].m_iIllusionTempleIndex = ILLUSIONTEMPLE_INVALID_INDEX;
				this->InitFloorData(i);
			}
			else
			{
				this->m_iEnteredUserCount++;
			}
		}
	}

	LeaveCriticalSection(&m_cs);
}

BYTE CIllusionTempleProcess::CheckLeftMinutesBeforeOpen() 
{
	if(this->GetState() == 0 && this->GetOpenStatus() == TRUE)
	{
		return this->m_iLeftMinutesBeforeOpen;
	}
	return FALSE;
}

BYTE CIllusionTempleProcess::RemainTime() 
{
	BYTE loc2 = 0;
	
	if(this->GetState() == 0 && this->GetOpenStatus() == TRUE)
	{
		loc2 = 0;
	}
	else if(this->GetState() == 0 && this->GetOpenStatus() == FALSE)
	{
		loc2 = this->m_iLeftMinutesBeforeOpen - m_i_IT_OpenTime;
	}
	else
	{
		std::list<ILLUSIONTEMPLE_START_TIME>::iterator it; //loc2 -> ebp 4
		ILLUSIONTEMPLE_START_TIME WebzenVar1; //loc 3-4 -> ebp C
		ILLUSIONTEMPLE_START_TIME WebzenVar2; //loc 5-6 -> epb 14
		int BaseTime = 0; // loc7 -> ebp 18
		int CheckTime = 0; // loc8 -> ebp 1C
		DWORD CurrentTime = 0;	// loc9 -> ebp 20
		
		tm * today; //loc10 -> ebp 28
		time_t ltime; //loc11 -> ebp 2c

		int loc12; //loc12 -> ebp30
		int loc13; //loc13 -> ebp34

		if(m_listIllusionTempleOpenTime.size() == 0)
		{
			MsgBox("Error : Illusion Temple StartTime size is 0");
			return FALSE;
		}

		time(&ltime); //
		today = localtime(&ltime); //

		
		CurrentTime = (today->tm_hour * 60) + today->tm_min;
		WebzenVar1 = *m_listIllusionTempleOpenTime.begin();

		for( it = m_listIllusionTempleOpenTime.begin(); it != m_listIllusionTempleOpenTime.end(); ++it ) //for identical
		{
			WebzenVar2 = *it; // loc5-6
			BaseTime = (WebzenVar1.m_iHour * 60) + WebzenVar1.m_iMinute;
			CheckTime =	(WebzenVar2.m_iHour * 60) + WebzenVar2.m_iMinute;

			if( BaseTime == CheckTime )
			{
				if( CurrentTime < CheckTime )
				{
					WebzenVar2 = *it;
					break;
				}
				continue;
			}
			
			if( CurrentTime >= BaseTime && CurrentTime < CheckTime )
			{
				break;
			}
			else
			{
				WebzenVar1 = *it;
			}
		}

		for(loc12 = 2;loc12--;)
		{
			if(it == m_listIllusionTempleOpenTime.end())
			{
				it = m_listIllusionTempleOpenTime.begin();

				WebzenVar2 = (*it);
			}

			CheckTime = WebzenVar2.m_iHour*60+WebzenVar2.m_iMinute;

			if(today->tm_hour <= WebzenVar2.m_iHour)
			{
				loc2 = CheckTime - CurrentTime;
			}
			else
			{
				loc2 = 1440-CurrentTime+CheckTime;
			}

			if(loc2 <= m_i_IT_OpenTime)
			{
				it++;

				if(it != m_listIllusionTempleOpenTime.end())
				{
					WebzenVar2 = (*it);
				}
			}
			else
			{
				loc2 -= m_i_IT_OpenTime;
				break;
			}
		}

		loc13 = GetTickCount();
		this->m_iOpenTickCount = loc13 + (60000 - (today->tm_sec * 1000));
	}

	return loc2;
}

void CIllusionTempleProcess::NpcStatueProc(LPOBJ lpObj, LPOBJ lpTargetObj) 
{
	if(lpObj->m_State == 0 || lpObj->m_PosNum == -1)
	{
		return;
	}

	if( (abs(lpTargetObj->Y - lpObj->Y)) > 3 || (abs(lpTargetObj->X - lpObj->X)) > 3)
	{
		return;
	}

	lpObj->m_PosNum = -1;
	lpObj->Life = 0;

	gObjLifeCheck(lpObj, lpTargetObj, 0, 1, 0, 0, 0, 0);

	float loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;

	loc3 = ItemGetNumberMake(14, 64);	//Ball
	loc5 = 0;
	loc6 = 0;
	loc7 = 0;
	loc4 = 0;

	ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, lpObj->X, lpObj->Y, loc3, loc4, loc2, loc5, loc6, loc7, lpTargetObj->m_Index, loc10, 0);

	LogAddTD("[Illusion Temple] (%d) [%s][%s] Click To Status (X:%d, Y:%d)", this->m_btFloorIndex+1, lpTargetObj->AccountID, lpTargetObj->Name, lpObj->X, lpObj->Y);

	this->SetBattleMonstersReady();
}

void CIllusionTempleProcess::NpcAlliedPedestalProc(LPOBJ lpObj, LPOBJ lpTargetObj) 
{
	if(this->m_btAllowedRegPedestal == (BYTE)-1 || this->m_btAllowedRegPedestal != 0 || lpTargetObj->m_Index != this->m_iBallPlayerIndex)
	{
		return;
	}

	if(lpTargetObj->pInventory[this->m_btBallInventoryPosition].m_Type == ITEMGET(14,64))
	{
		this->m_btYellowTeamScore++;
		this->DeleteRelicsItem(lpTargetObj);
		this->m_btAllowedRegPedestal = (BYTE) -1;
		this->m_iBallPlayerIndex = -1;
		this->m_btBallInventoryPosition = (BYTE) -1;
		this->IncreaseTeamPlayerReward(lpTargetObj->m_Index);

		LogAddTD("[Illusion Temple] (%d) Increase AlliedTeam Relics Point: (%s)(%s)(Score:%d)", this->m_btFloorIndex+1, lpTargetObj->AccountID, lpTargetObj->Name, this->m_btYellowTeamScore);
	}
	this->SetNpcStatueRegen();
}

void CIllusionTempleProcess::NpcRelicsPedestalProc(LPOBJ lpObj, LPOBJ lpTargetObj) 
{
	if(this->m_btAllowedRegPedestal == (BYTE)-1 || this->m_btAllowedRegPedestal != 1 || lpTargetObj->m_Index != this->m_iBallPlayerIndex)
	{
		return;
	}

	if(lpTargetObj->pInventory[this->m_btBallInventoryPosition].m_Type == ITEMGET(14,64))
	{
		this->m_btBlueTeamScore++;
		this->DeleteRelicsItem(lpTargetObj);
		this->m_btAllowedRegPedestal = (BYTE) -1;
		this->m_iBallPlayerIndex = -1;
		this->m_btBallInventoryPosition = (BYTE) -1;
		this->IncreaseTeamPlayerReward(lpTargetObj->m_Index);

		LogAddTD("[Illusion Temple] (%d) Increase IllusionTeam Relics Point: (%s)(%s)(Score:%d)", this->m_btFloorIndex+1, lpTargetObj->AccountID, lpTargetObj->Name, this->m_btBlueTeamScore);
	}
	this->SetNpcStatueRegen();
}

int CIllusionTempleProcess::FindItemBallPosition(int aIndex) 
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	for( int i = 0; i < INVENTORY_SIZE; i++ )
	{
		if( gObj[aIndex].pInventory[i].IsItem() == TRUE )
		{
			if( gObj[aIndex].pInventory[i].m_Type == ITEMGET(14,64) ) //Ball
			{
				return i;
			}
		}
	}
	return -1;
}

void CIllusionTempleProcess::DeleteRelicsItem(LPOBJ lpObj) 
{
	if(lpObj->pInventory[this->m_btBallInventoryPosition].m_Type == ITEMGET(14,64))
	{
		LogAddTD("[Illusion Temple] (%d) (%s)(%s) to Delete Relics Item [Serial:%u]", this->m_btFloorIndex+1, lpObj->AccountID, lpObj->Name, lpObj->pInventory[this->m_btBallInventoryPosition].m_Number);
		gObjInventoryDeleteItem(lpObj->m_Index, this->m_btBallInventoryPosition);
		GCInventoryItemDeleteSend(lpObj->m_Index, this->m_btBallInventoryPosition, 0);
	}
}

void CIllusionTempleProcess::DropRelicsItem(int iIndex) 
{
	if( OBJMAX_RANGE(iIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	if(this->m_iBallPlayerIndex != iIndex)
	{
		return;
	}

	LPOBJ lpObj = &gObj[iIndex]; //loc2

	if(this->m_btBallInventoryPosition == -1)
	{
		return;
	}

	if(lpObj->pInventory[this->m_btBallInventoryPosition].m_Type != ITEMGET(14,64))
	{
		return;
	}

	int iItemPos = this->m_btBallInventoryPosition; //item position loc3

	PMSG_ITEMTHROW_RESULT pResult;

	PHeadSetB((LPBYTE)&pResult, 0x23, sizeof(pResult));
	pResult.Result = TRUE;
	pResult.Ipos = iItemPos;

	int map_num = gObj[iIndex].MapNumber;
	int type = gObj[iIndex].pInventory[iItemPos].m_Type;
	int level = gObj[iIndex].pInventory[iItemPos].m_Level;
	float dur = gObj[iIndex].pInventory[iItemPos].m_Durability;
	BOOL ret = gObj[iIndex].pInventory[iItemPos].IsItem();
	BYTE Option1 = gObj[iIndex].pInventory[iItemPos].m_Option1;
	BYTE Option2 = gObj[iIndex].pInventory[iItemPos].m_Option2;
	BYTE Option3 = gObj[iIndex].pInventory[iItemPos].m_Option3;
	BYTE NOption = gObj[iIndex].pInventory[iItemPos].m_NewOption;
	DWORD s_num = gObj[iIndex].pInventory[iItemPos].m_Number;
	BYTE ItemExOption = g_kJewelOfHarmonySystem.GetItemStrengthenOption(&gObj[iIndex].pInventory[iItemPos]);
	BYTE ItemExLevel = g_kJewelOfHarmonySystem.GetItemOptionLevel(&gObj[iIndex].pInventory[iItemPos]); //loc17

	BYTE NewOption[MAX_EXOPTION_SIZE];

	::ItemIsBufExOption(NewOption, &gObj[iIndex].pInventory[iItemPos]);

	int PetLevel = gObj[iIndex].pInventory[iItemPos].m_PetItem_Level; //loc20

	int PetExp = gObj[iIndex].pInventory[iItemPos].m_PetItem_Exp; //loc21
	BYTE SOption = gObj[iIndex].pInventory[iItemPos].m_SetOption; //loc22

	BYTE ItemEffectEx = gObj[iIndex].pInventory[iItemPos].m_ItemOptionEx; //loc23
	int item_number = gObj[iIndex].pInventory[iItemPos].m_Number; //loc24

	char szItemName[50] = "저주받은성물";

	int aAntiLootIndex = -1; //loc38
	short cX = 0; //loc39
	short cY = 0; //loc40

	BYTE btMapAttr = MapC[map_num].GetAttr(gObj[iIndex].X, gObj[iIndex].Y);

	if((btMapAttr&4) == 4 || (btMapAttr&8) == 8)
	{
		cX = 168;
		cY = 85;
	}
	else
	{
		cX = gObj[iIndex].X;
		cY = gObj[iIndex].Y;
	}

	if ( MapC[map_num].ItemDrop(type, 
		level, dur, cX, cY,
		Option1, Option2, Option3, 
		NOption, SOption, item_number, 
		aAntiLootIndex, PetLevel, PetExp, ItemEffectEx) == TRUE )
	{
		LogAddTD("[Illusion Temple] (%d) (%s)(%s) to Drop Relics Item [Serial:%u]",this->m_btFloorIndex+1, lpObj->AccountID, lpObj->Name, lpObj->pInventory[this->m_btBallInventoryPosition].m_Number);
		
		::gObjInventoryDeleteItem(iIndex, iItemPos);
		pResult.Result = TRUE;

		LogAddTD(lMsg.Get(479), gObj[iIndex].AccountID, gObj[iIndex].Name, gObj[iIndex].MapNumber,
			gObj[iIndex].X, gObj[iIndex].Y, s_num, szItemName, type, level, Option1, Option2, Option3, (int)dur, NewOption[0],
			NewOption[1], NewOption[2], NewOption[3], NewOption[4], NewOption[5], NewOption[6], SOption,
			ItemEffectEx>>7, ItemExOption, ItemExLevel);
	}
	else
	{
		pResult.Result = FALSE;
	}

	this->m_iBallPlayerIndex = -1;
	this->m_btBallInventoryPosition = (BYTE)-1;
	this->m_btAllowedRegPedestal = (BYTE)-1;

	DataSend(iIndex, (LPBYTE)&pResult, pResult.h.size);
}

void CIllusionTempleProcess::UnlockTeamPedestal(int aIndex, BYTE pos)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	this->m_iBallPlayerIndex = aIndex;
	this->m_btBallInventoryPosition = pos;

	if(gObj[aIndex].m_iIllusionTempleIndex != -1 && this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex != -1 && this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex)
	{
		this->m_btAllowedRegPedestal = this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide;
	}
}

void CIllusionTempleProcess::GCSendPlayerRelicsCarrier(LPOBJ lpObj) //Seongmul Effect
{
	PMSG_ANNOUNCE_BALL_PLAYER pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x08, sizeof(pMsg));

	pMsg.m_sIndex = lpObj->m_Index;

	memcpy(pMsg.chCharacter, lpObj->Name, 10);

	for( int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY )
		{
			if( gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED )
			{
				DataSend(this->m_FloorData[i].m_iTeamPlayerIndex,(LPBYTE)&pMsg,pMsg.h.size);
			}
		}
	}
}

void CIllusionTempleProcess::TestBattleScene()
{
	this->m_iLeftMinutesBeforeOpen = 0;
	this->m_iEventBattleTimer = 1000;
}

void CIllusionTempleProcess::SetNPCPosition(int Class, int Position)
{
	if(Class == 380)
	{
		if(this->m_iStatueCount > 2)
		{
			return;
		}

		this->m_StatueData[this->m_iStatueCount].m_iStatueIndex = -1;
		this->m_StatueData[this->m_iStatueCount].m_sStatuePosition = (short)Position;

		this->m_iStatueCount+=1;
		return;
	}

	if(Class == 383)
	{
		this->m_iYellowPedestalIndex = -1;
		this->m_sYellowPedestalPosition = Position;
		return;
	}

	if(Class == 384)
	{
		this->m_iBluePedestalIndex = -1;
		this->m_sBluePedestalPosition = Position;
		return;
	}
}

void CIllusionTempleProcess::SetMonsterPosition(int Class, int Position)
{
	if(this->m_iMonsterCount > 40)
	{
		return;
	}

	this->m_MonsterData[this->m_iMonsterCount].m_iMonsterIndex = -1;
	this->m_MonsterData[this->m_iMonsterCount].m_sMonsterPosition = (short)Position;

	this->m_iMonsterCount++;
}

void CIllusionTempleProcess::ClearMonstersData() 
{
	int i;

	for(i = 0; i< MAX_STATUE_MONSTER; i++)
	{
		this->m_StatueData[i].m_iStatueIndex = -1;
		this->m_StatueData[i].m_sStatuePosition = -1;
	}

	this->m_iStatueCount = 0;
	this->m_iYellowPedestalIndex = -1;
	this->m_sYellowPedestalPosition = -1;
	this->m_iBluePedestalIndex = -1;
	this->m_sBluePedestalPosition = -1;

	for(i = 0; i< MAX_FLOOR_MONSTER; i++)
	{
		this->m_MonsterData[i].m_iMonsterIndex = -1;
		this->m_MonsterData[i].m_sMonsterPosition = -1;
	}

	this->m_iMonsterCount = 0;
}

void CIllusionTempleProcess::CreateNPCStatus() 
{
	for( int i = 0; i < this->m_iStatueCount; i++)
	{
		int loc3 = gObjAddMonster(this->m_btFloorIndex+MAP_INDEX_ILLUSIONTEMPLE);

		if(loc3 >= 0)
		{
			::gObjSetPosMonster(loc3, this->m_StatueData[i].m_sStatuePosition);
			::gObjSetMonster(loc3, 380);
			gObj[loc3].m_PosNum = -1;
			gObj[loc3].Live = 0;
			gObj[loc3].DieRegen = 2;
			gObj[loc3].m_State = 4;
			gObj[loc3].RegenTime = GetTickCount();
			this->m_StatueData[i].m_iStatueIndex = loc3;

			LogAddTD("[Illusion Temple] (%d) Create NPC Status Name: %s, (%d: %d/%d)", this->m_btFloorIndex+1, gObj[loc3].Name, gObj[loc3].MapNumber, gObj[loc3].X, gObj[loc3].Y);
		}
		else
		{
			LogAddTD("[Illusion Temple] (%d) Add Status Error", this->m_btFloorIndex+1);
		}
	}
}

void CIllusionTempleProcess::CreateNPC() 
{
	int loc2;

	loc2 = gObjAddMonster(this->m_btFloorIndex+MAP_INDEX_ILLUSIONTEMPLE);

	if(loc2 >= 0)
	{
		::gObjSetPosMonster(loc2, this->m_sYellowPedestalPosition);
		::gObjSetMonster(loc2, 383);
		gObj[loc2].Dir = 1;
		gObj[loc2].m_PosNum = -1;
		gObj[loc2].Live = 1;
		gObj[loc2].DieRegen = 0;
		gObj[loc2].m_State = 1;
		this->m_iYellowPedestalIndex = loc2;

		LogAddTD("[Illusion Temple] (%d) Create NPC AlliedRelicsBox Name: %s, (%d: %d/%d)", this->m_btFloorIndex+1, gObj[loc2].Name, gObj[loc2].MapNumber, gObj[loc2].X, gObj[loc2].Y);
	}
	else
	{
		LogAddTD("[Illusion Temple] (%d) Add AlliedRelicsBox Error", this->m_btFloorIndex+1);
	}

	loc2 = gObjAddMonster(this->m_btFloorIndex+MAP_INDEX_ILLUSIONTEMPLE);

	if(loc2 >= 0)
	{
		::gObjSetPosMonster(loc2, this->m_sBluePedestalPosition);
		::gObjSetMonster(loc2, 384);
		gObj[loc2].Dir = 1;
		gObj[loc2].m_PosNum = -1;
		gObj[loc2].Live = 1;
		gObj[loc2].DieRegen = 0;
		gObj[loc2].m_State = 1;
		this->m_iBluePedestalIndex = loc2;

		LogAddTD("[Illusion Temple] (%d) Create NPC IllusionRelicsBox Name: %s, (%d: %d/%d)", this->m_btFloorIndex+1, gObj[loc2].Name, gObj[loc2].MapNumber, gObj[loc2].X, gObj[loc2].Y);
	}
	else
	{
		LogAddTD("[Illusion Temple] (%d) Add IllusionRelicsBox Error", this->m_btFloorIndex+1);
	}
}

void CIllusionTempleProcess::CreateMonsterToBattle() 
{
	for( int i = 0; i < this->m_iMonsterCount; i++)
	{
		int loc3 = gObjAddMonster(this->m_btFloorIndex+MAP_INDEX_ILLUSIONTEMPLE);

		if(loc3 >= 0)
		{
			::gObjSetPosMonster(loc3, this->m_MonsterData[i].m_sMonsterPosition);
			::gObjSetMonster(loc3, gMSetBase.m_Mp[this->m_MonsterData[i].m_sMonsterPosition].m_Type);
			gObj[loc3].Dir = 1;
			gObj[loc3].m_PosNum = -1;
			gObj[loc3].Live = 0;
			gObj[loc3].DieRegen = 0;
			gObj[loc3].m_State = 4;
			gObj[loc3].RegenTime = GetTickCount();
			this->m_MonsterData[i].m_iMonsterIndex = loc3;
		}
		else
		{
			LogAddTD("[Illusion Temple] (%d) Add Monster Error", this->m_btFloorIndex+1);
		}
	}
}

void CIllusionTempleProcess::ClearAllBattleObjects()
{
	int i;

	for(i = 0; i < this->m_iStatueCount; i++)
	{
		if(this->m_StatueData[i].m_iStatueIndex != -1)
		{
			LogAddTD("[Illusion Temple] (%d) RemoveStatus Name: %s, (%d: %d/%d)",this->m_btFloorIndex+1, gObj[this->m_StatueData[i].m_iStatueIndex].Name, gObj[this->m_StatueData[i].m_iStatueIndex].MapNumber, gObj[this->m_StatueData[i].m_iStatueIndex].X, gObj[this->m_StatueData[i].m_iStatueIndex].Y);
			gObjDel(this->m_StatueData[i].m_iStatueIndex);
			this->m_StatueData[i].m_iStatueIndex = -1;
		}
	}

	if(this->m_iYellowPedestalIndex != -1)
	{
		LogAddTD("[Illusion Temple] (%d) RemoveAlliedRelicsBox Name: %s, (%d: %d/%d)",this->m_btFloorIndex+1, gObj[this->m_iYellowPedestalIndex].Name, gObj[this->m_iYellowPedestalIndex].MapNumber, gObj[this->m_iYellowPedestalIndex].X, gObj[this->m_iYellowPedestalIndex].Y);
		gObjDel(this->m_iYellowPedestalIndex);
		this->m_iYellowPedestalIndex = -1;
	}

	if(this->m_iBluePedestalIndex != -1)
	{
		LogAddTD("[Illusion Temple] (%d) RemoveIllusionRelicsBox Name: %s, (%d: %d/%d)",this->m_btFloorIndex+1, gObj[this->m_iBluePedestalIndex].Name, gObj[this->m_iBluePedestalIndex].MapNumber, gObj[this->m_iBluePedestalIndex].X, gObj[this->m_iBluePedestalIndex].Y);
		gObjDel(this->m_iBluePedestalIndex);
		this->m_iBluePedestalIndex = -1;
	}

	for(i = 0; i < this->m_iMonsterCount; i++)
	{
		if(this->m_MonsterData[i].m_iMonsterIndex != -1)
		{
			gObjDel(this->m_MonsterData[i].m_iMonsterIndex);
			this->m_MonsterData[i].m_iMonsterIndex = -1;
		}
	}

	LogAddTD("[Illusion Temple] (%d) Remove All Object", this->m_btFloorIndex+1);
}

void CIllusionTempleProcess::SetNpcStatueRegen() 
{
	this->m_iStatueRegenTickCount = 5000 + GetTickCount(); //Appear after 5 seconds
}

void CIllusionTempleProcess::RegenNPCStatus() 
{
	if(this->m_iBallPlayerIndex >= 0)
	{
		return;
	}

	int loc2 = rand()%this->m_iStatueCount;

	if(this->m_StatueData[loc2].m_iStatueIndex == -1)
	{
		return;
	}

	LPOBJ lpObj = &gObj[this->m_StatueData[loc2].m_iStatueIndex];

	lpObj->m_PosNum = this->m_StatueData[loc2].m_sStatuePosition;
	lpObj->DieRegen = 2;
	this->m_iStatueRegenTickCount = -1;

	LogAddTD("[Illusion Temple] (%d) RegenStatus Name: %s, (%d: %d/%d), PosNum(%d), connected:%d", this->m_btFloorIndex+1, lpObj->Name, lpObj->MapNumber, lpObj->X, lpObj->Y, lpObj->m_PosNum, lpObj->Connected);
}

void CIllusionTempleProcess::SetBattleMonstersReady() 
{
	for(int i = 0; i < MAX_FLOOR_MONSTER; i++)
	{
		if(this->m_MonsterData[i].m_iMonsterIndex != -1 && gObj[this->m_MonsterData[i].m_iMonsterIndex].m_PosNum == -1)
		{
			gObj[this->m_MonsterData[i].m_iMonsterIndex].m_PosNum = this->m_MonsterData[i].m_sMonsterPosition; 
			gObj[this->m_MonsterData[i].m_iMonsterIndex].DieRegen = 2;
		}
	}
}

void CIllusionTempleProcess::SendNoticeToAll(LPSTR lpszMsg) 
{
	PMSG_NOTICE pNotice;
	TNotice::MakeNoticeMsg(&pNotice, 0, lpszMsg);

	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			DataSend(this->m_FloorData[i].m_iTeamPlayerIndex,(LPBYTE)&pNotice,pNotice.h.size);
		}
	}
}

void CIllusionTempleProcess::OperateMiniMapWork(BYTE btTeam)
{
	int	iOfs = 0;

	char MessageBuff[256];

	PMSG_ILLUSIONTEMPLE_TEAMINFO_HEAD	pMsgHead;
	
	if( this->m_iEventBattleTimer < 0 )
	{
		this->m_iEventBattleTimer = 0;
	}

	pMsgHead.m_wTimer = this->m_iEventBattleTimer / 1000;
		
	if( this->m_iBallPlayerIndex != OBJ_EMPTY ) //Ball
	{
		pMsgHead.m_waIndex    = this->m_iBallPlayerIndex;
		pMsgHead.m_btPositionX = gObj[this->m_iBallPlayerIndex].X;
		pMsgHead.m_btPositionY = gObj[this->m_iBallPlayerIndex].Y;
	}
	else
	{
		pMsgHead.m_waIndex    = OBJ_EMPTY;
		pMsgHead.m_btPositionX = (BYTE)-1;
		pMsgHead.m_btPositionY = (BYTE)-1;
	}
	
	pMsgHead.m_btRelicsTeamScore 	= this->m_btYellowTeamScore;
	pMsgHead.m_btIllusionRelicsScore= this->m_btBlueTeamScore;
	pMsgHead.m_btTeam				= btTeam;
	
	iOfs += sizeof(pMsgHead);
	int Count = 0;

	for(int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && this->m_FloorData[i].m_btTeamJoinSide == btTeam && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED )
		{
			PMSG_ILLUSIONTEMPLE_TEAMINFO_MEMBERDATA pMsg;

			pMsg.m_waIndex    = this->m_FloorData[i].m_iTeamPlayerIndex;
			pMsg.m_btMapNumber = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber;
			pMsg.m_btPositionX = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].X;
			pMsg.m_btPositionY = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Y;
			
			Count++;
			
			memcpy((MessageBuff+iOfs), &pMsg, sizeof(pMsg));
			
			iOfs += sizeof(pMsg);
		}
	}
	
	if( btTeam == 0 )
	{
		if( this->m_iYellowTeamUserCount != Count )
		{
			this->m_iYellowTeamUserCount = Count;
		}

		pMsgHead.m_btCount = this->m_iYellowTeamUserCount;
	}
	else 
	{
		if( this->m_iBlueTeamUserCount != Count )
		{
			this->m_iBlueTeamUserCount = Count;
		}
		pMsgHead.m_btCount = this->m_iBlueTeamUserCount;
	}
	
	PHeadSubSetB((LPBYTE)&pMsgHead, 0xBF, 0x01, iOfs);
	
	memcpy(MessageBuff, &pMsgHead, sizeof(pMsgHead));
	
	for(int i = 0; i < MAX_FLOOR_USER; i++ )
	{
		if( this->m_FloorData[i].m_iTeamPlayerIndex != OBJ_EMPTY && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED && this->m_FloorData[i].m_btTeamJoinSide == btTeam )		
		{
			DataSend(this->m_FloorData[i].m_iTeamPlayerIndex, (LPBYTE)MessageBuff, pMsgHead.h.size);
		}
	}
}

void CIllusionTempleProcess::NotifyTempleInfo(BYTE btState, int aIndex) 
{
	_ILLUSIONTEMPLE_BARRIER pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x09, sizeof(pMsg));

	pMsg.m_btFloorIndex = 0;
	pMsg.m_btState = btState;

	//LogAddTD("pMsg.m_btFloorIndex: %d pMsg.m_btState: %d aIndex: %d ",pMsg.m_btFloorIndex, pMsg.m_btState, aIndex);

	if(aIndex != -1)
	{
		DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);
		return;
	}

	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			DataSend(this->m_FloorData[i].m_iTeamPlayerIndex,(LPBYTE)&pMsg,pMsg.h.size);
		}
	}
}

BYTE CIllusionTempleProcess::GetUserJoinSide(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			return this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide;
		}
	}

	return -1;
}

BYTE CIllusionTempleProcess::AddKillPointToUser(int aIndex, BYTE btPoint)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint += btPoint;

			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint > 90)
			{
				this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint = 90;
			}

			return this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint;
		}
	}

	return FALSE;
}

BYTE CIllusionTempleProcess::RemoveKillPointFromUser(int aIndex, BYTE btPoint)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint >= btPoint)
			{
				this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint-= btPoint;
				return this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint;
			}
		}
	}

	return FALSE;
}

BYTE CIllusionTempleProcess::GetKillCountPointFromUser(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			return this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint;
		}
	}

	return FALSE;
}

BOOL CIllusionTempleProcess::UpdateKillCountPointFromUser(int aIndex, BYTE btPoint)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return FALSE;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btKillCountPoint = btPoint;
			return TRUE;
		}
	}

	return FALSE;
}

void CIllusionTempleProcess::ResetUserKillCountPoint() 
{
	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		this->m_FloorData[i].m_btKillCountPoint = MAX_FLOOR_USER;
	}
}

void CIllusionTempleProcess::IncreaseUserKillCount(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btUserKillCount > (BYTE)-1)
			{
				return;
			}
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btUserKillCount+= 1;
		}
	}
}

void CIllusionTempleProcess::IncreaseMonsterKillCount(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btMonsterRewardKillCount > (BYTE)-1)
			{
				return;
			}
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btMonsterRewardKillCount+= 1;
		}
	}
}

void CIllusionTempleProcess::ResetAllKillCount()
{
	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		this->m_FloorData[i].m_btUserKillCount = 0;
		this->m_FloorData[i].m_btMonsterRewardKillCount = 0;
	}
}

void CIllusionTempleProcess::IncreaseTeamPlayerReward(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btPlayerRewardKillCount > (BYTE)-1)
			{
				return;
			}
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btPlayerRewardKillCount+= 1;
		}
	}
}

void CIllusionTempleProcess::ResetPlayerReward()
{
	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		this->m_FloorData[i].m_btPlayerRewardKillCount = 0;
	}
}

void CIllusionTempleProcess::IncreaseUsedKillCount(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	if(gObj[aIndex].m_iIllusionTempleIndex != -1)
	{
		if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex == aIndex || gObj[aIndex].Connected > PLAYER_LOGGED)
		{
			if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btUsedKillCountPoint > (BYTE)-1)
			{
				return;
			}
			this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btUsedKillCountPoint+= 1;
		}
	}
}

void CIllusionTempleProcess::ResetUserUsedKillCount()
{
	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		this->m_FloorData[i].m_btUsedKillCountPoint = 0;
	}
}

void CIllusionTempleProcess::RunningSkill(int aIndex, WORD skill, int aTargetIndex, BYTE btDir)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	LPOBJ lpObj;
	LPOBJ lpTargetObj;
	
	if( OBJMAX_RANGE(aTargetIndex) == FALSE )
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return;
	}

	lpObj = &gObj[aIndex]; //ebp-8
	lpTargetObj = &gObj[aTargetIndex];

	if(this->GetState() != 2)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 0);
		return;
	}

	if(lpObj->Connected <= PLAYER_LOGGED || lpTargetObj->Connected <= PLAYER_LOGGED)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 0);
		return;
	}

	if(lpObj->MapNumber != lpTargetObj->MapNumber)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 0);
		return;
	}

	if(lpObj->m_iIllusionTempleIndex == -1 || lpTargetObj->m_iIllusionTempleIndex == -1)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 0);
		return;
	}

	int ebp10 = -1; //loc4
	int ebp14 = 1; //loc5

	switch(skill)
	{
		case 210:
			{
				ebp10 = MagicDamageC.CheckKillCount(210, this->GetKillCountPointFromUser(lpObj->m_Index) );
				
				if(ebp10 < 0)
				{
					ebp14 = 0;
					LogAddTD("[Illusion Temple] (%d) Use Skill KillCount Error (Skill:%d)", this->m_btFloorIndex+1, skill);
					break;
				}
				ebp14 = this->ShieldSpell(lpObj);
			}
			break;
		case 211:
			{
				ebp10 = MagicDamageC.CheckKillCount(211, this->GetKillCountPointFromUser(lpObj->m_Index) );
				
				if(ebp10 < 0)
				{
					ebp14 = 0;
					LogAddTD("[Illusion Temple] (%d) Use Skill KillCount Error (Skill:%d)", this->m_btFloorIndex+1, skill);
					break;
				}
				ebp14 = this->RestrictionSpell(lpObj, lpTargetObj);
			}
			break;
		case 212:
			{
				ebp10 = MagicDamageC.CheckKillCount(212, this->GetKillCountPointFromUser(lpObj->m_Index) );
				
				if(ebp10 < 0)
				{
					ebp14 = 0;
					LogAddTD("[Illusion Temple] (%d) Use Skill KillCount Error (Skill:%d)", this->m_btFloorIndex+1, skill);
					break;
				}
				ebp14 = this->PursuitSpell(lpObj);
			}
			break;
		case 213:
			{
				ebp10 = MagicDamageC.CheckKillCount(213, this->GetKillCountPointFromUser(lpObj->m_Index) );
				
				if(ebp10 < 0)
				{
					ebp14 = 0;
					LogAddTD("[Illusion Temple] (%d) Use Skill KillCount Error (Skill:%d)", this->m_btFloorIndex+1, skill);
					break;
				}
				ebp14 = this->ShieldClashSpell(lpObj, lpTargetObj);
			}
			break;
		default:
			ebp14 = 0;
			break;
	}

	if(ebp14 == 1)
	{
		int ebp18 = this->UpdateKillCountPointFromUser(aIndex, ebp10);
		GCSendIllusionTempleKillCount(aIndex, ebp10);
		this->IncreaseUsedKillCount(aIndex);
		LogAddTD("[Illusion Temple] (%d) Use Skill (%d), (%s)(%s), (%d)",this->m_btFloorIndex+1, skill, lpObj->AccountID, lpObj->Name, ebp10);
	}

	if(skill != 212 )
	{
		if(ebp14 == 1)
		{
			this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 1);
			return;
		}
	}

	if(ebp14 == 0)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpTargetObj->m_Index, skill, 0);
	}
}

void CIllusionTempleProcess::SkillSecondProc(LPOBJ lpObj)
{
	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_iTeamPlayerIndex != lpObj->m_Index)
	{
		return;
	}

	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime > 0)
	{
		this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime--;

		if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime <= 0)
		{
			this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime = 0;
			this->GCIllusionTempleSkillCancel(lpObj, 210);
		}
	}
	
	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime > 0)
	{
		this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime--;

		if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime <= 0)
		{
			this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime = 0;
			this->GCIllusionTempleSkillCancel(lpObj, 211);
		}
	}
}

void CIllusionTempleProcess::GCIllusionTempleSkillCancel(LPOBJ lpObj, WORD skill)
{
	PMSG_CANCEL_SKILL_STATE pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x07, sizeof(pMsg));

	pMsg.m_btSkillIDH = SET_NUMBERH(skill);
	pMsg.m_btSkillIDL = SET_NUMBERL(skill);

	pMsg.m_wTargetIndex = lpObj->m_Index;

	DataSend(lpObj->m_Index,(LPBYTE)&pMsg,pMsg.h.size);
	MsgSendV2(lpObj, (LPBYTE)&pMsg, pMsg.h.size);
}

BOOL CIllusionTempleProcess::ShieldSpell(LPOBJ lpObj) 
{
	this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime = 15;
	return TRUE;
}

BOOL CIllusionTempleProcess::RestrictionSpell(LPOBJ lpObj, LPOBJ lpTargetObj) 
{
	if(gCheckSkillDistance(lpObj->m_Index, lpTargetObj->m_Index, 211) == FALSE)
	{
		return FALSE;
	}

	this->m_FloorData[lpTargetObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime = 15;

	lpTargetObj->lpAttackObj = lpObj;
	lpTargetObj->PathCount = 0;
	lpTargetObj->PathStartEnd = 0;

	gObjSetPosition(lpTargetObj->m_Index, lpTargetObj->X, lpTargetObj->Y);
	return TRUE;
}

BOOL CIllusionTempleProcess::PursuitSpell(LPOBJ lpObj) 
{
	int loc2 = this->m_iBallPlayerIndex;

	if(loc2 == -1)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpObj->m_Index, 212, 0);
		return FALSE;
	}

	if(loc2 == lpObj->m_Index)
	{
		this->GCIllusionTempleSkillApply(lpObj->m_Index, lpObj->m_Index, 212, 0);
		return FALSE;
	}

	this->GCIllusionTempleSkillApply(lpObj->m_Index, lpObj->m_Index, 212, 1);

	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 50; //ebp14
	int loc6 = 0;

	while(loc5-- != 0)
	{
		loc3 = gObj[loc2].X + rand()%3 - 1;
		loc4 = gObj[loc2].Y + rand()%3 - 1;

		if(gObjCheckTeleportArea(lpObj->m_Index,loc3,loc4))
		{
			loc6 = 1;
			break;
		}
	}

	if(loc6 == 0)
	{
		loc3 = gObj[loc2].X;
		loc4 = gObj[loc2].Y;
	}

	gObjTeleportMagicUse(lpObj->m_Index,loc3,loc4);

	return TRUE;
}

BOOL CIllusionTempleProcess::ShieldClashSpell(LPOBJ lpObj, LPOBJ lpTargetObj) 
{
	int loc2;
	if(gCheckSkillDistance(lpObj->m_Index, lpTargetObj->m_Index, 213) == FALSE)
	{
		return FALSE;
	}

	lpTargetObj->lpAttackObj = lpObj;

	if(lpTargetObj->iShield <= 1)
	{
		GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
		return TRUE;
	}

	loc2 = lpTargetObj->iShield / 2;

	lpTargetObj->iShield = loc2;

	GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, loc2);
	return TRUE;
}

void CIllusionTempleProcess::GCIllusionTempleSkillApply(int aIndex, int aTargetIndex, WORD skill, BYTE btUseType)
{
	PMSG_APPLY_SKILL_STATE pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x02, sizeof(pMsg));

	pMsg.m_btType = btUseType;
	pMsg.m_btSkillIDH = SET_NUMBERH(skill);
	pMsg.m_btSkillIDL = SET_NUMBERL(skill);
	pMsg.m_wIndex = aIndex;
	pMsg.m_wTargetIndex = aTargetIndex;

	DataSend(aIndex,(LPBYTE)&pMsg,pMsg.h.size);

	if(btUseType == 1)
	{
		MsgSendV2(&gObj[aIndex], (LPBYTE)&pMsg, pMsg.h.size);
	}
}

void CIllusionTempleProcess::ResetAndClearSkills(LPOBJ lpObj) 
{
	if(lpObj->m_iIllusionTempleIndex == -1 || this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_iTeamPlayerIndex != lpObj->m_Index)
	{
		return;
	}

	this->DropRelicsItem(lpObj->m_Index);

	this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_btKillCountPoint = 10;

	GCSendIllusionTempleKillCount(lpObj->m_Index, 10);

	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime > 0) //Cancel Shield Skill
	{
		this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwShieldSpellTime = 0;
		this->GCIllusionTempleSkillCancel(lpObj, 210);
	}

	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime > 0) //Cancel Stern Skill
	{
		this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_dwRestrictionSpellTime = 0;
		this->GCIllusionTempleSkillCancel(lpObj, 211);
	}
}

void CIllusionTempleProcess::CalcSendRewardEXP() 
{
	this->RemoveInvalid();

	int loc2 = 0;
	int loc3 = 0;

	if(this->m_btYellowTeamScore >= 2 && this->m_btYellowTeamScore > this->m_btBlueTeamScore) //Yellow
	{
		this->m_btWinnerTeam = 0;

		loc2 = (g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+((this->m_btYellowTeamScore-this->m_btBlueTeamScore)*g_IllusionTemple_unk0[this->m_btFloorIndex])) * 2;

		if(this->m_btBlueTeamScore == 0)
		{
			loc3 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex];
		}
		else
		{
			loc3 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+(this->m_btBlueTeamScore*g_IllusionTemple_unk0[this->m_btFloorIndex]);
		}

	}
	else if(this->m_btBlueTeamScore >= 2 && this->m_btYellowTeamScore < this->m_btBlueTeamScore) //Blue
	{
		this->m_btWinnerTeam = 1;

		loc3 = (g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+((this->m_btBlueTeamScore-this->m_btYellowTeamScore)*g_IllusionTemple_unk0[this->m_btFloorIndex])) * 2;

		if(this->m_btBlueTeamScore == 0) //Must be m_btYellowTeamScore
		{
			loc2 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex];

		}
		else
		{
			loc2 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+(this->m_btYellowTeamScore*g_IllusionTemple_unk0[this->m_btFloorIndex]);
		}

	}
	else
	{
		if(this->m_btYellowTeamScore == 0)
		{
			loc2 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex];
		}
		else
		{
			loc2 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+(this->m_btYellowTeamScore*g_IllusionTemple_unk0[this->m_btFloorIndex]);
		}

		if(this->m_btBlueTeamScore == 0)
		{
			loc3 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex];
		}
		else
		{
			loc3 = g_IllusionTemple_Default_Exp[this->m_btFloorIndex]+(this->m_btBlueTeamScore*g_IllusionTemple_unk0[this->m_btFloorIndex]);
		}
	}

	LogAddTD("[Illusion Temple] (%d) Result (WinTeam: %d)(Score:[%d][%d])", this->m_btFloorIndex+1, this->m_btWinnerTeam, this->m_btYellowTeamScore, this->m_btBlueTeamScore);

	int i; //loc4

	for(i = 0;i < MAX_FLOOR_USER;i++)
	{
		if(this->m_FloorData[i].m_btTeamJoinSide == (BYTE)-1)
		{
			continue;
		}

		if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].MapNumber == this->m_btFloorIndex+MAP_INDEX_ILLUSIONTEMPLE &&	this->m_FloorData[i].m_btUsedKillCountPoint >= g_iIllusionTempleMinUseSkillCnt)
		{
			switch(this->m_FloorData[i].m_btTeamJoinSide)
			{
				case 0:
					this->m_FloorData[i].m_i64ExpReward = loc2;
					break;

				case 1:
					this->m_FloorData[i].m_i64ExpReward = loc3;
					break;
			}

			if(gObj[this->m_FloorData[i].m_iTeamPlayerIndex].ChangeUP3rd != 0) //season4 add-on
			{
				this->m_FloorData[i].m_i64ExpReward = this->m_FloorData[i].m_i64ExpReward*g_iIllusionTempleRewardPercentMaster/100;
			}
			else
			{
				this->m_FloorData[i].m_i64ExpReward = this->m_FloorData[i].m_i64ExpReward*g_iIllusionTempleRewardPercent/100;
			}

		//	gObjSealUserSetExp(&gObj[this->m_FloorData[i].m_iTeamPlayerIndex], this->m_FloorData[i].m_i64ExpReward, TRUE); //Seal Exp

			int iPartyCount = 0; //loc5

			if(gObj[this->m_FloorData[i].m_iTeamPlayerIndex].PartyNumber >= 0)
			{
				iPartyCount = gParty.GetCount(gObj[this->m_FloorData[i].m_iTeamPlayerIndex].PartyNumber);
			}
			else
			{
				iPartyCount = 1;
			}

			this->m_FloorData[i].m_dwRankingPoint = ( this->m_FloorData[i].m_i64ExpReward + ( this->m_FloorData[i].m_btUserKillCount * g_IllusionTemple_unk1[this->m_btFloorIndex] ) + ( this->m_FloorData[i].m_btPlayerRewardKillCount * g_IllusionTemple_unk2[this->m_btFloorIndex] ) + g_IllusionTemple_Team_Players[iPartyCount] );

			int loc6 = this->m_FloorData[i].m_i64ExpReward;
			int loc7 = 0;

			while(loc6 > 0)
			{
				loc7 = loc6;
				loc6 = this->LevelUp(this->m_FloorData[i].m_iTeamPlayerIndex, loc6);
			}

			int iIndex = this->m_FloorData[i].m_iTeamPlayerIndex;
		}
	}

	if(g_iSaveIllusionTempleRankingPoint != FALSE)
	{
		for(i = 0;i < MAX_FLOOR_USER;i++)
		{
			if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
			{
				if(this->m_FloorData[i].m_btTeamJoinSide == (BYTE)-1)
				{
					continue;
				}

				PMSG_ILLUSIONTEMPLE_RANKING_UPDATE RankMsg = {0}; //optimization

				RankMsg.h.c = 0xC1;
				RankMsg.h.headcode = 0x26;
				RankMsg.h.size = sizeof(RankMsg);

				RankMsg.aIndex = this->m_FloorData[i].m_iTeamPlayerIndex;

				memcpy(RankMsg.AccountID,gObj[this->m_FloorData[i].m_iTeamPlayerIndex].AccountID,10);

				RankMsg.AccountID[11] = '\0';

				memcpy(RankMsg.Name,gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Name,10);

				RankMsg.Name[11] = '\0';

				RankMsg.ServerCode = Configs.gGameServerCode / 20;

				RankMsg.iIllusionIndex = this->m_btFloorIndex+1;

				RankMsg.iDbClass = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].DbClass;

				RankMsg.iLevel = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Level;

				if(this->m_btWinnerTeam == (BYTE)-1)
				{
					RankMsg.IsWinner = false;
				}
				else
				{
					RankMsg.IsWinner = (this->m_FloorData[i].m_btTeamJoinSide == this->m_btWinnerTeam);
				}

				RankMsg.RankingPoint = this->m_FloorData[i].m_dwRankingPoint;

				DataSendEventChip((char*)&RankMsg,sizeof(RankMsg));
			}
		}
	}
}

void CIllusionTempleProcess::DropRewardItem(int aIndex)
{
	if( OBJMAX_RANGE(aIndex) == FALSE )
	{
		return;
	}

	if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_iTeamPlayerIndex != gObj[aIndex].m_Index)
	{
		return;
	}

	if(this->GetState() != 3)
	{
		return;
	}

	if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide == (BYTE)-1)
	{
		return;
	}

	if(this->m_btWinnerTeam == (BYTE)-1)
	{
		return;
	}

	if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_btTeamJoinSide != this->m_btWinnerTeam)
	{
		return;
	}

	if(this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_bDropReward == 1)
	{
		return;
	}

	this->m_FloorData[gObj[aIndex].m_iIllusionTempleIndex].m_bDropReward = 1;
	int loc2 = aIndex;
	int loc3 = ItemGetNumberMake(12, 15);	// Jewel of Chaos
	ItemSerialCreateSend(gObj[aIndex].m_Index, gObj[aIndex].MapNumber, gObj[aIndex].X, gObj[aIndex].Y,loc3, 0, 0, 0, 0, 0, loc2, 0, 0);
}

int CIllusionTempleProcess::CheckEnterItemPosition(int aIndex, float Durability) //used by gs 56
{
	if(OBJMAX_RANGE(aIndex) == FALSE)
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	int loc2 = -1;

	for( int i = 0; i<INVENTORY_SIZE; i++ )
	{
		if( gObj[aIndex].pInventory[i].IsItem() == TRUE )
		{
			if(gObj[aIndex].pInventory[i].m_Type == ITEMGET(13,51) && gObj[aIndex].pInventory[i].m_Level == this->m_btFloorIndex+1) //Blood Scroll
			{
				if(gObj[aIndex].pInventory[i].m_Durability == Durability)
				{
					return i;
				}
			}
			if(gObj[aIndex].pInventory[i].m_Type == ITEMGET(13,61)) //Illusion Temple Ticket (CashShop)
			{
				if(gObj[aIndex].pInventory[i].m_Durability > 0.0f)
				{
					loc2 = i;
				}
			}
		}
	}

	if(loc2 >= 0)
	{
		return loc2;
	}

	return -1;
}

int CIllusionTempleProcess::CheckEnterItemPosition(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == FALSE)
	{
		LogAdd("return %s %d", __FILE__, __LINE__);
		return -1;
	}

	int loc2 = -1;

	for( int i = 0; i<INVENTORY_SIZE; i++ )
	{
		CItem * lpItem = &gObj[aIndex].pInventory[i];

		if( lpItem->IsItem() == TRUE )
		{
			if(lpItem->m_Type == ITEMGET(13,51) && lpItem->m_Level == this->m_btFloorIndex+1) //Blood Scroll
			{
				if(lpItem->m_Durability > 0.0f)
				{
					loc2 = i;
					break;
				}

				gObjInventoryDeleteItem(aIndex, i);
				GCInventoryItemDeleteSend(aIndex, i, 0);
			}
			if(lpItem->m_Type == ITEMGET(13,61)) //Illusion Temple Ticket (CashShop)
			{
				if(lpItem->m_Durability > 0.0f)
				{
					if(lpItem->m_Durability > 0.0f)
					{
						loc2 = i;
						break;
					}

					gObjInventoryDeleteItem(aIndex, i);
					GCInventoryItemDeleteSend(aIndex, i, 0);
				}
			}
		}
	}

	return loc2;
}

void CIllusionTempleProcess::DropMonsterItem(LPOBJ lpObj) 
{
	if(this->m_FloorData[lpObj->m_iIllusionTempleIndex].m_iTeamPlayerIndex != lpObj->m_Index)
	{
		return;
	}

	switch(lpObj->MapNumber - MAP_INDEX_ILLUSIONTEMPLE_MIN)
	{
		case 0:
		case 1:
			IllusionTemple1ItemBag->DropIllusionTempleEventReward(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y);
			break;
		case 2:
		case 3:
			IllusionTemple2ItemBag->DropIllusionTempleEventReward(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y);
			break;
		case 4:
		case 5:
			IllusionTemple3ItemBag->DropIllusionTempleEventReward(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y);
			break;
	}
}

void CIllusionTempleProcess::SendAllUserAnyMsg(LPBYTE lpMsg, int iSize) 
{
	for( int aIndex = OBJ_STARTUSERINDEX; aIndex<OBJMAX; aIndex++ )
	{
		if(gObj[aIndex].Connected == PLAYER_PLAYING && gObj[aIndex].Type == OBJ_USER)
		{
			DataSend(aIndex,lpMsg,iSize);
		}
	}
}

int CIllusionTempleProcess::LevelUp(int iUserIndex, int iAddExp) 
{
	if(OBJMAX_RANGE(iUserIndex ) == FALSE)
	{
		return 0;
	}

	gObjSetExpPetItem(iUserIndex, iAddExp);

	int iLEFT_EXP = 0;

	LogAddTD("Experience : Map[%d]-(%d,%d) [%s][%s](%d) %u %d ", gObj[iUserIndex].MapNumber, gObj[iUserIndex].X, gObj[iUserIndex].X, gObj[iUserIndex].AccountID, gObj[iUserIndex].Name,	gObj[iUserIndex].Level, gObj[iUserIndex].Experience, iAddExp);

	if(gObj[iUserIndex].Level >= MAX_CHAR_LEVEL)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 112)), gObj[iUserIndex].m_Index, 1);
		return 0;
	}

	if((gObj[iUserIndex].Experience + iAddExp) < gObj[iUserIndex].NextExp)
	{
		gObj[iUserIndex].Experience += iAddExp;
	}
	else
	{
		iLEFT_EXP = gObj[iUserIndex].Experience + iAddExp - gObj[iUserIndex].NextExp;
		gObj[iUserIndex].Experience = gObj[iUserIndex].NextExp;
		gObj[iUserIndex].Level++;

		if(gObj[iUserIndex].Class == CLASS_DARKLORD || gObj[iUserIndex].Class == CLASS_MAGUMSA)
		{
			gObj[iUserIndex].LevelUpPoint += 7;
		}
		else
		{
			gObj[iUserIndex].LevelUpPoint += 5;
		}

		if(gObj[iUserIndex].PlusStatQuestClear != false)
		{
			gObj[iUserIndex].LevelUpPoint++;

			LogAddTD("[%s][%s] LevelUp PlusStatQuest Clear AddStat %d", gObj[iUserIndex].AccountID, gObj[iUserIndex].Name, gObj[iUserIndex].LevelUpPoint);
		}

		gObj[iUserIndex].MaxLife += DCInfo.DefClass[gObj[iUserIndex].Class].LevelLife;
		gObj[iUserIndex].MaxMana += DCInfo.DefClass[gObj[iUserIndex].Class].LevelMana;
		gObj[iUserIndex].Life = gObj[iUserIndex].MaxLife;
		gObj[iUserIndex].Mana = gObj[iUserIndex].MaxMana;
		gObjNextExpCal(&gObj[iUserIndex]);
		gObjSetBP(gObj[iUserIndex].m_Index);
		GCLevelUpMsgSend(gObj[iUserIndex].m_Index, 1);
		gObjCalcMaxLifePower(gObj[iUserIndex].m_Index);

		LogAddTD(lMsg.Get(MSGGET(2, 8)), gObj[iUserIndex].AccountID, gObj[iUserIndex].Name, gObj[iUserIndex].Level);

		//----------------------------------------------------------------------------------------------

		if( gObj[iUserIndex].Level == 400 && gObj[iUserIndex].PartyNumber >= 0 )
		{
			int iPartyNumber = gObj[iUserIndex].PartyNumber;
			char szMsg[256];
			sprintf(szMsg,"400 LevelUp (%s)(%s) Party ",gObj[iUserIndex].AccountID,gObj[iUserIndex].Name);
			int iPartyNumIndex;

			for( int i = 0; i<MAX_USER_IN_PARTY; i++ )
			{
				iPartyNumIndex = gParty.m_PartyS[iPartyNumber].Number[i];

				if( iPartyNumIndex >= 0  )
				{
					int iSize = strlen(szMsg);
					sprintf(&szMsg[iSize],",(%s)(%s) ",gObj[iPartyNumIndex].AccountID,gObj[iPartyNumIndex].Name);
				}
			}
			LogAddTD(szMsg);
		}
	}

	GJSetCharacterInfo(&gObj[iUserIndex], gObj[iUserIndex].m_Index, 0);

	return iLEFT_EXP;
}

BYTE CIllusionTempleProcess::GetRemainTime() 
{
	if(!this->GetState())
	{
		return this->m_iLeftMinutesBeforeOpen;
	}

	return 0;
}

BOOL CIllusionTempleProcess::CheckShieldSpellTime(int aIndex)
{
	if(CHECK_LIMIT( (aIndex), MAX_FLOOR_USER) == FALSE)
	{
		return FALSE;
	}

	if(this->m_FloorData[aIndex].m_iTeamPlayerIndex != -1)
	{
		if(this->m_FloorData[aIndex].m_dwShieldSpellTime > 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CIllusionTempleProcess::CheckRestrictionSpellTime(int aIndex)
{
	if(CHECK_LIMIT( (aIndex), MAX_FLOOR_USER) == FALSE)
	{
		return FALSE;
	}

	if(this->m_FloorData[aIndex].m_iTeamPlayerIndex != -1)
	{
		if(this->m_FloorData[aIndex].m_dwRestrictionSpellTime > 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CIllusionTempleProcess::SendRewardScore() 
{
	int loc2 = 0;

	char cTEMP_BUF[256];
	_ILLUSIONTEMPLE_RANKING_DATA pMsg;

	pMsg.m_btYellowTeamScore = this->m_btYellowTeamScore;
	pMsg.m_btBlueTeamScore = this->m_btBlueTeamScore;
	pMsg.m_btEnteredUserCount = this->m_iEnteredUserCount;

	loc2 += sizeof(_ILLUSIONTEMPLE_RANKING_DATA);

	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		_ILLUSIONTEMPLE_PLAYER_RANK_DATA TempMsg;

		if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			
		//	TempMsg.m_btMapNumber = this->m_btFloorIndex + MAP_INDEX_ILLUSIONTEMPLE_MIN;
			TempMsg.ChangeUP = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].ChangeUP;
			TempMsg.m_btClass = gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Class;
			TempMsg.m_btTeamJoinSide = this->m_FloorData[i].m_btTeamJoinSide;
			//TempMsg.m_dwExpReward = this->m_FloorData[i].m_i64ExpReward;
			memcpy(TempMsg.szCharacterName, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Name, 10);
			memcpy(&cTEMP_BUF[loc2],&TempMsg,sizeof(_ILLUSIONTEMPLE_PLAYER_RANK_DATA));

			loc2 += sizeof(_ILLUSIONTEMPLE_PLAYER_RANK_DATA);

			LogAddTD("[Illusion Temple] (%d) RewardExp Result  (Account:%s, Name:%s, Team:%d, Class:%d, UserKillCount:%d, RelicsMoveCount:%d, RewardExp:%d, RankingPoint: %d)", this->m_btFloorIndex+1, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].AccountID, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Name, this->m_FloorData[i].m_btTeamJoinSide, gObj[this->m_FloorData[i].m_iTeamPlayerIndex].DbClass, this->m_FloorData[i].m_btUserKillCount, this->m_FloorData[i].m_btPlayerRewardKillCount, this->m_FloorData[i].m_i64ExpReward, this->m_FloorData[i].m_dwRankingPoint);
		}
	}

	PHeadSubSetB((LPBYTE)&pMsg, 0xBF, 0x04, loc2);

	memcpy(cTEMP_BUF,&pMsg,sizeof(pMsg));

	for(int i = 0; i < MAX_FLOOR_USER; i++)
	{
		if(this->m_FloorData[i].m_btTeamJoinSide == (BYTE)-1)
		{
			continue;
		}

		if(this->m_FloorData[i].m_iTeamPlayerIndex != -1 && gObj[this->m_FloorData[i].m_iTeamPlayerIndex].Connected > PLAYER_LOGGED)
		{
			DataSend(this->m_FloorData[i].m_iTeamPlayerIndex,(LPBYTE)cTEMP_BUF,pMsg.h.size);
		}
	}
}