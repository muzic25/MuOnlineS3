#pragma once


#ifndef MAX_ACCOUNT_LEN
#define MAX_ACCOUNT_LEN		10
#define MAX_GUILD_LEN		8
#endif


#define JS_ONLY_VIP_MEMBERS		0x02
#define JS_BAD_CLIENT_VERSION	0x06
#define MAX_CHAT_LEN			60


#define SET_NUMBERH(x)		( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x)		( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x)		( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x)		( (WORD)((DWORD)(x) & 0xFFFF) )
#define MAKE_NUMBERW(x,y)	( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERDW(x,y)	( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )


#define MAKEQWORD(a, b)		((QWORD)( ((QWORD) ((DWORD) (A))) << 32 | ((DWORD) (B))))
#define LODWORD(L)			((DWORD)(L))
#define HIDWORD(L)			((DWORD)(((QWORD)(L) >> 32)))


#define MACRO1(value)		(( value & 0xFF) & 0xFF)
#define MACRO2(value)		(( value & 0xFFFF ) & 0xFFFF)


#define MONTH_MACRO(value)	( (( (value)   )<0)?FALSE:(( (value)  )>12)?FALSE:TRUE  )
#define DAY_MACRO(value)	( (( (value - 1)   )<0)?FALSE:(( (value - 1)  )>30)?FALSE:TRUE  )
#define HOUR_MACRO(value)	( (( (value)   )<0)?FALSE:(( (value)  )>23)?FALSE:TRUE  )
#define MINUTE_MACRO(value) ( (( (value)   )<0)?FALSE:(( (value)  )>59)?FALSE:TRUE  )


typedef struct _PHEADB
{
    UCHAR uPacketType;
    UCHAR uSize;
    UCHAR uHead;

} PHEADB, PHEADBE, *LPHEADB, *LPHEADBE;


typedef struct _PHEADSUBB
{
    UCHAR uPacketType;
    UCHAR uSize;
    UCHAR uHead;
    UCHAR uSubHead;

} PHEADSUBB, *LPPHEADSUBB;


typedef struct _PHEADW
{
    UCHAR uPacketType;
    UCHAR uSize[2];
    UCHAR uHead;

} PHEADW, *LPPHEADW;


typedef struct _PHEADSUBW
{
    UCHAR uPacketType;
    UCHAR uSize[2];
    UCHAR uHead;
    UCHAR uSubHead;

} PHEADSUBW, *LPPHEADSUBW;


struct PBMSG_HEAD
{
public:
    void Set(BYTE head, BYTE Size)
    {
        this->c = 0xC1;
        this->Size = Size;
        this->headcode = head;
    };

    void setE(BYTE head, BYTE Size)
    {
        this->c = 0xC3;
        this->Size = Size;
        this->headcode = head;
    };

    BYTE c;
    BYTE Size;
    BYTE headcode;
};


struct PWMSG_HEAD
{
public:
    void Set(BYTE head, int size)
    {
        this->c = 0xC2;
        this->sizeH = SET_NUMBERH(size);
        this->sizeL = SET_NUMBERL(size);
        this->headcode = head;
    };

    void setE(BYTE head, int size)
    {
        this->c = 0xC4;
        this->sizeH = SET_NUMBERH(size);
        this->sizeL = SET_NUMBERL(size);
        this->headcode = head;
    };

    BYTE c;
    BYTE sizeH;
    BYTE sizeL;
    BYTE headcode;
};


struct PBMSG_HEAD2
{
public:
    void set(BYTE head, BYTE sub, BYTE Size)
    {
        this->c = 0xC1;
        this->Size = Size;
        this->headcode = head;
        this->subcode = sub;
    };

    BYTE c;
    BYTE Size;
    BYTE headcode;
    BYTE subcode;
};


struct PWMSG_HEAD2
{
public:
    void set(BYTE head, BYTE sub, int size)
    {
        this->c = 0xC2;
        this->sizeH = SET_NUMBERH(size);
        this->sizeL = SET_NUMBERL(size);
        this->headcode = head;
        this->subcode = sub;
    }

    BYTE c;
    BYTE sizeH;
    BYTE sizeL;
    BYTE headcode;
    BYTE subcode;
};


struct PMSG_DEFAULT
{
    PBMSG_HEAD h;
};


struct PMSG_DEFAULT2
{
    PBMSG_HEAD h;
    BYTE subcode;
};


struct PMSG_DEFRESULT
{
    PBMSG_HEAD h;
    BYTE result;	// 3
};


struct SDHP_SERVERINFO
{
    struct PBMSG_HEAD h;
    UCHAR Type;
    USHORT Port;
    char ServerName[50];
    USHORT ServerCode;
};


struct SDHP_RESULT
{
    struct PBMSG_HEAD h;
    UCHAR Result;
    ULONG ItemCount;
};