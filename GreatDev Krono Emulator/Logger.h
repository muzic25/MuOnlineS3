#ifndef _LOGGER_
#define _LOGGER_


#include "StdAfx.h"

#define MAX_ROWS 30
#define MAX_MSGLOGLEN	256

/*
Вообщем у меня есть просьба, для кажого модуля/евента и т.д. резервировать (если не хватает)
добавлять тот или иной цвет, чтобы не было бардака как раньше, тоже самое касаеться и записей логов в текстовые документы
Например
с_Red - для ошибок (использовать только t_ERROR)
c_DarkMagenta - для Хаос-машины (использовать только t_CHAOSMIX)
напротив кажого цвета/файла - пишите коментарий , что мол такой цвет для того та того та
*/



class cLog
{
public:
	enum eColor
	{
		c_White		= RGB(255,255,255),
		c_Black		= RGB(0,0,0),
		c_Red		= RGB(255,0,0), // Для ошибок
		c_Blue		= RGB(0,0,255),
		c_Green		= RGB(0,255,0),
		c_Cyan		= RGB(0,255,255),
		c_DarkGreen	= RGB(0,100,0),
		c_DarkMagenta	= RGB(139,0,139),  // Для хаос машины
		c_GreenYellow	= RGB(173,255,47),
		c_Indigo		= RGB(75,0,130), //Для комманд
		c_LightCoral	= RGB(240,128,128),
		c_Navy			= RGB(0,0,128),
		c_SkyBlue		= RGB(135,206,235),
		c_SteelBlue		= RGB(70,130,180)
	}Color;

	enum eTypeFile
	{
		t_NULL,
		t_DEFAULT,
		t_ERROR,  // Для ошибок
		t_CHAOSMIX, // Для хаос машины
		t_COMMANDS,
		t_EVENTS,
		t_DROP,
		t_CASTLESIEGE,
		t_KUNDUM,
		t_CRYWOLF,
	}TypeFile;

	cLog();
	~cLog();
	void LogOutPut(bool Date,eColor color,eTypeFile typefile,char* logmessage,...);
	void SaveLogInFile(eTypeFile typefile,char* msg);
	void LogPaint(HWND hwnd);

private:
	char LogMsgArr[MAX_ROWS][MAX_MSGLOGLEN]; 
	int LogMsgColorArr[MAX_ROWS];
	bool LogMsgBoldArr[MAX_ROWS];
	CRITICAL_SECTION LogCritical;	// Critical Section For LOG
	BYTE Counter;
};

extern cLog Log;

#endif