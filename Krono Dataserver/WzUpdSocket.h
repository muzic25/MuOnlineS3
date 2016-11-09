#pragma once

struct PER_IO_OPERATION_DATA
{
    WSAOVERLAPPED	Overlapped;
    WSABUF			DataBuf;
    char			Buffer[2048];
    DWORD			Bytes;
    int				lOfs;
};

struct PMSG_LOGINSEVER_LIVE
{
    PBMSG_HEAD h;
    DWORD RQueue;
};


class WzUpdateSocket
{
public:
    WzUpdateSocket();
    virtual ~WzUpdateSocket();

    BOOL Init();
    BOOL CreateSocket();
    BOOL SendData(LPBYTE SendData, DWORD nSendDataLen);
    BOOL Close();
    BOOL SendSet(LPSTR ip, u_short port);
private:
    int m_Port;
    HANDLE m_ThreadHandle;
    SOCKET m_Socket;
    LPBYTE m_Recvbuf;
    PER_IO_OPERATION_DATA m_PerIoSendData;
    sockaddr_in	m_SockAddr;
};
extern WzUpdateSocket gWzUpdateSocket;

unsigned __stdcall gConnectServerUpdate(void* pArguments);