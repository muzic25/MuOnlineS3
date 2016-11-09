#include "stdafx.h"

CFunction	gFunc;

void CFunction::BuxConvert(LPSTR Buff, int dwSize)
{
    static BYTE bBuxCode[3] = { 0xFC, 0xCF, 0xAB };

    for (int n = 0; n < dwSize; n++)
    {
        Buff[n] ^= bBuxCode[n % 3];
    }
}


bool CFunction::CheckSQLSyntex(LPSTR String)
{
    bool bReturn = true;

    for(int i = 0; i < strlen(String); ++i)
    {
        if(isalnum(String[i]) == 0)
            bReturn = false;
    }

    return bReturn;
}

void CFunction::PHeadSetW(LPBYTE lpBuf, BYTE head, int Size)
{
    lpBuf[0] = 0xC2;
    lpBuf[1] = SET_NUMBERH(Size);
    lpBuf[2] = SET_NUMBERL(Size);
    lpBuf[3] = head;
}


void CFunction::PHeadSubSetB(LPBYTE lpBuf, BYTE Head, BYTE SubHead, int Size)
{
    lpBuf[0] = 0xC1;
    lpBuf[1] = (BYTE)Size;
    lpBuf[2] = Head;
    lpBuf[3] = SubHead;
}

