#include "stdafx.h"

TServerInfoDisplayer g_ServerInfoDisplayer;

static char * ServerTypeText[] =
{
    "[-  Standby  -]",
    "[-  Active  -]"
};

static char * ErrorMessge[] =
{
    "0) JoinServer - Active",
    "1) CashShopServer - Active",
    "2) DataServer - Active",
    "3) ExDBServer - Active",
    "4) EventServer - Active",
    "5) RankingServer - Active"
};

TServerInfoDisplayer::TServerInfoDisplayer()
{
    this->m_bValidJSConnection = FALSE;
    this->m_bValidCSConnection = FALSE;
    this->m_bValidDSConnection = FALSE;
    this->m_bValidEXDSConnection = FALSE;
    this->m_bValidEVDSConnection = FALSE;
    this->m_bValidRKDSConnection = FALSE;

    this->InitGDIObject();
}

TServerInfoDisplayer::~TServerInfoDisplayer()
{
    this->DelGDIObject();
}

void TServerInfoDisplayer::InitGDIObject()
{
    this->m_hFont = CreateFontA(80, 0, 0, 0, FW_THIN, FALSE, TRUE, FALSE,
                                ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                DEFAULT_PITCH|FF_DONTCARE, "Times");

    this->m_hNormalBrush = CreateSolidBrush(RGB(110, 240, 120));
    this->m_hAbnormalBrush = CreateSolidBrush(RGB(105, 105, 105));
}



void TServerInfoDisplayer::DelGDIObject()
{
    DeleteObject(this->m_hFont);
    DeleteObject(this->m_hNormalBrush);
    DeleteObject(this->m_hAbnormalBrush);
}

void TServerInfoDisplayer::Run(HWND hWnd)
{
    this->PaintAllInfo(hWnd, 0, 20);
}

void TServerInfoDisplayer::PaintAllInfo(HWND hWnd, int iTopLeftX, int iTopLeftY)
{
    HDC hDC = GetDC(hWnd);
    RECT rect = {0};
    GetClientRect(hWnd, &rect);
    rect.top = 20;
    rect.bottom = 100;
    int iLineCount = 0;
    int iIndex=0;

    int iOldBkMode = SetBkMode(hDC, TRANSPARENT);

    if ( this->m_bValidJSConnection != FALSE ||
            this->m_bValidCSConnection != FALSE ||
            this->m_bValidDSConnection != FALSE ||
            this->m_bValidEXDSConnection != FALSE ||
            this->m_bValidEVDSConnection!= FALSE ||
            this->m_bValidRKDSConnection != FALSE )
    {
        FillRect(hDC, &rect, this->m_hNormalBrush);
        iIndex = 1;
    }
    else
        FillRect(hDC, &rect, this->m_hAbnormalBrush);

    if ( this->m_bValidJSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[0], strlen(ErrorMessge[0]));
        iLineCount++;
    }

    if ( this->m_bValidCSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX,  iTopLeftY+iLineCount*15, ErrorMessge[1], strlen(ErrorMessge[1]));
        iLineCount++;
    }

    if ( this->m_bValidDSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[2], strlen(ErrorMessge[2]));
        iLineCount++;
    }

    if ( this->m_bValidEXDSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[3], strlen(ErrorMessge[3]));
        iLineCount++;
    }

    if ( this->m_bValidEVDSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX,  iTopLeftY+iLineCount*15, ErrorMessge[4], strlen(ErrorMessge[4]));
        iLineCount++;
    }

    if ( this->m_bValidRKDSConnection != FALSE )
    {
        SetTextColor(hDC, RGB(0, 0, 255));
        TextOut(hDC, iTopLeftX, iTopLeftY+iLineCount*15, ErrorMessge[5], strlen(ErrorMessge[5]));
        iLineCount++;
    }

    HFONT pOldFont = (HFONT)SelectObject(hDC, this->m_hFont);
    SetTextColor(hDC, RGB(0, 0, 0));

    TextOutA(hDC, 250, 15, ServerTypeText[iIndex], strlen(ServerTypeText[iIndex]));
    SelectObject(hDC, pOldFont);
    SetBkMode(hDC, iOldBkMode);
    ReleaseDC(hWnd, hDC);
}