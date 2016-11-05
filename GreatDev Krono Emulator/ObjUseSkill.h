#ifndef OBJUSESKILL_H
#define OBJUSESKILL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MagicInf.h"
#include "user.h"



struct PMSG_DURATION_MAGIC_SEND {

  // static data ------------------------------------

  // non-static data --------------------------------
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PBMSG_HEAD h;
  /*<thisrel this+0x3>*/ /*|0x1|*/ unsigned char MagicNumber;
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char NumberH;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char NumberL;
  /*<thisrel this+0x6>*/ /*|0x1|*/ unsigned char X;
  /*<thisrel this+0x7>*/ /*|0x1|*/ unsigned char Y;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Dir;

  // base classes -----------------------------------

  // friends ----------------------------------------

  // static functions -------------------------------

  // non-virtual functions --------------------------

  // virtual functions ------------------------------
};
// <size 0x9>


class CObjUseSkill
{

public:

	CObjUseSkill();
	virtual ~CObjUseSkill();

	int SpeedHackCheck(int aIndex);
	int EnableSkill(BYTE Skill);
	int GetUseMana(int aIndex, CMagicInf* lpMagic);
	int GetAddUseMana(LPOBJ lpObj, CMagicInf* lpMagic);
	int GetUseBP(int aIndex, CMagicInf* lpMagic);
	void UseSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	void UseSkill(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int RunningSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL bCombo);
	void MaGumSkillDefenseDown(int aIndex, int aTargetIndex, int skill_level);
	void KnightSkillAddLife(int aIndex, int skill_level);
	void WizardMagicDefense(int aIndex, int aTargetIndex, int skill_level);
	void SkillDefense(int aIndex, int aTargetIndex, int skill_level);
	void SkillAttack(int aIndex, int aTargetIndex, int skill_level);
	int SkillChangeUse(int aIndex);
	void SkillHealing(int aIndex, int aTargetIndex, int skill_level);
	int SkillMonsterCall(int aIndex, int MonsterType, int x, int y);
	int SkillDeathPoison(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillSuddenIce(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillHellFire2Start(int aIndex, CMagicInf* lpMagic);
	int SkillHellFire2(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	void SkillBlowOfFury(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex, BOOL isCombo);
	void SkillWheel(int aIndex, CMagicInf* lpMagic, int aTargetIndex, BOOL isCombo);
	int SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BOOL isCombo);
	void SkillPowerSlash(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE Targetangle, int aTargetIndex);
	void SkillFrustrum(int aIndex, float fangle, float tx, float ty);
	int GetTargetLinePath(int sx, int sy, int tx, int ty,  int* PathX,int* PathY, int distance);
	int GetAngle(int x, int y, int tx,  int ty);
	int CalDistance(int x, int y, int x1, int y1);
	void SkillFrustrum2(int aIndex, float fangle, float tx, float ty);
	int SkillAreaCheck(int angel, int x, int y,  int tx, int ty,  int dis,  int arc);
	int SkillSpear(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillFireBurst(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillDarkHorseAttack(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int RecallPartyCheck(int aIndex, int skill_level);
	void SkillRecallParty(int aIndex, int skill_level);
	void SkillAddCriticalDamage(int aIndex, int skill_level);
	void SkillElectricSpark(int aIndex, CMagicInf* lpMagic, BYTE x, BYTE y, BYTE dir, BYTE TargetPos, int aTargetIndex);
	int SkillSummon(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillImmuneToMagic(int aIndex, CMagicInf* lpMagic);
	int SkillImmuneToHarm(int aIndex, CMagicInf* lpMagic);
	int SkillKnightRush(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillWizardJavalin(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillElfRush(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillMagumOneFlash(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillMagumDeathCannon(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillDarklordSpaceSplit(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillBrandOfSkill(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveStun(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillAddMana(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillCloaking(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveCloaking(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillRemoveMagic(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int RemoveCloakingEffect(int aIndex);
	int SkillStun(int aIndex, int aTargetIndex, CMagicInf* lpMagic, BYTE btX, BYTE btY, BYTE btDir, BYTE btTargetPos);
	int RemoveAllCharacterInvalidMagicAndSkillState(LPOBJ lpObj);
	int RemoveSpecificSkillState(LPOBJ lpObj, int iSkillNumber);
	int SkillFenrirAttack(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillInfinityArrow(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int SkillFireScream(int aIndex, int aTargetIndex, CMagicInf* lpMagic);
	int FireScreamExplosionAttack(LPOBJ lpObj, LPOBJ lpTargetObj, int iAttackDamage);
	void SpecificSkillAdditionTreat(LPOBJ lpObj, LPOBJ lpTargetObj, CMagicInf* lpMagic, int iAttackDamage);


};

int  DecPartyMemberHPandMP(LPOBJ lpObj);
extern CObjUseSkill gObjUseSkill;

#endif