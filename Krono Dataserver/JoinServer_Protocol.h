#pragma once

enum ACC_REQUEST_RESULT_TYPES
{
    ACC_REQ_WRONG_PASS = 0x00,
    ACC_REQ_SUCCESS = 0x01,
    ACC_REQ_WRONG_ID = 0x02,
    ACC_REQ_ALREADY_CONNECT = 0x03,
    ACC_REQ_20000 = 0x04,
    ACC_REQ_ACC_BANNED = 0x05,
    ACC_REQ_TEMP_BLOCK = 0x06,
    ACC_REQ_LOGIN_THREE_TIMES = 0x08
};


struct JOIN_SERVER_INFO
{
    struct PBMSG_HEAD h;
    unsigned char Type;
    unsigned __int16 Port;
    char ServerName[50];
    unsigned __int16 ServerCode;
};


struct JOIN_SERVER_RESULT
{
    PBMSG_HEAD		h;
    BYTE			Result;
};


struct JOIN_SERVER_ACC_REQUEST
{
    PBMSG_HEAD		h;
    char			AccountID[10];
    char			Password[10];
    __int16			Number;
    char			IPAddress[17];
};


struct JOIN_SERVER_ACC_REQ_RESULT
{
    PBMSG_HEAD		h;
    UCHAR		Result;
    __int16		aIndex;
    char		AccountID[10];
    int		UserNumber;
    int		DBNumber;
    char	JoominNumber[13];
    int		Magumsa;
    int		m_iPCRoom;
};


struct JOIN_SERVER_JOIN_FAIL
{
    PBMSG_HEAD		h;
    __int16			aIndex;
    char			AccountID[11];
    int				UserNumber;
    int				DBNumber;
};


struct JOIN_SERVER_USER_CLOSE
{
    PBMSG_HEAD		h;
    char			AccountID[10];
    char			PlayerName[10];
    USHORT			Level;
    UCHAR			DbClass;
};


struct JS_USER_DISCONNECT
{
    PBMSG_HEAD		h;
    char			AccountID[10];
    __int16			aIndex;
};


struct SDHP_COMMAND_BLOCK
{
    PBMSG_HEAD h;
    __int16 Number;
    char Id[11];
    int UserNumber;
    int DBNumber;
    unsigned char BlockCode;
};


struct PMSG_REQ_MAPSVRMOVE
{
    PBMSG_HEAD h;
    int iIndex;
    char szAccountID[11];
    char szCharName[11];
    WORD wCurMapSvrCode;
    WORD wDstMapSvrCode;
    WORD wMapNumber;
    BYTE btX;
    BYTE btY;
    BYTE btPcbangRoom;
};


struct PMSG_ANS_MAPSVRMOVE
{
    PBMSG_HEAD	h;
    int			iIndex;
    char		szAccountID[11];
    char		szCharName[11];
    USHORT		wCurMapSvrCode;
    USHORT		wDstMapSvrCode;
    USHORT		wMapNumber;
    UCHAR		btX;
    UCHAR		btY;
    int			iResult;
    int			iJoinAuthCode1;
    int			iJoinAuthCode2;
    int			iJoinAuthCode3;
    int			iJoinAuthCode4;
};


struct PMSG_REQ_MAPSVRAUTH
{
    PBMSG_HEAD	h;
    int			iIndex;
    char		szAccountID[11];
    char		szCharName[11];
    USHORT		wDstMapSvrCode;
    int			iJoinAuthCode1;
    int			iJoinAuthCode2;
    int			iJoinAuthCode3;
    int			iJoinAuthCode4;
};


struct PMSG_ANS_MAPSVRAUTH
{
    PBMSG_HEAD	h;
    int			iIndex;
    char		szAccountID[11];
    char		szCharName[11];
    WORD		wPrevMapSvrCode;
    WORD		wMapNumber;
    BYTE		btX;
    BYTE		btY;
    int			iResult;
    int			iUserNumber;
    int			iDBNumber;
    char		cJoominNumber[13];
    UCHAR 		btBlockCode;
    int			Magumsa;
    BYTE		m_iPCRoom;
};


struct SDHP_LOVEHEARTEVENT
{
    PBMSG_HEAD h;
    char Account[10];
    char Name[10];
};


struct SDHP_LOVEHEARTEVENT_RESULT
{
    PBMSG_HEAD h;
    unsigned char Result;
    char Name[10];
    int Number;
};


struct SDHP_LOVEHEARTCREATE
{
    PBMSG_HEAD h;
    unsigned char x;
    unsigned char y;
    unsigned char MapNumber;
};


struct SDHP_BILLSEARCH_RESULT
{
    PBMSG_HEAD h;
    char Id[10];
    __int16 Number;
    unsigned char cCertifyType;
    unsigned char PayCode;
    char EndsDays[12];
    int EndTime;
};


struct SDHP_BILLSEARCH
{
    PBMSG_HEAD h;
    char Id[10];
    __int16 Number;
};


struct PMSG_NOTIFY_MAXUSER
{
    PBMSG_HEAD h;
    int iSvrCode;
    int iMaxUserCount;
    int iCurUserCount;
};


struct UPDATEUSERCHARACTERS
{
    PBMSG_HEAD h;
    char szId[10];
    char szName[10];
    WORD Level;
    BYTE DbClass;
};


struct SDHP_OPTIONCONTROL
{
    PBMSG_HEAD h;
    unsigned char Option;
};


struct SDHP_NOTICE
{
    PBMSG_HEAD h;
    char Notice[61];
};

struct SDHP_BILLKILLUSER
{
    struct PBMSG_HEAD h;
    char Id[10];
    __int16 Number;
};

struct SDHP_OTHERJOINMSG
{
    struct PBMSG_HEAD h;
    char AccountID[10];
};

struct SDHP_EXITMSG
{
    PBMSG_HEAD h;
    BYTE ExitCode[3];
};

struct SDHP_USER_NOTICE
{
    PBMSG_HEAD h;
    char szId[10];
    char Notice[61];
};

struct SDHP_EVENTSTART
{
    PBMSG_HEAD h;
    BYTE Event;
};

struct SDHP_EVENTCONTROL
{
    PBMSG_HEAD h;
    BYTE Event;
    BYTE Stat;
};

struct PMSG_JG_MEMO_SEND
{
    PWMSG_HEAD h;
    char Name[10];
    char TargetName[10];
    char Subject[32];
    __int16 MemoSize;
    char Memo[1000];
};

struct LPPMSG_FORCELOGOUT
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    char		AccountID[10];
};

struct LPPMSG_SETENTIRENOTICE
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    char		Notice[60];
};

typedef struct
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    BYTE		Result;
} PMSG_FORCELOGOUT_RESULT, *LPPMSG_FORCELOGOUT_RESULT;

typedef struct
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    BYTE		Result;
} PMSG_SETENTIRENOTICE_RESULT, *LPPMSG_SETENTIRENOTICE_RESULT;

struct LPPMSG_USERNOTICE
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    char		Notice[60];
    char		AccountID[10];
};

typedef struct
{
    PBMSG_HEAD	h;
    int			ClientIndex;
    BYTE		Result;
} PMSG_USERNOTICE_RESULT, *LPPMSG_USERNOTICE_RESULT;

struct LPPMSG_GAME_BLOCK
{
    PBMSG_HEAD	h;
    int		ClientIndex;
    char	AccountID[10];
    BYTE	ServerNum;
    char	CharName[10];
    BYTE	Type;
};

typedef struct
{
    PBMSG_HEAD	h;
    int		ClientIndex;
    BYTE	Result;
} PMSG_GAME_BLOCK_RESULT, *LPPMSG_GAME_BLOCK_RESULT;

struct SDHP_SETSTATUSBAN_INFOSAVE
{
	PBMSG_HEAD h;
	char Name[11];
	BYTE Ban;
	BOOL Type;
};

class JoinServer_Protocol
{
public:
    void ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);

    void JoinServerLogin(int aIndex, JOIN_SERVER_INFO * lpMsg);
    void AccountRequest(int aIndex, JOIN_SERVER_ACC_REQUEST * lpMsg);
    void AccountFail(int aIndex, JOIN_SERVER_JOIN_FAIL * lpMsg);
    void UserClose(int aIndex, JOIN_SERVER_USER_CLOSE * lpMsg);
    void AccountBlock(int aIndex, SDHP_COMMAND_BLOCK * lpMsg);
    void ReqMapSvrMove(int aIndex, PMSG_REQ_MAPSVRMOVE * lpMsg);
    void ReqMapSvrAuth(int aIndex, PMSG_REQ_MAPSVRAUTH * lpMsg);
    void LoveHeartEventRecv(int aIndex, SDHP_LOVEHEARTEVENT * lpMsg);
    void LoveHeartCreateSend(int aIndex, SDHP_LOVEHEARTCREATE * lpMsg);
    void JoinBillCheckRecv(int aIndex, SDHP_BILLSEARCH * lpMsg);
    void GJPUserKill(char *Id, int Number, int aIndex);
    /*
    void GJPUserKillRecv		(int aIndex, SDHP_BILLKILLUSER * lpMsg);
    void JGOtherJoin			(int aIndex, SDHP_OTHERJOINMSG * lpMsg);
    void GJPUserDisconnectRecv	(int aIndex, SDHP_BILLKILLUSER * lpMsg);
    void JGPExitCodeRecv		(int aIndex, SDHP_EXITMSG * lpMsg );
    void AllNoticeRecv			(int aIndex, SDHP_NOTICE * lpMsg);
    void UserNoticeRecv			(int aIndex, SDHP_USER_NOTICE * lpMsg);
    void JGPEventStart			(int aIndex, SDHP_EVENTSTART * lpMsg );
    void JGPEventControl		(int aIndex, SDHP_EVENTCONTROL * lpMsg );
    void JGPOptionControl		(int aIndex, SDHP_OPTIONCONTROL * lpMsg );
    void JGPSendMail			(int aIndex, PMSG_JG_MEMO_SEND * lpMsg);
    */
    void MngPro_UserClose(int aIndex, LPPMSG_FORCELOGOUT *lpMsg);
    void MngPro_AllNoticeSend(int aIndex, LPPMSG_SETENTIRENOTICE *lpMsg);
    void MngPro_UserNoticeSend(int aIndex, LPPMSG_USERNOTICE *lpMsg);
	void GJSetStatusBan(int aIndex, SDHP_SETSTATUSBAN_INFOSAVE * lpMsg);
    //	void MngPro_GameBlock		(int aIndex, LPPMSG_GAME_BLOCK *lpMsg);
    void UserCountRecv(int aIndex, PMSG_NOTIFY_MAXUSER * lpMsg);
    void UpdateUserCharacters(int aIndex, UPDATEUSERCHARACTERS * lpMsg);
};
extern JoinServer_Protocol gJoinServer_Protocol;

