#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning ( disable : 4786 4244 4482 4101 4060 4554 4018 4996 4995 4700 4646 4532 4748 )
#define _WIN32_WINNT 0x500
#define WIN32_LEAN_AND_MEAN

#define INTERNATIONAL_INFO	0

#if(INTERNATIONAL_INFO == 1) //Japan
	#define MOVE_PROTOCOL		0x1D
	#define SETPOS_PROTOCOL		0xD6
	#define ATTACK_PROTOCOL		0xDC
	#define BEATTACK_PROTOCOL	0xD7
#endif
#if(INTERNATIONAL_INFO == 0) // Korea
	#define MOVE_PROTOCOL		0xD3
	#define SETPOS_PROTOCOL		0xDF
	#define ATTACK_PROTOCOL		0xD7
	#define BEATTACK_PROTOCOL	0x10
#endif
#if(INTERNATIONAL_INFO == 2) // Global
	#define MOVE_PROTOCOL		0xD4
	#define SETPOS_PROTOCOL		0x15
	#define ATTACK_PROTOCOL		0x11
	#define BEATTACK_PROTOCOL	0xDB
#endif


// Windows Header Files:
#include <afx.h>
#include <windows.h>
#include <winbase.h>
#include <winsock2.h>
#include "COMMCTRL.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <process.h>

// C++ STL Library
#include <map>
#include <string>
#include <ios>
#include <algorithm>
#include <vector>
#include <set>

// Local Header Files
#include "MuMsg.h"

// TODO: reference additional headers your program requires here
#pragma comment( lib , "wsock32.lib" )
#pragma comment( lib , "ws2_32.lib" )
#pragma comment( lib , "COMCTL32.lib" )

// GameServer Build
//--------------------------
// 0 : As Normal Game Server
// 1 : As Castle Siege Game Server

#define GS_CASTLE	0 
#define TEST_SERVER	0
#define MAX_PASS_LEN	10 

#define GAMESERVER_WIDTH		750	// Width of window

#include "AcceptIp.h"
#include "AttackEvent.h"
#include "BattleGround.h"
#include "BattleSoccer.h"
#include "BattleSoccerManager.h"
#include "BloodCastle.h"
#include "CallStackTrace.h"
#include "CannonTower.h"
#include "CashItemPeriodSystem.h"
#include "CashLotterySystem.h"
#include "CashShop.h"
#include "CastleCrown.h"
#include "CastleCrownSwitch.h"
#include "CastleDeepEvent.h"
#include "CastleSiege.h"
#include "CastleSiegeSync.h"

//#include "CCastleEventItemList.h"

#include "ChaosBox.h"
#include "ChaosCastle.h"
#include "ChaosCastleSetItemDrop.h"
#include "ChinaHackUserKick.h"
#include "classdef.h"
#include "CLoginCount.h"
#include "ClosePlayer.h"
#include "ComboAttack.h"
#include "ConMember.h"
#include "Crywolf.h"
#include "CrywolfAltar.h"
#include "CrywolfDarkElf.h"
#include "CrywolfMonster.h"
#include "CrywolfObjInfo.h"
#include "CrywolfStateTimeInfo.h"
#include "CrywolfStatue.h"
#include "CrywolfSync.h"
#include "CrywolfTanker.h"
#include "CrywolfUtil.h"

//#include "CSAuth2.h"

#include "CWhatsUpDummyServer.h"
#include "DarkSpirit.h"
#include "DbSave.h"
#include "DBSockMng.h"
#include "DevilSquare.h"
#include "DevilSquareGround.h"
#include "dirpath.h"
#include "DragonEvent.h"
#include "DSProtocol.h"
#include "EDSProtocol.h"
#include "EledoradoEvent.h"
#include "Event.h"
#include "EventManagement.h"
#include "GameEvent.h"
#include "GameMain.h"
#include "GameServer.h"
#include "GameServerAuth.h"
#include "Gate.h"
//#include "GGSvr.h"
#include "giocp.h"
#include "GMMng.h"
#include "gObjMonster.h"
#include "Guardian.h"
#include "GuardianStatue.h"
#include "GuildClass.h"
#include "IpCache.h"
#include "ItemAddOption.h"
#include "ItemBag.h"
#include "ItemBagEx.h"
#include "ItemSystemFor380.h"
#include "JewelMixSystem.h"
#include "JewelOfHarmonySystem.h"
#include "KalimaGate.h"
#include "Kanturu.h"
#include "KanturuBattleOfMaya.h"
#include "KanturuBattleOfNightmare.h"
#include "KanturuBattleStanby.h"
#include "KanturuBattleUser.h"
#include "KanturuBattleUserMng.h"
#include "KanturuEntranceNPC.h"
#include "KanturuMaya.h"
#include "KanturuMonsterMng.h"
#include "KanturuNightmare.h"
#include "KanturuObjInfo.h"
#include "KanturuStateInfo.h"
#include "KanturuTowerOfRefinement.h"
#include "KanturuUtil.h"
#include "LargeRand.h"
#include "LifeStone.h"
#include "logproc.h"
#include "LogToFile.h"
#include "MagicDamage.h"
#include "MagicInf.h"
#include "MapClass.h"
#include "MapItem.h"
#include "MapServerManager.h"
#include "Mercenary.h"
#include "MonsterAttr.h"
#include "MonsterHerd.h"
#include "MonsterItemMng.h"
#include "MonsterSetBase.h"
#include "MoveCheck.h"
#include "MoveCommand.h"
#include "MultiAttackHackCheck.h"
#include "MultiCheckSum.h"
#include "MyWinsockBase.h"
#include "NpcTalk.h"
#include "NSerialCheck.h"
#include "ObjAttack.h"
#include "ObjBaseAttack.h"
#include "ObjCalCharacter.h"
#include "ObjUseSkill.h"
#include "PacketCheckSum.h"
#include "PartyClass.h"
#include "protocol.h"
#include "QuestInfo.h"
#include "RingAttackEvent.h"
#include "SendHackLog.h"
#include "SetItemMacro.h"
#include "SetItemOption.h"
#include "Shop.h"
#include "SkillAdditionInfo.h"
#include "SkillDelay.h"
#include "SkillHitBox.h"
#include "spe.h"
#include "SProtocol.h"
#include "StatMng.h"
#include "TDurMagicKeyChecker.h"
#include "TMonsterAI.h"
#include "TMonsterAIAgro.h"
#include "TMonsterAIAutomata.h"
#include "TMonsterAIElement.h"
#include "TMonsterAIGroup.h"
#include "TMonsterAIGroupMember.h"
#include "TMonsterAIMovePath.h"
#include "TMonsterAIRule.h"
#include "TMonsterAIRuleInfo.h"
#include "TMonsterAIState.h"
#include "TMonsterAIUnit.h"
#include "TMonsterAIUtil.h"
#include "TMonsterSkillElement.h"
#include "TMonsterSkillElementInfo.h"
#include "TMonsterSkillInfo.h"
#include "TMonsterSkillManager.h"
#include "TMonsterSkillUnit.h"
#include "TNotice.h"
#include "TRandomPoolMgr.h"
#include "TServerAlertManager.h"
#include "TServerInfoDisplayer.h"
#include "TSkillElement.h"
#include "TStatistics.h"
#include "TSync.h"
#include "TUnion.h"
#include "TUnionInfo.h"
#include "user.h"
#include "ViewportGuild.h"
#include "Weapon.h"
#include "WhisperCash.h"
#include "winutil.h"
#include "wsGameServer.h"
#include "wsJoinServerCli.h"
#include "wsShopServerCli.h"

//#include "WTEventItemList.h"

#include "WzMemScript.h"
#include "WzMultiCastSock.h"
#include "WzQueue.h"
#include "WZScriptEncode.h"
#include "WzUdp.h"
#include "zzzitem.h"
#include "zzzmathlib.h"
#include "zzzpath.h"

#include "resource.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
