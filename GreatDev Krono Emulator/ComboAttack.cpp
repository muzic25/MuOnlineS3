#include "StdAfx.h"
#include "ComboAttack.h"

CComboAttack gComboAttack;

CComboAttack::CComboAttack()
{
	return;
}

CComboAttack::~CComboAttack()
{
	return;
}

int CComboAttack::GetSkillPos(int skillnum)
{
	switch (skillnum)
	{
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			return 0;
			break;
		case 41:
		case 42:
		case 43:
			return 1;
			break;
		default:
			return -1;
			break;
	}
}


BOOL CComboAttack::CheckCombo(int aIndex, int skillnum)
{
	LPOBJ lpObj = &gObj[aIndex];
	
	if ( lpObj->ComboSkillquestClear  != false )
	{
		int sp = this->GetSkillPos(skillnum);

		if ( sp == 0 )
		{
			lpObj->comboSkill.ProgressIndex  = 0;
			lpObj->comboSkill.dwTime = GetTickCount() + 3000;
			lpObj->comboSkill.Skill[0]  = skillnum;
		}
		else if ( sp == 1 )
		{
			if ( lpObj->comboSkill.Skill[0]  == 0xFF )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			int Time =GetTickCount();

			if (lpObj->comboSkill.dwTime < GetTickCount() )
			{
				lpObj->comboSkill.Init();
				return 0;
			}

			if ( lpObj->comboSkill.ProgressIndex == 0 )
			{
				lpObj->comboSkill.ProgressIndex = 1;
				lpObj->comboSkill.dwTime = GetTickCount() + 3000;
				lpObj->comboSkill.Skill[1] = skillnum;
			}
			else if ( lpObj->comboSkill.Skill[1]  != skillnum )
			{
				lpObj->comboSkill.Init();
				return 1;
			}
			else
			{
				lpObj->comboSkill.Init();
			}
		}
		else
		{
			lpObj->comboSkill.ProgressIndex= -1;
			lpObj->comboSkill.dwTime = 0;
			lpObj->comboSkill.Skill[0] = -1;
		}
	}

	return 0;
}
			


