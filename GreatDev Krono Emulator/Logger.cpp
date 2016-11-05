#include "StdAfx.h"
#include "Logger.h"

cLog Log;

cLog::cLog()
{
	InitializeCriticalSection(&LogCritical);	
}
cLog::~cLog() {}

void cLog::LogOutPut(bool Date,eColor color,eTypeFile typefile,char* logmessage,...)
{
	char szBuffer[256];
	va_list pArguments;

	EnterCriticalSection(&LogCritical);

	va_start(pArguments, logmessage);
	vsprintf(szBuffer, logmessage, pArguments);
	va_end(pArguments);

	if (Date)
	{
		CTime time = CTime::GetCurrentTime();
		char *zBuf = new char[256];
		if (zBuf != NULL)
		{
			strcpy(zBuf,szBuffer);
			sprintf(szBuffer,"[%02d:%02d:%02d] %s",time.GetHour(),time.GetMinute(),time.GetSecond(),zBuf);
			delete[] zBuf;
		}
	}

	if (Counter >= MAX_ROWS)
	{
		Counter--;
		for (BYTE i = 0; i < MAX_ROWS; i++)
		{
			strcpy(this->LogMsgArr[i],this->LogMsgArr[i+1]);
			this->LogMsgColorArr[i] = this->LogMsgColorArr[i+1];
			this->LogMsgBoldArr[i] = this->LogMsgBoldArr[i+1];
		}
	}
	
	strcpy(this->LogMsgArr[Counter],szBuffer);
	this->LogMsgColorArr[Counter] = color;

	Counter++;
	if (typefile != t_NULL)  
		SaveLogInFile(typefile,szBuffer);

	LeaveCriticalSection(&LogCritical);
}

void cLog::LogPaint(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	BYTE total = MAX_ROWS;

	BYTE CountWith = this->Counter - 1;

	static LOGFONT logfont;
	logfont.lfCharSet = DEFAULT_CHARSET;
	logfont.lfPitchAndFamily = DEFAULT_PITCH;
	strcpy(logfont.lfFaceName,"Calibri");
	logfont.lfHeight = 18;
	logfont.lfWeight = FW_DONTCARE;
	
	logfont.lfOrientation = logfont.lfEscapement = 0;
	HFONT hNFont = CreateFontIndirect(&logfont);
	HFONT hOFont = (HFONT)SelectObject(hdc,hNFont);


	for(BYTE i = 0; i < Counter; i++)
	{
		SetTextColor(hdc,this->LogMsgColorArr[i]);
		short shPoz = i * 18 + 100;
		TextOut(hdc, 5, shPoz, LogMsgArr[i], strlen(LogMsgArr[i]));
	}

	ReleaseDC(hwnd, hdc);
}

void cLog::SaveLogInFile(eTypeFile typefile,char* msg)
{	
	char TodayFileName[55];

	CTime t = CTime::GetCurrentTime();
	sprintf(TodayFileName,".\\Logs\\%02d-%02d-%02d\\",t.GetDay(),t.GetMonth(),t.GetYear());

	CreateDirectory(".\\Logs\\",NULL);
	CreateDirectory(TodayFileName,NULL);
	
	char Path[48];

	switch(typefile)
	{
	case t_DEFAULT:
		sprintf(Path,"%s%s",TodayFileName,"t_Default.txt");
		break;
	case t_ERROR:
		sprintf(Path,"%s%s",TodayFileName,"t_Error.txt");
		break;
	case t_CHAOSMIX:
		sprintf(Path,"%s%s",TodayFileName,"t_ChaosMix.txt");
		break;
	case t_EVENTS:
		sprintf(Path,"%s%s",TodayFileName,"t_Events.txt");
		break;
	case t_DROP:
		sprintf(Path,"%s%s",TodayFileName,"t_Drop.txt");
		break;
	case t_CASTLESIEGE:
		sprintf(Path,"%s%s",TodayFileName,"t_CastleSiege.txt");
		break;
	case t_KUNDUM:
		sprintf(Path,"%s%s",TodayFileName,"t_Kundum.txt");
		break;
	case t_CRYWOLF:
		sprintf(Path,"%s%s",TodayFileName,"t_CryWolf.txt");
		break;
	default:
		return;
	}

	FILE *file = fopen(Path,"a+");

	if (file == NULL)
		file = fopen(Path,"w");

	if (file != NULL)
	{
		fprintf(file,"%s\n",msg);
		fclose(file);
	}
}