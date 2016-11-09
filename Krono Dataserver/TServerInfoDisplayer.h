#pragma once

class TServerInfoDisplayer
{

public:

    TServerInfoDisplayer();
    virtual ~TServerInfoDisplayer();

    void Run(HWND hWnd);
    void CheckJSConnection(BOOL bActive) {
        this->m_bValidJSConnection = bActive;
    }
    void CheckCSConnection(BOOL bActive) {
        this->m_bValidCSConnection = bActive;
    }
    void CheckDSConnection(BOOL bActive) {
        this->m_bValidDSConnection = bActive;
    }
    void CheckEXDSConnection(BOOL bActive) {
        this->m_bValidEXDSConnection = bActive;
    }
    void CheckEVDSConnection(BOOL bActive) {
        this->m_bValidEVDSConnection = bActive;
    }
    void CheckRKDSConnection(BOOL bActive) {
        this->m_bValidRKDSConnection = bActive;
    }
    void InitGDIObject();
    void DelGDIObject();
    void PaintAllInfo(HWND hWnd, int iTopLeftX, int iTopLeftY);

private:

    BOOL m_bValidJSConnection;	// 4
    BOOL m_bValidCSConnection;	// 8
    BOOL m_bValidDSConnection;	// C
    BOOL m_bValidEXDSConnection;	// 10
    BOOL m_bValidEVDSConnection;	// 14
    BOOL m_bValidRKDSConnection;	// 18
    HFONT m_hFont;	// 1C
    HBRUSH m_hNormalBrush;	// 20
    HBRUSH m_hAbnormalBrush;	// 24
};

extern TServerInfoDisplayer g_ServerInfoDisplayer;