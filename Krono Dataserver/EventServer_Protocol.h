#pragma once



struct PMSG_REQ_VIEW_EC_MN
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
};


struct PMSG_ANS_VIEW_EC_MN
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    char bSUCCESS;
    int nEVENT_CHIPS;
    int iMUTTO_NUM;
};


struct PMSG_REQ_SET_PAYITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    __int16 nEventID;
};


struct PMSG_REQ_REGISTER_EVENTCHIP
{
    PBMSG_HEAD h;
    int iINDEX;
    BYTE Pos;
    char szUID[11];
};

struct PMSG_REQ_GET_PAYITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    __int16 nEventID;
};

struct PMSG_ANS_REGISTER_EVENTCHIP
{
    PBMSG_HEAD h;
    int iINDEX;
    BYTE iPosition;
    char szUID[11];
    char bSUCCESS;
    __int16 nEVENT_CHIPS;
};

struct PMSG_REQ_VIEW_FRIENDSHIP_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
};

struct PMSG_REQ_RESET_EVENTCHIP
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x04
    char szUID[11];//0x08
    char bSUCCESS;//0x13
};

struct PMSG_REQ_DEL_RENA
{
    PBMSG_HEAD h;
    char AccountId[11];
    int CurrRena;
};

struct PMSG_REQ_VIEW_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
};

struct PMSG_REQ_REGISTER_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    BYTE iPosition;
    char szUID[11];
};

struct PMSG_ANS_DELETE_STONES
{
    PBMSG_HEAD h;//0x00
    int iINDEX;//0x4
    char szUID[11];//0x8
    char bSUCCESS;//0x13
    int iStoneCount;//0x14
};

struct PMSG_REQ_2ANIV_SERIAL
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    char SERIAL1[5];
    char SERIAL2[5];
    char SERIAL3[5];
    int iMEMB_GUID;
};

struct PMSG_ANS_2ANIV_SERIAL
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x4
    char szUID[11];//0x8
    BYTE btIsRegistered;//0x13
    int iGiftNumber;//0x14
};

struct PMSG_ANS_RESET_EVENTCHIP
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x04
    char szUID[11];//0x08
    char bSUCCESS;//0x13
};

struct PMSG_ANS_VIEW_STONES
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x04
    char szUID[11];//0x08
    char bSUCCESS;//0x13
    int iStoneCount;//0x14
};

struct PMSG_ANS_REGISTER_STONES
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x04
    BYTE iPosition;//0x08
    char szUID[11];//0x09
    char bSUCCESS;//0x14
    int iStoneCount;//0x18
};

struct PMSG_REQ_DELETE_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
    int iStoneCount;
};

struct PMSG_REQ_REG_RINGGIFT
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    BYTE btGiftKind;
};

struct PMSG_ANS_REG_RINGGIFT
{
    PBMSG_HEAD h;//0x0
    int iINDEX;//0x4
    char szUID[11];//0x8
    BYTE btIsRegistered;//0x13
    BYTE btGiftSection;//0x14
    BYTE btGiftKind;//0x15
};

struct PMSG_REQ_REG_DL_OFFLINE_GIFT
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
};

struct PMSG_REQ_REG_CC_OFFLINE_GIFT
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
};

struct PMSG_ANS_REG_CC_OFFLINE_GIFT
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
    int iResultCode;
    char szGIFT_NAME[50];
};

struct PMSG_ANS_REG_DL_OFFLINE_GIFT
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
    int iResultCode;
    char szGIFT_NAME[50];
};

struct PMSG_REQ_REG_HT_OFFLINE_GIFT
{
    PBMSG_HEAD h;//0
    int iINDEX;//4
    char szUID[11];//8
    WORD wServerCode;//14
    char szNAME[11];//16
};

struct PMSG_ANS_REG_HT_OFFLINE_GIFT
{
    PBMSG_HEAD h;//0
    int iINDEX;//4
    char szUID[11];//8
    WORD wServerCode;//14
    char szNAME[11];//16
    int iResultCode;//24
    char szGIFT_NAME[50];//28
};

struct PMSG_REQ_POSSIBLE_PCBANG_COUPON
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
};

struct PMSG_ANS_POSSIBLE_PCBANG_COUPON
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_REQ_USE_PCBANG_COUPON
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
};

struct PMSG_ANS_USE_PCBANG_COUPON
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_ANS_CHECK_WHITEANGEL_GET_ITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_ANS_WHITEANGEL_GET_ITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_ANS_PCBANG_POINT_INFO
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    __int16 nPoint;
};

struct PMSG_ANS_PCBANG_POINT_NEW_INFO
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    BYTE btResult;
};

struct PMSG_ANS_CHECK_ALANS_TARGET
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_ANS_ALANS_ITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    BYTE iResultCode;
};

struct PMSG_ANS_PCBANG_POINT_INFO2
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    __int16 nPoint;
    __int16 nResetYear;
    __int16 nResetMonth;
    __int16 nResetDay;
    __int16 nResetHour;
};

struct PMSG_ANS_PCBANG_POINT_NEW_INFO2
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    BYTE btResult;
};

struct PMSG_ANS_GET_PAYITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    __int16 nEventID;
    BYTE bFirst;
    BYTE nResult;
};

struct PMSG_REQ_REGISTER_FRIENDSHIP_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    BYTE iPosition;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
};

struct PMSG_ANS_SET_PAYITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
    __int16 nEventID;
    BYTE bFirst;
    BYTE nResult;
};

struct PMSG_ES_ANS_GET_COIN_COUNT
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
    int nCurCoinCnt;
};

struct PMSG_ES_ANS_REG_COIN
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
    BYTE btResult;
    int nCurCoinCnt;
    BYTE btPos;
};

struct PMSG_ES_ANS_REG_MISSIONCLEAR
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
    BYTE btResult;
    int nClearCount;
};

struct PMSG_REQ_DELETE_FRIENDSHIP_STONES
{
    PBMSG_HEAD h;
    int iINDEX;
    char szUID[11];
    WORD wServerCode;
    char szNAME[11];
    int iStoneCount;
};

struct PMSG_REQ_LOG_KANTURU_TIMEATTACK_EVENT
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    char szNAME[11];
    WORD wServerCode;
    char szBattleID[14];
    BYTE btStageNumber;
    WORD wClearTime;
    int iLevel;
    int iExp;
};

struct PMSG_REQ_PCBANG_POINT_INFO
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    BYTE btServerType;
    char szUID[11];
};

struct PMSG_REQ_WHITEANGEL_GET_ITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
};

struct PMSG_REQ_PCBANG_POINT_NEW_INFO2
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    BYTE btServerType;
    __int16 nNewPoint;
    __int16 nResetYear;
    __int16 nResetMonth;
    __int16 nResetDay;
    __int16 nResetHour;
};

struct PMSG_REQ_PCBANG_POINT_NEW_INFO
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    BYTE btServerType;
    __int16 nNewPoint;
};

struct PMSG_PCBANG_POINT_RANKING_EVENT
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    BYTE btServerType;
    __int16 nUsePoint;
};

struct PMSG_ANS_ILLUSION_TEMPLE_SCORE
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
    int nTempleNumber;
    int nClass;
    int nLevel;
    BYTE btWin;
    int nPCBangGuid;
    int nRankPoint;
};

struct PMSG_REQ_CHECK_ALANS_TARGET
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
};

struct PMSG_REQ_ALANS_ITEM
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szUID[11];
    WORD wServerCode;
};

struct PMSG_REQ_PCBANG_POINT_INFO2
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    BYTE btServerType;
    char szUID[11];
};

struct PMSG_ES_REQ_GET_COIN_COUNT
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
};

struct PMSG_ES_REQ_REG_COIN
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
    BYTE btPos;
};

struct PMSG_ES_REQ_REG_MISSIONCLEAR
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
};

struct PMSG_ES_REQ_REG_DOPPELGANGER_CLEAR
{
    PBMSG_HEAD h;
    __int16 nINDEX;
    char szAccountID[11];
    char szGameID[11];
    WORD wServerCode;
};


class EventServer_Protocol
{
public:
    void ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);
    void EventChipInfo(int aIndex, PMSG_REQ_VIEW_EC_MN * lpMsg);
    void RegisterEventChip(int aIndex, PMSG_REQ_REGISTER_EVENTCHIP * lpMsg);
    void ResetEventChip(int aIndex, PMSG_REQ_RESET_EVENTCHIP * lpMsg);
    void StoneInfo(int aIndex, PMSG_REQ_VIEW_STONES * lpMsg);
    void RegisterStone(int aIndex, PMSG_REQ_REGISTER_STONES * lpMsg);
    void DeleteStone(int aIndex, PMSG_REQ_DELETE_STONES * lpMsg);
    void RegisterLottoSerial(int aIndex, PMSG_REQ_2ANIV_SERIAL * lpMsg);
    void ResetStone(int aIndex, PMSG_REQ_RESET_EVENTCHIP * lpMsg);
    void EventChipDeleteRena(int aIndex, PMSG_REQ_REG_RINGGIFT * lpMsg);
    void ViewFriendShipStones(int aIndex, PMSG_REQ_VIEW_FRIENDSHIP_STONES * lpMsg);
    void RegisterFriendShipStones(int aIndex, PMSG_REQ_REGISTER_FRIENDSHIP_STONES * lpMsg);
    void DeleteFriendShipStones(int aIndex, PMSG_REQ_DELETE_STONES * lpMsg);
    void RegisterCCOffineGift(int aIndex, PMSG_REQ_REG_CC_OFFLINE_GIFT * lpMsg);
    void RegisterDLOfflineGift(int aIndex, PMSG_REQ_REG_DL_OFFLINE_GIFT * lpMsg);
    void RegisterHTOfflineGift(int aIndex, PMSG_REQ_REG_HT_OFFLINE_GIFT * lpMsg);
    void RequestCheckPCBangCoupon(int aIndex, PMSG_REQ_POSSIBLE_PCBANG_COUPON * lpMsg);
    void RequestUsePCBangCoupon(int aIndex, PMSG_REQ_USE_PCBANG_COUPON * lpMsg);
    void RequestCheckWhiteAngelItem(int aIndex, PMSG_REQ_POSSIBLE_PCBANG_COUPON * lpMsg);
    void RequestGetWhiteAngelItem(int aIndex, PMSG_REQ_WHITEANGEL_GET_ITEM * lpMsg);
    void KanturuTimeAttackEvent(int aIndex, PMSG_REQ_LOG_KANTURU_TIMEATTACK_EVENT * lpMsg);
    void RequestPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_INFO * lpMsg);
    void ResultPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_NEW_INFO * lpMsg);
    void ReqUpdatePCBangPointRankingEvent(int aIndex, PMSG_PCBANG_POINT_RANKING_EVENT * lpMsg);
    void IllusionTempleScore(int aIndex, PMSG_ANS_ILLUSION_TEMPLE_SCORE * lpMsg);
    void RequestCheckAlansItem(int aIndex, PMSG_REQ_CHECK_ALANS_TARGET * lpMsg);
    void RequestGetAlansItem(int aIndex, PMSG_REQ_ALANS_ITEM * lpMsg);
    void RequestNewPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_INFO2 * lpMsg);
    void ResultNewPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_NEW_INFO2 * lpMsg);
    void GetPayItem(int aIndex, PMSG_REQ_GET_PAYITEM * lpMsg);
    void SetPayItem(int aIndex, PMSG_REQ_SET_PAYITEM * lpMsg);
    void CoinInfo(int aIndex, PMSG_ES_REQ_GET_COIN_COUNT * lpMsg);
    void RegisterCoin(int aIndex, PMSG_ES_REQ_REG_COIN * lpMsg);
    void RegisterIGClear(int aIndex, PMSG_ES_REQ_REG_MISSIONCLEAR * lpMsg);
    void RegDoppelgangerClear(int aIndex, PMSG_ES_REQ_REG_DOPPELGANGER_CLEAR * lpMsg);

};
extern EventServer_Protocol gEventServer_Protocol;

