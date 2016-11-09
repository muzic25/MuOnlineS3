#pragma once



class RankingServer_Manager : public IOCP
{
public:
    RankingServer_Manager(void);
    virtual ~RankingServer_Manager(void);

    void OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize);
    void OnConnect();
    void OnDisconnect(int aIndex);
};
extern RankingServer_Manager gRankingServer_Manager;

