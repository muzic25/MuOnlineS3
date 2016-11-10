// BuffEffect.h: interface for the CBuffEffect class.
//
//////////////////////////////////////////////////////////////////////
#ifndef BUFFEFFECT_H
#define BUFFEFFECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_BUFF_EFFECT 255
#define MAX_STATE_COUNT 16

typedef struct
{	// Perfect.
	BYTE btIndex;			// 0x00 - CBuffEffect + 0x08
	BYTE btViewPortIndex;	// 0x01 - CBuffEffect + 0x09
	BYTE btItemType;		// 0x02 - CBuffEffect + 0x0A
	BYTE btItemIndex;		// 0x03 - CBuffEffect + 0x0B
	char szBuffName[20];	// 0x04 - CBuffEffect + 0x0C
	BYTE btType;			// 0x24 - CBuffEffect + 0x20
	BYTE btNotification;	// 0x25 - CBuffEffect + 0x21
	BYTE btClearType;		// 0x26 - CBuffEffect + 0x22
	char szBuffInfo[100];	// 0x27 - CBuffEffect + 0x23
} BUFF_EFFECT_DATA, *LPBUFF_EFFECT_DATA;

class CBuffEffect  
{
public:
	CBuffEffect();
	virtual ~CBuffEffect();

	void Init();
	bool Load(char * filename);
	bool Insert(BYTE Index, BYTE ViewPortIndex, BYTE ItemType, BYTE ItemIndex, char *BuffName, BYTE Type, BYTE Notification, BYTE ClearType, char *BuffInfo);
	bool IsValidIndex(BYTE btBuffIndex);
	LPBUFF_EFFECT_DATA GetBuffData(BYTE btBuffIndex);

	int iLoadCount;	// 0x04
	BUFF_EFFECT_DATA m_EffectData[MAX_BUFF_EFFECT]; //Effects Struct
};

extern CBuffEffect g_BuffEffect;

#endif