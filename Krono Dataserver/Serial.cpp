#include "stdafx.h"

CWzItemSerial gWzItemSerial;

CWzItemSerial::CWzItemSerial()
{
    m_dwItemSerial = 0;
    m_dwLastSerial = 0;
}

CWzItemSerial::~CWzItemSerial()
{
}

int CWzItemSerial::GetItemSerial(DWORD& sirial_number, int MakeSeiralCount)
{
    sirial_number = 0;

    gDataBase.ExecFormat("EXEC WZ_GetItemSerial2 '%d'", MakeSeiralCount);

    if( gDataBase.Fetch() == SQL_NO_DATA )
    {
        gDataBase.Clear();
        return 0;
    }

    sirial_number = (DWORD)gDataBase.GetInt64(0);
    gDataBase.Clear();
    return 1;
}

int CWzItemSerial::MakeSerial()
{
    if( GetItemSerial(m_dwItemSerial, 100) == FALSE )
    {
        LogAddC(eError, "[gWzItemSerial] Failed to get new Serial");
        return FALSE;
    }

    m_dwLastSerial = m_dwItemSerial + 100;
    return 1;
}

DWORD CWzItemSerial::GetSerial()
{
    if ( m_dwItemSerial >= m_dwLastSerial )
        MakeSerial();

    DWORD retserial = m_dwItemSerial;
    m_dwItemSerial++;

    return retserial;
}