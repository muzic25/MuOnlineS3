#include "StdAfx.h"
#include "GameServerAuth.h"

FILE *fstream1, *fstream2;

//char *Lsrvname, *Lsrvver, *Lpartition, *Laddrarg7, 
char *FileBuffer;

unsigned long FileLen;

unsigned char szServerKey[19] = { 0x29, 0x23, 0xBE, 0x00, 0xE1, 0x6C, 0xD6,
	0xAE, 0x52, 0x90, 0x49, 0xF1, 0xF1, 0xBB, 0xE9, 0xEB, 0xB3, 0xA6, 0xDB };

CGameServerAuth gGameServerAuth;

// = { 0x29, 0x23, 0xBE, 0xFF, 0xE1, 0x6C, 0xD6, 0xAE, 0x52, 0x90, 0x49, 0x7E, 0xE9, 0xBB, 0xE9, 0xEB, 0xB3, 0xA6, 0xDB, 0xFF, 0xFF, 0xFF };
// szAuthKey[0] = 41
// szAuthKey[1] = 35
// szAuthKey[2] = 
// szAuthKey[3] = 
// szAuthKey[4] = -31
// szAuthKey[5] = 
// szAuthKey[6] = 
// szAuthKey[7] = 
// szAuthKey[8] = 
// szAuthKey[9] = -112
// szAuthKey[10] = 73
// szAuthKey[11] = -15
// szAuthKey[12] = -15
// szAuthKey[13] = -69
// szAuthKey[14] = 
// szAuthKey[15] = -15
// szAuthKey[16] = 
// szAuthKey[17] = -90
// szAuthKey[18] = -37
// szAuthKey[19] = 

CGameServerAuth::CGameServerAuth()
{
};

CGameServerAuth::~CGameServerAuth()
{
};

void GameServerAuthCallBackFunc(int Type, int pData)
{
 if (!Type)
 { 
		int i_DataSelect = pData;
	 switch (i_DataSelect)
 	{
		case 1: ReadCommonServerInfo();	break;
	 case 2: GameMonsterAllCloseAndReLoad(); break;
	 case 3: ReadServerInfo(); break;
		}
	}
}

// Обнуляем EAX = int gObjTotalUser
int CGameServerAuth::AGSetSubInfo(...) 
{
	__asm
	{
		Xor Eax, Eax 
	}
	return 0;
};

// CGameServerAuth::SendInfo вызывается функцией gObjSecondProc, дальше ветку вызовов не смотрел,
// но метод SendInfo работает циклически, параметры передаваемые методом AGSetSubInfo несут следующую информацию
// gAddExperience	2000.0000	float
// gItemDropPer	0x00000010	int
// gMonsterHp	0x00000000	int
// gObjTotalUser	0x00000000	int
// gServerMaxUser	0x0000012c	int
// По моему мнению каждый параметр в цикле за исключением gObjTotalUser статичного вида, то есть не изменяются.
// Данные члена gObjTotalUser хранятся в регистре EAX, передаваемые методом SendInfo в AGSetSubInfo, то есть его содержимое обнуляется.
// Получается мы имеем Real Time счетчик о количестве игроков в игре
// А может я и не прав (не исключено) 
void CGameServerAuth::SendInfo()
{
	this->AGSetSubInfo(gServerMaxUser, gObjTotalUser, Configs.gMonsterHp, Configs.gItemDropPer, Configs.gAddExperience, GetEventFlag());
}

void CGameServerAuth::GetKey(char *key, int startindex, int len)
{
	// Key        (&) - Буффер для ключей
	// StartIndex (x) - Варьирует 0/A/5 дальше не смотрел. Что за магические цифры, хуй его знает
	// Len        (5) - Не изменяется
	memcpy(key, szServerKey, sizeof(szServerKey)); 
}

void CGameServerAuth::RequestData(int type)
{
	char *filename = { 0 };

	switch (type)
	{
	case 0x00: 
	case 0x01:
		filename = "..\\Data\\Items\\Item.txt";
		break;
	case 0x02: 
	case 0x03:
		filename = "..\\Data\\Skills\\Skill.txt";
		break;
	case 0x04: 
	case 0x05:
		filename = "..\\Data\\Quests\\Quest.txt";
		break;
	case 0x06:
		filename = "..\\Data\\Encryption\\CheckSum.dat" ;
		break;
	case 0x07:
		filename = "..\\Data\\Monsters\\Monster.txt";
		break;
	case 0x08:	
		filename = "..\\Data\\Move\\Gate.txt" ;
		break;
	case 0x09: 
		filename = "..\\Data\\Monsters\\MonsterSetBase.txt"; 
		break;
	case 0x0A:
		break;
	case 0x0B:
		filename = "..\\Data\\Shops\\Shop0.txt";
		break;
	case 0x0C:
		filename = "..\\Data\\Shops\\Shop1.txt";
		break;
	case 0x0D:
		filename = "..\\Data\\Shops\\Shop2.txt";
		break;
	case 0x0E:
		filename = "..\\Data\\Shops\\Shop3.txt";
		break;
	case 0x0F:
		filename = "..\\Data\\Shops\\Shop4.txt";
		break;
	case 0x10:
		filename = "..\\Data\\Shops\\Shop5.txt";
		break;
	case 0x11:
		filename = "..\\Data\\Shops\\Shop6.txt";
		break;
	case 0x12:
		filename = "..\\Data\\Shops\\Shop7.txt";
		break;
	case 0x13:
		filename = "..\\Data\\Shops\\Shop8.txt";
		break;
	case 0x14:
		filename = "..\\Data\\Shops\\Shop9.txt";
		break;
	case 0x15:
		filename = "..\\Data\\Shops\\Shop10.txt";
		break;		
	case 0x16:
		filename = "..\\Data\\Shops\\Shop11.txt";
		break;
	case 0x17:
		filename = "..\\Data\\Shops\\Shop12.txt"; //23
		break;
	case 0x18:
		filename = "..\\Data\\Move\\MoveReq.txt";
		break;
	case 0x19:
		filename = "..\\Data\\Move\\MoveReq.txt";
		break;
	case 0x1A: 
	case 0x1B:
		filename = "..\\Data\\Items\\ItemSetOption.txt";
		break;
	case 0x1C: 
	case 0x1D:
		filename = "..\\Data\\Items\\ItemSetType.txt";
		break;
	case 0x1E:
		filename = "..\\Data\\Shops\\Shop13.txt";
		break;
	case 0x1F:
		filename = "..\\Data\\Shops\\Shop14.txt";
		break;
	case 0x20:
		filename = "..\\Data\\Shops\\Shop15.txt";
		break;
	case 0x21:
		filename = "..\\Data\\Shops\\Shop16.txt";
		break;
	case 0x22:
		filename = "..\\Data\\Shops\\Shop17.txt";
		break;
	default:
		filename = "Error!"; 
		::ExitProcess(0);
		break;
	}

	if (fstream1 = fopen(filename, "rb"))
	{
		fseek(fstream1, 0, SEEK_END);

		if (FileLen=ftell(fstream1)) 
		{
			fseek(fstream1, 0, SEEK_SET );
			FileBuffer = new char[FileLen + 1];
			fread(FileBuffer, FileLen, 1, fstream1);
		} 
		else 
		{
			MessageBox(NULL, filename, "Error!", MB_OK ); ::ExitProcess(0);
		}
		fclose(fstream1);
	}
	else
	{
		MessageBox(NULL, filename, "Error!", MB_OK);
		::ExitProcess(0);
	} 
}

// Размер файлов: Items.txt/Skills.txt/Quest.txt...
int CGameServerAuth::GetDataBufferSize()
{
	return FileLen;
}

// Буффер файлов: Items.txt/Skills.txt/Quest.txt...
char *CGameServerAuth::GetDataBuffer()
{
	return FileBuffer;
}

// Информация о GameServer (Нигде не используется, не нужды в данной функции)
DWORD CGameServerAuth::SetInfo(int iCountryCode, unsigned char cPartition, short iServerCode, char *szServerVersion,  char *szServerName, int ServerType,  void  (*callbackfunc)(int, int))
{
	/* Lsrvname = szServerName; // GameServer
	Lsrvver = szServerVersion; // 1.00.18
	Lpartition = (char*)cPartition; // 0
	Laddrarg7 = (char*)callbackfunc; // Address */
	return 0;	
}

// Чтение данных (версии и серийного номера клиента)
void CGameServerAuth::GetClientVersion(char *szClientVersion, char *szClientSerial)
{
	char Version[0x14];
	char SerialNumber[0x14];
	char CommonLocPath[] = "..\\Data\\CommonServer.cfg" ;

	GetPrivateProfileString("GameServerInfo",	"ClientExeVersion", "", &Version[0], 0x14, CommonLocPath);
	GetPrivateProfileString("GameServerInfo", "ClientExeSerial", "", &SerialNumber[0], 0x14, CommonLocPath);

	memcpy(szClientVersion, Version, 0x14);
	memcpy(szClientSerial, SerialNumber, 0x14);
}


