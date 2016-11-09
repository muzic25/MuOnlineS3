#pragma once

class DataServer_Manager: public IOCP
{
public:
    DataServer_Manager(void);
    virtual ~DataServer_Manager(void);
    void OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);
    void OnConnect();
    void OnDisconnect(int aIndex);
    void OnError(char * szMessage, ...);
    void OnMessage(char * szMessage, ...);
    void OnSearch(int aIndex);
	int gItemCount;
    LONGLONG GetPeriodLeftTime(char Date[20]);
};
extern DataServer_Manager gDataServer_Manager[];