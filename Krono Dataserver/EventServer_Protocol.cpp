#include "stdafx.h"



EventServer_Protocol gEventServer_Protocol;


void EventServer_Protocol::ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    g_ServerInfoDisplayer.CheckEVDSConnection(1);
    switch (HeadCode)
    {
    case 0x01: // [OK] - [Fine]
    {
        this->EventChipInfo(aIndex, reinterpret_cast<PMSG_REQ_VIEW_EC_MN *>(aRecv));
    }
    break;

    case 0x02: // [OK] - [Fine]
    {
        this->RegisterEventChip(aIndex, reinterpret_cast<PMSG_REQ_REGISTER_EVENTCHIP *>(aRecv));
    }
    break;

    case 0x04: // [OK] - [Fine]
    {
        this->ResetEventChip(aIndex, reinterpret_cast<PMSG_REQ_RESET_EVENTCHIP *>(aRecv));
    }
    break;

    case 0x05: // [OK] - [Fine]
    {
        this->StoneInfo(aIndex, reinterpret_cast<PMSG_REQ_VIEW_STONES *>(aRecv));
    }
    break;

    case 0x06: // [OK] - [Fine]
    {
        this->RegisterStone(aIndex, reinterpret_cast<PMSG_REQ_REGISTER_STONES *>(aRecv));
    }
    break;

    case 0x07: // [OK] - [Fine]
    {
        this->DeleteStone(aIndex, reinterpret_cast<PMSG_REQ_DELETE_STONES *>(aRecv));
    }
    break;

    case 0x08: // [OK] - [Fine]
    {
        this->RegisterLottoSerial(aIndex, reinterpret_cast<PMSG_REQ_2ANIV_SERIAL *>(aRecv));
    }
    break;

    case 0x09: // [OK] - [Fine]
    {
        this->ResetStone(aIndex, reinterpret_cast<PMSG_REQ_RESET_EVENTCHIP *>(aRecv));
    }
    break;

    case 0x10: // [OK] - [Fine]
    {
        this->EventChipDeleteRena(aIndex, reinterpret_cast<PMSG_REQ_REG_RINGGIFT *>(aRecv));
    }
    break;

    case 0x11: // [OK] - [Fine]
    {
        this->ViewFriendShipStones(aIndex, reinterpret_cast<PMSG_REQ_VIEW_FRIENDSHIP_STONES *>(aRecv));
    }
    break;

    case 0x12: // [OK] - [FINE]
    {
        this->RegisterFriendShipStones(aIndex, reinterpret_cast<PMSG_REQ_REGISTER_FRIENDSHIP_STONES *>(aRecv));
    }
    break;

    case 0x13: // [OK] - [FINE]
    {
        this->DeleteFriendShipStones(aIndex, reinterpret_cast<PMSG_REQ_DELETE_STONES *>(aRecv));
    }
    break;

    case 0x15: // [OK] - [Fine]
    {
        this->RegisterCCOffineGift(aIndex, reinterpret_cast<PMSG_REQ_REG_CC_OFFLINE_GIFT *>(aRecv));
    }
    break;

    case 0x16: // [OK] - [Fine]
    {
        this->RegisterDLOfflineGift(aIndex, reinterpret_cast<PMSG_REQ_REG_DL_OFFLINE_GIFT *>(aRecv));
    }
    break;

    case 0x17: // [OK] - [Fine]
    {
        this->RegisterHTOfflineGift(aIndex, reinterpret_cast<PMSG_REQ_REG_HT_OFFLINE_GIFT *>(aRecv));
    }
    break;

    case 0x18: // [OK] - [FINE]
    {
        this->RequestCheckPCBangCoupon(aIndex, reinterpret_cast<PMSG_REQ_POSSIBLE_PCBANG_COUPON *>(aRecv));
    }
    break;

    case 0x19: // [OK] - [FINE]
    {
        this->RequestUsePCBangCoupon(aIndex, reinterpret_cast<PMSG_REQ_USE_PCBANG_COUPON *>(aRecv));
    }
    break;

    case 0x20: // [OK] - [FINE]
    {
        this->RequestCheckWhiteAngelItem(aIndex, reinterpret_cast<PMSG_REQ_POSSIBLE_PCBANG_COUPON *>(aRecv));
    }
    break;

    case 0x21: // [OK] - [FINE]
    {
        this->RequestGetWhiteAngelItem(aIndex, reinterpret_cast<PMSG_REQ_WHITEANGEL_GET_ITEM *>(aRecv));
    }
    break;

    case 0x22: // [OK] - [FINE]
    {
        this->KanturuTimeAttackEvent(aIndex, reinterpret_cast<PMSG_REQ_LOG_KANTURU_TIMEATTACK_EVENT *>(aRecv));
    }
    break;

    case 0x23: // [OK] - [FINE]
    {
        this->RequestPCBangInfo(aIndex, reinterpret_cast<PMSG_REQ_PCBANG_POINT_INFO *>(aRecv));
    }
    break;

    case 0x24: // [OK] - [FINE]
    {
        this->ResultPCBangInfo(aIndex, reinterpret_cast<PMSG_REQ_PCBANG_POINT_NEW_INFO *>(aRecv));
    }
    break;

    case 0x25: // [OK] - [FINE]
    {
        this->ReqUpdatePCBangPointRankingEvent(aIndex, reinterpret_cast<PMSG_PCBANG_POINT_RANKING_EVENT *>(aRecv));
    }
    break;

    case 0x26: // [OK] - [FINE]
    {
        this->IllusionTempleScore(aIndex, reinterpret_cast<PMSG_ANS_ILLUSION_TEMPLE_SCORE *>(aRecv));
    }
    break;

    case 0x27: // [OK] - [FINE]
    {
        this->RequestCheckAlansItem(aIndex, reinterpret_cast<PMSG_REQ_CHECK_ALANS_TARGET *>(aRecv));
    }
    break;

    case 0x28: // [OK] - [FINE]
    {
        this->RequestGetAlansItem(aIndex, reinterpret_cast<PMSG_REQ_ALANS_ITEM *>(aRecv));
    }
    break;

    case 0x29: // [OK] - [FINE]
    {
        this->RequestNewPCBangInfo(aIndex, reinterpret_cast<PMSG_REQ_PCBANG_POINT_INFO2 *>(aRecv));
    }
    break;

    case 0x30: // [OK] - [FINE]
    {
        this->ResultNewPCBangInfo(aIndex, reinterpret_cast<PMSG_REQ_PCBANG_POINT_NEW_INFO2 *>(aRecv));
    }
    break;

    case 0x31: // [OK] - [FINE]
    {
        this->GetPayItem(aIndex, reinterpret_cast<PMSG_REQ_GET_PAYITEM *>(aRecv));
    }
    break;

    case 0x32: // [OK] - [FINE]
    {
        this->SetPayItem(aIndex, reinterpret_cast<PMSG_REQ_SET_PAYITEM *>(aRecv));
    }
    break;

    case 0x33: // [OK] - [FINE]
    {
        this->CoinInfo(aIndex, reinterpret_cast<PMSG_ES_REQ_GET_COIN_COUNT *>(aRecv));
    }
    break;

    case 0x34: // [OK] - [FINE]
    {
        this->RegisterCoin(aIndex, reinterpret_cast<PMSG_ES_REQ_REG_COIN *>(aRecv));
    }
    break;

    case 0x35: // [OK] - [FINE]
    {
        this->RegisterIGClear(aIndex, reinterpret_cast<PMSG_ES_REQ_REG_MISSIONCLEAR *>(aRecv));
    }
    break;

    case 0x36: // [OK] - [FINE]
    {
        this->RegDoppelgangerClear(aIndex, reinterpret_cast<PMSG_ES_REQ_REG_DOPPELGANGER_CLEAR *>(aRecv));
    }
    break;

    default:
    {
        LogAddC(eDebug, "[Debug] EventServer Recv: 0x%02x", HeadCode);
        gEventServer_Manager.CloseClient(aIndex);
    }
    break;
    }

    g_ServerInfoDisplayer.CheckEVDSConnection(0);
}


void EventServer_Protocol::EventChipInfo(int aIndex, PMSG_REQ_VIEW_EC_MN * lpMsg)
{
    PMSG_ANS_VIEW_EC_MN pMsg = { 0 };

    pMsg.h.Set(0x01, sizeof(pMsg));

    pMsg.iINDEX = lpMsg->iINDEX;
    memcpy(pMsg.szUID, lpMsg->szUID, sizeof(pMsg.szUID));

    if (gDataBase.ExecFormat("SELECT EventChips, Check_Code, MuttoNumber FROM T_MU2003_EVENT WHERE AccountID='%s'", lpMsg->szUID) == false)
    {
        pMsg.bSUCCESS = FALSE;
    }
    else
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            if (gDataBase.GetInt("Check_Code") != 0)
            {
                pMsg.nEVENT_CHIPS = 0;
            }
            else
            {
                pMsg.nEVENT_CHIPS = (__int16)gDataBase.GetInt("EventChips");
            }

            pMsg.iMUTTO_NUM = gDataBase.GetInt("MuttonNumber");
            pMsg.bSUCCESS = TRUE;
        }
        else
        {
            gDataBase.Clear();

            if (gDataBase.ExecFormat("INSERT INTO T_MU2003_EVENT (AccountID) VALUES ('%s')", pMsg.szUID) == false)
            {
                pMsg.bSUCCESS = FALSE;
            }
            else
            {
                pMsg.nEVENT_CHIPS = 0;
                pMsg.iMUTTO_NUM = 0;
                pMsg.bSUCCESS = TRUE;
            }
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}

void EventServer_Protocol::RegisterEventChip(int aIndex, PMSG_REQ_REGISTER_EVENTCHIP * lpMsg)
{
    gDataBase.ExecFormat("UPDATE T_MU2003_EVENT SET EventChips = EventChips + 1 WHERE AccountID = '%s'", lpMsg->szUID);

    gDataBase.Clear();

    PMSG_ANS_REGISTER_EVENTCHIP pMsg = { 0 };

    pMsg.h.Set(0x02, sizeof(pMsg));

    pMsg.iINDEX = lpMsg->iINDEX;

    pMsg.bSUCCESS = FALSE;

    pMsg.iPosition = lpMsg->Pos;

    pMsg.nEVENT_CHIPS = 0;

    gDataBase.ExecFormat("SELECT EventChips FROM T_MU2003_EVENT WHERE AccountID = '%s'", lpMsg->szUID);

    if (gDataBase.Fetch() != SQL_NO_DATA)
    {
        pMsg.bSUCCESS = TRUE;

        pMsg.nEVENT_CHIPS = (__int16)gDataBase.GetInt("EventChips");
    }

    gDataBase.Clear();

    gEventServer_Manager.DataSend(aIndex, (unsigned char *)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::ResetEventChip(int aIndex, PMSG_REQ_RESET_EVENTCHIP * lpMsg)
{
    PMSG_ANS_RESET_EVENTCHIP pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x04;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0;

    if (gDataBase.ExecFormat("UPDATE T_MU2003_EVENT SET Check_Code = 2 WHERE AccountID = '%s'", lpMsg->szUID))
    {
        pMsg.bSUCCESS = TRUE;
    }
    else
    {
        pMsg.bSUCCESS = FALSE;
    }

    gDataBase.Clear();

    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::StoneInfo(int aIndex, PMSG_REQ_VIEW_STONES * lpMsg)
{
    PMSG_ANS_VIEW_STONES pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x05;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0x00;

    if (gDataBase.ExecFormat("SELECT StoneCount, Check_Code FROM T_BLOOD_CASTLE WHERE AccountID='%s'", lpMsg->szUID) == FALSE)
    {
        pMsg.bSUCCESS = FALSE;
    }
    else
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            if (gDataBase.GetInt("Check_Code") != 0)
            {
                pMsg.iStoneCount = 0;
            }
            else
            {
                pMsg.iStoneCount = gDataBase.GetInt("StoneCount");
            }
            pMsg.bSUCCESS = TRUE;
        }
        else
        {
            gDataBase.Clear();

            if (gDataBase.ExecFormat("INSERT INTO T_BLOOD_CASTLE (AccountID) VALUES ('%s')", lpMsg->szUID))
            {
                pMsg.bSUCCESS = TRUE;
                pMsg.iStoneCount = 0;
            }
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));

}

void EventServer_Protocol::RegisterStone(int aIndex, PMSG_REQ_REGISTER_STONES * lpMsg)
{
    PMSG_ANS_REGISTER_STONES pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x06;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    pMsg.iPosition = lpMsg->iPosition;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0x00;

    if (gDataBase.ExecFormat("UPDATE T_BLOOD_CASTLE SET StoneCount = StoneCount + 1 WHERE AccountID = '%s'", lpMsg->szUID))
    {
        gDataBase.Clear();
        if (gDataBase.ExecFormat("SELECT StoneCount FROM T_BLOOD_CASTLE WHERE AccountID='%s'", lpMsg->szUID))
        {
            if (gDataBase.Fetch() != SQL_NO_DATA)
            {
                pMsg.iStoneCount = gDataBase.GetInt("StoneCount");

                if (pMsg.iStoneCount != -1)
                {
                    pMsg.bSUCCESS = TRUE;
                }
            }
            else
            {
                pMsg.bSUCCESS = FALSE;
            }
        }
    }
    else
    {
        pMsg.bSUCCESS = FALSE;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::DeleteStone(int aIndex, PMSG_REQ_DELETE_STONES * lpMsg)
{
    PMSG_ANS_DELETE_STONES pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x07;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0x00;

    pMsg.bSUCCESS = FALSE;

    if (gDataBase.ExecFormat("SELECT StoneCount FROM T_BLOOD_CASTLE WHERE AccountID='%s'", lpMsg->szUID) == FALSE || gDataBase.Fetch() == SQL_NO_DATA)
    {
        pMsg.bSUCCESS = FALSE;
    }
    else
    {
        int Stones = gDataBase.GetInt("StoneCount");

        gDataBase.Clear();

        if (Stones != -1 && Stones >= lpMsg->iStoneCount)
        {
            if (gDataBase.ExecFormat("UPDATE T_BLOOD_CASTLE SET StoneCount = StoneCount - %d WHERE AccountID='%s'", lpMsg->szUID) == FALSE)
            {

            }
            else
            {
                pMsg.bSUCCESS = TRUE;
                pMsg.iStoneCount = Stones - lpMsg->iStoneCount;
            }
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::RegisterLottoSerial(int aIndex, PMSG_REQ_2ANIV_SERIAL * lpMsg)
{
    PMSG_ANS_2ANIV_SERIAL pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x08;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REG_SERIAL '%s', '%d', '%s', '%s', '%s'", lpMsg->szUID, lpMsg->iMEMB_GUID, lpMsg->SERIAL1, lpMsg->SERIAL2, lpMsg->SERIAL3) && gDataBase.Fetch() != SQL_NO_DATA)
    {
        pMsg.btIsRegistered = (BYTE)gDataBase.GetInt("RegResult");
        pMsg.iGiftNumber = gDataBase.GetInt("F_Register_Section");

        if (pMsg.iGiftNumber == -1)
        {
            pMsg.btIsRegistered = 4;
        }
    }
    else
    {
        pMsg.btIsRegistered = 4;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::ResetStone(int aIndex, PMSG_REQ_RESET_EVENTCHIP * lpMsg)
{
    PMSG_ANS_RESET_EVENTCHIP pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x09;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0;

    if (gDataBase.ExecFormat("UPDATE T_BLOOD_CASTLE SET Check_Code = 2 WHERE AccountID = '%s'", lpMsg->szUID) == FALSE)
    {
        pMsg.bSUCCESS = FALSE;
    }
    else
    {
        pMsg.bSUCCESS = TRUE;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::EventChipDeleteRena(int aIndex, PMSG_REQ_REG_RINGGIFT * lpMsg)
{
    PMSG_ANS_REG_RINGGIFT pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x10;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    strcpy(pMsg.szUID, lpMsg->szUID);
    pMsg.szUID[10] = 0x10;

    pMsg.btIsRegistered = 0;

    if (gDataBase.ExecFormat("EXEC SP_REG_RINGGIFT '%s', '%d'", lpMsg->szUID, lpMsg->btGiftKind) == FALSE || gDataBase.Fetch() == SQL_NO_DATA)
    {

    }
    else
    {
        pMsg.btIsRegistered = (BYTE)gDataBase.GetInt("RegResult");
        pMsg.btGiftKind = (BYTE)gDataBase.GetInt("GiftKind");
        pMsg.btGiftSection = lpMsg->btGiftKind;

        if (pMsg.btIsRegistered == -1)
        {
            pMsg.btIsRegistered = 0;
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::ViewFriendShipStones(int aIndex, PMSG_REQ_VIEW_FRIENDSHIP_STONES * lpMsg)
{
    PMSG_ANS_VIEW_STONES tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x11;
    tMsg.h.Size = sizeof(PMSG_ANS_VIEW_STONES);
    tMsg.bSUCCESS = 0;
    tMsg.iINDEX = lpMsg->iINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);
    if (gDataBase.ExecFormat("SELECT FriendShipStoneCount, Check_Code FROM T_FRIENDSHIP_STONE WHERE AccountID = '%s' and ServerCode = '%d' and CharName = '%s'", lpMsg->szUID, lpMsg->wServerCode, lpMsg->szNAME))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            int iCHECK_CODE = gDataBase.GetInt("Check_Code");
            if (iCHECK_CODE != 0)
            {
                tMsg.iStoneCount = 0;
            }
            else
            {
                tMsg.iStoneCount = gDataBase.GetInt("FriendShipStoneCount");
            }
            tMsg.bSUCCESS = 1;
        }
        else
        {
            gDataBase.Clear();

            if (gDataBase.ExecFormat("INSERT INTO T_FRIENDSHIP_STONE (AccountID, ServerCode, CharName) VALUES ('%s', '%d', '%s')", lpMsg->szUID, lpMsg->wServerCode, lpMsg->szNAME) == false)
            {
                gDataBase.Clear();
                tMsg.bSUCCESS = 0;
            }
            else
            {
                tMsg.bSUCCESS = 1;
                tMsg.iStoneCount = 0;
            }
        }
    }
    else
    {
        tMsg.bSUCCESS = 0;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, tMsg.h.Size);
}

void EventServer_Protocol::RegisterFriendShipStones(int aIndex, PMSG_REQ_REGISTER_FRIENDSHIP_STONES * lpMsg)
{
    PMSG_ANS_REGISTER_STONES tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x12;
    tMsg.h.Size = sizeof(PMSG_ANS_REGISTER_STONES);
    tMsg.bSUCCESS = 0;
    tMsg.iINDEX = lpMsg->iINDEX;
    tMsg.iPosition = lpMsg->iPosition;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REG_FRIEND_STONE '%s', '%d', '%s'", lpMsg->szUID, lpMsg->wServerCode, lpMsg->szNAME))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iStoneCount = gDataBase.GetInt("FriendShipStoneCount");

            if (tMsg.iStoneCount != -102 && tMsg.iStoneCount != -100)
            {
                tMsg.bSUCCESS = 1;
            }
            else
            {
                tMsg.bSUCCESS = 0;
            }
        }
        else
        {
            gDataBase.Clear();
            tMsg.bSUCCESS = 0;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.bSUCCESS = 0;
        return;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, tMsg.h.Size);
}

void EventServer_Protocol::DeleteFriendShipStones(int aIndex, PMSG_REQ_DELETE_STONES * lpMsg)
{
    PMSG_ANS_DELETE_STONES tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x13;
    tMsg.h.Size = sizeof(PMSG_ANS_DELETE_STONES);
    tMsg.bSUCCESS = 0;
    tMsg.iINDEX = lpMsg->iINDEX;
    tMsg.iStoneCount = 0;
    strcpy(tMsg.szUID, lpMsg->szUID);
    int StoneCount = 0;

    if (gDataBase.ExecFormat("SELECT FriendShipStoneCount FROM T_FRIENDSHIP_STONE WHERE AccountID='%s' and ServerCode = '%d' and CharName='%s'", lpMsg->szUID, lpMsg->wServerCode, lpMsg->szNAME))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            StoneCount = gDataBase.GetInt("FriendShipStoneCount");

            if (StoneCount != -102 && StoneCount != -100)
            {
                tMsg.bSUCCESS = 1;
            }
            else
            {
                tMsg.bSUCCESS = 0;
            }
        }
        else
        {
            gDataBase.Clear();
            tMsg.bSUCCESS = 0;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.bSUCCESS = 0;
    }
    gDataBase.Clear();

    if (StoneCount >= tMsg.iStoneCount)
    {
        if (gDataBase.ExecFormat("UPDATE T_FRIENDSHIP_STONE SET FriendShipStoneCount = FriendShipStoneCount - %d WHERE AccountID='%s' and ServerCode = '%d' and CharName='%s'", tMsg.iStoneCount, lpMsg->szUID, lpMsg->wServerCode, lpMsg->szNAME))
        {
            tMsg.bSUCCESS = 1;
            tMsg.iStoneCount = StoneCount - lpMsg->iStoneCount;
        }
        else
        {
            gDataBase.Clear();
            tMsg.bSUCCESS = 0;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.bSUCCESS = 0;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, tMsg.h.Size);
}

void EventServer_Protocol::RegisterCCOffineGift(int aIndex, PMSG_REQ_REG_CC_OFFLINE_GIFT * lpMsg)
{
    PMSG_ANS_REG_CC_OFFLINE_GIFT pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x15;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    pMsg.wServerCode = lpMsg->wServerCode;
    strcpy(pMsg.szUID, lpMsg->szUID);
    strcpy(pMsg.szNAME, lpMsg->szNAME);
    pMsg.szUID[10] = 0x00;
    pMsg.szNAME[10] = 0x00;

    pMsg.iResultCode = 0;

    if (gDataBase.ExecFormat("EXEC SP_REG_CC_OFFLINE_GIFT '%s', '%s', %d", lpMsg->szUID, lpMsg->szNAME, lpMsg->wServerCode) == FALSE || gDataBase.Fetch() == SQL_NO_DATA)
    {

    }
    else
    {
        pMsg.iResultCode = gDataBase.GetInt("ResultCode");
        if (pMsg.iResultCode != -1)
        {
            gDataBase.GetStr("GiftName", pMsg.szGIFT_NAME);
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::RegisterDLOfflineGift(int aIndex, PMSG_REQ_REG_DL_OFFLINE_GIFT * lpMsg)
{
    PMSG_ANS_REG_DL_OFFLINE_GIFT pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x16;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    pMsg.wServerCode = lpMsg->wServerCode;
    strcpy(pMsg.szUID, lpMsg->szUID);
    strcpy(pMsg.szNAME, lpMsg->szNAME);
    pMsg.szUID[10] = 0x00;
    pMsg.szNAME[10] = 0x00;

    pMsg.iResultCode = 0;

    if (gDataBase.ExecFormat("EXEC SP_REG_DL_OFFLINE_GIFT '%s', '%s', %d", lpMsg->szUID, lpMsg->szNAME, lpMsg->wServerCode) == FALSE || gDataBase.Fetch() == SQL_NO_DATA)
    {

    }
    else
    {
        pMsg.iResultCode = gDataBase.GetInt("ResultCode");
        if (pMsg.iResultCode != -1)
        {
            gDataBase.GetStr("GiftName", pMsg.szGIFT_NAME);
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::RegisterHTOfflineGift(int aIndex, PMSG_REQ_REG_HT_OFFLINE_GIFT * lpMsg)
{
    PMSG_ANS_REG_HT_OFFLINE_GIFT pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x17;
    pMsg.h.Size = sizeof(pMsg);

    pMsg.iINDEX = lpMsg->iINDEX;
    pMsg.wServerCode = lpMsg->wServerCode;
    strcpy(pMsg.szUID, lpMsg->szUID);
    strcpy(pMsg.szNAME, lpMsg->szNAME);
    pMsg.szUID[10] = 0x00;
    pMsg.szNAME[10] = 0x00;

    pMsg.iResultCode = 0;

    if (gDataBase.ExecFormat("EXEC SP_REG_HT_OFFLINE_GIFT '%s', '%s', %d", lpMsg->szUID, lpMsg->szNAME, lpMsg->wServerCode) == FALSE || gDataBase.Fetch() == SQL_NO_DATA)
    {

    }
    else
    {
        pMsg.iResultCode = gDataBase.GetInt("ResultCode");
        if (pMsg.iResultCode != -1)
        {
            gDataBase.GetStr("GiftName", pMsg.szGIFT_NAME);
        }
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void EventServer_Protocol::RequestCheckPCBangCoupon(int aIndex, PMSG_REQ_POSSIBLE_PCBANG_COUPON * lpMsg)
{
    PMSG_ANS_POSSIBLE_PCBANG_COUPON tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x18;
    tMsg.h.Size = sizeof(PMSG_ANS_POSSIBLE_PCBANG_COUPON);
    tMsg.iResultCode = 3;
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_POSSIBLE_PCBANG_COUPON_EVENT '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");
        }
        else
        {
            tMsg.iResultCode = 3;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 3;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RequestUsePCBangCoupon(int aIndex, PMSG_REQ_USE_PCBANG_COUPON * lpMsg)
{
    PMSG_ANS_USE_PCBANG_COUPON tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x19;
    tMsg.h.Size = sizeof(PMSG_ANS_USE_PCBANG_COUPON);
    tMsg.iResultCode = 1;
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);
    tMsg.wServerCode = lpMsg->wServerCode;

    if (gDataBase.ExecFormat("EXEC SP_REQ_USE_PCBANG_COUPON_EVENT '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");

        }
        else
        {
            tMsg.iResultCode = 1;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 1;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RequestCheckWhiteAngelItem(int aIndex, PMSG_REQ_POSSIBLE_PCBANG_COUPON * lpMsg)
{
    PMSG_ANS_POSSIBLE_PCBANG_COUPON tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x20;
    tMsg.h.Size = sizeof(PMSG_ANS_WHITEANGEL_GET_ITEM);
    tMsg.wServerCode = lpMsg->wServerCode;
    tMsg.iResultCode = 3;
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_CHECK_WHITEANGEL_GET_ITEM_EVENT '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 3;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RequestGetWhiteAngelItem(int aIndex, PMSG_REQ_WHITEANGEL_GET_ITEM * lpMsg)
{
    PMSG_ANS_WHITEANGEL_GET_ITEM tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x21;
    tMsg.h.Size = sizeof(PMSG_ANS_WHITEANGEL_GET_ITEM);
    tMsg.iResultCode = 1;
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_WHITEANGEL_GET_ITEM '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");

        }
        else
        {
            tMsg.iResultCode = 0;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 0;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::KanturuTimeAttackEvent(int aIndex, PMSG_REQ_LOG_KANTURU_TIMEATTACK_EVENT * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_REG_KANTURU_TIMEATTACK_EVENT '%s', '%s', %d, '%s', %d, %d, %d, %d", lpMsg->szUID, lpMsg->szNAME, lpMsg->wServerCode, lpMsg->szBattleID, lpMsg->btStageNumber, lpMsg->wClearTime, lpMsg->iLevel, lpMsg->iExp);
    gDataBase.Clear();
}

void EventServer_Protocol::RequestPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_INFO * lpMsg)
{
    PMSG_ANS_PCBANG_POINT_INFO tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x23;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_INFO);
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);
    bool who = 0;

    if (lpMsg->btServerType == 1)
    {
        who = gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_INFO_TS '%s'", lpMsg->szUID);
    }
    else if (lpMsg->btServerType == 0)
    {
        who = gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_INFO '%s'", lpMsg->szUID);
    }

    if (who)
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nPoint = (__int16)gDataBase.GetInt("Result");
        }
        else
        {
            tMsg.nPoint = -2;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.nPoint = -1;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::ResultPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_NEW_INFO * lpMsg)
{
    PMSG_ANS_PCBANG_POINT_NEW_INFO tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x24;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_NEW_INFO);
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);
    bool who = 0;

    if (lpMsg->btServerType == 1)
    {
        who = gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_UPDATE_TS '%s', %d", lpMsg->szUID, lpMsg->nNewPoint);
    }
    else if (lpMsg->btServerType == 0)
    {
        who = gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_UPDATE '%s', %d", lpMsg->szUID, lpMsg->nNewPoint);
    }

    if (who)
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.btResult = (BYTE)gDataBase.GetInt("Result");
        }
        else
        {
            tMsg.btResult = 0;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.btResult = 0;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::ReqUpdatePCBangPointRankingEvent(int aIndex, PMSG_PCBANG_POINT_RANKING_EVENT * lpMsg)
{
    if (lpMsg->btServerType == 1)
    {
        gDataBase.ExecFormat("EXEC SP_UPDATE_PCBANG_POINT_RANKING_EVENT_TS '%s', %d", lpMsg->szUID, lpMsg->nUsePoint);
    }
    else if (lpMsg->btServerType == 0)
    {
        gDataBase.ExecFormat("EXEC SP_UPDATE_PCBANG_POINT_RANKING_EVENT '%s', %d", lpMsg->szUID, lpMsg->nUsePoint);
    }
    gDataBase.Clear();
}

void EventServer_Protocol::IllusionTempleScore(int aIndex, PMSG_ANS_ILLUSION_TEMPLE_SCORE * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_REG_ILLUSION_TEMPLE_RANKPOINT '%s', '%s', %d, %d, %d, %d, %d, %d, %d", lpMsg->szAccountID, lpMsg->szGameID, lpMsg->wServerCode, lpMsg->nTempleNumber, lpMsg->nClass, lpMsg->nLevel, lpMsg->btWin, lpMsg->nPCBangGuid, lpMsg->nRankPoint);
    gDataBase.Clear();
}

void EventServer_Protocol::RequestCheckAlansItem(int aIndex, PMSG_REQ_CHECK_ALANS_TARGET * lpMsg)
{
    PMSG_ANS_CHECK_ALANS_TARGET tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x27;
    tMsg.h.Size = sizeof(PMSG_ANS_CHECK_ALANS_TARGET);
    tMsg.iResultCode = 2;
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);


    if (gDataBase.ExecFormat("EXEC SP_CHECK_ALANS_LIST '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");
        }
        else
        {
            tMsg.iResultCode = 2;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 2;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RequestGetAlansItem(int aIndex, PMSG_REQ_ALANS_ITEM * lpMsg)
{
    PMSG_ANS_ALANS_ITEM tMsg = { 0 };

    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x28;
    tMsg.h.Size = sizeof(PMSG_ANS_ALANS_ITEM);
    tMsg.iResultCode = 2;
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_GET_ALANS_ITEM '%s'", lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.iResultCode = (BYTE)gDataBase.GetInt("ResultCode");
        }
        else
        {
            tMsg.iResultCode = 2;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.iResultCode = 2;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RequestNewPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_INFO2 * lpMsg)
{
    PMSG_ANS_PCBANG_POINT_INFO2 tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x29;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_INFO2);
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_INFO2 %d, '%s'", lpMsg->btServerType, lpMsg->szUID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nPoint = (__int16)gDataBase.GetInt("Result");
            tMsg.nResetYear = (__int16)gDataBase.GetInt("ResetYear");
            tMsg.nResetMonth = (__int16)gDataBase.GetInt("ResetMonth");
            tMsg.nResetDay = (__int16)gDataBase.GetInt("ResetDay");
            tMsg.nResetHour = (__int16)gDataBase.GetInt("ResetHour");
        }
        else
        {
            tMsg.nPoint = 2;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.nPoint = -1;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));

}

void EventServer_Protocol::ResultNewPCBangInfo(int aIndex, PMSG_REQ_PCBANG_POINT_NEW_INFO2 * lpMsg)
{
    PMSG_ANS_PCBANG_POINT_NEW_INFO2 tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x30;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_NEW_INFO2);
    tMsg.nINDEX = lpMsg->nINDEX;
    strcpy(tMsg.szUID, lpMsg->szUID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_PCBANG_POINT_UPDATE2 %d, '%s', %d, '%04d-%02d-%02d %02d:00:00'", lpMsg->btServerType, lpMsg->szUID, lpMsg->nNewPoint, lpMsg->nResetYear, lpMsg->nResetMonth, lpMsg->nResetDay, lpMsg->nResetHour))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.btResult = (BYTE)gDataBase.GetInt("Result");
        }
        else
        {
            tMsg.btResult = 0;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.btResult = 0;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::GetPayItem(int aIndex, PMSG_REQ_GET_PAYITEM * lpMsg)
{

    PMSG_ANS_GET_PAYITEM tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x31;
    tMsg.h.Size = sizeof(PMSG_ANS_GET_PAYITEM);
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.nEventID = lpMsg->nEventID;
    tMsg.bFirst = 0;
    tMsg.nResult = 3;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);
    tMsg.szUID[10] = '\0';

    if (gDataBase.ExecFormat("EXEC SP_GET_PAYITEM '%s', %d", lpMsg->szUID, lpMsg->nEventID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nResult = (BYTE)gDataBase.GetInt("ResultCode");
            tMsg.bFirst = (BYTE)gDataBase.GetInt("IsFirst");
        }
        else
        {
            tMsg.nResult = 3;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.nResult = 3;
    }

    if (lpMsg->nEventID < 1 || lpMsg->nEventID > 1)
    {
        tMsg.nResult = 3;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::SetPayItem(int aIndex, PMSG_REQ_SET_PAYITEM * lpMsg)
{
    PMSG_ANS_SET_PAYITEM tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x32;
    tMsg.h.Size = sizeof(PMSG_ANS_SET_PAYITEM);
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.nEventID = lpMsg->nEventID;
    tMsg.bFirst = 0;
    tMsg.nResult = 3;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szUID, lpMsg->szUID);
    tMsg.szUID[10] = '\0';

    if (gDataBase.ExecFormat("EXEC SP_SET_PAYITEM '%s', %d", lpMsg->szUID, lpMsg->nEventID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nResult = (BYTE)gDataBase.GetInt("ResultCode");
            tMsg.bFirst = (BYTE)gDataBase.GetInt("IsFirst");
        }
        else
        {
            tMsg.nResult = 3;
        }
    }
    else
    {
        gDataBase.Clear();
        tMsg.nResult = 3;
    }

    if (lpMsg->nEventID < 1 || lpMsg->nEventID > 1)
    {
        tMsg.nResult = 3;
    }

    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::CoinInfo(int aIndex, PMSG_ES_REQ_GET_COIN_COUNT * lpMsg)
{
    PMSG_ES_ANS_GET_COIN_COUNT tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x33;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_NEW_INFO2);
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szAccountID, lpMsg->szAccountID);
    strcpy(tMsg.szGameID, lpMsg->szGameID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_GET_COIN_COUNT %d, '%s', '%s' ", lpMsg->wServerCode, lpMsg->szAccountID, lpMsg->szGameID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nCurCoinCnt = gDataBase.GetInt("Result");
        }
        else
        {
            tMsg.nCurCoinCnt = -2;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.nCurCoinCnt = -1;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RegisterCoin(int aIndex, PMSG_ES_REQ_REG_COIN * lpMsg)
{
    PMSG_ES_ANS_REG_COIN tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x34;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_NEW_INFO2);
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    tMsg.btPos = lpMsg->btPos;
    strcpy(tMsg.szAccountID, lpMsg->szAccountID);
    strcpy(tMsg.szGameID, lpMsg->szGameID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_REGEIST_COIN %d, '%s', '%s', 1 ", lpMsg->wServerCode, lpMsg->szAccountID, lpMsg->szGameID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nCurCoinCnt = gDataBase.GetInt("Result");
            if (tMsg.nCurCoinCnt < 0)
            {
                tMsg.nCurCoinCnt = 0;
                tMsg.btResult = (BYTE)-2;
            }
        }
        else
        {
            tMsg.btResult = 1;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.btResult = (BYTE)-2;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RegisterIGClear(int aIndex, PMSG_ES_REQ_REG_MISSIONCLEAR * lpMsg)
{
    PMSG_ES_ANS_REG_MISSIONCLEAR tMsg = { 0 };
    tMsg.h.c = 0xC1;
    tMsg.h.headcode = 0x35;
    tMsg.h.Size = sizeof(PMSG_ANS_PCBANG_POINT_NEW_INFO2);
    tMsg.nINDEX = lpMsg->nINDEX;
    tMsg.wServerCode = lpMsg->wServerCode;
    strcpy(tMsg.szAccountID, lpMsg->szAccountID);
    strcpy(tMsg.szGameID, lpMsg->szGameID);

    if (gDataBase.ExecFormat("EXEC SP_REQ_IMPERIALGUARDIAN_EVENT %d, '%s', '%s', 1 ", lpMsg->wServerCode, lpMsg->szAccountID, lpMsg->szGameID))
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            tMsg.nClearCount = gDataBase.GetInt("Result");
            if (tMsg.nClearCount < 0)
            {
                tMsg.nClearCount = 0;
                tMsg.btResult = (BYTE)-2;
            }
        }
        else
        {
            tMsg.btResult = 1;
        }

    }
    else
    {
        gDataBase.Clear();
        tMsg.btResult = (BYTE)-2;
    }
    gDataBase.Clear();
    gEventServer_Manager.DataSend(aIndex, (LPBYTE)&tMsg, sizeof(tMsg));
}

void EventServer_Protocol::RegDoppelgangerClear(int aIndex, PMSG_ES_REQ_REG_DOPPELGANGER_CLEAR * lpMsg)
{
    gDataBase.ExecFormat("EXEC SP_REG_DOPPELGANGER_CLEAR %d, '%s', '%s'", lpMsg->wServerCode, lpMsg->szAccountID, lpMsg->szGameID);
    gDataBase.Clear();
}

