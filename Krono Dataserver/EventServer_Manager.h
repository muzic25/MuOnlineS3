#pragma once



class EventServer_Manager : public IOCP
{
public:
    EventServer_Manager(void);
    virtual ~EventServer_Manager(void);

    void OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);
    void OnConnect();
    void OnDisconnect(int aIndex);
};
extern EventServer_Manager gEventServer_Manager;

