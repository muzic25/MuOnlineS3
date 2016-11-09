#ifndef IOCP_H
#define IOCP_H
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <WinSock2.h>
#include <windows.h>
#include "process.h"
#include <cstdio>
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma comment(lib, "ws2_32.lib")
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//#include "WzaTool.h"
#include "TSynchro.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define WSA_VERSION				0x22
#define MAX_OBJECT				20
#define MAX_EXSENDBUF_SIZE		7024 * 2
#define MAX_IO_BUFFER_SIZE		50000//100000
#define MAX_IO_THREAD_HANDLES	16
#define MAX_USER				(MAX_OBJECT * 1000)
#define OP_SEND 				0
#define OP_RECV 				1
#define	DWAPI					static DWORD WINAPI
#define VVOID					virtual void
#define	LPTHREAD				LPTHREAD_START_ROUTINE
#define LPPERSOCKET				_PER_SOCKET_CONTEXT * lpPerSocketContext
#define	Tsynchro				TSynchroCriticalSection
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

enum eServer_STATE
{
	SS_CLOSED,
	SS_CONNECTED,
	SS_LOGGED,
	SS_GUILD
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _OBJECT
{
	int				m_Index;
	char			m_ServerIp[16];
	// ----
	eServer_STATE	m_State;
	SOCKET			m_Socket;
	// ----
	struct _PER_SOCKET_CONTEXT * PerSocketContext;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _PER_IO_CONTEXT
{
	WSAOVERLAPPED	Overlapped;
	WSABUF			wsabuf;
	// ----
	UCHAR			Buffer[MAX_IO_BUFFER_SIZE];
	UCHAR			BufferSecond[MAX_IO_BUFFER_SIZE];
	// ----
	int				nSecondOfs;
	int				nTotalBytes;
	int				nSentBytes;
	BYTE			IOOperation;
	BYTE			nWaitIO;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _PER_SOCKET_CONTEXT
{
	int				nIndex;
	int				dwIOCount;
	// ----
	SOCKET			m_socket;
	_PER_IO_CONTEXT IOContext[2];
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class IOCP
{
private:
	Tsynchro			m_GSync;
	// ----
	_OBJECT				m_Server[MAX_OBJECT];
	// ----
	HANDLE				m_hThread[MAX_IO_THREAD_HANDLES];
	HANDLE				m_hCmport;
	UINT				m_nThreadCount;
	SOCKET				m_Listen;
	// ----
	UINT				m_nPort;
	char				m_Name[30];
public:
	IOCP();
	~IOCP();
	// ----
	void	StartServer();
	void	SetDefaultSettings();
	bool	WSAStart();
	bool	CreateIOCompletionPort();
	bool	UpdateIOCompletionPort(SOCKET sd, int ClientIndex);
	bool	CreateIOCPListenWorker();
	bool	CreateIOCPThreads(UINT NumberOfThreads);
	bool	CreateIOCPSocket();
	bool	StartNetwork(UINT NumberOfThreads);
	// ----
	bool	DataSend(int aIndex, UCHAR* lpMsg, DWORD dwSize);
	void	DataSendAll(UCHAR * lpMsg, DWORD dwSize) {
		for (int i = 0; i != MAX_OBJECT; i++) {
			DataSend(i, lpMsg, dwSize);
		}
	};
	void	CloseClient(int index);
	// ----
	int		ServerAddSearch();
	int		ServerAdd(int aIndex, SOCKET Socket, char * Ip);
	void	ServerDel(int aIndex);
	// ----
	VVOID	OnError(const char * szMessage, ...) {};
	VVOID	OnMessage(const char * szMessage, ...) {};
	VVOID	OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize) {};
	VVOID	OnSearch(int aIndex) {};
	VVOID	OnConnect(int aIndex) {};
	VVOID	OnDisconnect(int aIndex) {};
	VVOID	OnConnected(int aIndex) {};
private:
	bool	RecvDataParse(_PER_IO_CONTEXT * lpIOContext, int uIndex);
	bool	IoSendSecond(_PER_SOCKET_CONTEXT * lpPerSocketContext);
	bool	IoMoreSend(_PER_SOCKET_CONTEXT * lpPerSocketContext);
	void	CloseClient(_PER_SOCKET_CONTEXT * lpPerSocketContext, int result);
	void	ResponErrorCloseClient(int index);
	// ----
	DWAPI	ListenWorker(LPVOID Param);
	DWAPI	RecvWorker(LPVOID Param);
public:
	inline void		SetPort(UINT Port) {
		m_nPort = Port;
	};
	inline void		SetName(char * Name) {
		memset(m_Name, 0, sizeof(m_Name));
		memcpy(m_Name, Name, sizeof(m_Name));
	};
	inline SOCKET	getSocket(int aIndex) {
		return m_Server[aIndex].m_Socket;
	};
	inline bool		isConnected(int aIndex) {
		if (m_Server[aIndex].m_State > SS_CLOSED)return true;
		else return false;
	};
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _THREAD_PARM
{
	Tsynchro *	m_Sync;
	IOCP *		m_IOCP;
};
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* IOCP_H */
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------