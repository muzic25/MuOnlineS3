#include "StdAfx.h"
#include "SkillDelay.h"

CSkillDelay::CSkillDelay()
{
	this->Init();
}


CSkillDelay::~CSkillDelay()
{
	return;
}


void CSkillDelay::Init()
{
	memset(this->LastSkillUseTime, 0, sizeof(this->LastSkillUseTime) );
}

int CSkillDelay::Check(BYTE skill)
{
	int skilldelaytime;
	DWORD dwtime;
	return 1;
}