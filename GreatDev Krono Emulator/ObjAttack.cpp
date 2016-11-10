#include "StdAfx.h"
#include "ObjAttack.h"

CObjAttack gclassObjAttack;

CObjAttack::CObjAttack()
{
	return;
}




CObjAttack::~CObjAttack()
{
	return;
}





BOOL CObjAttack::Attack(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf* lpMagic,  int magicsend, unsigned char MSBFlag, int AttackDamage, BOOL bCombo)
{
	int skillSuccess = 0;
	LPOBJ lpCallObj;
	LPOBJ lpCallTargetObj;
	unsigned char MsgDamage = 0;
	int ManaChange = 0;
	int iTempShieldDamage = 0;
	int iTotalShieldDamage = 0;

	if ( (lpTargetObj->Authority&2) == 2 )
		return FALSE;

	if ( lpObj->MapNumber != lpTargetObj->MapNumber )
		return FALSE;
	 
	if ( g_Crywolf.GetCrywolfState() == 3  || g_Crywolf.GetCrywolfState() == 5 )
	{
		if ( CHECK_CLASS(lpTargetObj->MapNumber, MAP_INDEX_CRYWOLF_FIRSTZONE) )
		{
			if ( lpTargetObj->Type == OBJ_MONSTER )
			{
				return FALSE;
			}
		}
	} 

	if (Configs.g_iUseCharacterAutoRecuperationSystem && lpObj->Level <= Configs.g_iCharacterRecuperationMaxLevel)
	{
		if ( lpObj->Type == OBJ_USER )
		{
			if (lpObj->Level <= Configs.g_iCharacterRecuperationMaxLevel) // #warning useless code
			{
				lpObj->m_iAutoRecuperationTime = GetTickCount();
			}
		}

		if ( lpTargetObj->Type == OBJ_USER )
		{
			if (lpTargetObj->Level <= Configs.g_iCharacterRecuperationMaxLevel)
			{
				lpTargetObj->m_iAutoRecuperationTime = GetTickCount();
			}
		}
	}

	if ( lpObj->Type == OBJ_USER )
		lpObj->dwShieldAutoRefillTimer = GetTickCount();

	if ( lpTargetObj->Type == OBJ_USER )
		lpTargetObj->dwShieldAutoRefillTimer = GetTickCount();

	int skill = 0;
	
	if ( lpMagic )
		skill = lpMagic->m_Skill;

	if ( lpObj->Class == 77 )
	{
		if ( lpObj->m_SkyBossMonSheild && skill == 17 )
		{
			skill = 3;
		}
	}

	skillSuccess = TRUE;

	if ( lpObj->GuildNumber > 0 )
	{
		if ( lpObj->lpGuild )
		{
			if ( lpObj->lpGuild->WarState )
			{
				if ( lpObj->lpGuild->WarType == 1 )
				{
					if ( !GetBattleSoccerGoalMove(0) )
					{
						return TRUE;
					}
				}
			}

			if ( lpObj->lpGuild->WarState )
			{
				if ( lpObj->lpGuild->WarType == 0 )
				{
					if ( lpTargetObj->Type == OBJ_MONSTER )
					{
						return TRUE;
					}
				}
			}
		}
	}

	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
		if ( lpTargetObj->m_iMonsterBattleDelay > 0 )
			return TRUE;
		
		if ( lpTargetObj->Class == 200 )
		{
			if ( skill )
			{
				gObjMonsterStateProc(lpTargetObj, 7, lpObj->m_Index, 0);
			}
			else
			{
				gObjMonsterStateProc(lpTargetObj, 6, lpObj->m_Index, 0);
			}

			if ( magicsend )
			{
				GCMagicAttackNumberSend(lpObj, skill, lpTargetObj->m_Index, skillSuccess);
			}

			return TRUE;
		}

		if ( lpTargetObj->m_ImmuneToMagicCount > 0 )
		{
			BOOL bCheckAttackIsMagicType = gObjCheckAttackTypeMagic(lpObj->Class, skill);

			if ( bCheckAttackIsMagicType == TRUE )
			{
				GCMagicAttackNumberSend(lpObj, skill, lpTargetObj->m_Index, 0);
				return TRUE;
			}
		}

		if ( lpTargetObj->m_ImmuneToHarmCount > 0 )
		{
			BOOL bCheckAttackIsMagicType = gObjCheckAttackTypeMagic(lpObj->Class, skill);

			if ( bCheckAttackIsMagicType == FALSE )
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
				return TRUE;
			}
		}
		if ( lpTargetObj->m_MonsterSkillElementInfo.m_iSkillElementImmuneTime > 0 )
		{
			if ( lpTargetObj->m_MonsterSkillElementInfo.m_iSkillElementImmuneNumber == skill )
			{
				return TRUE;
			}
		}
	}

	if ( lpObj->Type == OBJ_USER )
	{
		if ( !gObjIsConnected(lpObj) )
		{
			return FALSE;
		}

		if ( lpObj->m_Change == 8 )
		{
			skill = 1;
			lpMagic = &DefMagicInf[1];
			magicsend = 1;
		}

		gDarkSpirit[lpObj->m_Index].SetTarget(lpTargetObj->m_Index);
	}

	if ( lpTargetObj->Type == OBJ_USER )
	{
		if ( !gObjIsConnected(lpTargetObj))
		{
			return FALSE;
		}
	}

	if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_MONSTER )	// PLAYER VS MONSTER
	{
		if ( lpObj->m_RecallMon >= 0 )
		{
			if ( lpObj->m_RecallMon == lpTargetObj->m_Index )
			{
				return FALSE;
			}
		}
	}

	if ( !gObjAttackQ(lpTargetObj))
		return FALSE;

	if ( lpObj->m_RecallMon >= 0 )
		gObjCallMonsterSetEnemy(lpObj, lpTargetObj->m_Index);

	lpObj->m_TotalAttackCount++;

	if ( AttackDamage == 0 )
	{
		if ( skill != 76 )
		{
			if ( !lpObj->m_iMuseElfInfinityArrowSkillTime )
			{
				if ( !this->DecreaseArrow(lpObj) )
				{
					return FALSE;
				}
			}
		}
	}

	if ( this->CheckAttackArea(lpObj, lpTargetObj) == FALSE )
		return FALSE;

	lpCallObj = lpObj;

	if ( lpObj->Type == OBJ_MONSTER )
	{
		if ( lpObj->m_RecallMon >= 0 )
		{
			lpCallObj = &gObj[lpObj->m_RecallMon];
		}
	}

	lpCallTargetObj = lpTargetObj;

	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
		if ( lpTargetObj->m_RecallMon >= 0 )
		{
			lpCallTargetObj = &gObj[lpTargetObj->m_RecallMon];
		}
	}

	if ( this->PkCheck(lpCallObj, lpTargetObj) == FALSE )
		return FALSE;

	int Strength = lpObj->Strength + lpObj->AddStrength;
	int Dexterity = lpObj->Dexterity + lpObj->AddDexterity;
	int Vitality = lpObj->Vitality + lpObj->AddVitality;
	int Energy = lpObj->Energy + lpObj->AddEnergy;
	BOOL bIsOnDuel = gObjDuelCheck(lpObj, lpTargetObj);

	if ( bIsOnDuel )
	{
		lpObj->m_iDuelTickCount = GetTickCount();
		lpTargetObj->m_iDuelTickCount = GetTickCount();
	}

	if ( lpObj->pInventory[0].m_Type == ITEMGET(2,5) && lpObj->pInventory[0].m_IsValidItem != false )	// Crystal Sword
	{
		if ( (rand()%20) == 0 )
		{
			skill = 7;
			lpMagic = &DefMagicInf[7];
			magicsend = 1;
		}
	}
	else if ( lpObj->pInventory[1].m_Type == ITEMGET(2,5) && lpObj->pInventory[1].m_IsValidItem != false )	// Crystal Sword
	{
		if ( (rand()%20) == 0 )
		{
			skill = 7;
			lpMagic = &DefMagicInf[7];
			magicsend = 1;
		}
	}

	MSBFlag = 0;
	MsgDamage = 0;
	skillSuccess = this->ResistanceCheck(lpObj, lpTargetObj, skill);
	BOOL skillIceArrowSuccess = skillSuccess;

	if ( skill == 51 )
		skillSuccess = 0;

	BOOL bAllMiss = FALSE;
	
	if ( lpObj->m_iSkillInvisibleTime > 0 )
		gObjUseSkill.RemoveCloakingEffect(lpObj->m_Index);

	BOOL bDamageReflect = FALSE;
	
	if ( AttackDamage == 0 )
	{
		if (Configs.g_ShieldSystemOn == TRUE)
		{
			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				if ( !this->MissCheckPvP(lpObj, lpTargetObj, skill, skillSuccess, magicsend, bAllMiss) )
				{
					return FALSE;
				}
			}
			else if ( !this->MissCheck(lpObj, lpTargetObj, skill, skillSuccess, magicsend, bAllMiss) )
			{
				return FALSE;
			}

		}
		else if ( !this->MissCheck(lpObj, lpTargetObj, skill, skillSuccess, magicsend, bAllMiss) )
		{
			return FALSE;
		}

		if ( skill == 51 && skillIceArrowSuccess == TRUE )
		{
			lpTargetObj->m_SkillHarden = 7;
			lpTargetObj->m_SkillHardenTime = 7;
			lpTargetObj->lpAttackObj = lpObj;
			lpTargetObj->m_ViewSkillState |= 0x20;
			lpTargetObj->PathCount = 0;
			lpTargetObj->PathStartEnd = 0;
			skillSuccess = TRUE;

			gObjSetPosition(lpTargetObj->m_Index, lpTargetObj->X, lpTargetObj->Y);
		}

		int targetdefense = this->GetTargetDefense(lpObj, lpTargetObj, MsgDamage);

		if ( lpTargetObj->m_iSkillNPCDefense )
		{
			targetdefense += lpTargetObj->m_iSkillNPCDefense;
		}

		if ( skill == 19
			|| skill == 20
			|| skill == 21
			|| skill == 22
			|| skill == 23
			|| skill == 56
			|| skill == 41
			|| skill == 47
			|| skill == 42
			|| skill == 49
			|| skill == 43
			|| skill == 55
			|| skill == 44
			|| skill == 57
			|| skill == 74 )
		{
			AttackDamage = this->GetAttackDamage(lpObj, targetdefense, MsgDamage, bIsOnDuel, lpMagic);
			AttackDamage += lpObj->m_iSkillNPCAttack;

			if ( AttackDamage > 0 )
			{
				gObjWeaponDurDown(lpObj, lpTargetObj, 0);
			}
		}
		else if ( skill == 76 )	// pluzzmanton
		{
			int iFenrirAttackDmg = 0;

			if ( lpObj->Class == CLASS_KNIGHT || lpObj->Class == CLASS_MAGUMSA )
			{
				iFenrirAttackDmg = lpObj->Strength / 3 + lpObj->Dexterity / 5 + lpObj->Vitality / 5 + lpObj->Energy / 7;	// #formula
			}
			else if ( lpObj->Class == CLASS_WIZARD )
			{
				iFenrirAttackDmg = lpObj->Strength / 5 + lpObj->Dexterity / 5 + lpObj->Vitality / 7 + lpObj->Energy / 3;	// #formula
			}
			else if ( lpObj->Class == CLASS_ELF )
			{
				iFenrirAttackDmg = lpObj->Strength / 5 + lpObj->Dexterity / 3 + lpObj->Vitality / 7 + lpObj->Energy / 5;	// #formula
			}
			else	// Dark Lord
			{
				iFenrirAttackDmg = lpObj->Strength / 5 + lpObj->Dexterity / 5 + lpObj->Vitality / 7 + lpObj->Energy / 3 + lpObj->Leadership / 3;	// #formula
			}

			if ( iFenrirAttackDmg < 0 )
				iFenrirAttackDmg = 0;

			if ( lpObj->m_CriticalDamage > 0 )
			{
				if ( (rand()%100) < lpObj->m_CriticalDamage )
				{
					MsgDamage = 3;
				}
			}

			if ( lpObj->m_ExcelentDamage > 0 )
			{
				if ( (rand()%100) < lpObj->m_ExcelentDamage )
				{
					MsgDamage = 2;
				}
			}

			if ( MsgDamage == 3 )	// Critical Damage
			{
				AttackDamage =  iFenrirAttackDmg + lpMagic->m_DamageMax;
				AttackDamage += lpObj->SetOpAddCriticalDamage;
				AttackDamage += lpObj->SkillAddCriticalDamage;
				AttackDamage += lpObj->m_JewelOfHarmonyEffect.HJOpAddCriticalDamage;
				AttackDamage -= targetdefense;
			}
			else if ( MsgDamage == 2 )	// Excellent
			{
				AttackDamage = iFenrirAttackDmg + lpMagic->m_DamageMax;
				AttackDamage += AttackDamage * 20 / 100;
				AttackDamage += lpObj->SetOpAddExDamage;
				AttackDamage -= targetdefense;
			}
			else
			{
				AttackDamage = (iFenrirAttackDmg + lpMagic->m_DamageMin) + (rand()%(lpMagic->m_DamageMax - lpMagic->m_DamageMin + 1));
				AttackDamage -= targetdefense;
			}
		}
		else
		{
			if ( ( lpObj->Class == CLASS_WIZARD || lpObj->Class == CLASS_MAGUMSA ) && skill )
			{
				AttackDamage = this->GetAttackDamageWizard(lpObj, targetdefense, lpMagic, MsgDamage, bIsOnDuel);
				AttackDamage += lpObj->m_iSkillNPCAttack;

				if ( AttackDamage > 0 )
				{
					gObjWeaponDurDown(lpObj, lpTargetObj, 1);
				}
			}
			else
			{
				AttackDamage = this->GetAttackDamage(lpObj, targetdefense, MsgDamage, bIsOnDuel, lpMagic);
				AttackDamage += lpObj->m_iSkillNPCAttack;

				if ( AttackDamage > 0 )
				{
					gObjWeaponDurDown(lpObj, lpTargetObj, 0);
				}
			}
		}

		if ( bAllMiss )
		{
			AttackDamage = ( AttackDamage * 30 ) / 100;
		}

		if ( lpTargetObj->DamageMinus )
		{
			int beforeDamage = AttackDamage;
			AttackDamage -= ( ( AttackDamage * (int)lpTargetObj->DamageMinus) / 100 );
		}

		int tlevel = lpObj->Level / 10;

		if ( AttackDamage < tlevel )
		{
			if ( tlevel < 1 )
			{
				tlevel = 1;
			}

			AttackDamage = tlevel;
		}

		if ( lpTargetObj->m_SkillNumber == 18 )
		{
			if ( AttackDamage > 1 )
			{
				AttackDamage >>= 1;
			}
		}

		gObjSpriteDamage(lpTargetObj, AttackDamage);

		if ( gObjSatanSprite(lpObj) == TRUE )
		{
			lpObj->Life -= 3.0f;

			if ( lpObj->Life < 0.0f )
			{
				lpObj->Life = 0.0f;
			}
			else
			{
				AttackDamage = AttackDamage * 13 / 10;
			}

			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
		}

		if ( gObjAngelSprite(lpTargetObj) == TRUE )
		{
			if ( AttackDamage > 1 )
			{
				float  damage = (AttackDamage * 8) / 10.0f;
				AttackDamage = damage;
			}
		}

		if (gObjWingSprite(lpObj) == TRUE)
		{
			CItem * Wing = &lpObj->pInventory[7];

			if (lpObj->Class == CLASS_WIZARD || lpObj->Class == CLASS_ELF)
			{
				lpObj->Life -= 1.0f;
			}
			else if (lpObj->Class == CLASS_SUMMONER) //summoner
			{
				lpObj->Life -= 1.0f;
			}
			else
			{
				lpObj->Life -= 3.0f;
			}

			if (lpObj->Life < 0.0f)
			{
				lpObj->Life = 0.0f;
			}
			else
			{
				if (Wing->m_Type >= ITEMGET(12, 36) && Wing->m_Type <= ITEMGET(12, 40)) //season 2.5 add-on
				{
					AttackDamage = AttackDamage * (Wing->m_Level * 2 + 139) / 100;	// #formula
				}
				else if (Wing->m_Type == ITEMGET(13, 30))	// Cape Of Lord
				{
					AttackDamage = AttackDamage * (Wing->m_Level * 2 + 120) / 100;	// #formula
				}
				else if (Wing->m_Type == ITEMGET(12, 41))	//
				{
					AttackDamage = AttackDamage * (Wing->m_Level * 2 + 112) / 100;	// #formula
				}
				else if (Wing->m_Type == ITEMGET(12, 42))	//
				{
					AttackDamage = AttackDamage * (Wing->m_Level + 132) / 100;	// #formula
				}
				else if (Wing->m_Type == ITEMGET(12, 43))	//
				{
					AttackDamage = AttackDamage * (Wing->m_Level * 2 + 139) / 100;	// #formula
				}
				else if (Wing->m_Type > ITEMGET(12, 2))
				{
					AttackDamage = AttackDamage * (Wing->m_Level + 132) / 100;	// #formula
				}
				else
				{
					AttackDamage = AttackDamage * (Wing->m_Level * 2 + 112) / 100;	// #formula
				}
			}

			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
		}

		if (gObjWingSprite(lpTargetObj) == TRUE)
		{
			CItem * Wing = &lpTargetObj->pInventory[7];

			if (Wing->m_Type != ITEMGET(13, 30)) // Cape Of Lord
			{
				if (AttackDamage > 1)
				{
					if (Wing->m_Type >= ITEMGET(12, 36) && Wing->m_Type <= ITEMGET(12, 40) || Wing->m_Type == ITEMGET(12, 43)) //season 2.5 add-on
					{
						if (Wing->m_Type == ITEMGET(12, 40))
						{
							float damage = (float)(AttackDamage * (76 - (Wing->m_Level * 2))) / 100.0f;
							AttackDamage = (int)(damage);	//  #formula
						}
						else
						{
							float damage = (float)(AttackDamage * (61 - (Wing->m_Level * 2))) / 100.0f;
							AttackDamage = (int)(damage);	//  #formula
						}

						if ((rand() % 100)< 5)
						{
							BYTE WingOption = lpTargetObj->pInventory[7].m_NewOption;

							if ((WingOption & 4) == 4) // 5% Chance of Recover Full Life
							{
								gObjAddMsgSendDelay(lpTargetObj, 13, lpObj->m_Index, 100, 0);
							}
							else
							{
								if ((WingOption & 8) == 8) // 5% Chance of Recover Full Mana
								{
									gObjAddMsgSendDelay(lpTargetObj, 14, lpObj->m_Index, 100, 0);
								}
							}
						}
					}
					else if (Wing->m_Type > ITEMGET(12, 2))
					{
						float damage = (float)(AttackDamage * (75 - (Wing->m_Level * 2))) / 100.0f;
						AttackDamage = (int)(damage);	//  #formula

					}
					else
					{
						float damage = (float)(AttackDamage * (88 - (Wing->m_Level * 2))) / 100.0f;
						AttackDamage = (int)(damage);	//  #formula
					}
				}
			}
		}

		if ( gObjDenorantSprite(lpObj ) )
		{
			lpObj->Life -= 1.0f;

			if ( lpObj->Life < 0.0f )
			{
				lpObj->Life = 0.0f;
			}
			else
			{
				AttackDamage = AttackDamage * 115 / 100;
			}

			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
		}

		if ( gObjDenorantSprite(lpTargetObj ) )
		{
			CItem * Dinorant = &lpTargetObj->pInventory[8];
			int dinorantdecdamage = 90 - Dinorant->IsDinorantReduceAttackDamaege();
			lpObj->Life -= 1.0f;

			if ( lpObj->Life < 0.0f )
			{
				lpObj->Life = 0.0f;
			}
			else
			{
				AttackDamage = AttackDamage * dinorantdecdamage / 100;
			}

			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
		}

		if ( gObjDarkHorse(lpTargetObj ) )
		{
			CItem * Darkhorse = &lpTargetObj->pInventory[8];
			int decdamage = 100 - ((Darkhorse->m_PetItem_Level + 30) / 2 );

			lpTargetObj->Life -= 1.0f;

			if ( lpTargetObj->Life < 0.0f )
			{
				lpTargetObj->Life = 0.0f;
			}
			else
			{
				AttackDamage = AttackDamage * decdamage / 100;
			}

			GCReFillSend(lpTargetObj->m_Index, lpTargetObj->Life, 0xFF, 0, lpTargetObj->iShield);
		}

		if ( lpTargetObj->Live )
		{
			switch ( skill )
			{
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 41:
				case 42:
				case 43:
				case 44:
				case 49:
				case 55:
				case 57:
					if ( lpObj->Class == CLASS_DARKLORD || lpObj->Class == CLASS_MAGUMSA )
					{
						AttackDamage *= 2;
					}
					else
					{
						AttackDamage = ( AttackDamage * ( 200 + ( Energy / 10 ) ) ) / 100;
					}
					break;

				case 47:
					if ( lpObj->pInventory[8].m_Type == ITEMGET(13,3) ||
						 lpObj->pInventory[8].m_Type == ITEMGET(13,2) ||
						 lpObj->pInventory[8].m_Type == ITEMGET(13,37) )
					{
						if ( lpObj->Class == CLASS_DARKLORD || lpObj->Class == CLASS_MAGUMSA )
						{
							AttackDamage *= 2;
						}
						else
						{
							AttackDamage = ( AttackDamage * ( Energy / 10 + 200 )  ) / 100;
						}
					}
					break;

				case 56:
					AttackDamage *= 2;
					break;

				case 46:
				case 51:
				case 52:
					AttackDamage *= 2;
					break;

				case 60:
				case 61:
				case 62:
				case 65:
				case 74:
				case 78:
					AttackDamage = ( AttackDamage * ( ( ( lpObj->Energy + lpObj->AddEnergy ) / 20 + 200 ) ) ) / 100;
					break;

				case 76:
					int iDamageInc = lpObj->Level - 300;

					if ( iDamageInc < 0 )
						iDamageInc = 0;

					iDamageInc /= 5;
					AttackDamage = ( AttackDamage * ( iDamageInc + 200 ) ) / 100;
					break;
			}

			if ( skill == 0 )
			{
				if ( lpObj->pInventory[8].m_Type == ITEMGET(13, 3) )
				{
					AttackDamage = AttackDamage * 130 / 100;
				}
			}
			
			if ( lpTargetObj->m_WizardSkillDefense && AttackDamage > 0)
			{
				int replacemana = (WORD)lpTargetObj->Mana * 2 / 100;

				if ( replacemana < lpTargetObj->Mana )
				{
					lpTargetObj->Mana -= replacemana;
					int decattackdamage = AttackDamage * lpTargetObj->m_WizardSkillDefense / 100;
					AttackDamage -= decattackdamage;
					ManaChange = TRUE;

				}
			}

			AttackDamage += lpObj->SetOpAddDamage;

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				AttackDamage += lpObj->m_ItemOptionExFor380.OpAddDamage;
			}

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				if ( CC_MAP_RANGE(lpObj->MapNumber ) && CC_MAP_RANGE(lpTargetObj->MapNumber) )
				{
					AttackDamage = AttackDamage * 50 / 100;
				}
			}
			 
			if ( g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
			{
				if ( lpObj->Type == OBJ_USER && lpTargetObj->Type ==OBJ_USER )
				{
					if ( lpObj->MapNumber == MAP_INDEX_CASTLESIEGE && lpTargetObj->MapNumber == MAP_INDEX_CASTLESIEGE )
					{
						if ( lpObj->m_btCsJoinSide == lpTargetObj->m_btCsJoinSide )
						{
							AttackDamage = AttackDamage * 20 / 100;
						}
						else
						{
							AttackDamage = AttackDamage * 40 / 100;
						}
					}
				}
			} 

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_MONSTER )
			{
				if ( lpTargetObj->Class == 283 )
				{
					if ( lpObj->m_iPotionBlessTime > 0 )
					{
						AttackDamage += (AttackDamage * 20) / 100;
					}
					else if ( lpObj->m_iPotionSoulTime > 0 )
					{
						AttackDamage = AttackDamage;
					}
					else 
					{
						if ( lpObj->m_iAccumulatedDamage > 100 )
						{
							gObjWeaponDurDownInCastle(lpObj, lpTargetObj, 1);
							lpObj->m_iAccumulatedDamage = 0;
						}
						else
						{
							lpObj->m_iAccumulatedDamage += AttackDamage;
						}

						AttackDamage = AttackDamage * 5 / 100;
					}
				}

				if ( lpTargetObj->Class == 277 )
				{
					if ( lpObj->m_iPotionBlessTime > 0 )
					{
						AttackDamage += (AttackDamage * 20) / 100;
					}
					else if ( lpObj->m_iPotionSoulTime > 0 )
					{
						AttackDamage = AttackDamage;
					}
					else 
					{
						if ( lpObj->m_iAccumulatedDamage > 100 )
						{
							gObjWeaponDurDownInCastle(lpObj, lpTargetObj, 1);
							lpObj->m_iAccumulatedDamage = 0;
						}
						else
						{
							lpObj->m_iAccumulatedDamage += AttackDamage;
						}

						AttackDamage = AttackDamage * 5 / 100;
					}
				}
			}

			if ( gObjFenrir( lpObj ) )
			{
				int iIncPercent = lpObj->pInventory[8].IsFenrirIncLastAttackDamage();

				if ( iIncPercent > 0 )
				{
					AttackDamage += AttackDamage * iIncPercent / 100;
				}
			}

			if ( gObjFenrir( lpTargetObj ) )
			{
				int iDecPercent = lpTargetObj->pInventory[8].IsFenrirDecLastAttackDamage();

				if ( iDecPercent > 0 )
				{
					AttackDamage -= AttackDamage * iDecPercent / 100;
				}
			}

			if ( AttackDamage < 0 )
				AttackDamage = 0;

			if ( skill == 76 )
			{
				if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
				{
					if ( AttackDamage > 0 )
					{ 
						if ( !lpObj->m_btCsJoinSide || lpObj->m_btCsJoinSide != lpTargetObj->m_btCsJoinSide ) 
						{ 
							int iEquipmentPos = rand()%5 + 2;	// Select and Armor
							CItem * lpEquipment = &lpTargetObj->pInventory[iEquipmentPos];

							if ( lpEquipment && lpEquipment->IsItem() )
							{
								int iDurEquipment = lpEquipment->m_Durability * 50.0f / 100.0f;
								lpEquipment->m_Durability = iDurEquipment;

								if ( lpEquipment->m_Durability < 0.0f )
								{
									lpEquipment->m_Durability = 0.0f;
								}

								GCItemDurSend(lpTargetObj->m_Index, iEquipmentPos, lpEquipment->m_Durability, 0);
							} 
						} 
					}
				}
			}

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				iTempShieldDamage = this->GetShieldDamage(lpObj, lpTargetObj, AttackDamage);
				lpTargetObj->iShield -= iTempShieldDamage;
				lpTargetObj->Life -= AttackDamage - iTempShieldDamage;
				iTotalShieldDamage += iTempShieldDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}
			else
			{
				lpTargetObj->Life -= AttackDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}
		}
	}	
	else
	{
		if ( g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
		{
			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type ==OBJ_USER )
			{
				if ( lpObj->MapNumber == MAP_INDEX_CASTLESIEGE && lpTargetObj->MapNumber == MAP_INDEX_CASTLESIEGE )
				{
					if ( lpObj->m_btCsJoinSide == lpTargetObj->m_btCsJoinSide )
					{
						AttackDamage = AttackDamage * 20 / 100;
					}
					else if (Configs.g_ShieldSystemOn == 0)
					{
						AttackDamage = AttackDamage * 40 / 100;
					}
				}
			}
		}
		if ( skill != 79 )
		{
			bDamageReflect = TRUE;
			MsgDamage = 4;
		}

		if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
		{
			iTempShieldDamage = this->GetShieldDamage(lpObj, lpTargetObj, AttackDamage);
			lpTargetObj->iShield -= iTempShieldDamage;
			lpTargetObj->Life -= AttackDamage - iTempShieldDamage;
			iTotalShieldDamage += iTempShieldDamage;

			if ( lpTargetObj->Life < 0.0f )
			{
				lpTargetObj->Life = 0.0f;
			}
		}
		else
		{
			lpTargetObj->Life -= AttackDamage;

			if ( lpTargetObj->Life < 0.0f )
			{
				lpTargetObj->Life = 0.0f;
			}
		}
	}

	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
		gObjAddMsgSendDelay(lpTargetObj, 0, lpObj->m_Index, 100, 0);
		lpTargetObj->LastAttackerID = lpObj->m_Index;

		if ( lpTargetObj->m_iCurrentAI )
		{
			lpTargetObj->m_Agro.IncAgro(lpObj->m_Index, AttackDamage / 50);
		}
	}

	BOOL selfdefense = 0;
	lpCallObj = lpTargetObj;
	
	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
		if ( lpTargetObj->m_RecallMon >= 0 )
		{
			lpCallObj = &gObj[lpTargetObj->m_RecallMon];
		}
	}

	if ( AttackDamage >= 1 )
	{
		if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
		{
			if ( gObjDuelCheck(lpObj, lpTargetObj) )
			{
				selfdefense = 0;
			}
			else if ( CC_MAP_RANGE(lpObj->MapNumber) || CC_MAP_RANGE(lpTargetObj->MapNumber) )
			{
				selfdefense = 0;
			}
			else if (IT_MAP_RANGE(lpObj->MapNumber) || IT_MAP_RANGE(lpTargetObj->MapNumber)) //season 2.5 add-on
			{
				selfdefense = 0;
			}
			else
			{
				selfdefense = 1;
			}

			if ( gObjGetRelationShip(lpObj, lpTargetObj) == 2 )
			{
				selfdefense = FALSE;
			}
			if ( g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
			{
				if ( lpObj->m_btCsJoinSide > 0 )
				{
					selfdefense = FALSE;
				}
			}
		}
		else if ( lpTargetObj->Type == OBJ_MONSTER && lpObj->Type == OBJ_USER )
		{
			if ( lpTargetObj->m_RecallMon >= 0 )
			{
				selfdefense = TRUE;
			}
		}

		if ( lpTargetObj->Type == OBJ_USER )
		{
			gObjArmorRandomDurDown(lpTargetObj, lpObj);
		}

		if ( lpTargetObj->m_SkillHarden )
		{
			lpTargetObj->m_SkillHarden--;

			if ( lpTargetObj->m_SkillHarden <= 0 )
			{
				lpTargetObj->m_SkillHardenTime = 0;
				lpTargetObj->m_SkillHarden = 0;
				lpTargetObj->m_ViewSkillState &= -33;
				GCMagicCancelSend(lpTargetObj, 51);
			}
		}
	}

	if ( selfdefense == TRUE && bDamageReflect == FALSE )
	{
		if ( !gObjTargetGuildWarCheck(lpObj, lpCallObj) )
		{
			gObjCheckSelfDefense(lpObj, lpCallObj->m_Index);
		}
	}

	if ( lpTargetObj->Class == 275 )	// KUNDUN
	{
		if ( lpTargetObj->m_iMonsterBattleDelay <= 0 )
		{
			if ( (rand()%15) < 1 )
			{
				gObjAddMsgSendDelay(lpTargetObj, 4, lpObj->m_Index, 100, 0);
				lpTargetObj->m_iMonsterBattleDelay = 10;
				GCActionSend(lpTargetObj, 126, lpTargetObj->m_Index, lpObj->m_Index);
			}
		}
	}

	if ( lpTargetObj->Class == 131 ||BC_STATUE_RANGE(lpTargetObj->Class-132) )
	{
		gObjAddMsgSendDelay(lpTargetObj, 4, lpObj->m_Index, 100, 0);
		gObjSetPosition(lpTargetObj->m_Index, lpTargetObj->X, lpTargetObj->Y);
	}
	else if ( AttackDamage >= 5 )	// To make strong hit
	{
		if ( lpTargetObj->Type == OBJ_MONSTER )
		{
			if ( (rand()%26) == 0 )
			{
				gObjAddMsgSendDelay(lpTargetObj,4, lpObj->m_Index, 100, 0);
			}
		}
		else if ( (rand()%4) == 0 )
		{
			if ( !gObjUniriaSprite(lpTargetObj) )
			{
				MSBFlag = 1;
			}
		}
	}

	if ( ManaChange )
	{
		GCManaSend(lpTargetObj->m_Index, lpTargetObj->Mana, 0xFF, 0, lpTargetObj->BP);
	}

	if ( magicsend )
	{
		GCMagicAttackNumberSend(lpObj, skill, lpTargetObj->m_Index, skillSuccess);
	}

	if ( lpObj->Type == OBJ_USER )
	{
		if ( lpObj->m_Change == 9 )
		{
			GCMagicAttackNumberSend(lpObj, 3, lpTargetObj->m_Index, 1);
		}
	}

	if ( lpObj->Class == CLASS_ELF && lpObj->Level == 1 && AttackDamage > 10 )
	{
		LogAdd("error-Level1 : [%s][%s] Str:%d %d %d %d %d %d %d",
			lpObj->AccountID, lpObj->Name, lpObj->Strength,
			lpObj->m_AttackDamageMinRight, lpObj->m_AttackDamageMaxRight,
			lpObj->m_AttackDamageMinLeft, lpObj->m_AttackDamageMaxLeft, 
			lpObj->m_AttackDamageMax, lpObj->m_AttackDamageMin);
	}

	lpObj->m_Rest = 0;

	if ( AttackDamage > 0 )
	{
		int atd_reflect = (int)((float)AttackDamage * lpTargetObj->DamageReflect / 100.0f);

		if ( atd_reflect )
		{
			gObjAddMsgSendDelay(lpTargetObj, 10, lpObj->m_Index, 10, atd_reflect);
		}

		if ( (rand()%100) < lpObj->SetOpReflectionDamage )
		{
			gObjAddMsgSendDelay(lpTargetObj, 10, lpObj->m_Index, 10, AttackDamage);
		}

		if ((rand() % 100) < 5) //season 2.5 add-on
		{
			if (gObjWingSprite(lpTargetObj) == TRUE)
			{
				CItem * Wing = &lpTargetObj->pInventory[7];

				if (Wing->m_Type >= ITEMGET(12, 36) && Wing->m_Type <= ITEMGET(12, 40) || Wing->m_Type == ITEMGET(12, 43))
				{
					BYTE WingOption = lpTargetObj->pInventory[7].m_NewOption;

					if ((WingOption & 2) == 2) // 5% Chance of Return Damage
					{
						if (lpObj->Type == OBJ_MONSTER)
						{
							gObjAddMsgSendDelay(lpTargetObj, 12, lpObj->m_Index, 10, lpObj->m_AttackDamageMax);
						}
						else if (lpObj->Type == OBJ_USER)
						{
							gObjAddMsgSendDelay(lpTargetObj, 12, lpObj->m_Index, 10, AttackDamage);
						}
					}
				}
			}
		}

		if ( bCombo )
		{
			int iComboDamage = ( Strength + Dexterity + Energy ) / 2;	// #formula
			AttackDamage += iComboDamage;

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				iTempShieldDamage = this->GetShieldDamage(lpObj, lpTargetObj, iComboDamage);
				lpTargetObj->iShield -= iTempShieldDamage;
				lpTargetObj->Life -= iComboDamage - iTempShieldDamage;
				iTotalShieldDamage += iTempShieldDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}
			else
			{
				lpTargetObj->Life -= iComboDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}

			MsgDamage |= 0x80;
			skill = 59;
		}

		if ( (rand()%100) < lpObj->SetOpDoubleDamage )
		{
			if ( skill == 78 )
			{
				gObjUseSkill.FireScreamExplosionAttack(lpObj, lpTargetObj, AttackDamage);
			}

			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				iTempShieldDamage = this->GetShieldDamage(lpObj, lpTargetObj, AttackDamage);
				lpTargetObj->iShield -= iTempShieldDamage;
				lpTargetObj->Life -= AttackDamage - iTempShieldDamage;
				iTotalShieldDamage += iTempShieldDamage;
				AttackDamage += AttackDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}
			else
			{
				lpTargetObj->Life -= AttackDamage;
				AttackDamage += AttackDamage;

				if ( lpTargetObj->Life < 0.0f )
				{
					lpTargetObj->Life = 0.0f;
				}
			}

			MsgDamage |= 0x40;
		}

		if (Configs.g_ShieldSystemOn == TRUE)
		{
			AttackDamage -= iTotalShieldDamage;
		}

		if (Configs.g_ShieldSystemOn == FALSE)
		{
			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				if ( CC_MAP_RANGE(lpObj->MapNumber) && CC_MAP_RANGE(lpTargetObj->MapNumber) )
				{
					AttackDamage = AttackDamage * 50 / 100;
				}
			}
		}

		gObjLifeCheck(lpTargetObj, lpObj, AttackDamage, 0, MSBFlag, MsgDamage, skill, iTotalShieldDamage);

		if ( iTotalShieldDamage > 0 )
		{
			LogAddTD("[PvP System] Victim:[%s][%s], Attacker:[%s][%s] - SD[%d] HP[%f] -> SD[%d] HP[%f]",
				lpTargetObj->AccountID, lpTargetObj->Name, lpObj->AccountID, lpObj->Name,
				lpTargetObj->iShield + iTotalShieldDamage, lpTargetObj->Life + AttackDamage, 
				lpTargetObj->iShield, lpTargetObj->Life);
		}
	}
	else
	{
		GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, MsgDamage, 0);
	}

	if ( lpObj->Life <= 0.0f && lpObj->Type == OBJ_USER )
	{
		if ( lpObj->m_CheckLifeTime <= 0 )
		{
			lpObj->lpAttackObj = lpTargetObj;

			if ( lpTargetObj->Type == OBJ_USER )
			{
				lpObj->m_bAttackerKilled = true;
			}
			else
			{
				lpObj->m_bAttackerKilled = false;
			}

			lpObj->m_CheckLifeTime = 3;
		}
	}

	if ( lpMagic )
	{
		gObjUseSkill.SpecificSkillAdditionTreat(lpObj, lpTargetObj, lpMagic, AttackDamage);
	}

	return TRUE;
}





int  CObjAttack::GetAttackDamage(LPOBJ lpObj, int targetDefense, BYTE& effect, BOOL bIsOnDuel, CMagicInf* lpMagic)
{
	if (Configs.g_ShieldSystemOn == TRUE)
	{
		if ( bIsOnDuel == TRUE )
		{
			bIsOnDuel = FALSE;
		}
	}

	int ad;
	int sub;
	int SkillRightMaxDamage =0;
	int SkillRightMinDamage =0;
	int SkillLeftMaxDamage =0;
	int SkillLeftMinDamage =0;
	CItem * Right = &lpObj->pInventory[0];
	CItem * Left = &lpObj->pInventory[1];
	BOOL bTwoHandWeapon = FALSE;

	if ( lpObj->Type == OBJ_MONSTER || lpObj->Type == OBJ_NPC )
	{
		int AttackMin = 0;
		sub = lpObj->m_AttackDamageMax - lpObj->m_AttackDamageMin;
		AttackMin = lpObj->m_AttackDamageMin + (rand()%(sub+1));
		lpObj->m_AttackDamageRight = AttackMin;
		lpObj->m_AttackDamageLeft = AttackMin;
	}
	else
	{
		int cDamage=0;

		if ( lpObj->Class == CLASS_DARKLORD ||
			 lpObj->Class == CLASS_KNIGHT   ||
			 lpObj->Class == CLASS_MAGUMSA )
		{
			if ( Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(4,0) &&
				 Left->m_Type >= ITEMGET(0,0) && Left->m_Type < ITEMGET(4,0) )
			{
				if ( Right->m_IsValidItem && Left->m_IsValidItem )
				{
					bTwoHandWeapon = TRUE;
				}
			}
		}

		if ( lpMagic )
		{
			if ( lpMagic ->m_Skill == 60 && lpObj->SkillLongSpearChange )	// #error 60 and skil from GEt is 66???
			{
				SkillRightMaxDamage = DefMagicInf[66].m_DamageMax;// #error ???
				SkillRightMinDamage = DefMagicInf[66].m_DamageMin;// #error ???
			}
			else
			{
				SkillRightMaxDamage = lpMagic->m_DamageMax;
				SkillRightMinDamage = lpMagic->m_DamageMin;
			}

			if ( bTwoHandWeapon == FALSE )
			{
				SkillLeftMaxDamage = SkillRightMaxDamage;
				SkillLeftMinDamage = SkillRightMinDamage;
			}

			SkillRightMaxDamage += lpObj->SetOpAddSkillAttack;
			SkillRightMinDamage += lpObj->SetOpAddSkillAttack;
			SkillLeftMaxDamage += lpObj->SetOpAddSkillAttack;
			SkillLeftMinDamage += lpObj->SetOpAddSkillAttack;

			int SkillAttr = MagicDamageC.GetSkillAttr(lpMagic->m_Skill);

			if (SkillAttr != -1)
			{
				if ((lpObj->Authority & 32) == 32 && (lpObj->pInventory[10].m_Type == ITEMGET(13, 42) || lpObj->pInventory[11].m_Type == ITEMGET(13, 42))) //season 2.5 add-on
				{
					SkillRightMaxDamage += (BYTE)255;
					SkillRightMinDamage += (BYTE)255;
					SkillLeftMaxDamage += (BYTE)255;
					SkillLeftMinDamage += (BYTE)255;
				}
				else
				{
					SkillRightMaxDamage += (BYTE)lpObj->m_AddResistance[SkillAttr];
					SkillRightMinDamage += (BYTE)lpObj->m_AddResistance[SkillAttr];
					SkillLeftMaxDamage += (BYTE)lpObj->m_AddResistance[SkillAttr];
					SkillLeftMinDamage += (BYTE)lpObj->m_AddResistance[SkillAttr];
				}
			}

			SkillRightMaxDamage += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
			SkillRightMinDamage += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
			SkillLeftMaxDamage += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
			SkillLeftMinDamage += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;

			if ( lpMagic->m_Skill == 65 )
			{
				int iPartyCount = this->GetPartyMemberCount(lpObj);
				int addskilldamage = ( lpObj->Leadership + lpObj->AddLeadership ) / 10 + ( iPartyCount * 50 );	// #formula

				SkillRightMaxDamage += addskilldamage;
				SkillRightMinDamage += addskilldamage;
				SkillLeftMaxDamage += addskilldamage;
				SkillLeftMinDamage += addskilldamage;
			}
			else if( lpMagic->m_Skill == 62 )
			{
				if ( lpObj->pInventory[8].m_Type == ITEMGET(13,4) )	// Dark Horse
				{
					int addskilldamage = ( lpObj->Strength + lpObj->AddStrength ) / 10 + ( lpObj->Leadership + lpObj->AddLeadership ) / 5 + lpObj->pInventory[8].m_PetItem_Level * 10;	// #formula

					SkillRightMaxDamage += addskilldamage;
					SkillRightMinDamage += addskilldamage;
					SkillLeftMaxDamage += addskilldamage;
					SkillLeftMinDamage += addskilldamage;
				}
			}
			else if ( lpObj->Class == CLASS_DARKLORD )
			{
				int iadddamage = ( lpObj->Strength + lpObj->AddStrength ) / 25 + ( lpObj->Energy + lpObj->AddEnergy ) / 50;	// #formula

				SkillRightMaxDamage += iadddamage;
				SkillRightMinDamage += iadddamage;
				SkillLeftMaxDamage += iadddamage;
				SkillLeftMinDamage += iadddamage;
			}
		}

		if ( lpObj->m_CriticalDamage > 0 )
		{
			if ( (rand()%100) < lpObj->m_CriticalDamage )
			{
				cDamage = TRUE;
				effect = 3;
			}
		}

		if ( lpObj->m_ExcelentDamage > 0 )
		{
			if ( (rand()%100) < lpObj->m_ExcelentDamage )
			{
				cDamage = TRUE;
				effect = 2;
			}
		}

		__try
		{
			sub = ( lpObj->m_AttackDamageMaxRight + SkillRightMaxDamage ) - ( lpObj->m_AttackDamageMinRight + SkillRightMinDamage );	// #formula
			lpObj->m_AttackDamageRight = ( lpObj->m_AttackDamageMinRight + SkillRightMinDamage ) + (rand()%(sub+1));
		}
		__except ( sub=1, 1 )
		{

		}

		__try
		{
			sub = ( lpObj->m_AttackDamageMaxLeft + SkillLeftMaxDamage ) - ( lpObj->m_AttackDamageMinLeft + SkillLeftMinDamage );	// #formula
			lpObj->m_AttackDamageLeft = ( lpObj->m_AttackDamageMinLeft + SkillLeftMinDamage ) + (rand()%(sub+1));
		}
		__except ( sub=1, 1 )
		{

		}

		if ( cDamage )
		{
			lpObj->m_AttackDamageRight = lpObj->m_AttackDamageMaxRight + SkillRightMaxDamage;
			lpObj->m_AttackDamageLeft = lpObj->m_AttackDamageMaxLeft + SkillLeftMaxDamage;

			lpObj->m_AttackDamageRight += lpObj->SetOpAddCriticalDamage;
			lpObj->m_AttackDamageLeft += lpObj->SetOpAddCriticalDamage;

			lpObj->m_AttackDamageRight += lpObj->m_JewelOfHarmonyEffect.HJOpAddCriticalDamage;
			lpObj->m_AttackDamageLeft += lpObj->m_JewelOfHarmonyEffect.HJOpAddCriticalDamage;

			lpObj->m_AttackDamageRight += lpObj->SkillAddCriticalDamage;
			lpObj->m_AttackDamageLeft += lpObj->SkillAddCriticalDamage;

			if ( effect == 2 )
			{
				lpObj->m_AttackDamageRight += ( lpObj->m_AttackDamageMaxRight + SkillRightMaxDamage ) * 20 / 100;
				lpObj->m_AttackDamageLeft += ( lpObj->m_AttackDamageMaxLeft + SkillLeftMaxDamage ) * 20 / 100;

				lpObj->m_AttackDamageRight += lpObj->SetOpAddExDamage;
				lpObj->m_AttackDamageLeft += lpObj->SetOpAddExDamage;
			}
		}
	}

	if ( bTwoHandWeapon )
	{
		if ( bIsOnDuel )
		{
			ad = ( lpObj->m_AttackDamageRight + lpObj->m_AttackDamageLeft ) * 60 / 100 - targetDefense;
		}
		else
		{
			ad = ( lpObj->m_AttackDamageRight + lpObj->m_AttackDamageLeft ) - targetDefense;
		}
	}
	else if ( (Left->m_Type >= ITEMGET(4, 0) && Left->m_Type < ITEMGET(4, 7)) ||
			 Left->m_Type == ITEMGET(4,20) || Left->m_Type == ITEMGET(4,21)  )
	{
		if ( bIsOnDuel )
		{
			ad = ( lpObj->m_AttackDamageLeft ) * 60 / 100 - targetDefense;
		}
		else
		{
			ad = lpObj->m_AttackDamageLeft - targetDefense;
		}
	}
	else if ( (Right->m_Type >= ITEMGET(4, 8) && Right->m_Type < ITEMGET(4, 15)) ||
			  ( Right->m_Type >= ITEMGET(4,16) && Right->m_Type < ITEMGET(5,0) )  )
	{
		if ( bIsOnDuel )
		{
			ad = ( lpObj->m_AttackDamageRight ) * 60 / 100 - targetDefense;
		}
		else
		{
			ad = lpObj->m_AttackDamageRight - targetDefense;
		}
	}
	else if ( Right->m_Type >= ITEMGET(0,0) && Right->m_Type < ITEMGET(4,0) )
	{
		if ( bIsOnDuel )
		{
			ad = ( lpObj->m_AttackDamageRight ) * 60 / 100 - targetDefense;
		}
		else
		{
			ad = lpObj->m_AttackDamageRight - targetDefense;
		}
	}
	else if ( Right->m_Type >= ITEMGET(5,0) && Right->m_Type < ITEMGET(6,0) )
	{
		if ( bIsOnDuel )
		{
			ad = ( lpObj->m_AttackDamageRight ) * 60 / 100 - targetDefense;
		}
		else
		{
			ad = lpObj->m_AttackDamageRight - targetDefense;
		}
	}
	else if ( bIsOnDuel )
	{
		ad = ( lpObj->m_AttackDamageLeft ) * 60 / 100 - targetDefense;
	}
	else
	{
		ad = lpObj->m_AttackDamageLeft - targetDefense;
	}

	if ( lpObj->SetOpTwoHandSwordImproveDamage )
	{
		ad += ad * lpObj->SetOpTwoHandSwordImproveDamage  / 100;
	}

	ad += lpObj->m_SkillAttack;
	
	if ( lpObj->m_SkillAttack2 )
	{
		ad += 15;
	}

	if ( lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttackTime > 0 )
	{
		ad += lpObj->m_MonsterSkillElementInfo.m_iSkillElementAttack;

		if ( ad < 0 )
		{
			ad = 0;
		}
	}

	return ad;
}





int  CObjAttack::GetAttackDamageWizard(LPOBJ lpObj, int targetDefense, CMagicInf* lpMagic, BYTE& effect, BOOL bIsOnDuel)
{
	if (Configs.g_ShieldSystemOn == TRUE)
	{
		if ( bIsOnDuel == TRUE )
		{
			bIsOnDuel = FALSE;
		}
	}

	int damagemin;
	int damagemax;
	int ad;

	if ( lpMagic->m_Skill == 40 )
	{
		if ( lpObj->SkillHellFire2Count >= 0 )
		{
			int SkillHellFire2CountDamageTable[13] =
			{
				0,	20,	50,	99,	160,
				225,	325,	425,	550,	700,
				880,	1090,	1320
			};
			int CountDamage;

			if ( lpObj->SkillHellFire2Count > 12 )
			{
				CountDamage = 0;
			}
			else
			{
				CountDamage = SkillHellFire2CountDamageTable[lpObj->SkillHellFire2Count];
			}

			ad = ( lpObj->Strength + lpObj->AddStrength ) / 2 + CountDamage;
			damagemin = ad + lpObj->m_MagicDamageMin;
			damagemax = ad + lpObj->m_MagicDamageMax;

			damagemin += lpObj->SetOpAddSkillAttack;
			damagemax += lpObj->SetOpAddSkillAttack;

			int SkillAttr = MagicDamageC.GetSkillAttr(lpMagic->m_Skill);

			if (SkillAttr != -1)
			{
				if ((lpObj->Authority & 32) == 32 && (lpObj->pInventory[10].m_Type == ITEMGET(13, 42) || lpObj->pInventory[11].m_Type == ITEMGET(13, 42))) //season 2.5 add-on
				{
					damagemin += (BYTE)255;
					damagemax += (BYTE)255;
				}
			}

			damagemin += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
			damagemax += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
		}
	}
	else
	{
		ad = lpMagic->GetDamage();

		damagemin = lpMagic->m_DamageMin + lpObj->m_MagicDamageMin;
		damagemax = lpMagic->m_DamageMax + lpObj->m_MagicDamageMax;

		damagemin += lpObj->SetOpAddSkillAttack;
		damagemax += lpObj->SetOpAddSkillAttack;

		int SkillAttr = MagicDamageC.GetSkillAttr(lpMagic->m_Skill);

		if (SkillAttr != -1)
		{
			if ((lpObj->Authority & 32) == 32 && (lpObj->pInventory[10].m_Type == ITEMGET(13, 42) || lpObj->pInventory[11].m_Type == ITEMGET(13, 42))) //season 2.5 add-on
			{
				damagemin += (BYTE)255;
				damagemax += (BYTE)255;
			}
		}

		damagemin += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
		damagemax += lpObj->m_JewelOfHarmonyEffect.HJOpAddSkillAttack;
	}

	CItem * Right = &lpObj->pInventory[0];

	if ( Right->IsItem() )
	{
		if ( (Right->m_Type >= ITEMGET(5,0) && Right->m_Type < ITEMGET(6,0) ) ||
			 Right->m_Type == ITEMGET(0,31) ||
			 Right->m_Type == ITEMGET(0,21) ||
			 Right->m_Type == ITEMGET(0,23) ||
			 Right->m_Type == ITEMGET(0,25) )
		{
			if ( Right->m_IsValidItem  )
			{
				int damage = Right->m_Magic / 2 + Right->m_Level * 2;	// #formula
				damage -= (WORD)(Right->m_CurrentDurabilityState * damage);	// #formula

				damagemin += damagemin * damage / 100;	// #formula
				damagemax += damagemax * damage / 100;	// #formula
			}
		}
	}

	int subd = damagemax - damagemin;

	__try
	{
		if ( bIsOnDuel )
		{
			ad = ( damagemin + (rand()%(subd+1)) ) * 60 / 100 - targetDefense;	// #formula
		}
		else
		{
			ad = ( damagemin + (rand()%(subd+1)) ) - targetDefense;
		}

		if ( lpObj->m_CriticalDamage > 0 )
		{
			if ( (rand()%100) < lpObj->m_CriticalDamage )
			{
				if ( bIsOnDuel )
				{
					ad = damagemax * 60 / 100 - targetDefense;
				}
				else
				{
					ad = damagemax - targetDefense;
				}

				ad += lpObj->SetOpAddCriticalDamage;
				ad += lpObj->m_JewelOfHarmonyEffect.HJOpAddCriticalDamage;
				ad += lpObj->SkillAddCriticalDamage;
				effect = 3;
			}
		}

		if ( lpObj->m_ExcelentDamage > 0 )
		{
			if ( (rand()%100) < lpObj->m_ExcelentDamage )
			{
				if ( bIsOnDuel )
				{
					ad = damagemax * 60 / 100 - targetDefense;
				}
				else
				{
					ad = damagemax - targetDefense;
				}

				ad += damagemax * 20 / 100;
				ad += lpObj->SetOpAddExDamage;
				effect = 2;
			}
		}
	}
	__except ( subd=1, 1 )
	{

	}

	ad += lpObj->m_SkillAttack;

	if ( lpObj->m_SkillAttack2 )
	{
		ad += 10;
	}

	return ad;
}




BOOL gObjDenorantSprite(LPOBJ lpObj)
{
	if ( lpObj->Type != OBJ_USER )
	{
		return FALSE;
	}

	if ( lpObj->pInventory[8].IsItem() == FALSE )
	{
		return FALSE;
	}

	CItem * Denorant = & lpObj->pInventory[8];

	if ( Denorant->m_Type == ITEMGET(13,3) )
	{
		if ( Denorant->m_Durability > 0.0f )
		{
			return TRUE;
		}
	}

	return FALSE;
}




BOOL gObjDarkHorse(LPOBJ lpObj)
{
	if ( lpObj->Type != OBJ_USER )
	{
		return FALSE;
	}

	if ( lpObj->pInventory[8].IsItem() == FALSE )
	{
		return FALSE;
	}

	CItem * Denorant = & lpObj->pInventory[8];

	if ( Denorant->m_Type == ITEMGET(13,4) )
	{
		if ( Denorant->m_Durability > 0.0f )
		{
			return TRUE;
		}
	}

	return FALSE;
}



BOOL gObjFenrir(LPOBJ lpObj)
{
	if ( lpObj->Type != OBJ_USER )
	{
		return FALSE;
	}

	if ( lpObj->pInventory[8].IsItem() == FALSE )
	{
		return FALSE;
	}

	CItem * lpFenrir = & lpObj->pInventory[8];

	if ( lpFenrir->m_Type == ITEMGET(13,37) )	// Fenrir
	{
		if ( lpFenrir->m_Durability > 0.0f )
		{
			return TRUE;
		}
	}

	return FALSE;
}


int CObjAttack::GetShieldDamage(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage)
{
	int iShieldDamage = 0;

	if (Configs.g_ShieldSystemOn == FALSE)
		return 0;

	if ( iAttackDamage <= 0 )
		return 0;

	int iReduceLife = 0;
	int iReduceShield = 0;
	int iReduceLifeForEffect = 0; 
	bool bReduceShieldGage = 0;
	int iDamageDevideToSDRate = Configs.g_iDamageDevideToSDRate;
	iDamageDevideToSDRate -= lpObj->m_JewelOfHarmonyEffect.HJOpDecreaseSDRate;
	iDamageDevideToSDRate += lpTargetObj->m_JewelOfHarmonyEffect.HJOpAddSDRate;

	if ( iDamageDevideToSDRate < 0 )
		iDamageDevideToSDRate = 0;

	if ( iDamageDevideToSDRate > 100 )
		iDamageDevideToSDRate = 100;

	if ( lpObj->m_JewelOfHarmonyEffect.HJOpAddIgnoreSDRate > 0 )
	{
		int iRand = rand()%100;

		if ( iRand < lpObj->m_JewelOfHarmonyEffect.HJOpAddIgnoreSDRate )
		{
			iDamageDevideToSDRate = 0;
		}
	}

	if ( lpObj->m_JewelOfHarmonyEffect.HJOpDecreaseSDRate ||
		 lpTargetObj->m_JewelOfHarmonyEffect.HJOpAddSDRate ||
		 lpObj->m_JewelOfHarmonyEffect.HJOpAddIgnoreSDRate )
	{
		LogAddTD("[JewelOfHarmony][PvP System] Attacker:[%s][%s]-SD Decrease[%d] SD Ignore[%d] Defender:[%s][%s] SD Increase Option[%d] - SD Rate[%d]",
			lpObj->AccountID, lpObj->Name,
			lpObj->m_JewelOfHarmonyEffect.HJOpDecreaseSDRate,
			lpObj->m_JewelOfHarmonyEffect.HJOpAddIgnoreSDRate,
			lpTargetObj->AccountID, lpTargetObj->Name,
			lpTargetObj->m_JewelOfHarmonyEffect.HJOpAddSDRate,
			iDamageDevideToSDRate);
	}

	iReduceShield = iAttackDamage * iDamageDevideToSDRate / 100;
	iReduceLife = iAttackDamage - iReduceShield;

	if ( (lpTargetObj->iShield-iReduceShield) <0 )
	{
		iReduceLife += iReduceShield  - lpTargetObj->iShield;
		iReduceShield = lpTargetObj->iShield;

		if ( lpTargetObj->iShield > 0 )
		{
			bReduceShieldGage = true;
		}
	}

	iReduceLifeForEffect = ( lpTargetObj->MaxLife + lpTargetObj->AddLife ) * 20.0f / 100.0f;

	if ( bReduceShieldGage == true && iReduceLife > iReduceLifeForEffect )
	{
		if ( !CC_MAP_RANGE(lpTargetObj->MapNumber) )
		{
			GCSendEffectInfo(lpTargetObj->m_Index, 17);
		}
	}

	return iReduceShield;
}
