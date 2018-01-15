#include "StdAfx.h"
#include "CannonTower.h"

CCannonTower g_CsNPC_CannonTower;

CCannonTower::CCannonTower()
{
	return;
}

CCannonTower::~CCannonTower()
{
	return;
}


void CCannonTower::CannonTowerAct(int iIndex)
{
	if ( (rand()%2) != 0 )
		return;

	LPOBJ lpObj = &gObj[iIndex];
	int tObjNum;
	int count = 0;
	PMSG_BEATTACK_COUNT pCount;
	PMSG_BEATTACK pAttack;
	BYTE AttackSendBuff[256];
	int ASBOfs = 0;
	
	pCount.h.c = 0xC1;
	if (Configs.gLanguage == 0)
	{
		pCount.h.headcode = 0x10;
	}

	else if (Configs.gLanguage == 2)
	{
		pCount.h.headcode = 0xD7;
	}

	pCount.h.size = 0;
	pCount.MagicNumber = 0;
	pCount.Count = 0;
	pCount.X = lpObj->X;
	pCount.Y = lpObj->Y;
	
	ASBOfs = sizeof(pCount);

	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state )
		{
			if ( lpObj->VpPlayer2[count].type == OBJ_USER )
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if ( tObjNum >= 0 )
				{
					if ( gObj[tObjNum].m_btCsJoinSide != 1 )
					{
						if ( gObjCalDistance(lpObj, &gObj[tObjNum]) < 7 )
						{
							pAttack.NumberH = SET_NUMBERH(tObjNum);
							pAttack.NumberL = SET_NUMBERL(tObjNum);
							memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
							ASBOfs += sizeof(pAttack);
							pCount.Count++;
						}
					}
				}
			}
		}
		
		count++;

		if ( count > MAX_VIEWPORT-1 )
			break;
	}

	if ( pCount.Count > 0 )
	{
		pCount.h.size = ASBOfs;
		memcpy(AttackSendBuff, &pCount, sizeof(pCount));
		CGBeattackRecv(AttackSendBuff, lpObj->m_Index, 1);

		PMSG_DURATION_MAGIC_SEND pMsg;

		PHeadSetBE((LPBYTE)&pMsg, 0x1E, sizeof(pMsg));
		pMsg.MagicNumber = 50;
		pMsg.X = lpObj->X;
		pMsg.Y = lpObj->Y;
		pMsg.Dir = 0;
		pMsg.NumberH = SET_NUMBERH(iIndex);
		pMsg.NumberL = SET_NUMBERL(iIndex);

		MsgSendV2(lpObj, (LPBYTE)&pMsg, pMsg.h.size);
	}
}