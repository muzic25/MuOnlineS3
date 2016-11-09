#pragma once

class CWzItemSerial
{
public:
    CWzItemSerial();
    virtual ~CWzItemSerial();

    int GetItemSerial(DWORD& sirial_number, int MakeSeiralCount);
    int MakeSerial();
    DWORD GetSerial();

public:
    DWORD m_dwItemSerial;
    DWORD m_dwLastSerial;
};

extern CWzItemSerial gWzItemSerial;