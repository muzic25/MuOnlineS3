#pragma once


class CFunction
{
public:
    void	BuxConvert(LPSTR Buff, int dwSize);
    bool	CheckSQLSyntex(LPSTR String);
    void	PHeadSetW(LPBYTE lpBuf, BYTE Head, int Size);
    void	PHeadSubSetB(LPBYTE lpBuf, BYTE Head, BYTE SubHead, int Size);
};
extern CFunction gFunc;

