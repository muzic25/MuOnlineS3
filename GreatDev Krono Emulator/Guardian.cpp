#include "StdAfx.h"
#include "Guardian.h"

CGuardian g_CsNPC_Guardian;

CGuardian::CGuardian()
{
	return;
}

CGuardian::~CGuardian()
{
	return;
}

BOOL CGuardian::CreateGuardian(int iIndex)
{	
	MsgOutput(iIndex, lMsg.Get( MSGGET(6,104) ));
	return true;
}

void CGuardian::GuardianAct(int iIndex)
{ 
	if ( !gObjIsConnected(iIndex))
		return;

	LPOBJ lpObj = &gObj[iIndex];

	if ( lpObj->VPCount < 1 ) 
		return;

	int tObjNum = -1;

	for (int i=0;i<MAX_VIEWPORT;i++)
	{
		tObjNum = lpObj->VpPlayer[i].number;

		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_USER && gObj[tObjNum].Live )
			{
				if ( gObj[tObjNum].m_btCsJoinSide == lpObj->m_btCsJoinSide )
				{
					if ( abs(lpObj->Y - gObj[tObjNum].Y) <= 3 &&
						 abs(lpObj->X - gObj[tObjNum].X) <= 3 )
					{
						gObj[tObjNum].Life += 100.0f;
						gObj[tObjNum].Mana += 100.0f;
						gObj[tObjNum].BP += 100;

						if ( gObj[tObjNum].Life > gObj[tObjNum].MaxLife )
							gObj[tObjNum].Life = gObj[tObjNum].MaxLife;

						if ( gObj[tObjNum].Mana > gObj[tObjNum].MaxMana )
							gObj[tObjNum].Mana = gObj[tObjNum].MaxMana;

						if ( gObj[tObjNum].BP > gObj[tObjNum].MaxBP )
							gObj[tObjNum].BP = gObj[tObjNum].MaxBP;

						GCReFillSend(tObjNum, gObj[tObjNum].Life, 0xFF, 1, gObj[tObjNum].iShield);
						GCManaSend(tObjNum, gObj[tObjNum].Mana, 0xFF, 0, gObj[tObjNum].BP);
					}
				}
			}
		}
	} 
	return;
}

