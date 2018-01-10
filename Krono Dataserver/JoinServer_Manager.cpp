#include "stdafx.h"


void tagSERVER_DATA::Clear()
{
    memset(m_szServerName, 0, sizeof(m_szServerName));

    m_Index = -1;
    m_ServerCode = -1;
    m_Port = -1;
    m_ConnectedCount = 0;
    m_MaxUser = 0;
}


void tagUSER_DATA::Clear()
{
    memset(m_szAccountID, 0, sizeof(m_szAccountID));

    memset(m_IP, 0, sizeof(m_IP));

    m_ServerIndex = -1;
    m_ServerCode = -1;
    iUserNumber = -1;
    nNumber = 0;
    BillCheckTimer = 0;
    BillCheckSendTimer = 0;
    m_bRequestMapSvrMove = false;
}


JoinServer_Manager::JoinServer_Manager(void)
{
    memset(m_ServObj, 0, sizeof(m_ServObj));
    memset(m_UserObj, 0, sizeof(m_UserObj));

    this->Initialize();
}


JoinServer_Manager::~JoinServer_Manager(void)
{
}

void JoinServer_Manager::Initialize()
{
    for (int i = 0; i != MAX_OBJECT; i++)
    {
        m_ServObj[i].Clear();
    }

    for (int i = 0; i != MAX_USER; i++)
    {
        m_UserObj[i].Clear();
    }
}


void JoinServer_Manager::OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    gJoinServer_Protocol.ProtocolCore(aIndex, HeadCode, aRecv, iSize);
}


void JoinServer_Manager::OnConnect()
{
    gSettings.ServiceActive++;

    LogAddC(eConnect, "[JoinServer] Connection is accepted");
}


void JoinServer_Manager::OnDisconnect(int aIndex)
{
    DelServer(aIndex);

    gSettings.ServiceActive--;

    LogAddC(eConnect, "[JoinServer] Connection is deleted");
}


bool JoinServer_Manager::IsCodeNotExist(int ServerCode)
{
    bool bReturn = true;

    for (int i = 0; i != MAX_OBJECT; i++)
    {
        tagSERVER_DATA * lpServ = &m_ServObj[i];

        if (lpServ->m_ServerCode == ServerCode)
        {
            bReturn = false;
        }
    }

    return bReturn;
}


bool JoinServer_Manager::AddServer(int ServerIndex, int ServerCode, char * szServerName, int Port)
{
    bool bReturn = true;

    if (IsCodeNotExist(ServerCode) == true)
    {
        tagSERVER_DATA * lpServ = &m_ServObj[ServerIndex];

        memcpy(lpServ->m_szServerName, szServerName, sizeof(lpServ->m_szServerName));

        lpServ->m_Port = Port;
        lpServ->m_ServerCode = ServerCode;
        lpServ->m_Index = ServerIndex;

        LogAddC(eConnect, "[JoinServer] Server added: [%d] [%d] [%s]", ServerIndex, ServerCode, szServerName);
    }
    else
    {
        LogAddC(eError, "[JoinServer] Server code already added [%d] [%s]", ServerCode, szServerName);

        bReturn = false;
    }

    return bReturn;
}

void JoinServer_Manager::DelServer(int ServerIndex)
{
    tagSERVER_DATA * lpServ = &m_ServObj[ServerIndex];

    for (int i = 0; i != MAX_USER; i++)
    {
        if (m_UserObj[i].m_ServerIndex == ServerIndex)
        {
            DelUserByIndex(i, 0);
        }
    }

    LogAddC(eConnect, "[JoinServer] Server [%d] deleted", ServerIndex);

    lpServ->Clear();
}


int JoinServer_Manager::AddUser(int ServerIndex, char * szAccountID, char * szIP, __int16 nNumber, int MembGUID)
{
    int bReturn = -1;

    tagSERVER_DATA * lpServ = &m_ServObj[ServerIndex];

    if (ServerIndex == lpServ->m_Index)
    {
        for (int i = 0; i != MAX_USER; i++)
        {
            tagUSER_DATA * lpUser = &m_UserObj[i];

            if (!strcmp(lpUser->m_szAccountID, ""))
            {
                memcpy(lpUser->m_szAccountID, szAccountID, 10);
                memcpy(lpUser->m_IP, szIP, 20);
                lpServ->m_ConnectedCount++;

                lpUser->m_ServerIndex = ServerIndex;
                lpUser->iUserNumber = lpServ->m_ConnectedCount;
                lpUser->nNumber = nNumber;
                lpUser->m_ServerCode = m_ServObj[ServerIndex].m_ServerCode;
                lpUser->Timer = time(0);

                bReturn = lpUser->iUserNumber;

                gDataBase.ExecFormat("EXEC WZ_CONNECT_MEMB '%s','%s','%s'", szAccountID, m_ServObj[ServerIndex].m_szServerName, szIP);

                LogAddC(eConnect, "[JoinServer] User [%s] [%s] connected to Server [%d]", szAccountID, szIP, ServerIndex);

                gDataBase.Clear();

                break;
            }
        }
    }

    return bReturn;
}

bool JoinServer_Manager::CheckUser(const char * szAccountID)
{
    bool bReturn = false;

    int i = GetUserIndexByID(szAccountID);

    if (i != -1)
    {
        bReturn = true;
        tagUSER_DATA * lpUser = &m_UserObj[i];

        if (lpUser->m_bRequestMapSvrMove == true)
        {
            DelUserByIndex(i, 0);
            bReturn = false;
        }
    }

    return bReturn;
}

int JoinServer_Manager::GetUserIndexByID(const char * szAccountID)
{
    int iReturn = -1;

    for (int i = 0; i != MAX_USER; i++)
    {
        tagUSER_DATA * lpUser = &m_UserObj[i];

        if (!strcmp(lpUser->m_szAccountID, szAccountID))
        {
            iReturn = i;

            break;
        }
    }

    return iReturn;
}

void JoinServer_Manager::DelUserByIndex(int nIndex, int MembGUID)
{
    if (nIndex >= 0 && nIndex < MAX_USER)
    {
        tagUSER_DATA * lpUser = &m_UserObj[nIndex];

        m_ServObj[lpUser->m_ServerIndex].m_ConnectedCount--;

        gDataBase.ExecFormat("EXEC WZ_DISCONNECT_MEMB '%s'", lpUser->m_szAccountID);
        gDataBase.Clear();
     //   gDataBase.ExecFormat("UPDATE MEMB_STAT SET ConnectStat='0' WHERE memb___id='%s'", lpUser->m_szAccountID);
      //  gDataBase.Clear();

        JS_USER_DISCONNECT pMsg = { 0 };
        pMsg.h.Set(0x09, sizeof(pMsg));
        memcpy(pMsg.AccountID, lpUser->m_szAccountID, sizeof(lpUser->m_szAccountID));
        pMsg.aIndex = lpUser->nNumber;
        DataSendAll((LPBYTE)&pMsg, pMsg.h.Size);

        LogAddC(eConnect, "[JoinServer] User [%s] disconnected Time On Game [%ld] Minutes. ", lpUser->m_szAccountID, (time(0) - lpUser->Timer) / 60);
        lpUser->Clear();
    }
}

