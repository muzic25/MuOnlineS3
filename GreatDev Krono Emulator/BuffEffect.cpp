// BuffEffect.cpp: implementation of the CBuffEffect class.
//	GS-N	1.00.77	JPN	0xXXXXXXXX	- Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BuffEffect.h"
#include "readscript.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuffEffect g_BuffEffect;

CBuffEffect::CBuffEffect()
{

}

CBuffEffect::~CBuffEffect()
{

}

//Identical
void CBuffEffect::Init()
{
	this->iLoadCount = 0;	

	for ( int i = 0; i < MAX_BUFF_EFFECT-1; i++ )
	{
		this->m_EffectData[i].btIndex			= 0xFF;
		this->m_EffectData[i].btType			= 0;
		this->m_EffectData[i].btClearType		= 0;
		this->m_EffectData[i].btNotification	= 0;
		this->m_EffectData[i].szBuffInfo[0]		= 0;
	}
}

//Identical
bool CBuffEffect::Load(char * filename)
{
	this->Init();

	if ( (SMDFile = fopen(filename, "r")) == NULL )
	{
		return false;
	}

	SMDToken Token;
	int iIndex = 0;
	BYTE btIndex = 0;
	BYTE btViewPortIndex = 0;
	BYTE btItemType = 0;
	BYTE btItemIndex = 0;
	BYTE btType = 0;
	BYTE btNotification = 0;
	BYTE btClearType = 0;
	char szBuffName[20];
	char szBuffInfo[100];

	while ( TRUE )
	{
		Token = GetToken();

		if ( Token == END )
		{
			break;
		}
		
		if ( Token == NUMBER )
		{
			iIndex = TokenNumber;

			while ( TRUE )
			{
				Token = GetToken();

				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				btIndex			= TokenNumber; Token = GetToken();
				btViewPortIndex	= TokenNumber; Token = GetToken();
				btItemType		= TokenNumber; Token = GetToken();
				btItemIndex		= TokenNumber; Token = GetToken();

				memcpy(szBuffName, TokenString, sizeof(szBuffName));

				Token = GetToken();

				btType			= TokenNumber; Token = GetToken();
				btNotification	= TokenNumber; Token = GetToken();
				btClearType		= TokenNumber; Token = GetToken();

				memcpy(szBuffInfo, TokenString, sizeof(szBuffInfo));

				this->Insert(btIndex, btViewPortIndex, btItemType, btItemIndex, szBuffName, btType, btNotification, btClearType, szBuffInfo);
			}
		}
	}

	fclose(SMDFile);

	return true;
}

//Identical
bool CBuffEffect::Insert(BYTE Index, BYTE ViewPortIndex, BYTE ItemType, BYTE ItemIndex, char *BuffName, BYTE Type, BYTE Notification, BYTE ClearType, char *BuffInfo)
{
	this->m_EffectData[this->iLoadCount].btIndex = Index;
	this->m_EffectData[this->iLoadCount].btViewPortIndex = ViewPortIndex;
	this->m_EffectData[this->iLoadCount].btItemType = ItemType;
	this->m_EffectData[this->iLoadCount].btItemIndex = ItemIndex;
	this->m_EffectData[this->iLoadCount].btType = Type;
	this->m_EffectData[this->iLoadCount].btNotification = Notification;
	this->m_EffectData[this->iLoadCount].btClearType = ClearType;

	memcpy(this->m_EffectData[this->iLoadCount].szBuffName,	BuffName, sizeof(this->m_EffectData[this->iLoadCount].szBuffName));
	memcpy(this->m_EffectData[this->iLoadCount].szBuffInfo,	BuffInfo, sizeof(this->m_EffectData[this->iLoadCount].szBuffInfo));

	this->iLoadCount++;

	return true;
}

//Identical
bool CBuffEffect::IsValidIndex(BYTE btBuffIndex)
{
	if ( btBuffIndex < 0 || btBuffIndex > MAX_BUFF_EFFECT-1 )
	{
		return false;
	}

	return true;
}

//Identical
LPBUFF_EFFECT_DATA CBuffEffect::GetBuffData(BYTE btBuffIndex)
{
	int loc2 = 0;

	if ( this->IsValidIndex(btBuffIndex) == false )
	{
		return NULL;
	}

	for ( int i = 0; i < MAX_BUFF_EFFECT-1; i++ )
	{
		if ( this->m_EffectData[i].btIndex == btBuffIndex )
		{
			return &this->m_EffectData[i];
		}
	}

	return NULL;
}