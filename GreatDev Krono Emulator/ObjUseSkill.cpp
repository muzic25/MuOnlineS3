#include "StdAfx.h"
#include "ObjUseSkill.h"

CObjUseSkill gObjUseSkill;


CObjUseSkill::CObjUseSkill()
{
	return ;
}




CObjUseSkill::~CObjUseSkill()
{
	return;
}



int  CObjUseSkill::GetTargetLinePath(int sx, int sy, int tx, int ty, int * PathX, int * PathY, int distance)
{
	int x,y;
	int delta_x,delta_y;
	int half;

	int error = 0;

	int incx = 1,incy = 1;
	int dis;
	int count;

	if(sx > tx)
	{
		incx = -1;
		delta_x = sx - tx;
	}
	else
	{
		delta_x = tx - sx;
	}

	if(sy > ty)
	{
		incy = -1;
		delta_y = sy - ty;
	}
	else
	{
		delta_y = ty - sy;
	}

	dis = sqrt((float)(delta_x * delta_x + delta_y * delta_y));
	dis = distance - dis;

	count = 0;
	PathX[count] = sx;
	PathY[count] = sy;
	count++;

	if(delta_x > delta_y)
	{
		y = sy;
		half = delta_x / 2;

		if(incx > 0)
		{
			for(x = (sx+1); x <= (tx + dis); x++)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
		else
		{
			for(x = (sx-1); x >= (tx - dis);x--)
			{
				error += delta_y;

				if(error > half)
				{
					y += incy;
					error -= delta_x;
				}

				PathX[count] = x;
				PathY[count] = y;

				count++;
			}
		}
	}
	else
	{
		x = sx;
		half = delta_y / 2;

		if(incy > 0)
		{
			for(y = (sy+1); y <= (ty + dis);y++)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
		else
		{
			for(y = (sy-1);y >= (ty - dis);y--)
			{
				error += delta_x;

				if(error > half)
				{
					x += incx;
					error -= delta_y;
				}

				PathX[count] = x;
				PathY[count] = y;
				count++;
			}
		}
	}
	return count;
}




BOOL CObjUseSkill::SpeedHackCheck(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];


	int iTimeCalc = GetTickCount() - lpObj->m_LastAttackTime;

	if(iTimeCalc < lpObj->m_DetectSpeedHackTime && iTimeCalc != 0)
	{
		lpObj->m_DetectCount++;
		lpObj->m_SumLastAttackTime += iTimeCalc;

		if (lpObj->m_DetectCount > Configs.gHackCheckCount)
		{
			lpObj->m_DetectedHackKickCount++;

			if (Configs.gIsKickDetecHackCountLimit != 0 && lpObj->m_DetectedHackKickCount > Configs.gDetectedHackKickCount)
			{
				LogAddTD("[%s][%s] %s Kick DetecHackCountLimit Over User (%d)",
					lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectedHackKickCount);
				CloseClient(aIndex);
				return false;
			}

			lpObj->m_SpeedHackPenalty = Configs.gSpeedHackPenalty;
			LogAddTD("[%s][%s] %s Attack Speed Is Wrong MagicSkill (%d)(%d) Penalty %d",
				lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class+1900),lpObj->m_DetectSpeedHackTime,lpObj->m_SumLastAttackTime / lpObj->m_DetectCount,lpObj->m_SpeedHackPenalty);
		}
	}
	else
	{
		lpObj->m_SumLastAttackTime = 0;
		lpObj->m_DetectCount = 0;
	}

	lpObj->m_LastAttackTime = GetTickCount();

	if (Configs.bIsIgnorePacketSpeedHackDetect != 0 && lpObj->m_SpeedHackPenalty > 0)
	{
		lpObj->m_SpeedHackPenalty--;
		LogAddTD("[%s][%s] %s Apply Attack Speed Penalty (%d left)",
			lpObj->AccountID,lpObj->Name,lMsg.Get(lpObj->Class + 1900),lpObj->m_SpeedHackPenalty);
		return false;
	}
	return true;
}




BOOL CObjUseSkill::EnableSkill(BYTE Skill)
{
	if(Skill != AT_SKILL_STORM
		&& Skill != AT_SKILL_EVIL
		&& Skill != AT_SKILL_FLAME
		&& Skill != AT_SKILL_HELL
		&& Skill != AT_SKILL_BLAST
		&& Skill != AT_SKILL_INFERNO
		&& Skill != AT_SKILL_CROSSBOW
		&& Skill != AT_SKILL_DEVILFIRE
		&& Skill != AT_SKILL_FLASH
		&& Skill != AT_SKILL_WHEEL
		&& Skill != AT_SKILL_SWORD6
		&& Skill != AT_SKILL_KNIGHTSPEAR
		&& Skill != AT_SKILL_KNIGHTADDLIFE
		&& Skill != AT_SKILL_STRIKE
		&& Skill != AT_SKILL_KNIGHTDINORANT
		&& Skill != AT_SKILL_ELFHARDEN
		&& Skill != AT_SKILL_PENETRATION
		&& Skill != AT_SKILL_DEFENSEDOWN
		&& Skill != AT_SKILL_MAGICDEFENSE
		&& Skill != AT_SKILL_BLOWOFFURY
		&& Skill != AT_SKILL_EXPPOISON
		&& Skill != AT_SKILL_EXPICE
		&& Skill != AT_SKILL_EXPHELL
		&& Skill != AT_SKILL_ELECTRICSPARK
		&& Skill != AT_SKILL_DARKHORSE_ATTACK
		&& Skill != AT_SKILL_BRAND_OF_SKILL
		&& Skill != AT_SKILL_STUN
		&& Skill != AT_SKILL_REMOVAL_STUN
		&& Skill != AT_SKILL_ADD_MANA
		&& Skill != AT_SKILL_INVISIBLE 
		&& Skill != AT_SKILL_REMOVAL_INVISIBLE
		&& Skill != AT_SKILL_REMOVAL_MAGIC
		&& Skill != AT_SKILL_FENRIR_ATTACK
		&& Skill != AT_SKILL_INFINITY_ARROW
		&& Skill != AT_SKILL_FIRESCREAM)
	{
		return false;
	}
	return true;
}




int  CObjUseSkill::GetUseMana(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj =&gObj[aIndex];
	float mana = lpObj->Mana;

	if ( lpObj->Type != OBJ_USER )
	{
		return 0;
	}

	if ( lpMagic == NULL )
	{
		return 0;
	}

	mana -= MagicDamageC.SkillGetMana(lpMagic->m_Skill);

	mana -= this->GetAddUseMana(lpObj,lpMagic);

	if(mana < 0.0f)
	{
		return -1;
	}
	return mana;
}



int CObjUseSkill::GetAddUseMana(LPOBJ lpObj,CMagicInf * lpMagic)
{
	int iRetValue = 0;

	if(lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER && lpObj->ChangeUP == 1 && lpObj->m_iMuseElfInfinityArrowSkillTime > 0)
	{
		if(lpMagic->m_Skill == AT_SKILL_CROSSBOW
			|| lpMagic->m_Skill == AT_SKILL_BOW
			|| lpMagic->m_Skill == AT_SKILL_ELFHARDEN
			|| lpMagic->m_Skill == AT_SKILL_PENETRATION
			|| lpMagic->m_Skill == AT_SKILL_5CROSSBOW)
		{
			int iArrowLevel = 0;

			CItem * Right = &lpObj->pInventory[0];
			CItem * Left = &lpObj->pInventory[1];

			if(Right->m_Type >= ITEMGET(4,8) && Right->m_Type <= ITEMGET(4,14)
				|| Right->m_Type == ITEMGET(4,16)
				|| Right->m_Type == ITEMGET(4,18)
				|| Right->m_Type == ITEMGET(4,19))
			{
				if(Left->m_Type == ITEMGET(4,7))
				{
					iArrowLevel = Left->m_Level;
				}
			}
			else if(Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,6)
				|| Left->m_Type == ITEMGET(4,17)
				|| Left->m_Type == ITEMGET(4,20)
				|| Left->m_Type == ITEMGET(4,21)
				|| Left->m_Type == ITEMGET(4,22))
			{
				if(Right->m_Type == ITEMGET(4,15))
				{
					iArrowLevel = Right->m_Level;
				}
			}

			if(iArrowLevel == 0)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus0();
			}
			else if(iArrowLevel == 1)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus1();
			}
			else if(iArrowLevel == 2)
			{
				iRetValue = g_SkillAdditionInfo.GetInfinityArrowMPConsumptionPlus2();
			}
		}
	}
	return iRetValue;
}


int  CObjUseSkill::GetUseBP(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	int bp = lpObj->BP;

	if(lpObj->Type != OBJ_USER)
	{
		return 0;
	}

	if(lpMagic == 0)
	{
		return 0;
	}

	int usingbp = MagicDamageC.SkillGetBP(lpMagic->m_Skill);

	usingbp -= usingbp * lpObj->SetOpDecreaseAG / 100;

	bp -= usingbp;

	if(bp < 0)
	{
		return -1;
	}

	return bp;
}




void CObjUseSkill::UseSkill(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

	PMSG_DURATION_MAGIC_SEND pMsg;

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] 스킬 딜레이시간 오버",gObj[aIndex].Name);
			return;
		}

		int usebp = gObjMagicBPUse(&gObj[aIndex],lpMagic);

		if(usebp >= 0)
		{
			lpObj->UseMagicNumber = lpMagic->m_Skill;
			lpObj->UseMagicTime = GetTickCount();
			lpObj->UseMagicCount = 0;

			lpObj->Mana = usemana;
			lpObj->BP = usebp;

			GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);

			PHeadSetBE((PBYTE)&pMsg,0x1E,sizeof(pMsg));

			pMsg.MagicNumber = lpMagic->m_Skill;
			pMsg.X = x;
			pMsg.Y = y;
			pMsg.Dir = dir;
			pMsg.NumberH = SET_NUMBERH(aIndex);
			pMsg.NumberL = SET_NUMBERL(aIndex);

			if(lpObj->Type == OBJ_USER)
			{
				DataSend(lpObj->m_Index,(PBYTE)&pMsg,pMsg.h.size);
			}

			if(CC_MAP_RANGE(lpObj->MapNumber))
			{
				switch(lpMagic->m_Skill)
				{
				case AT_SKILL_MAGICDEFENSE:
				case AT_SKILL_HEALING:
				case AT_SKILL_DEFENSE:
				case AT_SKILL_ATTACK:
				case AT_SKILL_KNIGHTADDLIFE:
					break;
				default: 
					MsgSendV2(lpObj,(PBYTE)&pMsg,pMsg.h.size);
				}
			}
			else
			{
				MsgSendV2(lpObj,(PBYTE)&pMsg,pMsg.h.size);
			}
		}

		if(lpMagic->m_Skill == AT_SKILL_SWORD6)
		{
			this->SkillPowerSlash(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}

		if(lpMagic->m_Skill == AT_SKILL_EXPPOISON)
		{
			this->SkillDeathPoison(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_EXPICE)
		{
			this->SkillSuddenIce(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_BLOWOFFURY)
		{
			this->SkillBlowOfFury(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_WHEEL)
		{
			this->SkillWheel(aIndex,lpMagic,aTargetIndex,bCombo);
		}
		else if(lpMagic->m_Skill == AT_SKILL_ELECTRICSPARK)
		{
			this->SkillElectricSpark(aIndex,lpMagic,x,y,dir,TargetPos,aTargetIndex);
		}
		else if(lpMagic->m_Skill == AT_SKILL_DARKHORSE_ATTACK)
		{
			this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
		}
		else if(lpMagic->m_Skill == AT_SKILL_STUN)
		{
			this->SkillStun(aIndex,aTargetIndex,lpMagic,x,y,dir,TargetPos);
		}
		else if(lpMagic->m_Skill == AT_SKILL_FENRIR_ATTACK)
		{
			this->SkillFenrirAttack(aIndex,aTargetIndex,lpMagic);
		}
	}
}




void CObjUseSkill::UseSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	int bCombo = 0;

	if(gComboAttack.CheckCombo(aIndex,lpMagic->m_Skill))
	{
		bCombo = 1;
	}

	if(lpObj->SkillHellFire2State && lpMagic->m_Skill != AT_SKILL_EXPHELL)
	{
		CMagicInf * lpMagic = gObjGetMagicSearch(lpObj,AT_SKILL_EXPHELL);

		if(lpMagic != 0)
		{
			gObjUseSkill.RunningSkill(lpObj->m_Index,0,lpMagic,0);
		}

		return;
	}

	if(lpMagic->m_Skill == AT_SKILL_EXPHELL && aTargetIndex != 58)
	{
		this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo);
		lpObj->UseMagicNumber = lpMagic->m_Skill;
		lpObj->UseMagicTime = GetTickCount();
		lpObj->UseMagicCount = 0;
		return;
	}

	int usemana = this->GetUseMana(aIndex,lpMagic);

	if(usemana >= 0)
	{
		if(!gObj[aIndex].SkillDelay.Check(lpMagic->m_Skill))
		{
			LogAddTD("[%] 스킬 딜레이시간 오버",gObj[aIndex].Name);
			return;
		}

		int usebp = this->GetUseBP(aIndex,lpMagic);

		if(usebp >= 0)
		{
			if(this->RunningSkill(aIndex,aTargetIndex,lpMagic,bCombo)==1)
			{
				lpObj->UseMagicNumber = lpMagic->m_Skill;
				lpObj->UseMagicTime = GetTickCount();
				lpObj->UseMagicCount = 0;

				lpObj->Mana = usemana;
				lpObj->BP = usebp;

				GCManaSend(aIndex,lpObj->Mana,0xFF,0,lpObj->BP);
			}
		}
	}
}




BOOL CObjUseSkill::RunningSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BOOL bCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	BYTE MagicNumber = lpMagic->m_Skill;

	lpObj->m_SkillNumber = MagicNumber;

	if(lpObj->m_iSkillInvisibleTime > 0)
	{
		this->RemoveCloakingEffect(lpObj->m_Index);
	}

	switch(MagicNumber)
	{
	case AT_SKILL_BLOCKING:
		if(lpObj->pInventory[1].IsItem() == 1)
		{
			if(lpObj->pInventory[1].m_Type >= ITEMGET(6,4) && lpObj->pInventory[1].m_Type < ITEMGET(7,0))
			{
				if(lpObj->pInventory[1].m_Option1 != 0)
				{
					lpObj->m_SkillTime = GetTickCount() + 4000;
					GCActionSend(lpObj,18,lpObj->m_Index,aTargetIndex);
				}
			}
		}
		break;
	case AT_SKILL_POISON:
	case AT_SKILL_METEO:
	case AT_SKILL_THUNDER:
	case AT_SKILL_FIREBALL:
	case AT_SKILL_FLAME:
	case AT_SKILL_SLOW:
	case AT_SKILL_ENERGYBALL:
	case AT_SKILL_SWORD1:
	case AT_SKILL_SWORD2:
	case AT_SKILL_SWORD3:
	case AT_SKILL_SWORD4:
	case AT_SKILL_SWORD5:
	case AT_SKILL_CROSSBOW:
	case AT_SKILL_BOW:
	case AT_SKILL_WHEEL:
	case AT_SKILL_BLOWOFFURY:
	case AT_SKILL_KNIGHTSPEAR:
	case AT_SKILL_PENETRATION:
	case AT_SKILL_SWORD6:
		gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0);
		break;
	case AT_SKILL_HEALING:	this->SkillHealing(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_MAGICDEFENSE:	this->WizardMagicDefense(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_KNIGHTADDLIFE:	this->KnightSkillAddLife(aIndex,lpMagic->m_Level);break;
	case AT_SKILL_DEFENSE:	this->SkillDefense(aIndex,aTargetIndex,lpMagic->m_Level);break;
	case AT_SKILL_ATTACK:	this->SkillAttack(aIndex,aTargetIndex,lpMagic->m_Level);break;

	case AT_SKILL_CALLMON1:	return this->SkillMonsterCall(lpObj->m_Index,26,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON2:	return this->SkillMonsterCall(lpObj->m_Index,32,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON3:	return this->SkillMonsterCall(lpObj->m_Index,21,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON4:	return this->SkillMonsterCall(lpObj->m_Index,20,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON5:	return this->SkillMonsterCall(lpObj->m_Index,10,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON6:	return this->SkillMonsterCall(lpObj->m_Index,150,lpObj->X-1,lpObj->Y+1);
	case AT_SKILL_CALLMON7:	return this->SkillMonsterCall(lpObj->m_Index,151,lpObj->X-1,lpObj->Y+1);

	case AT_SKILL_EXPHELL:	return this->SkillHellFire2(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_STRIKE:	return this->SkillKnightBlow(lpObj->m_Index,aTargetIndex,lpMagic,bCombo);

	case AT_SKILL_SPEAR:	return this->SkillSpear(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_FIREBURST:	return this->SkillFireBurst(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_DARKHORSE_ATTACK:	return this->SkillDarkHorseAttack(lpObj->m_Index,aTargetIndex,lpMagic);
	case AT_SKILL_RECALL_PARTY:	this->SkillRecallParty(aIndex,lpMagic->m_Level);break;
	case AT_SKILL_ADD_CRITICALDAMAGE:	this->SkillAddCriticalDamage(aIndex,lpMagic->m_Level);break;

	case AT_SKILL_DEFENSEDOWN:	this->MaGumSkillDefenseDown(lpObj->m_Index,aTargetIndex,1);break;

	case AT_SKILL_SUMMON:	this->SkillSummon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_MAGIC:	this->SkillImmuneToMagic(lpObj->m_Index,lpMagic);break;
	case AT_SKILL_IMMUNE_TO_HARM:	this->SkillImmuneToHarm(lpObj->m_Index,lpMagic);break;

	case AT_SKILL_RUSH:	this->SkillKnightRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_JAVALIN:	this->SkillWizardJavalin(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEEPIMPACT:	this->SkillElfRush(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_ONE_FLASH:	this->SkillMagumOneFlash(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_DEATH_CANNON:	this->SkillMagumDeathCannon(lpObj->m_Index,aTargetIndex,lpMagic);break;
	case AT_SKILL_SPACE_SPLIT:	this->SkillDarklordSpaceSplit(lpObj->m_Index,aTargetIndex,lpMagic);break;

	case AT_SKILL_BRAND_OF_SKILL:	this->SkillBrandOfSkill(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_REMOVAL_STUN:	this->SkillRemoveStun(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_ADD_MANA:	this->SkillAddMana(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_INVISIBLE:	this->SkillCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_INVISIBLE:	this->SkillRemoveCloaking(aIndex,aTargetIndex,lpMagic);break;
	case AT_SKILL_REMOVAL_MAGIC:	this->SkillRemoveMagic(aIndex,aTargetIndex,lpMagic);break;

	case AT_SKILL_INFINITY_ARROW:	this->SkillInfinityArrow(aIndex,aTargetIndex,lpMagic);break;

	default:	gObjAttack(lpObj,lpTargetObj,lpMagic,1,0,0,0);break;
	}

	return true;
}




void CObjUseSkill::MaGumSkillDefenseDown(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = 1;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->Type == OBJ_USER && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}
	LogAdd("마검사 몬스터방어력감소 : %d",10); // !!! Need Translation

	if(retCalcSkillResistance(lpTargetObj,1))
	{
		lpTargetObj->m_SkillMagumReduceDefense = 10;
		lpTargetObj->m_SkillMagumReduceDefenseTime = 10;
		lpTargetObj->m_ViewSkillState |= 64;

		GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSEDOWN,lpTargetObj->m_Index,skillSuccess);
	}
}




void CObjUseSkill::KnightSkillAddLife(int aIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];


#if (FOREIGN_GAMESERVER==1)
	if (szAuthKey[14] != AUTHKEY14 )
	{
		DestroyGIocp();
	}
#endif

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_KNIGHT && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	int number;
	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];

	int viewplayer = 0;
	int viewpercent = 0;

	LPOBJ lpPartyObj;

	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);

					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
						viewplayer++;
					}
				}
			}
		}
	}

	if(viewplayer > 1)
	{
		if(viewplayer == 2)
		{
			viewpercent = 1;
		}
		else if(viewplayer == 3)
		{
			viewpercent = 2;
		}
		else if(viewplayer == 4)
		{
			viewpercent = 3;
		}
		else
		{
			viewpercent = 4;
		}
	}

	int iaddLifepower = 12 + (lpObj->Vitality + lpObj->AddVitality) / 100 + (lpObj->Energy + lpObj->AddEnergy)/20 + viewpercent;
	int iLifeTime = 60 + (lpObj->Energy + lpObj->AddEnergy) / 10;
	int iaddlife;

	if(partynum == -1)
	{
		iaddlife = int(lpObj->MaxLife) * iaddLifepower / 100;
		lpObj->AddLife -= lpObj->m_SkillAddLife;
		lpObj->AddLife += iaddlife;

		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);

		lpObj->m_SkillAddLife = iaddlife;
		lpObj->m_SkillAddLifeTime = iLifeTime;

		lpObj->m_ViewSkillState |= 16;
		GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			if(ApplyPartyIndex[n]!= -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];

				iaddlife = int(lpPartyObj->MaxLife) * iaddLifepower / 100;
				lpPartyObj->AddLife -= lpPartyObj->m_SkillAddLife;
				lpPartyObj->AddLife += iaddlife;

				GCReFillSend(lpPartyObj->m_Index,lpPartyObj->MaxLife + lpPartyObj->AddLife,0xFE,0,lpPartyObj->iMaxShield + lpPartyObj->iAddShield);

				lpPartyObj->m_SkillAddLife = iaddlife;
				lpPartyObj->m_SkillAddLifeTime = iLifeTime;

				lpPartyObj->m_ViewSkillState |= 16;
				GCMagicAttackNumberSend(lpObj,AT_SKILL_KNIGHTADDLIFE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}




void CObjUseSkill::WizardMagicDefense(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = true;

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon== -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_WIZARD && lpObj->Class != CLASS_MAGUMSA)
	{
		return;
	}

	if(lpObj->PartyNumber != lpTargetObj->PartyNumber)
	{
		return;
	}

	lpTargetObj->m_WizardSkillDefense = 10 + (lpObj->Dexterity + lpObj->AddDexterity) / 50 + (lpObj->Energy + lpObj->AddEnergy) / 200;
	lpTargetObj->m_WizardSkillDefenseTime = 60 + (lpObj->Energy + lpObj->AddEnergy) / 40;
	lpTargetObj->m_ViewSkillState |= 256;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_MAGICDEFENSE,lpTargetObj->m_Index,skillSuccess);
}




void CObjUseSkill::SkillDefense(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	float skill_defense = float(skill_level + 1)*2 + (lpObj->Energy + lpObj->AddEnergy) / 8;

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_defense += skill_defense/10.0f;
	}

	lpTargetObj->m_SkillDefense = skill_defense;
	lpTargetObj->m_SkillDefenseTime = 60;
	lpTargetObj->m_ViewSkillState |= 8;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_defense)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DEFENSE,lpTargetObj->m_Index,skillSuccess);
}




void CObjUseSkill::SkillAttack(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	float skill_attack = float((skill_level + 1) * 3) + (lpObj->Energy + lpObj->AddEnergy) / 7.0f;

	if(lpTargetObj->Class == CLASS_KNIGHT)
	{
		skill_attack += skill_attack/10.0f;
	}

	lpTargetObj->m_SkillAttack = skill_attack;
	lpTargetObj->m_SkillAttackTime = 60;
	lpTargetObj->m_ViewSkillState |= 4;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
		{
			LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
			if(lpMonster->m_iCurrentAI != 0)
			{
				lpMonster->m_Agro.IncAgro(lpObj->m_Index,int(skill_attack)/10);
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ATTACK,lpTargetObj->m_Index,skillSuccess);
}




BOOL CObjUseSkill::SkillChangeUse(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int skill_level = -1;

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[10].m_Level;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,10))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = lpObj->pInventory[11].m_Level;
		}
	}

	if(skill_level > 7)
	{
		return false;
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,39))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 372;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,40))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,40))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 373;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,41))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,41))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 374;
		}
	}

	if(lpObj->pInventory[10].IsItem()==1 && lpObj->pInventory[10].m_Type == ITEMGET(13,42))
	{
		if(lpObj->pInventory[10].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 378;
		}
	}

	if(lpObj->pInventory[11].IsItem()==1 && skill_level == -1 && lpObj->pInventory[11].m_Type == ITEMGET(13,42))
	{
		if(lpObj->pInventory[11].m_Durability < 1.0f)
		{
			skill_level = -1;
		}
		else
		{
			skill_level = 378;
		}
	}

	if (IT_MAP_RANGE(lpObj->MapNumber) != FALSE) //Season2.5 add-on (illusion temple checks)
	{
		if (g_IllusionTempleEvent.GetState(lpObj->MapNumber) != 0)
		{
			int ebp10 = g_IllusionTempleEvent.GetUserJoinSide(lpObj->MapNumber, lpObj->m_Index);
			if (ebp10 == 0)
			{
				skill_level = 404;
			}
			else if (ebp10 == 1)
			{
				skill_level = 405;
			}
		}
	}

	int change = -1;

	switch(skill_level)
	{
	case 0: change = 2;	break;
	case 1: change = 7; break;
	case 2: change = 14;	break;
	case 3: change = 8;	break;
	case 4:	change = 9;	break;
	case 5:	change = 41;	break;
	case 372:	change = skill_level;	break;
	case 373:	change = skill_level;	break;
	case 374:	change = skill_level;	break;
	case 378:	change = skill_level;	break;
	case 404:	change = skill_level;	break;//season 2.5
	case 405:   change = skill_level;	break;

	default: change = -1;	break;
	}

	if(lpObj->m_Change >= 0 && lpObj->m_Change == change)
	{
		return false;
	}

	if(lpObj->m_Change == 41 && change != 41)
	{
		lpObj->AddLife = 0;

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if(lpObj->m_Change == 372 && change != 372)
	{
		lpObj->AddLife = 0;
		gObjCalCharacter(lpObj->m_Index);

		GCReFillSend(lpObj->m_Index,lpObj->Life,0xFF,0,lpObj->iShield);
		GCReFillSend(lpObj->m_Index,lpObj->MaxLife + lpObj->AddLife,0xFE,0,lpObj->iMaxShield + lpObj->iAddShield);
	}

	if (lpObj->m_Change == 374) //Season 2.5 add-on
	{
		if (change != 374)
		{
			lpObj->m_AttackDamageMaxLeft -= 20;
			lpObj->m_AttackDamageMinLeft -= 20;
			lpObj->m_AttackDamageMaxRight -= 20;
			lpObj->m_AttackDamageMinRight -= 20;
			lpObj->m_MagicDamageMin -= 20;
			lpObj->m_MagicDamageMax -= 20;
		}
	}

	if(lpObj->m_Change >= 0 && lpObj->m_iPeriodItemEffectIndex != -1)
	{
		GCStateInfoSend(lpObj, 0, 0x8000000);
	}

	lpObj->m_Change = change;
	gObjViewportListProtocolCreate(lpObj);
	 
	g_CastleSiege.NotifySelfCsJoinSide(lpObj->m_Index); 

	PMSG_KILLCOUNT pMsg = {0};

	PHeadSubSetB((LPBYTE)&pMsg,0xB8,0x01,sizeof(pMsg));

	pMsg.btKillCount = lpObj->m_btKillCount;

	DataSend(aIndex,(PBYTE)&pMsg,sizeof(pMsg));

	return true;
}




void CObjUseSkill::SkillHealing(int aIndex, int aTargetIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpTargetObj->Type != OBJ_USER && lpTargetObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_ELF)
	{
		return;
	}

	if(CC_MAP_RANGE(lpObj->MapNumber) && lpObj->m_Index != lpTargetObj->m_Index)
	{
		return;
	}

	if(skill_level < 0 || skill_level > 7)
	{
		skill_level = 0;
	}

	lpTargetObj->Life = ((skill_level + 1) * 5 + (lpObj->Energy + lpObj->AddEnergy) / 5) + lpTargetObj->Life;

	if((lpTargetObj->MaxLife + lpTargetObj->AddLife) < lpTargetObj->Life)
	{
		lpTargetObj->Life = lpTargetObj->MaxLife + lpTargetObj->AddLife;
	}

	if(lpTargetObj->Type == OBJ_USER)
	{
		GCReFillSend(lpTargetObj->m_Index,lpTargetObj->Life,0xFF,0,lpTargetObj->iShield);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_HEALING,lpTargetObj->m_Index,skillSuccess);

		for(int n = 0; n < MAX_VIEWPORT; n++)
		{
			if(lpObj->VpPlayer2[n].type == OBJ_MONSTER && lpObj->VpPlayer2[n].state != 0)
			{
				LPOBJ lpMonster = &gObj[lpObj->VpPlayer2[n].number];
				if(lpMonster->m_iCurrentAI != 0)
				{
					lpMonster->m_Agro.IncAgro(lpObj->m_Index,(lpObj->Energy / 5)/40);
				}
			}
		}
	}
	else if(lpTargetObj->m_RecallMon >= 0)
	{
		GCRecallMonLife(lpTargetObj->m_RecallMon,lpTargetObj->MaxLife,lpTargetObj->Life);
	}
}




int CObjUseSkill::SkillMonsterCall(int aIndex, int MonsterType, int x, int y)
{
	if(gObj[aIndex].MapNumber == MAP_INDEX_ICARUS)
	{
		return false;
	}

	if(CC_MAP_RANGE(gObj[aIndex].MapNumber))
	{
		return false;
	}

	if(gObj[aIndex].m_RecallMon >= 0)
	{
		GCRecallMonLife(aIndex,60,0);
		gObjMonsterCallKill(aIndex);
		return false;
	}

	int result = gObjAddCallMon();

	if(result >= 0)
	{
		gObj[result].X = x;
		gObj[result].Y = y;
		gObj[result].MTX = x;
		gObj[result].MTY = y;
		gObj[result].Dir = 2;
		gObj[result].MapNumber = gObj[aIndex].MapNumber;
		gObjSetMonster(result,MonsterType);
		gObj[result].m_RecallMon = aIndex;
		gObj[result].m_Attribute = 100;
		gObj[result].TargetNumber = (WORD)-1;
		gObj[result].m_ActState.Emotion = 0;
		gObj[result].m_ActState.Attack = 0;
		gObj[result].m_ActState.EmotionCount = 0;
		gObj[result].PathCount = 0;

		gObj[aIndex].m_RecallMon = result;
		gObj[result].m_MoveRange = 15;

		GCRecallMonLife(gObj[result].m_RecallMon,gObj[result].MaxLife,gObj[result].Life);
		return true;
	}
	return false;
}




void CObjUseSkill::SkillBlowOfFury(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int HitCount = 0;
	int bAttack = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{

					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 4)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,isCombo);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,aIndex,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}




void CObjUseSkill::SkillWheel(int aIndex, CMagicInf* lpMagic, int aTargetIndex, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 3)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{

							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo);

							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}




void CObjUseSkill::SkillPowerSlash(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE targetangle, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	::SkillFrustrum(targetangle,aIndex);
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0);
						}

						HitCount++;
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
}




int CObjUseSkill::SkillDeathPoison(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];


	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delay,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




int CObjUseSkill::SkillSuddenIce(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int FirstHit = 0;
	int HitCount = 0;
	int bAttack;
	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(this->CalDistance(x,y,gObj[tObjNum].X,gObj[tObjNum].Y) < 4)
					{
						bAttack = 0;

						if(HitCount > 10)
						{
							bAttack = 0;
						}
						
						if(HitCount >= 5)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							int delay = rand()%500;
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,1,1,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(aTargetIndex == 58)
	{
		return this->SkillHellFire2Start(aIndex,lpMagic);
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->SkillHellFire2State == 0)
	{
		LogAddTD("[%s][%s] 헬파이어2 버튼 눌러지지도 않았는데 완료가 되었다",lpObj->AccountID,lpObj->Name);
		return false;
	}

	lpObj->SkillHellFire2State = 0;
	int count = 0;
	lpObj->SkillHellFire2Time = 0;

	LPOBJ lpTargetObj = &gObj[aTargetIndex];
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(aTargetIndex == tObjNum || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
				else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
						gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					EnableAttack = 1;
				} 
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 6)
					{
						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,600,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL,lpObj->m_Index,1);
	return true;
}




BOOL CObjUseSkill::SkillHellFire2Start(int aIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->SkillHellFire2State != 0)
	{
		LogAddTD("[%s][%s] 헬파이어2 버튼 눌러졌는데 또 눌러졌다는거 왔다",lpObj->AccountID,lpObj->Name);
		return false;
	}

	lpObj->SkillHellFire2Time = GetTickCount();
	lpObj->SkillHellFire2State = 1;
	lpObj->SkillHellFire2Count = 0;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_EXPHELL_START,aIndex,1);
	return true;
}




BOOL CObjUseSkill::SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL isCombo)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	float fangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);

	this->SkillFrustrum(aIndex,fangle,1.5f,3.0f);

	int count = 0;
	int loopcount = 0;
	int attackcheck;
	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(::SkillTestFrustrum(gObj[tObjNum].X,gObj[tObjNum].Y,aIndex))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,isCombo);
							if(isCombo != 0)
							{
								GCMagicAttackNumberSend(lpObj,AT_SKILL_COMBO,gObj[tObjNum].m_Index,1);
							}
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			loopcount++;
			count = 0;
			if(loopcount >= 3)
			{
				break;
			}
		}
	}
	return true;
}




void CObjUseSkill::SkillFrustrum(int aIndex, float fangle, float tx, float ty)
{
	LPOBJ lpObj = &gObj[aIndex];

	float p[MAX_ARRAY_FRUSTRUM][3];

	p[0][0] = -tx;
	p[0][1] = ty;
	p[0][2] = 0;
	p[1][0] = tx;
	p[1][1] = ty;
	p[1][2] = 0;
	p[2][0] = 1.0f;
	p[2][1] = 0;
	p[2][2] = 0;
	p[3][0] = -1.0f;
	p[3][1] = 0;
	p[3][2] = 0;

	float Angle[3];

	Angle[0] = 0;
	Angle[1] = 0;
	Angle[2] = fangle;

	float Matrix[3][MAX_ARRAY_FRUSTRUM];
	float vFrustrum[MAX_ARRAY_FRUSTRUM][3];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < MAX_ARRAY_FRUSTRUM; i++)
	{
		VectorRotate((const float *)&p[i],(const float *)&Matrix[0],(float *)&vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}




void CObjUseSkill::SkillFrustrum2(int aIndex, float fangle, float tx, float ty)
{
	LPOBJ lpObj = &gObj[aIndex];


	float p[MAX_ARRAY_FRUSTRUM][3];

	p[0][0] = 0;
	p[0][1] = ty;
	p[0][2] = 0;
	p[1][0] = 0;
	p[1][1] = ty;
	p[1][2] = 0;
	p[2][0] = tx;
	p[2][1] = 1.0f;
	p[2][2] = 0;
	p[3][0] = -tx;
	p[3][1] = 1.0f;
	p[3][2] = 0;

	float Angle[3];

	Angle[0] = 0;
	Angle[1] = 0;
	Angle[2] = fangle;

	float Matrix[3][MAX_ARRAY_FRUSTRUM];
	float vFrustrum[MAX_ARRAY_FRUSTRUM][3];

	AngleMatrix(Angle,Matrix);

	for(int i = 0; i < MAX_ARRAY_FRUSTRUM; i++)
	{
		VectorRotate((const float *)&p[i],(const float *)&Matrix[0],(float *)&vFrustrum[i]);

		lpObj->fSkillFrustrumX[i] = (int)vFrustrum[i][0] + lpObj->X;
		lpObj->fSkillFrustrumY[i] = (int)vFrustrum[i][1] + lpObj->Y;
	}
}




int  CObjUseSkill::GetAngle(int x, int y, int tx, int ty)
{
	double diffX = x - tx;
	double diffY = y - ty;

	double rad = atan2(diffY,diffX);

	int angle = rad * 180 / Q_PI + 90;

	if(angle < 0)
	{
		angle += 360;
	}
	return angle;
}




int  CObjUseSkill::CalDistance(int x, int y, int x1, int y1)
{
	if(x == x1 && y == y1)
	{
		return 0;
	}

	float tx = x - x1;
	float ty = y - y1;

	return sqrt(tx*tx + ty*ty);
}




BOOL CObjUseSkill::SkillAreaCheck(int angel, int x, int y, int tx, int ty, int dis, int arc)
{
	int minangel = angel - arc;
	int maxangel = angel + arc;

	if(this->CalDistance(x,y,tx,ty) > dis)
	{
		return false;
	}

	int targetangle = this->GetAngle(x,y,tx,ty);

	if(minangel < 0)
	{
		if(targetangle > maxangel)
		{
			if(targetangle > minangel + 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(maxangel > 360)
	{
		if(targetangle < minangel)
		{
			if(targetangle < maxangel - 360)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(maxangel < targetangle)
		{
			return false;
		}
	}
	else if(minangel > targetangle)
	{
		return false;
	}
	else if(maxangel < targetangle)
	{
		return false;
	}
	return true;
}




BOOL CObjUseSkill::SkillSpear(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,gObj[aTargetIndex].X,gObj[aTargetIndex].Y);
	int count = 0;
	int loopcount = 0;
	int attackcheck;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	if(lpObj->SkillLongSpearChange == 0)
	{
		gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
		return true;
	}

	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(SkillSpearHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							gObjAttack(lpObj,&gObj[tObjNum],lpMagic,0,1,0,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillFireBurst(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int StartDis = 1;
	int tObjNum;
	int count = 0;
	int loopcount = 0;

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);

	int attackcheck;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;
	int delaytime;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0 && aTargetIndex != tObjNum)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				}
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					attackcheck = 0;

					if(loopcount == 0)
					{
						attackcheck = 1;
					}
					else if(rand()%3==0)
					{
						attackcheck = 1;
					}

					if(attackcheck != 0)
					{
						if(gObjCalDistance(&gObj[aTargetIndex],&gObj[tObjNum]) < 3)
						{
							delaytime = (rand()*17)%300 + 500;

							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillDarkHorseAttack(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_DARKHORSE_ATTACK,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;
				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
	
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					} 
					else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
							gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
							g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
					{
						EnableAttack = 1;
					} 
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;
	
						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}
	
						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
						{
							EnableAttack = 1;
						}
					}
				}
				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						bAttack = 0;

						if(HitCount > 15)
						{
							bAttack = 0;
						}

						if(HitCount >= 10)
						{
							if(rand()%2)
							{
								bAttack = 1;
							}
						}
						else
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,500,lpMagic->m_Skill,0);
						}
					}
				}
			}
		}
	
		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}
return true;
}




BOOL CObjUseSkill::RecallPartyCheck(int aIndex, int skill_level)
{
	LPOBJ lpObj = &gObj[aIndex];
	int number;
	int partynum = 0;

	partynum = lpObj->PartyNumber;

	int partycount;
	LPOBJ lpPartyObj;
	int recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{
					if(lpPartyObj->MapNumber == lpObj->MapNumber)
					{
						if(lpPartyObj->SkillRecallParty_Time != 0)
						{
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}




void CObjUseSkill::SkillRecallParty(int aIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(this->RecallPartyCheck(aIndex,skill_level) == 0)
	{
		MsgOutput(aIndex,lMsg.Get(1238));
		return;
	}

	if(gMoveCommand.CheckMainToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1249));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	if(gMoveCommand.CheckInterfaceToMove(lpObj) == 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1239));
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
		return;
	}

	int number;
	int partynum;
	int partycount;
	LPOBJ lpPartyObj;
	int recallcount;

	partynum = 0;
	partynum = lpObj->PartyNumber;

	GCMagicAttackNumberSend(lpObj,AT_SKILL_RECALL_PARTY,lpObj->m_Index,skillSuccess);

	recallcount = 0;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY;n ++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpPartyObj->m_Index != lpObj->m_Index)
				{ 
					if ( g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
					{
						if ( lpPartyObj->m_btCsJoinSide != lpObj->m_btCsJoinSide )
						{
							continue;
						}
					} 
					int movelevel = gMoveCommand.GetMoveLevel(lpObj->MapNumber,lpObj->X,lpObj->Y,lpPartyObj->Class);
					int bCheckMainToMove = gMoveCommand.CheckMainToMove(lpPartyObj);
					int bCheckEquipmentToMove = gMoveCommand.CheckEquipmentToMove(lpPartyObj,lpObj->MapNumber);
					int bCheckInterfaceToMove = gMoveCommand.CheckInterfaceToMove(lpPartyObj);

					if(lpPartyObj->Level >= movelevel
						&& movelevel != -1
						&& bCheckMainToMove != false
						&& bCheckEquipmentToMove != false
						&& bCheckInterfaceToMove != false)
					{
						int addx;
						int addy;
						int count = 50;
						int Find = 0;

						while(count--)
						{
							addx = lpObj->X + rand()%9 - 4;
							addy = lpObj->Y + rand()%9 - 4;

							if(gObjCheckTeleportArea(lpObj->m_Index,addx,addy))
							{
								Find = 1;
								break;
							}
						}

						if(Find == 0)
						{
							addx = lpObj->X;
							addy = lpObj->Y;
						}

						lpPartyObj->SkillRecallParty_Time = 7;
						lpPartyObj->SkillRecallParty_MapNumber = lpObj->MapNumber;
						lpPartyObj->SkillRecallParty_X = addx;
						lpPartyObj->SkillRecallParty_Y = addy;

						char msg[255];

						wsprintf(msg,lMsg.Get(1251));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
						recallcount++;
					}
					else
					{
						char msg[255];
						wsprintf(msg,lMsg.Get(1252));
						GCServerMsgStringSend(msg,lpPartyObj->m_Index,1);
					}
				}
			}
		}
	}

	if(recallcount != 0)
	{
		char msg[255];
		wsprintf(msg,lMsg.Get(1244),recallcount);
		GCServerMsgStringSend(msg,lpObj->m_Index,1);
	}
}




void CObjUseSkill::SkillAddCriticalDamage(int aIndex, int skill_level)
{
	int skillSuccess = true;
	LPOBJ lpObj = &gObj[aIndex];
	int number;

#if (FOREIGN_GAMESERVER==1)
	if (szAuthKey[14] != AUTHKEY14 )
	{
		DestroyGIocp();
	}
#endif

	if(lpObj->Type != OBJ_USER && lpObj->m_RecallMon == -1)
	{
		return;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return;
	}


	int partynum = 0;
	int totallevel = 0;
	int partycount;
	int dis;

	int ApplyPartyIndex[MAX_USER_IN_PARTY];
	LPOBJ lpPartyObj;
	memset(ApplyPartyIndex,-1,sizeof(ApplyPartyIndex));

	partynum = lpObj->PartyNumber;

	if(partynum != -1)
	{
		partycount = gParty.m_PartyS[partynum].Count;

		for(int n = 0; n < MAX_USER_IN_PARTY; n++)
		{
			number = gParty.m_PartyS[partynum].Number[n];

			if(number >= 0)
			{
				lpPartyObj = &gObj[number];

				if(lpObj->MapNumber == lpPartyObj->MapNumber)
				{
					dis = gObjCalDistance(lpObj,&gObj[number]);
					if(dis < 10)
					{
						ApplyPartyIndex[n] = lpPartyObj->m_Index;
					}
				}
			}
		}
	}

	int addcriticaldamagevalue = (lpObj->Leadership + lpObj->AddLeadership)/25 + (lpObj->Energy + lpObj->AddEnergy)/30;
	int SkillTime = (lpObj->Energy + lpObj->AddEnergy)/10 + 60;

	if(partynum == -1)
	{
		lpObj->SkillAddCriticalDamageTime = SkillTime;
		lpObj->SkillAddCriticalDamage = addcriticaldamagevalue;
		lpObj->m_ViewSkillState |= 2048;

		MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpObj->m_Index,skillSuccess);
	}
	else
	{
		for(int n = 0;n < MAX_USER_IN_PARTY;n++)
		{
			if(ApplyPartyIndex[n] != -1)
			{
				lpPartyObj = &gObj[ApplyPartyIndex[n]];

				lpPartyObj->SkillAddCriticalDamageTime = SkillTime;
				lpPartyObj->SkillAddCriticalDamage = addcriticaldamagevalue;
				lpPartyObj->m_ViewSkillState |= 2048;

				MsgOutput(aIndex,lMsg.Get(1240),SkillTime);
				GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_CRITICALDAMAGE,lpPartyObj->m_Index,skillSuccess);
			}
		}
	}
}




void CObjUseSkill::SkillElectricSpark(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (TargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((TargetPos & 240) >> 4));

	int tObjNum;
	int count = 0;
	int DuelIndex = lpObj->m_iDuelUser;
	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);
	int delaytime;
	int Hit = 0;
	int EnableAttack;

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
				{
					EnableAttack = 1;
				}
				else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
				{
					EnableAttack = 1;
				} 
					else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
							gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
							g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
					{
						EnableAttack = 1;
					}  
				else
				{
					int CallMonIndex = gObj[tObjNum].m_Index;

					if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
					{
						CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
					}

					if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex])==1)
					{
						EnableAttack = 1;
					}
				}

				if(EnableAttack != 0)
				{
					if(SkillElectricSparkHitBox.HitCheck(iangle,gObj[aIndex].X,gObj[aIndex].Y,gObj[tObjNum].X,gObj[tObjNum].Y))
					{
						delaytime = 500;
						Hit = 1;

						gObjAddAttackProcMsgSendDelay(lpObj,50,tObjNum,delaytime,lpMagic->m_Skill,0);
					}
				}
			}
		}

		count++;
		if(count > MAX_VIEWPORT -1)
		{
			break;
		}
	}

	if(Hit != 0)
	{
		DecPartyMemberHPandMP(lpObj);
	}
}




int  DecPartyMemberHPandMP(LPOBJ lpObj)
{
	LPOBJ lpPartyObj;
	int partynum = lpObj->PartyNumber;

	if(OBJMAX_RANGE(partynum)==false)
	{
		LogAdd("error : DecPartyMemberHPandMP %s %d",__FILE__,__LINE__);
		return false;
	}

	int partycount = gParty.m_PartyS[partynum].Count;
	int retcount = 0;

	for(int n = 0; n < MAX_USER_IN_PARTY;n++)
	{
		int number = gParty.m_PartyS[partynum].Number[n];

		if(number >= 0)
		{
			lpPartyObj = &gObj[number];

			if(lpObj->MapNumber == lpPartyObj->MapNumber && lpObj->m_Index != number)
			{
				int dis = gObjCalDistance(lpObj,&gObj[number]);
				if(dis < 10)
				{
					lpPartyObj = &gObj[number];

					int declife = lpPartyObj->Life * 20.0f / 100.0f;
					int decmana = lpPartyObj->Mana * 5.0f / 100.0f;

					lpPartyObj->Life = lpPartyObj->Life - declife;
					lpPartyObj->Mana = lpPartyObj->Mana - decmana;

					GCReFillSend(lpPartyObj->m_Index,lpPartyObj->Life,0xFF,0,lpPartyObj->iShield);
					GCManaSend(lpPartyObj->m_Index,lpPartyObj->Mana,0xFF,0,lpPartyObj->BP);
					retcount++;
				}
			}
		}
	}

	return retcount;
}




BOOL CObjUseSkill::SkillSummon(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex)==false)
	{
		return false;
	}

	int iSummonCount = 1;
	int iSummonMonterType = 0;
	BYTE bDoSummon = 1;
	BYTE bSummonSuccess = 0;
	BYTE cSummonX = 0;
	BYTE cSummonY = 0;

	LPOBJ lpObj = &gObj[aIndex];

	switch(lpObj->Class)
	{
	case 161:
		iSummonMonterType = rand()%2+ 147;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 181:
		iSummonMonterType = rand()%2+ 177;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 189:
		iSummonMonterType = rand()%2+ 185;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 197:
		iSummonMonterType = rand()%2+ 193;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 267:
		iSummonMonterType = rand()%2+ 263;
		bDoSummon = (rand()%15) ? false : true;
		break;
	case 275:
		iSummonMonterType = rand()%2+ 271;
		bDoSummon = (rand()%15) ? false : true;
		break;
	}

	if(bDoSummon == false)
	{
		return false;
	}

	for(int iSC = 0; iSC < iSummonCount; iSC++)
	{
		BYTE cSX = lpObj->X;
		BYTE cSY = lpObj->Y;

		if(gObjGetRandomFreeLocation(lpObj->MapNumber,(BYTE &)cSX,(BYTE &)cSY,2,2,30)==1)
		{
			int result = gObjAddMonster(lpObj->MapNumber);

			if(result >= 0)
			{
				gObj[result].m_PosNum = (WORD)-1;
				gObj[result].X = cSX;
				gObj[result].Y = cSY;
				gObj[result].MapNumber = lpObj->MapNumber;
				gObj[result].TX = gObj[result].X;
				gObj[result].TY = gObj[result].Y;
				gObj[result].m_OldX = gObj[result].X;
				gObj[result].m_OldY = gObj[result].Y;
				gObj[result].Dir = 1;
				gObj[result].StartX = gObj[result].X;
				gObj[result].StartY = gObj[result].Y;
				gObjSetMonster(result,iSummonMonterType);
				gObj[result].m_Attribute = 60;
				gObj[result].MaxRegenTime = 0;
				gObj[result].Dir = rand()%8;
				bSummonSuccess = 1;
				cSummonX = gObj[result].StartX;
				cSummonY = gObj[result].StartY;
			}
		}
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_SUMMON,(((cSummonX & 0xFF)&0xFF) | ((cSummonY & 0xFF)&0xFF) << 8) & 0xFFFF,bSummonSuccess);
	return bSummonSuccess;
}




BOOL CObjUseSkill::SkillImmuneToMagic(int aIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_ImmuneToMagicCount <= 0 && lpObj->m_ImmuneToHarmCount <= 0)
	{
		lpObj->m_ImmuneToMagicCount = 10;
		lpObj->m_ViewSkillState |= 128;
		GCStateInfoSend(lpObj,1,128);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_MAGIC,lpObj->m_Index,1);
		return true;
	}
	return false;
}




BOOL CObjUseSkill::SkillImmuneToHarm(int aIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_ImmuneToMagicCount <= 0 && lpObj->m_ImmuneToHarmCount <= 0)
	{
		lpObj->m_ImmuneToHarmCount = 10;
		lpObj->m_ViewSkillState |= 8;
		GCStateInfoSend(lpObj,1,8);
		GCMagicAttackNumberSend(lpObj,AT_SKILL_IMMUNE_TO_HARM,lpObj->m_Index,1);
		return true;
	}
	return false;
}


int CObjUseSkill::RemoveSpecificSkillState(LPOBJ lpObj, int iSkillNumber)
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	int iViewSkillState = 0;

	if(iSkillNumber == AT_SKILL_ATTACK)
	{
		lpObj->m_SkillAttackTime = 0;
		lpObj->m_SkillAttack = 0;
		iViewSkillState = 4;
	}
	else if(iSkillNumber == AT_SKILL_DEFENSE)
	{
		lpObj->m_SkillDefenseTime = 0;
		lpObj->m_SkillDefense = 0;
		iViewSkillState = 8;
	}

	lpObj->m_ViewSkillState &= ~iViewSkillState;
	GCStateInfoSend(lpObj,0,iViewSkillState);
	return true;
}


BOOL CObjUseSkill::RemoveAllCharacterInvalidMagicAndSkillState(LPOBJ lpObj)
{
	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	lpObj->m_SkillAttackTime = 0;
	lpObj->m_SkillAttack = 0;
	lpObj->m_ViewSkillState &= ~4;

	lpObj->m_SkillAttackTime2 = 0;
	lpObj->m_SkillAttack2 = 0;
	lpObj->m_SkillDefenseTime = 0;
	lpObj->m_SkillDefense = 0;
	lpObj->m_ViewSkillState &= ~8;

	lpObj->m_WizardSkillDefenseTime = 0;
	lpObj->m_WizardSkillDefense = 0;
	lpObj->m_ViewSkillState &= ~256;

	lpObj->m_SkillAddLifeTime = 0;
	lpObj->m_SkillAddLife = 0;
	lpObj->m_ViewSkillState &= ~16;

	lpObj->m_SkillHardenTime = 0;
	lpObj->m_SkillHarden = 0;
	lpObj->m_ViewSkillState &= ~32;

	lpObj->m_SkillMagumReduceDefenseTime = 0;
	lpObj->m_SkillMagumReduceDefense = 0;
	lpObj->m_ViewSkillState &= ~64;

	lpObj->SkillRecallParty_Time = 0;
	lpObj->SkillAddCriticalDamageTime = 0;
	lpObj->SkillAddCriticalDamage = 0;
	lpObj->m_ViewSkillState &= ~2048;

	lpObj->m_iSkillStunTime = 0;
	lpObj->m_ViewSkillState &= ~4096;

	lpObj->m_iSkillBrandOfSkillTime = 0;
	lpObj->m_ViewSkillState &= ~512;

	lpObj->m_iSkillInvisibleTime = 0;
	lpObj->m_ViewSkillState &= ~16384;

	lpObj->m_iSkillManaSwellTime = 0;
	lpObj->m_iSkillManaSwell = 0;
	lpObj->m_ViewSkillState &= ~8192;

	lpObj->m_PoisonBeattackCount = 0;
	lpObj->m_PoisonType = 0;
	lpObj->m_ViewSkillState &= ~1;

	lpObj->m_ColdBeattackCount = 0;
	lpObj->m_IceType = 0;
	lpObj->m_ViewSkillState &= ~2;

	lpObj->m_ImmuneToMagicCount = 0;
	lpObj->m_ImmuneToHarmCount = 0;

	lpObj->m_ViewSkillState &= ~128;
	lpObj->m_ViewSkillState &= ~8;

	lpObj->m_iMuseElfInfinityArrowSkillTime = 0;
	lpObj->m_ViewSkillState &= ~67108864;

	return true;
}




BOOL CObjUseSkill::SkillKnightRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	return true;
}




BOOL CObjUseSkill::SkillWizardJavalin(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);

	int iDelay = 500;

	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay,lpMagic->m_Skill,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,iDelay+200,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillElfRush(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,800,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumOneFlash(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,100,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillMagumDeathCannon(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAttack(lpObj,&gObj[aTargetIndex],lpMagic,0,1,0,0);
	return true;
}




BOOL CObjUseSkill::SkillDarklordSpaceSplit(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	GCMagicAttackNumberSend(lpObj,lpMagic->m_Skill,aTargetIndex,1);
	gObjAddAttackProcMsgSendDelay(lpObj,50,aTargetIndex,500,lpMagic->m_Skill,0);
	return true;
}




BOOL CObjUseSkill::SkillBrandOfSkill(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int count = 0;

	lpObj->m_iSkillBrandOfSkillTime = 10;
	lpObj->m_ViewSkillState |= 512;
	GCStateInfoSend(lpObj,1,512);

	GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
					{
						gObj[tObjNum].m_iSkillBrandOfSkillTime = 10;
						gObj[tObjNum].m_ViewSkillState |= 512;
						GCStateInfoSend(&gObj[tObjNum],1,512);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_BRAND_OF_SKILL,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BYTE btX, BYTE btY, BYTE btDir, BYTE btTargetPos)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	int TargePosx = lpObj->X - (8 - (btTargetPos & 15));
	int TargePosy = lpObj->Y - (8 - ((btTargetPos & 240) >> 4));

	int iangle = this->GetAngle(lpObj->X,lpObj->Y,TargePosx,TargePosy);

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			if(lpObj->VpPlayer2[count].type == OBJ_USER || lpObj->VpPlayer2[count].type == OBJ_MONSTER)
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if(OBJMAX_RANGE(tObjNum))
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) <= 4)
					{
						if(SkillElectricSparkHitBox.HitCheck(iangle,lpObj->X,lpObj->Y,gObj[tObjNum].X,gObj[tObjNum].Y))
						{
							gObj[tObjNum].m_iSkillStunTime = 10;
							gObj[tObjNum].m_ViewSkillState |= 4096;
							GCStateInfoSend(&gObj[tObjNum],1,4096);
							GCMagicAttackNumberSend(lpObj,AT_SKILL_STUN,tObjNum,1);
							gObjSetPosition(tObjNum,gObj[tObjNum].X,gObj[tObjNum].Y);
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillRemoveStun(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{

	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{

			tObjNum = lpObj->VpPlayer2[count].number;
			if(OBJMAX_RANGE(tObjNum))
			{
				if(lpObj->VpPlayer2[count].type == OBJ_USER)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						gObj[tObjNum].m_iSkillStunTime = 0;
						gObj[tObjNum].m_ViewSkillState &= ~4096;
						GCStateInfoSend(&gObj[tObjNum],0,4096);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_STUN,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
return true;
}




BOOL CObjUseSkill::SkillAddMana(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;
	gObjSetKillCount(aIndex,0);

	lpObj->AddMana -= lpObj->m_iSkillManaSwell;

	int iSwelledMana = short(lpObj->MaxMana + lpObj->AddMana) * 50 / 100;
	lpObj->AddMana += iSwelledMana;
	lpObj->m_iSkillManaSwellTime = 60;
	lpObj->m_iSkillManaSwell = iSwelledMana;

	GCManaSend(lpObj->m_Index,lpObj->MaxMana + lpObj->AddMana,0xFE,0,lpObj->MaxBP + lpObj->AddBP);

	if( (lpObj->MaxMana + lpObj->AddMana) < lpObj->Mana)
	{
		lpObj->Mana = lpObj->MaxMana + lpObj->AddMana;
		GCManaSend(lpObj->m_Index,lpObj->Mana,0xFF,0,lpObj->BP);
	}

	GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,lpObj->m_Index,1);

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					if(lpObj->GuildNumber > 0 && gObj[tObjNum].GuildNumber > 0)
					{
						if(lpObj->GuildNumber != gObj[tObjNum].GuildNumber)
						{
							count++;
							continue;
						}

						gObj[tObjNum].AddMana -= gObj[tObjNum].m_iSkillManaSwell;
						iSwelledMana = short(gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) * 50 / 100;
						gObj[tObjNum].AddMana += iSwelledMana;

						gObj[tObjNum].m_iSkillManaSwellTime = 60;
						gObj[tObjNum].m_iSkillManaSwell = iSwelledMana;


						GCManaSend(tObjNum,gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana,0xFE,0,gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP);

						if(gObj[tObjNum].Mana > gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana)
						{
							gObj[tObjNum].Mana = gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana;
							GCManaSend(tObjNum,gObj[tObjNum].Mana,0xFF,0,gObj[tObjNum].BP);
						}

						gObj[tObjNum].m_ViewSkillState |= 8192;
						GCStateInfoSend(&gObj[tObjNum],1,8192);
						GCMagicAttackNumberSend(lpObj,AT_SKILL_ADD_MANA,tObjNum,1);
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	if(OBJMAX_RANGE(aTargetIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	if(lpTargetObj->Type != OBJ_USER)
	{
		LogAddTD("[ANTI-HACK][Cloaking Skill] [%s][%s] Invalid Targeting  TargetType [%d] TargetClass [%d]",
			lpObj->AccountID,lpObj->Name,lpTargetObj->Type,lpTargetObj->Class);
		return false;
	}

	gObjSetKillCount(aIndex,0);

	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,lpObj->m_Index,1);
	lpTargetObj->m_iSkillInvisibleTime = 60;
	lpTargetObj->m_ViewSkillState |= 16384;

	GCStateInfoSend(lpTargetObj,1,16384);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_INVISIBLE,aTargetIndex,1);
	return true;
}


BOOL CObjUseSkill::RemoveCloakingEffect(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	gObj[aIndex].m_iSkillInvisibleTime = 0;
	gObj[aIndex].m_ViewSkillState &= ~16384;
	GCStateInfoSend(&gObj[aIndex],0,16384);
	return true;
}




BOOL CObjUseSkill::SkillRemoveCloaking(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	LPOBJ lpTargetObj = &gObj[aTargetIndex]; //loc3

	if ((lpTargetObj->Authority & 32) == 32) //Season 2.5 add-on
	{
		if (gObjSearchActiveEffect(lpTargetObj, AT_INVISIBILITY) != FALSE) //season3 add-on
		{
			return false;
		}
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					gObj[tObjNum].m_iSkillInvisibleTime = 0;
					gObj[tObjNum].m_ViewSkillState &= ~16384;
					GCStateInfoSend(&gObj[tObjNum],0,16384);
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_INVISIBLE,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}




BOOL CObjUseSkill::SkillRemoveMagic(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(OBJMAX_RANGE(aIndex) == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MapNumber != MAP_INDEX_CASTLESIEGE && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
	{
		return false;
	}

	int tObjNum;
	int count = 0;

	gObjSetKillCount(aIndex,0);
	GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,lpObj->m_Index,1);

	while ( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(OBJMAX_RANGE(tObjNum) && lpObj->VpPlayer2[count].type == OBJ_USER)
			{
				if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 5)
				{
					this->RemoveAllCharacterInvalidMagicAndSkillState(&gObj[tObjNum]);
					GCStateInfoSend(&gObj[tObjNum],0,1048576);
					GCMagicAttackNumberSend(lpObj,AT_SKILL_REMOVAL_MAGIC,tObjNum,1);
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}


int CObjUseSkill::SkillFenrirAttack(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];
	int tObjNum;
	int count = 0;
	int HitCount = 0;
	int bAttack;
	int DuelIndex = lpObj->m_iDuelUser;
	int EnableAttack;

	if(lpObj->Level < 300)
	{
		return false;
	}

	while( true )
	{
		if(lpObj->VpPlayer2[count].state != 0)
		{
			tObjNum = lpObj->VpPlayer2[count].number;

			if(tObjNum >= 0)
			{
				EnableAttack = 0;

				if(gObj[tObjNum].Class < 100 || gObj[tObjNum].Class > 110)
				{
					if(lpObj->VpPlayer2[count].type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon < 0)
					{
						EnableAttack = 1;
					}
					else if(tObjNum == aTargetIndex || DuelIndex == tObjNum)
					{
						EnableAttack = 1;
					}
					else if (lpObj->VpPlayer2[count].type != OBJ_NPC &&
							gObj[tObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
							g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
					{
						EnableAttack = 1;
					}
					else
					{
						int CallMonIndex = gObj[tObjNum].m_Index;


						if(gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0)
						{
							CallMonIndex = gObj[gObj[tObjNum].m_RecallMon].m_Index;
						}

						if(gObjTargetGuildWarCheck(lpObj,&gObj[CallMonIndex]) == 1)
						{
							EnableAttack = 1;
						}
					}
				}

				if(EnableAttack != 0)
				{
					if(gObjCalDistance(lpObj,&gObj[tObjNum]) < 6)
					{
						bAttack = 0;

						if(HitCount >= 5)
						{
							bAttack = 0;
						}
						else
						{
							bAttack = 1;
						}

						if(tObjNum == aTargetIndex)
						{
							bAttack = 1;
						}

						if(bAttack != 0)
						{
							gObjAddAttackProcMsgSendDelay(lpObj,53,tObjNum,300,lpMagic->m_Skill,0);
							HitCount++;
						}
					}
				}
			}
		}

		count++;

		if(count > MAX_VIEWPORT - 1)
		{
			break;
		}
	}
	return true;
}

BOOL CObjUseSkill::SkillInfinityArrow(int aIndex,int aTargetIndex,CMagicInf * lpMagic)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_ELF || lpObj->ChangeUP == 0)
	{
		return false;
	}

	if(lpObj->m_Index != aTargetIndex)
	{
		return false;
	}

	if(lpObj->m_iMuseElfInfinityArrowSkillTime > 0)
	{
		return false;
	}

	lpObj->m_iMuseElfInfinityArrowSkillTime = g_SkillAdditionInfo.GetInfinityArrowSkillTime();
	lpObj->m_ViewSkillState |= 0x4000000;
	GCStateInfoSend(lpObj,1,0x4000000);
	GCMagicAttackNumberSend(lpObj,0x4D,lpObj->m_Index,1);
	LogAddTD("[%s][%s] Use Infinity Arrow Skill (Time:%d)(Character Level : %d)(ChangeUp: %d)",
		lpObj->AccountID,lpObj->Name,lpObj->m_iMuseElfInfinityArrowSkillTime,lpObj->Level,lpObj->ChangeUP);
	return true;
}

BOOL CObjUseSkill::SkillFireScream(int aIndex, int aTargetIndex, CMagicInf * lpMagic)
{
	if(g_SkillAdditionInfo.GetFireScreamSkill() == false)
	{
		return false;
	}

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aTargetIndex];

	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(lpObj->Type != OBJ_USER)
	{
		return false;
	}

	if(lpObj->Class != CLASS_DARKLORD)
	{
		return false;
	}

	gObjAttack(lpObj,lpTargetObj,lpMagic,0,0,0,0);
	return true;
}



BOOL CObjUseSkill::FireScreamExplosionAttack(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage)
{

	if(gObjIsConnected(lpObj->m_Index) == false && gObjIsConnected(lpTargetObj->m_Index) == false)
	{
		return false;
	}

	if(rand()%10000 > g_SkillAdditionInfo.GetFireScreamExplosionRate())
	{
		return false;
	}

	int iExplosionDamage = iAttackDamage / 10;
	int iTarObjNum;

	if(iExplosionDamage < 1)
	{
		return true;
	}

	int iCount = 0;
	int bEnableAttack;

	while( true )
	{
		if(lpObj->VpPlayer2[iCount].state != 0)
		{
			iTarObjNum = lpObj->VpPlayer2[iCount].number;

			if(iTarObjNum >= 0)
			{
				bEnableAttack = 0;

				if(gObj[iTarObjNum].Type == OBJ_MONSTER && gObj[iTarObjNum].m_RecallMon < 0)
				{
					bEnableAttack = 1;
				}
				else if(lpTargetObj->Type == OBJ_USER && lpObj->Type == OBJ_USER && gObj[iTarObjNum].Type != OBJ_NPC)
				{
					bEnableAttack = 1;
				}
				else if(lpTargetObj->m_cChaosCastleIndex == gObj[iTarObjNum].m_cChaosCastleIndex && lpTargetObj->m_cChaosCastleIndex != -1)
				{
					bEnableAttack = 1;
				}
				else if (gObj[iTarObjNum].Type != OBJ_NPC &&
					 	 gObj[iTarObjNum].MapNumber == MAP_INDEX_CASTLESIEGE &&
						 g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE )
				{
					bEnableAttack = 1;
				}
				if(bEnableAttack != 0)
				{
					if(lpObj->m_Index != gObj[iTarObjNum].m_Index)
					{
						int iSkillDistance = gObjCalDistance(lpTargetObj,&gObj[iTarObjNum]);

						if(iSkillDistance <= g_SkillAdditionInfo.GetFireScreamExplosionAttackDistance())
						{
							gObjAddMsgSendDelay(lpObj,54,iTarObjNum,100,iExplosionDamage);
						}
					}
				}
			}
		}

		iCount++;

		if(iCount > MAX_VIEWPORT -1)
		{
			break;
		}
	}
	return true;
}




void CObjUseSkill::SpecificSkillAdditionTreat(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf * lpMagic, int iAttackDamage)
{
	BYTE bySkillNum = lpMagic->m_Skill;

	if(bySkillNum == AT_SKILL_FIRESCREAM)
	{
		gObjUseSkill.FireScreamExplosionAttack(lpObj,lpTargetObj,iAttackDamage);
	}
}







