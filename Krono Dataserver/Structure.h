#pragma once


#include "stdafx.h"


enum SERVER_STATUS
{
    SRVS_OFFLINE,
    SRVS_ONLINE,
};


struct OBJECTSTRUCT
{
    __int16			  m_Index;
    char					m_ServerIp[16];

    SERVER_STATUS			m_State;
    SOCKET					m_Socket;

    struct _PER_SOCKET_CONTEXT * PerSocketContext;
};


struct tagSERVER_DATA
{
    void	Clear();
    char	m_szServerName[50];
    int		m_Index;
    int		m_ServerCode;
    int		m_Port;
    int		m_ConnectedCount;
    int		m_MaxUser;
};


struct tagUSER_DATA
{
    void	Clear();
    char	m_szAccountID[10];
    int		m_ServerIndex;
    int		m_ServerCode;
    time_t  Timer;
    bool	m_bRequestMapSvrMove;
    int		m_nMoveMapTime;
    int		iUserNumber;
    __int16	nNumber;
    DWORD	BillCheckTimer;
    DWORD	BillCheckSendTimer;
    int		iJoinAuthCode1;
    int		iJoinAuthCode2;
    int		iJoinAuthCode3;
    int		iJoinAuthCode4;
    WORD	wPrevMapSvrCode;
    WORD	wMapNumber;
    BYTE	btX;
    BYTE	btY;
    char	m_IP[20];
};

