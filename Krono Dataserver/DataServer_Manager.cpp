#include "stdafx.h"

DataServer_Manager::DataServer_Manager(void)
{
}

DataServer_Manager::~DataServer_Manager(void)
{
}

void DataServer_Manager::OnError(char * szMessage, ...)
{
}

void DataServer_Manager::OnMessage(char * szMessage, ...)
{

}

void DataServer_Manager::OnSearch(int aIndex)
{

}

void DataServer_Manager::OnConnect()
{
    gSettings.ServiceActive++;
    LogAddC(eConnect, "[DataServer] Connection is accepted");
}

void DataServer_Manager::OnDisconnect(int aIndex)
{
    gSettings.ServiceActive--;
    LogAddC(eConnect, "[DataServer] Connection is deleted");
}

void DataServer_Manager::OnRecv(int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    gDataServer_Protocol.ProtocolCore(this, aIndex, HeadCode , aRecv , iSize);
}

LONGLONG DataServer_Manager::GetPeriodLeftTime(char Date[20])
{
    int YearBuff = 0;
    int MonthBuff = 0;
    int DayBuff = 0;
    int HourBuff = 0;
    int MinuteBuff = 0;

    SYSTEMTIME t = {0};
    GetLocalTime(&t);

    sscanf(Date, "%d-%d-%d %d:%d", &YearBuff, &MonthBuff, &DayBuff, &HourBuff, &MinuteBuff);

    CTime ExpireDate(YearBuff, MonthBuff, DayBuff, HourBuff, MinuteBuff, 0);
    CTime CurrentDate(t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, 0);

    CTimeSpan LeftTimeSpan = ExpireDate - CurrentDate;
    LONGLONG LeftTime = LeftTimeSpan.GetTotalMinutes();

    if( LeftTime <= 0 )
        return 0;
    else
        return LeftTime;
}