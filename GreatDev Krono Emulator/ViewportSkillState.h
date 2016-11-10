// ViewportSkillState.h: interface for the CViewportSkillState class.
//
//////////////////////////////////////////////////////////////////////
#ifndef VIEWPORTSKILLSTATE_H
#define VIEWPORTSKILLSTATE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "user.h"

class CViewportSkillState  
{
public:
	CViewportSkillState();
	virtual ~CViewportSkillState();

	void AddBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue);
	void RemoveBuffEffect(LPOBJ lpObj, BYTE btEffectType, int iValue);

	void SetDamageType(LPOBJ lpObj, BYTE DamageType, int iDamageValue);

	void ReflectDamage(LPOBJ lpObj, int iDamageValue);
	void PoisonDamage(LPOBJ lpObj, BYTE btDamageValue);

	void PrevBuffLastEffect(LPOBJ lpObj);
	void NextSetBuffLastEffect(LPOBJ lpObj);

	void CalCharacterRemoveBuffEffect(LPOBJ lpObj);
};

extern CViewportSkillState g_ViewportSkillState;

#endif