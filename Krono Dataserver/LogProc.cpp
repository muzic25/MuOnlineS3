#include "stdafx.h"

static char m_szLogFileName[256] ="";
static FILE *	logfp=NULL;

#define MAXLOGTEXT		30
#define MAXLOGTEXTC		80

char  LogText[MAXLOGTEXT][MAXLOGTEXTC] = {0};
short LogTextLength[MAXLOGTEXT] = {0};
BYTE  LogTextViewType[MAXLOGTEXT] = {0};

int   gLogOutType		= 1;

void LogAddFuncVoid(char *szlog, ...);
void LogAddHeadHexFuncVoid(int type, char *data, int len);
void LogTextPaintProcVoid(HWND hWnd);
BOOL LogDateChange();
void LogDataSet();

void LogAddTimeDateFunc(char *szlog, ...);
void LogAddTimeDateVoid(char *szlog, ...);

void LogAddFunc(char *szlog, ...);
void LogAddFuncColor(BYTE Color, char *szlog, ...);
void LogAddHeadHexFunc(int type, char *data, int len);

void (*LogAdd)(char *szlog, ...);
void (*LogAddC)(BYTE Color, char *szlog, ...);
void (*LogAddTD)(char *szlog, ...);
void (*LogAddHeadHex)(int Type,char* data,int len);

void (*LogTextPaint)(HWND hWnd);
void LogTextPaintProc(HWND hWnd);


void LogInit(int logprint)
{
    if( logprint )
    {
        LogAdd = LogAddFunc;
        LogAddC = LogAddFuncColor;
        LogAddTD = LogAddTimeDateFunc;
        LogAddHeadHex = LogAddHeadHexFunc;
        LogTextPaint = LogTextPaintProc;

        for(int n=0; n<MAXLOGTEXT; n++)
        {
            memset(LogText[n], 0, MAXLOGTEXTC);
            LogTextLength[n] = 0;
            LogTextViewType[n] = 0;
        }

        if( gLogOutType == 0 )
            return;

        LogDataSet();
    }
    else
    {
        LogAdd = LogAddFuncVoid;
        LogAddHeadHex = LogAddHeadHexFuncVoid;
        LogTextPaint = LogTextPaintProcVoid;
        LogAddTD = LogAddTimeDateVoid;
    }
}

int LogMYear, LogMonth, LogMDay;

void LogDataSet()
{
    char		szTemp[50] = "";
    struct tm * today = {0};
    time_t		ltime = {0};

    time( &ltime );
    today = localtime( &ltime );

    today->tm_year += 1900;

    LogMYear = today->tm_year;
    LogMonth = today->tm_mon+1;
    LogMDay  = today->tm_mday;

    wsprintf(szTemp, "log\\%02d_%02d_%02d.log",LogMYear, LogMonth,LogMDay);

    if( logfp != NULL )
    {
        fclose(logfp);
        logfp = NULL;
    }

    logfp = fopen(szTemp, "a+t");
    if( logfp == NULL )
        LogAdd("error-L1 : Log write error.");

    strcpy(m_szLogFileName, szTemp);
}

BOOL LogDateChange()
{
    char szTemp[20] = "";
    struct tm *today = {0};
    time_t ltime = {0};

    time( &ltime );
    today = localtime( &ltime );

    today->tm_year += 1900;
    today->tm_mon  += 1;

    if( (today->tm_year <= LogMYear) &&
            (today->tm_mon  <= LogMonth) &&
            (today->tm_mday <= LogMDay) )
    {
        return FALSE;
    }
    LogMYear = today->tm_year;
    LogMonth = today->tm_mon;
    LogMDay  = today->tm_mday;

    wsprintf(szTemp, "log\\%02d_%02d_%02d.log",LogMYear, LogMonth,LogMDay);

    if( logfp!=NULL )
    {
        fclose(logfp);
        logfp = NULL;
    }

    logfp = fopen(szTemp, "a+t");
    if( logfp == NULL )
        MsgBox("error-L1 : Log write error.");

    strcpy(m_szLogFileName, szTemp);
    return TRUE;
}
int m_cline=0;

void LogTextAdd(BYTE type, char *msg, int len)
{
    if( len > MAXLOGTEXTC-1 )
        len = MAXLOGTEXTC-1;

    m_cline++;

    if( m_cline > MAXLOGTEXT-1)
        m_cline = 0;

    LogText[m_cline][0]			= '\0';

    memcpy(LogText[m_cline], msg, len);

    LogText[m_cline][len]		= LogText[m_cline][len+1] = '\0';
    LogTextLength[m_cline  ]	= len;
    LogTextViewType[m_cline]	= type;

}

void LogAddFuncVoid(char *szlog, ...)
{
    return;
}

void LogAddTimeDateVoid(char *szlog, ...)
{
    return;
}

void LogAddFunc(char *szlog, ...)
{
    char szBuffer[1024]="";
    va_list		pArguments;

    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);
    LogTextAdd(0, szBuffer, strlen(szBuffer));

    if( gLogOutType == 0 )
        return;

    if( logfp == NULL )
        return;

    fprintf(logfp, "%s\n",szBuffer);
}

void LogAddFuncColor(BYTE Color, char *szlog, ...)
{
    if(szlog == NULL)
        return;

    char		szBuffer[1024]="";
    va_list		pArguments;

    struct tm * today = {0};
    time_t		ltime = {0};
    char		tmpbuf[2048] = "";
    time( &ltime );
    today = localtime( &ltime );
    wsprintf(tmpbuf, "%.8s ",asctime( today ) + 11);

    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);

    strcat(tmpbuf, szBuffer);

    LogTextAdd(Color, tmpbuf, strlen(tmpbuf));

    if( gLogOutType == 0 )
        return;

    if( logfp == NULL )
        return;

    fprintf(logfp, "%s\n",tmpbuf);
}

void LogAddTimeDateFunc(char *szlog, ...)
{
    char		szBuffer[1024]="";
    va_list		pArguments;
    struct tm * today = {0};
    time_t		ltime = {0};
    char		tmpbuf[2048] = "";

    time( &ltime );
    today = localtime( &ltime );

    wsprintf(tmpbuf, "%.8s ",asctime( today ) + 11);

    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);

    strcat(tmpbuf, szBuffer);

    LogTextAdd(0, tmpbuf, strlen(tmpbuf));

    if( gLogOutType == 0 )
        return;

    if( logfp == NULL )
        return;

    fprintf(logfp, "%s\n",tmpbuf);
}

void LogAddHeadHexFuncVoid(int type, char *data, int len)
{
    return;
}

void LogAddHeadHexFunc(int type, char *data, int len)
{
    LogTextAdd(type, data, len);

    if( gLogOutType == 0 )
        return;

    if( logfp == NULL )
        return;

    switch(type)
    {
    case 2  :
        fprintf(logfp, "Send:[%d] : (", len);
        break;
    case 3  :
        fprintf(logfp, "FDWrite:[%d] : (", len);
        break;
    case 4  :
        fprintf(logfp, "Recv:[%d] : (", len);
        break;
    default :
        fprintf(logfp, "%d[%d] : (", type, len);
        break;
    }

    for( int n=0; n<len; n++)
        fprintf(logfp, "0x%02x ",(BYTE)data[n]);

    fprintf(logfp, ")\n");
}

void LogTextPaintProcVoid(HWND hWnd)
{
    return;
}


void LogTextPaintProc(HWND hWnd)
{
    HDC	hdc;
    hdc = GetDC(hWnd);
    int total = MAXLOGTEXT;
    int n     = m_cline;
    while( total-- )
    {
        switch( LogTextViewType[n] )
        {
        case 2  :
            SetTextColor(hdc, RGB(255,0,0));
            break;
        case 3  :
            SetTextColor(hdc, RGB(0,100,0));
            break;
        case 4  :
            SetTextColor(hdc, RGB(0,0,255));
            break;
        case 5  :
            SetTextColor(hdc, RGB(155,0,0));
            break;
        case 6  :
            SetTextColor(hdc, RGB(0,0,100));
            break;
        default :
            SetTextColor(hdc, RGB(0,0,0));
            break;
        }
        if( strlen(LogText[n]) > 1 )
            TextOut(hdc, 0, 15 * total + 100, LogText[n], strlen(LogText[n]));
        n--;
        if( n < 0 ) n = MAXLOGTEXT-1;
    }

    ReleaseDC(hWnd, hdc);
}

void MsgBox(char *szlog, ...)
{
    char szBuffer[512]="";
    va_list		pArguments;

    va_start(pArguments, szlog);
    vsprintf(szBuffer, szlog, pArguments);
    va_end(pArguments);

    MessageBox(NULL, szBuffer, "error", MB_OK);
}