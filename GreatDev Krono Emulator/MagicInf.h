#ifndef MAGICINF_H
#define MAGICINF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicDamage.h"


#define MAX_MAGIC_INFO	2

	#define	DBM_TYPE	0
	#define DBM_LEVEL	1



class CMagicInf
{

public:

	CMagicInf();
	virtual ~CMagicInf();
	
	int IsMagic();
	//void __thiscall Init();
	void Clear();
	int Set(BYTE aSkill, BYTE aLevel);
	int Set(BYTE aType, BYTE aIndex, BYTE aLevel);
	int GetDamage();
	
	CMagicInf & operator = (CMagicInf & __that)
	{
		this->m_Level = __that.m_Level;
		this->m_Skill = __that.m_Skill;
		this->m_DamageMin = __that.m_DamageMin;
		this->m_DamageMax = __that.m_DamageMax;

		return *this;
	};

public:

	BYTE m_Level;	// 4
	BYTE m_Skill;	// 5
	int m_DamageMin;	// 8
	int m_DamageMax;	// C

};

extern CMagicInf DefMagicInf[MAX_SKILL-1];

int GetSkillNumberInex(int type, int Index, int level);
void MagicByteConvert(unsigned char* buf, CMagicInf* const Magici, int maxmagic);

#endif