#include "stdafx.h"

TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HINSTANCE hInst;
HWND ghWnd;

Settings				gSettings;
DataBase				gDataBase;
IOCP					gIOCP;
WzUpdateSocket			gWzUpdateSocket;
JoinServer_Manager		gJoinServer_Manager;
EventServer_Manager		gEventServer_Manager;
RankingServer_Manager	gRankingServer_Manager;
DataServer_Manager		gDataServer_Manager[];

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HACCEL hAccelTable;

    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_CougarEMU, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    InitCommonControls();

    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    CreateDirectory("LOG", NULL);
    hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CougarEMU);
    LogInit(TRUE);
    LogAddC(eLoading, "Intializing...");
    LogDateChange();
    SendMessage(ghWnd, WM_TIMER, WM_LOG_PAINT, NULL);

    gSettings.Loading(".\\Config.ini");
    gDataBase.Initialize();
    gIOCP.StartServer();

    SetTimer(ghWnd, WM_LOG_PAINT, 1000, NULL);
    SetTimer(ghWnd, WM_LOG_DATE_CHANGE, 300, NULL);
    SetWindowText(ghWnd, "KronoDS [0.0.0.2]");

    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style			= CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc	= (WNDPROC)WndProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CougarEMU);
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= (LPCSTR)IDC_CougarEMU;
    wcex.lpszClassName	= szWindowClass;
    wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    ghWnd = hWnd;

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;

    switch (message)
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_TIMER:
        switch ( wParam )
        {
        case WM_LOG_PAINT:
        {
            RECT rect;
            HDC hdc = GetDC(hWnd);
            GetClientRect(hWnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)GetStockObject(0));
            ReleaseDC(hWnd, hdc);

            if ( LogTextPaint != NULL )
                LogTextPaint(hWnd);

            g_ServerInfoDisplayer.Run(hWnd);
        }
        break;
        case WM_LOG_DATE_CHANGE:
            LogDateChange();
            break;
        }
        break;
    case WM_DESTROY:
        if( gSettings.JoinServer_Active == 1 )
            gDataBase.ExecFormat("UPDATE MEMB_STAT SET ConnectStat = 0");
        PostQuitMessage(0);
        break;
    case WM_CLOSE:
        if ( MessageBox(NULL, "Are you sure to Close?", "Confirmation", MB_YESNO|MB_ICONQUESTION) == IDYES )
        {
            if( gSettings.JoinServer_Active == 1 )
                gDataBase.ExecFormat("UPDATE MEMB_STAT SET ConnectStat = 0");
            DestroyWindow(hWnd);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}