#ifndef PROTOCOL_H
#define PROTOCOL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "prodef.h"
#include "GuildClass.h"
#include "user.h"
#include "MapClass.h"

enum MUPROTOCOL_DECL
{
	// ----------
	SELECT_SERVER               = 0xF1,
	// SubCode
	JOIN_ID_PASS_REQ            = 0x01,
	CLIENT_CLOSE_MSG            = 0x02,
	CLIENT_MSG                  = 0x03,
	// ----------

	// ----------
	SELECT_CHARACTER            = 0xF3,
	// SubCode
	GET_CHAR_LIST_REQ           = 0x00,
	CHARACTER_CREATE            = 0x01,
	CHARACTER_DELETE            = 0x02,
	CHAR_MAP_JOIN_REQ           = 0x03,
	LEVEL_UP_POINT_ADD          = 0x06,
	MOVE_DATA_LOADING           = 0x12,
	SKILL_KEY                   = 0x30,
	// ----------

	// ----------
	CHAT_PROC                   = 0x00,
	// ----------
	CHAT_RECV                   = 0x01,
	// ----------
	CHAT_WHISPER_RECV           = 0x02,
	// ----------
	CHECK_MAIN_RECV             = 0x03,
	// ----------
	LIVE_CLIENT                 = 0x0E,
	// ----------
	ACTION_RECV                 = 0x18,
	// ----------
	MAGIC_ATTACK                = 0x19,
	// ----------
	MAGIC_CANCEL                = 0x20,
	// ----------
	TELEPORT_RECV               = 0x1C,
	// ----------
	TARGET_TELEPORT_RECV        = 0xB0,
	// ----------
	DURATION_MAGIC_RECV         = 0x1E,
	// ----------
	ITEM_GET_REQUEST            = 0x22,
	// ----------
	ITEM_DROP_REQUEST           = 0x23,
	// ----------
	INVENTORY_ITEM_MOVE         = 0x24,
	// ----------
	USE_ITEM_RECV               = 0x26,
	// ----------
	TALK_REQ_RECV               = 0x30,
	// ----------
	CLOSE_WINDOW                = 0x31,
	// ----------
	BUY_REQ_RECV                = 0x32,
	// ----------
	SELL_REQ_RECV               = 0x33,
	// ----------
	MODIFY_REQ_ITEM             = 0x34,
	// ----------
	TRADE_REQ_SEND              = 0x36,
	// ----------
	TRADE_RESPONSE_RECV         = 0x37,
	// ----------
	TRADE_MONEY_RECV            = 0x3A,
	// ----------
	TRADE_OK_BUTTON_RECV        = 0x3C,
	// ----------
	TRADE_CANCEL_BUTTON_RECV    = 0x3D,
	// ----------
	SHOP_PROTOCOL_ID            = 0x3F,
	// SubCode
	SHOP_REQ_SET_ITEM_PRICE     = 0x01,
	SHOP_REQ_OPEN               = 0x02,
	SHOP_REQ_CLOSE              = 0x03,
	SHOP_REQ_BUY_LIST           = 0x05,
	SHOP_REQ_BUY_ITEM           = 0x06,
	// ----------
	PARTY_REQ_RECV              = 0x40,
	// ----------
	PARTY_REQ_RESULT_RECV       = 0x41,
	// ----------
	PARTY_LIST                  = 0x42,
	// ----------
	PARTY_DELETE_USER           = 0x43,
	// ----------
	GUILD_REQ_RECV              = 0x50,
	// ----------
	GUILD_REQ_RESULT_RECV       = 0x51,
	// ----------
	GUILD_LIST_ALL              = 0x52,
	// ----------
	GUILD_DELETE_USER           = 0x53,
	// ----------
	GUILD_MASTER_ANSWER_RECV    = 0x54,
	// ----------
	GUILD_MASTER_INFO_SAFE      = 0x55,
	// ----------
	GUILD_MASTER_CREATE_CANCEL  = 0x57,
	// ----------
	GUILD_WAR_REQ_SEND_RECV     = 0x61,
	// ----------
	GUILD_VIEWPORT_INFO         = 0x66,
	// ----------
	MAP_SRV_AUTH_PROTOCOL_ID    = 0xB1,
	// SubCode
	REQ_MAP_SRV_AUTH            = 0x01,
	// ----------
	CASTLE_SIEGE_PROTOCOL_ID    = 0xB2,
	// SubCode
	REQ_CASTLE_SIEGE_STATE      = 0x00,
	REQ_REG_CASTLE_SIEGE        = 0x01,
	REQ_GIVE_UP_CASTLE_SIEGE    = 0x02,
	REQ_GUILD_REG_INFO          = 0x03,
	REQ_REG_GUILD_MARK          = 0x04,
	REQ_NPC_BUY                 = 0x05,
	REQ_NPC_REPAIR              = 0x06,
	REQ_NPC_UPGRADE             = 0x07,
	REQ_TAX_MONEY_INFO          = 0x08,
	REQ_TAX_RATE_CHANGE         = 0x09,
	REQ_MONEY_DRAW_OUT          = 0x10,
	REQ_CS_GATE_OPERATE         = 0x12,
	REQ_CS_MINIMAP_DATA         = 0x1B,
	REQ_CS_STOP_MINIMAP_DATA    = 0x1C,
	REQ_CS_SEND_COMMAND         = 0x1D,
	REQ_CS_SET_ENTER_HUNTZONE   = 0x1F,
	// ----------
	REQ_NPC_DB_LIST             = 0xB3,
	// ----------
	REQ_CS_REG_GUILD_LIST       = 0xB4,
	// ----------
	REQ_CS_ATTACK_GUILD_LIST    = 0xB5,
	// ----------
	WEAPON_PROTOCOL_ID          = 0xB7,
	// SubCode
	REQ_WEAPON_USE              = 0x01,
	REQ_WEAPON_DAMAGE_VALUE     = 0x04,
	// ----------
	CASTLESIEGE_PROTOCOL_ID     = 0xB9,
	// SubCode
	REQ_GUILD_MARK_OF_CS_OWNER  = 0x02,
	REQ_CS_HUNTZONE_ENTRANCE    = 0x05,
	// ----------
	JEWEL_PROTOCOL_ID          = 0xBC,
	// SubCode
	REQ_JEWEL_MIX               = 0x00,
	// ----------
	REQ_JEWEL_UNMIX             = 0x01,
	// ----------
	CRYWOLF_PROTOCOL_ID         = 0xBD,
	//SubCode 
	REQ_CRYWOLF_INFO            = 0x00,
	REQ_ALTAR_CONTRACT          = 0x03,
	REQ_PLUS_CHAOS_RATE         = 0x09,
	// ----------
	GUILD_ASIGN_STATUS          = 0xBE,
	// ----------
	ILLUSION_TEMPLE_PROTOCOL_ID = 0xBF,
	// ----------
	GUILD_ASIGN_TYPE            = 0xE2,
	// ----------
	REL_SHIP_REQ_JOIN_BREAK_OFF = 0xE5,
	// ----------
	REL_SHIP_ANS_JOIN_BREAK_OFF = 0xE6,
	// ----------
	UNION_LIST                  = 0xE9,
 // ----------
	KICK_OUT_UNION_MEMBER_PROTOCOL_ID = 0xEB,
	// SubCode
	REL_SHIP_REQ_KICK_OUT_UNION_MEMB  = 0x01,
	// ----------
	PING_SEND_RECV              = 0x71,
	// ----------
	PACKET_CHECKSUM_RECV        = 0x72,
	// ----------
	GAMEGUARD_CHECKSUM_RECV     = 0x73,
 // ----------
	WAREHOUSE_MONEY_IN_OUT      = 0x81,
	// ----------
	WAREHOUSE_USE_END           = 0x82,
	// ----------
	WAREHOUSE_RECIVE_PASSWORD   = 0x83,
	// ----------
	CHAOSBOX_ITEM_MIX_BTN_CLICK = 0x86,
	// ----------
	CHAOSBOX_USE_END            = 0x87,
 // ----------
	REQ_MOVE_DEVILSQUARE        = 0x90,
	// ----------
	REQ_DEVIL_SQUARE_REMAIN_TIME = 0x91,
	// ----------
	REQ_EVENT_CHIP_RECV          = 0x95,
	// ----------
	GET_MUTO_NUM_RECV            = 0x96,
	// ----------
	USE_END_EVENT_CHIP_RECV      = 0x97,
 // ----------
	USE_RENA_CHANGE_ZEN_RECV     = 0x98,
	// ----------
	REQ_MOVE_OTHER_SERVER        = 0x99,
	// ----------
	REQ_QUEST_INFO               = 0xA0,
	// ----------
	SET_QUEST_STATE              = 0xA2,
	// ----------
	REQ_PET_ITEM_COMMAND         = 0xA7,
 // ----------
	REQ_PET_ITEM_INFO            = 0xA9,
	// ----------
	DUEL_START_REQ_RECV          = 0xAA,
	// ----------
	DUEL_END_REQ_RECV            = 0xAB,
	// ----------
	DUEL_OK_REQ_RECV             = 0xAC,
	// ----------
	REQ_ENTER_BLOODCASTLE        = 0x9A,
 // ----------
	LACKING_PACKET_PROTOCOL_ID   = 0x9B,
	// ----------
	REQ_EVENT_ENTER_COUNT        = 0x9F,
	// ----------
	REQ_LOTTO_REGISTER           = 0x9D,
	// ----------
	CHAOSCASTLE_PROTOCOL_ID      = 0xAF,
	// SubCode
	REQ_ENTER_CHAOSCASTLE              = 0x01,
	REQ_REPOSITION_USER_IN_CHAOSCASTLE = 0x02,
 // ----------
	FRIEND_LIST_REQ              = 0xC0,
	// ----------
	FRIEND_ADD_REQ               = 0xC1,
	// ----------
	WAIT_FRIEND_ADD_REQ          = 0xC2,
	// ----------
	FRIEND_DELETE_REQ            = 0xC3,
	// ----------
	FRIEND_STATE_CLIENT_RECV     = 0xC4,
 // ----------
	FRIEND_MEMO_SEND             = 0xC5,
	// ----------
	FRIEND_MEMO_READ_REQ         = 0xC7,
	// ----------
	FRIEND_MEMO_DELETE_REQ       = 0xC8,
	// ----------
	FRIEND_MEMO_LIST_REQ         = 0xC9,
	// ----------
	FRIEND_CHAT_ROOM_CREATE_REQ  = 0xCA,
 // ----------
	FRIEND_ROOM_INVITATION_REQ   = 0xCB,
	// ----------
	EVENT_NPC					 = 0xD0,
	//Subcode
	LUKEHELPLERNPC				 = 0x03,
	PCBANGSHOPBUY				 = 0x05,
	PCBANGSHOPOPEN				 = 0x06,
	THIRDQUESTWEREWOLF			 = 0x07,
	THIRDQUESTGATEKEEPER		 = 0x08,
	LEOHELPLERNPC				 = 0x09,
	// ----------
	KANTURU_PROTOCOL_ID          = 0xD1,
	// SubCode
	REQ_KANTURU_STATE_INFO       = 0x00,
	REQ_KANTURU_ENTER_BOSS_MAP   = 0x01,
	// ----------
	CASH_SHOP_PROTOCOL_ID        = 0xF5,
	// SubCode
	CASH_SHOP_OPEN               = 0x01,
	CASH_POINT                   = 0x03,
	CASH_ITEM_LIST_SEND          = 0x05,
	CASH_ITEM_BUY                = 0x07,
	// ----------
};

extern int iCount;

struct PMSG_KILLPLAYER_EXT
{
	PBMSG_HEAD h;	// C3:9C
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	WORD ExpH;	// 6
	WORD ExpL;	// 8
	BYTE DamageH;	// A
	BYTE DamageL;	// B
};

struct PMSG_ANS_END_DUEL
{
	PBMSG_HEAD h;	// C1:AB
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Send Warehouse Info Packet
 *	Direction : GameServer -> Client
 *  Code      : 0xC3
 *	HeadCode  : 0x30
 */
struct PMSG_TALKRESULT
{
	PBMSG_HEAD h;
	unsigned char result;	// 3
	BYTE level1;	// 4
	BYTE level2;	// 5
	BYTE level3;	// 6
	BYTE level4;	// 7
	BYTE level5;	// 8
	BYTE level6;	// 9
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Mu Result Packet
 *	Direction : GameServer -> Client
 *  Code     : 0xC1
 *	HeadCode : 0xF3
 *	SubCode  : 0x02
 */
struct PMSG_RESULT
{
	PBMSG_HEAD h;
	unsigned char subcode;	// 3
	unsigned char result;	// 4
};

/* * * * * * * * * * * * * * * * * * * * * 
 *	Packet to Send Blod Castle State
 *	Direction : GameServer -> Client
 *	Code      : 0xC1
 *	HeadCode  : 0x9B
 */
struct PMSG_STATEBLOODCASTLE
{
	PBMSG_HEAD h;	// C1:9B
	BYTE btPlayState;		// 3
	WORD wRemainSec;	// 4
	WORD wMaxKillMonster;	// 6
	WORD wCurKillMonster;	// 8
	WORD wUserHaveWeapon;	// A
	BYTE btWeaponNum;	// C
};

struct PMSG_KILLCOUNT
{
	PBMSG_HEAD2 h;
	BYTE btKillCount;
};

struct PMSG_ATTACKRESULT
{
	PBMSG_HEAD h;	// C1:DC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE DamageH;	// 5
	BYTE DamageL;	// 6
	BYTE DamageType;	// 7
	BYTE btShieldDamageH;	// 8
	BYTE btShieldDamageL;	// 9
};

struct PMSG_RECV_POSISTION_SET
{
	PBMSG_HEAD h;	// C1:D6
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};

struct PMSG_USEREQUIPMENTCHANGED
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE ItemInfo[MAX_ITEM_INFO];	// 5
};

struct PMSG_SERVERCMD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE CmdType;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};

struct PMSG_ITEMTHROW_RESULT
{
	PBMSG_HEAD h;	// C1:23
	unsigned char Result;	// 3
	BYTE Ipos;	// 4
};

struct PMSG_GUILDCREATED_RESULT
{
	PBMSG_HEAD h;	// C1:56
	BYTE Result;	// 3
	BYTE btGuildType;	// 4
};

struct PMSG_SIMPLE_GUILDVIEWPORT_COUNT
{
	PWMSG_HEAD h;	// C2:65
	BYTE Count;	// 4
};

struct PMSG_SIMPLE_GUILDVIEWPORT
{
	int GuildNumber;	// 0
	BYTE btGuildStatus;	// 4
	BYTE btGuildType;	// 5
	BYTE btGuildRelationShip;	// 6
	BYTE NumberH;	// 7
	BYTE NumberL;	// 8
};

struct PMSG_RECVMOVE
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
	BYTE Path;	// 7
};

struct PMSG_MAGICATTACK_RESULT
{
	PBMSG_HEAD h;	// C3:19
	BYTE MagicNumber;	// 3
	BYTE SourceNumberH;	// 4
	BYTE SourceNumberL;	// 5
	BYTE TargetNumberH;	// 6
	BYTE TargetNumberL;	// 7
};

struct PMSG_BEATTACK_COUNT
{
	PBMSG_HEAD h;	// C1:D7
	BYTE MagicNumber;	// 3
	BYTE X;	// 4
	BYTE Y;	// 5
	BYTE Serial;	// 6
	BYTE Count;	// 7
};

struct PMSG_BEATTACK
{
	BYTE NumberH;	// 0
	BYTE NumberL;	// 1
	BYTE MagicKey;	// 2
};

struct PMSG_SET_DEVILSQUARE
{
	PBMSG_HEAD h;	// C1:92
	BYTE Type;	// 3
};

struct PMSG_GUILD_ASSIGN_STATUS_RESULT
{
	PBMSG_HEAD h;	// C1:E1
	BYTE btType;	// 3
	BYTE btResult;	// 4
	char szTagetName[10];	// 5
};

struct PMSG_GUILD_ASSIGN_TYPE_RESULT
{
	PBMSG_HEAD h;	// C1:E2
	BYTE btGuildType;	// 3
	BYTE btResult;	// 4
};

//////////////////////////////////////////////////////////////////////////////
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//////////////////////////////////////////////////////////////////////////////

struct PMSG_CLIENTTIME
{
	PBMSG_HEAD h;
	DWORD Time;	// 4
	WORD AttackSpeed;	// 8
	WORD MagicSpeed;	// A
};

struct PMSG_CHECK_MAINEXE_RESULT
{
	PBMSG_HEAD h;
	DWORD m_dwKey;	// 4
};

struct PMSG_CHATDATA
{
	PBMSG_HEAD h;	//	
	char chatid[10];	//	3
	char chatmsg[60];	//	D
};

struct PMSG_CHATDATA_NUMBER
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char chatmsg[60];	// 5
};

struct PMSG_CHATDATA_WHISPER
{
	PBMSG_HEAD h;	// C1:02
	char id[10];	// 3
	char chatmsg[60];	// D  
};

struct PMSG_IDPASS
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Id[10];	// 4
	char Pass[MAX_PASS_LEN];	// E
	DWORD TickCount;	// 18
	BYTE CliVersion[5];	// 1C
	BYTE CliSerial[16];	// 21  
};

struct PMSG_CLIENTCLOSE
{
	PBMSG_HEAD h;
	BYTE SubCode;	// 3
	BYTE Flag;	// 4
};

struct PMSG_CLIENTMSG
{
	PBMSG_HEAD h;
	BYTE SubCode;	// 3
	BYTE Flag;	// 4
	BYTE subFlag;	// 5
};

struct PMSG_CHARCREATE
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
	BYTE ClassSkin;	// E
};

struct PMSG_CHARDELETE
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
	char LastJoominNumber[10];	// E
};

struct PMSG_CHARMAPJOIN
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	char Name[10];	// 4
};

struct PMSG_LVPOINTADD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE Type;	// 4
};

struct PMSG_SKILLKEY
{
	PBMSG_HEAD h;	// C1:F3:30
	BYTE subcode;	// 3
	BYTE SKillKey[10];	// 4
	BYTE GameOption;	// E
	BYTE QkeyDefine;	// F
	BYTE WkeyDefine;	// 10
	BYTE EkeyDefine;	// 11
	BYTE ChatWindow;	// 12
};

struct PMSG_ITEMGETREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_ITEMTHROW
{
	PBMSG_HEAD h;
	BYTE px;	// 3
	BYTE py;	// 4
	BYTE Ipos;	// 5
};

struct PMSG_INVENTORYITEMMOVE
{
	PBMSG_HEAD h;
	BYTE sFlag;	// 3
	BYTE source_item_num;	// 4
	BYTE sItemInfo[MAX_ITEM_INFO];	// 5
	BYTE tFlag;	// C
	BYTE target_item_num;	// D
};

struct PMSG_TALKREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_BUYREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;	// 3
};

struct PMSG_SELLREQUEST
{
	PBMSG_HEAD h;
	BYTE Pos;	// 3
};

struct PMSG_ITEMDURREPAIR
{
	PBMSG_HEAD h;
	BYTE Position;	// [0xFF:Repair ALL] 3
	BYTE Requestpos;	// 4
};

struct PMSG_TRADE_REQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_TRADE_RESPONSE
{
	PBMSG_HEAD h;	// C1:37
	BYTE Response;	// 3
	BYTE Id[10];	// 4
	WORD Level;	// E
	int GuildNumber;	// 10
};

struct PMSG_TRADE_GOLD
{
	PBMSG_HEAD h;
	DWORD Money;	// 4
};

struct PMSG_TRADE_OKBUTTON
{
	PBMSG_HEAD h;	// C1:3C
	BYTE Flag;	// 3
};

struct PMSG_REQ_PSHOP_SETITEMPRICE
{
	PBMSG_HEAD2 h;
	BYTE btItemPos;	// 4
	BYTE sItemPrice1;	// 5
	BYTE sItemPrice2;	// 6
	BYTE sItemPrice3;	// 7
	BYTE sItemPrice4;	// 8
};

struct PMSG_REQ_PSHOP_OPEN
{
	PBMSG_HEAD2 h;
	char szPShopText[36];	// 4
};

struct PMSG_REQ_BUYLIST_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
};

struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};

struct PMSG_REQ_PSHOPDEAL_CLOSE
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
};

struct PMSG_PARTYREQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_PARTYREQUESTRESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_PARTYDELUSER
{
	PBMSG_HEAD h;
	BYTE Number;	// 3
};

struct PMSG_GUILDJOINQ
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};

struct PMSG_GUILDQRESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_GUILDDELUSER
{
	PBMSG_HEAD h;
	char Name[10];	// 3
	char JoominNumber[10];	// D
};

struct PMSG_GUILDMASTERANSWER
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
};

struct PMSG_GUILDINFOSAVE
{
	PBMSG_HEAD h;
	BYTE btGuildType;	// 3
	char GuildName[8];	// 4
	BYTE Mark[32];	// C
};

struct PMSG_GUILDWARSEND_RESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
};

struct PMSG_WAREHOUSEMONEYINOUT
{
	PBMSG_HEAD h;
	BYTE Type;	// [0x01:Deposit] [0x02:Withdraw] 3
	int Money;	// 4
};

struct PMSG_WAREHOUSEPASSSEND
{
	PBMSG_HEAD h;
	BYTE Type;	// [0x00:Open Warehouse] [0x01:Set Pass] [0x02:Delete Pass] 3
	short Pass;	// 4
	char LastJoominNumber[10];	// 6
};

struct PMSG_CHAOSMIX
{
	PBMSG_HEAD h;
	BYTE Type;	// 3
};

struct PMSG_MOVE
{
	PBMSG_HEAD h;	// C1:1D
	BYTE X;	// 3
	BYTE Y;	// 4
	BYTE Path[8];	// 5
};

struct PMSG_POSISTION_SET
{
	PBMSG_HEAD h;
	BYTE X;	// 3
	BYTE Y;	// 4
};

struct PMSG_ATTACK
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE AttackAction;	// 5
	BYTE DirDis;	// 6
};

struct PMSG_ACTION
{
	PBMSG_HEAD h;
	BYTE Dir;	// 3
	BYTE ActionNumber;	// 4
	BYTE iTargetIndexH;	// 5
	BYTE iTargetIndexL;	// 6
};

struct PMSG_MAGICATTACK
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE Dis;	// 6
};

struct PMSG_MAGICCANCEL 
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};

struct PMSG_TELEPORT
{
	PBMSG_HEAD h;
	BYTE MoveNumber;	// 3
	BYTE MapX;	// 4
	BYTE MapY;	// 5
};

struct PMSG_TARGET_TELEPORT
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE MapX;	// 5
	BYTE MapY;	// 6
};

struct PMSG_DURATION_MAGIC_RECV
{
	PBMSG_HEAD h;
	BYTE MagicNumber;	// 3
	BYTE X;	// 4
	BYTE Y;	// 5
	BYTE Dir;	// 6
	BYTE Dis;	// 7
	BYTE TargetPos;	// 8
	BYTE NumberH;	// 9
	BYTE NumberL;	// A
	BYTE MagicKey;	// B
};

struct PMSG_USEITEM
{
	PBMSG_HEAD h;
	BYTE inventoryPos;	// 3
	BYTE invenrotyTarget;	// 4
	BYTE btItemUseType;	// 5
};

struct PMSG_REQ_MOVEDEVILSQUARE
{
	PBMSG_HEAD h;
	BYTE SquareNumber;	// 3
	BYTE InvitationItemPos;	// 4
};

struct PMSG_REQ_DEVILSQUARE_REMAINTIME
{
	PBMSG_HEAD h;
	BYTE hEventType;	// 3
	BYTE btItemLevel;	// 4
};

struct PMSG_PING_RESULT
{
	PBMSG_HEAD h;
};

struct PMSG_REGEVENTCHIP
{
	PBMSG_HEAD h;
	BYTE Type;	// 3
	BYTE ChipPos;	// 4
};

struct PMSG_GETMUTONUMBER
{
	PBMSG_HEAD h;
};

struct PMSG_EXCHANGE_EVENTCHIP
{
	PBMSG_HEAD h;
	BYTE btType;	// [0x00:Change Renas] [0x01:Change Stones]	3
};

struct PMSG_SETQUEST 
{
	PBMSG_HEAD h;	// C1:A1
	BYTE QuestIndex;	// 3
	BYTE State;	// 4
};

struct PMSG_REQ_MOVEBLOODCASTLE
{
	PBMSG_HEAD h;
	BYTE iBridgeNumber;	// 3
	BYTE iItemPos;	// 4
};

struct PMSG_REQ_MOVECHAOSCASTLE
{
	PBMSG_HEAD2 h;
	BYTE iChaosCastleNumber;	// 4
	BYTE iItemPos;	// 5
};

struct PMSG_REQ_REPOSUSER_IN_CC
{
	PBMSG_HEAD2 h;
	BYTE btPX;	// 4
	BYTE btPY;	// 5
};

struct PMSG_REQ_CL_ENTERCOUNT
{
	PBMSG_HEAD h;
	BYTE btEventType;	// 3
};

struct PMSG_REQ_2ANV_LOTTO_EVENT
{
	PBMSG_HEAD h;
	char SERIAL1[5];	// 3
	char SERIAL2[5];	// 8
	char SERIAL3[5];	// D
};

struct PMSG_REQ_MOVE_OTHERSERVER
{
	PBMSG_HEAD h;
	char LastJoominNumber[10];	// 3
};

struct PMSG_PACKETCHECKSUM
{
	PBMSG_HEAD h;
	BYTE funcindex;	// 3
	DWORD CheckSum;	// 4
};

/*
struct _GG_AUTH_DATA
{
	unsigned long dwIndex;
	unsigned long dwValue1;
	unsigned long dwValue2;
	unsigned long dwValue3;
};
*/

/* struct PMSG_NPROTECTGGCHECKSUM
{
	PBMSG_HEAD h;	// C3:73
	_GG_AUTH_DATA m_ggadCheckSum;	// 4
}; */

struct PMSG_REQ_START_DUEL
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	char szName[10];	// 5
};

struct PMSG_REQ_END_DUEL
{
	PBMSG_HEAD h;
};

struct PMSG_ANS_DUEL_OK
{
	PBMSG_HEAD h;
	bool bDuelOK;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	char szName[10];	// 6
};

struct PMSG_REQUEST_PET_ITEM_COMMAND
{
	PBMSG_HEAD h;
	BYTE PetType;	// 3
	BYTE Command;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
};

struct PMSG_REQUEST_PET_ITEMINFO
{
	PBMSG_HEAD h;
	BYTE PetType;	// 3
	BYTE InvenType;	// 4
	BYTE nPos;	// 5
};

struct PMSG_REQ_GUILDVIEWPORT
{
	PBMSG_HEAD h;
	int GuildNumber;	// 4
};

struct PMSG_GUILD_ASSIGN_STATUS_REQ
{
	PBMSG_HEAD h;
	BYTE btType;	// 3
	BYTE btGuildStatus;	// 4
	char szTagetName[10];	// 5
};

struct PMSG_GUILD_ASSIGN_TYPE_REQ
{
	PBMSG_HEAD h;
	BYTE btGuildType;	// 3
};

struct PMSG_RELATIONSHIP_JOIN_BREAKOFF_REQ
{
	PBMSG_HEAD h;	// C1:E5
	BYTE btRelationShipType;	// 3
	BYTE btRequestType;	// 4
	BYTE btTargetUserIndexH;	// 5
	BYTE btTargetUserIndexL;	// 6
};

struct PMSG_RELATIONSHIP_JOIN_BREAKOFF_ANS
{
	PBMSG_HEAD h;	// C1:E6
	BYTE btRelationShipType;	// 3
	BYTE btRequestType;	// 4
	BYTE btResult;	// 5
	BYTE btTargetUserIndexH;	// 6
	BYTE btTargetUserIndexL;	// 7
};

struct PMSG_UNIONLIST_REQ {
  PBMSG_HEAD h; 
};

struct PMSG_KICKOUT_UNIONMEMBER_REQ
{
	PBMSG_HEAD2 h;
	char szTargetGuildName[8];	// 4
};

struct PMSG_REQ_MAPSERVERAUTH
{
	PBMSG_HEAD2 h;
	char szAccountID[12];	// 4
	char szCharName[12];	// 10
	int iJoinAuthCode1;	// 1C
	int iJoinAuthCode2;	// 20
	int iJoinAuthCode3;	// 24
	int iJoinAuthCode4;	// 28
	int iTickCount;	// 2C
	BYTE btCliVersion[5];	// 30
	BYTE btCliSerial[16];	// 35
};

struct PMSG_REQ_CASTLESIEGESTATE { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_REGCASTLESIEGE { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h; 
};

struct PMSG_REQ_GIVEUPCASTLESIEGE {
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btGiveUp;
};

struct PMSG_REQ_GUILDREGINFO { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;  
};

struct CSP_ANS_GUILDREGINFO
{
	PBMSG_HEAD2 h;
	int iResult;	// 4
	WORD wMapSvrNum;	// 8
	int iIndex;	// C
	char szGuildName[8];	// 10
	int iRegMarkCount;	// 18
	unsigned char bIsGiveUp;	// 1C
	BYTE btRegRank;	// 1D
};

struct PMSG_REQ_REGGUILDMARK {  
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btItemPos;
};

struct CSP_ANS_GUILDREGMARK {
  // static data ------------------------------------

  // non-static data --------------------------------
  /*<thisrel this+0x0>*/ /*|0x4|*/ struct PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iResult;
  /*<thisrel this+0x8>*/ /*|0x2|*/ unsigned short wMapSvrNum;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iIndex;
  /*<thisrel this+0x10>*/ /*|0x8|*/ char szGuildName[8];
  /*<thisrel this+0x18>*/ /*|0x4|*/ int iItemPos;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int iRegMarkCount;

  // base classes -----------------------------------

  // friends ----------------------------------------

  // static functions -------------------------------

  // non-virtual functions --------------------------

  // virtual functions ------------------------------
};
// <size 0x20>

struct PMSG_REQ_NPCBUY { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex; 
};

struct PMSG_REQ_NPCREPAIR { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex;
};

struct PMSG_REQ_NPCUPGRADE { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcNumber;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcIndex;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcUpType;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int iNpcUpValue;
};

struct PMSG_REQ_TAXMONEYINFO { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h; 
};

struct PMSG_REQ_TAXRATECHANGE { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btTaxType;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btTaxRate1;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btTaxRate2;
  /*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btTaxRate3;
  /*<thisrel this+0x8>*/ /*|0x1|*/ BYTE btTaxRate4; 
};

struct PMSG_REQ_MONEYDRAWOUT {  
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btMoney1;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btMoney2;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btMoney3;
  /*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btMoney4; 
};

struct PMSG_REQ_CSGATEOPERATE { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btOperate;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btIndex1;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btIndex2; 
};

struct PMSG_REQ_MINIMAPDATA { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h; 
};

struct PMSG_REQ_STOPMINIMAPDATA {
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h; 
};

struct PMSG_REQ_CSCOMMAND { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btTeam;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btX;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btY;
  /*<thisrel this+0x7>*/ /*|0x1|*/ BYTE btCommand; 
};

struct PMSG_REQ_CSHUNTZONEENTER { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btHuntZoneEnter; 
};

struct PMSG_REQ_NPCDBLIST { 
  PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ BYTE btMonsterCode; 
};

struct PMSG_ANS_NPCDBLIST 
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ struct PWMSG_HEAD h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char btResult;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iCount;
};

struct PMSG_NPCDBLIST {
  // static data ------------------------------------

  // non-static data --------------------------------
  /*<thisrel this+0x0>*/ /*|0x4|*/ int iNpcNumber;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iNpcIndex;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iNpcDfLevel;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iNpcRgLevel;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int iNpcMaxHp;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int iNpcHp;
  /*<thisrel this+0x18>*/ /*|0x1|*/ unsigned char btNpcX;
  /*<thisrel this+0x19>*/ /*|0x1|*/ unsigned char btNpcY;
  /*<thisrel this+0x1a>*/ /*|0x1|*/ unsigned char btNpcLive;

  // base classes -----------------------------------

  // friends ----------------------------------------

  // static functions -------------------------------

  // non-virtual functions --------------------------

  // virtual functions ------------------------------
};

struct PMSG_REQ_CSREGGUILDLIST { 
  PBMSG_HEAD h; 
};

struct PMSG_REQ_CSATTKGUILDLIST { 
  PBMSG_HEAD h;
};

struct PMSG_REQ_USEWEAPON {
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btTargetIndex; 
};

struct PMSG_REQ_WEAPON_DAMAGE_VALUE {  
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL; 
};

struct PMSG_REQ_GUILDMARK_OF_CASTLEOWNER { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_JEWEL_MIX { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btJewelType;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btJewelMix;  
};

struct PMSG_REQ_JEWEL_UNMIX { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btJewelType;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btJewelLevel;
  /*<thisrel this+0x6>*/ /*|0x1|*/ BYTE btJewelPos; 
};

struct PMSG_REQ_CRYWOLF_INFO { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;  
};

struct PMSG_REQ_CRYWOLF_ALTAR_CONTRACT { 
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btObjIndexH;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btObjIndexL;
 
};

struct PMSG_REQ_CRYWOLF_BENEFIT_PLUS_CHAOSRATE {  
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_KANTURU_STATE_INFO {
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};

struct PMSG_REQ_ENTER_KANTURU_BOSS_MAP {
  /*<thisrel this+0x0>*/ /*|0x4|*/PBMSG_HEAD2 h;
};
 
struct CSP_ANS_CSINITDATA
{
	struct PWMSG_HEAD h;	// C2:81
	int iResult;	// 0x04
	unsigned short wMapSvrNum;	// 0x08
	unsigned short wStartYear;	// 0x0A
	unsigned char btStartMonth;	// 0x0C
	unsigned char btStartDay;	// 0x0D
	unsigned short wEndYear;	// 0x0E
	unsigned char btEndMonth;	// 0x10
	unsigned char btEndDay;		// 0x11
	unsigned char btIsSiegeGuildList;	// 0x12
	unsigned char btIsSiegeEnded;	// 0x13
	unsigned char btIsCastleOccupied; // 0x14
	char szCastleOwnGuild[0x8];	// 0x15
	__int64 i64CastleMoney;	// 0x20
	int iTaxRateChaos;	// 0x28
	int iTaxRateStore;	// 0x2C
	int iTaxHuntZone;	// 0x30
	int iFirstCreate;	// 0x34
	int iCount;	// 0x38
};
// size 0x3C

struct CSP_CSINITDATA
{
	int iNpcNumber;	// 0
	int iNpcIndex;	// 4
	int iNpcDfLevel;// 8
	int iNpcRgLevel;// C
	int iNpcMaxHp;	// 10
	int iNpcHp;	// 14
	unsigned char btNpcX;//18
	unsigned char btNpcY;//19
	unsigned char btNpcDIR;//1A
};

struct CSP_CALCREGGUILDLIST
{
	char szGuildName[0x8];	// 0
	int iRegMarkCount;	// 8
	int iGuildMemberCount;	// C
	int iGuildMasterLevel;	// 10
	int iSeqNum;	// 14
};

struct CSP_CSGUILDUNIONINFO
{
	char szGuildName[0x8];	// 0
	int iCsGuildID;	// 8
};

struct CSP_CSLOADTOTALGUILDINFO
{
	char szGuildName[0x8];	// 0

	int iCsGuildID;	// 8
	int iGuildInvolved;	// C
};

struct PMSG_CSATTKGUILDLIST
{
	BYTE btCsJoinSide;
	BYTE btGuildInvolved;
	char szGuildName[8];
};


struct PMSG_REQ_MOVE_TO_CASTLE_HUNTZONE 
{
	PBMSG_HEAD2 h;
	int iPrice;
};
 
struct PMSG_REQ_WEREWOLF_MOVE
{
	PBMSG_HEAD2 h;
};

struct PMSG_REQ_GATEKEEPER_MOVE
{
	PBMSG_HEAD2 h;
};

void ProtocolCore(BYTE protoNum, LPBYTE aRecv, int aLen, int aIndex, BOOL Encrypt, int serial);
void TestSend();
void MsgSendV2(LPOBJ lpObj, unsigned char* Msg, int size);
void CGLiveClient(PMSG_CLIENTTIME* lpClientTime, short aIndex);
void GCCheckMainExeKeySend(int aIndex);
WORD EncryptCheckSumKey(WORD wSource);
void CGCheckMainRecv(PMSG_CHECK_MAINEXE_RESULT* lpMsg, int aIndex);
void PEchoProc(unsigned char* aMsg, int aLen, short aIndex);
void GCResultSend(int aIndex, unsigned char headcode, unsigned char result);
void ChatSend(LPOBJ lpObj, char* szChat);
void vChatSend(LPOBJ lpObj, char* szChat, ...);
void AllSendServerMsg(char* chatmsg);
void DataSendAll(unsigned char* lpMsg, int iMsgSize);
void ChatTargetSend(LPOBJ lpObj, char* szChat, int senduser);
void PChatProc(PMSG_CHATDATA* lpChat, short aIndex);
void CGChatRecv(PMSG_CHATDATA_NUMBER* lpMsg, int aIndex);
void GCServerMsgSend(unsigned char msg, int aIndex);
void GCServerMsgStringSend(char* szMsg, int aIndex, BYTE type);
void GCServerMsgStringSendGuild(_GUILD_INFO_STRUCT* lpNode, char* szMsg, unsigned char type);
void GCEventStateSend(int aIndex, unsigned char state, unsigned char event);
void GCMapEventStateSend(int map, unsigned char state, unsigned char event);
void CGReqWerewolfMove(PMSG_REQ_WEREWOLF_MOVE* lpMsg, int iIndex);
void CGReqGatekeeperMove(PMSG_REQ_GATEKEEPER_MOVE* lpMsg, int iIndex);
void CGChatWhisperRecv(PMSG_CHATDATA_WHISPER* lpMsg, int aIndex);
void SCPJoinResultSend(int aIndex, unsigned char result);
void CSPJoinIdPassRequest(PMSG_IDPASS* lpMsg, int aIndex);
void CSPJoinIdPassRequestTEST(PMSG_IDPASS* lpMsg, int aIndex);
void GCJoinResult(unsigned char result, int aIndex);
void GCJoinSocketResult(unsigned char result, SOCKET Socket);
void CGClientCloseMsg(PMSG_CLIENTCLOSE* lpMsg, int aIndex);
void GCCloseMsgSend(int aIndex, unsigned char result);
void CGClientMsg(PMSG_CLIENTMSG* lpMsg, int aIndex);
void CGPCharacterCreate(PMSG_CHARCREATE* lpMsg, int aIndex);
void CGPCharDel(PMSG_CHARDELETE* lpMsg, int aIndex);
void CGPCharacterMapJoinRequest(PMSG_CHARMAPJOIN* lpMsg, int aIndex);
void GCLevelUpMsgSend(int aIndex, int iSendEffect);
void CGLevelUpPointAdd(PMSG_LVPOINTADD* lpMsg, int aIndex);
void GCInventoryItemOneSend(int aIndex, int pos);
void GCPkLevelSend(int aIndex, unsigned char pklevel);
void GCMagicListOneSend(int aIndex, char Pos, unsigned char type, unsigned char level, unsigned char skill, BYTE btListType);
void GCMagicListOneDelSend(int aIndex, char Pos, BYTE type, BYTE level, BYTE skill, BYTE btListType);
void GCMagicListMultiSend(LPOBJ lpObj, BYTE btListType);
void GCEquipmentSend(int aIndex);
void GCRecallMonLife(int aIndex, int maxlife, int life);
void GCTimeViewSend(int aIndex, int second);
void GCGoalSend(int aIndex, char* Name1, unsigned char score1, char* Name2, unsigned char score2);
void GCSkillKeyRecv(PMSG_SKILLKEY* lpMsg, int aIndex);
void GCSkillKeySend(int aIndex, unsigned char* keybuffer, unsigned char GO, unsigned char Qk, unsigned char Wk, unsigned char Ek, /*<regrel ebp+0x20>*/ /*|0x1|*/ unsigned char ChatWnd);
void GCMoneySend(int aIndex, unsigned long money);
void GCItemInventoryPutSend(int aIndex, unsigned char result, unsigned char iteminfo1, unsigned char iteminfo2);
void CGItemGetRequest(PMSG_ITEMGETREQUEST* lpMsg, int aIndex);
BOOL CGItemDropRequest(PMSG_ITEMTHROW* lpMsg, int aIndex, int drop_type);
void GCItemMoveResultSend(int aIndex, unsigned char result, unsigned char pos, unsigned char* const ItemInfo);
void CGInventoryItemMove(PMSG_INVENTORYITEMMOVE* lpMsg, int aIndex);
void GCEquipmentChange(int aIndex, int pos);
void CGTalkRequestRecv(PMSG_TALKREQUEST* lpMsg, int aIndex);
void GCUserWarehouseSend(LPOBJ lpObj);
void CGBuyRequestRecv(PMSG_BUYREQUEST* lpMsg, int aIndex);
void CGSellRequestRecv(PMSG_SELLREQUEST* lpMsg, int aIndex);
int  GetNeedMoneyItemDurRepaire(class CItem* DurItem, int RequestPos);
void ItemDurRepaire(LPOBJ lpObj, class CItem* DurItem, int pos, int RequestPos);
void CGModifyRequestItem(PMSG_ITEMDURREPAIR* lpMsg, int aIndex);
void CGTradeRequestSend(PMSG_TRADE_REQUEST* lpMsg, int aIndex);
void CGTradeResponseRecv(PMSG_TRADE_RESPONSE* lpMsg, int aIndex);
BOOL GCTradeResponseSend(BYTE response, int aIndex, LPSTR id, WORD level, int GuildNumber);
int GCTradeOtherDel(int aIndex, BYTE tradeindex);
int GCTradeOtherAdd(int aIndex, BYTE tradeindex, LPBYTE iteminfo);
void CGTradeMoneyRecv(PMSG_TRADE_GOLD* lpMsg, int aIndex);
BOOL GCTradeMoneyOther(int aIndex, DWORD money);
BOOL GCTradeOkButtonSend(int aIndex, unsigned char flag);
void CGTradeOkButtonRecv(PMSG_TRADE_OKBUTTON* lpMsg, int aIndex);
void CGTradeCancelButtonRecv(int aIndex);
void CGTradeResult(int aIndex, unsigned char result);
void CGPShopReqSetItemPrice(PMSG_REQ_PSHOP_SETITEMPRICE* lpMsg, int aIndex);
void CGPShopAnsSetItemPrice(int aIndex, BYTE btResult, BYTE btItemPos);
void CGPShopReqOpen(PMSG_REQ_PSHOP_OPEN* lpMsg, int aIndex);
void CGPShopAnsOpen(int aIndex, BYTE btResult);
void CGPShopReqClose(int aIndex);
void CGPShopAnsClose(int aIndex, BYTE btResult);
void CGPShopReqBuyList(PMSG_REQ_BUYLIST_FROM_PSHOP* lpMsg, int aSourceIndex);
void CGPShopAnsBuyList(int aSourceIndex, int aTargetIndex, BYTE btResult, bool bResend);
void CGPShopReqBuyItem(PMSG_REQ_BUYITEM_FROM_PSHOP* lpMsg, int aSourceIndex);
void CGPShopAnsBuyItem(int aSourceIndex, int aTargetIndex, int iItemPos, BYTE btResult);
void CGPShopReqCloseDeal(PMSG_REQ_PSHOPDEAL_CLOSE* lpMsg, int aIndex);
void CGPShopAnsSoldItem(int aSourceIndex, int aTargetIndex, int iItemPos);
void CGPShopAnsDealerClosedShop(int aSourceIndex, int aTargetIndex);
void CGPartyRequestRecv(PMSG_PARTYREQUEST* lpMsg, int aIndex);
void CGPartyRequestResultRecv(PMSG_PARTYREQUESTRESULT* lpMsg, int aIndex);
void CGPartyList(int aIndex);
void CGPartyListAll(int pnumber);
void CGPartyDelUser(PMSG_PARTYDELUSER* lpMsg, int aIndex);
void GCPartyDelUserSend(int aIndex);
void CGGuildRequestRecv(PMSG_GUILDJOINQ* lpMsg, int aIndex);
void CGGuildRequestResultRecv(PMSG_GUILDQRESULT* lpMsg, int aIndex);
void CGGuildListAll(int pnumber);
void CGGuildDelUser(PMSG_GUILDDELUSER* lpMsg, int aIndex);
void GCGuildDelUserResult(int aIndex, unsigned char Result);
void GCGuildMasterQuestionSend(int aIndex);
void CGGuildMasterAnswerRecv(PMSG_GUILDMASTERANSWER* lpMsg, int aIndex);
void GCGuildMasterManagerRun(int aIndex);
void CGGuildMasterInfoSave(int aIndex,PMSG_GUILDINFOSAVE* lpMsg);
void CGGuildMasterCreateCancel(int aIndex);
void GCGuildViewportNowPaint(int aIndex, char* guildname, unsigned char* Mark, int isGuildMaster);
void GCGuildViewportDelNow(int aIndex, int isGuildMaster);
void GCManagerGuildWarEnd(char* GuildName);
void GCManagerGuildWarSet(char* GuildName1, char* GuildName2, int type);
void GCGuildWarRequestResult(char* GuildName, int aIndex, int type);
void GCGuildWarRequestSend(char* GuildName, int aIndex, int type);
void GCGuildWarRequestSendRecv(PMSG_GUILDWARSEND_RESULT* lpMsg, int aIndex);
void GCGuildWarDeclare(int aIndex, char* _guildname);
void GCGuildWarEnd(int aIndex, unsigned char result, char* _guildname);
void GCGuildWarScore(int aIndex);
void CGWarehouseMoneyInOut(int aIndex,PMSG_WAREHOUSEMONEYINOUT* lpMsg);
void GCWarehouseInventoryMoneySend(int aIndex, unsigned char result, int money, int wmoney);
void CGWarehouseUseEnd(int aIndex);
void GCWarehouseStateSend(int aIndex, unsigned char state);
void GCWarehouseRecivePassword(int aIndex,PMSG_WAREHOUSEPASSSEND* lpMsg);
void GCUserChaosBoxSend(LPOBJ lpObj, int iChaosBoxType);
void CGChaosBoxItemMixButtonClick(PMSG_CHAOSMIX* aRecv, int aIndex);
void CGChaosBoxUseEnd(int aIndex);
void PMoveProc(PMSG_MOVE* lpMove, int aIndex);
void RecvPositionSetProc(PMSG_POSISTION_SET* lpMove, int aIndex);
void CGAttack(PMSG_ATTACK* lpMsg, int aIndex);
void GCDamageSend(int aIndex, int damage, int iShieldDamage);
void GCDamageSend(int aIndex, int TargetIndex, int AttackDamage, int MSBFlag, int MSBDamage, int iShieldDamage);
void GCKillPlayerExpSend(int aIndex, int TargetIndex, int exp, int AttackDamage, int MSBFlag);
void GCDiePlayerSend(LPOBJ lpObj, int TargetIndex, BYTE skill, int KillerIndex);
void GCActionSend(LPOBJ lpObj, BYTE ActionNumber, int aIndex, int aTargetIndex);
void CGActionRecv(PMSG_ACTION* lpMsg, int aIndex);
void CGMagicAttack(PMSG_MAGICATTACK* lpMsg, int aIndex);
void GCMagicAttackNumberSend(LPOBJ lpObj, BYTE MagicNumber, int usernumber, unsigned char skillsuccess);
void GCMagicCancelSend(LPOBJ lpObj, BYTE MagicNumber);
void GCMagicCancel(PMSG_MAGICCANCEL * lpMsg, int aIndex);
void GCUseEffectItem(LPOBJ lpObj, int iEffectUseOption, int iOptionType, int iEffectType, int iLeftTime);
void CGMagicCancel(PMSG_MAGICCANCEL* lpMsg, int aIndex);
void GCUseMonsterSkillSend(LPOBJ lpObj, LPOBJ lpTargetObj, int iSkillNumber);
void GCStateInfoSend(LPOBJ lpObj, unsigned char state, int ViewSkillState);
void CGTeleportRecv(PMSG_TELEPORT* lpMsg, int aIndex);
void CGTargetTeleportRecv(PMSG_TARGET_TELEPORT* lpMsg, int aIndex);
void GCTeleportSend(LPOBJ lpObj, unsigned char MoveNumber, BYTE MapNumber, BYTE MapX, BYTE MapY, BYTE Dir);
void CGBeattackRecv(unsigned char* lpRecv, int aIndex, int magic_send);
void CGDurationMagicRecv(PMSG_DURATION_MAGIC_RECV* lpMsg, int aIndex);
void ObjectMapJoinPositionSend(short aIndex);
void CGUseItemRecv(PMSG_USEITEM* lpMsg, int aIndex);
void GCReFillSend(int aIndex, WORD Life, BYTE Ipos, unsigned char flag,  WORD wShield);
void GCManaSend(int aIndex, short Mana, BYTE Ipos, unsigned char flag,  WORD BP);
void GCInventoryItemDeleteSend(int aIndex, BYTE pos, unsigned char flag);
void GCItemUseSpecialTimeSend(int aIndex, unsigned char number, int time);
void GCItemDurSend(int aIndex, BYTE pos, unsigned char dur, unsigned char flag);
void GCItemDurSend2(int aIndex, BYTE pos, unsigned char dur, unsigned char flag);
void CGWeatherSend(int aIndex, BYTE weather);
void GCServerCmd(int aIndex, BYTE type, unsigned char Cmd1, unsigned char Cmd2);
void GCReqmoveDevilSquare(PMSG_REQ_MOVEDEVILSQUARE* lpMsg, int aIndex);
void GCReqDevilSquareRemainTime(PMSG_REQ_DEVILSQUARE_REMAINTIME* lpMsg, int aIndex);
void AllSendMsg(unsigned char* Msg, int size);
void AllSendSameMapMsg(unsigned char* Msg, int size, unsigned char mapnumber);
void GCSendPing(int aIndex);
void GCPingSendRecv(PMSG_PING_RESULT* aRecv, int aIndex);
void GCRegEventChipRecv(PMSG_REGEVENTCHIP* lpMsg, int aIndex);
void GCGetMutoNumRecv(PMSG_GETMUTONUMBER* lpMsg, int aIndex);
void GCUseEndEventChipRescv(int aIndex);
void GCUseRenaChangeZenRecv(PMSG_EXCHANGE_EVENTCHIP* lpMsg, int aIndex);
void CGRequestQuestInfo(int aIndex);
void GCSendQuestInfo(int aIndex, int QuestIndex);
void CGSetQuestState(PMSG_SETQUEST* lpMsg, int aIndex);
void GCSendQuestPrize(int aIndex, unsigned char Type, unsigned char Count);
void CGCloseWindow(int aIndex);
void CGRequestEnterBloodCastle(PMSG_REQ_MOVEBLOODCASTLE* lpMsg, int iIndex);
void CGRequestEnterChaosCastle(PMSG_REQ_MOVECHAOSCASTLE* lpMsg, int iIndex);
void CGRequestRepositionUserInChaosCastle(PMSG_REQ_REPOSUSER_IN_CC* lpMsg, int aIndex);
void CGRequestEventEnterCount(PMSG_REQ_CL_ENTERCOUNT* lpMsg, int aIndex);
void CGRequestLottoRegister(PMSG_REQ_2ANV_LOTTO_EVENT* lpMsg, int aIndex);
void CGReqMoveOtherServer(PMSG_REQ_MOVE_OTHERSERVER* lpMsg, int aIndex);
void GCPacketCheckSumRecv(PMSG_PACKETCHECKSUM* aRecv, int aIndex);

//void GCNPggSendCheckSum(int aIndex,_GG_AUTH_DATA* pggAuthData);
//void GCNPggCheckSumRecv(PMSG_NPROTECTGGCHECKSUM* lpMsg, int aIndex);

void CGDuelStartRequestRecv(PMSG_REQ_START_DUEL* lpMsg, int aIndex);
void CGDuelEndRequestRecv(PMSG_REQ_END_DUEL* lpMsg, int aIndex);
void CGDuelOkRequestRecv(PMSG_ANS_DUEL_OK* lpMsg, int aIndex);
void GCSendDuelScore(int aIndex1, int aIndex2);
void GCSendGetItemInfoForParty(int aIndex, class CMapItem* lpItem);
void GCSendEffectInfo(int aIndex, BYTE btType);
void CGRequestPetItemCommand(PMSG_REQUEST_PET_ITEM_COMMAND* lpMsg, int aIndex);
void CGRequestPetItemInfo(PMSG_REQUEST_PET_ITEMINFO* lpMsg, int aIndex);
void GCGuildViewportInfo(PMSG_REQ_GUILDVIEWPORT* aRecv, int aIndex);
void CGGuildAssignStatus(PMSG_GUILD_ASSIGN_STATUS_REQ* aRecv, int aIndex);
void CGGuildAssignType(PMSG_GUILD_ASSIGN_TYPE_REQ* aRecv, int aIndex);
void CGRelationShipReqJoinBreakOff(PMSG_RELATIONSHIP_JOIN_BREAKOFF_REQ* aRecv, int aIndex);
void CGRelationShipAnsJoinBreakOff(PMSG_RELATIONSHIP_JOIN_BREAKOFF_ANS* aRecv, int aIndex);
void CGUnionList(PMSG_UNIONLIST_REQ* aRecv, int aIndex);
void CGRelationShipReqKickOutUnionMember(PMSG_KICKOUT_UNIONMEMBER_REQ* aRecv, int aIndex);
void CGReqMapSvrAuth(PMSG_REQ_MAPSERVERAUTH* lpMsg, int iIndex);
void GCAnsMapSvrAuth(int iIndex, int iResult);
void CGReqCastleSiegeState(PMSG_REQ_CASTLESIEGESTATE* lpMsg, int iIndex);
void GCAnsCastleSiegeState(int iIndex, int iResult, char* lpszGuildName, char* lpszGuildMaster);
void CGReqRegCastleSiege(PMSG_REQ_REGCASTLESIEGE* lpMsg, int iIndex);
void GCAnsRegCastleSiege(int iIndex, int iResult, char* lpszGuildName);
void CGReqGiveUpCastleSiege(PMSG_REQ_GIVEUPCASTLESIEGE* lpMsg, int iIndex);
void GCAnsGiveUpCastleSiege(int iIndex, int iResult, int bGiveUp, int iMarkCount, char* lpszGuildName);
void CGReqGuildRegInfo(PMSG_REQ_GUILDREGINFO* lpMsg, int iIndex);
void GCAnsGuildRegInfo(int iIndex, int iResult,CSP_ANS_GUILDREGINFO* lpMsgResult);
void CGReqRegGuildMark(PMSG_REQ_REGGUILDMARK* lpMsg, int iIndex);
void GCAnsRegGuildMark(int iIndex, int iResult,CSP_ANS_GUILDREGMARK* lpMsgResult);
void CGReqNpcBuy(PMSG_REQ_NPCBUY* lpMsg, int iIndex);
void GCAnsNpcBuy(int iIndex, int iResult, int iNpcNumber, int iNpcIndex);
void CGReqNpcRepair(PMSG_REQ_NPCREPAIR* lpMsg, int iIndex);
void GCAnsNpcRepair(int iIndex, int iResult, int iNpcNumber, int iNpcIndex, int iNpcHP, int iNpcMaxHP);
void CGReqNpcUpgrade(PMSG_REQ_NPCUPGRADE* lpMsg, int iIndex);
void GCAnsNpcUpgrade(int iIndex, int iResult, int iNpcNumber, int iNpcIndex, int iNpcUpType, int iNpcUpValue);
void CGReqTaxMoneyInfo(PMSG_REQ_TAXMONEYINFO* lpMsg, int iIndex);
void GCAnsTaxMoneyInfo(int iIndex, int iResult, BYTE btTaxRateChaos, BYTE btTaxRateStore, __int64 i64Money);
void CGReqTaxRateChange(PMSG_REQ_TAXRATECHANGE* lpMsg, int iIndex);
void GCAnsTaxRateChange(int iIndex, int iResult, BYTE btTaxType, int iTaxRate);
void CGReqMoneyDrawOut(PMSG_REQ_MONEYDRAWOUT* lpMsg, int iIndex);
void GCAnsMoneyDrawOut(int iIndex, int iResult, __int64 i64Money);
void GCAnsCsGateState(int iIndex, int iResult, int iGateIndex);
void CGReqCsGateOperate(PMSG_REQ_CSGATEOPERATE* lpMsg, int iIndex);
void GCAnsCsGateOperate(int iIndex, int iResult, int iGateIndex, int iGateOperate);
void GCAnsCsGateCurState(int iIndex, int iGateIndex, int iGateOperate);
void GCAnsCsAccessSwitchState(int iIndex, int iSwitchIndex, int iSwitchUserIndex, BYTE btSwitchState);
void GCAnsCsAccessCrownState(int iIndex, BYTE btCrownState);
void GCAnsCsNotifyStart(int iIndex, BYTE btStartState);
void GCAnsCsNotifyProgress(int iIndex, BYTE btCastleSiegeState, char* lpszGuildName);
void GCAnsCsMapSvrTaxInfo(int iIndex, BYTE btTaxType, BYTE btTaxRate);
void CGReqCsMiniMapData(PMSG_REQ_MINIMAPDATA* lpMsg, int iIndex);
void GCAnsCsMiniMapData(int iIndex, BYTE btResult);
void CGReqStopCsMiniMapData(PMSG_REQ_STOPMINIMAPDATA* lpMsg, int iIndex);
void CGReqCsSendCommand(PMSG_REQ_CSCOMMAND* lpMsg, int iIndex);
void GCAnsCsSendCommand(int iCsJoinSide, BYTE btTeam, BYTE btX, BYTE btY, BYTE btCommand);
void GCAnsCsLeftTimeAlarm(BYTE btHour, BYTE btMinute);
void GCAnsSelfCsLeftTimeAlarm(int iIndex, BYTE btHour, BYTE btMinute);
void CGReqCsSetEnterHuntZone(PMSG_REQ_CSHUNTZONEENTER* lpMsg, int iIndex);
void GCAnsCsSetEnterHuntZone(int iIndex, BYTE btResult, BYTE btEnterHuntZone);
void CGReqNpcDbList(PMSG_REQ_NPCDBLIST* lpMsg, int iIndex);
void CGReqCsRegGuildList(PMSG_REQ_CSREGGUILDLIST* lpMsg, int iIndex);
void CGReqCsAttkGuildList(PMSG_REQ_CSATTKGUILDLIST* lpMsg, int iIndex);
void CGReqWeaponUse(PMSG_REQ_USEWEAPON* aRecv, int iIndex);
void CGReqWeaponDamageValue(PMSG_REQ_WEAPON_DAMAGE_VALUE* aRecv, int iIndex); 
void GCSendObjectCreationState(int iObjectIndex);
void CGReqCastleHuntZoneEntrance(PMSG_REQ_MOVE_TO_CASTLE_HUNTZONE* aRecv, int iIndex); 

void CGReqGuildMarkOfCastleOwner(PMSG_REQ_GUILDMARK_OF_CASTLEOWNER* aRecv, int iIndex);
void CGReqJewelMix(PMSG_REQ_JEWEL_MIX* lpMsg, int iIndex);
void GCAnsJewelMix(int iIndex, int iResult);
void CGReqJewelUnMix(PMSG_REQ_JEWEL_UNMIX* lpMsg, int iIndex);
void GCAnsJewelUnMix(int iIndex, int iResult);
void CGReqCrywolfInfo(PMSG_REQ_CRYWOLF_INFO* lpMsg, int iIndex);
void GCAnsCrywolfInfo(int iIndex, BYTE btOccupationState, BYTE btCrywolfState);
void CGReqAlatrContract(PMSG_REQ_CRYWOLF_ALTAR_CONTRACT* lpMsg, int iIndex);
void CGReqPlusChaosRate(PMSG_REQ_CRYWOLF_BENEFIT_PLUS_CHAOSRATE* lpMsg, int iIndex);
void CGReqKanturuStateInfo(PMSG_REQ_KANTURU_STATE_INFO* lpMsg, int iIndex);
void GCReqEnterKanturuBossMap(PMSG_REQ_ENTER_KANTURU_BOSS_MAP* lpMsg, int iIndex);

//void CGReqCastleHuntZoneEntrance(PMSG_REQ_MOVE_TO_CASTLE_HUNTZONE* aRecv, int iIndex);

#endif