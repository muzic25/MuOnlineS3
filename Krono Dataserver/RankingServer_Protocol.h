#pragma once


struct PMSG_ANS_EVENTUSERSCORE
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int Score;
    int Class;
    int SquareNum;
};


struct PMSG_REQ_BLOODCASTLE_ENTERCOUNT
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int iObjIndex;
};


struct PMSG_ANS_BLOODCASTLE_ENTERCOUNT
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int iObjIndex;
    int iLeftCount;
};


struct PMSG_ANS_BLOODCASTLESCORE_5TH
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int Score;
    int Class;
    int BridgeNum;
    int iLeftTime;
    int iAlivePartyCount;
};


struct PMSG_ANS_ILLUSIONTEMPLE_ENTERCOUNT
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int iObjIndex;
    int iLeftCount;
};


struct PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT
{
    PBMSG_HEAD h;
    char AccountID[10];
    char GameID[10];
    int ServerCode;
    int iObjIndex;
};

struct PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT
{
    PBMSG_HEAD h;
    char AccountID[10];
    char CharacterName[10];
    int ServerCode;
};

struct PMSG_REQ_ILLUSIONTEMPLE_ENTER
{
    PBMSG_HEAD h;
    char AccountID[10];
    char CharacterName[10];
    int ServerCode;
    int Index;
    int InventoryTicketPos;
    int Level;
    int FloorIndex;
};

struct PMSG_SEND_ILLUSION_ENTER_RESULT
{
    PBMSG_HEAD2 h;
    BYTE btResult;
};

class RankingServer_Protocol
{
public:
    void ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);
    void RankingUpdate();
    void DevilSquareScore(int aIndex, PMSG_ANS_EVENTUSERSCORE * lpMsg);
    void BloodCastleLeftEnterCount(int aIndex, PMSG_REQ_BLOODCASTLE_ENTERCOUNT * lpMsg);
    void BloodCastle3RDRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg);
    void BloodCastle4THRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg);
    void BloodCastle5THRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg);
    void IllusionTempleEnterCheck(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTER * lpMsg);
    void IllusionTempleEnterSend(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT * lpMsg);
    void IllusionTempleLeftEnterCount(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT * lpMsg);

};
extern RankingServer_Protocol gRankingServer_Protocol;

