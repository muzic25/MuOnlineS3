//----------------------------------------------------------------------------
// 서버와 클라이언트가 공유하는 헤더 정의
//----------------------------------------------------------------------------
#ifndef __PUBLIC_H__
#define __PUBLIC_H__

//----------------------------------------------------------------------------
// 캐릭터 번호
/*enum ClassNumber
{
	CLASS_WIZARD,
	CLASS_KNIGHT,
	CLASS_ELF,
	CLASS_MAGUMSA,
};

#define MAX_MAGIC					20	// 사용자당 최대 마법 개수
#define MAX_TOTALMAGIC				100	// 마법최대 개수

//----------------------------------------------------------------------------
// 저항력 번호
#define RESISTANCE_COLD				0
#define RESISTANCE_POISON			1
#define RESISTANCE_THUNDER			2
#define RESISTANCE_FIRE				3

#define MAX_RESISTANCE				4

#define MAX_SKILL					256*/

//----------------------------------------------------------------------------
// 캐릭터의 행동 번호
/*enum ActionType
{
	//마법사
	AT_SKILL_POISON		= 1,		// 이곳부터 16개는 마법책과 대응한다.(수정할수 없다)
	AT_SKILL_METEO		= 2,
	AT_SKILL_THUNDER	= 3,
	AT_SKILL_FIREBALL	= 4,
	AT_SKILL_FLAME		= 5,
	AT_SKILL_TELEPORT   = 6,
	AT_SKILL_SLOW		= 7,
	AT_SKILL_STORM		= 8,
	AT_SKILL_EVIL		= 9,
	AT_SKILL_HELL		= 10,	
	AT_SKILL_POWERWAVE  = 11,	
	AT_SKILL_FLASH      = 12,	
	AT_SKILL_ENERGYBALL = 17,	
	
	//기사
	AT_SKILL_BLOCKING   = 18,//방어
	AT_SKILL_SWORD1     = 19,//내려찍기
	AT_SKILL_SWORD2     = 20,//찌르기
	AT_SKILL_SWORD3     = 21,//올려치기
	AT_SKILL_SWORD4     = 22,//돌려치기
	AT_SKILL_SWORD5     = 23,//베기

	//요정
	AT_SKILL_CROSSBOW   = 24,//활스킬     (다발)
	AT_SKILL_BOW        = 25,//활스킬     (??)
	AT_SKILL_HEALING    = 26,//치료       (에너지/5+(아이템레벨+1)*5)                   //이곳부터는 마법구술과 대응한다.
	AT_SKILL_DEFENSE    = 27,//방어력증가 (약30초간 에너지/8+(아아템레벨+1)*2만큼 증가)
	AT_SKILL_ATTACK     = 28,//공격력증가 (약30초간 에너지/7+(아아템레벨+1)*3만큼 증가)

	AT_SKILL_CALLMON1   = 30,//소환       (아아템레벨에 따라 몹소환)
	AT_SKILL_CALLMON2   = 31,//소환       (아아템레벨에 따라 몹소환)
	AT_SKILL_CALLMON3   = 32,//소환       (아아템레벨에 따라 몹소환)
	AT_SKILL_CALLMON4   = 33,//소환       (아아템레벨에 따라 몹소환)
	AT_SKILL_CALLMON5   = 34,//소환       (아아템레벨에 따라 몹소환)
	AT_SKILL_CALLMON6   = 35,//소환       (아아템레벨에 따라 몹소환)

	AT_SKILL_WHEEL      = 41,//다중공격
	
	//몬스터
	AT_SKILL_DEVILFIRE	= 50,

	AT_IMPROVE_DAMAGE       = 60,//추가 공격력           (Level*4)
	AT_IMPROVE_MAGIC        = 61,//추가 마력             (Level*4)
	AT_IMPROVE_BLOCKING     = 62,//추가 방어율           (Level*5)
	AT_IMPROVE_DEFENSE      = 63,//추가 방어력           (Level*4)
    AT_LIFE_REGENERATION    = 65,//생명 자동 회복        (Level*1%)
	AT_LUCK                 = 64,//영혼의 보석 성공 확율 +25%

	AT_IMPROVE_LIFE           = 65,//생명력 증가
	AT_IMPROVE_MANA           = 66,//마나 증가
	AT_DECREASE_DAMAGE        = 67,//데미지 감소
	AT_REFLECTION_DAMAGE      = 68,//데미지 반사
	AT_BLOCKING_RATE          = 69,//방어성공율
	AT_IMPROVE_GAIN_GOLD      = 70,//획득 젠 증가
	AT_DECREASE_SKILL_MANA    = 71,//스킬 사용시 마나량 감소
	AT_IMPROVE_DAMAGE_LEVEL   = 72,//공격력 증가(레벨)
	AT_IMPROVE_DAMAGE_PERCENT = 73,//공격력 증가(퍼센트)
	AT_IMPROVE_MAGIC_LEVEL    = 74,//마력 증가(레벨)
	AT_IMPROVE_MAGIC_PERCENT  = 75,//마력 증가(퍼센트)
	AT_IMPROVE_ATTACK_SPEED   = 76,//공격 속도
	AT_IMPROVE_GAIN_LIFE      = 77,//획득 생명력
	AT_IMPROVE_GAIN_MANA      = 78,//획득 마나

	AT_ATTACK1          = 100,
	AT_ATTACK2,

	AT_STAND1,
	AT_STAND2,
	AT_MOVE1,
	AT_MOVE2,

	AT_DAMAGE1,
	AT_DIE1,
	AT_SIT1,
	AT_POSE1,
	AT_HEALING1,
	AT_GREETING1,
	AT_GOODBYE1,
	AT_CLAP1,
	AT_GESTURE1,
	AT_DIRECTION1,
	AT_UNKNOWN1,
	AT_CRY1,
	AT_CHEER1,
	AT_AWKWARD1,
	AT_SEE1,
	AT_WIN1,
    AT_SMILE1,
	AT_SLEEP1,
	AT_COLD1,
	AT_AGAIN1,
	AT_RESPECT1,
	AT_SALUTE1,
	AT_RUSH1,
};*/
//----------------------------------------------------------------------------


#endif
