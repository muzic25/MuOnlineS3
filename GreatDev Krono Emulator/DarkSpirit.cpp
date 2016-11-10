#include "StdAfx.h"
#include "DarkSpirit.h"

CDarkSpirit gDarkSpirit[OBJMAX];

CDarkSpirit::CDarkSpirit() : m_ActionMode(PetItem_Mode_Normal)
{
	this->Init();
}





CDarkSpirit::~CDarkSpirit()
{
	return;
}





void CDarkSpirit::Init()
{
	this->m_AttackDamageMin = 0;
	this->m_AttackDamageMax = 0;
	this->m_AttackSpeed = 0;
	this->m_SuccessAttackRate = 0;
	this->m_dwLastAttackTime = 0;
	this->m_iMasterIndex = -1;
	this->m_iTargetIndex = -1;
	this->m_pPetItem = NULL;
}





void CDarkSpirit::Run()
{
	if ( this->m_iMasterIndex == -1 )
	{
		return;
	}

	LPOBJ lpObj = &gObj[this->m_iMasterIndex];

	if ( lpObj->Class != 4 ) // dñl
	{
		return;
	}

	if ( this->m_pPetItem == NULL )
	{
		return;
	}

	if ( this->m_pPetItem->m_Durability <= 0.0f )
	{
		return;
	}

	BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ( (attr&1) != 0 )
	{
		return;
	}

	if ( this->m_dwLastAttackTime > GetTickCount() )
	{
		return;
	}

	this->m_dwLastAttackTime = ( GetTickCount() + 1500 ) - ( this->m_AttackSpeed * 10 );

	switch ( this->m_ActionMode )
	{
		case PetItem_Mode_Normal:
			this->ModeNormal();
			break;

		case PetItem_Mode_Attack_Random:
			this->ModeAttackRandom();
			break;

		case PetItem_Mode_Attack_WithMaster:
			this->ModeAttackWithMaster();
			break;

		case PetItem_Mode_Attack_Target:
			this->ModeAttakTarget();
			break;
	}
}





void CDarkSpirit::ModeNormal()
{
	LPOBJ lpObj = &gObj[this->m_iMasterIndex];
}




void CDarkSpirit::ModeAttackRandom()
{
	LPOBJ lpObj = &gObj[this->m_iMasterIndex];
	int tObjNum;
	int count = 0;
	int FindObj[MAX_VIEWPORT];
	int FindObjCount = 0;
	int dis;
	int DuelIndex = lpObj->m_iDuelUser;
	BOOL EnableAttack;
	int criticaldamage = 0;

	if ( (rand()%10) < 3 )
	{
		criticaldamage = 1;
	}

	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state != 0 )
		{
			if ( lpObj->VpPlayer2[count].type == OBJ_MONSTER )
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if ( tObjNum >= 0 )
				{
					EnableAttack = FALSE;

					if ( gObj[tObjNum].Life > 0.0f && (gObj[tObjNum].Class < 100 || gObj[tObjNum].Class  > 110 ) )
					{
						if ( lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
						{
							EnableAttack = TRUE;
						}
						else if ( DuelIndex == tObjNum )
						{
							EnableAttack = TRUE;
						}
						else
						{
							int lc85 = gObj[tObjNum].m_Index;

							if ( gObj[tObjNum].Type == OBJ_MONSTER )
							{
								if ( gObj[tObjNum].m_RecallMon >= 0 )
								{
									lc85 = gObj[gObj[tObjNum].m_RecallMon].m_Index; 
								}
							}

							if ( gObjTargetGuildWarCheck(lpObj, &gObj[lc85]) == TRUE )
							{
								EnableAttack = TRUE;
							}
						}

						if ( EnableAttack != FALSE )
						{
							if ( lpObj->MapNumber == gObj[tObjNum].MapNumber )
							{
								dis = gObjCalDistance(lpObj, &gObj[tObjNum]);

								if ( dis < RAVEN_ATTACK_DISTANCE-2 )
								{
									FindObj[FindObjCount] = tObjNum;
									FindObjCount++;
								}
							}
						}
					}
				}
			}
		}

		count++;

		if ( count > MAX_VIEWPORT-1 )
		{
			break;
		}
	}

	if ( FindObjCount != 0 )
	{
		if ( criticaldamage != 0 )
		{
			int target = FindObj[rand()%FindObjCount];
			this->SendAttackMsg( lpObj->m_Index, target, criticaldamage, 0);
		}
		else
		{
			int target = FindObj[rand()%FindObjCount];
			this->RangeAttack( lpObj->m_Index, target);
		}
	}
}






void CDarkSpirit::ModeAttackWithMaster()
{
	LPOBJ lpObj = &gObj[this->m_iMasterIndex];
	int count = 0;
	int dis;

	if ( this->m_iTargetIndex == -1 )
	{
		return;
	}

	if ( lpObj->MapNumber == gObj[this->m_iTargetIndex].MapNumber )
	{
		if ( gObj[this->m_iTargetIndex].Life > 0.0f )
		{
			dis = gObjCalDistance(lpObj, &gObj[this->m_iTargetIndex]);

			if ( dis < RAVEN_ATTACK_DISTANCE )
			{
				int criticaldamage = 0;

				if ( (rand()%10) < 3 )
				{
					criticaldamage = FALSE;
				}

				if ( criticaldamage != FALSE )
				{
					this->SendAttackMsg(lpObj->m_Index, this->m_iTargetIndex, criticaldamage, 0);
				}
				else
				{
					this->RangeAttack(lpObj->m_Index, this->m_iTargetIndex);
				}
			}
		}
		else
		{
			this->ReSetTarget(this->m_iTargetIndex);
		}
	}
}






void CDarkSpirit::ModeAttakTarget()
{
	LPOBJ lpObj = &gObj[this->m_iMasterIndex];
	int count = 0;
	int dis;

	if ( this->m_iTargetIndex == -1 )
	{
		return;
	}

	if ( lpObj->MapNumber == gObj[this->m_iTargetIndex].MapNumber )
	{
		if ( gObj[this->m_iTargetIndex].Life > 0.0f )
		{
			dis = gObjCalDistance(lpObj, &gObj[this->m_iTargetIndex]);

			if ( dis < RAVEN_ATTACK_DISTANCE )
			{
				int criticaldamage = TRUE;
				int msg = 1;	// Attack with picada

				if ( criticaldamage != FALSE )
				{
					this->SendAttackMsg(lpObj->m_Index, this->m_iTargetIndex, criticaldamage, msg);
				}
				else
				{
					this->RangeAttack(lpObj->m_Index, this->m_iTargetIndex);
				}
			}
		}
		else
		{
			this->ReSetTarget(this->m_iTargetIndex);
		}
	}
}






void CDarkSpirit::RangeAttack(int aIndex, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	int count = 0;
	int loopcount = 0;
	int attackcheck;
	int EnableAttack;
	int HitCount = 0;

	this->SendAttackMsg(lpObj->m_Index, aTargetIndex, 0, 0);

	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state != 0 )
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if ( tObjNum >= 0 && aTargetIndex != tObjNum )
			{
				EnableAttack = FALSE;
				
				if ( lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = TRUE;
				}
				else if ( tObjNum == aTargetIndex )
				{
					EnableAttack = TRUE;
				}
				else
				{
					int lc10 = gObj[tObjNum].m_Index;

					if ( gObj[tObjNum].Type == OBJ_MONSTER )
					{
						if ( gObj[tObjNum].m_RecallMon >= 0 )
						{
							lc10 = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}
					}

					if ( gObjTargetGuildWarCheck(lpObj, &gObj[lc10]) == TRUE )
					{
						EnableAttack = TRUE;
					}
				}

				if ( EnableAttack != FALSE )
				{
					attackcheck = FALSE;

					if ( loopcount == 0 )
					{
						attackcheck = TRUE;
					}
					else if ( (rand()%3) == 0 )
					{
						attackcheck = TRUE;
					}

					if ( attackcheck != FALSE )
					{
						if ( gObjCalDistance(&gObj[aTargetIndex], &gObj[tObjNum]) < RAVEN_ATTACK_DISTANCE-3 )
						{
							this->SendAttackMsg(lpObj->m_Index, tObjNum, 2, 0);
							HitCount++;

							if ( HitCount > 3 )
							{
								break;
							}
						}
					}
				}
			}				
		}

		count++;

		if ( count > MAX_VIEWPORT-1 )
		{
			break;
		}
	}
}



struct PMSG_PET_ITEM_ATTACK_COMMAND
{
	PBMSG_HEAD h;	// C1:A8
	BYTE PetType;	//	3
	BYTE SkillType;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
	BYTE TargetNumberH;	// 7
	BYTE TargetNumberL;	// 8
};


void CDarkSpirit::SendAttackMsg(int aIndex, int aTargetIndex, int criticaldamage, int iActionType)
{
	PMSG_PET_ITEM_ATTACK_COMMAND pMsg;

	if ( criticaldamage != 2 )
	{
		pMsg.PetType = 0;
		pMsg.SkillType = (criticaldamage)? 0 : 1;
		pMsg.NumberH = SET_NUMBERH(aIndex);
		pMsg.NumberL = SET_NUMBERL(aIndex);
		pMsg.TargetNumberH = SET_NUMBERH(aTargetIndex);
		pMsg.TargetNumberL = SET_NUMBERL(aTargetIndex);
		pMsg.h.set((LPBYTE)&pMsg, 0xA8, sizeof(pMsg));
		
		DataSend(aIndex, (UCHAR*)&pMsg, pMsg.h.size);
		MsgSendV2(&gObj[aIndex], (UCHAR*)&pMsg, pMsg.h.size);

		if ( iActionType == 1 )
		{
			criticaldamage = 0;
			
			if ( (rand()%10) < 3 )
			{
				criticaldamage = TRUE;
			}
		}
	}
	else
	{
		criticaldamage = 0;
	}

	gObjAddAttackProcMsgSendDelay(&gObj[aIndex], 51, aTargetIndex, 600, criticaldamage, iActionType);
}





void CDarkSpirit::SetTarget(int aTargetIndex)
{
	if ( this->m_iMasterIndex == -1 )
	{
		return;
	}

	LPOBJ lpObj = &gObj[this->m_iMasterIndex];

	if ( lpObj->Class != 4 )	// DL
	{
		return;
	}

	this->m_iTargetIndex = aTargetIndex;
}





void CDarkSpirit::ReSetTarget(int aTargetIndex)
{
	if ( this->m_iMasterIndex == -1 )
	{
		return;
	}

	LPOBJ lpObj = &gObj[this->m_iMasterIndex];

	if ( lpObj->Class != 4 )	// DL
	{
		return;
	}

	if ( aTargetIndex == this->m_iTargetIndex )
	{
		this->m_iTargetIndex = -1;

		if ( this->m_ActionMode == PetItem_Mode_Attack_Target )
		{
			this->SetMode(PetItem_Mode_Normal, -1);
		}
	}
}




struct PMSG_SEND_PET_ITEM_COMMAND
{
	PBMSG_HEAD h;	// C1:A7
	BYTE PetType;	// 3
	BYTE Command;	// 4
	BYTE NumberH;	// 5
	BYTE NumberL;	// 6
};

void CDarkSpirit::SetMode(ePetItem_Mode mode, int iTargetindex)
{
	if ( this->m_iMasterIndex == -1 )
	{
		return;
	}

	LPOBJ lpObj = &gObj[this->m_iMasterIndex];

	if ( lpObj->Class != CLASS_DARKLORD )	// DL
	{
		return;
	}

	if ( mode == PetItem_Mode_Attack_Target || this->m_ActionMode != mode)
	{
		if ( mode == PetItem_Mode_Attack_Target )
		{
			if ( OBJMAX_RANGE(iTargetindex) != FALSE )
			{
				this->m_iTargetIndex = iTargetindex;
			}
			else
			{
				return;
			}
		}

		this->m_ActionMode = mode;
		PMSG_SEND_PET_ITEM_COMMAND pMsg;

		pMsg.h.set((LPBYTE)&pMsg, 0xA7, sizeof(pMsg));
		pMsg.PetType = 0;
		pMsg.Command = mode;
		pMsg.NumberH = SET_NUMBERH(this->m_iTargetIndex);
		pMsg.NumberL = SET_NUMBERL(this->m_iTargetIndex);

		DataSend(this->m_iMasterIndex, (UCHAR*)&pMsg, sizeof(pMsg));

		char strMode[4][255] =
		{
			"[ÀÏ¹Ý]",
			"[·£´ý°ø°Ý]",
			"[ÁÖÀÎ°ú°°ÀÌ°ø°Ý]",
			"[»ç¿ëÀÚÁöÁ¤]"
		};
/*
		char szNormal[256] = "[Raven Mode Normal]";
		char szRandom[256] = "[Raven Mode Random]";
		char szMaster[256] = "[Raven Mode With Master]";
		char szTarget[256] = "[Raven Mode Attack Target]";*/
	}
}






void CDarkSpirit::Set(int aIndex, CItem * pPetItem)
{
	LPOBJ lpObj = &gObj[aIndex];

	if ( lpObj->Class != 4 )	// DL
	{
		return;
	}

	BOOL bChange = FALSE;

	if ( this->m_iMasterIndex == -1 )
	{
		bChange = TRUE;
	}

	this->Init();

	if ( pPetItem->m_Type != ITEMGET(13,5) ) // Talon of Dark Raven
	{
		return;
	}

	if ( pPetItem->m_Durability <= 0.0f )
	{
		return;
	}

	int petitemlevel = pPetItem->m_PetItem_Level;
	int leadership = lpObj->Leadership + lpObj->AddLeadership;
	this->m_AttackDamageMin = petitemlevel*15 + leadership/8 + 180;
	this->m_AttackDamageMax = petitemlevel*15 + leadership/4 + 200;
	this->m_AttackSpeed = petitemlevel * 4 / 5 + leadership / 50 + 20;
	this->m_SuccessAttackRate= petitemlevel + petitemlevel / 15 + 1000;
	this->m_iMasterIndex = aIndex;
	this->m_pPetItem = pPetItem;

	if ( bChange != FALSE )
	{
		this->SetMode(PetItem_Mode_Normal, -1);
	}
}





BOOL CDarkSpirit::Attack(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf * lpMagic, int criticaldamage, int iActionType)
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

	int skill = 0;
	
	if ( lpMagic )
		skill = lpMagic->m_Skill;

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
		}
	}

	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
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

			return TRUE;
		}
	}

	if ( lpObj->Type == OBJ_USER )
	{
		if ( !gObjIsConnected(lpObj))
		{
			return FALSE;
		}
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


	if ( g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
	{
		if ( lpObj->m_btCsJoinSide > 0 && lpObj->m_btCsJoinSide == lpTargetObj->m_btCsJoinSide )
		{
			return FALSE;
		}
	}

	lpObj->m_TotalAttackCount++;

	if ( this->CheckAttackArea(lpObj, lpTargetObj) == FALSE )
		return FALSE;

	lpCallObj = lpObj;
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

	int MSBFlag = 0;
	//MsgDamage = 0;
	
	if ( criticaldamage )
	{
		MsgDamage = 3;
	}
	else
	{
		MsgDamage = 0;
	}

	BOOL bAllMiss = FALSE;
	int AttackDamage = 0;

	if (Configs.g_ShieldSystemOn == TRUE)
	{
		if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
		{
			if ( !this->MissCheckPvP(lpObj, lpTargetObj, skill, skillSuccess, bAllMiss) )
			{
				return FALSE;
			}
		}
		else if ( !this->MissCheck(lpObj, lpTargetObj, skill, skillSuccess, bAllMiss) )
		{
			return FALSE;
		}

	}
	else if ( !this->MissCheck(lpObj, lpTargetObj, skill, skillSuccess, bAllMiss) )
	{
		return FALSE;
	}

	int targetdefense = this->GetTargetDefense(lpObj, lpTargetObj, MsgDamage);
	AttackDamage = this->GetAttackDamage(lpObj, targetdefense, bIsOnDuel, criticaldamage);

	if ( criticaldamage == 0 && iActionType == 0 )
	{
		AttackDamage /= 1.5;
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

	lpObj->pInventory[1].m_DurabilitySmall += AttackDamage * 2 / 100;

	if ( lpObj->pInventory[1].m_DurabilitySmall >= 800 )
	{
		lpObj->pInventory[1].m_DurabilitySmall = 0;
		lpObj->pInventory[1].m_Durability -= 1.0f;

		if ( lpObj->pInventory[1].m_Durability < 1.0f )
		{
			lpObj->pInventory[1].m_Durability = 0;
			int iPetExp = lpObj->pInventory[1].m_PetItem_Exp;

			if ( lpObj->pInventory[1].DecPetItemExp(10) )
			{
				LogAddTD("[%s][%s][PetItemExpDown] [%s] Level:[%d]Exp:[%d]DecExp[%d]",
					lpObj->AccountID, lpObj->Name, lpObj->pInventory[1].GetName(),
					lpObj->pInventory[1].m_PetItem_Level,
					lpObj->pInventory[1].m_PetItem_Exp, iPetExp - lpObj->pInventory[1].m_PetItem_Exp);

				this->Set(lpObj->m_Index, &lpObj->pInventory[1]);
				this->SendLevelmsg(lpObj->m_Index, 1, 0, 0xFF);
			}

			LogAddTD("[%s][%s] ´ÙÅ©½ºÇÇ¸´ÀÇ¹ßÅé Item is Broken because durability is exhausted [%d]",
				lpObj->AccountID, lpObj->Name, lpObj->pInventory[1].m_Number);
		}

		GCItemDurSend(lpObj->m_Index, 1, lpObj->pInventory[1].m_Durability, 0);
	}

	if ( gObjAngelSprite(lpTargetObj) == TRUE )
	{
		if ( AttackDamage > 1 )
		{
			float  damage = (AttackDamage * 8) / 10.0f;
			AttackDamage = damage;
		}
	}

	if ( gObjWingSprite(lpTargetObj) == TRUE )
	{
		CItem * Wing = &lpTargetObj->pInventory[7];

		if (AttackDamage > 1)
		{
			if (Wing->m_Type == ITEMGET(12, 36) || //season 2.5 add-on
				Wing->m_Type == ITEMGET(12, 37) ||
				Wing->m_Type == ITEMGET(12, 38) ||
				Wing->m_Type == ITEMGET(12, 39))
			{
				float damage = (float)(AttackDamage * (61 - (Wing->m_Level * 2))) / 100.0f;
				AttackDamage = (int)(damage);	//  #formula
			}
			else if (Wing->m_Type == ITEMGET(12, 40))
			{
				float damage = (float)(AttackDamage * (76 - (Wing->m_Level * 2))) / 100.0f;
				AttackDamage = (int)(damage);	//  #formula
			}
			else if (Wing->m_Type == ITEMGET(12, 41))
			{
				float damage = (float)(AttackDamage * (88 - (Wing->m_Level * 2))) / 100.0f;
				AttackDamage = (int)(damage);	//  #formula
			}
			else if (Wing->m_Type == ITEMGET(12, 42))
			{
				float damage = (float)(AttackDamage * (75 - (Wing->m_Level * 2))) / 100.0f;
				AttackDamage = (int)(damage);	//  #formula
			}
			else if (Wing->m_Type == ITEMGET(12, 43))
			{
				float damage = (float)(AttackDamage * (61 - (Wing->m_Level * 2))) / 100.0f;
				AttackDamage = (int)(damage);	//  #formula
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

		if (Configs.g_ShieldSystemOn == FALSE)
		{
			if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
			{
				if ( CC_MAP_RANGE(lpObj->MapNumber ) && CC_MAP_RANGE(lpTargetObj->MapNumber) )
				{
					AttackDamage = AttackDamage * 50 / 100;
				}
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
					else if (Configs.g_ShieldSystemOn == 0)
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
				if ( lpObj->m_iPotionBlessTime > 0 || lpObj->m_iPotionSoulTime > 0 )
				{
					AttackDamage += (AttackDamage * 20) / 100;
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

					AttackDamage = AttackDamage * 20 / 100;
				}
			}

			if ( lpTargetObj->Class == 277 )
			{
				if ( lpObj->m_iPotionBlessTime > 0 || lpObj->m_iPotionSoulTime > 0 )
				{
					AttackDamage += (AttackDamage * 20) / 100;
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

					AttackDamage = AttackDamage * 20 / 100;
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

	if ( lpTargetObj->Type == OBJ_MONSTER )
	{
		gObjAddMsgSendDelay(lpTargetObj, 0, lpObj->m_Index, 100, 0);
		lpTargetObj->LastAttackerID = lpObj->m_Index;

		if ( lpTargetObj->m_iCurrentAI )
		{
			lpTargetObj->m_Agro.IncAgro(lpObj->m_Index, AttackDamage / 100);
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
			else if (IT_MAP_RANGE(lpObj->MapNumber) || IT_MAP_RANGE(lpTargetObj->MapNumber)) //season 2.5 add-on
			{
				selfdefense = 0;
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

	if ( selfdefense == TRUE )
	{
		if ( !gObjTargetGuildWarCheck(lpObj, lpCallObj) )
		{
			gObjCheckSelfDefense(lpObj, lpCallObj->m_Index);
		}
	}

	if ( AttackDamage >= 5 )	// To make strong hit
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

	if ( lpObj->Type == OBJ_USER )
	{
		if ( lpObj->m_Change == 9 )
		{
			GCMagicAttackNumberSend(lpObj, 3, lpTargetObj->m_Index, 1);
		}
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

		//if ( g_ShieldSystemOn == TRUE )	// #error Remove the //
		//{
			AttackDamage -= iTotalShieldDamage;
		//}

		gObjLifeCheck(lpTargetObj, lpObj, AttackDamage, 0, MSBFlag, MsgDamage, skill, iTotalShieldDamage);
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

	return TRUE;
}





int  CDarkSpirit::GetAttackDamage(LPOBJ lpObj, int targetDefense, BOOL bIsOnDuel, int crititcaldamage)
{
	if (Configs.g_ShieldSystemOn == TRUE)
	{
		if ( bIsOnDuel == TRUE )
		{
			bIsOnDuel = FALSE;
		}
	}

	int ad;
	int sub = this->m_AttackDamageMax - this->m_AttackDamageMin;
	int AttackDamage;

	if ( crititcaldamage )
	{
		AttackDamage = this->m_AttackDamageMin + sub;
	}
	else
	{
		AttackDamage = this->m_AttackDamageMin + (rand()%(sub+1));
	}

	if ( ( lpObj->pInventory[0].m_Type >= ITEMGET(2,8) && lpObj->pInventory[0].m_Type <= ITEMGET(2,12) ) ||
		   lpObj->pInventory[0].m_Type == ITEMGET(2,13) ||
		   lpObj->pInventory[0].m_Type == ITEMGET(2,14) ||
		   lpObj->pInventory[0].m_Type == ITEMGET(2,15) )
	{
		int damage = lpObj->pInventory[0].m_Magic / 2;
		damage -= damage * lpObj->pInventory[0].m_CurrentDurabilityState;
		damage = AttackDamage * damage / 100;
		AttackDamage += damage;
	}

	if ( bIsOnDuel )
	{
		ad = AttackDamage * 60 / 100 - targetDefense;
	}
	else
	{
		ad = AttackDamage - targetDefense;
	}

	return ad;
}





BOOL CDarkSpirit::MissCheck(LPOBJ lpObj, LPOBJ lpTargetObj, int skill,  int skillSuccess, BOOL& bAllMiss)
{
	int SuccessAttackRate = 0;
	int TargetSuccessfulBlocking = lpTargetObj->m_SuccessfulBlocking;
	int MsgDamage = 0;

	if ( this->m_SuccessAttackRate < TargetSuccessfulBlocking )
	{
		bAllMiss = TRUE;
	}


	if (IT_MAP_RANGE(lpTargetObj->MapNumber) != FALSE) //Season2.5 add-on Illusion
	{
		if (g_IllusionTempleEvent.GetState(lpTargetObj->MapNumber) == 2)
		{
			if (lpTargetObj->Type == OBJ_USER)
			{
				if (g_IllusionTempleEvent.GetShieldSpellStatus(lpTargetObj->m_iIllusionTempleIndex, lpTargetObj->MapNumber) != FALSE)
				{
					GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
					return FALSE;
				}
			}
			if (lpObj->PartyNumber == lpTargetObj->PartyNumber)
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
				return FALSE;
			}
		}
	}

	if ( bAllMiss != FALSE )
	{
		if ( (rand()%100) >= 5 )
		{
			GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, MsgDamage, 0);
			return FALSE;
		}
	}
	else if ( this->m_SuccessAttackRate )
	{
		if ( (rand()%this->m_SuccessAttackRate) < TargetSuccessfulBlocking)
		{
			GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, MsgDamage, 0);
			return FALSE;
		}
	}

	return TRUE;
}



BOOL CDarkSpirit::MissCheckPvP(LPOBJ lpObj, LPOBJ lpTargetObj, int skill,  int skillSuccess, BOOL& bAllMiss)
{
	float iAttackRate = 0;
	float iDefenseRate = 0;
	int iAttackSuccessRate = 0;



	if (IT_MAP_RANGE(lpTargetObj->MapNumber) != FALSE) //Season2.5 add-on Illusion
	{
		if (g_IllusionTempleEvent.GetState(lpTargetObj->MapNumber) == 2)
		{
			if (lpTargetObj->Type == OBJ_USER)
			{
				if (g_IllusionTempleEvent.GetShieldSpellStatus(lpTargetObj->m_iIllusionTempleIndex, lpTargetObj->MapNumber) != FALSE)
				{
					GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
					return FALSE;
				}
			}
			if (lpObj->PartyNumber == lpTargetObj->PartyNumber)
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
				return FALSE;
			}
		}
	}


	if ( lpObj->Class == CLASS_KNIGHT )
	{
		iAttackRate = lpObj->Level * 3 + ( lpObj->Dexterity * 45) / 10;	// #formula
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		iAttackRate = lpObj->Level * 3 + ( lpObj->Dexterity * 4 );	// #formula
	}
	else if ( lpObj->Class == CLASS_ELF )
	{
		iAttackRate = lpObj->Level * 3 + ( lpObj->Dexterity * 6 ) / 10;	// #formula
	}
	else if ( lpObj->Class == CLASS_MAGUMSA )
	{
		iAttackRate = lpObj->Level * 3 + ( lpObj->Dexterity * 35 ) / 10;	// #formula
	}
	else if ( lpObj->Class == CLASS_WIZARD )
	{
		iAttackRate = lpObj->Level * 3 + ( lpObj->Dexterity * 4 );	// #formula
	}

	if ( lpTargetObj->Class == CLASS_KNIGHT )
	{
		iDefenseRate = lpTargetObj->Level * 2 + lpTargetObj->Dexterity / 2;	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_DARKLORD )
	{
		iDefenseRate = lpTargetObj->Level * 2 + lpTargetObj->Dexterity / 2;	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_ELF )
	{
		iDefenseRate = lpTargetObj->Level * 2 + lpTargetObj->Dexterity / 10;	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_MAGUMSA )
	{
		iDefenseRate = lpTargetObj->Level * 2 + lpTargetObj->Dexterity / 4;	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_WIZARD )
	{
		iDefenseRate = lpTargetObj->Level * 2 + lpTargetObj->Dexterity / 4;	// #formula
	}

	if ( iAttackRate <= 0.0f || iDefenseRate <= 0.0f || lpObj->Level <= 0 || (DWORD)lpTargetObj <= 0 )	// #error lpTargetObj
		return FALSE;

	iAttackRate += lpObj->m_ItemOptionExFor380.OpAddAttackSuccessRatePVP;
	iDefenseRate += lpTargetObj->m_ItemOptionExFor380.OpAddDefenseSuccessRatePvP;

	iAttackRate += lpObj->m_JewelOfHarmonyEffect.HJOpAddAttackSuccessRatePVP;
	iDefenseRate += lpTargetObj->m_JewelOfHarmonyEffect.HJOpAddDefenseSuccessRatePvP;

	float iExpressionA = ( iAttackRate * 10000.0f ) / ( iAttackRate + iDefenseRate );	// #formula
	float iExpressionB = ( lpObj->Level * 10000 ) / ( lpObj->Level + lpTargetObj->Level );	// #formula

	iExpressionA /= 10000.0f;
	iExpressionB /= 10000.0f;

	iAttackSuccessRate = 100.0f * iExpressionA * Configs.g_fSuccessAttackRateOption * iExpressionB;

	if ( (lpTargetObj->Level - lpObj->Level) >= 100 )
	{
		iAttackSuccessRate -= 5;
	}
	else if ( (lpTargetObj->Level - lpObj->Level) >= 200 )
	{
		iAttackSuccessRate -= 10;
	}
	else if ( (lpTargetObj->Level - lpObj->Level) >= 300 )
	{
		iAttackSuccessRate -= 15;
	}

	DWORD dwRate = rand() % 100;

	if ( dwRate > iAttackSuccessRate )
	{
		GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
		return FALSE;
	}

	return TRUE;
}

	


void CDarkSpirit::ChangeCommand(int command, int targetindex)
{
	CDarkSpirit::ePetItem_Mode setmode = PetItem_Mode_Normal;

	if ( command == PetItem_Mode_Normal )
	{
		setmode = PetItem_Mode_Normal;
	}
	else if ( command == PetItem_Mode_Attack_Random )
	{
		setmode = PetItem_Mode_Attack_Random;
	}
	else if ( command == PetItem_Mode_Attack_WithMaster )
	{
		setmode = PetItem_Mode_Attack_WithMaster;
	}
	else if ( command == PetItem_Mode_Attack_Target )
	{
		setmode = PetItem_Mode_Attack_Target;
	}

	this->SetMode(setmode, targetindex);
}


void __cdecl CDarkSpirit::SendLevelmsg(int aIndex, int nPos, int PetType, int InvenType)
{
	PMSG_SEND_PET_ITEMINFO pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0xA9, sizeof(pMsg));
	pMsg.PetType = PetType;
	pMsg.InvenType = 0xFE;
	pMsg.nPos = nPos;
	pMsg.Level = gObj[aIndex].pInventory[nPos].m_PetItem_Level;
	pMsg.Exp = gObj[aIndex].pInventory[nPos].m_PetItem_Exp;

	DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
}



int CDarkSpirit::GetShieldDamage(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage)
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
