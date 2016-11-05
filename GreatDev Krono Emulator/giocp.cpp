#include "StdAfx.h"
#include "giocp.h"

HANDLE g_CompletionPort;
DWORD g_dwThreadCount;
enum SOCKET_FLAG;
CRITICAL_SECTION criti;
HANDLE g_ThreadHandles[MAX_IO_THREAD_HANDLES];
int g_ServerPort;
HANDLE g_IocpThreadHandle;
unsigned char* ExSendBuf;

SOCKET g_Listen = INVALID_SOCKET;	// THIS IS NOT THE PLACE OF TTHIS VARIABLE

void GiocpInit()
{
	ExSendBuf=new unsigned char[MAX_EXSENDBUF_SIZE];
}

void GiocpDelete()
{
	delete[] ExSendBuf;
}


BOOL CreateGIocp(int server_port)
{
	unsigned long ThreadID;
	
	g_ServerPort=server_port;

	g_IocpThreadHandle=CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)IocpServerWorker, NULL, 0, &ThreadID);

	if ( g_IocpThreadHandle == 0 )
	{
		LogAdd("CreateThread() failed with error %d", GetLastError());
		return 0;
	}
	else
	{
		return 1;
	}

	
	
}


void DestroyGIocp()
{
//#ifndef HIDE_ERRORL10
	LogAddTD("Error-L10");
//#endif
	return; // DESTROY FIX
	closesocket(g_Listen);

	for (DWORD dwCPU=0; dwCPU < g_dwThreadCount;dwCPU++ )
	{
		TerminateThread( g_ThreadHandles[dwCPU] , 0);
	}

	TerminateThread(g_IocpThreadHandle, 0);

	if ( g_CompletionPort != NULL )
	{
		CloseHandle(g_CompletionPort);
		g_CompletionPort=NULL;
	} 
	
}


int CreateListenSocket()
{
	sockaddr_in InternetAddr;
	int nRet;

	g_Listen=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if ( g_Listen == -1 )
	{
		LogAdd("WSASocket() failed with error %d", WSAGetLastError() );
		return 0;
	}
	else
	{
		InternetAddr.sin_family=AF_INET;
		InternetAddr.sin_addr.S_un.S_addr=htonl(0);
		InternetAddr.sin_port=htons(g_ServerPort);
		nRet=bind(g_Listen, (sockaddr*)&InternetAddr, 16);
		
		if ( nRet == -1 )
		{
			MsgBox(lMsg.Get(MSGGET(2, 55)));
			SendMessage(ghWnd, WM_CLOSE, 0,0);	// Kill aplication
			return 0 ;
		}
		else
		{
			nRet=listen(g_Listen, 5);
			if (nRet == -1)
			{
				LogAdd("listen() failed with error %d", WSAGetLastError());
				return 0;
			}
			else
			{
				return 1;
			}
		}
	} 
}


unsigned long __stdcall IocpServerWorker(void * p)
{
	SYSTEM_INFO SystemInfo;
	DWORD ThreadID;
	SOCKET Accept;
	int nRet;
	int ClientIndex;
	sockaddr_in cAddr;
	in_addr cInAddr;
	int cAddrlen;
	_PER_SOCKET_CONTEXT * lpPerSocketContext;
	int RecvBytes;
	unsigned long Flags;
	
	


	cAddrlen=16;
	lpPerSocketContext=0;
	Flags=0;

	InitializeCriticalSection(&criti);
	GetSystemInfo(&SystemInfo);

	g_dwThreadCount = SystemInfo.dwNumberOfProcessors * 2;
	__try
	{

		g_CompletionPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

		if ( g_CompletionPort == NULL )
		{
			LogAdd("CreateIoCompletionPort failed with error: %d", GetLastError());
			__leave;
		}

		for ( DWORD n = 0; n<g_dwThreadCount; n++ )
		{
			

			HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ServerWorkerThread, g_CompletionPort, 0, &ThreadID);

			if ( hThread == 0 )
			{
				LogAdd("CreateThread() failed with error %d", GetLastError() );
				__leave;
			}

			g_ThreadHandles[n] = hThread;

			CloseHandle(hThread);
		}

		if ( CreateListenSocket() == 0 )
		{

		}
		else
		{
			while ( true )
			{
				Accept = WSAAccept(g_Listen, (sockaddr*)&cAddr, &cAddrlen, NULL, 0 );

				if ( Accept == -1 )
				{
					EnterCriticalSection(&criti);
					LogAdd("WSAAccept() failed with error %d", WSAGetLastError() );
					LeaveCriticalSection(&criti);
					continue;
				}

				EnterCriticalSection(&criti);
				memcpy(&cInAddr, &cAddr.sin_addr  , sizeof(cInAddr) );

				ClientIndex = gObjAddSearch(Accept, inet_ntoa(cInAddr) );

				if ( ClientIndex == -1 )
				{
					LogAddL("error-L2 : ClientIndex = -1");
					closesocket(Accept);
					LeaveCriticalSection(&criti);
					continue;
				}

				if (UpdateCompletionPort(Accept, ClientIndex, 1) == 0 )
				{
					LogAddL("error-L1 : %d %d CreateIoCompletionPort failed with error %d", Accept, ClientIndex, GetLastError() );
					closesocket(Accept);
					LeaveCriticalSection(&criti);
					continue;
				}

				if (gObjAdd(Accept, inet_ntoa(cInAddr), ClientIndex) == -1 )
				{
					LogAddL("error-L1 : %d %d gObjAdd() failed with error %d", Accept, ClientIndex, GetLastError() );
					LeaveCriticalSection(&criti);
					closesocket(Accept);
					continue;
				}
				
				memset(&gObj[ClientIndex].PerSocketContext->IOContext[0].Overlapped, 0, sizeof(WSAOVERLAPPED));
				memset(&gObj[ClientIndex].PerSocketContext->IOContext[1].Overlapped, 0, sizeof(WSAOVERLAPPED));

				gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf.buf = (char*)&gObj[ClientIndex].PerSocketContext->IOContext[0].Buffer;
				gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf.len = MAX_IO_BUFFER_SIZE;
				gObj[ClientIndex].PerSocketContext->IOContext[0].nTotalBytes = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[0].nSentBytes = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[0].nSecondOfs = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[0].IOOperation = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[1].wsabuf.buf = (char*)gObj[ClientIndex].PerSocketContext->IOContext[0].Buffer;
				gObj[ClientIndex].PerSocketContext->IOContext[1].wsabuf.len = MAX_IO_BUFFER_SIZE;
				gObj[ClientIndex].PerSocketContext->IOContext[1].nTotalBytes = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[1].nSentBytes = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[1].nWaitIO = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[1].nSecondOfs = 0;
				gObj[ClientIndex].PerSocketContext->IOContext[1].IOOperation = 1;
				gObj[ClientIndex].PerSocketContext->m_socket = Accept;
				gObj[ClientIndex].PerSocketContext->nIndex = ClientIndex;

				nRet = WSARecv(Accept, &gObj[ClientIndex].PerSocketContext->IOContext[0].wsabuf , 1, (unsigned long*)&RecvBytes, &Flags, 
						&gObj[ClientIndex].PerSocketContext->IOContext[0].Overlapped, NULL);

				if ( nRet == -1 )
				{
					if ( WSAGetLastError() != WSA_IO_PENDING )
					{
						LogAddL("error-L1 : WSARecv() failed with error %d", WSAGetLastError() );
						gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO = 4;
						CloseClient(gObj[ClientIndex].PerSocketContext, 0);
						LeaveCriticalSection(&criti);
						continue;
					}
				}

				gObj[ClientIndex].PerSocketContext->IOContext[0].nWaitIO  = 1;
				gObj[ClientIndex].PerSocketContext->dwIOCount++;

				LeaveCriticalSection(&criti);
				SCPJoinResultSend(ClientIndex, 1);
			}


		}
	}
	__finally
	{
		
		if ( g_CompletionPort != NULL )
		{
			for ( int i = 0 ; i < g_dwThreadCount ; i++ )
			{
				PostQueuedCompletionStatus( g_CompletionPort , 0, 0, 0);
			}
		}

		if ( g_CompletionPort != NULL )
		{
			CloseHandle(g_CompletionPort);
			g_CompletionPort = NULL;
		}
		if ( g_Listen != INVALID_SOCKET )
		{
			closesocket( g_Listen);
			g_Listen = INVALID_SOCKET;
		}
	}

	return 1;
		
}


unsigned long __stdcall ServerWorkerThread(HANDLE CompletionPortID)
{
	HANDLE CompletionPort;
	DWORD dwIoSize;
	unsigned long RecvBytes;
	unsigned long Flags;
	DWORD dwSendNumBytes;
	BOOL bSuccess;
	int nRet;
	DWORD ClientIndex;
	_PER_SOCKET_CONTEXT * lpPerSocketContext;
	LPOVERLAPPED lpOverlapped;
	_PER_IO_CONTEXT * lpIOContext;
	
	

	CompletionPort=CompletionPortID;
	dwSendNumBytes=0;
	bSuccess=0;
	lpPerSocketContext=0;
	lpOverlapped=0;
	lpIOContext=0;
	
	while ( true )
	{
		bSuccess=GetQueuedCompletionStatus( CompletionPort, &dwIoSize, &ClientIndex, &lpOverlapped, -1); // WAIT_FOREVER

		if (bSuccess == 0)
		{
			if (lpOverlapped != 0)
			{
				int aError = GetLastError();
				if ( (aError != ERROR_NETNAME_DELETED) && (aError != ERROR_CONNECTION_ABORTED) && (aError != ERROR_OPERATION_ABORTED) )
				{
					EnterCriticalSection(&criti);
					LogAdd("Error Thread : GetQueueCompletionStatus( %d )", GetLastError());
					LeaveCriticalSection(&criti);
					return 0;
				}
			}
		}

		EnterCriticalSection(&criti);

		lpPerSocketContext=gObj[ClientIndex].PerSocketContext;
		lpPerSocketContext->dwIOCount --;
				
		if ( dwIoSize == 0 )
		{
			LogAdd("Connection Closed, dwIoSize == 0 (Index:%d)", lpPerSocketContext->nIndex);
			CloseClient(lpPerSocketContext, 0);
			LeaveCriticalSection(&criti);
			continue;
		}

		lpIOContext = (_PER_IO_CONTEXT *)lpOverlapped;

		if ( lpIOContext == 0 )
		{
			continue;
		}

		if ( lpIOContext->IOOperation == 1 )
		{
			lpIOContext->nSentBytes += dwIoSize;


			if ( lpIOContext->nSentBytes >= lpIOContext->nTotalBytes )
			{
				lpIOContext->nWaitIO = 0;
						
				if ( lpIOContext->nSecondOfs > 0)
				{
					IoSendSecond(lpPerSocketContext);
				}
			}
			else
			{
				IoMoreSend(lpPerSocketContext);
			}
			
		}
		else if ( lpIOContext->IOOperation == 0 )
		{
			RecvBytes = 0;
			lpIOContext->nSentBytes += dwIoSize;

			if ( RecvDataParse(lpIOContext, lpPerSocketContext->nIndex ) == 0 )
			{
				LogAdd("error-L1 : Socket Header error %d, %d", WSAGetLastError(), lpPerSocketContext->nIndex);
				CloseClient(lpPerSocketContext, 0);
				LeaveCriticalSection(&criti);
				continue;
			}

			lpIOContext->nWaitIO = 0;
			Flags = 0;
			memset(&lpIOContext->Overlapped, 0, sizeof (WSAOVERLAPPED));
			lpIOContext->wsabuf.len = MAX_IO_BUFFER_SIZE - lpIOContext->nSentBytes;
			lpIOContext->wsabuf.buf = (char*)&lpIOContext->Buffer[lpIOContext->nSentBytes];
			lpIOContext->IOOperation = 0;

			nRet = WSARecv(lpPerSocketContext->m_socket, &lpIOContext->wsabuf, 1, &RecvBytes, &Flags,
						&lpIOContext->Overlapped, NULL);

			if ( nRet == -1 )
			{
				if ( WSAGetLastError() != WSA_IO_PENDING)
				{
					LogAdd("WSARecv() failed with error %d", WSAGetLastError() );
					CloseClient(lpPerSocketContext, 0);
					LeaveCriticalSection(&criti);
					continue;
				}
			}

			lpPerSocketContext->dwIOCount ++;
			lpIOContext->nWaitIO = 1;
		}
		LeaveCriticalSection(&criti);
		

	}


	return 1;
}



BOOL RecvDataParse(_PER_IO_CONTEXT * lpIOContext, int uIndex)	
{
	unsigned char* recvbuf;
	int lOfs;
	int size;
	BYTE headcode;
	BYTE xcode;

	// Check If Recv Data has More thatn 3 BYTES
	if ( lpIOContext->nSentBytes < 3 )
	{
		return TRUE;
	}

	// Initialize Variables
	lOfs=0;
	size=0;
	xcode=0;
	recvbuf = lpIOContext->Buffer;

	unsigned char byDec[7024];
	
	// Start Loop
	while ( true )
	{
		
		
		// Select packets with
		// C1 or C2 as HEader
		if ( recvbuf[lOfs] == 0xC1 ||
			 recvbuf[lOfs] == 0xC3 )
		{
			unsigned char * pBuf;

			// Set Local Var to save values from
			// Cryps
			// th C1 and C3
			pBuf = &recvbuf[lOfs];
			size = pBuf[1];
			headcode = pBuf[2];
			xcode = recvbuf[lOfs];
		}
		else if ( recvbuf[lOfs] == 0xC2 ||
			      recvbuf[lOfs] == 0xC4 )
		{
			unsigned char * pBuf;

			// Set Local Var to save values from
			// Cryps
			// th C2 and C4
			pBuf = &recvbuf[lOfs];
			size = pBuf[1] * 256;
			size |= pBuf[2];
			headcode = pBuf[3];
			xcode = recvbuf[lOfs];
		}
		// If HEader Differs
		else
		{
			LogAdd("error-L1 : Header error (%s %d)lOfs:%d, size:%d",
											__FILE__, __LINE__,
											lOfs,
											lpIOContext->nSentBytes);

			lpIOContext->nSentBytes = 0;
			return false;
		}

		// Check Size is leess thant 0
		if ( size <= 0 )
		{
			LogAdd("error-L1 : size %d",
				size);

			return false;
		}

		// Check if Size is On Range
		if ( size <= lpIOContext->nSentBytes )
		{
			// Case C3 type
			if ( xcode == 0xC3 )
			{

				// Decrypt Packet
				int ret = g_SimpleModulusCS.Decrypt( &byDec[2],
													&recvbuf[lOfs+2],
													size-2);

				// Case if ret BYTE is Less thant ZERO
				if ( ret < 0 )
				{

				}
				else
				{
					unsigned char* pDecBuf = &byDec[1];
					
					// Set Local Var 
					// Accoirding Recv Buffer
					headcode = pDecBuf[2];
					BYTE subhead = byDec[2];
					byDec[1] = 0xC1;
					byDec[2] = (ret&0xFF)+2;

					// Initialize PAcket Stream
					CStreamPacketEngine_Server PacketStream;

					// Clear Packet Stream
					PacketStream.Clear();

					// Add Data PAckte Stream
					if ( PacketStream.AddData(&byDec[1], ret +2) == 0 )
					{

						LogAddC(2, "error-L1 : CStreamPacketEngine Adding Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
							gObj[uIndex].Ip_addr,
							gObj[uIndex].AccountID, gObj[uIndex].Name,
							headcode,
							__FILE__, __LINE__,
							gObj[uIndex].Connected);
						//PacketStream.~CStreamPacketEngine_Server();
						return 0;
					}

					if ( PacketStream.ExtractPacket(byDec) != 0 )
					{
						LogAddC(2, "error-L1 : CStreamPacketEngine ExtractPacket Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
							gObj[uIndex].Ip_addr, gObj[uIndex].AccountID, gObj[uIndex].Name, headcode, __FILE__, __LINE__, gObj[uIndex].Connected);
						//PacketStream.~CStreamPacketEngine_Server();
						return 0;
					}

					if ( xcode == 0xC3 && headcode == 0xC5 )
					{
						LogAdd("암호패킷 : [0x%x]" , headcode); // Wrong Password
					}
	
					ProtocolCore(headcode, byDec, ret, uIndex, 1, subhead);
					//return;
				}
			}

			else if ( xcode == 0xC4 )
			{
				int ret = g_SimpleModulusCS.Decrypt(&byDec[3], &recvbuf[lOfs+3], size-3);
				if ( ret < 0 )
				{

				}
				else
				{
					unsigned char* pDecBuf = &byDec[1];
					
					
					BYTE hcode = byDec[3];
					byDec[1] = 0xC2;
					WORD size = (ret &0xFFFF)+3;
					byDec[2] = SET_NUMBERH(size);
					byDec[3] = SET_NUMBERL(size); 
					CStreamPacketEngine_Server PacketStream;

					PacketStream.Clear();
					if ( PacketStream.AddData(&byDec[1], ret+3) == 0 )
					{
						LogAddC(2, "error-L1 : CStreamPacketEngine Adding Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
							gObj[uIndex].Ip_addr, gObj[uIndex].AccountID, gObj[uIndex].Name, headcode, __FILE__, __LINE__, gObj[uIndex].Connected);
						//PacketStream.~CStreamPacketEngine_Server();
						return 0;
					}

					if ( PacketStream.ExtractPacket(byDec) != 0 )
					{
						LogAddC(2, "error-L1 : CStreamPacketEngine ExtractPacket Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
							gObj[uIndex].Ip_addr, gObj[uIndex].AccountID, gObj[uIndex].Name, headcode, __FILE__, __LINE__, gObj[uIndex].Connected);
						//PacketStream.~CStreamPacketEngine_Server();
						return 0;
					}
					headcode = pDecBuf[2];
					if ( xcode == 0xC4 && headcode == 0xC5 )
					{
						LogAdd("암호패킷 : [0x%x]" , headcode); // Wrong Password
					}
	
					ProtocolCore(headcode, byDec, ret, uIndex, 1, hcode);
					//continue;
				}
			}
			else
			{
				CStreamPacketEngine_Server ps;
				ps.Clear();
				
				if ( ps.AddData(&recvbuf[lOfs], size) == 0 )
				{
					LogAddC(2, "error-L1 : CStreamPacketEngine Adding Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
						gObj[uIndex].Ip_addr, gObj[uIndex].AccountID, gObj[uIndex].Name, headcode, __FILE__, __LINE__, gObj[uIndex].Connected);
					return 0;
				}

				if ( ps.ExtractPacket(byDec) != 0 )
				{
					LogAddC(2, "error-L1 : CStreamPacketEngine ExtractPacket Error : ip = %s account:%s name:%s HEAD:%x (%s,%d) State:%d",
						gObj[uIndex].Ip_addr, gObj[uIndex].AccountID, gObj[uIndex].Name, headcode, __FILE__, __LINE__, gObj[uIndex].Connected);
					return 0;
				}

				ProtocolCore(headcode, byDec, size, uIndex, 0, -1);
			}

			lOfs += size;
			lpIOContext->nSentBytes  -= size;

			if ( lpIOContext->nSentBytes <= 0 )
			{
				break;
			}
		}
		else if ( lOfs > 0 )
		{
			if ( lpIOContext->nSentBytes < 1 )
			{
				LogAdd("error-L1 : recvbuflen 1 %s %d", __FILE__, __LINE__);
				break;
			}

			if ( lpIOContext->nSentBytes < MAX_IO_BUFFER_SIZE ) 
			{
				memcpy(recvbuf, &recvbuf[lOfs], lpIOContext->nSentBytes);
				LogAdd("Message copy %d", lpIOContext->nSentBytes);
				//break;
			}
			break;
		
		}
		else
		{
			break;
		}
		
	}

	return true;
}











BOOL DataSend(int aIndex, unsigned char* lpMsg, DWORD dwSize)
{
	unsigned long SendBytes;
	_PER_SOCKET_CONTEXT * lpPerSocketContext;
	unsigned char * SendBuf;
	

	if ( aIndex < OBJ_STARTUSERINDEX )
	{
		return true;
	}

	EnterCriticalSection(&criti);

	if ( ((aIndex < 0)? FALSE : (aIndex > OBJMAX-1)? FALSE : TRUE )  == FALSE )
	{
		LogAdd("error-L2 : Index(%d) %x %x %x ", dwSize, lpMsg[0], lpMsg[1], lpMsg[2]);
		LeaveCriticalSection(&criti);
		return false;
	}

	if ( lpMsg[0] == 0xC3 || lpMsg[0] == 0xC4 )
	{
		int ret;
		BYTE btsize;

		if ( lpMsg[0] == 0xC3 )
		{
			btsize = lpMsg[1];
			lpMsg[1]=gNSerialCheck[aIndex].GetSendSerial();

			ret = g_SimpleModulusSC.Encrypt(&ExSendBuf[2], &lpMsg[1], dwSize-1);
			ExSendBuf[0] = 0xC3;
			ExSendBuf[1] = ret + 2;
			SendBuf = ExSendBuf;
			dwSize = ret + 2;
			lpMsg[1] = btsize;
		}
		else
		{
			btsize = lpMsg[2];
			lpMsg[2] = gNSerialCheck[aIndex].GetSendSerial();
			ret = g_SimpleModulusSC.Encrypt(&ExSendBuf[3], &lpMsg[2], dwSize-2);
			ExSendBuf[0] = 0xC4;
			ExSendBuf[1] = SET_NUMBERH(ret +3 );
			ExSendBuf[2] = SET_NUMBERL(ret+3);
			SendBuf = ExSendBuf;
			dwSize = ret + 3;
			lpMsg[2] = btsize;
		}
	}
	else
	{
		SendBuf = lpMsg;
	}

	if ( gObj[aIndex].Connected < PLAYER_CONNECTED )
	{
		LeaveCriticalSection(&criti);
		return FALSE;
	}

	lpPerSocketContext= gObj[aIndex].PerSocketContext;

	if ( dwSize > sizeof(lpPerSocketContext->IOContext[0].Buffer))
	{
		LogAdd("Error : Max msg(%d) %s %d", dwSize, __FILE__, __LINE__);
		CloseClient(aIndex);
		LeaveCriticalSection(&criti);
		return false;
	}

	_PER_IO_CONTEXT  * lpIoCtxt;

	lpIoCtxt = &lpPerSocketContext->IOContext[1];

	if ( lpIoCtxt->nWaitIO > 0 )
	{
		if ( ( lpIoCtxt->nSecondOfs + dwSize ) > MAX_IO_BUFFER_SIZE-1 )
		{
			LogAdd("(%d)error-L2 MAX BUFFER OVER %d %d %d [%s][%s]", aIndex, lpIoCtxt->nTotalBytes, lpIoCtxt->nSecondOfs, dwSize, gObj[aIndex].AccountID, gObj[aIndex].Name);
			lpIoCtxt->nWaitIO = 0;
			CloseClient(aIndex);
			LeaveCriticalSection(&criti);
			return true;
		}

		memcpy( &lpIoCtxt->BufferSecond[lpIoCtxt->nSecondOfs], SendBuf, dwSize);
		lpIoCtxt->nSecondOfs += dwSize;
		LeaveCriticalSection(&criti);
		return true;
	}

	lpIoCtxt->nTotalBytes = 0;
	
	if ( lpIoCtxt->nSecondOfs > 0 )
	{
		memcpy(lpIoCtxt->Buffer, lpIoCtxt->BufferSecond, lpIoCtxt->nSecondOfs);
		lpIoCtxt->nTotalBytes = lpIoCtxt->nSecondOfs;
		lpIoCtxt->nSecondOfs = 0;
	}

	if ( (lpIoCtxt->nTotalBytes+dwSize) > MAX_IO_BUFFER_SIZE-1 )
	{
		LogAdd("(%d)error-L2 MAX BUFFER OVER %d %d [%s][%s]", aIndex, lpIoCtxt->nTotalBytes, dwSize, gObj[aIndex].AccountID, gObj[aIndex].Name);
		lpIoCtxt->nWaitIO = 0;
		CloseClient(aIndex);
		LeaveCriticalSection(&criti);
		return FALSE;
	}

	memcpy( &lpIoCtxt->Buffer[lpIoCtxt->nTotalBytes], SendBuf, dwSize);
	lpIoCtxt->nTotalBytes += dwSize;
	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer;
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes;
	lpIoCtxt->nSentBytes = 0;
	lpIoCtxt->IOOperation = 1;
	

	if ( WSASend( gObj[aIndex].m_socket, &lpIoCtxt->wsabuf , 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == -1 )
	{

		if ( WSAGetLastError() != WSA_IO_PENDING )	
		{
			lpIoCtxt->nWaitIO = 0;
			

			if ( lpIoCtxt->wsabuf.buf[0] == 0xC1 )
			{
				LogAdd("(%d)WSASend(%d) failed with error [%x][%x] %d %s ", __LINE__, aIndex, (BYTE)lpIoCtxt->wsabuf.buf[0],
					(BYTE)lpIoCtxt->wsabuf.buf[2], WSAGetLastError(), gObj[aIndex].Ip_addr);
			}
			else if ( lpIoCtxt->wsabuf.buf[0] == 0xC2 )
			{
				LogAdd("(%d)WSASend(%d) failed with error [%x][%x] %d %s ", __LINE__, aIndex, (BYTE)lpIoCtxt->wsabuf.buf[0],
					(BYTE)lpIoCtxt->wsabuf.buf[3], WSAGetLastError(), gObj[aIndex].Ip_addr);
			}
			CloseClient(aIndex);
			LeaveCriticalSection(&criti);
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount ++;
	}
	
	
	lpIoCtxt->nWaitIO = 1;
	LeaveCriticalSection(&criti);
	return true;
}





BOOL IoSendSecond(_PER_SOCKET_CONTEXT * lpPerSocketContext)
{
	unsigned long SendBytes;
	int aIndex;
	_PER_IO_CONTEXT * lpIoCtxt;

	EnterCriticalSection(&criti);
	aIndex = lpPerSocketContext->nIndex;
	lpIoCtxt = &lpPerSocketContext->IOContext[1];

	if ( lpIoCtxt->nWaitIO > 0 )
	{
		LeaveCriticalSection(&criti);
		return false;
	}

	lpIoCtxt->nTotalBytes = 0;
	if ( lpIoCtxt->nSecondOfs > 0 )
	{
		memcpy(lpIoCtxt->Buffer, lpIoCtxt->BufferSecond, lpIoCtxt->nSecondOfs);
		lpIoCtxt->nTotalBytes = lpIoCtxt->nSecondOfs;
		lpIoCtxt->nSecondOfs = 0;
	}
	else
	{
		LeaveCriticalSection(&criti);
		return false;
	}

	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer;
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes;
	lpIoCtxt->nSentBytes = 0;
	lpIoCtxt->IOOperation = 1;

	if ( WSASend(gObj[aIndex].m_socket, &lpIoCtxt->wsabuf, 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == -1 )
	{
		if ( WSAGetLastError() != WSA_IO_PENDING )
		{
			LogAdd("WSASend(%d) failed with error %d %s ", __LINE__, WSAGetLastError(), gObj[aIndex].Ip_addr);
			CloseClient(aIndex);
			LeaveCriticalSection(&criti);
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount ++;
	}
	
	lpIoCtxt->nWaitIO = 1;
	LeaveCriticalSection(&criti);
	
	return true;
}


BOOL IoMoreSend(_PER_SOCKET_CONTEXT * lpPerSocketContext)
{
	unsigned long SendBytes;
	int aIndex;
	_PER_IO_CONTEXT * lpIoCtxt;

	EnterCriticalSection(&criti);
	aIndex = lpPerSocketContext->nIndex;
	lpIoCtxt = &lpPerSocketContext->IOContext[1];

	if ( (lpIoCtxt->nTotalBytes - lpIoCtxt->nSentBytes) < 0 )
	{
		LeaveCriticalSection(&criti);
		return false;
	}

	lpIoCtxt->wsabuf.buf = (char*)&lpIoCtxt->Buffer[lpIoCtxt->nSentBytes];
	lpIoCtxt->wsabuf.len = lpIoCtxt->nTotalBytes - lpIoCtxt->nSentBytes;
	lpIoCtxt->IOOperation = 1;

	if ( WSASend(gObj[aIndex].m_socket, &lpIoCtxt->wsabuf, 1, &SendBytes, 0, &lpIoCtxt->Overlapped, NULL) == -1 )
	{
		if ( WSAGetLastError() != WSA_IO_PENDING )
		{
			LogAdd("WSASend(%d) failed with error %d %s ", __LINE__, WSAGetLastError(), gObj[aIndex].Ip_addr);
			CloseClient(aIndex);
			LeaveCriticalSection(&criti);
			return false;
		}
	}
	else
	{
		lpPerSocketContext->dwIOCount ++;
	}
	
	
	lpIoCtxt->nWaitIO = 1;
	LeaveCriticalSection(&criti);
	return true;
}


BOOL UpdateCompletionPort(SOCKET sd, int ClientIndex, BOOL bAddToList)
{
	_PER_SOCKET_CONTEXT * lpPerSocketContext = NULL;

	HANDLE cp = CreateIoCompletionPort((HANDLE) sd, g_CompletionPort, ClientIndex, 0);

	if ( cp == 0 )
	{
		LogAdd("CreateIoCompletionPort: %d", GetLastError() );
		return FALSE;
	}

	gObj[ClientIndex].PerSocketContext->dwIOCount = 0;
	return TRUE;
}


void CloseClient(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result)
{
	int index = -1;
	index = lpPerSocketContext->nIndex ;

	if ( index >= OBJ_STARTUSERINDEX && index < OBJMAX )
	{
		if ( gObj[index].m_socket != INVALID_SOCKET )
		{
			if (closesocket(gObj[index].m_socket) == -1 )
			{
				if ( WSAGetLastError() != WSAENOTSOCK )
				{
					return;
				}
			}

			gObj[index].m_socket = INVALID_SOCKET;
		}

		gObjDel(index);
	}
}



void CloseClient(int index)
{
	if ( index < 0 || index > OBJMAX-1 )
	{
		LogAdd("error-L1 : CloseClient index error");
		return;
	}

	if ( gObj[index].Connected == PLAYER_EMPTY )
	{
		LogAdd("error-L1 : CloseClient connect error");
		return;
	}

	EnterCriticalSection(&criti);

	if ( gObj[index].m_socket != INVALID_SOCKET )
	{
		closesocket(gObj[index].m_socket );
		gObj[index].m_socket = INVALID_SOCKET;
	}
	else
	{
		LogAdd("error-L1 : CloseClient INVALID_SOCKET");
	}

	LeaveCriticalSection(&criti);
}

void ResponErrorCloseClient(int index)
{
	if ( index < 0 || index > OBJMAX-1 )
	{
		LogAdd("error-L1 : CloseClient index error");
		return;
	}

	if ( gObj[index].Connected == PLAYER_EMPTY )
	{
		LogAdd("error-L1 : CloseClient connect error");
		return;
	}

	EnterCriticalSection(&criti);
	closesocket(gObj[index].m_socket);
	gObj[index].m_socket = INVALID_SOCKET;

	if ( gObj[index].m_socket == INVALID_SOCKET )
	{
		LogAdd("error-L1 : CloseClient INVALID_SOCKET");
	}

	gObjDel(index);
	LeaveCriticalSection(&criti);
}
