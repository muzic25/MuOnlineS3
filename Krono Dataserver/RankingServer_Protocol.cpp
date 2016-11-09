#include "stdafx.h"
RankingServer_Protocol gRankingServer_Protocol;

void RankingServer_Protocol::ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    g_ServerInfoDisplayer.CheckRKDSConnection(1);

    switch (HeadCode)
    {
    case 0x01: // [OK] - [Fine]
    {
        this->DevilSquareScore(aIndex, reinterpret_cast<PMSG_ANS_EVENTUSERSCORE *>(aRecv));
    }
    break;

    case 0x02: // [OK] - [Fine]
    {
        this->RankingUpdate();
    }
    break;

    case 0x03: // [OK] - [NOT NEEDED]
    {
        // In Use But Just to Keep The Ranking Server ON = WZ Stupid Code
    }
    break;

    case 0x07: // [OK] - [0%]
    {
        //BloodCastleRankUpdate -> NOT USE IN GS 1.00.90
    }
    break;

    case 0x08: // [OK] - [0%]
    {
        //BloodCastleCheckEnterCount -> NOT USE IN GS 1.00.90
    }
    break;

    case 0x09: // [OK] - [0%]
    {
        //BloodCastleSetEnterCount -> NOT USE IN GS 1.00.90
    }
    break;

    case 0x0A: // [OK] - [Fine]
    {
        this->BloodCastle3RDRankUpdate(aIndex, reinterpret_cast<PMSG_ANS_BLOODCASTLESCORE_5TH *>(aRecv));
    }
    break;

    case 0x0B: // [OK] - [Fine]
    {
        this->BloodCastleLeftEnterCount(aIndex, reinterpret_cast<PMSG_REQ_BLOODCASTLE_ENTERCOUNT *>(aRecv));
    }
    break;

    case 0x0C: // [OK] - [Fine]
    {
        this->BloodCastle4THRankUpdate(aIndex, reinterpret_cast<PMSG_ANS_BLOODCASTLESCORE_5TH *>(aRecv));
    }
    break;

    case 0x0D: // [OK] - [Fine]
    {
        this->BloodCastle5THRankUpdate(aIndex, reinterpret_cast<PMSG_ANS_BLOODCASTLESCORE_5TH *>(aRecv));
    }
    break;

    case 0x12: // [OK] - [Fine]
    {
        this->IllusionTempleEnterCheck(aIndex, reinterpret_cast<PMSG_REQ_ILLUSIONTEMPLE_ENTER *>(aRecv));
    }
    break;

    case 0x13: // [OK] - [Fine]
    {
        this->IllusionTempleEnterSend(aIndex, reinterpret_cast<PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT *>(aRecv));
    }
    break;

    case 0x14: // [OK] - [Fine]
    {
        this->IllusionTempleLeftEnterCount(aIndex, reinterpret_cast<PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT *>(aRecv));
    }
    break;

    default:
    {
        LogAddC(eDebug, "[RankingServer] Debug Recv: 0x%02x", HeadCode);
        gRankingServer_Manager.CloseClient(aIndex);
    }
    break;
    }

    g_ServerInfoDisplayer.CheckRKDSConnection(0);
}


void RankingServer_Protocol::RankingUpdate()
{
    if (gDataBase.Exec("EXEC SP_RANKING") == true)
    {
        LogAddC(eNormal, "[RankingServer] Ranking updated");
    }
    else
    {
        LogAddC(eError, "[RankingServer] Ranking not updated");
    }

    gDataBase.Clear();
}


void RankingServer_Protocol::DevilSquareScore(int aIndex, PMSG_ANS_EVENTUSERSCORE * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_POINT_ACCUMULATION '%d', '%d', '%s', '%s', '%d', '%d'",
                         lpMsg->ServerCode / 20 + 1, lpMsg->SquareNum, lpMsg->AccountID, lpMsg->GameID,
                         lpMsg->Class, lpMsg->Score);

    gDataBase.Clear();
}


void RankingServer_Protocol::BloodCastleLeftEnterCount(int aIndex, PMSG_REQ_BLOODCASTLE_ENTERCOUNT * lpMsg)
{
    PMSG_ANS_BLOODCASTLE_ENTERCOUNT pMsg = { 0 };

    pMsg.h.Set(0x0B, sizeof(pMsg));

    memcpy(pMsg.AccountID, lpMsg->AccountID, sizeof(pMsg.AccountID));
    memcpy(pMsg.GameID, lpMsg->GameID, sizeof(pMsg.GameID));

    pMsg.ServerCode = lpMsg->ServerCode;
    pMsg.iObjIndex = lpMsg->iObjIndex;

    if (gDataBase.ExecFormat("EXEC SP_LEFT_ENTERCOUNT_BC '%s', '%s', '%d'",
                             lpMsg->AccountID, lpMsg->GameID, lpMsg->ServerCode) == true)
    {
        pMsg.iLeftCount = gDataBase.GetInt("LeftEnterCount");
    }
    else
    {
        pMsg.iLeftCount = -1;
    }

    gDataBase.Clear();

    gRankingServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}


void RankingServer_Protocol::BloodCastle3RDRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_POINT_ACCM_BC_3RD '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d'",
                         lpMsg->ServerCode / 20 + 1, lpMsg->BridgeNum, lpMsg->AccountID, lpMsg->GameID, lpMsg->Class,
                         lpMsg->Score, lpMsg->iLeftTime, lpMsg->iAlivePartyCount);

    gDataBase.Clear();
}


void RankingServer_Protocol::BloodCastle4THRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_POINT_ACCM_BC_4TH '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d'",
                         lpMsg->ServerCode / 20 + 1, lpMsg->BridgeNum, lpMsg->AccountID, lpMsg->GameID, lpMsg->Class,
                         lpMsg->Score, lpMsg->iLeftTime, lpMsg->iAlivePartyCount);

    gDataBase.Clear();
}


void RankingServer_Protocol::BloodCastle5THRankUpdate(int aIndex, PMSG_ANS_BLOODCASTLESCORE_5TH * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_POINT_ACCM_BC_5TH '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d'",
                         lpMsg->ServerCode / 20 + 1, lpMsg->BridgeNum, lpMsg->AccountID, lpMsg->GameID, lpMsg->Class,
                         lpMsg->Score, lpMsg->iLeftTime, lpMsg->iAlivePartyCount);

    gDataBase.Clear();
}

void RankingServer_Protocol::IllusionTempleLeftEnterCount(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTERCOUNT * lpMsg)
{
    PMSG_ANS_ILLUSIONTEMPLE_ENTERCOUNT pMsg = { 0 };

    pMsg.h.Set(0x14, sizeof(pMsg));

    memcpy(pMsg.AccountID, lpMsg->AccountID, sizeof(pMsg.AccountID));
    memcpy(pMsg.GameID, lpMsg->GameID, sizeof(pMsg.GameID));

    pMsg.ServerCode = lpMsg->ServerCode;
    pMsg.iObjIndex = lpMsg->iObjIndex;

    if (gDataBase.ExecFormat("EXEC SP_LEFT_ENTERCOUNT_ILLUSIONTEMPLE '%s', '%s', '%d'",
                             lpMsg->AccountID, lpMsg->GameID, lpMsg->ServerCode) == true)
    {
        pMsg.iLeftCount = gDataBase.GetInt("LeftEnterCount");
    }
    else
    {
        pMsg.iLeftCount = -1;
    }

    gDataBase.Clear();

    gRankingServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}

void RankingServer_Protocol::IllusionTempleEnterSend(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTER_RESULT * lpMsg)
{

    if (gDataBase.ExecFormat("EXEC SP_ENTER_ILLUSION_TEMPLE '%s', '%s', '%d'",
                             lpMsg->AccountID, lpMsg->CharacterName, lpMsg->ServerCode) == true)
    {
        LogAddC(eNormal, "[RankingServer] EXEC SP_ENTER_ILLUSION_TEMPLE %s %s %d", lpMsg->AccountID, lpMsg->CharacterName, lpMsg->ServerCode);
    }
    gDataBase.Clear();

}

void RankingServer_Protocol::IllusionTempleEnterCheck(int aIndex, PMSG_REQ_ILLUSIONTEMPLE_ENTER * lpMsg)
{
    PMSG_SEND_ILLUSION_ENTER_RESULT pMsg = { 0 };

    int Result = -1;

    if (gDataBase.ExecFormat("EXEC SP_CHECK_ILLUSION_TEMPLE '%s', '%s', '%d'",
                             lpMsg->AccountID, lpMsg->CharacterName, lpMsg->ServerCode) == true)
    {
        Result = gDataBase.GetInt("EnterResult");
    }

    gDataBase.Clear();
    pMsg.h.set(0x12, sizeof(pMsg), (BYTE)Result);

    gRankingServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}

