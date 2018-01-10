#ifndef NPCTALK_H
#define NPCTALK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000 



struct GC_ANS_NPC_TALK_V1
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
};

struct GC_ANS_NPC_TALK_V2
{
	PHEADB	PHeader;	// C3:30
	BYTE NpcNumber;
	BYTE Param1;
	BYTE Param2;
	BYTE Param3;
	BYTE Param4;
	BYTE Param5;
	BYTE Param6;
};

struct SDHP_NPC_LEO_THE_HELPER_RECV
{
	PBMSG_HEAD header; // C1:0E:00
	WORD index;
	char account[11];
	char name[11];
	BYTE status;
};
struct SDHP_NPC_LEO_THE_HELPER_SEND
{
	PBMSG_HEAD header; // C1:0E:00
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_NPC_LEO_THE_HELPER_SAVE_SEND
{
	PBMSG_HEAD header; // C1:0E:30
	WORD index;
	char account[11];
	char name[11];
	BYTE status;
};

struct SDHP_NPC_LUKE_THE_HELPER_RECV
{
	PBMSG_HEAD header; // C1:0E:01
	WORD index;
	char account[11];
	char name[11];
	BYTE status;
};
struct SDHP_NPC_LUKE_THE_HELPER_SEND
{
	PBMSG_HEAD header; // C1:0E:01
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_NPC_LUKE_THE_HELPER_SAVE_SEND
{
	PBMSG_HEAD header; // C1:0E:31
	WORD index;
	char account[11];
	char name[11];
	BYTE status;
};

BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);

int NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj);
//NPCS New
BOOL NpcPamelaSupplier(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcAngelaSupplier(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcFireworkGirl(LPOBJ lpNpc, LPOBJ lpObj);
//Illusion Temple
BOOL NpcIllusionStatue(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionYellowPedestal(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionBluePedestal(LPOBJ lpNpc, LPOBJ lpObj);
BOOL NpcIllusionMirage(LPOBJ lpNpc, LPOBJ lpObj);

BOOL NpcCouponEvent(LPOBJ lpNpc, LPOBJ lpObj); //OK

BOOL NpcWhiteAngelEvent(LPOBJ lpNpc, LPOBJ lpObj); //OK
#endif