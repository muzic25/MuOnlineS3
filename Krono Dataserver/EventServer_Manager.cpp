#include "stdafx.h"



EventServer_Manager::EventServer_Manager(void)
{
}


EventServer_Manager::~EventServer_Manager(void)
{
}


void EventServer_Manager::OnConnect()
{
    gSettings.ServiceActive++;

    LogAddC(eConnect, "[EventServer] Connection is accepted");
}


void EventServer_Manager::OnDisconnect(int aIndex)
{
    gSettings.ServiceActive--;

    LogAddC(eConnect, "[EventServer] Connection is deleted");
}


void EventServer_Manager::OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    gEventServer_Protocol.ProtocolCore(aIndex, HeadCode, aRecv, iSize);
}

