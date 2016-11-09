#pragma once


#define LOGC_RED			2
#define LOGC_GREEN			3
#define LOGC_BLUE			4
#define LOGC_LIGHTRED		5


extern void (*LogAdd)(char *szlog, ...);
extern void (*LogAddC)(BYTE, char *szlog, ...);
extern void (*LogAddHeadHex)(int type,char *data, int);
extern void (*LogTextPaint)(HWND hWnd);
extern void (*LogAddTD)(char *szlog, ...);

extern void LogInit(int logprint);
extern char * LogGetFileName();
extern void LogClose();
extern void LogTextClear();
extern BOOL LogDateChange();

extern void MsgBox(char *szlog, ...);