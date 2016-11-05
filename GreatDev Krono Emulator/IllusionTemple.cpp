 // --------------------------------------------------------------- //
 // Project:	MU.NET.PL - Season 3 Episode I & Episode II project //
 // Author:		f1x & Gravers										//
 // Coded by:	f1x													//
 // Date:		2007-12-28 :: 16:55									//
 // File:		MUNET.cpp :: MUNET\\src\\game\\illusion.cpp			//
 // Hint:		Illusion Temple Event for GameServer 1.00.18		//
 // --------------------------------------------------------------- //

#include "stdafx.h"
#include "IllusionTemple.h"


unsigned IL_EVENT_STATE = IL_STATE_IDLE;
short IL_BATTLE_TIMER = IL_TIMERVALUE;
IL_BATTLESTRUCT Battle[IL_MAXBATTLE];

struct sIllusionConf
{
	int isIllusionTemple;
	int m_IllusionDayStep;
	int OldScrollDropRate;
	int m_IllusionStartHour;
	int CovenantOfIllusionDropRate;
}IllusionConf;

void LoadIllusionTempleConfig()
{
	IllusionConf.isIllusionTemple					= 1;
	IllusionConf.m_IllusionDayStep					= 1;		
	IllusionConf.m_IllusionStartHour				= 15;
	IllusionConf.CovenantOfIllusionDropRate			= 75;
	IllusionConf.OldScrollDropRate					= 75;
}

void ILTIMER_Noticer()
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	char Notice[128];

	if((t.wDay % IllusionConf.m_IllusionDayStep) == 0)
	{
		if((t.wHour + 1) == IllusionConf.m_IllusionStartHour) // one hour before
		{
			if(t.wMinute == 29 || t.wMinute == 39)
			{
				sprintf_s(Notice, "[Illusion] Employee will be active after %d minutes.", 44 - t.wMinute);
				AllSendServerMsg(Notice);
				LogAdd("[ ILLUSION TIMER ] %d minutes to activate NPC.", 44 - t.wMinute);
			}

			if(t.wMinute == 44)
			{
				IL_EVENT_STATE = IL_STATE_GUARD_ACTIVE;

				sprintf_s(Notice, "[Illusion] Employee is active now.");
				AllSendServerMsg(Notice);
				LogAdd("[ ILLUSION TIMER ] Changed state to IL_STATE_GUARD_ACTIVE.");
			}

			if(t.wMinute == 49 || t.wMinute == 54)
			{
				IL_EVENT_STATE = IL_STATE_GUARD_ACTIVE;

				sprintf_s(Notice, "[Illusion] Employee will be inactive after %d minutes.", 59 - t.wMinute);
				AllSendServerMsg(Notice);
				LogAdd("[ ILLUSION TIMER ] %d minutes to deactivate NPC.", 59 - t.wMinute);
			}

			if(t.wMinute == 59)
			{
				IL_EVENT_STATE = IL_STATE_GUARD_INACTIVE;

				sprintf_s(Notice, "[Illusion] Employee is inactive now. Try again later.");
				AllSendServerMsg(Notice);
				LogAdd("[ ILLUSION TIMER ] Changed state to IL_STATE_GUARD_INACTIVE.");
			}
		}

		if(t.wHour == IllusionConf.m_IllusionStartHour && t.wMinute == 00)
		{
			IL_EVENT_STATE = IL_STATE_BATTLE_START;

			LogAdd("[ ILLUSION TIMER ] Changed state to IL_STATE_BATTLE_START.");
		}

		if(t.wHour == IllusionConf.m_IllusionStartHour && t.wMinute == 25)
		{
			IL_EVENT_STATE = IL_STATE_BATTLE_CLEAR;
			
			LogAdd("[ ILLUSION TIMER ] Changed state to IL_STATE_BATTLE_CLEAR.");
		}
	}
}
/**/
void ILPROC_Core() {
	switch(IL_EVENT_STATE)
	{
	case IL_STATE_BATTLE_START:
		ILAPI_SetupBattles();
		ILAPI_SetBattlesStatus();
		
		if(ILAPI_GetActiveBattlesCount() == 0)
		{
			ILAPI_ClearEvent();
			LogAdd("[ ILLUSION ] Any battle isn't active. Cycle has been broken.");
		}

		else
		{
			ILSCENARIO_StartBattle();
			IL_BATTLE_TIMER = IL_TIMERVALUE;
			IL_EVENT_STATE = IL_STATE_BATTLE;
			LogAdd("[ ILLUSION ] %d battles are actives. Cycle has been continued.", ILAPI_GetActiveBattlesCount());
		}
		break;

	case IL_STATE_BATTLE:
		IL_BATTLE_TIMER--;

		if(IL_BATTLE_TIMER == 0)
		{
			IL_EVENT_STATE = IL_STATE_BATTLE_END;
			LogAdd("[ ILLUSION TIMER ] Changed state to IL_STATE_BATTLE_END.");
		}

		ILPROTO_GCIllusionStateSend();
		ILPROC_PlayersProc();
		ILPROC_SkillsProc();

		if(ILAPI_GetActiveBattlesCount() == 0)
		{
			ILAPI_ClearEvent();
			LogAdd("[ ILLUSION ] All battles capitulated. Reseted event.");
		}
		break;

	case IL_STATE_BATTLE_END:
		ILSCENARIO_EndBattle();
		IL_EVENT_STATE = IL_STATE_BATTLE_CLIDLE;
		/*  TODO:
			1. Wyswietlic statystyki eventu.
			2. Dac nagrode i przeniesc do miasta (po kliknieciu w przycisk).
		*/
		break;

	case IL_STATE_BATTLE_CLEAR:
		ILSCENARIO_TownTeleport();
		ILAPI_ClearEvent();
	}
}
void ILPROC_SkillsProc() {
	for(unsigned bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		if(Battle[bId].Active)
		{
			for(unsigned tId = 0; tId < IL_MAXTEAM; tId++)
			{
				for(int pId = 0; pId < ILAPI_GetTeamMembersCount(&Battle[bId].Team[tId]); pId++)
				{
					IL_OBJECTSTRUCT *pPlayer = &Battle[bId].Team[tId].v_Members.at(pId);

					if(pPlayer->usingSkillId != 0) // using skill
					{
						if(pPlayer->usingSkillTime > 0)
						{
							pPlayer->usingSkillTime--;
						}

						else
						{
							ILSKILL_DissapearSkill(pPlayer);
						}
					}
				}
			}
		}
	}
}
void ILPROC_PlayersProc() {
	for(int bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		if(Battle[bId].Active)
		{
			for(int tId = 0; tId < IL_MAXTEAM; tId++)
			{
				for(int pId = 0; pId < ILAPI_GetTeamMembersCount(&Battle[bId].Team[tId]); pId++)
				{
					IL_OBJECTSTRUCT *pPlayer = &Battle[bId].Team[tId].v_Members.at(pId);
					int aTmpIndex = -2;
					
					if(gObj[pPlayer->aIndex].Life == 0.0)
					{
						ILAPI_KillPointsManage(&Battle[bId].Team[!tId], 5, IL_KP_ADD);
						gObj[pPlayer->aIndex].Life = (float)0.1;
						aTmpIndex = pPlayer->aIndex;
						LogAdd("[%s][%s] [ ILLUSION ] Player has been killed.", gObj[pPlayer->aIndex].AccountID, gObj[pPlayer->aIndex].Name);
					}

					if(gObj[pPlayer->aIndex].MapNumber != 44 + pPlayer->m_BattleId)
					{
						if(pPlayer->usingSkillId != 0)
						{
							ILSKILL_DissapearSkill(pPlayer);
						}

						//Battle[bId].Team[tId].v_Members.erase(Battle[bId].Team[tId].v_Members.begin() + pId);
						ILAPI_DeleteMember(pPlayer->aIndex);
						aTmpIndex = pPlayer->aIndex;
						LogAdd("[%s][%s] [ ILLUSION ] Deleted from event. Reason: invalid map.", gObj[pPlayer->aIndex].AccountID, gObj[pPlayer->aIndex].Name);
					}

					if(gObj[pPlayer->aIndex].Connected == PLAYER_EMPTY)
					{
						//Battle[bId].Team[tId].v_Members.erase(Battle[bId].Team[tId].v_Members.begin() + pId);
						ILAPI_DeleteMember(pPlayer->aIndex);
						aTmpIndex = pPlayer->aIndex;
						LogAdd("[%s][%s] [ ILLUSION ] Deleted from event. Reason: Account inactive.", gObj[pPlayer->aIndex].AccountID, gObj[pPlayer->aIndex].Name);
					}

					if(Battle[bId].aHeroIndex == aTmpIndex)
					{
						ILAPI_GiftUserClear(aTmpIndex);
						LogAdd("[ ILLUSION ] Hero has been defeated. ", gObj[aTmpIndex].AccountID, gObj[aTmpIndex].Name);
					}
				}
			}

			if(ILAPI_GetBattleMembersCount(&Battle[bId]) == 0)
			{
				ILAPI_ClearBattle(&Battle[bId]);
				LogAdd("[ ILLUSION ] All users capitulate. End battle.");
			}
		}
	}
}
/**/
void ILPROTO_ProtocolCore(int aIndex, unsigned char *pMsg, unsigned Length) {
	switch(pMsg[3])
	{
	case IL_PROTO_REGISTER:
		ILAPI_RegisterMember(aIndex, pMsg[5], pMsg[4]);
		break;

	case IL_PROTO_USESKILL: 
		ILSKILL_SkillUse(aIndex, (pMsg[5] * 256) + pMsg[6], pMsg[4]);
		break;

	case IL_PROTO_ADDREWARD:
		ILAPI_DeleteMember(aIndex);
		gObjTeleport(aIndex, 0, 130, 133);
		break;
	}
}
void ILPROTO_GCIllusionStateSend() {
	PMSG_ILLUSION_EVENTSTATE evState;

	evState.head.head = 0xc1;
	evState.head.len = 0x00;
	evState.head.type = 0xbf;
	evState.subtype = 0x01;
	evState.Timer = IL_BATTLE_TIMER;

	for(unsigned bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		evState.aHeroIndex = Battle[bId].aHeroIndex;
		evState.HeroX = (unsigned char)gObj[Battle[bId].aHeroIndex].X;
		evState.HeroY = (unsigned char)gObj[Battle[bId].aHeroIndex].Y;
		evState.RedPoints = Battle[bId].Team[IL_COLOR_RED].m_Points;
		evState.BluePoints = Battle[bId].Team[IL_COLOR_BLUE].m_Points;

		for(unsigned tId = 0; tId < IL_MAXTEAM; tId++)
		{
			evState.RadarColor = tId;
			evState.PlayersCount = ILAPI_GetTeamMembersCount(&Battle[bId].Team[tId]);
			evState.head.len = 14 + (evState.PlayersCount * sizeof(PMSG_ILLUSION_RADAR));
			ILPROTO_GenIllusionRadar(&Battle[bId].Team[tId], evState.Radar);
			ILAPI_SendDataTeam(&Battle[bId].Team[!tId], (unsigned char*)&evState, evState.head.len);
		}
	}
}
void ILPROTO_GenIllusionRadar(IL_TEAMSTRUCT *pTeam, PMSG_ILLUSION_RADAR *pRadar) {
	ZeroMemory(pRadar, sizeof(*pRadar) * 5);

	for(int i = 0; i < ILAPI_GetTeamMembersCount(pTeam); i++)
	{
		pRadar[i].aIndex = (unsigned short)pTeam->v_Members.at(i).aIndex;
		pRadar[i].X = (unsigned char)gObj[pRadar->aIndex].X;
		pRadar[i].Y = (unsigned char)gObj[pRadar->aIndex].Y;
	}
}
void ILPROTO_GCIllusionOverStatisticsSend() {
	PMSG_ILLUSION_STATISTICS msgStats;
	msgStats.head.head = 0xc1;
	msgStats.head.type = 0xbf;
	msgStats.subtype = 0x04;

	for(unsigned bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		if(Battle[bId].Active)
		{
			for(unsigned tId = 0; tId < IL_MAXTEAM; tId++)
			{
				for(unsigned pId = 0; pId < Battle[bId].Team[tId].v_Members.size(); pId++)
				{
					int aIndex = Battle[bId].Team[tId].v_Members.at(pId).aIndex;

					msgStats.RedPoints = Battle[bId].Team[IL_COLOR_RED].m_Points;
					msgStats.BluePoints = Battle[bId].Team[IL_COLOR_BLUE].m_Points;
					msgStats.Data[pId].ChangeUP = gObj[aIndex].ChangeUP;
					msgStats.Data[pId].Class = (unsigned char)gObj[aIndex].Class;
					msgStats.Data[pId].Color = !Battle[bId].Team[tId].m_Color;
					memcpy(msgStats.Data[pId].Name, gObj[aIndex].Name, 10);
				}
			}

			msgStats.PlayersCount = ILAPI_GetBattleMembersCount(&Battle[bId]);
			msgStats.head.len = 7 + (msgStats.PlayersCount * sizeof(PMSG_ILLUSION_STATISTICS_DATA));
			ILAPI_SendDataBattle(&Battle[bId], (unsigned char*)&msgStats, msgStats.head.len);
			ZeroMemory(&msgStats.Data, sizeof(PMSG_ILLUSION_STATISTICS_DATA) * 10);
		}
	}
}
/**/
void ILSKILL_GCSendSkillEffectStart(int aIndex, int aTargetIndex, unsigned char SkillId, unsigned char SkillLen) {
	PMSG_ILLUSION_ACTIVESKILL Msg;
	Msg.head.head = 0xc1;
	Msg.head.len = 0x0a;
	Msg.head.type = 0xbf;
	Msg.subtype = 0x02;
	Msg.SkillId = SkillId;
	Msg.useTime = SkillLen;
	Msg.aOwnerIndex = (short)aIndex;
	Msg.aRecvrIndex = (short)aTargetIndex;

	ILAPI_SendDataBattle((IL_BATTLESTRUCT*)ILAPI_Handle(aIndex, IL_HANDBATTLE), (unsigned char*)&Msg, 10);
}
void ILSKILL_GCSendSkillEffectEnd(int aIndex, unsigned char SkillId) {
	PMSG_ILLUSION_DEACTIVESKILL Msg;
	Msg.head.head = 0xc1;
	Msg.head.len = 0x08;
	Msg.head.type = 0xbf;
	Msg.subtype = 0x07;
	Msg.aOwnerIndex = aIndex;
	Msg.SkillId = SkillId;
	ILAPI_SendDataBattle((IL_BATTLESTRUCT*)ILAPI_Handle(aIndex, IL_HANDBATTLE), (unsigned char*)&Msg, 10);
}
void ILSKILL_SkillUse(int aIndex, int aTargetIndex, unsigned char SkillId) {
	if(SkillId >= IL_ORDER_OF_PROTECT && SkillId <= IL_ORDER_OF_SHIELD)
	{
		if(ILAPI_Handle(aIndex, IL_HANDPLAYER) != NULL && ILAPI_Handle(aTargetIndex, IL_HANDPLAYER) != NULL) // jest na evencie
		{
			IL_OBJECTSTRUCT *pPlayer =  (IL_OBJECTSTRUCT*)ILAPI_Handle(aIndex, IL_HANDPLAYER);
			IL_TEAMSTRUCT *pTeam = (IL_TEAMSTRUCT*)ILAPI_Handle(aIndex, IL_HANDTEAM);

			if(pTeam == NULL) // security
				return;

			unsigned NeedPts = 5;
			if(SkillId == IL_ORDER_OF_TRACKING)
				NeedPts = 10;

			if(pTeam->m_KillPoints >= NeedPts) // jesli team ma punkty
			{
				ILAPI_KillPointsManage(pTeam, NeedPts, IL_KP_SUB);

				unsigned char SkillLen = IL_SKILL_NEW;
				if(pPlayer->usingSkillId == SkillId) // chce kontynuowac dzialanie obecnego skilla
				{
					SkillLen = IL_SKILL_CONTINUE;
					LogAdd("[%s][%s] [ ILLUSION SKILL ] Continue skill at target[%d]: Id(%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, aTargetIndex, SkillId);
				}

				else // nowy skill
				{
					LogAdd("[%s][%s] [ ILLUSION SKILL ] Used Skill at target[%d]: Id(%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, aTargetIndex, SkillId);
				}

				pPlayer->aAttackedIndex = aTargetIndex;
				pPlayer->usingSkillId = SkillId;

				switch(SkillId)
				{
				case IL_ORDER_OF_PROTECT:
					pPlayer->usingSkillTime = 15;
					ILSKILL_GCSendSkillEffectStart(aIndex, aTargetIndex, IL_ORDER_OF_PROTECT, SkillLen);
					break;

				case IL_ORDER_OF_FREEZE:
					pPlayer->usingSkillTime = 15;
					ILSKILL_GCSendSkillEffectStart(aIndex, aTargetIndex, IL_ORDER_OF_FREEZE, SkillLen);
					break;

				case IL_ORDER_OF_TRACKING:
					gObjTeleport(aIndex, gObj[aTargetIndex].MapNumber, gObj[aTargetIndex].X, gObj[aTargetIndex].Y);
					ILSKILL_GCSendSkillEffectStart(aIndex, aTargetIndex, IL_ORDER_OF_TRACKING, SkillLen);
					break;

				case IL_ORDER_OF_SHIELD:
					ILSKILL_GCSendSkillEffectStart(aIndex, aTargetIndex, IL_ORDER_OF_SHIELD, SkillLen);
					break;
				}
			}

			else
			{
				LogAdd("[%s][%s] [ ILLUSION SKILL ] Not enough KillPoints %d < %d.", gObj[aIndex].AccountID, gObj[aIndex].Name, pTeam->m_KillPoints, NeedPts);
			}
		}

		else
		{
			LogAdd("[%s][%s] [ ILLUSION SKILL ] User or target isn't event member.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		}
	}
	else
	{
		LogAdd("[%s][%s] [ ILLUSION SKILL ] Invalid SkillId(%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, SkillId);
	}
}
void ILSKILL_DissapearSkill(IL_OBJECTSTRUCT *pPlayer) {
	switch(pPlayer->usingSkillId)
	{
	case 0xd2:
		break;
	
	case 0xd3:
		break;
	}

	ILSKILL_GCSendSkillEffectEnd(pPlayer->aAttackedIndex, pPlayer->usingSkillId);
	LogAdd("[%s][%s] [ ILLUSION SKILL ] Skill (%d) has been dissapeared.", gObj[pPlayer->aIndex].AccountID, gObj[pPlayer->aIndex].Name, pPlayer->usingSkillId);

	pPlayer->usingSkillId = 0;
	pPlayer->usingSkillTime = 0;
	pPlayer->aAttackedIndex = OBJ_EMPTY;
}
void ILSKILL_DissapearAllPlayersSkill() {
	for(unsigned bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		if(Battle[bId].Active)
		{
			for(unsigned tId = 0; tId < IL_MAXTEAM; tId++)
			{
				for(int pId = 0; pId < ILAPI_GetTeamMembersCount(&Battle[bId].Team[tId]); pId++)
				{
					register IL_OBJECTSTRUCT *pPlayer = &Battle[bId].Team[tId].v_Members.at(pId);

					if(pPlayer->usingSkillId != 0) // using skill
					{
						ILSKILL_DissapearSkill(pPlayer);
					}
				}
			}
		}
	}
}
/**/
void ILSCENARIO_StartBattle() {
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		if(Battle[i].Active)
		{
			ILAPI_MaskTeam(&Battle[i].Team[0], IL_MASK_RED);
			ILAPI_MaskTeam(&Battle[i].Team[0], IL_MASK_BLUE);

			ILAPI_TeleportTeam(&Battle[i].Team[0], 45 + i, 143, 43);
			ILAPI_TeleportTeam(&Battle[i].Team[1], 45 + i, 197, 124);

			unsigned char MsgInterface[6] = {0xc1, 0x06, 0xbf, 0x09, 0x00, 0x01};
			unsigned char MsgOpenGates[6] =	{0xc1, 0x06, 0xbf, 0x09, 0x00, 0x02};

			ILAPI_SendDataBattle(&Battle[i], MsgInterface, 6);
			ILAPI_SendDataBattle(&Battle[i], MsgOpenGates, 6);
			ILAPI_SendMessageBattle(&Battle[i], "[Illusion] Fight!");
			ILAPI_KillPointsManage(&Battle[4].Team[0], 155, IL_KP_ADD);
			ILAPI_KillPointsManage(&Battle[4].Team[1], 155, IL_KP_ADD);
		}
	}
}
void ILSCENARIO_EndBattle() {
	ILSKILL_DissapearAllPlayersSkill();
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		if(Battle[i].Active)
		{
			ILAPI_MaskTeam(&Battle[i].Team[0], -1);
			ILAPI_MaskTeam(&Battle[i].Team[0], -1);

			ILAPI_TeleportTeam(&Battle[i].Team[0], 45 + i, 143, 43);
			ILAPI_TeleportTeam(&Battle[i].Team[1], 45 + i, 197, 124);

			unsigned char MsgCloseGates[6] =	{0xc1, 0x06, 0xbf, 0x09, 0x00, 0x03};
			ILAPI_SendDataBattle(&Battle[i], MsgCloseGates, 6);
		}
	}

	ILPROTO_GCIllusionOverStatisticsSend();
}
void ILSCENARIO_TownTeleport() {
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		if(Battle[i].Active)
		{
			ILAPI_TeleportTeam(&Battle[i].Team[0], 0, 130, 133 - (i * 2));
			ILAPI_TeleportTeam(&Battle[i].Team[1], 0, 130, 133 - (i * 2));
		}
	}
}
/**/
unsigned char ILAPI_GetTempleLevel(short UserLevel) {
	if(UserLevel >= 220 && UserLevel <= 270)
		return 1;
	if(UserLevel >= 271 && UserLevel <= 320)
		return 2;
	if(UserLevel >= 321 && UserLevel <= 350)
		return 3;
	if(UserLevel >= 351 && UserLevel <= 380)
		return 4;
	if(UserLevel >= 381 && UserLevel <= 500)
		return 5;

	return 0;
}
bool ILAPI_ReduceTicket(int aIndex, int TicketPos) {
	if(gObj[aIndex].pInventory[TicketPos].m_Durability >= 85.0)
	{
		gObj[aIndex].pInventory[TicketPos].m_Durability -= 85.0;
		GCItemDurSend2(aIndex, TicketPos, (int)gObj[aIndex].pInventory[TicketPos].m_Durability, 0);
		return true;
	}

	else
	{
		return false;
	}
}
bool ILAPI_RegisterMember(int aIndex, int TicketPos, int TargetTemple) {
	if(ILAPI_Handle(aIndex, IL_HANDPLAYER) != NULL)
	{
		gObjTeleport(aIndex, 44 + TargetTemple, 110, 133);
		LogAdd("[%s][%s] [ ILLUSION ] Found user on event.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return true;
	}

	if(IL_EVENT_STATE != IL_STATE_GUARD_ACTIVE)
	{
		GCServerMsgStringSend("[Illusion]: Sorry, employee is inactive now.", aIndex, 1);
		LogAdd("[%s][%s][ ILLUSION ] Can't enter, when NPC is inactive.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return false;
	}

	if(ILAPI_GetBattleMembersCount(&Battle[TargetTemple - 1]) > 9)
	{
		GCServerMsgStringSend("[Illusion]: Sorry, temple is full.", aIndex, 1);
		LogAdd("[%s][%s][ ILLUSION ] Temple %d is full.", gObj[aIndex].AccountID, gObj[aIndex].Name, TargetTemple);
		return false;
	}

	if(!ILAPI_ReduceTicket(aIndex, TicketPos))
	{
		GCServerMsgStringSend("[Illusion]: Sorry, your ticket is broken.", aIndex, 1);
		LogAdd("[%s][%s][ ILLUSION ] Can't authorize invite.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return false;
	}

	unsigned char TeamColor = IL_COLOR_RED;
	if(ILAPI_GetTeamMembersCount(&Battle[TargetTemple - 1].Team[IL_COLOR_RED]) > ILAPI_GetTeamMembersCount(&Battle[TargetTemple - 1].Team[IL_COLOR_BLUE]))
	{
		TeamColor = IL_COLOR_BLUE;
	}

	IL_OBJECTSTRUCT newPlayer = {aIndex, -1, 0, 0, TeamColor, TargetTemple};
	Battle[TargetTemple - 1].Team[TeamColor].v_Members.push_back(newPlayer);
	gObjTeleport(aIndex, 44 + (TargetTemple - 1), 110, 133);
	LogAdd("[%s][%s] [ ILLUSION ] Added to event (%d/%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, newPlayer.m_TeamColor, newPlayer.m_BattleId);
	return true;
}
void* ILAPI_Handle(int aIndex, IL_HANDLETYPE hType) {
	for(unsigned bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		for(unsigned tId = 0; tId < IL_MAXTEAM; tId++)
		{
			for(unsigned pId = 0; pId < Battle[bId].Team[tId].v_Members.size(); pId++)
			{
				if(aIndex == Battle[bId].Team[tId].v_Members.at(pId).aIndex)
				{
					switch(hType)
					{
					case IL_HANDPLAYER:
						return &Battle[bId].Team[tId].v_Members.at(pId);
						break;
					case IL_HANDTEAM:
						return &Battle[bId].Team[tId];
						break;
					case IL_HANDBATTLE:
						return &Battle[bId];
						break;
					}
					LogAdd("[%s][%s] [ ILLUSION HANDLER ] Found on event at (%d/%d/%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, pId, tId, bId);
					break;
				}
			}
		}
	}
	return NULL;
}
void ILAPI_DeleteMember(int aIndex) {
	for(int bId = 0; bId < IL_MAXBATTLE; bId++)
	{
		if(Battle[bId].Active)
		{
			for(int tId = 0; tId < IL_MAXTEAM; tId++)
			{
				for(int pId = 0; pId < ILAPI_GetTeamMembersCount(&Battle[bId].Team[tId]); pId++)
				{
					if(Battle[bId].Team[tId].v_Members.at(pId).aIndex == aIndex)
					{
						if(Battle[bId].aHeroIndex == aIndex)
						{
							ILAPI_GiftUserClear(aIndex);
						}
						
						gObj[aIndex].m_Change = -1;
						Battle[bId].Team[tId].v_Members.erase(Battle[bId].Team[tId].v_Members.begin() + pId);
						LogAdd("[%s][%s] [ ILLUSION ] Deleted member from event.", gObj[aIndex].AccountID, gObj[aIndex].Name);
					}
				}
			}
		}
	}
}
void ILAPI_ClearTeam(IL_TEAMSTRUCT *pTeam) {
	pTeam->m_BattleId = 0;
	pTeam->m_Color = 0;
	pTeam->m_KillPoints = 0;
	pTeam->m_Points = 0;
	pTeam->v_Members.clear();
}
void ILAPI_ClearBattle(IL_BATTLESTRUCT *pBattle) {
	pBattle->Active = false;
	pBattle->aHeroIndex = OBJ_EMPTY;
	pBattle->m_BattleId = 0;

	ILAPI_ClearTeam(&pBattle->Team[0]);
	ILAPI_ClearTeam(&pBattle->Team[1]);
}
void ILAPI_ClearEvent() {
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		ILAPI_ClearBattle(&Battle[i]);
	}

	IL_EVENT_STATE = IL_STATE_IDLE;
	IL_BATTLE_TIMER = IL_TIMERVALUE; 
}
void ILAPI_SetupBattles() {
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		Battle[i].m_BattleId = i + 1;

		Battle[i].Team[0].m_BattleId = i + 1;
		Battle[i].Team[1].m_BattleId = i + 1;
		Battle[i].Team[0].m_Color = IL_COLOR_RED;
		Battle[i].Team[1].m_Color = IL_COLOR_BLUE;
	}
}
void ILAPI_SetBattlesStatus() {
	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		if(ILAPI_GetBattleMembersCount(&Battle[i]) < 4 && i != 4)
		{
			ILAPI_TeleportBattle(&Battle[i], 0, 130, 130);
			ILAPI_SendMessageBattle(&Battle[i], "Sorry, not enough players to start battle.");
			ILAPI_ClearBattle(&Battle[i]);
			LogAdd("[ ILLUSION ] Not enough players to start battles -> cleared.");
		}

		else
		{
			Battle[i].Active = true;
			Battle[4].Active = true;
		}
	}
}
int	ILAPI_GetActiveBattlesCount() {
	int Count = 0;

	for(unsigned i = 0; i < IL_MAXBATTLE; i++)
	{
		if(Battle[i].Active)
			Count++;
	}
	return Count;
}
void ILAPI_TeleportTeam(IL_TEAMSTRUCT *pTeam, int MapNumber, int X, int Y) {
	for(unsigned i = 0; i < pTeam->v_Members.size(); i++)
	{
		gObjTeleport(pTeam->v_Members.at(i).aIndex, MapNumber, X, Y);
	}
}
void ILAPI_TeleportBattle(IL_BATTLESTRUCT *pBattle, int MapNumber, int X, int Y) {
	ILAPI_TeleportTeam(&pBattle->Team[0], MapNumber, X, Y);
	ILAPI_TeleportTeam(&pBattle->Team[1], MapNumber, X, Y);
}
void ILAPI_SendMessageTeam(IL_TEAMSTRUCT *pTeam, const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	char tmp[2048];
	vsprintf_s(tmp, format, argv);
	va_end(argv);

	for(unsigned i = 0; i < pTeam->v_Members.size(); i++)
	{
		GCServerMsgStringSend(tmp, pTeam->v_Members.at(i).aIndex, 0);
	}
}
void ILAPI_SendMessageBattle(IL_BATTLESTRUCT *pBattle, const char *format, ...) {
	va_list argv;
	va_start(argv, format);

	char tmp[2048];
	vsprintf_s(tmp, format, argv);
	va_end(argv);

	ILAPI_SendMessageTeam(&pBattle->Team[0], tmp);
	ILAPI_SendMessageTeam(&pBattle->Team[1], tmp);
}
void ILAPI_SendDataTeam(IL_TEAMSTRUCT *pTeam, unsigned char *pMsg, int Length) {
	for(unsigned i = 0; i < pTeam->v_Members.size(); i++)
	{
		DataSend(pTeam->v_Members.at(i).aIndex, pMsg, Length);
	}
}
void ILAPI_SendDataBattle(IL_BATTLESTRUCT *pBattle, unsigned char *pMsg, int Length) {
	ILAPI_SendDataTeam(&pBattle->Team[0], pMsg, Length);
	ILAPI_SendDataTeam(&pBattle->Team[1], pMsg, Length);
}

void ILAPI_GiftUserTake(int aIndex) {
	if(ILAPI_Handle(aIndex, IL_HANDBATTLE) == NULL)
	{
		GCServerMsgStringSend("[Illusion]: Sorry, you are not event member.", aIndex, 1);
		LogAdd("[%s][%s] [ ILLUSION GIFT ] Want take gift from NPC, but isn't event member.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}

	IL_BATTLESTRUCT *pBattle = (IL_BATTLESTRUCT*)ILAPI_Handle(aIndex, IL_HANDBATTLE);

	if(pBattle->aHeroIndex != OBJ_EMPTY)
	{
		GCServerMsgStringSend("[Illusion]: No gift in statue.", aIndex, 1);
		LogAdd("[%s][%s] [ ILLUSION GIFT ] Someone took gift after this user.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}

	else
	{
		pBattle->aHeroIndex = aIndex;
		ItemSerialCreateSend(aIndex, 0xeb, 0, 0, 0x1C40, 0, 255, 0, 0, 0, -1, 0, 0);
		ILAPI_SendMessageBattle(pBattle, "[Illusion] %s have the gift!", gObj[aIndex].Name);
		LogAdd("[%s][%s] [ ILLUSION GIFT ] has been taken gift from NPC -> Battle:(%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, pBattle->m_BattleId);
	}
}
void ILAPI_GiftUserGive(int aIndex) {
	if(ILAPI_Handle(aIndex, IL_HANDTEAM) == NULL)
	{
		GCServerMsgStringSend("[Illusion]: Sorry, you are not event member.", aIndex, 1);
		LogAdd("[%s][%s] [ ILLUSION GIFT ] Want give gift to NPC, but isn't event member.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return;
	}

	if(ILAPI_GiftUserClear(aIndex))
	{
		IL_TEAMSTRUCT *pTeam = (IL_TEAMSTRUCT*)ILAPI_Handle(aIndex, IL_HANDTEAM);
		pTeam->m_Points++;
		LogAdd("[%s][%s] [ ILLUSION GIFT ] gave point team (%d/%d).", gObj[aIndex].AccountID, gObj[aIndex].Name, pTeam->m_Color, pTeam->m_BattleId);
	}
}
bool ILAPI_GiftUserClear(int aIndex) {
	if(ILAPI_Handle(aIndex, IL_HANDBATTLE) == NULL)
	{
		LogAdd("[%s][%s] [ ILLUSION GIFT ] Can't clear gift - not event member.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return false;
	}

	IL_BATTLESTRUCT *pBattle = (IL_BATTLESTRUCT*)ILAPI_Handle(aIndex, IL_HANDBATTLE);

	if(pBattle->aHeroIndex != aIndex)
	{
		LogAdd("[%s][%s] [ ILLUSION GIFT ] he isn't current hero!", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return false;
	}

	else
	{
		pBattle->aHeroIndex = OBJ_EMPTY;
		gObjDeleteItemsCount(aIndex, 0x1c40, 0, 1);
		ILAPI_SendMessageBattle(pBattle, "[Illusion] Gift returned to statue!");
		LogAdd("[%s][%s] [ ILLUSION GIFT ] Cleared gift.", gObj[aIndex].AccountID, gObj[aIndex].Name);
		return true;
	}
}
void ILAPI_KillPointsManage(IL_TEAMSTRUCT *pTeam, int Points, IL_KILL_POINTS Reason) {
	switch(Reason)
	{
	case IL_KP_ADD:
		if((pTeam->m_KillPoints + Points) > IL_MAX_KILLPOINT)
		{
			pTeam->m_KillPoints = IL_MAX_KILLPOINT;
		}

		else
		{
			pTeam->m_KillPoints += Points;
		}
		break;

	case IL_KP_SUB:
		if((pTeam->m_KillPoints - Points) < 0)
		{
			pTeam->m_KillPoints = 0;
		}

		else
		{
			pTeam->m_KillPoints -= Points;
		}
		break;
	}

	unsigned char msg[5] = {0xc1, 0x05, 0xbf, 0x06, pTeam->m_KillPoints};
	ILAPI_SendDataTeam(pTeam, msg, 5);

	LogAdd("[ ILLUSION ] KillPoints managed: Action(%d), Team(%d/%d), current(%d).", Reason, pTeam->m_Color, pTeam->m_BattleId, pTeam->m_KillPoints);
}
void ILAPI_MaskTeam(IL_TEAMSTRUCT *pTeam, int m_Change) {
	for(unsigned i = 0; i < pTeam->v_Members.size(); i++)
	{
		gObj[pTeam->v_Members.at(i).aIndex].m_Change = m_Change;
	}
}

int gObjDeleteItemsCount(int aIndex, short Type, short Level, int Count) 
{
	int count = 0;

	for(unsigned i = 0; i < 76; i++)
	{
		if(gObj[aIndex].pInventory[i].m_Type == Type && gObj[aIndex].pInventory[i].m_Level == Level)
		{
			gObjInventoryDeleteItem(aIndex, i);
			GCInventoryItemDeleteSend(aIndex, i, 1);
			count++;

			if(Count == count)
				break;
		}
	}
	return count;
}