#pragma once


class JoinServer_Manager : public IOCP
{
public:
    JoinServer_Manager(void);
    virtual ~JoinServer_Manager(void);

    void			Initialize();

    void			OnConnect();
    void			OnDisconnect(int aIndex);
    void			OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);

    void			DelServer(int ServerCode);
    void			DelUserByIndex(int nIndex, int MembGUID);

    int				AddUser(int ServerIndex, char * szAccountID, char * szIP, __int16 nNumber, int MembGUID);
    bool			CheckUser(const char * szAccountID);
    bool			IsCodeNotExist(int ServerCode);
    bool			AddServer(int ServerIndex, int ServerCode, char * szServerName, int Port);

    int				GetUserIndexByID(const char * szAccountID);

    tagSERVER_DATA	m_ServObj[MAX_OBJECT];
    tagUSER_DATA	m_UserObj[MAX_USER];
};
extern JoinServer_Manager gJoinServer_Manager;