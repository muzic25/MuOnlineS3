#include "stdafx.h"

WzUpdateSocket::WzUpdateSocket()
{
    m_Port = 0;
    m_Recvbuf = 0;
    memset(&m_PerIoSendData, 0, sizeof(PER_IO_OPERATION_DATA));
    memset(&m_SockAddr, 0, sizeof(sockaddr_in));

    this->Init();
}

unsigned __stdcall gConnectServerUpdate(void* pArguments)
{
    UINT bRet = 1;

    PMSG_LOGINSEVER_LIVE pMsg = { 0 };
    pMsg.h.Set(0x02, sizeof(pMsg));

    while (true)
    {
        pMsg.RQueue = 0;
        gWzUpdateSocket.SendData((LPBYTE)&pMsg, pMsg.h.Size);
        Sleep(1000);
    }

    return bRet;
}


WzUpdateSocket::~WzUpdateSocket()
{
    this->Close();
}


int WzUpdateSocket::Init()
{
    int bRet = 0;
    WSADATA wsd = {0};

    if (WSAStartup(0x202, &wsd) != 0)
    {
        this->m_Socket = INVALID_SOCKET;
        this->m_ThreadHandle = NULL;
        bRet = 1;
    }

    return bRet;
}


int WzUpdateSocket::Close()
{
    int bRet = 1;
    ::TerminateThread(this->m_ThreadHandle, 0);

    if (this->m_ThreadHandle != NULL)
    {
        WaitForSingleObject(this->m_ThreadHandle, INFINITE);
        CloseHandle(this->m_ThreadHandle);

        this->m_ThreadHandle = 0;
    }

    HeapFree(GetProcessHeap(), 0, this->m_Recvbuf);

    return bRet;
}


int WzUpdateSocket::CreateSocket()
{
    int bRet = 1;

    if (this->m_Socket != INVALID_SOCKET)
    {
        closesocket(this->m_Socket);
        this->m_Socket = INVALID_SOCKET;
    }

    this->m_Socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_IP, NULL, 0, 0);

    if (this->m_Socket == INVALID_SOCKET)
    {
        LogAddC(eError, "[WzUpdate] socket create fail with error : %d", GetLastError());
        bRet = 0;
    }

    return bRet;
}


int WzUpdateSocket::SendSet(char * IP, u_short Port)
{
    int bRet = 0;
    this->m_Port = Port;
    this->m_SockAddr.sin_family = AF_INET;

    this->m_SockAddr.sin_port = htons(Port);
    this->m_SockAddr.sin_addr.S_un.S_addr = inet_addr(IP);

    if (this->m_SockAddr.sin_addr.S_un.S_addr == -1)
    {
        hostent* host = 0;
        host = gethostbyname(IP);

        if (host != 0)
            memcpy(&this->m_SockAddr.sin_addr.S_un.S_addr, *host->h_addr_list, host->h_length);
    }
    else
        bRet = 1;

    return bRet;
}

int WzUpdateSocket::SendData(LPBYTE SendData, DWORD nSendDataLen)
{
    int bRet = SOCKET_ERROR;
    memset(&this->m_PerIoSendData.Overlapped, 0, 20);
    memcpy(this->m_PerIoSendData.Buffer, SendData, nSendDataLen);

    this->m_PerIoSendData.lOfs = nSendDataLen;
    this->m_PerIoSendData.DataBuf.buf = this->m_PerIoSendData.Buffer;
    this->m_PerIoSendData.DataBuf.len = this->m_PerIoSendData.lOfs;

    int Ret = WSASendTo(this->m_Socket, &this->m_PerIoSendData.DataBuf, 1, (unsigned long*)&nSendDataLen, 0, reinterpret_cast<sockaddr*>(&this->m_SockAddr), 16, &this->m_PerIoSendData.Overlapped, NULL);

    if (Ret == SOCKET_ERROR)
    {
        if (WSAGetLastError() != WSA_IO_PENDING)
            return bRet;
    }
    bRet = 0;

    return bRet;
}