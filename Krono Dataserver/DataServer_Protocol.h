#pragma once

struct SDHP_PET_ITEMCREATERECV
{
    PBMSG_HEAD h;
    BYTE x;
    BYTE y;
    BYTE MapNumber;
    DWORD m_Number;
    short Type;
    BYTE Level;
    BYTE Dur;
    BYTE Op1;
    BYTE Op2;
    BYTE Op3;
    BYTE NewOption;
    int aIndex;
    short lootindex;
    BYTE SetOption;
};

struct SDHP_PET_ITEMCREATE
{
    PBMSG_HEAD h;
    BYTE x;
    BYTE y;
    BYTE MapNumber;
    short Type;
    BYTE Level;
    BYTE Dur;
    BYTE Op1;
    BYTE Op2;
    BYTE Op3;
    BYTE NewOption;
    int aIndex;
    short lootindex;
    BYTE SetOption;
};

struct SDHP_PROPERTY_ITEMRECV
{
    PBMSG_HEAD h;
    BYTE x;
    BYTE y;
    BYTE MapNumber;
    DWORD m_Number;
    short Type;
    BYTE Level;
    BYTE Dur;
    BYTE Op1;
    BYTE Op2;
    BYTE Op3;
    BYTE NewOption;
    int aIndex;
    short lootindex;
    BYTE SetOption;
    DWORD dwTime;
    WORD wRemainTime;
    WORD wLevel;
    WORD wLevel_T;
    char szName[10];
    char szName_T[10];
    BYTE btClass;
    BYTE btClass_T;
    WORD wItemIndex;
};

struct SDHP_PROPERTY_ITEMCREATE
{
    PBMSG_HEAD h;
    BYTE x;
    BYTE y;
    BYTE MapNumber;
    short Type;
    BYTE Level;
    BYTE Dur;
    BYTE Op1;
    BYTE Op2;
    BYTE Op3;
    BYTE NewOption;
    int aIndex;
    short lootindex;
    BYTE SetOption;
    DWORD dwTime;
    WORD wRemainTime;
    WORD wLevel;
    WORD wLevel_T;
    char szName[10];
    char szName_T[10];
    BYTE btClass;
    BYTE btClass_T;
    WORD wItemIndex;
};

struct SDHP_MACRODATA
{
    PWMSG_HEAD h;
    int aIndex;
    char AccountID[11];
    char Name[11];
    unsigned char btResult;
    unsigned char btMacroData[256];
};


struct PMSG_ANS_USERID
{
    PBMSG_HEAD2 head;
    DWORD dwKey;
    DWORD dwUserGUID;
    char chUserID[11];
    BYTE btResult;
};


struct SDHP_CHANGE_NAME_RESULT
{
    PBMSG_HEAD h;
    int aIndex;
    char AccountId[10];
    char OldName[10];
    char NewName[10];
    BYTE btResult;
};


struct SDHP_CHANGE_NAME
{
    PBMSG_HEAD h;
    int aIndex;
    char AccountId[10];
    char OldName[10];
    char NewName[10];
};



struct SDHP_CHARLISTCOUNT
{
    PWMSG_HEAD	h;
    short		Number;
    BYTE		Count;
    int			DbNumber;
    BYTE		Magumsa;
    char		AccountId[11];
    BYTE		MoveCnt;
#if (SEASON > 5)
    BYTE		ExtendedWarehouseCount;
#endif // SEASON >5
};


struct SDHP_CHARLIST
{
    BYTE Index;
    char Name[10];
    WORD Level;
    BYTE Class;
    BYTE CtlCode;
    BYTE dbInventory[48];
    BYTE DbVersion;
    BYTE btGuildStatus;
};


struct SDHP_CREATECHAR
{
    PBMSG_HEAD h;	// C1:04
    int UserNumber;	// 4
    int DBNumber;	// 8
    short Number;	// C
    char AccountId[10];	// E
    char Name[10];	// 18
    BYTE ClassSkin;	// 22
};


struct SDHP_CREATECHARRESULT
{
    PBMSG_HEAD h;	// C1:04
    unsigned char Result;	// 3
    short Number;	// 4
    char AccountId[10];	// 6
    char Name[10];	// 10
    BYTE Pos;	// 1A
    BYTE ClassSkin;	// 1B
    BYTE Equipment[24];	// 1C
    WORD Level;	// 34
};


struct SDHP_CHARDELETE
{
    PBMSG_HEAD h;	// C1:05
    short Number;	// 4
    char AccountID[10];	// 6
    char Name[10];	// 10
    BYTE Guild;	// [0:NoGuild] [1:Master] [2:Member] 1A
    char GuildName[8];	// 1B
};


struct SDHP_CHARDELETERESULT
{
    PBMSG_HEAD h;	// C1:05
    unsigned char Result;	// 3
    short Number;	// 4
    char AccountID[10];	// 6
};


struct SDHP_DBCHARINFOREQUEST
{
    PBMSG_HEAD h;	// C1:06
    char AccountID[11];	// 3
    char Name[11];	// E
    short Number;	// 1A
};


struct SDHP_DBCHAR_INFORESULT
{
    PWMSG_HEAD h;
    BYTE result;
    short Number;
    char AccountID[10];
    char Name[11];
    BYTE Class;
    short Level;
    int LevelUpPoint;
    int Exp;
    int NextExp;
    int Money;
    short Str;
    short Dex;
    short Vit;
    short Energy;
    WORD Life;
    WORD MaxLife;
    WORD Mana;
    WORD MaxMana;
#if(SEASON > 5)
    BYTE dbInventory[3776];
#else
    BYTE dbInventory[INVERTORY_SIZE];
#endif
    BYTE dbMagicList[MAGICLIST_SIZE];
    BYTE MapNumber;
    BYTE MapX;
    BYTE MapY;
    BYTE Dir;
    int PkCount;
    int PkLevel;
    int PkTime;
    BYTE CtlCode;
    BYTE DbVersion;
    BYTE AccountCtlCode;
    BYTE dbQuest[50];
    WORD Leadership;
    WORD ChatLitmitTime;
    int iFruitPoint;
#if(SEASON > 5)
    BYTE btExtendedInvenCount;
    BYTE btExtendedWarehouseCount;
    short sExGameServerCode;
#endif
};


struct SDHP_GETWAREHOUSEDB_SAVE
{
    PWMSG_HEAD	h;
    char		AccountID[10];
    short		aIndex;
    int			Money;
#if(SEASON > 5)
    BYTE		dbItems[3840];
#else
    BYTE		dbItems[1920];
#endif
    BYTE		DbVersion;
    short		pw;
};


struct SDHP_GETWAREHOUSEDB_RESULT
{
    PBMSG_HEAD h;
    char AccountID[10];	// 3
    short aIndex;	// E
};


struct SDHP_ITEMCREATERECV
{
    PBMSG_HEAD h;
    BYTE x;
    BYTE y;
    BYTE MapNumber;
    DWORD m_Number;
    short Type;
    BYTE Level;
    BYTE Dur;
    BYTE Op1;
    BYTE Op2;
    BYTE Op3;
    BYTE NewOption;
    int aIndex;
    short lootindex;
    BYTE SetOption;
    long lDuration;
    DWORD dwEventIndex;
};

#if (Season > 3)
struct SDHP_SKILLKEYDATA_SEND
{
    PBMSG_HEAD h;
    int aIndex;	// 4
    char Name[10];	// 8
    BYTE SkillKeyBuffer[20];	// 12
    BYTE GameOption;	// 1C
    BYTE QkeyDefine;	// 1D
    BYTE WkeyDefine;	// 1E
    BYTE EkeyDefine;	// 1F
    BYTE ChatWindow;	// 20
    BYTE RkeyDefine;	// 21
    int QWERLevel;	// 22
};
#else
struct SDHP_SKILLKEYDATA_SEND
{
    PBMSG_HEAD h;
    int aIndex;     // 4
    char Name[10];  // 8
    BYTE SkillKeyBuffer[10];        // 12
    BYTE GameOption;        // 1C
    BYTE QkeyDefine;        // 1D
    BYTE WkeyDefine;        // 1E
    BYTE EkeyDefine;        // 1F
    BYTE ChatWindow;        // 20
};
#endif

struct SDHP_CHARACTER_TRANSFER_RESULT
{
    PBMSG_HEAD h;
    char Account[10];	// 3
    short Number;	// E
    unsigned char Result;	// 10
};


struct PMSG_CHARLISTCOUNT
{
    /*FOR NEW JAPAN CLIENTS!!! [Researched By: Gembrid]*/
    struct PBMSG_HEAD h;
    unsigned char subcode;
    unsigned char MaxClass;
    unsigned char MoveCnt;
    unsigned char Count;

    char _new_data_for_new_login_system[0x11];
};


struct PMSG_CHARLIST
{
    BYTE Index;			// 0
    char Name[10];		// 1
    WORD Level;			// C
    BYTE CtlCode;		// E
    BYTE CharSet[18];	// F
    BYTE btGuildStatus;	// 21
};


struct SDHP_GETCHARLIST
{
    PBMSG_HEAD h;	// C1:01
    char Id[10];	// 3
    short Number;	// E
};


struct SDHP_DBCHAR_INFOSAVE
{
    PWMSG_HEAD h;
    char Name[11];
    short Level;
    BYTE Class;
    int LevelUpPoint;
    int Exp;
    int NextExp;
    int Money;
    short Str;
    short Dex;
    short Vit;
    short Energy;
    WORD Life;
    WORD MaxLife;
    WORD Mana;
    WORD MaxMana;
#if(SEASON > 5)
    BYTE dbInventory[3776];
#else
    BYTE dbInventory[INVERTORY_SIZE];
#endif
    BYTE dbMagicList[MAGICLIST_SIZE];
    BYTE MapNumber;
    BYTE MapX;
    BYTE MapY;
    BYTE Dir;
    int PkCount;
    int PkLevel;
    int PkTime;
    BYTE dbQuest[50];
    BYTE CharInfoSave;
    WORD Leadership;
    WORD ChatLitmitTime;
    int iFruitPoint;
#if(SEASON > 5)
    BYTE btExtendedInvenCount;
    BYTE btExtendedWarehouseCount;
    short sExGameServerCode;
#endif
};


struct SDHP_GETWAREHOUSEDB
{
    PBMSG_HEAD	h;	// C1:08
    char		AccountID[10];	// 3
    short		aIndex;	// E
};


struct SDHP_GETQUESTMONSTER_KILL
{
    struct PBMSG_HEAD	h;
    int					aIndex;
    char				Name[10];
    UCHAR				Result;
};


struct SDHP_DBQUEST_KILLSAVE
{
    /*<thisrel this+0x0>*/ /*|0x4|*/ struct PBMSG_HEAD h;
    /*<thisrel this+0x4>*/ /*|0x4|*/ int aIndex;
    /*<thisrel this+0x8>*/ /*|0xa|*/ char Name[10];
    /*<thisrel this+0x12>*/ /*|0x2|*/ char filler[2];
    /*<thisrel this+0x14>*/ /*|0x4|*/ int QuestDBIndex;
    /*<thisrel this+0x18>*/ /*|0x4|*/ int QuestMonsterIndex1;
    /*<thisrel this+0x1c>*/ /*|0x4|*/ int QuestMonsterKillCount1;
    /*<thisrel this+0x20>*/ /*|0x4|*/ int QuestMonsterIndex2;
    /*<thisrel this+0x24>*/ /*|0x4|*/ int QuestMonsterKillCount2;
    /*<thisrel this+0x28>*/ /*|0x4|*/ int QuestMonsterIndex3;
    /*<thisrel this+0x2c>*/ /*|0x4|*/ int QuestMonsterKillCount3;
    /*<thisrel this+0x30>*/ /*|0x4|*/ int QuestMonsterIndex4;
    /*<thisrel this+0x34>*/ /*|0x4|*/ int QuestMonsterKillCount4;
    /*<thisrel this+0x38>*/ /*|0x4|*/ int QuestMonsterIndex5;
    /*<thisrel this+0x3c>*/ /*|0x4|*/ int QuestMonsterKillCount5;
};


struct SDHP_DBCHAR_ITEMSAVE
{
    PWMSG_HEAD h;	// C2:11
    char Name[10];	// 4
#if(SEASON > 5)
    BYTE dbInventory[3776];	// E
#else
    BYTE dbInventory[INVERTORY_SIZE];	// E
#endif
};


struct SDHP_WAREHOUSEMONEY_SAVE
{
    PBMSG_HEAD h;	// C1:12
    char AccountID[10];	// 3
    short aIndex;	// E
    int Money;	// 10
};


struct SDHP_ITEMCREATE
{
    PBMSG_HEAD	h;
    BYTE		x;
    BYTE		y;
    BYTE		MapNumber;
    short		Type;
    BYTE		Level;
    BYTE		Dur;
    BYTE		Op1;
    BYTE		Op2;
    BYTE		Op3;
    BYTE		NewOption;
    int			aIndex;
    short		lootindex;
    BYTE		SetOption;
    long		lDuration;
    DWORD		dwEventIndex;
};


struct SDHP_ITEMMOVESAVE
{
    PBMSG_HEAD h;	// C1:53
    DWORD Serial;	// 4
    char ServerName[20];	// 8
    char Account[10];	// 1C
    char Name[10];	// 26
    char ItemName[21];	// 30
    BYTE X;	// 45
    BYTE Y;	// 46
    BYTE ItemLevel;	// 47
    BYTE ItemOp1;	// 48
    BYTE ItemOp2;	// 49
    BYTE ItemOp3;	// 4A
};

#if(SEASON > 3)
struct SDHP_SKILLKEYDATA
{
    PBMSG_HEAD h;
    char Name[10];
    BYTE SkillKeyBuffer[20];
    BYTE GameOption;
    BYTE QkeyDefine;
    BYTE WkeyDefine;
    BYTE EkeyDefine;
    BYTE ChatWindow;
    BYTE RkeyDefine;
    int QWERLevel;
};
#else
struct SDHP_SKILLKEYDATA
{
    PBMSG_HEAD h;
    char Name[10];  // 8
    BYTE SkillKeyBuffer[10];        // 12
    BYTE GameOption;        // 1C
    BYTE QkeyDefine;        // 1D
    BYTE WkeyDefine;        // 1E
    BYTE EkeyDefine;        // 1F
    BYTE ChatWindow;        // 20
};
#endif

struct Request_PetItem_Info
{
    BYTE nPos;	// 0
    int nSerial;	// 4
};


struct SDHP_REQUEST_PETITEM_INFO
{
    PWMSG_HEAD h;	// C2:56
    char AccountID[11];	// 4
    WORD Number;	// 10
    BYTE InvenType;	// 12
    BYTE nCount;	// 13
};


struct Recv_PetItem_Info
{
    BYTE nPos;	// 0
    int nSerial;	// 4
    BYTE Level;	// 8
    int Exp;	// C
};


struct SDHP_RECV_PETITEM_INFO
{
    PWMSG_HEAD h;
    char AccountID[11];	// 4
    WORD Number;	// 10
    BYTE InvenType;	// 12
    BYTE nCount;	// 13
};


struct Save_PetItem_Info
{
    int nSerial;	// 0
    BYTE Level;	// 3
    int Exp;	// 8
};


struct SDHP_SAVE_PETITEM_INFO
{
    PWMSG_HEAD h;
    BYTE nCount;	// 4
};

struct CSP_ANS_CASTLEDATA
{
    PBMSG_HEAD2 h;
    int iResult;
    WORD wMapSvrNum;
    WORD wStartYear;
    BYTE btStartMonth;
    BYTE btStartDay;
    WORD wEndYear;
    BYTE btEndMonth;
    BYTE btEndDay;
    BYTE btIsSiegeGuildList;
    BYTE btIsSiegeEnded;
    BYTE btIsCastleOccupied;
    char szCastleOwnGuild[8];
    __int64 i64CastleMoney;
    int iTaxRateChaos;
    int iTaxRateStore;
    int iTaxHuntZone;
    int iFirstCreate;
};

struct CSP_REQ_CASTLEDATA
{
    PBMSG_HEAD2 h;	// C1:80:00
    WORD wMapSvrNum;	// 4
    int iCastleEventCycle;	// 8
};

struct CASTLE_DATA
{
    WORD wStartYear;
    BYTE btStartMonth;
    BYTE btStartDay;
    WORD wEndYear;
    BYTE btEndMonth;
    BYTE btEndDay;
    BYTE btIsSiegeGuildList;
    BYTE btIsSiegeEnded;
    BYTE btIsCastleOccupied;
    char szCastleOwnGuild[9];
    __int64 i64CastleMoney;
    int iTaxRateChaos;
    int iTaxRateStore;
    int iTaxHuntZone;
    int iFirstCreate;
};


struct CSP_REQ_OWNERGUILDMASTER
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
};


struct CSP_REQ_NPCBUY
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    int iNpcNumber;	// C
    int iNpcIndex;	// 10
    int iNpcDfLevel;	// 14
    int iNpcRgLevel;	// 18
    int iNpcMaxHp;	// 1C
    int iNpcHp;	// 20
    BYTE btNpcX;	// 24
    BYTE btNpcY;	// 25
    BYTE btNpcDIR;	// 26
    int iBuyCost;	// 28
};


struct CSP_REQ_NPCREPAIR
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    int iNpcNumber;	// C
    int iNpcIndex;	// 10
    int iRepairCost;	// 14
};


struct CSP_REQ_NPCUPGRADE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    int iNpcNumber;	// C
    int iNpcIndex;	// 10
    int iNpcUpType;	// 14
    int iNpcUpValue;	// 18
    int iNpcUpIndex;	// 1C
};


struct CSP_REQ_TAXINFO
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 3
    int iIndex;	// 8
};


struct CSP_REQ_TAXRATECHANGE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    int iTaxKind;	// C
    int iTaxRate;	// 10
};


struct CSP_REQ_MONEYCHANGE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    int iMoneyChanged;	// C
};


struct CSP_REQ_SDEDCHANGE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    WORD wStartYear;	// C
    BYTE btStartMonth;	// E
    BYTE btStartDay;	// F
    WORD wEndYear;	// 10
    BYTE btEndMonth;	// 12
    BYTE btEndDay;	// 13
};


struct CSP_REQ_GUILDREGINFO
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    char szGuildName[8];	// C
};


struct CSP_REQ_SIEGEENDCHANGE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    BOOL bIsSiegeEnded;	// 8
};


struct CSP_REQ_CASTLEOWNERCHANGE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    BOOL bIsCastleOccupied;	// 8
    char szOwnerGuildName[8];	// C
};


struct CSP_REQ_REGATTACKGUILD
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    char szEnemyGuildName[8];	// C
};


struct CSP_REQ_CASTLESIEGEEND
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
};


struct CSP_REQ_MAPSVRMULTICAST
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    char szMsgText[128];	// 6
};


struct CSP_REQ_GUILDREGMARK
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    char szGuildName[8];	// C
    int iItemPos;	// 14
};


struct CSP_REQ_GUILDRESETMARK
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    char szGuildName[8];	// C
};


struct CSP_REQ_GUILDSETGIVEUP
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
    char szGuildName[8];	// C
    BOOL bIsGiveUp;	// 14
};


struct CSP_REQ_NPCREMOVE
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iNpcNumber;	// 8
    int iNpcIndex;	// C
};


struct CSP_REQ_CASTLESTATESYNC
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iCastleState;	// 8
    int iTaxRateChaos;	// C
    int iTaxRateStore;	// 10
    int iTaxHuntZone;	// 14
    char szOwnerGuildName[8];	// 18
};


struct CSP_REQ_CASTLETRIBUTEMONEY
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iCastleTributeMoney;	// 8
};



struct CSP_REQ_RESETCASTLETAXINFO
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
};


struct CSP_REQ_RESETSIEGEGUILDINFO
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
};


struct CSP_REQ_RESETREGSIEGEINFO
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 2
};


struct CSP_REQ_CSINITDATA
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
    int iCastleEventCycle;	// 8
};


struct CSP_REQ_NPCDATA
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
};


struct CSP_REQ_ALLGUILDREGINFO
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
    int iIndex;	// 8
};


struct CSP_REQ_CALCREGGUILDLIST
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
};


struct CSP_REQ_CSLOADTOTALGUILDINFO
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
};


struct CSP_ANS_MAPSVRMULTICAST
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    char szMsgText[128];	// 6
};


struct CSP_ANS_CASTLESTATESYNC
{
    PBMSG_HEAD2 h;
    WORD wMapSvrNum;	// 4
    int iCastleState;	// 8
    int iTaxRateChaos;	// C
    int iTaxRateStore;	// 10
    int iTaxHuntZone;	// 14
    char szOwnerGuildName[8];	// 18
};


struct CSP_ANS_CASTLETRIBUTEMONEY
{
    PBMSG_HEAD2 h;
    int iResult;	// 4
    WORD wMapSvrNum;	// 8
};


struct CWP_REQ_CRYWOLFSYNC
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
    int iCrywolfState;	// 8
    int iOccupationState;	// C
};


struct CWP_ANS_CRYWOLFSYNC
{
    PBMSG_HEAD h;
    BYTE btResult;	// 3
    int iCrywolfState;	// 4
    int iOccupationState;	// 8
};


struct CWP_REQ_CRYWOLFINFOLOAD
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
};


struct CWP_ANS_CRYWOLFINFOLOAD
{
    PBMSG_HEAD h;
    BYTE btResult;	// 3
    int iCrywolfState;	// 4
    int iOccupationState;	// 8
};


struct CWP_REQ_CRYWOLFINFOSAVE
{
    PBMSG_HEAD h;
    WORD wMapSvrNum;	// 4
    int iCrywolfState;	// 8
    int iOccupationState;	// C
};


struct CWP_ANS_CRYWOLFINFOSAVE
{
    PBMSG_HEAD h;
    BYTE btResult;	// 3
};


struct SDHP_CHARACTER_TRANSFER
{
    PBMSG_HEAD h;	// C1:CF
    char Account[10];	// 3
    short Number;	// E
};



struct CSP_REQ_NPCSAVEDATA
{
    PWMSG_HEAD h;	// C1:84
    unsigned short wMapSvrNum;	// 4
    int iCount;	// 8
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


struct CSP_ANS_OWNERGUILDMASTER
{
    PBMSG_HEAD2 h; // C1:80:1
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szCastleOwnGuild[0x8];	// 10
    char szCastleOwnGuildMaster[0xA];	// 18
};


struct CSP_ANS_NPCBUY
{
    PBMSG_HEAD2 h;	// C1:80:03
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    int iNpcNumber;	// 10
    int iNpcIndex;	// 14
    int iBuyCost;	// 18
};


struct CSP_ANS_NPCREPAIR
{
    PBMSG_HEAD2 h;	// C1:80:04
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    int iNpcNumber;	// 10
    int iNpcIndex;	// 14
    int iNpcMaxHp;	// 18
    int iNpcHp;	// 1C
    int iRepairCost;	// 20
};


struct CSP_ANS_NPCUPGRADE
{
    PBMSG_HEAD2 h;	// C1:80:05
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    int iNpcNumber;	// 10
    int iNpcIndex;	// 14
    int iNpcUpType;	// 18
    int iNpcUpValue;	// 1C
    int iNpcUpIndex;	// 20
};


struct CSP_ANS_TAXINFO
{
    PBMSG_HEAD2 h;	// C1:80:06
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    __int64 i64CastleMoney;	// 10
    int iTaxRateChaos;	// 18
    int iTaxRateStore;	// 1C
    int iTaxHuntZone;	// 20
};


struct CSP_ANS_TAXRATECHANGE
{
    PBMSG_HEAD2 h;	// C1:80:07
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    int iTaxKind;	// 10
    int iTaxRate;	// 14
};


struct CSP_ANS_MONEYCHANGE
{
    PBMSG_HEAD2 h;	// C1:80:08
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    int iMoneyChanged;	// 10
    __int64 i64CastleMoney;	// 18
};


struct CSP_ANS_SDEDCHANGE
{
    PBMSG_HEAD2 h;	// C1:80:09
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    unsigned short wStartYear;	// 10
    unsigned char btStartMonth;	// 12
    unsigned char btStartDay;	// 13
    unsigned short wEndYear;	// 14
    unsigned char btEndMonth;	// 16
    char btEndDay;	// 17
};


struct CSP_ANS_GUILDREGINFO
{
    PBMSG_HEAD2 h;	// C1:80:0A
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szGuildName[0x8];	// 10
    int iRegMarkCount;	// 18
    bool bIsGiveUp;
    BYTE btRegRank;
};


struct CSP_ANS_SIEGEENDCHANGE
{
    PBMSG_HEAD2 h;	// C1:80:0B
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int bIsSiegeEnded;	// C
};


struct CSP_ANS_CASTLEOWNERCHANGE
{
    PBMSG_HEAD2 h;	// C1:80:0C
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int bIsCastleOccupied;	// C
    char szOwnerGuildName[0x8];	// 10
};


struct CSP_ANS_REGATTACKGUILD
{
    PBMSG_HEAD2 h;	// C1:80:0D
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szEnemyGuildName[0x8];	// 10
};


struct CSP_ANS_CASTLESIEGEEND
{
    PBMSG_HEAD2 h;	// C1:80:0E
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_GUILDREGMARK
{
    PBMSG_HEAD2 h;	// C1:80:10
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szGuildName[0x8];	// 10
    int iItemPos;	// 18
    int iRegMarkCount;	// 1C
};


struct CSP_ANS_GUILDRESETMARK
{
    PBMSG_HEAD2 h;	// C1:80:11
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szGuildName[0x8];	// 10
    int iRegMarkCount;	// 18
};


struct CSP_ANS_GUILDSETGIVEUP
{
    PBMSG_HEAD2 h;	// C1:80:12
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iIndex;	// C
    char szGuildName[0x8];	// 10
    int bIsGiveUp;	// 18
    int iRegMarkCount;	// 1C
};


struct CSP_ANS_NPCREMOVE
{
    PBMSG_HEAD2 h;	// C1:80:16
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iNpcNumber;	// C
    int iNpcIndex;	// 10
};


struct CSP_ANS_RESETCASTLETAXINFO
{
    PBMSG_HEAD2 h;	// C1:80:19
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_RESETSIEGEGUILDINFO
{
    PBMSG_HEAD2 h;	// C1:80:1A
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_RESETREGSIEGEINFO
{
    PBMSG_HEAD2 h;	// C1:80:1B
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_ALLGUILDREGINFO
{
    struct PWMSG_HEAD h;	// C2:83
    int iResult;	// 4
    WORD wMapSvrNum;	// 8
    int iIndex;	// C
    int iCount;	// 10
};


struct CSP_GUILDREGINFO
{
    char szGuildName[8];	// 0
    int iRegMarkCount;	// 8
    bool bIsGiveUp;	// C
    BYTE btRegRank;	// D
};


struct CSP_NPCSAVEDATA
{
    int iNpcNumber;	// 0
    int iNpcIndex;	// 4
    int iNpcDfLevel;	// 8
    int iNpcRgLevel;	// C
    int iNpcMaxHp;	// 10
    int iNpcHp;	// 14
    BYTE btNpcX;	// 18
    BYTE btNpcY;	// 19
    BYTE btNpcDIR;	// 1A
};


struct CSP_ANS_NPCSAVEDATA
{
    PBMSG_HEAD h;	// C1:84
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
};


struct CSP_ANS_CALCREGGUILDLIST
{
    PWMSG_HEAD h;	// C1:85
    int iResult;	// 4
    WORD wMapSvrNum;	// 8
    int iCount;	// C
};


struct CSP_CALCREGGUILDLIST
{
    char szGuildName[8];	// 0
    int iRegMarkCount;	// 8
    int iGuildMemberCount;	// C
    int iGuildMasterLevel;	// 10
    int iSeqNum;	// 14
};


struct CSP_REQ_CSGUILDUNIONINFO
{
    PWMSG_HEAD h;	// C2:86
    unsigned short wMapSvrNum;	// 4
    int iCount;	// 8
};


struct CSP_CSGUILDUNIONINFO
{
    char szGuildName[8];	// 0
    int iCsGuildID;	// 8
};


struct CSP_ANS_CSGUILDUNIONINFO
{
    PWMSG_HEAD h;	// C2:86
    int iResult;	// 4
    WORD wMapSvrNum;	// 8
    int iCount;	// C
};


struct CSP_CSSAVETOTALGUILDINFO
{
    char szGuildName[0x8];	// 0
    int iCsGuildID;	// 8
    int iGuildInvolved;	// C
    int iGuildScore;
};


struct CSP_REQ_CSSAVETOTALGUILDINFO
{
    PWMSG_HEAD h;	// C2:87
    unsigned short wMapSvrNum;	// 4
    int iCount;	// 8
};


struct CSP_ANS_CSSAVETOTALGUILDINFO
{
    PBMSG_HEAD h;	// C1:87
    int iResult;	// 4
    WORD wMapSvrNum;	// 8
};


struct CSP_ANS_CSLOADTOTALGUILDINFO
{
    PWMSG_HEAD h;	// C2:88
    int iResult;	// 4
    unsigned short wMapSvrNum;	// 8
    int iCount;	// C
};


struct CSP_CSLOADTOTALGUILDINFO
{
    char szGuildName[8];	// 0
    int iCsGuildID;	// 8
    int iGuildInvolved;	// C
    int iGuildScore;
};


struct CSP_REQ_NPCUPDATEDATA
{
    PWMSG_HEAD h;	// C2:89
    WORD wMapSvrNum;	// 4
    int iCount;	// 8
};


struct CSP_NPCUPDATEDATA
{
    int iNpcNumber;	// 0
    int iNpcIndex;	// 4
    int iNpcDfLevel;	// 8
    int iNpcRgLevel;	// C
    int iNpcMaxHp;	// 10
    int iNpcHp;	// 14
    unsigned char btNpcX;	// 18
    unsigned char btNpcY;	// 19
    unsigned char btNpcDIR;	// 1A
};


struct CSP_ANS_NPCUPDATEDATA
{
    PBMSG_HEAD h;
    int iResult;
    unsigned short wMapSvrNum;
};


struct PMSG_REQ_ML_INFO_LOAD
{
    PBMSG_HEAD h;
    int iUserIndex;
    char chCharacterName[11];
};


struct PMSG_ANS_ML_INFO_LOAD
{
    PBMSG_HEAD h;
    BYTE Result; //3
    int Index; //4
    char szName[11];
    short MLevel; //14
    __int64 MLExp; //
    __int64 MLNextExp; //
    short MLPoint; //28 Should be int not short
};


struct PMSG_REQ_ML_INFO_SAVE
{
    PBMSG_HEAD h;
    char chCharacterName[11];
    short MLevel;
    __int64 MLExp;
    __int64 MLNextExp;
    short MLPoint; //Should be int not short
};


struct PMSG_REQ_PERIODITEM_INQUIRY
{
    PBMSG_HEAD2 h;	// C1:D0:01
    int iUserIndex;		// 4
    int iUserGuid;		// 8
};


struct PMSG_ANS_PERIODITEM_INSERT
{
    PBMSG_HEAD2 h;
    int iUserIndex;	// 4
    int iItemCode;	// 8
    int iItemPeriodDate;	// C
    BYTE btItemEffectType1;	// 10
    BYTE btItemEffectType2;	// 11
    BYTE btResult;	// 12
};


struct PMSG_REQ_PERIODITEM_INSERT
{
    PBMSG_HEAD2 h;	// C1:D0:03
    int iUserIndex;	// 4
    int iUserGuid;	// 8
    int iItemCode;	// C
    int iItemPeriodDate;	// 10
    BYTE btItemEffectType1;	// 14
    BYTE btItemEffectType2;	// 15
    char chUserID[11];	// 16
    char chExpireDate[20];	//21
    BYTE btOptionType;//DiG fix
};


struct PMSG_ANS_PERIODITEM_DELETE
{
    PBMSG_HEAD2 h;
    int iUserIndex;	// 4
    int iUserGuid;	// 8
    BYTE btResult;	// C
};


struct PMSG_REQ_PERIODITEM_DELETE
{
    PBMSG_HEAD2 h;	// C1:D0:09
    int iUserIndex;	// 4
    int iUserGuid;	// 8
    char chCharacterName[11];	// C
};


struct PMSG_ANS_PERIODITEM_UPDATE
{
    PBMSG_HEAD2 h;
    int iUserIndex;	// 4
    int iItemCode;	// 8
    BYTE btResult;	// C
};


struct PMSG_REQ_PERIODITEM_UPDATE
{
    PBMSG_HEAD2 h;	// C1:D0:07
    int iUserIndex;	// 4
    int iUserGuid;	// 8
    int iItemCode;	// C
    int iUsedTime;	// 10
    int iLeftTime;	// 14
    char chCharacterName[11];	// 18
};


struct PMSG_ANS_PERIODITEM_DATA
{
    BYTE btInUse;					// 10
    int iItemCode;					// 14
    BYTE btOptionType;				// 18
    BYTE btEffectType1;				// 19
    BYTE btEffectType2;				// 1A
    int iItemPeriodUsedTime;		// 20
    UINT iItemPeriodLeftTime;		// 24
};


struct PMSG_ANS_PERIODITEM_LIST//DiG FiX
{
    PBMSG_HEAD2 h;	//  0
    int iUserIndex;		//  4
    int iUserGuid;		//  8
    BYTE btCountItems;	//  C
    char btResult;		//  D
    PMSG_ANS_PERIODITEM_DATA	m_ListItem[10];//10
};


struct SDHP_ANS_ACCOUNTINFO
{
    PBMSG_HEAD h;
    char AccountId[11];
    short Number;
    BYTE Result;
    BYTE bSummoner;
};


struct PMSG_REQ_PERIODITEM_LIST
{
    PBMSG_HEAD2 h;	// C1:D0:05
    int iUserIndex;	// 4
    int iUserGuid;	// 8
    char chCharacterName[11];	// C
};


struct PMSG_REQ_SUMMONER_CREATE
{
    PBMSG_HEAD h;
    char szAccountID[11];
    short aIndex;
};


struct PMSG_ANS_SUMMONER_CREATE
{
    PBMSG_HEAD h;
    char szAccountID[11];
    short aIndex;
    BYTE btResult;
};


struct SDHP_USERCLOSE
{
    PBMSG_HEAD h;
    char CharName[10];
    char GuildName[8];
    BYTE Type;
};


struct CSP_ANS_NPCDATA
{
    PWMSG_HEAD h;
    int iResult;
    WORD wMapSvrNum;
    int iIndex;
    int iCount;
};


struct CSP_NPCDATA
{
    int iNpcNumber;
    int iNpcIndex;
    int iNpcDfLevel;
    int iNpcRgLevel;
    int iNpcMaxHp;
    int iNpcHp;
    BYTE btNpcX;
    BYTE btNpcY;
    BYTE btNpcDIR;
};


struct SDHP_LOAD_MEDALINFO
{
    PBMSG_HEAD h;
    WORD wIndex;
    DWORD dwItemSerial;
    WORD wItemIndex;
};


struct SDHP_GAMESERVERINFO
{
    PBMSG_HEAD h;
    DWORD ItemCount;
};


struct SDHP_LOAD_MEDALINFO_RESULT
{
    PBMSG_HEAD h;
    WORD wIndex;
    DWORD dwItemSerial;
    DWORD dwTime;
    WORD wRemainTime;
    WORD wLevel;
    WORD wLevel_T;
    char szName[10];
    char szName_T[10];
    BYTE btClass;
    BYTE btClass_T;
    WORD wItemIndex;
};

struct SDHP_DELETE_TEMPUSERINFO_RESULT
{
    PBMSG_HEAD h;
    char CharName[10];
};

struct SDHP_DELETE_TEMPUSERINFO
{
    PBMSG_HEAD h;
    unsigned short ServerCode;
    char CharName[10];
};

struct SDHP_SETGMEVENT
{
    PBMSG_HEAD h;
    char CharName[10];
};

struct PMSG_REQ_PERIODITEMEX_INSERT
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    char chCharacterName[11];
    BYTE btItemType;
    WORD wItemCode;
    BYTE btOptionType;
    BYTE btEffectType1;
    BYTE btEffectType2;
    DWORD dwSerial;
    DWORD dwDuration;
    long lBuyDate;
    long lExpireDate;
};

struct PMSG_ANS_PERIODITEMEX_INSERT
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    BYTE btResultCode;
    BYTE btItemtype;
    WORD wItemCode;
    BYTE btOptionType;
    BYTE btEffectType1;
    BYTE btEffectType2;
    DWORD dwSerial;
    DWORD dwDuration;
    long lBuyDate;
    long lExpireDate;
};

struct PMSG_ANS_PERIODITEMEX_DELETE
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    BYTE btResultCode;
};

struct PMSG_REQ_PERIODITEMEX_DELETE
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    DWORD dwSerial;
    WORD wItemCode;
    BYTE btItemType;
    char chCharacterName[11];
};

struct PMSG_REQ_PERIODITEMEX_SELECT
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    char chCharacterName[11];
};

struct PMSG_ANS_PERIODITEMEX_LIST_COUNT
{
    PBMSG_HEAD2 head;
    WORD wUserIndex;
    BYTE btResult;
    BYTE btListCount;
    DWORD dwUserGuid;
};

struct PMSG_ANS_PERIODITEMEX_LIST
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    WORD wUserIndex;
    BYTE btUsedInfo;
    BYTE btItemType;
    DWORD dwSerial;
    long lItemBuyDate;
    long lItemExpireDate;
    WORD wItemCode;
    BYTE btEffectCategory;
    BYTE btEffectType1;
    BYTE btEffectType2;
};

struct PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST
{
    PBMSG_HEAD2 head;
    WORD wUserIndex;
    BYTE btExpiredItemCount;
    WORD wItemCode[30];
    DWORD dwSerial[30];
};

struct PERIOD_EXPIRED_ITEM
{
    WORD wItemCode;
    DWORD dwSerial;
};

struct PERIOD_EXPIRED_ITEMLIST
{
    BYTE btItemCount;
    PERIOD_EXPIRED_ITEM ExpiredItem[30];
};

struct ITEMPERIOD_DATEINFO
{
    BYTE btUsedInfo;
    BYTE btItemType;
    WORD wItemCode;
    BYTE btEffectCategory;
    BYTE btEffectType1;
    BYTE btEffectType2;
    DWORD dwSerial;
    long lItemBuyDate;
    long lItemExpireDate;
};

struct PERIOD_ITEMLIST
{
    DWORD dwUserGuid;
    BYTE btItemCount;
    char chCharacterName[11];
    ITEMPERIOD_DATEINFO ItemData[100];
};

struct PMSG_REQ_LUCKYITEM_SELECT
{
    PBMSG_HEAD2 head;
    WORD wUserIndex;
    char chCharacterName[11];
};

struct PMSG_LUCKYITME_DB_INFO
{
    WORD wItemCode;
    DWORD dwSerial;
    WORD wDurabilitySmall;
};

struct PMSG_ANS_LUCKYITEM_SELECT
{
    PWMSG_HEAD head;
    WORD wUserIndex;
    BYTE btResultCode;
    BYTE btItemCnt;
};

struct PMSG_REQ_LUCKYITEM_INSERT
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    char szCharName[11];
    PMSG_LUCKYITME_DB_INFO LuckyItemDBInfo;
};

struct PMSG_REQ_LUCKYITEM_DELETE
{
    PBMSG_HEAD2 head;
    WORD wUserIndex;
    char szCharName[11];
    WORD wItemCode;
    DWORD dwSerial;
};


struct PMSG_REQ_LUCKYITEM_INSERT_2ND
{
    PBMSG_HEAD2 head;
    DWORD dwUserGuid;
    BYTE btItemCnt;
    char szCharName[11];
    PMSG_LUCKYITME_DB_INFO LuckyItemDBInfo[5];
};

struct PMSG_REQ_USERID
{
    PBMSG_HEAD2 head;
    DWORD dwKey;
    DWORD dwUserGUID;
    char chUserName[11];
};

struct SDHP_REQ_SET_EXTENDEDINVEN_COUNT
{
    PBMSG_HEAD h;
    char szCharName[11];
    WORD Number;
    BYTE ExtendedInvenCount;
    DWORD EventIndex;
    int ItemPos;
    BYTE BuyAtInGameShop;
    BYTE IsReplace;
};

struct SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT
{
    PBMSG_HEAD h;
    WORD Number;
    BYTE Result;
    BYTE ExtendedWarehouseCount;
    DWORD EventIndex;
    int ItemPos;
    BYTE BuyAtInGameShop;
    BYTE IsReplace;
};

struct SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT
{
    PBMSG_HEAD h;
    char AccountId[11];
    WORD Number;
    BYTE ExtendedWarehouseCount;
    DWORD EventIndex;
    int ItemPos;
    BYTE BuyAtInGameShop;
    BYTE IsReplace;
};

struct _PMSG_QUESTEXP_INFO
{
    PWMSG_HEAD h;
    BYTE btQuestCnt;
    char szCharName[11];
};

#pragma pack(1)
struct _QUESTEXP_INFO
{
    _QUESTEXP_INFO();

    DWORD dwQuestIndexID;
    WORD wProgState;
    BYTE btAskIndex[5];
    BYTE btAskValue[5];
    BYTE btAskState[5];
    long lStartDate;
    long lEndDate;
};
#pragma pack()

#pragma pack(1)
struct PMSG_ANS_QUESTEXP_INFO
{
    PWMSG_HEAD head;
    BYTE btQuestCnt;
    int iUserIndex;
};
#pragma pack()

#pragma pack(1)
struct PMSG_REQ_QUESTEXP_INFO
{
    PBMSG_HEAD h;
    int iUserIndex;
    char szCharName[11];
};
#pragma pack()

struct SDHP_REQ_SET_EXGAMESERVERCODE
{
    PBMSG_HEAD h;
    char szCharName[11];
    short sExGameServerCode;
};

struct SDHP_REQ_SETACCOUNTINFO
{
    PBMSG_HEAD h;
    char AccountId[11];
    short Number;
};

struct SDHP_ANS_SET_EXTENDEDINVEN_COUNT
{
    PBMSG_HEAD h;
    WORD Number;
    BYTE Result;
    BYTE ExtendedInvenCount;
    DWORD EventIndex;
    int ItemPos;
    BYTE BuyAtInGameShop;
    BYTE IsReplace;
};

struct SDHP_NPC_LEO_THE_HELPER_RECV
{
	PBMSG_HEAD header; // C1:0E:00
	WORD index;
	char account[11];
	char name[11];
};


struct SDHP_NPC_LEO_THE_HELPER_SAVE_RECV
{
	PBMSG_HEAD header; // C1:0E:30
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
	BYTE status;
};


struct SDHP_NPC_LUKE_THE_HELPER_RECV
{
	PBMSG_HEAD header; // C1:0E:01
	WORD index;
	char account[11];
	char name[11];
};


struct SDHP_NPC_LUKE_THE_HELPER_SAVE_RECV
{
	PBMSG_HEAD header; // C1:0E:31
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
	BYTE status;
};


class DataServer_Protocol
{
public:
    void ProtocolCore(DataServer_Manager * Service, int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);

    void DataServerLogin(DataServer_Manager * Service, int aIndex, SDHP_SERVERINFO * aRecv);
    void JGPGetCharList(DataServer_Manager * Service, int aIndex, SDHP_GETCHARLIST * aRecv);
    void JGCharacterCreateRequest(DataServer_Manager * Service, int aIndex, SDHP_CREATECHAR * aRecv);
    void JGCharDelRequest(DataServer_Manager * Service, int aIndex, SDHP_CHARDELETE * aRecv);
    void JGGetCharacterInfo(DataServer_Manager * Service, int aIndex, SDHP_DBCHARINFOREQUEST * aRecv);
    void GJSetCharacterInfo(DataServer_Manager * Service, int aIndex, SDHP_DBCHAR_INFOSAVE * aRecv);
    void DGGetWarehouseList(DataServer_Manager * Service, int aIndex, SDHP_GETWAREHOUSEDB * aRecv);
    void GDSetWarehouseList(DataServer_Manager * Service, int aIndex, SDHP_GETWAREHOUSEDB_SAVE * aRecv);
    void DGGetQuestMonsterKill(DataServer_Manager * Service, int aIndex, SDHP_GETQUESTMONSTER_KILL* aRecv);
    void GDQuestMonsterKillSave(DataServer_Manager * Service, int aIndex, SDHP_DBQUEST_KILLSAVE* aRecv);
    void DGChangeName(DataServer_Manager * Service, int aIndex, SDHP_CHANGE_NAME* aRecv);
    void GDMacroLoad(DataServer_Manager * Service, int aIndex, SDHP_MACRODATA* aRecv);
    void GDMacroSave(DataServer_Manager * Service, int aIndex, SDHP_MACRODATA* aRecv);
    void GDUserItemSave(DataServer_Manager * Service, int aIndex, SDHP_DBCHAR_ITEMSAVE * aRecv);
    void GDSetWarehouseMoney(DataServer_Manager * Service, int aIndex, SDHP_WAREHOUSEMONEY_SAVE * aRecv);
    void ItemSerialCreateRecv(DataServer_Manager * Service, int aIndex, SDHP_ITEMCREATE * aRecv);
    void GDPropertyItemCreate(DataServer_Manager * Service, int aIndex, SDHP_PROPERTY_ITEMCREATE * aRecv);
    void PetItemSerialCreateRecv(DataServer_Manager * Service, int aIndex, SDHP_PET_ITEMCREATE * aRecv);
    void DGRecvPetItemInfo(DataServer_Manager * Service, int aIndex, SDHP_REQUEST_PETITEM_INFO * aRecv);
    void GDSavePetItemInfo(DataServer_Manager * Service, int aIndex, SDHP_SAVE_PETITEM_INFO * aRecv);
    void DGOptionDataRecv(DataServer_Manager * Service, int aIndex, SDHP_SKILLKEYDATA * aRecv);
    void DGMoveOtherServer(DataServer_Manager * Service, int aIndex, SDHP_CHARACTER_TRANSFER * aRecv);
    void RequestMasterLevelInfoLoad(DataServer_Manager * Service, int aIndex, PMSG_REQ_ML_INFO_LOAD * aRecv);
    void RequestMasterLevelInfoSave(DataServer_Manager * Service, int aIndex, PMSG_REQ_ML_INFO_SAVE * aRecv);
    void PeriodItemInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_INSERT * aRecv);
    void PeriodItemDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_DELETE * aRecv);
    void PeriodItemUpdate(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_UPDATE * aRecv);
    void PeriodItemList(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_LIST * aRecv);
    void DS_GDReqCastleTotalInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsOwnerGuildMaster(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCastleNpcBuy(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCastleNpcRepair(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCastleNpcUpgrade(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsTaxInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_TAXINFO * aRecv);
    void GS_DGAnsTaxRateChange(DataServer_Manager * Service, int aIndex, CSP_REQ_TAXRATECHANGE * aRecv);
    void GS_DGAnsCastleMoneyChange(DataServer_Manager * Service, int aIndex, CSP_REQ_MONEYCHANGE * aRecv);
    void GS_DGAnsSiegeDateChange(DataServer_Manager * Service, int aIndex, CSP_REQ_SDEDCHANGE * aRecv);
    void GS_DGAnsGuildMarkRegInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDREGINFO * aRecv);
    void GS_DGAnsSiegeEndedChange(DataServer_Manager * Service, int aIndex, CSP_REQ_SIEGEENDCHANGE * aRecv);
    void GS_DGAnsCastleOwnerChange(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsRegAttackGuild(DataServer_Manager * Service, int aIndex, CSP_REQ_REGATTACKGUILD * aRecv);
    void GS_DGAnsRestartCastleState(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLESIEGEEND * aRecv);
    void GS_DGAnsMapSvrMsgMultiCast(DataServer_Manager * Service, int aIndex, CSP_REQ_MAPSVRMULTICAST * aRecv);
    void GS_DGAnsRegGuildMark(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDREGMARK * aRecv);
    void GS_DGAnsGuildMarkReset(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDRESETMARK * aRecv);
    void GS_DGAnsGuildSetGiveUp(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDSETGIVEUP * aRecv);
    void GS_DGAnsNpcRemove(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCastleStateSync(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLESTATESYNC * aRecv);
    void GS_DGAnsCastleTributeMoney(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLETRIBUTEMONEY * aRecv);
    void GS_DGAnsResetCastleTaxInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETCASTLETAXINFO * aRecv);
    void GS_DGAnsResetSiegeGuildInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETSIEGEGUILDINFO * aRecv);
    void GS_DGAnsResetRegSiegeInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETREGSIEGEINFO * aRecv);
    void GS_DGAnsCastleInitData(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsAllGuildMarkRegInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsFirstCreateNPC(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCalcRegGuildList(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCsGulidUnionInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCsSaveTotalGuildInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCsLoadTotalGuildInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GS_DGAnsCastleNpcUpdate(DataServer_Manager * Service, int aIndex, CSP_REQ_NPCUPDATEDATA * aRecv);
    void DGAnsCrywolfSync(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFSYNC * aRecv);
    void DGAnsCrywolfInfoLoad(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFINFOLOAD * aRecv);
    void SummonerStateUpdate(DataServer_Manager * Service, int aIndex, PMSG_REQ_SUMMONER_CREATE * aRecv);
    void GDCharacterClose(DataServer_Manager * Service, int aIndex, SDHP_USERCLOSE * aRecv);
    void DS_GDReqCastleNpcInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv);
    void GDReqCrywolfInfoSave(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFINFOSAVE * aRecv);
    void GDReqPeriodItemExInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_INSERT * aRecv);
    void GDReqPeriodItemExDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_DELETE * aRecv);
    void GDReqPeriodItemExSelect(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_SELECT * aRecv);
    void GDReqLuckyItemSelect(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_SELECT * aRecv);
    void GDReqLuckyItemInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_INSERT * aRecv);
    void GDReqLuckyItemDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_DELETE * aRecv);
    void GDReqLuckyItemInsert2nd(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_INSERT_2ND * aRecv);
    void GDReqUserID(DataServer_Manager * Service, int aIndex, PMSG_REQ_USERID * aRecv);
    void GDLoadMedalInfo(DataServer_Manager * Service, int aIndex, SDHP_LOAD_MEDALINFO * aRecv);
    void GetGameServerInfo(DataServer_Manager * Service, int aIndex, SDHP_GAMESERVERINFO * aRecv);
    void GDDeleteTempUserInfo(DataServer_Manager * Service, int aIndex, SDHP_DELETE_TEMPUSERINFO *lpMsg);
    void SetGameMasterEvent(DataServer_Manager * Service, int aIndex, SDHP_SETGMEVENT * aRecv);
    void GDSetExtendedInvenCount(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXTENDEDINVEN_COUNT * aRecv);
    void GDSetExtendedWarehouseCount(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT * aRecv);
    void GDReqQuestExpInfoSave(DataServer_Manager * Service, int  aIndex, _PMSG_QUESTEXP_INFO * aRecv);
    void GDReqQuestExpInfoLoad(DataServer_Manager * Service, int aIndex, PMSG_REQ_QUESTEXP_INFO * aRecv);
    void GDSetExGameServerCode(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXGAMESERVERCODE * aRecv);
	void GDNpcLeoTheHelperRecv(DataServer_Manager * Service, SDHP_NPC_LEO_THE_HELPER_RECV* lpMsg, int index);
	void GDNpcLeoTheHelperSaveRecv(DataServer_Manager * Service, SDHP_NPC_LEO_THE_HELPER_SAVE_RECV* lpMsg);
	void GDNpcLukeTheHelperRecv(DataServer_Manager * Service, SDHP_NPC_LUKE_THE_HELPER_RECV* lpMsg, int index);
	void GDNpcLukeTheHelperSaveRecv(DataServer_Manager * Service, SDHP_NPC_LUKE_THE_HELPER_SAVE_RECV* lpMsg);
};
extern DataServer_Protocol gDataServer_Protocol;
