#include "stdafx.h"

IOCP::IOCP()
{
	SetDefaultSettings();
}
// --------------------------------------------------------

IOCP::~IOCP()
{
	// ----
}
// --------------------------------------------------------

void IOCP::StartServer()
{

	if (gSettings.JoinServer_Active == 1)
	{
		gWzUpdateSocket.CreateSocket();
		gWzUpdateSocket.SendSet("127.0.0.1", gSettings.UpdatePort);
		// ----
		gJoinServer_Manager.SetPort(gSettings.ServicePort);
		gJoinServer_Manager.SetName("JoinServer");
		gJoinServer_Manager.StartNetwork(2);
		// ----
		DWORD dwThreadID;
		// ----
		if (!CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gConnectServerUpdate, NULL, 0, &dwThreadID))
		{
			LogAddC(eError, "[Error] WzUpdate thread can't start");
		}
		else
		{
			LogAddC(eLoading, "[Success] WzUpdate thread start");
		}
	}

	if (gSettings.EventServer_Active == 1)
	{
		gEventServer_Manager.SetPort(gSettings.EventPort);
		gEventServer_Manager.SetName("EventServer");
		gEventServer_Manager.StartNetwork(4);
	}


	if (gSettings.RankingServer_Active == 1)
	{
		gRankingServer_Manager.SetPort(gSettings.RankingPort);
		gRankingServer_Manager.SetName("RankingServer");
		gRankingServer_Manager.StartNetwork(4);
	}



	if (gSettings.DataServer_Active == 1)
	{
		char szTemp[1024] = { 0 };
		// ----
		DataServer_Manager * gDataServer_Manager = new DataServer_Manager[gSettings.ServersCount];
		// ----
		for (int i = 0; i != gSettings.ServersCount; i++)
		{
			sprintf(szTemp, "DataServer%d", i + 1);
			// ----
			gDataServer_Manager[i].SetPort((i * 2) + gSettings.StartPort);
			gDataServer_Manager[i].SetName(szTemp);
			gDataServer_Manager[i].StartNetwork(16);
			// ----
			gDataBase.Exec("SELECT ItemCount, Number from GameServerInfo where Number=0");
			gDataServer_Manager[i].gItemCount = gDataBase.GetInt(0);
			gDataBase.Clear();
		}
	}
}
// --------------------------------------------------------

void IOCP::SetDefaultSettings()
{
	m_GSync.Lock();
	// ----
	memset(m_Name, 0, sizeof(m_Name));
	// ----
	m_Name[0] = 'I';
	m_Name[1] = 'O';
	m_Name[2] = 'C';
	m_Name[3] = 'P';
	// ----
	m_nPort = 44405;
	m_hCmport = 0;
	m_nThreadCount = 0;
	m_Listen = INVALID_SOCKET;
	// ----
	for (int i = 0; i != MAX_OBJECT; i++)
	{
		m_Server[i].m_Index = SOCKET_ERROR;
		m_Server[i].m_Socket = INVALID_SOCKET;
		m_Server[i].m_State = SS_CLOSED;
		m_Server[i].PerSocketContext = new _PER_SOCKET_CONTEXT;
	}
	// ----
	m_GSync.Unlock();
}
// --------------------------------------------------------

bool IOCP::WSAStart()
{
	WSAData	wsData = { 0 };
	// ----
	if (WSAStartup(MAKEWORD(2, 2), &wsData) != 0)
	{
		LogAddC(eError, "[%s][WSAStart] Can't load WSA library", m_Name);
		// ----
		return false;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::CreateIOCompletionPort()
{
	m_hCmport = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	// ----
	if (m_hCmport == NULL)
	{
		LogAddC(eError, "[%s][CreateIOCompletionPort] Error on create port: %d", m_Name, GetLastError());
		// ----
		return false;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::UpdateIOCompletionPort(SOCKET sd, int ClientIndex)
{
	if (CreateIoCompletionPort((HANDLE)sd, m_hCmport, ClientIndex, 0) == NULL)
	{
		LogAddC(eError, "[%s][UpdateIOCompletionPort] Error on create completion port: %d", m_Name, GetLastError());
		// ----
		m_Server[ClientIndex].PerSocketContext->dwIOCount = 0;
		// ----
		return false;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::CreateIOCPListenWorker()
{
	if (CreateThread(NULL, 0, (LPTHREAD)ListenWorker, this, 0, NULL) == NULL)
	{
		LogAddC(eError, "[%s][CreateIOCPListenWorker] Error on listen worker: %d", m_Name, GetLastError());
		// ----
		return false;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::CreateIOCPThreads(UINT NumberOfThreads)
{
	for (int i = 0; i != NumberOfThreads; i++)
	{
		m_hThread[i] = CreateThread(NULL, 0, RecvWorker, (LPVOID)this, 0, NULL);
		// ----
		if (m_hThread[i] == NULL)
		{
			LogAddC(eError, "[%s][CreateIOCPThreads] Error on create thread: %d", m_Name, GetLastError());
			// ----
			return false;
		}
		// ----
		//LogAddC(eNormal, "[%s] Thread '%d' start", m_Name, i);
		// ----
		m_nThreadCount++;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::CreateIOCPSocket()
{
	sockaddr_in	ServerAddr = { 0 };
	// ----
	m_Listen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	// ----
	if (m_Listen != SOCKET_ERROR)
	{
		ServerAddr.sin_family = AF_INET;
		ServerAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
		ServerAddr.sin_port = htons(m_nPort);
		// ----
		if (bind(m_Listen, (sockaddr*)&ServerAddr, 16) == SOCKET_ERROR)
		{
			LogAddC(eError, "[%s][CreateIOCPSocket] Socket bind error [%d] [%d]", m_Name, m_nPort, WSAGetLastError());
			// ----
			return false;
		}
		else
		{
			if (listen(m_Listen, 5) == SOCKET_ERROR)
			{
				LogAddC(eError, "[%s][CreateIOCPSocket] Socket listen error [%d] [%d]", m_Name, m_nPort, WSAGetLastError());
				// ----
				return false;
			}
			else
			{
				LogAddC(eNormal, "[%s][CreateIOCPSocket] Socket listen port [%d]", m_Name, m_nPort);
			}
		}
	}
	else
	{
		LogAddC(eError, "[%s][CreateIOCPSocket] Failed with error [%d]", m_Name, WSAGetLastError());
		// ----
		return false;
	}
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::StartNetwork(UINT NumberOfThreads)
{
	m_GSync.Lock();
	// ----
	if (WSAStart() == false)
	{
		LogAddC(eError, "[%s][StartNetwork] WSAStart() == false", m_Name);
		// ----
		return false;
	}
	// ----
	if (CreateIOCompletionPort() == false)
	{
		LogAddC(eError, "[%s][StartNetwork] CreateIOCompletionPort() == false", m_Name);
		// ----
		return false;
	}
	// ----
	if (CreateIOCPSocket() == false)
	{
		LogAddC(eError, "[%s][StartNetwork] CreateIOCPSocket() == false", m_Name);
		// ----
		return false;
	}
	// ----
	if (CreateIOCPListenWorker() == false)
	{
		LogAddC(eError, "[%s][StartNetwork] CreateIOCPListenWorker() == false", m_Name);
		// ----
		return false;
	}
	// ----
	if (CreateIOCPThreads(NumberOfThreads) == false)
	{
		LogAddC(eError, "[%s][StartNetwork] CreateIOCPThreads() == false", m_Name);
		// ----
		return false;
	}
	// ----
	m_GSync.Unlock();
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::RecvDataParse(_PER_IO_CONTEXT * lpIOContext, int uIndex)
{
	bool bReturn = true;
	// ----
	UCHAR* recvbuf = lpIOContext->Buffer;
	int lOfs = 0;
	int size = 0;
	BYTE headcode = 0x00;
	BYTE xcode = 0x00;
	// ----
	if (lpIOContext->nSentBytes < 3)
	{
		bReturn = false;
	}
	// ----
	while (true && bReturn)
	{
		if ((recvbuf[lOfs + 0] == 0xC1) || (recvbuf[lOfs + 0] == 0xC3))
		{
			size = recvbuf[lOfs + 1];
			headcode = recvbuf[lOfs + 2];
			xcode = recvbuf[lOfs + 0];
		}
		else if ((recvbuf[lOfs + 0] == 0xC2) || (recvbuf[lOfs + 0] == 0xC4))
		{
			size = recvbuf[lOfs + 1] * 256;
			size |= recvbuf[lOfs + 2];
			headcode = recvbuf[lOfs + 3];
			xcode = recvbuf[lOfs + 0];
		}
		else
		{
			LogAddC(eError, "[%s][RecvDataParse] Header parser get error, Size: [%d], HeadCode: [%x], Case: [%x]", m_Name, size, headcode, xcode);
			// ----
			bReturn = false;
			// ----
			break;
		}
		if (size <= 0)
		{
			LogAddC(eError, "[%s][RecvDataParse] Recv size error [%d]", m_Name, size);
			// ----
			bReturn = false;
			// ----
			break;
		}
		// ----
		if (size <= lpIOContext->nSentBytes)
		{
			OnRecv(uIndex, headcode, &recvbuf[lOfs], size);
			// ----
			lOfs += size;
			lpIOContext->nSentBytes -= size;
			// ----
			if (lpIOContext->nSentBytes <= 0)
			{
				break;
			}
		}
		else if (lOfs > 0)
		{
			if (lpIOContext->nSentBytes < 1)
			{
				LogAddC(eError, "[%s][RecvDataParse] Buff < 1", m_Name);
				// ----
				break;
			}
			// ----
			if (lpIOContext->nSentBytes < MAX_IO_BUFFER_SIZE)
			{
				memcpy(recvbuf, &recvbuf[lOfs], lpIOContext->nSentBytes);
			}
			// ----
			break;
		}
		else
		{
			break;
		}
	}
	// ----
	return bReturn;
}
// --------------------------------------------------------

bool IOCP::DataSend(int aIndex, UCHAR * lpMsg, DWORD dwSize)
{
	ULONG SendBytes = NULL;
	// ----
	_OBJECT * lpObj = &m_Server[aIndex];
	// ----
	LPPERSOCKET = lpObj->PerSocketContext;
	// ----
	if ((aIndex < 0) || (aIndex > MAX_OBJECT))
	{
		LogAddC(eError, "[%s][DataSend] :: (DataSend) Index(%d) %x %x %x ", m_Name, dwSize, lpMsg[0], lpMsg[1], lpMsg[2]);
		// ----
		return false;
	}
	// ----
	if (lpObj->m_State < SS_CONNECTED)
	{
		// ----
		return false;
	}
	// ----
	if (dwSize > sizeof(lpPerSocketContext->IOContext[0].Buffer))
	{
		LogAddC(eError, "[%s][DataSend] :: Error Max msg(%d) %s %d", m_Name, dwSize, __FILE__, __LINE__);
		// ----
		CloseClient(aIndex);
		// ----
		return false;
	}
	// ----
	_PER_IO_CONTEXT  * lpIoCtxt = &lpPerSocketContext->IOContext[1];
	// ----
	if (lpIoCtxt->nWaitIO > 0)
	{
		if ((lpIoCtxt->nSecondOfs + dwSize) > MAX_IO_BUFFER_SIZE - 1)
		{
			LogAddC(eError, "[%s][DataSend] :: (Index->%d) MAX BUFFER OVER %d %d %d", m_Name, aIndex, lpIoCtxt->nTotalBytes, lpIoCtxt->nSecondOfs, dwSize);
			// ----
			lpIoCtxt->nWaitIO = 0;
			// ----
			CloseClient(aIndex);
			// ----
			return true;
		}
		// ----
		memcpy(&lpIoCtxt->BufferSecond[lpIoCtxt->nSecondOfs], lpMsg, dwSize);
		// ----
		lpIoCtxt->nSecondOfs += dwSize;
		// ----
		return true;
	}
	// ----
	lpIoCtxt->nTotalBytes = 0;
	// ----
	if (lpIoCtxt->nSecondOfs > 0)
	{
		memcpy(lpIoCtxt->Buffer, lpIoCtxt->BufferSecond, lpIoCtxt->nSecondOfs);
		// ----
		lpIoCtxt->nTotalBytes = lpIoCtxt->nSecondOfs;
		lpIoCtxt->nSecondOfs = 0;
	}
	// ----
	if ((lpIoCtxt->nTotalBytes + dwSize) > (MAX_IO_BUFFER_SIZE - 1))
	{
		LogAddC(eError, "[%s][DataSend] :: (Index->%d) MAX BUFFER OVER %d %d %d", m_Name, aIndex, lpIoCtxt->nTotalBytes, lpIoCtxt->nSecondOfs, dwSize);
		// ----
		lpIoCtxt->nWaitIO = 0;
		// ----
		CloseClient(aIndex);
		// ----
		return false;
	}
	memcpy(&lpIoCtxt->Buffer[lpIoCtxt->nTotalBytes], lpMsg, dwSize);
	// ----
	lpIoCtxt->nTotalBytes += dwSize;
	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer;
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes;
	lpIoCtxt->nSentBytes = 0;
	lpIoCtxt->IOOperation = OP_RECV;
	// ----
	if (WSASend(lpObj->m_Socket, &lpIoCtxt->wsabuf, 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			lpIoCtxt->nWaitIO = 0;
			// ----
			if (lpIoCtxt->wsabuf.buf[0] == 0xC1)
			{
				LogAddC(eError, "[%s][DataSend] :: (%d)WSASend(%d) failed with error [%x][%x] %d %s ", m_Name, __LINE__, aIndex, (BYTE)lpIoCtxt->wsabuf.buf[0],
					(BYTE)lpIoCtxt->wsabuf.buf[2], WSAGetLastError(), lpObj->m_ServerIp);
			}
			else if (lpIoCtxt->wsabuf.buf[0] == 0xC2)
			{
				LogAddC(eError, "[%s][DataSend] :: (%d)WSASend(%d) failed with error [%x][%x] %d %s ", m_Name, __LINE__, aIndex, (BYTE)lpIoCtxt->wsabuf.buf[0],
					(BYTE)lpIoCtxt->wsabuf.buf[3], WSAGetLastError(), lpObj->m_ServerIp);;
			}
			// ----
			CloseClient(aIndex);
			// ----
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount++;
	}
	// ----
	lpIoCtxt->nWaitIO = 1;
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::IoSendSecond(_PER_SOCKET_CONTEXT * lpPerSocketContext)
{
	_OBJECT * lpObj = &m_Server[lpPerSocketContext->nIndex];
	ULONG SendBytes = NULL;
	_PER_IO_CONTEXT * lpIoCtxt = &lpPerSocketContext->IOContext[1];
	// ----
	if (lpIoCtxt->nWaitIO > 0)
	{
		return false;
	}
	// ----
	lpIoCtxt->nTotalBytes = 0;
	// ----
	if (lpIoCtxt->nSecondOfs > 0)
	{
		// ----
		memcpy(lpIoCtxt->Buffer, lpIoCtxt->BufferSecond, lpIoCtxt->nSecondOfs);
		// ----
		lpIoCtxt->nTotalBytes = lpIoCtxt->nSecondOfs;
		lpIoCtxt->nSecondOfs = 0;
	}
	else
	{
		return false;
	}
	// ----
	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer;
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes;
	lpIoCtxt->nSentBytes = 0;
	lpIoCtxt->IOOperation = OP_RECV;
	// ----
	if (WSASend(lpObj->m_Socket, &lpIoCtxt->wsabuf, 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			LogAddC(eError, "[%s][IoSendSecond] :: WSASend(%d) failed with error %d %s ", m_Name, __LINE__, WSAGetLastError(), lpObj->m_ServerIp);
			// ----
			CloseClient(lpObj->m_Index);
			// ----
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount++;
	}
	// ----
	lpIoCtxt->nWaitIO = 1;
	// ----
	return true;
}
// --------------------------------------------------------

bool IOCP::IoMoreSend(_PER_SOCKET_CONTEXT * lpPerSocketContext)
{
	_OBJECT * lpObj = &m_Server[lpPerSocketContext->nIndex];
	ULONG SendBytes = NULL;
	_PER_IO_CONTEXT * lpIoCtxt = &lpPerSocketContext->IOContext[1];
	// ----
	if (lpIoCtxt->nWaitIO > 0)
	{
		return false;
	}
	// ----
	if ((lpIoCtxt->nTotalBytes - lpIoCtxt->nSentBytes) < 0)
	{
		return false;
	}
	// ----
	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer[lpIoCtxt->nSentBytes];
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes - lpIoCtxt->nSentBytes;
	lpIoCtxt->IOOperation = OP_RECV;
	// ----
	if (WSASend(lpObj->m_Socket, &lpIoCtxt->wsabuf, 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			LogAddC(eError, "[%s][IoMoreSend] :: WSASend(%d) failed with error %d %s ", m_Name, __LINE__, WSAGetLastError(), lpObj->m_ServerIp);
			// ----
			CloseClient(lpObj->m_Index);
			// ----
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount++;
	}
	// ----
	lpIoCtxt->nWaitIO = 1;
	// ----
	return true;
}
// --------------------------------------------------------

void IOCP::CloseClient(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result)
{
	int index = lpPerSocketContext->nIndex;
	// ----
	if (index >= 0 && index <= MAX_OBJECT)
	{
		if (m_Server[index].m_Socket != INVALID_SOCKET)
		{
			if (closesocket(m_Server[index].m_Socket) == -1)
			{
				if (WSAGetLastError() != WSAENOTSOCK)
				{
					return;
				}
			}
			m_Server[index].m_Socket = INVALID_SOCKET;
		}
		ServerDel(index);
	}
}
// --------------------------------------------------------

void IOCP::CloseClient(int index)
{
	if (index < 0 || index >= MAX_OBJECT)
	{
		LogAddC(eError, "[%s][CloseClient] :: CloseClient index error", m_Name);
		// ----
		return;
	}
	// ----
	if (m_Server[index].m_State == SS_CLOSED)
	{
		LogAddC(eError, "[%s][CloseClient] :: CloseClient connect error", m_Name);
		// ----
		return;
	}
	// ----
	if (m_Server[index].m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Server[index].m_Socket);
		// ----
		m_Server[index].m_Socket = INVALID_SOCKET;
	}
	else
	{
		LogAddC(eError, "[%s][CloseClient] :: CloseClient INVALID_SOCKET", m_Name);
	}
}
// --------------------------------------------------------

void IOCP::ResponErrorCloseClient(int index)
{
	if ((index < 0) || (index >= MAX_OBJECT))
	{
		LogAddC(eError, "[%s][ResponErrorCloseClient] :: CloseClient index error", m_Name);
		// ----
		return;
	}
	// ----
	if (m_Server[index].m_State == SS_CLOSED)
	{
		LogAddC(eError, "[%s][ResponErrorCloseClient] :: CloseClient connect error", m_Name);
		// ----
		return;
	}
	// ----
	closesocket(m_Server[index].m_Socket);
	// ----
	m_Server[index].m_Socket = INVALID_SOCKET;
	// ----
	if (m_Server[index].m_Socket == INVALID_SOCKET)
	{
		LogAddC(eError, "[%s][ResponErrorCloseClient] :: CloseClient INVALID_SOCKET", m_Name);
	}
	// ----
	ServerDel(index);
}
// --------------------------------------------------------

int IOCP::ServerAddSearch()
{
	int iReturn = -1;
	// ----
	if (m_Server == NULL)
	{
		return iReturn;
	}
	// ----
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_Server[i].m_Index == -1)
		{
			iReturn = i;
			// ----
			break;
		}
	}
	// ----
	OnSearch(iReturn);
	// ----
	return iReturn;
}
// --------------------------------------------------------

int IOCP::ServerAdd(int ServerIndex, SOCKET Socket, char * Ip)
{
	LogAddC(eConnect, "[%s] Connection is accepted [%d] [%d] [%s]", m_Name, ServerIndex, Socket, Ip);
	// ----
	memcpy(m_Server[ServerIndex].m_ServerIp, Ip, 16);
	// ----
	m_Server[ServerIndex].m_Index = ServerIndex;
	m_Server[ServerIndex].m_State = SS_CONNECTED;
	m_Server[ServerIndex].m_Socket = Socket;
	// ----
	//gSettings.ServiceActive++;
	OnConnect(ServerIndex);
	// ----
	return ServerIndex;
}
// --------------------------------------------------------

void IOCP::ServerDel(int aIndex)
{
	LogAddC(eNormal, "[%s] Connection is deleted [%d]", m_Name, aIndex);
	// ----
	m_Server[aIndex].m_Index = -1;
	m_Server[aIndex].m_Socket = INVALID_SOCKET;
	m_Server[aIndex].m_State = SS_CLOSED;
	// ----
	memset(m_Server[aIndex].m_ServerIp, 0, sizeof(m_Server[aIndex].m_ServerIp));
	// ----
	//gSettings.ServiceActive--;
	// ----
	OnDisconnect(aIndex);
}
// --------------------------------------------------------

DWORD IOCP::ListenWorker(LPVOID Param)
{
	IOCP *	lpThis = (IOCP *)Param;
	// ----
	int	ClientIndex = SOCKET_ERROR;
	SOCKET AcceptSocket = INVALID_SOCKET;
	// ----
	sockaddr_in cAddr = { 0 };
	in_addr	cInAddr = { 0 };
	int	cAddrlen = 16;
	// ----
	int	RecvBytes = 0;
	ULONG Flags = 0;
	// ----
	__try
	{
		while (true)
		{
			AcceptSocket = WSAAccept(lpThis->m_Listen, (sockaddr*)&cAddr, &cAddrlen, NULL, 0);
			// ----
			if (AcceptSocket == SOCKET_ERROR)
			{
				LogAddC(eError, "[%s][ListenWorker] :: WSAAccept() failed with error %d", lpThis->m_Name, WSAGetLastError());
				// ----
				continue;
			}
			// ----
			memcpy(&cInAddr, &cAddr.sin_addr, sizeof(cInAddr));
			// ----
			ClientIndex = lpThis->ServerAddSearch();
			// ----
			if (ClientIndex == SOCKET_ERROR)
			{
				LogAddC(eError, "[%s][ListenWorker] :: ClientIndex : SOCKET_ERROR(-1) ; MAX ACTIVE", lpThis->m_Name);
				// ----
				closesocket(AcceptSocket);
				// ----
				continue;
			}
			// ----
			if (lpThis->UpdateIOCompletionPort(AcceptSocket, ClientIndex) == false)
			{
				LogAddC(eError, "[%s][ListenWorker] :: CreateIoCompletionPort failed with error %d. Socket %d Index %d", lpThis->m_Name,
					GetLastError(), AcceptSocket, ClientIndex);
				// ----
				closesocket(AcceptSocket);
				// ----
				continue;
			}
			// ----
			if (lpThis->ServerAdd(ClientIndex, AcceptSocket, inet_ntoa(cInAddr)) == SOCKET_ERROR)
			{
				LogAddC(eError, "[%s][ListenWorker] :: CreateIoCompletionPort failed with error %d. Socket %d Index %d", lpThis->m_Name,
					GetLastError(), AcceptSocket, ClientIndex);
				// ----
				closesocket(AcceptSocket);
				// ----
				continue;
			}
			// ----
			_PER_IO_CONTEXT * IOContext0 = &lpThis->m_Server[ClientIndex].PerSocketContext->IOContext[0];
			_PER_IO_CONTEXT * IOContext1 = &lpThis->m_Server[ClientIndex].PerSocketContext->IOContext[1];
			// ----
			memset(&IOContext0->Overlapped, 0, sizeof(WSAOVERLAPPED));
			memset(&IOContext1->Overlapped, 0, sizeof(WSAOVERLAPPED));
			// ----
			IOContext0->wsabuf.buf = (char*)&IOContext0->Buffer;
			IOContext0->wsabuf.len = MAX_IO_BUFFER_SIZE;
			IOContext0->nTotalBytes = 0;
			IOContext0->nSentBytes = 0;
			IOContext0->nWaitIO = 0;
			IOContext0->nSecondOfs = 0;
			IOContext0->IOOperation = 0;
			// ----
			IOContext1->wsabuf.buf = (char*)IOContext0->Buffer;
			IOContext1->wsabuf.len = MAX_IO_BUFFER_SIZE;
			IOContext1->nTotalBytes = 0;
			IOContext1->nSentBytes = 0;
			IOContext1->nWaitIO = 0;
			IOContext1->nSecondOfs = 0;
			IOContext1->IOOperation = 1;
			// ----
			lpThis->m_Server[ClientIndex].PerSocketContext->m_socket = AcceptSocket;
			lpThis->m_Server[ClientIndex].PerSocketContext->nIndex = ClientIndex;
			// ----
			if (WSARecv(AcceptSocket, &IOContext0->wsabuf, 1, (ULONG*)& RecvBytes, &Flags,
				&IOContext0->Overlapped, NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					LogAddC(eError, "[%s][ListenWorker] :: WSARecv() failed with error %d", lpThis->m_Name, WSAGetLastError());
					// ----
					lpThis->m_Server[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 4;
					// ----
					lpThis->CloseClient(lpThis->m_Server[ClientIndex].PerSocketContext, 0);
					// ----
					continue;
				}
			}
			// ----
			lpThis->m_Server[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 1;
			lpThis->m_Server[ClientIndex].PerSocketContext->dwIOCount++;
			// ----
			lpThis->OnConnected(ClientIndex);
		}
	}
	__finally
	{
		LogAddC(eError, "__finally");
	}
	// ----
	return 1;
}
// --------------------------------------------------------

DWORD IOCP::RecvWorker(LPVOID Param)
{
	IOCP *	lpThis = (IOCP *)Param;
	BOOL bSuccess = FALSE;
	DWORD ClientIndex = SOCKET_ERROR;
	DWORD dwIoSize = 0;
	DWORD dwWSARet = 0;
	// ----
	LPOVERLAPPED lpOverlapped = { 0 };
	_PER_SOCKET_CONTEXT *lpPerSocketContext = { 0 };
	_PER_IO_CONTEXT * lpIOContext = { 0 };
	// ----
	ULONG RecvBytes = 0;
	ULONG Flags = 0;
	// ----
	while (true)
	{
		bSuccess = GetQueuedCompletionStatus(lpThis->m_hCmport, &dwIoSize, &ClientIndex, &lpOverlapped, -1); // WAIT_FOREVER
		// ----
		lpThis->m_GSync.Lock();
		// ----
		if (bSuccess == 0)
		{
			if (lpOverlapped != 0)
			{
				DWORD aError = GetLastError();
				// ----
				if ((aError != ERROR_SEM_TIMEOUT)
					&& (aError != ERROR_NETNAME_DELETED)
					&& (aError != ERROR_CONNECTION_ABORTED)
					&& (aError != ERROR_OPERATION_ABORTED))
				{
					LogAddC(eError, "[%s][RecvWorker] :: Error Thread : GetQueueCompletionStatus( %d )", lpThis->m_Name, GetLastError());
					lpThis->m_GSync.Unlock();
					// ----
					return 0;
				}
			}
		}
		// ----
		lpPerSocketContext = lpThis->m_Server[ClientIndex].PerSocketContext;
		// ----
		lpPerSocketContext->dwIOCount--;
		// ----
		if (dwIoSize == 0)
		{
			LogAddC(eError, "[%s][RecvWorker] :: Connection Closed, dwIoSize == 0 (Index:%d)", lpThis->m_Name, lpPerSocketContext->nIndex);
			lpThis->CloseClient(lpPerSocketContext, 0);
			lpThis->m_GSync.Unlock();
			// ----
			continue;
		}
		lpIOContext = (_PER_IO_CONTEXT *)lpOverlapped;
		// ----
		if (lpIOContext == 0)
		{
			lpThis->m_GSync.Unlock();
			// ----
			continue;
		}
		// ----
		if (lpIOContext->IOOperation == OP_RECV)
		{
			lpIOContext->nSentBytes += dwIoSize;
			// ----
			if (lpIOContext->nSentBytes >= lpIOContext->nTotalBytes)
			{
				lpIOContext->nWaitIO = 0;
				// ----
				if (lpIOContext->nSecondOfs > 0)
				{
					lpThis->IoSendSecond(lpPerSocketContext);
				}
			}
			else
			{
				lpThis->IoMoreSend(lpPerSocketContext);
			}
		}
		else if (lpIOContext->IOOperation == OP_SEND)
		{
			RecvBytes = 0;
			lpIOContext->nSentBytes += dwIoSize;
			// ----
			if (lpThis->RecvDataParse(lpIOContext, lpPerSocketContext->nIndex) == false)
			{
				LogAddC(eError, "[%s][RecvWorker] :: Socket Header error %d, %d", lpThis->m_Name, WSAGetLastError(), lpPerSocketContext->nIndex);
				lpThis->m_GSync.Unlock();
				// ----
				continue;
			};
			// ----
			lpIOContext->nWaitIO = 0;
			Flags = 0;
			// ----
			memset(&lpIOContext->Overlapped, 0, sizeof(WSAOVERLAPPED));
			// ----
			lpIOContext->wsabuf.len = MAX_IO_BUFFER_SIZE - lpIOContext->nSentBytes;
			lpIOContext->wsabuf.buf = (char*)&lpIOContext->Buffer[lpIOContext->nSentBytes];
			lpIOContext->IOOperation = OP_SEND;
			// ----
			dwWSARet = WSARecv(lpPerSocketContext->m_socket, &lpIOContext->wsabuf, 1, &RecvBytes, &Flags,
				&lpIOContext->Overlapped, NULL);
			// ----
			if (dwWSARet == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSA_IO_PENDING)
				{
					LogAddC(eError, "[%s][RecvWorker] :: WSARecv() failed with error %d", lpThis->m_Name, WSAGetLastError());
					// ----
					lpThis->CloseClient(lpPerSocketContext, 0);
					lpThis->m_GSync.Unlock();
					// ----
					continue;
				}
			}
			// ----
			lpPerSocketContext->dwIOCount++;
			lpIOContext->nWaitIO = 1;
		}
		// ----
		lpThis->m_GSync.Unlock();
	}
	return 1;
}
// --------------------------------------------------------