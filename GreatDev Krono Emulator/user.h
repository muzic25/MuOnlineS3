// ------------------------------
// Decompiled by Deathway
// Date : 2007-05-09
// ------------------------------
#ifndef USER_H__
#define USER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkillDelay.h"
#include "ComboAttack.h"
#include "giocp.h"
//#include "..\ggsvr\ggsvr.h"
#include "MagicInf.h"
#include "zzzitem.h"
#include "classdef.h"
#include "define.h"
#include "GuildClass.h"
#include "TDurMagicKeyChecker.h"
#include "TMonsterAIAgro.h"
#include "TMonsterSkillElementInfo.h"
#include "JewelOfHarmonySystem.h"
#include "ItemSystemFor380.h"

#define OBJMIN 0 
#define OBJMAX 15000
#define OBJMAXUSER 1000
//#define OBJ_MAXMONSTER 13500
#define OBJ_STARTUSERINDEX (OBJMAX - OBJMAXUSER)
#define OBJ_MAXMONSTER				(OBJ_STARTUSERINDEX - 500)		//11500 //5800
#define OBJ_STARTUSERINDEX (OBJMAX - OBJMAXUSER)
#define OBJ_CALLMONCOUNT (OBJ_STARTUSERINDEX - OBJ_MAXMONSTER)
#define MAX_MONSTER_SEND_MSG	10
#define MAX_MONSTER_SEND_ATTACK_MSG	50
#define MAX_MONSTER_TYPE 512
#define MAX_GUILD_LEN 8
#define MAX_ACCOUNT_LEN 10
#define INVENTORY_SIZE 108
#define WAREHOUSE_SIZE 120
#define TRADE_BOX_SIZE 32
#define MAGIC_SIZE 60
#define INVETORY_WEAR_SIZE	12
#define INVENTORY_BAG_START INVETORY_WEAR_SIZE
#define MAIN_INVENTORY_SIZE 76	// Not included PersonalSh
#define INVENTORY_MAP_SIZE 96	// Not included wared iems
#define TRADE_BOX_MAP_SIZE 32
#define PSHOP_SIZE 32
#define PSHOP_MAP_SIZE 32
#define MAX_CHAR_LEVEL	400
#define MAX_SELF_DEFENSE 5
#define MAX_ST_HIT_DAMAGE 40
#define MAX_ZEN 2000000000
#define MAX_WAREHOUSE_ZEN	100000000
#define ACTIVE_ITEM_SEARCH 0
#define CHAOS_BOX_SIZE 32
#define CHAOS_BOX_MAP_SIZE 32 

enum MAP_INDEX
{
	MAP_INDEX_RORENCIA = 0x0,
	MAP_INDEX_DUNGEON = 0x1,
	MAP_INDEX_DEVIAS = 0x2,
	MAP_INDEX_NORIA = 0x3,
	MAP_INDEX_LOSTTOWER = 0x4,
	MAP_INDEX_RESERVED = 0x5,
	MAP_INDEX_BATTLESOCCER = 0x6,
	MAP_INDEX_ATHLANSE = 0x7,
	MAP_INDEX_TARKAN = 0x8,
	MAP_INDEX_DEVILSQUARE = 0x9,
	MAP_INDEX_ICARUS = 0xa,
	MAP_INDEX_BLOODCASTLE1 = 0xb,
	MAP_INDEX_BLOODCASTLE2 = 0xc,
	MAP_INDEX_BLOODCASTLE3 = 0xd,
	MAP_INDEX_BLOODCASTLE4 = 0xe,
	MAP_INDEX_BLOODCASTLE5 = 0xf,
	MAP_INDEX_BLOODCASTLE6 = 0x10,
	MAP_INDEX_BLOODCASTLE7 = 0x11,
	MAP_INDEX_CHAOSCASTLE1 = 0x12,
	MAP_INDEX_CHAOSCASTLE2 = 0x13,
	MAP_INDEX_CHAOSCASTLE3 = 0x14,
	MAP_INDEX_CHAOSCASTLE4 = 0x15,
	MAP_INDEX_CHAOSCASTLE5 = 0x16,
	MAP_INDEX_CHAOSCASTLE6 = 0x17,
	MAP_INDEX_KALIMA1 = 0x18,
	MAP_INDEX_KALIMA2 = 0x19,
	MAP_INDEX_KALIMA3 = 0x1a,
	MAP_INDEX_KALIMA4 = 0x1b,
	MAP_INDEX_KALIMA5 = 0x1c,
	MAP_INDEX_KALIMA6 = 0x1d,
	MAP_INDEX_CASTLESIEGE = 0x1e,
	MAP_INDEX_CASTLEHUNTZONE = 0x1f,
	MAP_INDEX_DEVILSQUARE2 = 0x20,
	MAP_INDEX_AIDA = 0x21,
	MAP_INDEX_CRYWOLF_FIRSTZONE = 0x22,
	MAP_INDEX_CRYWOLF_SECONDZONE = 0x23,
	MAP_INDEX_KALIMA7 = 0x24,
	MAP_INDEX_KANTURU1 = 0x25,
	MAP_INDEX_KANTURU2 = 0x26,
	MAP_INDEX_KANTURU_BOSS = 0x27,
	MAP_INDEX_GM_SUMMONZONE = 0x28,
	MAP_INDEX_BALGASS_BARRACKS = 0x29,
	MAP_INDEX_BALGASS_REFUGEE = 0x2A,
	MAP_INDEX_BLOODCASTLE8 = 0x34,
	MAP_INDEX_CHAOSCASTLE7 = 0x35,
	MAP_INDEX_SANTATOWN = 62,
	MAP_INDEX_VULCANROOM = 63,
	MAP_INDEX_DUELROOM = 64,
	MAP_INDEX_ILLUSION_TEMPLE1 = 0x2D,
	MAP_INDEX_ILLUSION_TEMPLE2 = 0x2E,
	MAP_INDEX_ILLUSION_TEMPLE3 = 0x2F,
	MAP_INDEX_ILLUSION_TEMPLE4 = 0x30,
	MAP_INDEX_ILLUSION_TEMPLE5 = 0x31,
};




enum EXP_GETTING_EVENT_TYPE {
	EVENT_TYPE_NONE = 0x0,
	EVENT_TYPE_PARTY = 0x1,
	EVENT_TYPE_DEVILSQUARE = 0x2,
	EVENT_TYPE_CHAOSCASTLE = 0x3,
	EVENT_TYPE_BLOODCASTLE = 0x4,
	EVENT_TYPE_CRYWOLF = 0x5,
};








#define MAX_RESISTENCE_TYPE 7

#define R_ICE			0
#define R_POISON		1
#define R_LIGHTNING		2
#define R_FIRE			3
#define R_EARTH			4
#define R_WIND			5
#define R_WATER			6



#define OBJ_EMPTY -1
#define OBJ_MONSTER 2
#define OBJ_USER 1
#define OBJ_NPC	3
#define MAX_PARTY_LEVEL_DIFFERENCE	130
#define MAX_MAGIC 60
#define MAX_VIEWPORT 75 
#define MAX_VIEWPORT_MONSTER 75 //gs 20

#define MAX_ROAD_PATH_TABLE 16
#define MAX_ARRAY_FRUSTRUM 4
#define PLAYER_EMPTY  0
#define PLAYER_CONNECTED 1
#define PLAYER_LOGGED 2
#define PLAYER_PLAYING 3
#define MAX_CHECKSUM_KEY 1024
#define OBJMAX_RANGE(aIndex) ( ((aIndex) < 0 )?FALSE:( (aIndex) > OBJMAX-1 )?FALSE:TRUE   )
#define FRIEND_SERVER_STATE_LOGIN_FAIL	0
#define FRIEND_SERVER_STATE_OFFLINE		1
#define FRIEND_SERVER_STATE_ONLINE		2

#define MAIN_INVENTORY_RANGE(x) (((x)<0)?FALSE:((x)>MAIN_INVENTORY_SIZE-1)?FALSE:TRUE )
#define INVENTORY_RANGE(x) (((x)<0)?FALSE:((x)>INVENTORY_SIZE-1)?FALSE:TRUE )
#define WAREHOUSE_RANGE(x) (((x)<0)?FALSE:((x)>WAREHOUSE_SIZE-1)?FALSE:TRUE )
#define TRADE_BOX_RANGE(x) (((x)<0)?FALSE:((x)>TRADE_BOX_SIZE-1)?FALSE:TRUE )
#define OBJMON_RANGE(x) ( ((x)<0)?FALSE:((x)>OBJ_MAXMONSTER-1)?FALSE:TRUE)
#define PSHOP_RANGE(x) ( (((x)-MAIN_INVENTORY_SIZE)<0)?FALSE:(((x)-MAIN_INVENTORY_SIZE)>(INVENTORY_SIZE-MAIN_INVENTORY_SIZE-1))?FALSE:TRUE )
#define ATTRIBUTE_RANGE(x) (((x)<51)?FALSE:((x)>58)?FALSE:TRUE )

#define CURRENT_DB_VERSION	3
/*
 *	CHAR SET
 *	
 *	It Contains the Character Settings
 *	CS_CLASS(0)	Contains the Class and the ChangeUP
 *				You can use CS_GET_CLASS and CS_GET_CHANGEUP
 *	MAP of CHAR SET
 *
 *	    0         1			2		  3			4		  5			6		  7
 *	0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *	AAAB k CC EEEE EEEE GGGG GGGG JJJJ MMMM PPPP SSSS VVVV WWjj XXXX XXXX YYYY YYYY
 *
 *	    8         9			10		  11		12		  13		14		  15
 *	0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
 *	ZZZZ ZZZZ ILOR Uiii aaaa aaad bbbb bbbc DDDD  hne FFFF HHHH KKKK NNNN QQQQ TTTT
 *
 *		16		  17
 *	0000 0000 0000 0000
 *	   l llgf         m
 *
 *	AAA Contain Class Character Definition (DK:1 DW:0 ELF:2 MG:3 DL:4)
 *	B Contains the Change UP (0:Normal 1:Evolved)
 *	CC Contains a value Acording m_ActionNumber fron gObj
 *
 *	DDDD Contains the 8..11 bits of Rigth Hand Item Index
 *	EEEE EEEE Contains the 0..7 bits Rigth Hand Item Index
 *
 *	FFFF Contains the 8..11 bits of Left Hand Item Index
 *	GGGG GGGG Contains the 0..7 bits of Left Hand Item Index
 *
 *	HHHH Contains the 5..8 Bits from Helmet Item Index
 *	I Contains the 4 bit from Helmet Item Index
 *	JJJJ Contains the 0..3 bits from Helmet Item Index
 *
 *	KKKK Contains the 5..8 Bits from Armor Item Index
 *	L Contains the 4 bit from Armor Item Index
 *	MMMM Contains the 0..3 bits from Armor Item Index
 *
 *	NNNN Contains the 5..8 Bits from Pants Item Index
 *	O Contains the 4 bit from Pants Item Index
 *	PPPP Contains the 0..3 bits from Pants Item Index
 *
 *	QQQQ Contains the 5..8 Bits from Gloves Item Index
 *	R Contains the 4 bit from Gloves Item Index
 *	SSSS Contains the 0..3 bits from Gloves Item Index
 *
 *	TTTT Contains the 5..8 Bits from Boots Item Index
 *	U Contains the 4 bit from Boots Item Index
 *	VVVV Contains the 0..3 bits from Boots Item Index
 *
 *	WW Contains Wings
 *
 *	XXXX XXXX Contains Levels (Shine Levels) from Wings and Boots
 *	YYYY YYYY Contains Levels (Shine Levels) from Gloves and Pants and Armor
 *	ZZZZ ZZZZ Contains Levels (Shine Levels) from Helmet , Right and Left HAnd
 *
 *	aaaa aaa Contains the If the item is Excellent
 *
 *	bbbb bbb Contains the If the item is SetItem
 *	c   1 if the Char have the Full Set Item
 *
 *	d   Dinorant
 *	e   Have Dark Horse
 *	f   Fenrir Inc Attack Damage
 *	g   Fenrir Dec Attack Damage
 *	h   Pet Fenrir
 *	iii	Another part of wings ( Third level wings )
 *	jj  Helper
 *	k   Master up???
 *	lll Unknown??? from 1 to 6 put items ITEMGET(12, 43)
 *	m   Unknown
 *	n   Unknown
 */
#define CHAR_SET_SIZE		18

	#define CS_CLASS		0

	#define CS_WEAPON1_TYPE	1
	#define CS_WEAPON2_TYPE	2

	#define CS_WEAPON1_DATA	12
	#define CS_WEAPON2_DATA	13

	#define CS_HELMET1		13
	#define CS_HELMET2		9
	#define CS_HELMET3		3

	#define CS_ARMOR1		14
	#define CS_ARMOR2		9
	#define CS_ARMOR3		3

	#define CS_PANTS1		14
	#define CS_PANTS2		9
	#define CS_PANTS3		4

	#define CS_GLOVES1		15
	#define CS_GLOVES2		9
	#define CS_GLOVES3		4

	#define CS_BOOTS1		15
	#define CS_BOOTS2		9
	#define CS_BOOTS3		5



#define CHECK_LIMIT(value, limit) ( ((value)<0)?FALSE:((value)>((limit)-1))?FALSE:TRUE  )
#define CHECK_LIMIT2(value, base, limit) ( ((value)<base)?FALSE:((value)>((limit)-1))?FALSE:TRUE  )
#define CHECK_CLASS(value, type) ( ((value)!=(type))?FALSE:TRUE )


#define CS_GET_CLASS(x) ( (((x)>>4)<<5)&(0xE0) )
#define CS_GET_CHANGEUP(x) ( ((x)&0x07) )
#define CS_SET_CLASS(x) ( ((x)<<5)& 0xE0 )
#define CS_SET_CHANGEUP(x) ( ((x) << 4) & 0x10 )
#define CS_SET_3RD_CHANGEUP(x) ( ((x) << 3) & 8 )
#define CS_SET_HELMET1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_HELMET2(x) ( ((x) & 0x10 ) << 3 )
#define CS_SET_HELMET3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_ARMOR1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_ARMOR2(x) ( ((x) & 0x10 ) << 2 )
#define CS_SET_ARMOR3(x) ( ((x) & 0x0F )      )

#define CS_SET_PANTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_PANTS2(x) ( ((x) & 0x10 ) << 1 )
#define CS_SET_PANTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_GLOVES1(x) ( ((x) & 0x1E0) >> 1 )
#define CS_SET_GLOVES2(x) ( ((x) & 0x10 )      )
#define CS_SET_GLOVES3(x) ( ((x) & 0x0F )      )

#define CS_SET_BOOTS1(x) ( ((x) & 0x1E0) >> 5 )
#define CS_SET_BOOTS2(x) ( ((x) & 0x10 ) >> 1 )
#define CS_SET_BOOTS3(x) ( ((x) & 0x0F ) << 4 )

#define CS_SET_WING1(x)  ( ((x) & 0x03 ) << 2 )
#define CS_SET_HELPER(x) ( ((x) & 0x03 )      )

#define CS_SET_SMALLLEVEL_RH(x)		( (x)       )
#define CS_SET_SMALLLEVEL_LH(x)		( (x) << 3  ) 
#define CS_SET_SMALLLEVEL_HELMET(x)	( (x) << 6  )
#define CS_SET_SMALLLEVEL_ARMOR(x)	( (x) << 9  )
#define CS_SET_SMALLLEVEL_PANTS(x)	( (x) << 12 )
#define CS_SET_SMALLLEVEL_GLOVES(x)	( (x) << 15 )
#define CS_SET_SMALLLEVEL_BOOTS(x)	( (x) << 18 )

#define CS_SET_SMALLLEVEL1(x)		( ((x) >> 16) & 0xFF )
#define CS_SET_SMALLLEVEL2(x)		( ((x) >> 8 ) & 0xFF )
#define CS_SET_SMALLLEVEL3(x)		((x) & 0xFF )





#include "ViewPortGuild.h"





typedef union tagPATHTABLE
{
	short sPathTable[16];
	char cPathTable[32];
} PATHTABLE, * LPPATHTABLE;



typedef struct tagActionState
{
	unsigned long Rest:1;	// 0
	unsigned long Attack:1;	// 1
	unsigned long Move:1;	// 2
	unsigned long Escape:1;	// 3
	unsigned long Emotion:4;	// 4
	unsigned long EmotionCount:8;	// 8

} ACTION_STATE, * LPACTION_STATE;



typedef struct tagInterfaceState
{
	DWORD use	: 2;
	DWORD state : 4;
	DWORD type	: 10;

} INTERFACE_STATE, * LPINTERFACE_STATE;



typedef struct
{
	DWORD unk0 : 1;
	DWORD unk1 : 1;
	DWORD unk2 : 1;
	DWORD unk3 : 1;
	DWORD unk4 : 1;
	DWORD unk5 : 1;
	DWORD unk6 : 1;
	DWORD unk7 : 1;
	DWORD unk8 : 1;
	DWORD unk9 : 1;
	DWORD unkA : 1;
	DWORD unkB : 1;
	DWORD unkC : 1;
	DWORD unkD : 1;
	DWORD unkE : 1;
	DWORD unkF : 1;
	DWORD unk10: 1;

}  ST_SKILL_STATE;


union STU_SKILL_STATE
{
	ST_SKILL_STATE SkillStates;
	DWORD AllData;
};



extern short RoadPathTable[MAX_ROAD_PATH_TABLE];
extern int  gServerMaxUser;	
extern BOOL g_EnergyCheckOff;





struct HITDAMAGE_STRUCT
{
	short number;	// 0
	int HitDamage;	// 4
	DWORD LastHitTime;	// 8
};




struct VIEWPORT_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8
};

struct VIEWPORT_PLAYER_STRUCT
{
	char state;	// 0
	short number;	// 2
	unsigned char type;	// 4
	short index;	// 6
	int dis;	// 8

};


struct MessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	DWORD MsgTime;	// 8
	int SubCode;	// C

};


struct ExMessageStateMachine
{
	int MsgCode;	// 0
	int SendUser;	// 4
	DWORD MsgTime;	// 8
	int SubCode;	// C
	int SubCode2;	// 10
};



typedef struct tagSEND_MONSTER_ATTACK_MENSSAGE
{
	int iMsgCode;	// unk0
	int iIndex;	// unk4
	DWORD dwDelay;	// unk8
	int iSubCode;	// unkC
	int iSubCode2;	// unk10
}SEND_MONSTER_ATTACK_MENSSAGE;

extern ExMessageStateMachine gSMAttackProcMsg[OBJMAX][MAX_MONSTER_SEND_ATTACK_MSG];
extern MessageStateMachine gSMMsg[OBJMAX][MAX_MONSTER_SEND_MSG];

struct MONSTERKILLINFO
{
	int MonIndex;
	int KillCount;
};

struct BUFF_MANAGER
{
	BYTE btBuffIndex; //210
	BYTE btVpIndex; //211
	BYTE btEffectType1; //212
	BYTE btEffectType2; //213
	int iValue1; //214
	int iValue2; //218
	DWORD dwBuffTickCount; //21C
	int iDuration; //220
};


struct OBJECTSTRUCT
{
	int m_Index;	// 0
	int Connected;	// 4
	char LoginMsgSnd;	// 8
	char LoginMsgCount;	// 9
	char CloseCount;	// A
	char CloseType;	// B
	BOOL bEnableDelCharacter;	// C
	_PER_SOCKET_CONTEXT* PerSocketContext;	// 10
	unsigned int m_socket;	// 14
	char Ip_addr[16];	// 18
	int UserNumber;	// 28
	int DBNumber;	// 2C
	unsigned char Magumsa;	// 20
	DWORD AutoSaveTime;	// 34
	DWORD ConnectCheckTime;	// 38
	DWORD CheckTick;	// 3C
	unsigned char CheckSpeedHack;	// 40
	DWORD CheckTick2;	// 44
	unsigned char CheckTickCount;	// 48
	DWORD SaveTimeForStatics;	// 4C
	int iPingTime;	// 50
	unsigned char m_TimeCount;	// 54
	DWORD m_dwPKTimer;	// 58
	short CheckSumTableNum;	// 5C
	DWORD CheckSumTime;	// 60
	WORD Type;	// 64
	unsigned char Live;	// 66
	char  CharacterPos;	// 67
	char  AccountID[11];	// 68
	char  Name[11];	// 73
	char  LastJoominNumber[14];	// 7E
	bool  PlusStatQuestClear; // 8C
	bool  ComboSkillquestClear;	// 8D
	ComboSkillData comboSkill; // 90
	WORD  Class; // 9C
	BYTE  DbClass;	// 9E
	BYTE  ChangeUP; // 9F
	BYTE	ChangeUP3rd;
	short Level; // A0
	int   LevelUpPoint; // A4
	int   iFruitPoint;	// A8
	DWORD Experience;	// AC
	DWORD NextExp; // B0
	int   Money; // B4
	unsigned short Strength; // B8
	unsigned short Dexterity;	// BA
	unsigned short Vitality;	// BC
	unsigned short Energy;	// BE
	float Life; // C0
	float MaxLife; // C4
	int   m_iScriptMaxLife;	// C8
	float FillLife;	// CC
	float FillLifeMax;	// D0
	float Mana;	// D4
	float MaxMana;	// D8
	WORD  Leadership;	// DC
	WORD  AddLeadership;	// DE
	WORD  ChatLimitTime;	// E0
	BYTE  ChatLimitTimeSec;	// E2
	BYTE  FillLifeCount;	// E3
	short AddStrength;	// E4
	short AddDexterity;	// E6
	short AddVitality;	// E8
	short AddEnergy;	// EA
	int   BP;	// EC
	int   MaxBP;	// F0
	int	  AddBP;	// F4
	float VitalityToLife;	// F8
	float EnergyToMana;	// FC
	char  m_PK_Count;	// 100
	char  m_PK_Level;	// 101
	int   m_PK_Time;	// 104
	short X; // 108
	short Y; // 10A
	BYTE  Dir; // 10C
	BYTE  MapNumber; // 10D
	int   AddLife;	// 110
	int   AddMana;	// 114
	int   iShield;	// 118
	int   iMaxShield;	// 11C
	int   iAddShield;	// 120
	int   iFillShieldMax;	// 124
	int   iFillShield;	// 128
	int   iFillShieldCount;	// 12C
	DWORD dwShieldAutoRefillTimer;	// 130
	BYTE  DamageMinus;	// 134
	BYTE  DamageReflect;	// 135
	short MonsterDieGetMoney;	// 136
	BYTE  MonsterDieGetLife;	// 138
	BYTE  MonsterDieGetMana;	// 139
	BYTE  StartX;	// 13A
	BYTE  StartY;	// 13B
	short m_OldX;	// 13C
	short m_OldY;	// 13E
	short TX;	// 140
	short TY;	// 142
	short MTX;	// 144
	short MTY;	// 146
	int   PathCount;	// 148
	int   PathCur;	// 14C
	char  PathStartEnd;	// 150
	short PathOri[15];	// 152
	short PathX[15];	// 170
	short PathY[15];	// 18E
	char  PathDir[15];	// 1AC
	DWORD PathTime; // 1BC
	BYTE  m_MoveGateNumber;	// 1C0
	DWORD Authority;	// 1C4
	DWORD AuthorityCode;	// 1C8
	DWORD Penalty;	// 1CC
	BYTE  m_cAccountItemBlock; // 1D0
	ACTION_STATE m_ActState;	// 1D4
	BYTE  m_ActionNumber;	// 1D8
	DWORD m_State;	// 1DC
	char m_StateSub;	// 1E0
	unsigned char m_Rest;	// 1E1
	char m_ViewState;	// 1E2
	int m_ViewSkillState;	// 1E4
	DWORD m_LastMoveTime;	// 1E8
	DWORD m_LastAttackTime;	// 1EC
	BYTE m_FriendServerOnline;	// 1F0
	int m_DetectSpeedHackTime;	// 1F4
	unsigned long m_SumLastAttackTime;	// 1F8
	unsigned long m_DetectCount;	// 1FC
	int m_DetectedHackKickCount;	// 200
	int m_SpeedHackPenalty;	// 204
	unsigned char m_AttackSpeedHackDetectedCount;	// 208
	unsigned long m_PacketCheckTime;	// 20C
	unsigned char m_ShopTime;	// 210
	unsigned long m_TotalAttackTime;	// 214
	int m_TotalAttackCount;	// 218
	unsigned long TeleportTime;	// 21C
	char Teleport;	// 220
	char KillerType;	// 221
	char DieRegen;	// 222
	char RegenOk;	// 223
	BYTE  RegenMapNumber;	// 224
	BYTE  RegenMapX;	// 225
	BYTE  RegenMapY;	// 226
	DWORD RegenTime;	// 228
	DWORD MaxRegenTime;	// 22C
	short m_PosNum;	// 230
	DWORD LifeRefillTimer;	// 234
	DWORD CurActionTime;	// 238
	DWORD NextActionTime;	// 23C
	DWORD DelayActionTime;	// 240
	char DelayLevel;	// 244
	char m_PoisonType;	// 245
	char m_IceType;	// 246
	char m_PoisonBeattackCount; // 247
	char m_ColdBeattackCount;	// 248
	char m_ImmuneToMagicCount;	// 249
	char m_ImmuneToHarmCount;	// 24A
	char m_iMonsterBattleDelay;	// 24B
	char m_cKalimaGateExist; // 24C
	int m_iKalimaGateIndex; // 250
	char m_cKalimaGateEnterCount;	// 254
	OBJECTSTRUCT * lpAttackObj;	// 258
	short m_SkillNumber;	// 25C
	DWORD m_SkillTime;	// 260
	bool m_bAttackerKilled;	// 264
	char m_ManaFillCount;	// 265
	char m_LifeFillCount;	// 266
	int SelfDefense[MAX_SELF_DEFENSE];	// 268
	DWORD SelfDefenseTime[MAX_SELF_DEFENSE];	// 27C
	DWORD MySelfDefenseTime;	// 290
	char m_Drink;	// 294
	int m_SkillDefense;	// 298
	char m_SkillDefenseTime;	// 29C
	int m_SkillAttack;	// 2A0
	char m_SkillAttackTime;	// 2A4
	int m_SkillAttack2;	// 2A8
	char m_SkillAttackTime2;	// 2AC
	int m_SkillAddLife;	// 2B0
	int m_SkillAddLifeTime;	// 2B4
	int m_SkillHarden;	// 2B8
	int m_SkillHardenTime;	// 2BC
	int m_SkillMagumReduceDefense;	// 2C0
	int m_SkillMagumReduceDefenseTime;	// 2C4
	int PartyNumber; // 2C8
	int PartyTargetUser;	// 2CC
	int GuildNumber;	// 2D0
	_GUILD_INFO_STRUCT * lpGuild;	// 2D4
	char GuildName[11]; // 2D8
	int GuildStatus;	// 2E4
	int iGuildUnionTimeStamp;	// 2E8
	int m_RecallMon;	// 2EC
	int m_Change;	// 2F0
	short TargetNumber;	// 2F4
	short TargetShopNumber;	// 2F6
	short ShopNumber;	// 2F8
	short LastAttackerID;	// 2FA
	int m_AttackDamageMin;	// 2FC
	int m_AttackDamageMax;	// 300
	int m_MagicDamageMin;	// 304
	int m_MagicDamageMax;	// 308
	int m_AttackDamageLeft;	// 30C
	int m_AttackDamageRight;	// 310
	int m_AttackDamageMaxLeft;	// 314
	int m_AttackDamageMinLeft;	// 318
	int m_AttackDamageMaxRight;	// 31C
	int m_AttackDamageMinRight;	// 320
	int m_AttackRating;	// 324
	int m_AttackSpeed;	// 328
	int m_MagicSpeed;	// 32C
	int m_Defense;	// 330
	int m_MagicDefense;	// 334
	int m_SuccessfulBlocking;	// 338
	short m_MoveSpeed;	// 33C
	short m_MoveRange;	// 33E
	short m_AttackRange;	// 340
	short m_AttackType;	// 342
	short m_ViewRange;	// 344
	short m_Attribute;	// 346
	short m_ItemRate;	// 348
	short m_MoneyRate;	// 34A
	int m_CriticalDamage;	// 34C
	int m_ExcelentDamage;	// 350
	CMagicInf * m_lpMagicBack;	// 354
	CMagicInf * Magic;	// 358
	char MagicCount;	// 35C
	unsigned char UseMagicNumber;	// 35D
	unsigned long UseMagicTime;	// 360
	char UseMagicCount;	// 364
	short OSAttackSerial;	// 366
	unsigned char SASCount;	// 368
	DWORD SkillAttackTime;	// 36C
	char CharSet[18]; 	// 370
	char m_Resistance[MAX_RESISTENCE_TYPE];	// 382
	char m_AddResistance[MAX_RESISTENCE_TYPE];	// 389
	int FrustrumX[MAX_ARRAY_FRUSTRUM];	// 390
	int FrustrumY[MAX_ARRAY_FRUSTRUM]; // 3A4
	VIEWPORT_STRUCT VpPlayer[MAX_VIEWPORT];	// 3B0
	VIEWPORT_PLAYER_STRUCT VpPlayer2[MAX_VIEWPORT];	// 734
	int VPCount; // AB8
	int VPCount2;	// ABC
	HITDAMAGE_STRUCT sHD[MAX_ST_HIT_DAMAGE];	// AC0
	short sHDCount;	// CA0
	tagInterfaceState m_IfState;	// CA4
	DWORD m_InterfaceTime;	// CA8
	CItem * pInventory; // CAC
	LPBYTE  pInventoryMap; // CB0
	char * pInventoryCount;	// CB4
	char pTransaction;	// CB8
	CItem * Inventory1;	//CBC
	LPBYTE  InventoryMap1;	// CC0
	char InventoryCount1;	// CC4
	CItem * Inventory2;	// CC8
	LPBYTE InventoryMap2;	// CCC
	char InventoryCount2;	// CD0
	CItem * Trade; // CD4
	LPBYTE TradeMap;	// unkCD8
	int TradeMoney;	// CDC
	bool TradeOk;	// CE0
	CItem * pWarehouse; // CE4
	LPBYTE pWarehouseMap; // CE8
	char WarehouseCount;	// CEC
	short WarehousePW; // CEE
	BYTE WarehouseLock;	// CF0
	BYTE WarehouseUnfailLock;	// CF1
	int WarehouseMoney;	// CF4
	int WarehouseSave;	// CF8
	CItem * pChaosBox;	// CFC
	LPBYTE pChaosBoxMap;	// D00
	int ChaosMoney;	// D04
	int ChaosSuccessRate;	// D08
	BOOL ChaosLock;	// D0C
	DWORD m_Option;	// D10
	int m_nEventScore;	// D14
	int m_nEventExp;	// D18
	int m_nEventMoney;	// D1C
	BYTE m_bDevilSquareIndex;	// D20
	bool m_bDevilSquareAuth;	// D21
	char m_cBloodCastleIndex;	// D22
	char m_cBloodCastleSubIndex;	// D23
	int m_iBloodCastleEXP;	// D24
	bool m_bBloodCastleComplete;	// D28
	char m_cChaosCastleIndex;	// D29
	char m_cChaosCastleSubIndex;	// D2A
	int m_iChaosCastleBlowTime;	// D2C
	char m_cKillUserCount;	// D30
	char m_cKillMonsterCount;	// D31
	int m_iDuelUserReserved;	// D34
	int m_iDuelUserRequested;	// D38
	int m_iDuelUser;	// D3C
	BYTE m_btDuelScore;	// D40
	int m_iDuelTickCount;	// D44
	bool m_bPShopOpen;	// D48
	bool m_bPShopTransaction;	// D49	
	bool m_bPShopItemChange;	// D4A
	bool m_bPShopRedrawAbs;	// D4B
	char m_szPShopText[36];		// D4C
	bool m_bPShopWantDeal;	// D70
	int m_iPShopDealerIndex;	// D74
	char m_szPShopDealerName[10];	// D78
	CRITICAL_SECTION m_critPShopTrade;	// D84
	int m_iVpPShopPlayer[MAX_VIEWPORT];	// D9C
	WORD m_wVpPShopPlayerCount;	// EC8
	bool IsInBattleGround;	// ECA
	bool HaveWeaponInHand;	// ECB
	short EventChipCount;	// ECC
	int MutoNumber;	// ED0
	BOOL UseEventServer;	// ED4
	bool LoadWareHouseInfo;	// ED8
	int iStoneCount;	// EDC
	//new
	int		m_i3rdQuestState;
	int		m_i3rdQuestIndex;
	MONSTERKILLINFO MonsterKillInfo[5];



	//end new
	int		m_iSoulBarrierDefense; //Season 3 BuffEffect for Soul Barrier Skill
	short	m_sSoulBarrierDuration; //Season 3 BuffEffect for Soul Barrier Skill

	BYTE m_Quest[50];	// EE0
	bool m_SendQuestInfo;	// F12
	int m_SkyBossMonSheildLinkIndex;	// F14
	int m_SkyBossMonSheild;	// F18
	int m_SkyBossMonSheildTime;	// F1C
	int m_MaxLifePower;	// F20
	int m_WizardSkillDefense;	// F24
	int m_WizardSkillDefenseTime;	// F28
	int m_PacketChecksumTime;	// F2C
	int m_CheckLifeTime;	// F30
	unsigned char m_MoveOtherServer;	// F34
	char BackName[11];	// F35
	char m_BossGoldDerconMapNumber;	// F40
	bool m_InWebzen;	// F41
	char m_LastTeleportTime;	// F42
	BYTE m_ClientHackLogCount;	// F43
	BOOL m_bIsInMonsterHerd;	// F44
	BOOL m_bIsMonsterAttackFirst;	// F48
	class MonsterHerd * m_lpMonsterHerd;	// F4C
	BYTE Summoner; //0x2108
	//CCSAuth2 NPggCSAuth;	// F50

	bool m_bSentGGAuth;	// F7C
	DWORD m_NPggCheckSumSendTime;	// F80
	int fSkillFrustrumX[MAX_ARRAY_FRUSTRUM];	// F84
	int fSkillFrustrumY[MAX_ARRAY_FRUSTRUM];	// F94
	BYTE SkillHellFire2State;	// FA4
	BYTE SkillHellFire2Count;	// FA5
	DWORD SkillHellFire2Time;	// FA8
	unsigned char m_ReqWarehouseOpen;	// FAC
	int m_NotAttackAreaCount;	// FB0
	short SetOpAddSkillAttack;	// FB4
	short SetOpAddExDamage;	// FB6
	short SetOpAddExDamageSuccessRate;	// FB8
	short SetOpAddCriticalDamage;	// FBA
	short SetOpAddCriticalDamageSuccessRate;	// FBC
	short SetOpIncAGValue;	// FBE
	short SetOpAddDamage;	// FC0
	short SetOpAddMinAttackDamage;	// FC2
	short SetOpAddMaxAttackDamage;	// FC4
	short SetOpAddAttackDamage;	// FC6
	short SetOpAddDefence;	// FC8
	short SetOpAddDefenceRate;	// FCA
	short SetOpAddMagicPower;	// FCC
	BYTE SetOpIgnoreDefense;	// FCE
	BYTE SetOpDoubleDamage;	// FCF
	BYTE SetOpTwoHandSwordImproveDamage;	// FD0
	BYTE SetOpImproveSuccessAttackRate;	// FD1
	BYTE SetOpReflectionDamage;	// FD2
	BYTE SetOpImproveSheldDefence;	// FD3
	BYTE SetOpDecreaseAG;	// FD4
	BYTE SetOpImproveItemDropRate;	// FD5
	bool IsFullSetItem;	// FD6
	TDurMagicKeyChecker DurMagicKeyChecker;	// FD8
	WORD SkillRecallParty_Time;	// 1104
	BYTE SkillRecallParty_MapNumber;	// 1106
	BYTE SkillRecallParty_X;	// 1107
	BYTE SkillRecallParty_Y;	// 1108
	WORD SkillAddCriticalDamageTime;	// 110A
	WORD SkillAddCriticalDamage;	// 110C
	bool bIsChaosMixCompleted;	// 110E
	bool SkillLongSpearChange;	// 110F
	CSkillDelay SkillDelay;	// 1110
	int iObjectSecTimer;	// 1514
	bool m_bMapSvrMoveQuit;	// 1518
	bool m_bMapSvrMoveReq;	// 1519
	DWORD m_dwMapSvrQuitTick;	// 151C
	short m_sPrevMapSvrCode;	// 1520
	short m_sDestMapNumber;	// 1522
	BYTE m_btDestX;	// 1524
	BYTE m_btDestY;	// 1525 
	union
	{
		struct
		{
			BYTE	m_btCsNpcExistVal1;
			BYTE	m_btCsNpcExistVal2;
			BYTE	m_btCsNpcExistVal3;
			BYTE	m_btCsNpcExistVal4;
		};
		int		m_iCsNpcExistVal;
	};

	BYTE	m_btCsNpcType;

	BYTE	m_btCsGateOpen;

	int		m_iCsGateLeverLinkIndex;

	BYTE	m_btCsNpcDfLevel;
	BYTE	m_btCsNpcRgLevel;

	BYTE	m_btCsJoinSide;
	bool	m_bCsGuildInvolved;
	
	bool m_bIsCastleNPCUpgradeCompleted;	// 1526
	BYTE m_btWeaponState;	// 1527
	int m_iWeaponUser;	// 1528
	BYTE m_btKillCount;	// 152C
	int m_iSkillStunTime;	// 1530
	int m_iSkillBrandOfSkillTime;	// 1534
	int m_iSkillInvisibleTime;	// 1538
	int m_iSkillManaSwellTime;	// 153C
	int m_iSkillManaSwell;	// 1540
	int m_iAccumulatedDamage;	// 1544
	int m_iPotionBlessTime;	// 1548
	int m_iPotionSoulTime;	// 154C 
/* this+0x1570, */unsigned char m_btLifeStoneCount;
/* this+0x1571, */unsigned char m_btCreationState;
/* this+0x1574, */int m_iCreatedActivationTime; 
	int m_iAccumulatedCrownAccessTime;	// 1550
	TMonsterSkillElementInfo m_MonsterSkillElementInfo;	// 1554
	int m_iBasicAI;	// 15A4
	int m_iCurrentAI;	// 15A8
	int m_iCurrentAIState;	// 15AC
	int m_iLastAIRunTime;	// 15B0
	int m_iGroupNumber;	// 15B4
	int m_iSubGroupNumber;	// 15B8
	int m_iGroupMemberGuid;	// 15BC
	int m_iRegenType;	// 15C0
	TMonsterAIAgro m_Agro;	// 15C4
	int m_iLastAutomataRuntime;	// 18E8
	int m_iLastAutomataDelay;	// 18EC
	int m_iCrywolfMVPScore;	// 18F0
	DWORD m_dwLastCheckTick;	// 18F4
	int m_iAutoRecuperationTime;	// 18F8
	int m_iSkillNPCHelpTime;	// 18FC
	int m_iSkillNPCDefense;	// 1900
	int m_iSkillNPCAttack;	// 1904
	int m_iMuseElfInfinityArrowSkillTime;	// 1908
	int m_iSkillDistanceErrorCount;	// 190C
	DWORD m_dwSkillDistanceErrorTick;	// 1910
	JEWELOFHARMONY_ITEM_EFFECT m_JewelOfHarmonyEffect;	// 1914
	ITEMOPTION_FOR380ITEM_EFFECT m_ItemOptionExFor380;	// 193A 
	BOOL m_bKanturuEntranceByNPC;	// 194C 
	WORD m_wItemEffectType;	// 1950
	int m_iItemEffectValidTime;	// 1954
	WORD m_wCashPoint;	// 1958
	int m_iPeriodItemEffectIndex;	// 195C
	WORD m_wExprienceRate;	// 1960
	WORD m_wItemDropRate;	// 1962
	BYTE m_btMoveMapBound;	// 1964
	int		m_iIllusionTempleIndex; //20FC
	BOOL	m_bSkillKeyRecv; //0x2100

	//PC Point System
	int PCPoint;

	WORD aFloodPostCmd;
	short   TempoRespownVault;
};

typedef OBJECTSTRUCT * LPOBJ;

#include "protocol.h"

//extern CViewportGuild ViewGuildMng;
extern OBJECTSTRUCT gObj[OBJMAX];

extern int gObjCSFlag;
extern int gItemLoop;
extern int gItemLoop2;
extern int gItemLoopMax;
extern int gObjTotalUser;
extern int gDisconnect; 
extern int gCurConnectUser; 
extern int skillSuccess;
extern int GuildInfoOfs;
extern int GuildInfoCount;
extern int GuilUserOfs;
extern int GuildUserCount;
extern int lOfsChange;
extern int ChangeCount; // 8bf8b44

extern int gObjCallMonCount;
extern int gObjMonCount;
extern int gObjCount;



void gObjCalCharacter(int aIndex);
void gObjSkillUseProcTime500(LPOBJ lpObj);
void MonsterAndMsgProc();
void MoveMonsterProc();
void gObjRefillProcess(int aIndex, LPOBJ lpObj);
void gObjInit();
void gObjEnd();
void gObjClearViewportOfMine(LPOBJ lpObj);
void gObjClearViewport(LPOBJ lpObj);
void gObjCloseSet(int aIndex, int Flag);
void gObjCharTradeClear(LPOBJ lpObj);
void gObjCharZeroSet(int aIndex);
int gObjGetSocket(SOCKET socket);
void gObjSetTradeOption(int aIndex, int option);
void gObjSetDuelOption(int aIndex, int option);
bool IsDuelEnable(int aIndex);
bool IsOnDuel(int aIndex1, int aIndex2);
int GetMapMoveLevel(LPOBJ lpObj, int mapnumber, int max_over);
void DbItemSetInByte(LPOBJ lpObj, struct SDHP_DBCHAR_INFORESULT* lpMsg, int ItemDbByte, bool* bAllItemExist);
void gObjSetBP(int aIndex);
int gObjSetCharacter(unsigned char* lpdata, int aIndex);
int gObjCanItemTouch(LPOBJ lpObj, int type);
void gObjMagicTextSave(LPOBJ lpObj);
void ItemIsBufExOption(unsigned char* buf, class CItem* lpItem);
void gObjStatTextSave(LPOBJ lpObj);
void gObjItemTextSave(LPOBJ lpObj);
void gObjWarehouseTextSave(LPOBJ lpObj);
void gObjAuthorityCodeSet(LPOBJ lpObj);
int gObjSetPosMonster(int aIndex, int PosTableNum);
int gObjSetMonster(int aIndex, int MonsterClass);
void gObjDestroy(SOCKET aSocket, int client);
short gObjAddSearch(unsigned int aSocket, char* ip);
short gObjAdd(SOCKET aSocket, char* ip, int aIndex);
short gObjMonsterRecall(int iMapNumber);
short gObjAddMonster(int iMapNumber);
short gObjAddCallMon();
void gObjUserKill(int aIndex);
void gObjAllLogOut();
void gObjAllDisconnect();
void gObjTradeSave(LPOBJ lpObj, int index);
short gObjMemFree(int index);
int gObjGameClose(int aIndex);
short gObjDel(int index);
short gObjSometimeClose(int index);
int gObjIsGamePlaing(LPOBJ lpObj);
int gObjIsConnectedGP(int aIndex, char* CharName);
int gObjIsConnectedGP(int aIndex);
int gObjIsConnected(LPOBJ lpObj, int dbnumber);
int gObjIsConnected(int aIndex);
int gObjIsConnected(LPOBJ lpObj);
int gObjIsAccontConnect(int aIndex, char* accountid);
int gObjJoominCheck(int aIndex, char* szInJN);
int gObjTaiwanJoominCheck(int aIndex, char* szInJN);
int gObjCheckXYMapTile(LPOBJ lpObj, int iDbgName);
int gObjSetAccountLogin(int aIndex, char* szId, int aUserNumber, int aDBNumber, char* JoominNumber);
int gObjGetUserNumber(int aIndex);
int gObjGetNumber(int aIndex, int& UN, int& DBN);
LPSTR gObjGetAccountId(int aIndex);
int gObjGetIndex(char* szId);
int gObjUserIdConnectCheck(char* szId, int index);
unsigned char GetPathPacketDirPos(int px, int py);
int gObjCalDistance(LPOBJ lpObj1, LPOBJ lpObj2);
int gObjPositionCheck(LPOBJ lpObj);
int gObjCheckTileArea(int aIndex, int x, int y, int dis);
int ExtentCheck(int x, int y, int w, int h);
void gObjSetInventory1Pointer(LPOBJ lpObj);
void gObjSetInventory2Pointer(LPOBJ lpObj);
void gObjAddMsgSend(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode);
void gObjAddMsgSendDelay(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode);
void gObjAddMsgSendDelayInSpecificQPos(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode, int iQPosition);
void gObjAddAttackProcMsgSendDelay(LPOBJ lpObj, int aMsgCode, int aIndex, int delay, int SubCode, int SubCode2);
void gObjMsgProc(LPOBJ lpObj);
void gObjStateProc(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode);
void gObjStateAttackProc(LPOBJ lpObj, int aMsgCode, int aIndex, int SubCode, int SubCode2);
int gObjBackSpring(LPOBJ lpObj, LPOBJ lpTargetObj);
int BackSpringCheck(int& x, int& y, int& dir, unsigned char map);
int gObjBackSpring2(LPOBJ lpObj, LPOBJ lpTargetObj, int count);
bool gObjLevelUp(LPOBJ lpObj, int addexp, int iMonsterType, int iEventType);
int gObjLevelUpPointAdd(unsigned char type, LPOBJ lpObj);
void gObjMonsterItemLoadScript(LPOBJ lpObj, char* script_file);
void gObjGiveItemSearch(LPOBJ lpObj, int maxlevel);
unsigned char gObjWarehouseInsertItem(LPOBJ lpObj, int type, int index, int level, int pos);
void gObjGiveItemWarehouseSearch(LPOBJ lpObj, int maxlevel);
int gObjGuildMasterCapacityTest(LPOBJ lpObj);
void gObjNextExpCal(LPOBJ lpObj);
int retResistance(LPOBJ lpObj, int Resistance_Type);
int retCalcSkillResistance(LPOBJ lpTargetObj, int isDouble);
int gObjAttackQ(LPOBJ lpObj);
void gObjPlayerKiller(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjUserDie(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjInterfaceTimeCheck(LPOBJ lpObj);
void gObjPkDownTimeCheck(LPOBJ lpObj, int TargetLevel);
int gObjAngelSprite(LPOBJ lpObj);
int gObjSatanSprite(LPOBJ lpObj);
int gObjWingSprite(LPOBJ lpObj);
int gObjUniriaSprite(LPOBJ lpObj);
void gObjSpriteDamage(LPOBJ lpObj, int damage);
void gObjSecondDurDown(LPOBJ lpObj);
void gObjChangeDurProc(LPOBJ lpObj);
void gObjWingDurProc(LPOBJ lpObj);
void gObjPenaltyDurDown(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjWeaponDurDown(LPOBJ lpObj, LPOBJ lpTargetObj, int type);
void gObjArmorRandomDurDown(LPOBJ lpObj, LPOBJ lpAttackObj);
bool gObjIsSelfDefense(LPOBJ lpObj, int aTargetIndex);
void gObjCheckSelfDefense(LPOBJ lpObj, int aTargetIndex);
void gObjTimeCheckSelfDefense(LPOBJ lpObj);
int gObjAttack(LPOBJ lpObj, LPOBJ lpTargetObj, class CMagicInf* lpMagic, int magicsend, unsigned char MSBFlag, int AttackDamage, BOOL bCombo);
void gObjMonsterExpDivision(LPOBJ lpMonObj, LPOBJ lpObj, int AttackDamage, int MSBFlag);
int gObjMonsterExpSingle(LPOBJ lpObj, LPOBJ lpTargetObj, int dmg, int tot_dmg, bool& bSendExp);
void gObjExpParty(LPOBJ lpObj, LPOBJ lpTargetObj, int AttackDamage, int MSBFlag);
void gObjMonsterDieLifePlus(LPOBJ lpObj, LPOBJ lpTartObj);
void gObjLifeCheck(LPOBJ lpTargetObj, LPOBJ lpObj, int AttackDamage, int DamageSendType, int MSBFlag, int MSBDamage, unsigned char Skill, int iShieldDamage);
int gObjInventoryTrans(int aIndex);
int gObjInventoryCommit(int aIndex);
int gObjInventoryRollback(int aIndex);
void gObjInventoryItemSet(int aIndex, int itempos, unsigned char set_byte);
void gObjInventoryItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
bool gObjFixInventoryPointer(int aIndex);
void gObjInventoryItemSet_PShop(int aIndex, int itempos, unsigned char set_byte);
void gObjInventoryItemBoxSet_PShop(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
BYTE gObjInventoryDeleteItem(int aIndex, int itempos);
BYTE gObjWarehouseDeleteItem(int aIndex, int itempos);
BYTE gObjChaosBoxDeleteItem(int aIndex, int itempos);
unsigned char gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
DWORD gGetItemNumber();
void gPlusItemNumber();
unsigned char gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
unsigned char gObjOnlyInventoryInsertItem(int aIndex, class CItem item);
unsigned char gObjInventoryInsertItem(LPOBJ lpObj, int type, int index, int level);
int gObjSearchItem(LPOBJ lpObj, int item_type, int add_dur, int nLevel);
int gObjSearchItemMinus(LPOBJ lpObj, int pos, int m_dur);
unsigned char gObjShopBuyInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int iSerial, int iDur);
unsigned char gObjShopBuyInventoryInsertItem(int aIndex, class CItem item);
unsigned char gObjInventoryInsertItemTemp(LPOBJ lpObj, class CMapItem* Item);
unsigned char gObjInventoryInsertItem(int aIndex, class CMapItem* item);
unsigned char gObjInventoryInsertItem(int aIndex, class CItem item);
unsigned char gObjMonsterInventoryInsertItem(LPOBJ lpObj, int type, int index, int level, int op1, int op2, int op3);
unsigned char gObjInventoryRectCheck(int aIndex, int sx, int sy, int width, int height);
unsigned char gObjOnlyInventoryRectCheck(int aIndex, int sx, int sy, int width, int height);
int CheckInventoryEmptySpace(LPOBJ lpObj, int iItemHeight, int iItemWidth);
int gObjIsItemPut(LPOBJ lpObj, class CItem* lpItem, int pos);
unsigned char gObjWerehouseRectCheck(int aIndex, int sx, int sy, int width, int height);
unsigned char gObjMapRectCheck(unsigned char* lpMapBuf, int sx, int sy, int ex, int ey, int width, int height);
void gObjWarehouseItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
void gObjWarehouseItemSet(int aIndex, int itempos, unsigned char set_byte);
void gObjChaosItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
void gObjChaosItemSet(int aIndex, int itempos, unsigned char set_byte);
unsigned char gObjChaosBoxInsertItemPos(int aIndex, class CItem item, int pos, int source);
unsigned char gObjWarehouseInsertItemPos(int aIndex, class CItem item, int pos, int source);
unsigned char gObjInventoryInsertItemPos(int aIndex, class CItem item, int pos, int RequestCheck);
int gObjInventorySearchSerialNumber(LPOBJ lpObj, unsigned long serial);
int gObjWarehouseSearchSerialNumber(LPOBJ lpObj, unsigned long sirial);
unsigned char gObjInventoryMoveItem(int aIndex, unsigned char source, unsigned char target, int& durSsend, int& durTsend, unsigned char sFlag, unsigned char tFlag, unsigned char* siteminfo);
unsigned char gObjTradeRectCheck(int aIndex, int sx, int sy, int width, int height);
int gObjTradeItemBoxSet(int aIndex, int itempos, int xl, int yl, unsigned char set_byte);
unsigned char gObjTradeInventoryMove(LPOBJ lpObj, unsigned char source, unsigned char target);
unsigned char gObjInventoryTradeMove(LPOBJ lpObj, unsigned char source, unsigned char target);
unsigned char gObjTradeTradeMove(LPOBJ lpObj, unsigned char source, unsigned char target);
void gObjTradeCancel(int aIndex);
void gObjTempInventoryItemBoxSet(unsigned char* TempMap, int itempos, int xl, int yl, unsigned char set_byte);
unsigned char gObjTempInventoryRectCheck(unsigned char* TempMap, int sx, int sy, int width, int height);
unsigned char gObjTempInventoryInsertItem(LPOBJ lpObj, class CItem item, unsigned char* TempMap);
int TradeItemInventoryPutTest(int aIndex);
int TradeitemInventoryPut(int aIndex);
void gObjTradeOkButton(int aIndex);
unsigned char LevelSmallConvert(int level);
unsigned char LevelSmallConvert(int aIndex, int inventoryindex);
void gObjAttackDamageCalc(int aIndex); 
void gObjMakePreviewCharSet(int aIndex);
void gObjViewportPaint(HWND hWnd, /*<regrel ebp+0xc>*/ /*|0x2|*/ short aIndex);
void InitFrustrum();
void CreateFrustrum(int x, int y, int aIndex);
bool TestFrustrum2(int x, int y, int aIndex);
int gObjCheckViewport(int aIndex, int x, int y);
void gObjViewportClose(LPOBJ lpObj);
void gObjViewportListCreate(short aIndex);
int ViewportAdd(int aIndex, int aAddIndex, int aType);
int ViewportAdd2(int aIndex, int aAddIndex, int aType);
void ViewportDel(short aIndex, int aDelIndex);
void Viewport2Del(short aIndex, int aDelIndex);
void gObjViewportAllDel(short aIndex);
void gObjViewportListDestroy(short aIndex);
void PShop_ViewportListRegenarate(short aIndex);
bool PShop_CheckInventoryEmpty(short aIndex);
void gObjStateSetCreate(int aIndex);
void gObjSetState();
void gObjSecondProc();
void gObjManaPotionFill(LPOBJ lpObj);
void gObjRestPotionFill(LPOBJ lpObj);
void gObjUseDrink(LPOBJ lpObj, int level);
int gObjCurMoveMake(unsigned char* const path, LPOBJ lpObj);
void gObjViewportListProtocolDestroy(LPOBJ lpObj);
void gObjViewportListProtocolCreate(LPOBJ lpObj);
void gObjViewportListProtocol(short aIndex);
void gObjSkillUseProc(LPOBJ lpObj);
void gObjSkillBeAttackProc(LPOBJ lpObj);
void gObjTeleportMagicUse(int aIndex, unsigned char x, unsigned char y);
int gObjMoveGate(int aIndex, int gt);
void gObjTeleport(int aIndex, int map, int x, int y);
void gObjMoveDataLoadingOK(int aIndex);
class CMagicInf* gObjGetMagic(LPOBJ lpObj, int mIndex);
class CMagicInf* gObjGetMagicSearch(LPOBJ lpObj, unsigned char skillnumber);
int gObjMagicManaUse(LPOBJ lpObj, class CMagicInf* lpMagic);
int gObjMagicBPUse(LPOBJ lpObj, class CMagicInf* lpMagic);
int gObjPosMagicAttack(LPOBJ lpObj, class CMagicInf* lpMagic, unsigned char x, unsigned char y);
void gObjMagicAddEnergyCheckOnOff(int flag);
int gObjMagicAdd(LPOBJ lpObj, unsigned char aSkill, unsigned char Level);
int gObjMagicDel(LPOBJ lpObj, unsigned char aSkill, unsigned char Level);
int gObjMagicAdd(LPOBJ lpObj, unsigned char Type, unsigned char Index, unsigned char Level, unsigned char& SkillNumber);
int gObjWeaponMagicAdd(LPOBJ lpObj, BYTE aSkill, BYTE Level);
int gObjMonsterMagicAdd(LPOBJ lpObj, BYTE aSkill, BYTE Level);
int gObjMagicEnergyCheck(LPOBJ lpObj, unsigned char aSkill);
int gObjItemLevelUp(LPOBJ lpObj, int source, int target);
int gObjItemRandomLevelUp(LPOBJ lpObj, int source, int target);
int gObjItemRandomOption3Up(LPOBJ lpObj, int source, int target);
void gObjAbilityReSet(LPOBJ lpObj);
int gObjTargetGuildWarCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjGuildWarEndSend(struct _GUILD_INFO_STRUCT* lpGuild1, struct _GUILD_INFO_STRUCT* lpGuild2, unsigned char Result1, unsigned char Result2);
void gObjGuildWarEndSend(LPOBJ lpObj, unsigned char Result1, unsigned char Result2);
void gObjGuildWarEnd(struct _GUILD_INFO_STRUCT* lpGuild, struct _GUILD_INFO_STRUCT* lpTargetGuild);
int gObjGuildWarProc(struct _GUILD_INFO_STRUCT* lpGuild1, struct _GUILD_INFO_STRUCT* lpGuild2, int score);
int gObjGuildWarCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjGuildWarMasterClose(LPOBJ lpObj);
int gObjGuildWarItemGive(struct _GUILD_INFO_STRUCT* lpWinGuild, struct _GUILD_INFO_STRUCT* lpLoseGuild);
int gObjGetPkTime(LPOBJ lpObj, int& hour, int& min);
int gObjMonsterCall(int aIndex, int MonsterType, int x, int y);
void gObjMonsterCallKill(int aIndex);
int gObjCheckTeleportArea(int aIndex, unsigned char x, unsigned char y);
int gObjCheckAttackAreaUsedPath(int aIndex, int TarObjIndex);
int gObjCheckattackAreaUsedViewPort(int aIndex, int TarObjIndex);
int gObjCheckAttackArea(int aIndex, int TarObjIndex);
int gUserFindDevilSquareInvitation(int aIndex);
int gUserFindDevilSquareKeyEyes(int aIndex);
void gObjSendUserStatistic(int aIndex, int startLevel, int endLevel);
LPOBJ gObjFind(char* targetcharname);
int gObjFind10EventChip(int aIndex);
int gObjDelete10EventChip(int aIndex);
void gObjSetPosition(int aIndex, int x, int y);
int gObjGetItemCountInEquipment(int aIndex, int itemtype, int itemindex, int itemlevel);
int gObjGetItemCountInIventory(int aIndex, int itemnum);
int gObjGetItemCountInIventory(int aIndex, int itemtype, int itemindex, int itemlevel);
int gObjGetManaItemPos(int aIndex);
void gObjDelteItemCountInInventory(int aIndex, int itemtype, int itemindex, int count);
void gObjGetStatPointState(int aIndex, short& AddPoint, short& MaxAddPoint, short& MinusPoint, short& MaxMinusPoint);
int gObjCheckStatPointUp(int aIndex);
int gObjCheckStatPointDown(int aIndex);
void gObjUseCircle(int aIndex, int pos);
void gObjUsePlusStatFruit(int aIndex, int pos);
void gObjUseMinusStatFruit(int aIndex, int pos);
void gObjCalcMaxLifePower(int aIndex);
void gObjDelayLifeCheck(int aIndex);
int gObjDuelCheck(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjDuelCheck(LPOBJ lpObj);
void gObjResetDuel(LPOBJ lpObj);
void gObjSendDuelEnd(LPOBJ lpObj);
void gObjCheckAllUserDuelStop();

//void gObjNProtectGGCheckSum(int aIndex);

void SkillFrustrum(unsigned char bangle, int aIndex);
int SkillTestFrustrum(int x, int y, int aIndex);
int gObjCheckMaxZen(int aIndex, int nAddZen);
void MakeRandomSetItem(int aIndex);
void MakeRewardSetItem(int aIndex, BYTE cDropX, BYTE cDropY, int iRewardType, int iMapnumber);
void gObjRecall(int aIndex, int mapnumber, int x, int y);
void gObjSetExpPetItem(int aIndex, int exp);
int gObjGetRandomItemDropLocation(int iMapNumber, BYTE& cX, BYTE& cY, int iRangeX, int iRangeY, int iLoopCount);
int gObjGetRandomFreeLocation(int iMapNumber, BYTE& cX, BYTE& cY, int iRangeX, int iRangeY, int iLoopCount);
int gObjCheckAttackTypeMagic(int iClass, int iSkill);
int gObjGetGuildUnionNumber(LPOBJ lpObj);
void gObjGetGuildUnionName(LPOBJ lpObj, char* szUnionName, int iUnionNameLen);
int gObjCheckRival(LPOBJ lpObj, LPOBJ lpTargetObj);
int gObjGetRelationShip(LPOBJ lpObj, LPOBJ lpTargetObj);
void gObjNotifyUpdateUnionV1(LPOBJ lpObj);
void gObjNotifyUpdateUnionV2(LPOBJ lpObj);
void gObjUnionUpdateProc(int aIndex);
void gObjSetKillCount(int aIndex, int iOption);
void gObjNotifyUseWeaponV1(LPOBJ lpOwnerObj, LPOBJ lpWeaponObj, int iTargetX, int iTargetY);
void gObjNotifyUseWeaponDamage(LPOBJ lpWeaponObj, int iTargetX, int iTargetY);
void gObjUseBlessAndSoulPotion(int aIndex, int iItemLevel);
void gObjWeaponDurDownInCastle(LPOBJ lpObj, LPOBJ lpTargetObj, int iDecValue);
void gObjReady4Relife(LPOBJ lpObj);
void gObjCheckTimeOutValue(LPOBJ lpObj, DWORD& rNowTick);
void MsgOutput(int aIndex, char* msg, ...);
void gProcessAutoRecuperation(LPOBJ lpObj);
void gObjShieldAutoRefill(LPOBJ lpObj);
int gObjCheckOverlapItemUsingDur(int iUserIndex, int iMaxOverlapped, int iItemType, int iItemLevel);
int gObjOverlapItemUsingDur(class CItem* lpItem, int iMapNumber, int iItemNumber, int iUserIndex, int iMaxOverlapped, int iItemType, int iItemLevel);
int gObjCheckSerial0ItemList(class CItem* lpItem);
int gObjCheckInventorySerial0Item(LPOBJ lpObj);
BOOL gCheckSkillDistance(int aIndex, int aTargetIndex, int iSkillNum);
void gObjSaveChaosBoxItemList(LPOBJ lpObj);
int gObjGetRandomFreeArea(int iMapNumber,unsigned char & cX,unsigned char & cY,int iSX,int iSY,int iDX,int iDY,int iLoopCount);

#endif