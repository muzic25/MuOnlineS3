#include "StdAfx.h"
#include "MonsterAttr.h"

CMonsterAttr::CMonsterAttr()
{
	return;
}

CMonsterAttr::~CMonsterAttr()
{
	return;
}


LPMONSTER_ATTRIBUTE CMonsterAttr::GetAttr(int aClass)
{
	for ( int n = 0; n<MAX_MONSTER_TYPE;n++)
	{
		if ( this->m_MonsterAttr[n].m_Index == aClass )
		{
			return &this->m_MonsterAttr[n];
		}
	}

	return NULL;
}

void CMonsterAttr::LoadAttr(char* filename)
{
	int Token;	int n;
	SMDFile = fopen(filename, "r");
	if ( SMDFile == NULL )
	{
		MsgBox("load error %s", filename);
		return;
	}
	n= 0;
	while ( true )
	{
		Token = GetToken();

		if ( Token == END )
			break;

		if ( Token == 1 )
		{
			this->m_MonsterAttr[n].m_Index = TokenNumber;

			Token = GetToken();					this->m_MonsterAttr[n].m_Rate = TokenNumber;
			Token = GetToken();					strcpy(this->m_MonsterAttr[n].m_Name, TokenString);
			Token = GetToken();					this->m_MonsterAttr[n].m_Level = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Hp = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Mp = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_DamageMin = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_DamageMax = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Defense = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MagicDefense = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackRating = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Successfulblocking = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoveRange = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackType = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackRange = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_ViewRange = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoveSpeed = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_AttackSpeed = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_RegenTime = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Attribute = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_ItemRate = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MoneyRate = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MaxItemLevel = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_MonsterSkill = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_ICE]  = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_POISON] = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_LIGHTNING] = TokenNumber;
			Token = GetToken();					this->m_MonsterAttr[n].m_Resistance[R_FIRE] = TokenNumber;

			this->m_MonsterAttr[n].m_Hp = this->m_MonsterAttr[n].m_Hp - (INT)(this->m_MonsterAttr[n].m_Hp / 100.0f * Configs.gMonsterHp);
			this->m_MonsterAttr[n].m_iScriptHP = this->m_MonsterAttr[n].m_Hp;

			if ( this->m_MonsterAttr[n].m_Level <= 24 && this->m_MonsterAttr[n].m_Index < 50)
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 ||
					 this->m_MonsterAttr[n].m_Level == 24 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*20/100;
					modiryvalue -= modiryvalue*Configs.gMonsterHPAdjust / 100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else if ( this->m_MonsterAttr[n].m_Level == 20 ||
						  this->m_MonsterAttr[n].m_Level == 22 )
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp*30/100;
					modiryvalue -= modiryvalue*Configs.gMonsterHPAdjust / 100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
				else
				{
					int modiryvalue = this->m_MonsterAttr[n].m_Hp/2;
					modiryvalue -= modiryvalue*Configs.gMonsterHPAdjust / 100;
					this->m_MonsterAttr[n].m_Hp -= modiryvalue;
				}
			}

			if ( this->m_MonsterAttr[n].m_Level  <= 19 && this->m_MonsterAttr[n].m_Index  < 50 )
			{
				if ( this->m_MonsterAttr[n].m_Level == 13 ||
					 this->m_MonsterAttr[n].m_Level == 14 ||
					 this->m_MonsterAttr[n].m_Level == 17 ||
					 this->m_MonsterAttr[n].m_Level == 18 ||
					 this->m_MonsterAttr[n].m_Level == 19 )
				 {
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin*30/100;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax*30/100;

					modiryvaluemin -= modiryvaluemin*Configs.gMonsterHPAdjust / 100;
					modiryvaluemax -= modiryvaluemax*Configs.gMonsterHPAdjust / 100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
				else
				{
					int modiryvaluemin = this->m_MonsterAttr[n].m_DamageMin/2;
					int modiryvaluemax = this->m_MonsterAttr[n].m_DamageMax/2;

					modiryvaluemin -= modiryvaluemin*Configs.gMonsterHPAdjust / 100;
					modiryvaluemax -= modiryvaluemax*Configs.gMonsterHPAdjust / 100;

					this->m_MonsterAttr[n].m_DamageMin -= modiryvaluemin;
					this->m_MonsterAttr[n].m_DamageMax -= modiryvaluemax;
				}
			}	 

			n++;
			if ( n> MAX_MONSTER_TYPE-1 )
			{
				MsgBox("Monster attribute max over %s %d", __FILE__, __LINE__);
				fclose(SMDFile);
				return;
			}
		}
	}

	fclose(SMDFile);
}