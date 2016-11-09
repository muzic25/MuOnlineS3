#include "stdafx.h"



RankingServer_Manager::RankingServer_Manager(void)
{
}


RankingServer_Manager::~RankingServer_Manager(void)
{
}


void RankingServer_Manager::OnConnect()
{
    gSettings.ServiceActive++;

    LogAddC(eConnect, "[RankingServer] Connection is accepted");
}


void RankingServer_Manager::OnDisconnect(int aIndex)
{
    gSettings.ServiceActive--;

    LogAddC(eConnect, "[RankingServer] Connection is deleted");
}


void RankingServer_Manager::OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    gRankingServer_Protocol.ProtocolCore(aIndex, HeadCode, aRecv, iSize);
}

