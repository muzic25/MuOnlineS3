#include "stdafx.h"

JoinServer_Protocol gJoinServer_Protocol;

void JoinServer_Protocol::ProtocolCore(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    g_ServerInfoDisplayer.CheckJSConnection(1);

    switch (HeadCode)
    {
    case 0x00: // [OK] - [Fine]
    {
        this->JoinServerLogin(aIndex, reinterpret_cast<JOIN_SERVER_INFO *>(aRecv));
    }
    break;

    case 0x01: // [OK] - [Fine]
    {
        this->AccountRequest(aIndex, reinterpret_cast<JOIN_SERVER_ACC_REQUEST *>(aRecv));
    }
    break;

    case 0x02: // [OK] - [Fine]
    {
        this->AccountFail(aIndex, reinterpret_cast<JOIN_SERVER_JOIN_FAIL *>(aRecv));
    }
    break;
    case 0x04: // [OK] - [Fine]
    {
        this->AccountBlock(aIndex, reinterpret_cast<SDHP_COMMAND_BLOCK *>(aRecv));
    }
    break;

    case 0x05: // [OK] - [Fine]
    {
        this->UserClose(aIndex, reinterpret_cast<JOIN_SERVER_USER_CLOSE *>(aRecv));
    }
    break;

    case 0x06: // [OK] - [9%] - Only old korean protocol
    {
        this->JoinBillCheckRecv(aIndex, reinterpret_cast<SDHP_BILLSEARCH *>(aRecv));
    }
    break;

    case 0x07:
    {
        // Not In Use
        //this->GJPUserKillRecv(aIndex, (SDHP_BILLKILLUSER *)aRecv);
    }
    break;

    case 0x08:
    {
        // Not In Use
        //this->JGOtherJoin(aIndex, (SDHP_OTHERJOINMSG *)aRecv);
    }
    break;

    case 0x09:
    {
        // Not In Use
        //this->GJPUserDisconnectRecv(aIndex, (SDHP_BILLKILLUSER *)aRecv);
    }
    break;

    case 0x16: // [OK] - [Fine]
    {
        this->UpdateUserCharacters(aIndex, reinterpret_cast<UPDATEUSERCHARACTERS *>(aRecv));
    }
    break;

    case 0x20:
    {
        // Not In Use
        //this->JGPExitCodeRecv(aIndex, (SDHP_EXITMSG *)aRecv);
    }
    break;

    case 0x30: // [OK] - [Fine]
    {
        this->LoveHeartEventRecv(aIndex, reinterpret_cast<SDHP_LOVEHEARTEVENT *>(aRecv));
    }
    break;

    case 0x31: // [OK] - [Fine]
    {
        this->LoveHeartCreateSend(aIndex, reinterpret_cast<SDHP_LOVEHEARTCREATE *>(aRecv));
    }
    break;

    case 0x40:
    {
        // Not In Use
        //this->AllNoticeRecv(aIndex, (SDHP_NOTICE *)aRecv);
    }
    break;

    case 0x41:
    {
        // Not In Use
        //this->UserNoticeRecv(aIndex, (SDHP_USER_NOTICE *)aRecv);
    }
    break;

    case 0xA0:
    {
        this->MngPro_UserClose(aIndex, reinterpret_cast<LPPMSG_FORCELOGOUT*>(aRecv));
    }
    break;

    case 0xA1:	// [OK] - [Fine]
    {
        this->MngPro_AllNoticeSend(aIndex, reinterpret_cast<LPPMSG_SETENTIRENOTICE *>(aRecv));
    }
    break;

    case 0xA2:	// [OK] - [Fine]
    {
        this->MngPro_UserNoticeSend(aIndex, reinterpret_cast<LPPMSG_USERNOTICE *>(aRecv));
    }
    break;

    case 0xA3:
    {
        // Not In Use
        //this->MngPro_GameBlock(aIndex, (LPPMSG_GAME_BLOCK *)aRecv);
    }
    break;

    case 0x7A: // [OK] - [Fine]
    {
        this->ReqMapSvrMove(aIndex, reinterpret_cast<PMSG_REQ_MAPSVRMOVE *>(aRecv));
    }
    break;

    case 0x7B: // [OK] - [Fine]
    {
        this->ReqMapSvrAuth(aIndex, reinterpret_cast<PMSG_REQ_MAPSVRAUTH *>(aRecv));
    }
    break;

    case 0x7C: // [OK] - [Fine]
    {
        this->UserCountRecv(aIndex, reinterpret_cast<PMSG_NOTIFY_MAXUSER *>(aRecv));
    }
    break;

    default:
    {
        LogAddC(eDebug, "[Debug] JoinServer Recv: 0x%02x", HeadCode);
        gJoinServer_Manager.CloseClient(aIndex);
    }
    break;
    }

    g_ServerInfoDisplayer.CheckJSConnection(0);
}


void JoinServer_Protocol::JoinServerLogin(int aIndex, JOIN_SERVER_INFO * lpMsg)
{
    JOIN_SERVER_RESULT JSResult = { 0 };

    JSResult.h.Set(0x00, sizeof(JOIN_SERVER_RESULT));

    JSResult.Result = 0x00;

    if (gJoinServer_Manager.AddServer(aIndex, lpMsg->ServerCode, lpMsg->ServerName, lpMsg->Port) == true)
    {
        JSResult.Result = 0x01;

        LogAddC(eConnect, "[JoinServer] GameServer [%s] [%d] [%d] connected", lpMsg->ServerName, lpMsg->ServerCode, lpMsg->Port);
    }

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&JSResult, JSResult.h.Size);
}


void JoinServer_Protocol::AccountRequest(int aIndex, JOIN_SERVER_ACC_REQUEST * lpMsg)
{
    char	szAccountID[11] = { 0 };
    char	szIp[16] = { 0 };
    char	szPass[11] = { 0 };
#if(SEASON > 5)
    char	JoominNumber[18] = { 0 };
#else
    char	JoominNumber[14] = { 0 };
#endif
    __int16	Number = lpMsg->Number;
    int		DBNumber = 0;
    int		UserNumber = -1;
    UCHAR	Result = ACC_REQ_SUCCESS;

    gFunc.BuxConvert(lpMsg->AccountID, sizeof(lpMsg->AccountID));
    gFunc.BuxConvert(lpMsg->Password, sizeof(lpMsg->Password));

    memcpy(szAccountID, lpMsg->AccountID, sizeof(lpMsg->AccountID));
    memcpy(szPass, lpMsg->Password, sizeof(lpMsg->Password));
    memcpy(szIp, lpMsg->IPAddress, sizeof(lpMsg->IPAddress) - 1);

    if ((gFunc.CheckSQLSyntex(szAccountID) == true) &&
            (gFunc.CheckSQLSyntex(szPass) == true))
    {
        if (gJoinServer_Manager.CheckUser(szAccountID) == false)
        {
            if (gDataBase.ExecFormat("SELECT * FROM MEMB_INFO WHERE memb___id='%s'", szAccountID) == true)
            {
                if (gDataBase.Fetch() == SQL_SUCCESS)
                {
                    char szPassword[11] = { 0 };
                    gDataBase.GetStr("memb__pwd", szPassword);

                    if (strcmp(szPass, szPassword) == NULL)
                    {
                        Result = ACC_REQ_SUCCESS;
                    }
                    else
                    {
                        LogAddC(eError, "[Error] Account [%s] wrong password", szAccountID);

                        Result = ACC_REQ_WRONG_PASS;
                    }
                    gDataBase.GetStr("sno__numb", JoominNumber);
                    DBNumber = gDataBase.GetInt("memb_guid");
                    int BlocCode = gDataBase.GetInt("bloc_code");

                    gDataBase.Clear();

                    if (Result == ACC_REQ_SUCCESS)
                    {
                        if (BlocCode > 0)
                        {
                            Result = ACC_REQ_ACC_BANNED;
                        }
                        else
                        {
                            UserNumber = gJoinServer_Manager.AddUser(aIndex, szAccountID, szIp, lpMsg->Number, DBNumber);
                            if (UserNumber == -1)
                            {
                                Result = ACC_REQ_20000;
                            }
                        }
                    }
                }
                else
                {
                    LogAddC(eError, "[Error] Account [%s] does not exits", szAccountID);

                    Result = ACC_REQ_WRONG_ID;
                }
            }
            else
            {
                LogAddC(eError, "[Error] Failed ExecFormat [%s]", szAccountID);

                Result = ACC_REQ_TEMP_BLOCK;
            }

            gDataBase.Clear();
        }
        else
        {
            LogAddC(eError, "[Error] Account [%s] already connected", szAccountID);

            Result = ACC_REQ_ALREADY_CONNECT;
        }
    }
    else
    {
        LogAddC(eError, "[Error] Account [%s] antihack check fail", szAccountID);

        Result = ACC_REQ_TEMP_BLOCK;
    }

    JOIN_SERVER_ACC_REQ_RESULT Msg = { 0 };
    Msg.h.Set(0x01, sizeof(JOIN_SERVER_ACC_REQ_RESULT));
    Msg.Result = Result;
    Msg.aIndex = Number;
    Msg.UserNumber = UserNumber;
    Msg.DBNumber = DBNumber;
    Msg.Magumsa = 0;
    Msg.m_iPCRoom = 1;
    memcpy(Msg.AccountID, szAccountID, sizeof(Msg.AccountID));
    memcpy(Msg.JoominNumber, JoominNumber, sizeof(Msg.JoominNumber));

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&Msg, Msg.h.Size);

}


void JoinServer_Protocol::AccountFail(int aIndex, JOIN_SERVER_JOIN_FAIL * lpMsg)
{
    char szAccountID[11] = { 0 };

    memcpy(szAccountID, lpMsg->AccountID, 10);

    gJoinServer_Manager.DelUserByIndex(gJoinServer_Manager.GetUserIndexByID(szAccountID), lpMsg->DBNumber);
}


void JoinServer_Protocol::UserClose(int aIndex, JOIN_SERVER_USER_CLOSE * lpMsg)
{
    char szAccountID[11] = { 0 };

    memcpy(szAccountID, lpMsg->AccountID, 10);

    gJoinServer_Manager.DelUserByIndex(gJoinServer_Manager.GetUserIndexByID(szAccountID), lpMsg->DbClass);
}


void JoinServer_Protocol::AccountBlock(int aIndex, SDHP_COMMAND_BLOCK * lpMsg)
{
    char szAccountID[11] = { 0 };

    memcpy(szAccountID, lpMsg->Id, 10);

    if (gDataBase.ExecFormat("UPDATE MEMB_INFO SET bloc_code = 1 WHERE memb___id = '%s'", szAccountID) == true)
    {
        LogAddC(eNormal, "[JoinServer] Account [%s] is blocked", szAccountID);
    }

    gDataBase.Fetch();
    gDataBase.Clear();
}


void JoinServer_Protocol::ReqMapSvrMove(int aIndex, PMSG_REQ_MAPSVRMOVE * lpMsg)
{
    char szAccountID[11] = { 0 };
    DWORD fResult = 0;
    tagUSER_DATA * lpUser = NULL;

    int	iJoinAuthCode1 = 0;
    int	iJoinAuthCode2 = 0;
    int	iJoinAuthCode3 = 0;
    int	iJoinAuthCode4 = 0;

    memcpy(szAccountID, lpMsg->szAccountID, sizeof(lpMsg->szAccountID) - 1);

    LogAddC(eNormal, "[JoinServer] Account [%s] send request to map move", szAccountID);

    if (lstrlen(szAccountID) > 1)
    {
        if (gJoinServer_Manager.IsCodeNotExist(lpMsg->wDstMapSvrCode) == false)
        {
            if (gJoinServer_Manager.m_ServObj[aIndex].m_ConnectedCount < gJoinServer_Manager.m_ServObj[aIndex].m_MaxUser)
            {
                int iUserIndex = gJoinServer_Manager.GetUserIndexByID(szAccountID);
                if (iUserIndex != -1)
                {
                    lpUser = &gJoinServer_Manager.m_UserObj[iUserIndex];
                    lpUser->m_bRequestMapSvrMove = true;
                    lpUser->m_nMoveMapTime = GetTickCount();
                }
                else
                {
                    fResult = NotConnected;
                }
            }
            else
            {
                fResult = UserLimit;
            }
        }
        else
        {
            fResult = ServerOffline;
        }
    }
    else
    {
        fResult = NotConnected;
    }
    LogAddC(eNormal, "[JoinServer] Result [%d] Account [%s] send request to map move", fResult, szAccountID);

    PMSG_ANS_MAPSVRMOVE	pMsg = { 0 };

    pMsg.h.Set(0x7A, sizeof(pMsg));

    memcpy(pMsg.szAccountID, lpMsg->szAccountID, sizeof(lpMsg->szAccountID) - 1);
    memcpy(pMsg.szCharName, lpMsg->szCharName, sizeof(lpMsg->szCharName) - 1);

    iJoinAuthCode1 = GetTickCount();
    iJoinAuthCode2 = GetTickCount() + rand() % 10000;
    iJoinAuthCode3 = GetTickCount() + rand() % 777;
    iJoinAuthCode4 = GetTickCount() + rand() % 8911;

    pMsg.iIndex = lpMsg->iIndex;
    pMsg.btX = lpMsg->btX;
    pMsg.btY = lpMsg->btY;
    pMsg.wCurMapSvrCode = lpMsg->wCurMapSvrCode;
    pMsg.wDstMapSvrCode = lpMsg->wDstMapSvrCode;
    pMsg.wMapNumber = lpMsg->wMapNumber;
    pMsg.iJoinAuthCode1 = iJoinAuthCode1;
    pMsg.iJoinAuthCode2 = iJoinAuthCode2;
    pMsg.iJoinAuthCode3 = iJoinAuthCode3;
    pMsg.iJoinAuthCode4 = iJoinAuthCode4;
    pMsg.iResult = fResult;

    if ((lpUser != NULL) && (fResult == 0))
    {
        lpUser->iJoinAuthCode1 = iJoinAuthCode1;
        lpUser->iJoinAuthCode2 = iJoinAuthCode2;
        lpUser->iJoinAuthCode3 = iJoinAuthCode3;
        lpUser->iJoinAuthCode4 = iJoinAuthCode4;
        lpUser->wPrevMapSvrCode = lpMsg->wCurMapSvrCode;
        lpUser->wMapNumber = lpMsg->wMapNumber;
        lpUser->btX = lpMsg->btX;
        lpUser->btY = lpMsg->btY;
    }

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}


void JoinServer_Protocol::ReqMapSvrAuth(int aIndex, PMSG_REQ_MAPSVRAUTH * lpMsg)
{
    char szAccountID[11] = { 0 };
    char JoominNumber[18] = { 0 };
    DWORD fResult = 0;
    tagUSER_DATA * lpUser = NULL;

    int	DBNumber = 0;
    int	UserNumber = -1;
    int	BlocCode = 0;

    WORD wPrevMapSvrCode = 0x00;
    WORD wMapNumber = 0x00;
    BYTE btX = 0x00;
    BYTE btY = 0x00;

    memcpy(szAccountID, lpMsg->szAccountID, sizeof(lpMsg->szAccountID) - 1);

    if (lstrlen(szAccountID) > 1)
    {
        if (gJoinServer_Manager.IsCodeNotExist(lpMsg->wDstMapSvrCode) == false)
        {
            if (gJoinServer_Manager.m_ServObj[aIndex].m_ConnectedCount < gJoinServer_Manager.m_ServObj[aIndex].m_MaxUser)
            {
                int iUserIndex = gJoinServer_Manager.GetUserIndexByID(szAccountID);

                if (iUserIndex != -1)
                {
                    lpUser = &gJoinServer_Manager.m_UserObj[iUserIndex];

                    if (lpUser->m_bRequestMapSvrMove == true)
                    {
                        if (lpMsg->iJoinAuthCode1 == lpUser->iJoinAuthCode1 &&
                                lpMsg->iJoinAuthCode2 == lpUser->iJoinAuthCode2 &&
                                lpMsg->iJoinAuthCode3 == lpUser->iJoinAuthCode3 &&
                                lpMsg->iJoinAuthCode4 == lpUser->iJoinAuthCode4
                           )
                        {
                            lpUser->m_bRequestMapSvrMove = false;

                            wPrevMapSvrCode = lpUser->wPrevMapSvrCode;
                            wMapNumber = lpUser->wMapNumber;
                            btX = lpUser->btX;
                            btY = lpUser->btY;
                            UserNumber = lpUser->iUserNumber;

                            gDataBase.ExecFormat("SELECT * FROM MEMB_INFO WHERE memb___id='%s'", szAccountID);

                            if (gDataBase.Fetch() != SQL_NO_DATA)
                            {
                                gDataBase.GetStr("sno__numb", JoominNumber);

                                DBNumber = gDataBase.GetInt("memb_guid");
                                BlocCode = (BYTE)gDataBase.GetInt("bloc_code");
                            }

                            gDataBase.Clear();
                        }
                        else
                        {
                            fResult = ServerOffline;
                        }
                    }
                    else
                    {
                        fResult = MoveRequest;
                    }
                }
                else
                {
                    fResult = NotConnected;
                }
            }
            else
            {
                fResult = UserLimit;
            }
        }
        else
        {
            fResult = ServerOffline;
        }
    }
    else
    {
        fResult = NotConnected;
    }

    LogAddC(eNormal, "[JoinServer] Result [%d] Account [%s] send request to map auth", fResult, szAccountID);

    PMSG_ANS_MAPSVRAUTH pMsg = { 0 };

    pMsg.h.Set(0x7B, sizeof(pMsg));

    pMsg.iIndex = lpMsg->iIndex;
    pMsg.wPrevMapSvrCode = wPrevMapSvrCode;
    pMsg.wMapNumber = wMapNumber;
    pMsg.btX = btX;
    pMsg.btY = btY;
    pMsg.iResult = fResult;
    pMsg.iUserNumber = UserNumber;
    pMsg.iDBNumber = DBNumber;
    pMsg.btBlockCode = (UCHAR)BlocCode;
    pMsg.Magumsa = 0;
    pMsg.m_iPCRoom = 1;

    memcpy(pMsg.szAccountID, szAccountID, sizeof(pMsg.szAccountID) - 1);
    memcpy(pMsg.cJoominNumber, JoominNumber, sizeof(pMsg.cJoominNumber));
    memcpy(pMsg.szCharName, lpMsg->szCharName, sizeof(pMsg.szCharName) - 1);

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}


void JoinServer_Protocol::LoveHeartEventRecv(int aIndex, SDHP_LOVEHEARTEVENT * aRecv)
{
    char szAccountID[11] = { 0 };
    char szName[11] = { 0 };
    DWORD dwHeartCount = 0;
    memcpy(szAccountID, aRecv->Account, sizeof(aRecv->Account));
    memcpy(szName, aRecv->Name, sizeof(aRecv->Name));

    SDHP_LOVEHEARTEVENT_RESULT pMsg = { 0 };

    pMsg.h.Set(0x30, sizeof(pMsg));

    pMsg.Result = 0;
    memcpy(pMsg.Name, aRecv->Name, sizeof(aRecv->Name));

    if (gDataBase.Exec("SELECT heart_count FROM LoveHeartCount WHERE Number=0") == true)
    {
        if (gDataBase.Fetch() == SQL_NO_DATA)
        {
            gDataBase.Clear();
            gDataBase.Exec("UPDATE LoveHeartCount SET heart_count=0 WHERE Number=0");
            gDataBase.Fetch();
            gDataBase.Clear();
        }
        else
        {
            dwHeartCount = gDataBase.GetInt("heart_count");
        }
    }
    gDataBase.Clear();

    dwHeartCount++;

    if (dwHeartCount > 217000)
    {
        gDataBase.Exec("UPDATE LoveHeartCount SET heart_count=0 WHERE Number=0");
        gDataBase.Clear();
    }

    gDataBase.ExecFormat("UPDATE LoveHeartCount SET heart_count= %d where Number=0", dwHeartCount);
    gDataBase.Fetch();
    gDataBase.Clear();

    gDataBase.ExecFormat("INSERT INTO LoveHeartAll ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')",
                         dwHeartCount, szAccountID, gJoinServer_Manager.m_ServObj[aIndex].m_szServerName, szName);
    gDataBase.Fetch();
    gDataBase.Clear();

    int iIndex = gJoinServer_Manager.GetUserIndexByID(szAccountID);

    if (iIndex >= 0)
    {
        if ((rand() % 217000) == iIndex)
        {
            int iServerIndex = gJoinServer_Manager.m_ServObj[aIndex].m_Index;

            if (iServerIndex != -1)
            {
                gDataBase.ExecFormat("INSERT INTO LoveHeart ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')", dwHeartCount, szAccountID, gJoinServer_Manager.m_ServObj[aIndex].m_szServerName, szName);
            }
            else
            {
                gDataBase.ExecFormat("INSERT INTO LoveHeart ( Number, Id, Server, Name ) Values (%d, '%s','%s','%s')", dwHeartCount, szAccountID, "", szName);
            }

            gDataBase.Fetch();
            gDataBase.Clear();

            pMsg.Result = 1;

            LogAddC(eNormal, "[JoinServer] Love Heart event winner [%s] [%s]", szName, gJoinServer_Manager.m_ServObj[aIndex].m_szServerName);
        }
    }

    pMsg.Number = dwHeartCount;

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}


void JoinServer_Protocol::LoveHeartCreateSend(int aIndex, SDHP_LOVEHEARTCREATE * aRecv)
{
    gDataBase.Exec("UPDATE LoveHeartCount SET heart_count=heart_count+1 where Number=1");
    gDataBase.Fetch();
    gDataBase.Clear();
}


void JoinServer_Protocol::JoinBillCheckRecv(int aIndex, SDHP_BILLSEARCH * aRecv)
{
    SDHP_BILLSEARCH_RESULT pMsg = { 0 };

    pMsg.h.Set(0x06, sizeof(pMsg));
    char szAccountID[11] = { 0 };
    memcpy(szAccountID, aRecv->Id, 10);
    memcpy(pMsg.Id, aRecv->Id, 10);

    pMsg.Number = aRecv->Number;
}

void JoinServer_Protocol::GJPUserKill(char *Id, int Number, int aIndex)
{
    SDHP_BILLKILLUSER pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0x07;
    pMsg.h.Size = sizeof(pMsg);
    memcpy(pMsg.Id, Id, 10);
    pMsg.Number = (__int16)Number;

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}


void JoinServer_Protocol::UserCountRecv(int aIndex, PMSG_NOTIFY_MAXUSER * lpMsg)
{
    if ((aIndex != -1) && (!gJoinServer_Manager.IsCodeNotExist(lpMsg->iSvrCode)))
    {
        gJoinServer_Manager.m_ServObj[aIndex].m_ConnectedCount = lpMsg->iCurUserCount;
        gJoinServer_Manager.m_ServObj[aIndex].m_MaxUser = lpMsg->iMaxUserCount;
    }
    else
    {
        LogAddC(eError, "[Error] Failed to recv users count");
    }
}


void JoinServer_Protocol::UpdateUserCharacters(int aIndex, UPDATEUSERCHARACTERS * lpMsg)
{
    gDataBase.ExecFormat("UPDATE Character SET cLevel = '%d', Class = '%d' WHERE Name = '%s' AND AccountID = '%s'",
                         lpMsg->Level, lpMsg->DbClass, lpMsg->szName, lpMsg->szId);
}

void JoinServer_Protocol::MngPro_UserClose(int aIndex, LPPMSG_FORCELOGOUT *lpMsg)
{
    char szId[11] = { 0 };
    PMSG_FORCELOGOUT_RESULT	pMsg = { 0 };

    memcpy(szId, lpMsg->AccountID, 10);
    pMsg.Result = 0x01;

    if (strlen(szId) < 1)
    {
        pMsg.Result = 0x00;
    }
    if (pMsg.Result == 0x01)
    {
        int user = gJoinServer_Manager.GetUserIndexByID(szId); //
        if (user < 0)
        {
            pMsg.Result = 0x00;
        }
        else
            GJPUserKill(gJoinServer_Manager.m_UserObj[aIndex].m_szAccountID, gJoinServer_Manager.m_UserObj[aIndex].nNumber, gJoinServer_Manager.m_UserObj[aIndex].m_ServerIndex);
    }
    pMsg.h.c = 0xC1; //
    pMsg.h.Size = sizeof(pMsg);
    pMsg.h.headcode = 0xA0;
    pMsg.ClientIndex = lpMsg->ClientIndex;

    gJoinServer_Manager.DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.Size);
}

// 0xA1
void JoinServer_Protocol::MngPro_AllNoticeSend(int aIndex, LPPMSG_SETENTIRENOTICE  * lpMsg)
{
    if (strlen(lpMsg->Notice) > 1)
    {
        SDHP_NOTICE	pMsg = { 0 };
        pMsg.h.c = 0xC1;
        pMsg.h.Size = sizeof(pMsg);
        pMsg.h.headcode = 0x40;
        memcpy(pMsg.Notice, lpMsg->Notice, 60);
        gJoinServer_Manager.DataSendAll((LPBYTE)&pMsg, pMsg.h.Size);

        if (aIndex != -1)
            gJoinServer_Manager.ServerDel(aIndex);
    }
    else
    {
        LogAddC(eError, "[JoinServer] Case 0xA1: Empty notice sent");
    }
}

void JoinServer_Protocol::MngPro_UserNoticeSend(int aIndex, LPPMSG_USERNOTICE * lpMsg)
{
    if ((strlen(lpMsg->Notice) > 1) && (strlen(lpMsg->AccountID) > 1))
    {
        int iUserIndex = gJoinServer_Manager.GetUserIndexByID(lpMsg->AccountID);

        if (iUserIndex != -1)
        {
            SDHP_USER_NOTICE tMsg = { 0 };
            tMsg.h.Set(0x41, sizeof(tMsg));
            tMsg.h.c = 0xC1;
            memcpy(tMsg.Notice, lpMsg->Notice, 60);
            memcpy(tMsg.szId, lpMsg->AccountID, 10);

            LogAddC(eNormal, "Send Entire Notice To User %s", tMsg.Notice);
            gJoinServer_Manager.DataSend(gJoinServer_Manager.m_ServObj[aIndex].m_Index, (LPBYTE)&tMsg, tMsg.h.Size);
            gJoinServer_Manager.CloseClient(aIndex);
        }
    }
}
