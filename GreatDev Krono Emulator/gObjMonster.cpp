#include "StdAfx.h"
#include "gObjMonster.h"

CLogToFile KUNDUN_EVENT_LOG("KUNDUN_EVENT_LOG", ".\\LOG", 1);	// line : 68
CQeustNpcTeleport gQeustNpcTeleport;	// line : 91

void gObjMonsterMoveRegen(int x, int y, LPOBJ lpObj)
{
	gMSetBase.GetBoxPosition(lpObj->MapNumber, x-1, y-1, x+1, y+1, lpObj->X, lpObj->Y);

	lpObj->TX = lpObj->X;
	lpObj->TY = lpObj->Y;
	lpObj->MTX = lpObj->X;
	lpObj->MTY = lpObj->Y;
	lpObj->StartX = lpObj->X;
	lpObj->StartY = lpObj->Y;
}

BOOL gObjMonsterRegen(LPOBJ lpObj)
{
	int map[3];

	map[0] = 0;
	map[1] = 2;
	map[2] = 3;

	gObjViewportListProtocolDestroy(lpObj);
	gObjViewportClose(lpObj);

	lpObj->m_ActState.Attack = 0;
	lpObj->m_ActState.EmotionCount = 0;
	lpObj->m_ActState.Escape = 0;
	lpObj->m_ActState.Move = 0;
	lpObj->m_ActState.Rest = 0;
	lpObj->m_ActState.Emotion = 0;
	lpObj->TargetNumber = -1;
	lpObj->NextActionTime = 5000;

	if ( lpObj->Class == 43 )
	{
		lpObj->MapNumber = map[ rand() % 3 ];

		if ( gMSetBase.GetBoxPosition(lpObj->MapNumber, 10, 10, 240, 240, lpObj->X, lpObj->Y)== FALSE )
		{
			lpObj->Live = FALSE;
			lpObj->m_State = 4;
			lpObj->RegenTime = GetTickCount();
			lpObj->DieRegen = TRUE;
			return FALSE;
		}

		lpObj->TX = lpObj->X;
		lpObj->TY = lpObj->Y;
		lpObj->MTX = lpObj->X;
		lpObj->MTY = lpObj->Y;
		lpObj->StartX = lpObj->X;
		lpObj->StartY = lpObj->Y;
	}
	else if ( lpObj->Class == 44 )
	{

	}
	else if ( lpObj->Class == 53 || lpObj->Class == 54 || lpObj->Class == 55 || lpObj->Class == 56 )
	{
		return FALSE;
	}
	else if ( lpObj->Class >= 78 && lpObj->Class <= 83 )
	{
		return FALSE;
	}
	else if ( (lpObj->m_Attribute < 51) ? FALSE : (lpObj->m_Attribute > 58)? FALSE : TRUE )
	{
		lpObj->Live = TRUE;
		lpObj->DieRegen = FALSE;
		CreateFrustrum(lpObj->X, lpObj->Y, lpObj->m_Index);
		gObjClearViewport(lpObj);
		gObjViewportListCreate(lpObj->m_Index);
		gObjViewportListProtocolCreate(lpObj);
		return FALSE;
	}
	else if ( gMSetBase.GetPosition(lpObj->m_PosNum, lpObj->MapNumber, lpObj->X, lpObj->Y) == FALSE )
	{
		if(lpObj->m_Attribute == 62)
		{
			BYTE btX = lpObj->X,btY = lpObj->Y;
			if(gObjGetRandomFreeLocation(lpObj->MapNumber,(BYTE &)btX,(BYTE &)btY,5,5,30) == FALSE)
			{
				return FALSE;
			}

			lpObj->X = btX;
			lpObj->Y = btY;
			__asm Jmp EndLabel;
		}

		lpObj->Live = FALSE;
		lpObj->m_State = 4;
		lpObj->RegenTime = GetTickCount();
		lpObj->DieRegen = TRUE;
		return FALSE;


	}
	else
	{
EndLabel:
		lpObj->MTX = lpObj->X;
		lpObj->MTY = lpObj->Y;
		lpObj->TX = lpObj->X;
		lpObj->TY = lpObj->Y;
		lpObj->StartX = lpObj->X;
		lpObj->StartY = lpObj->Y;
	}


	gObjMonsterHitDamageInit(lpObj);

	if ( lpObj->MapNumber == MAP_INDEX_CRYWOLF_FIRSTZONE && g_CrywolfSync.GetCrywolfState() >= 2 && g_CrywolfSync.GetCrywolfState() <= 5  ) // Crywolf
	{
	
	}
	else if ( g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit != 0 )
	{
		lpObj->Life = ( lpObj->m_iScriptMaxLife * g_CrywolfSync.GetMonHPBenefitRate()  ) / 100;
		lpObj->MaxLife = (lpObj->m_iScriptMaxLife * g_CrywolfSync.GetMonHPBenefitRate() ) / 100;
	}
	return TRUE;
}










int gObjMonsterViewportIsCharacter(LPOBJ lpObj)
{
	int tObjNum;

	for ( int n = 0; n<MAX_VIEWPORT_MONSTER ; n++ )
	{
		if ( lpObj->VpPlayer2[n].state  != 0 )
		{
			tObjNum = lpObj->VpPlayer2[n].number;

			if ( tObjNum == lpObj->TargetNumber ) 
			{
				return n;
			}
		}
	}

	return -1;
}









void gObjMonsterHitDamageInit(LPOBJ lpObj)
{
	for ( int i = 0; i< MAX_ST_HIT_DAMAGE ; i++ )
	{
		lpObj->sHD[i].number  = -1;
	}

	lpObj->sHDCount = 0;
}









int gObjMonsterHitDamageUserDel(LPOBJ lpObj)
{
	int delok = 0;
	int delindex = -1;

	for ( int n = 0;n<MAX_ST_HIT_DAMAGE ; n++ )
	{
		if ( lpObj->sHD[n].number >= 0 )
		{
			delok = FALSE;

			if ( gObjIsConnected(lpObj->sHD[n].number ) == TRUE )
			{
				if ( (GetTickCount()- lpObj->sHD[n].LastHitTime) > 20000 )
				{
					delok = TRUE;
				}

				if ( gObj[lpObj->sHD[n].number].MapNumber != lpObj->MapNumber)
				{
					delok = TRUE;
				}
				else if ( gObjCheckTileArea(lpObj->m_Index, gObj[lpObj->sHD[n].number].X , gObj[lpObj->sHD[n].number].Y , 20) == FALSE )
				{
					delok = TRUE;
				}
			}
			else
			{
				delok = TRUE;
			}


			if ( delok == TRUE )
			{
				lpObj->sHD[n].number = -1;
				delindex = n;
				lpObj->sHDCount--;
			}


		}
	}

	return delindex;
}








void gObjMonsterSetHitDamage(LPOBJ lpObj, int hit_player, int hit_damage)
{
	int blank = -1;

	for (int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpObj->sHD[n].number >= 0 )
		{
			if ( lpObj->sHD[n].number == hit_player )
			{
				lpObj->sHD[n].HitDamage += hit_damage;
				lpObj->sHD[n].LastHitTime = GetTickCount();

				if ( lpObj->sHD[n].HitDamage > lpObj->MaxLife )
				{
					lpObj->sHD[n].HitDamage = lpObj->MaxLife;
				}

				return;
			}
		}
		else if ( blank < 0 )
		{
			blank = n;
		}
	}

	if ( blank < 0 )
	{
		blank = gObjMonsterHitDamageUserDel(lpObj);
	}

	if ( blank >= 0 )
	{
		lpObj->sHD[blank].number = hit_player;
		lpObj->sHD[blank].HitDamage = hit_damage;

		if ( lpObj->sHD[blank].HitDamage > lpObj->MaxLife )
		{
			lpObj->sHD[blank].HitDamage = lpObj->MaxLife;
		}
	
		lpObj->sHD[blank].LastHitTime = GetTickCount();
		lpObj->sHDCount++;
	}
	else
	{
		LogAdd("error-L2 : Hit Damage Set error");
	}
}









int gObjMonsterTopHitDamageUser(LPOBJ lpMonObj)
{
	int MaxHitDamage = 0;
	int MaxHitDamageUser = -1;

	for ( int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpMonObj->sHD[n].number >= 0 )
		{
			if ( lpMonObj->sHD[n].HitDamage > MaxHitDamage )
			{
				MaxHitDamage = lpMonObj->sHD[n].HitDamage;
				MaxHitDamageUser = lpMonObj->sHD[n].number;
			}
		}
	}

	return MaxHitDamageUser;
}










int	 gObjMonsterLastHitDamageUser(LPOBJ lpMonObj, int & hitindex)
{
	int LastHitTime = 0;
	int LastHitUser = -1;

	for ( int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpMonObj->sHD[n].number >= 0 )
		{
			if ( lpMonObj->sHD[n].LastHitTime > LastHitTime )
			{
				LastHitTime = lpMonObj->sHD[n].LastHitTime;
				LastHitUser = lpMonObj->sHD[n].number;
				hitindex = n;
			}
		}
	}

	return LastHitUser;
}










BOOL gObjMonsterMoveCheck(LPOBJ lpObj, int tx, int ty)
{
	if ( lpObj->m_ActState.Emotion  == 1 )
	{
		return TRUE;
	}

	if ( lpObj->MapNumber == MAP_INDEX_KANTURU_BOSS && lpObj->m_PosNum < 0)
	{
		tx -= lpObj->StartX;
		ty -= lpObj->StartY;
		int dis = sqrt((double)tx*tx + ty*ty);

		if ( dis > 30 )
		{
			LogAddTD("[ KANTURU ][ Debug - m_PosNum ] Fail %s(Index:%d) X%d-Y%d -> X%d-Y%d(%d)",
				lpObj->Name, lpObj->Class, lpObj->StartX, lpObj->StartY, tx, ty, dis);
			return FALSE;
		}
	}
	else
	{
		LPMONSTER_POSITION lpPos = &gMSetBase.m_Mp[lpObj->m_PosNum];

		if ( lpPos->m_Dis < 1 )
		{
			return FALSE;
		}

		tx -= lpObj->StartX;
		ty -= lpObj->StartY;

		int dis = sqrt((double)tx * tx + ty * ty);

		if ( dis > lpPos->m_Dis)
		{
			return FALSE;
		}	
	}

	return TRUE;
}









BOOL gObjMonsterGetTargetPos(LPOBJ lpObj)
{
	int tpx;	// Target Player X
	int tpy;
	int mtx;	// Monster Target X
	int mty;
	int searchp = 0;
	int sn = 0;
	int searchcount = MAX_ROAD_PATH_TABLE/2-1;
	BYTE attr;
	BOOL result;
	LPOBJ lpTargetObj;

	if ( lpObj->m_MoveRange == 0 && lpObj->m_SkillHarden != 0 && lpObj->m_iSkillStunTime > 0 )
	{
		return FALSE;
	}

	if ( OBJMAX_RANGE(lpObj->TargetNumber) == FALSE )
	{
		return FALSE;
	}

	lpTargetObj = &gObj[lpObj->TargetNumber];

	if ( lpTargetObj->Teleport != 0 )
	{
		return FALSE;
	}

	int vpn = gObjMonsterViewportIsCharacter(lpObj);

	if ( vpn < 0 )
	{
		return FALSE;
	}
	
	tpx = lpTargetObj->X;
	mtx = tpx;
	tpy = lpTargetObj->Y;
	mty = tpy;
	int dis;

	if ( lpObj->m_AttackType >= 100 )
	{
		dis = lpObj->m_AttackRange + 2;
	}
	else
	{
		dis = lpObj->m_AttackRange;
	}

	if ( lpObj->X < mtx )
	{
		tpx -= dis;
	}

	if ( lpObj->X > mtx )
	{
		tpx += dis;
	}

	if ( lpObj->Y < mty )
	{
		tpy -= dis;
	}

	if ( lpObj->Y > mty )
	{
		tpy += dis;
	}

	searchp = GetPathPacketDirPos( (lpTargetObj->X - tpx), (lpTargetObj->Y - tpy) ) * 2;

	if ( MapC[lpObj->MapNumber].GetStandAttr(tpx, tpy) == 0 )
	{
		while ( searchcount-- )
		{
			mtx = lpTargetObj->X + RoadPathTable[searchp];
			mty = lpTargetObj->Y + RoadPathTable[1+searchp];
			attr = MapC[lpObj->MapNumber].GetAttr(mtx, mty);
			result = gObjMonsterMoveCheck(lpObj, mtx, mty);

			if ( lpObj->Class == 249 )
			{
				if ( (attr&2)!=2 && result == TRUE )
				{
					lpObj->MTX = mtx;
					lpObj->MTY = mty;
					return TRUE;
				}
			}
			else if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 && result == TRUE )
			{
				lpObj->MTX = mtx;
				lpObj->MTY = mty;
				return TRUE;
			}

			searchp += 2;

			if ( searchp > MAX_ROAD_PATH_TABLE-1 )
			{
				searchp = 0;
			}
		}

		return FALSE;
	}

	attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);
	result = gObjMonsterMoveCheck(lpObj, mtx, mty);

	if ( lpObj->Class == 249 )
	{
		if ( (attr&2)!=2 && result == TRUE )
		{
			lpObj->MTX = tpx;
			lpObj->MTY = tpy;
			return TRUE;
		}
	}
	else if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 && result == TRUE )
	{
		lpObj->MTX = tpx;
		lpObj->MTY = tpy;
		return TRUE;
	}

	return FALSE;
}















BOOL gObjGetTargetPos(LPOBJ lpObj, int sx, int sy, int & tx , int & ty)
{
	int tpx;	// Target Player X
	int tpy;
	int mtx;	// Monster Target X
	int mty;
	int searchp = 0;
	int sn = 0;
	int searchcount = MAX_ROAD_PATH_TABLE/2-1;
	BYTE attr;
	int dis;

	tpx = sx;
	mtx = tpx;
	tpy = sy;
	mty = tpy;

	if ( lpObj->m_AttackType >= 100 )
	{
		dis = lpObj->m_AttackRange + 2;
	}
	else
	{
		dis = lpObj->m_AttackRange;
	}

	if ( lpObj->X < mtx )
	{
		tpx -= dis;
	}

	if ( lpObj->X > mtx )
	{
		tpx += dis;
	}

	if ( lpObj->Y < mty )
	{
		tpy -= dis;
	}

	if ( lpObj->Y > mty )
	{
		tpy += dis;
	}

	searchp = GetPathPacketDirPos( sx - tpx, sy - tpy ) * 2;

	if ( MapC[lpObj->MapNumber].GetStandAttr(tpx, tpy) == 0 )
	{
		while ( searchcount-- )
		{
			mtx = sx + RoadPathTable[searchp];
			mty = sy + RoadPathTable[1+searchp];
			attr = MapC[lpObj->MapNumber].GetAttr(mtx, mty);
			
			if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
			{
				tx = mtx;
				ty = mty;
				return TRUE;
			}

			searchp += 2;

			if ( searchp > MAX_ROAD_PATH_TABLE-1 )
			{
				searchp = 0;
			}
		}

		return FALSE;
	}

	attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);

	if ( lpObj->m_Attribute >= 100 )
	{
		if (  (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
		{
			tx = tpx;
			ty = tpy;
			return TRUE;
		}
	}
	else if  ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
	{
		tx = tpx;
		ty = tpy;
		return TRUE;
	}

	return FALSE;
}
















int gObjCallMonsterSetEnemy(LPOBJ lpObj, int Target)
{
	if ( lpObj->Type != OBJ_USER )
	{
		return -1;
	}

	LPOBJ lpCallObj = &gObj[lpObj->m_RecallMon];

	if ( lpCallObj->TargetNumber >= 0 )
	{
		return -1;
	}

	if ( lpCallObj->TargetNumber != Target )
	{
		lpCallObj->TargetNumber = Target;
		lpCallObj->m_ActState.EmotionCount = 30;
		lpCallObj->m_ActState.Emotion = 1;
	}

	return -1;
}













int gObjMonsterSearchEnemy(LPOBJ lpObj, BYTE objtype)
{
	int n;
	int tx;
	int ty;
	int dis;
	int mindis = lpObj->m_ViewRange;
	int searchtarget = -1;
	int tObjNum;
	int count = 3;
	int t1 = objtype;
	int t2 = objtype;

	for (n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if ( tObjNum >= 0 )
		{
			if ( (gObj[tObjNum].Type == t1 || gObj[tObjNum].Type == t2) && (gObj[tObjNum].Live != FALSE) )
			{
				if ( (gObj[tObjNum].Class >= 100 && gObj[tObjNum].Class < 110 ) || (gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0) )
				{

				}
				else if ( (gObj[tObjNum].Authority &2) != 2 && gObj[tObjNum].Teleport == 0 ) // Check if this is teleport #error
				{
					tx = lpObj->X - gObj[tObjNum].X;
					ty = lpObj->Y - gObj[tObjNum].Y;
					dis = sqrt((double)tx * tx + ty * ty);
					lpObj->VpPlayer2[n].dis = dis;

					if ( dis < mindis )
					{
						searchtarget = tObjNum;
						mindis = dis;
					}
				}
			}
		}
	}

	return searchtarget;
}









int gObjGuardSearchEnemy(LPOBJ lpObj)
{
	int n;
	int tx;
	int ty;
	int dis;
	int mindis = lpObj->m_ViewRange;
	int searchtarget = -1;
	int tObjNum;
	BYTE attr;

	for (n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_USER && gObj[tObjNum].m_PK_Level > 4 )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);

				if ( (attr&1) != 1 )
				{
					tx = lpObj->X - gObj[tObjNum].X;
					ty = lpObj->Y - gObj[tObjNum].Y;
					dis = sqrt((double)tx * tx + ty * ty);
					lpObj->VpPlayer2[n].dis = dis;

					if ( dis < mindis )
					{
						searchtarget = tObjNum;
						mindis = dis;
					}
				}
			}
		}
	}

	return searchtarget;
}
	






void gObjMonsterStateProc(LPOBJ lpObj, int aMsgCode, int aIndex, int aMsgSubCode)
{
	if ( lpObj->m_iMonsterBattleDelay > 0 )
	{
		return;
	}

	switch ( aMsgCode )
	{
		case 0:

			if ( lpObj->m_Attribute == 0 )
			{
				return;
			}
			
			if ( gObj[aIndex].Live == FALSE || gObj[aIndex].m_State != 2)
			{
				return;
			}

			if ( lpObj->m_ActState.Emotion == 0 )
			{
				lpObj->m_ActState.Emotion = 1;
				lpObj->m_ActState.EmotionCount = 10;
			}
			else if ( lpObj->m_ActState.Emotion == 1 )
			{
				lpObj->m_ActState.EmotionCount = 10;
			}

			if ( lpObj->m_ActState.Attack == 0 && lpObj->PathStartEnd == 0)
			{
				if ( OBJMAX_RANGE(aIndex) )
				{
					int map = gObj[aIndex].MapNumber;
					BYTE attr;
					int dis = gObjCalDistance(lpObj, &gObj[aIndex]);
					int range;

					if ( lpObj->m_AttackType >= 100 )
					{
						range = lpObj->m_AttackRange +2;
					}
					else
					{
						range = lpObj->m_AttackRange;
					}

					if ( dis <= range )
					{
						if ( gObj[aIndex].m_RecallMon >= 0 )
						{
							if ( lpObj->m_RecallMon >= 0 )
							{
								if ( gObj[aIndex].Type == OBJ_MONSTER )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
							else
							{
								lpObj->TargetNumber = aIndex;
							}
						}
						else if ( (rand()%100) < 90 )
						{
							if ( lpObj->m_RecallMon >= 0 )
							{
								if ( gObj[aIndex].Type == OBJ_MONSTER )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
							else
							{
								lpObj->TargetNumber = aIndex;
							}
						}
					}
					else
					{
						BYTE wall = 0;

						wall = MapC[map].CheckWall2(lpObj->X, lpObj->Y, gObj[aIndex].X, gObj[aIndex].Y);

						if ( wall == 1 )
						{
							attr = MapC[map].GetAttr(gObj[aIndex].X, gObj[aIndex].Y);

							if ( (attr&1) != 1 )
							{
								if ( lpObj->TargetNumber < 0 )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
						}
					}


					if ( lpObj->m_bIsInMonsterHerd != false && lpObj->TargetNumber == aIndex )
					{
						if ( lpObj->m_lpMonsterHerd )
						{
							lpObj->m_lpMonsterHerd->BeenAttacked (lpObj, &gObj[aIndex]);
						}
					}
				}
			}
			else
			{
				if ( (rand() % 2 )== 1 && lpObj->PathStartEnd == 0)
				{
					int IndexEnemy = lpObj->TargetNumber;
					int EnemyMap = gObj[IndexEnemy].MapNumber;

					int enemydis = gObjCalDistance(lpObj, &gObj[aIndex]);
					int range;

					if ( lpObj->m_AttackType >= 100 )
					{
						range = lpObj->m_AttackRange + 2;
					}
					else
					{
						range = lpObj->m_AttackRange;
					}

					if ( enemydis <= range )
					{
						lpObj->m_ActState.Attack = 1;
						lpObj->TargetNumber = aIndex;
					}
					else
					{
						if ( MapC[EnemyMap].CheckWall2(lpObj->X, lpObj->Y, gObj[IndexEnemy].X, gObj[IndexEnemy].Y) == 1 )
						{
							lpObj->m_ActState.Attack = 1;
							lpObj->TargetNumber = aIndex;
						}
					}
				}
				else
				{
					int MaxLife = lpObj->MaxLife;
					MaxLife >>= 1;

					if ( MaxLife > lpObj->Life )
					{
						if ( lpObj->m_Attribute != 2 )
						{
							lpObj->m_ActState.Emotion = 2;
							lpObj->m_ActState.EmotionCount = 2;
						}
					}
				}
			}
			break;
		case 1:
			if ( lpObj->m_btCsNpcType )
			{
				switch ( lpObj->m_btCsNpcType )
				{
					case 1:	g_CastleSiege.DelNPC(lpObj->m_Index, lpObj->Class, lpObj->m_iCsNpcExistVal, TRUE);	break;
					case 2:	g_CastleSiege.DelNPC(lpObj->m_Index, lpObj->Class, lpObj->m_iCsNpcExistVal, FALSE);break;
					case 3:	g_CastleSiege.DelNPC(lpObj->m_Index, lpObj->Class, lpObj->m_iCsNpcExistVal, FALSE);	break;
				}

				if ( lpObj->Class == 287 || lpObj->Class == 286 )
					g_CsNPC_Mercenary.DeleteMercenary(lpObj->m_Index);

				if ( lpObj->Class == 278 )
					g_CsNPC_LifeStone.DeleteLifeStone(lpObj->m_Index);

				gObjDel(lpObj->m_Index);
			}
			if ( KALIMA_MAP_RANGE(lpObj->MapNumber)  )
			{
				if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 || lpObj->Class == 197 || lpObj->Class == 267 )
				{
					g_KalimaGate.CreateKalimaGate2(aIndex, lpObj->MapNumber, lpObj->X, lpObj->Y);
				}
			}

			if ( lpObj->Class == 409 || lpObj->Class == 410 || lpObj->Class == 411 || lpObj->Class == 412 )//Season 2.5 Addon
			{
				g_QuestInfo.MonsterPlusKillCountParty(lpObj, &gObj[aIndex]);
			}


			gObjMonsterDieGiveItem(lpObj, &gObj[aIndex] );
			lpObj->NextActionTime = 500;

			if ( lpObj->m_RecallMon >= 0 )
			{
				gObjMonsterCallKill(lpObj->m_RecallMon);
			}

			if (  BC_MAP_RANGE(lpObj->MapNumber) != FALSE && lpObj->Type >= OBJ_MONSTER)
			{
				if ( lpObj->Class == 89 || lpObj->Class == 95 || lpObj->Class == 112 || lpObj->Class == 118 || lpObj->Class == 124 || lpObj->Class == 130 || lpObj->Class == 143)
				{
					g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_KILL_COUNT++;
				}
				else
				{
					g_BloodCastle.m_BridgeData[lpObj->MapNumber - MAP_INDEX_BLOODCASTLE1].m_iBC_MONSTER_KILL_COUNT++;
				}

				if ( g_BloodCastle.CheckMonsterKillCount(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1) != false )
				{
					if (g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_bBC_MONSTER_KILL_COMPLETE == false )
					{
						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_bBC_MONSTER_KILL_COMPLETE = true;
						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_MONSTER_MAX_COUNT = -1;

						PMSG_STATEBLOODCASTLE pMsg;

						PHeadSetB((LPBYTE)&pMsg, 0x9B, sizeof(PMSG_STATEBLOODCASTLE));

						pMsg.btPlayState = BC_STATE_PLAYEND;
						pMsg.wRemainSec = 0;
						pMsg.wMaxKillMonster = 0;
						pMsg.wCurKillMonster = 0;
						pMsg.wUserHaveWeapon = 0;
						pMsg.btWeaponNum = -1;

						g_BloodCastle.SendBridgeAnyMsg( (UCHAR *)&pMsg, pMsg.h.size, lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1);
						g_BloodCastle.ReleaseCastleBridge(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1);
						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_dwBC_TICK_DOOR_OPEN = GetTickCount() + 3000;

						LogAddTD("[Blood Castle] (%d) All of the Monster Terminated -> %d", lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1+1,
							g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_MONSTER_KILL_COUNT);

						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_MAX_COUNT = g_BloodCastle.GetCurrentLiveUserCount(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1)*2;
						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_KILL_COUNT = 0;

						if ( g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_MAX_COUNT > 10) 
						{
							g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_MAX_COUNT = 10;
						}
					}

					if (g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_MONSTER_SUCCESS_MSG_COUNT < 1 )
					{
						g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_MONSTER_SUCCESS_MSG_COUNT++;
						g_BloodCastle.SendNoticeMessage(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1, lMsg.Get(MSGGET(4, 144))); 
					}
					
				}

				if ( g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_bBC_MONSTER_KILL_COMPLETE != false )
				{
					if ( g_BloodCastle.CheckBossKillCount(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1) != false )
					{
						if ( g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_bBC_BOSS_MONSTER_KILL_COMPLETE == false )
						{
							g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_bBC_BOSS_MONSTER_KILL_COMPLETE = true;
							g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_MAX_COUNT = -1;

							g_BloodCastle.SetSaintStatue(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1);

							LogAddTD("[Blood Castle] (%d) All of the Boss Monster Terminated -> %d",
								lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1+1, g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_KILL_COUNT);
						}

						if ( g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_SUCCESS_MSG_COUNT < 1 )
						{
							g_BloodCastle.m_BridgeData[lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1].m_iBC_BOSS_MONSTER_SUCCESS_MSG_COUNT++;
							g_BloodCastle.SendNoticeMessage(lpObj->MapNumber-MAP_INDEX_BLOODCASTLE1, lMsg.Get(MSGGET(4, 156)));
						}
					}
				}
			}
			
			break;


		case 2:
			if ( gObj[aIndex].Live != FALSE )
			{
				if ( BC_MAP_RANGE(gObj[aIndex].MapNumber) == FALSE )
				{
					if ( gObj[aIndex].Class != 131 || ((  (lpObj->Class-132)<0)?FALSE:((lpObj->Class-132)>2)?FALSE:TRUE)==FALSE )
					{
						gObjBackSpring(lpObj, &gObj[aIndex]);
					}
				}
			}

			break;

		case 3:
			lpObj->TargetNumber = -1;
			lpObj->LastAttackerID = -1;
			lpObj->m_ActState.Emotion = 0;
			lpObj->m_ActState.Attack = 0;
			lpObj->m_ActState.Move = 0;
			lpObj->NextActionTime = 1000;
			break;

		case 4:
			lpObj->m_ActState.Emotion = 3;
			lpObj->m_ActState.EmotionCount = 1;
			break;

		case 5:
			gObjMemFree(lpObj->m_Index);
			break;

		case 6:
			if ( gObj[aIndex].Live != FALSE )
			{
				gObjBackSpring2(lpObj, &gObj[aIndex], 2);
			}

			break;

		case 7:
			if ( gObj[aIndex].Live != FALSE )
			{
				gObjBackSpring2(lpObj, &gObj[aIndex], 3);
			}
			break;

		case 55:
			gObjAttack(lpObj, &gObj[aIndex], NULL, FALSE, 0, 0, FALSE);
			break;

		case 56:
			{
				LPOBJ lpTargetObj = &gObj[aIndex];

				if ( lpTargetObj->m_PoisonType == 0 )
				{
					if ( retResistance(lpTargetObj, 1) == 0 )
					{
						lpTargetObj->m_PoisonType = 1;
						lpTargetObj->m_PoisonBeattackCount = aMsgSubCode;
						lpTargetObj->lpAttackObj = lpObj;
						lpTargetObj->m_ViewSkillState |= 1;
						GCStateInfoSend(lpTargetObj, 1, lpTargetObj->m_ViewSkillState);
					}
				}
			}
			break;

		case 57:
			{
				LPOBJ lpTargetObj = &gObj[aIndex];
				gObjBackSpring2(lpTargetObj, lpObj, aMsgSubCode);
			}
			break;
	}
}






void gObjMonsterProcess(LPOBJ lpObj)
{
	gObjMsgProc(lpObj);

	if ( lpObj->Live == FALSE )
	{
		return;
	}

	if ( lpObj->m_iMonsterBattleDelay > 0 )
	{
		lpObj->m_iMonsterBattleDelay--;
	}

	if ( (GetTickCount() - lpObj->CurActionTime ) < (lpObj->NextActionTime + lpObj->DelayActionTime) )
	{
		return;
	}

	lpObj->CurActionTime = GetTickCount();

	if ( BC_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		if ( lpObj->Class == 131|| ((lpObj->Class-132<0)?FALSE:(lpObj->Class-132>2)?FALSE:TRUE) != FALSE )
		{
			return;
		}
	}

	if ( ((lpObj->m_Attribute < 51)?FALSE:(lpObj->m_Attribute > 58)?FALSE:TRUE) != FALSE )
	{
		if ( lpObj->m_Attribute == 58 )
		{
			g_KalimaGate.KalimaGateAct2(lpObj->m_Index);
			return;
		}

		g_KalimaGate.KalimaGateAct(lpObj->m_Index);
		return;
	}

	if ( lpObj->Class == 283 )	return;
	if ( lpObj->Class == 288 )	return;
	if ( lpObj->Class == 278 )	return;

	if ( lpObj->Class >= 100 && lpObj->Class <= 110 )
	{
		gObjMonsterTrapAct(lpObj);
		
	}
	else if ( lpObj->Class == 200 )
	{
		int ground;
		int team = gCheckGoal(lpObj->X, lpObj->Y, ground);

		if ( team >= 0 )
		{
			gObjMonsterRegen(lpObj);
			gBattleSoccerScoreUpdate(ground, team);
			return;
		}
	}
	else 
	{
		if ( lpObj->Class == 287 || lpObj->Class == 286 )
		{
			g_CsNPC_Mercenary.MercenaryAct(lpObj->m_Index);
		}
		else if ( lpObj->m_bIsInMonsterHerd != false )
		{
			if ( lpObj->m_lpMonsterHerd != NULL )
			{
				lpObj->m_lpMonsterHerd->MonsterBaseAct(lpObj);
			}
		}
		else
		{
			gObjMonsterBaseAct(lpObj);
		}
	}

	if ( lpObj->m_Attribute == 100 )
	{
		if ( lpObj->m_RecallMon >= 0 && lpObj->m_RecallMon < OBJMAX )
		{
			LPOBJ lpCallMonObj;
			BOOL Success = FALSE;

			lpCallMonObj = &gObj[lpObj->m_RecallMon];


			if ( lpObj->MapNumber != lpCallMonObj->MapNumber )
			{
				Success = TRUE;
			}
	
			if ( gObjCalDistance(lpCallMonObj, lpObj)> 14 )
			{
				Success = TRUE;
			}

			if ( Success == TRUE )
			{
				gObjTeleportMagicUse(lpObj->m_Index, (BYTE)lpCallMonObj->X+1, lpCallMonObj->Y);
				lpObj->MapNumber = lpCallMonObj->MapNumber;

				return;
			}
		}
	}

	if ( lpObj->m_ActState.Move != 0 )
	{
		if ( PathFindMoveMsgSend(lpObj ) == TRUE )
		{
			lpObj->m_ActState.Move  = (DWORD)0;
		}

		lpObj->m_ActState.Move = (DWORD)0;

		return;
	}

	if ( lpObj->m_ActState.Attack == 1 )
	{
		if ( TMonsterSkillManager::CheckMonsterSkill(lpObj->Class) )
		{
			BOOL bEnableAttack = TRUE;

			if ( lpObj->TargetNumber < 0 )
				bEnableAttack = FALSE;

			if ( gObj[lpObj->TargetNumber].Live == FALSE || gObj[lpObj->TargetNumber].Teleport != 0)
				bEnableAttack = FALSE;

			if ( gObj[lpObj->TargetNumber].Connected <= PLAYER_LOGGED || gObj[lpObj->TargetNumber].CloseCount != -1 )
				bEnableAttack = FALSE;

			if ( bEnableAttack == FALSE )
			{
				lpObj->TargetNumber = -1;
				lpObj->m_ActState.Emotion = 0;
				lpObj->m_ActState.Attack = 0;
				lpObj->m_ActState.Move = 0;
				lpObj->NextActionTime = 1000;
				return;
			}
			
			if ( rand()%4 == 0 )
			{
				PMSG_ATTACK pAttackMsg;

				pAttackMsg.AttackAction = 120;
				pAttackMsg.DirDis = lpObj->Dir;
				pAttackMsg.NumberH = (BYTE)((DWORD)lpObj->TargetNumber>>(DWORD)8);
				pAttackMsg.NumberL = lpObj->TargetNumber&0xFF;

				GCActionSend(lpObj, 120, lpObj->m_Index, lpObj->TargetNumber);
				gObjAttack(lpObj, &gObj[lpObj->TargetNumber], NULL, FALSE, 0, 0, FALSE);
			}
			else
			{
				TMonsterSkillManager::UseMonsterSkill(lpObj->m_Index, lpObj->TargetNumber, 0);
			}

			lpObj->m_ActState.Attack = 0;
		}
		else
		{
			int AttackType = lpObj->m_AttackType;
			int lc6 = 0;

			if ( AttackType >= 100 )
			{
				if ( (rand()%5) == 0 )
				{
					AttackType -= 100;
					lc6 = TRUE;
				}
				else
				{
					AttackType = 0;
				}
			}

			if ( lc6 != FALSE || lpObj->m_AttackType == 50)
			{
				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Connected > PLAYER_LOGGED && gObj[lpObj->TargetNumber].CloseCount == -1 )
					{
						if ( gObj[lpObj->TargetNumber].Live == FALSE )
						{
							lpObj->TargetNumber = -1;
							lpObj->m_ActState.Emotion = 0;
							lpObj->m_ActState.Attack = 0;
							lpObj->m_ActState.Move = 0;
							lpObj->NextActionTime = 1000;
						}
						else if ( gObj[lpObj->TargetNumber].Teleport == 0 ) // if is not dead
						{
							gObjMonsterMagicAttack(lpObj, -1);

							if ( lpObj->Type == OBJ_MONSTER )
							{
								if ( lpObj->m_bIsInMonsterHerd != false )
								{
									if (lpObj->m_lpMonsterHerd != NULL )
									{
										lpObj->m_lpMonsterHerd->MonsterAttackAction(lpObj, &gObj[lpObj->TargetNumber]);
									}
								}
							}
						}
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.Emotion = 0;
						lpObj->m_ActState.Attack = 0;
						lpObj->m_ActState.Move = 0;
						lpObj->NextActionTime = 1000;
					}
				}
			}
			else
			{
				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Connected > PLAYER_LOGGED &&  gObj[lpObj->TargetNumber].CloseCount == -1 )
					{
						if ( gObj[lpObj->TargetNumber].Live == FALSE )
						{
							lpObj->TargetNumber = -1;
							lpObj->m_ActState.Emotion = 0;
							lpObj->m_ActState.Attack = 0;
							lpObj->m_ActState.Move = 0;
							lpObj->NextActionTime = 1000;
						}
						else if ( gObj[lpObj->TargetNumber].Teleport == 0 )
						{
							gObjMonsterAttack(lpObj, &gObj[lpObj->TargetNumber]);

							if ( lpObj->Type == OBJ_MONSTER )
							{
								if ( lpObj->m_bIsInMonsterHerd != false )
								{
									if (lpObj->m_lpMonsterHerd != NULL )
									{
										lpObj->m_lpMonsterHerd->MonsterAttackAction(lpObj, &gObj[lpObj->TargetNumber]);
									}
								}
							}
						}
						
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.Emotion = 0;
						lpObj->m_ActState.Attack = 0;
						lpObj->m_ActState.Move = 0;
						lpObj->NextActionTime = 1000;
					}
				}
			}

			lpObj->m_ActState.Attack = 0;
		}
	}
}






void gObjMonsterMagicAttack(LPOBJ lpObj, int iMonsterClass)
{
	int tObjNum;
	int count = 0;
	PMSG_BEATTACK_COUNT pCount;
	PMSG_BEATTACK pAttack;
	BYTE AttackSendBuff[256];
	int ASBOfs = 0;
	PMSG_DURATION_MAGIC_RECV pDuration;

	pDuration.MagicNumber = 0;
	pDuration.Dir = 0;
	pDuration.X = lpObj->X;
	pDuration.Y = lpObj->Y;

	CGDurationMagicRecv(&pDuration, lpObj->m_Index);

	pCount.h.c = 0xC1;
	pCount.h.headcode = BEATTACK_PROTOCOL;
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
					if ( lpObj->Class == 77 )	// Phoenix of Darkness
					{
						pAttack.NumberH = SET_NUMBERH(tObjNum);
						pAttack.NumberL = SET_NUMBERL(tObjNum);
						memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
						ASBOfs+= sizeof(pAttack);
						pCount.Count++;
					}
					else if ( lpObj->Class == 275 || gObjCalDistance(lpObj, &gObj[tObjNum]) < 6 )
					{
						pAttack.NumberH = SET_NUMBERH(tObjNum);
						pAttack.NumberL = SET_NUMBERL(tObjNum);
						memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
						ASBOfs+= sizeof(pAttack);
						pCount.Count++;
					}
				}
			}
		}

		count++;

		if ( count > MAX_VIEWPORT_MONSTER-1 )
			break;
	}

	if ( pCount.Count > 0 )
	{
		pCount.h.size = ASBOfs;
		memcpy(AttackSendBuff, &pCount, sizeof(pCount));

		if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 || lpObj->Class == 197 || lpObj->Class == 267 || lpObj->Class == 275 )
		{
			gObjMonsterBeattackRecv(AttackSendBuff, lpObj->m_Index);
		}
		else
		{
			CGBeattackRecv(AttackSendBuff, lpObj->m_Index, TRUE);
		}
	}
}


void gObjUseMonsterSpecialAbillity(LPOBJ lpMonsterObj)
{
	if ( lpMonsterObj->Class == 275 )	// Kundun
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = 1;
		pAttackMsg.NumberH = SET_NUMBERH(lpMonsterObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpMonsterObj->TargetNumber);
		pAttackMsg.Dis = 0;

		if ( (lpMonsterObj->MaxLife / 25.0f) > lpMonsterObj->Life  )
		{
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
		}
		else if ( (lpMonsterObj->MaxLife / 5.0f) > lpMonsterObj->Life  )
		{
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
		}
	}
}



void gObjMonsterBeattackRecv(BYTE * lpRecv, int aIndex)
{
	
	// Get Packet Pointer
	PMSG_BEATTACK_COUNT * lpCount = (PMSG_BEATTACK_COUNT *)lpRecv;

	// Set Offset
	int lOfs = sizeof(PMSG_BEATTACK_COUNT);

	int tNumber;	// Target Index Number

	// Get Current Magic
	CMagicInf * lpMagic = gObjGetMagic(&gObj[aIndex], lpCount->MagicNumber);

	if ( lpMagic == NULL )
	{
		LogAdd("error-L3 %s %d", __FILE__, __LINE__);
		return;
	}

	PMSG_BEATTACK * lpMsg;
	int lOfs2 = lOfs;
	int pTargetNumber[128]={0};

	for (int i=0;i<lpCount->Count;i++)
	{
		lpMsg = (PMSG_BEATTACK *)&lpRecv[lOfs2];
		pTargetNumber[i] = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		lOfs2+= sizeof(PMSG_BEATTACK);
	}
	
	for (int n=0;n<lpCount->Count;n++)
	{
		lpMsg = (PMSG_BEATTACK *)&lpRecv[lOfs];
		tNumber = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		gObjAttack(&gObj[aIndex], &gObj[tNumber], lpMagic, 1, 1, 0 ,0);
		lOfs+= sizeof(PMSG_BEATTACK);
	}
}





void gObjMonsterAttack(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	int AttackType = int(lpObj->m_AttackType);

	if ( AttackType >= 100 )
		AttackType = 0;

	if ( lpObj->m_iMonsterBattleDelay > 0 )
		return;

	if ( lpObj->Class == 144 || lpObj->Class == 174 || lpObj->Class == 182 || lpObj->Class == 190 ||
		lpObj->Class == 260 || lpObj->Class == 268 )
	{
		if ( rand()%2 )
		{
			PMSG_MAGICATTACK pAttackMsg;

			pAttackMsg.MagicNumber = 0;
			pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
			pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
			pAttackMsg.Dis = 0;

			CGMagicAttack(&pAttackMsg, lpObj->m_Index);
			return;
		}

		AttackType = 0;
	}

	if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 ||
		lpObj->Class == 197 || lpObj->Class == 267 || lpObj->Class == 275  )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = rand()%6+1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);

		if ( pAttackMsg.MagicNumber == 1 || pAttackMsg.MagicNumber == 2 || pAttackMsg.MagicNumber == 0 )
		{
			gObjUseMonsterSpecialAbillity(lpObj);	// Kundun
		}

		gObjMonsterMagicAttack(lpObj, lpObj->Class);
		return;
	}

	if ( lpObj->Class == 149 || lpObj->Class == 179 || lpObj->Class == 187 ||
		lpObj->Class == 195 || lpObj->Class == 265 || lpObj->Class == 273  )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = rand()%2+1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
		return;
	}
	
	if (     lpObj->Class == 145
          || lpObj->Class == 175
          || lpObj->Class == 183
          || lpObj->Class == 191
          || lpObj->Class == 261
          || lpObj->Class == 269
          || lpObj->Class == 146
          || lpObj->Class == 176
          || lpObj->Class == 184
          || lpObj->Class == 192
          || lpObj->Class == 262
          || lpObj->Class == 270
          || lpObj->Class == 147
          || lpObj->Class == 177
          || lpObj->Class == 185
          || lpObj->Class == 193
          || lpObj->Class == 263
          || lpObj->Class == 271
          || lpObj->Class == 148
          || lpObj->Class == 178
          || lpObj->Class == 186
          || lpObj->Class == 194
          || lpObj->Class == 264
          || lpObj->Class == 272
          || lpObj->Class == 160
          || lpObj->Class == 180
          || lpObj->Class == 188
          || lpObj->Class == 196
          || lpObj->Class == 266
          || lpObj->Class == 274 )
	{
		if ( (rand()%2) )
		{
			PMSG_MAGICATTACK pAttackMsg;

			pAttackMsg.MagicNumber = 1;
			pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
			pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
			pAttackMsg.Dis = 0;

			CGMagicAttack(&pAttackMsg, lpObj->m_Index);
			return;
		}
		AttackType = 0;
	}
	
	if (	 lpObj->Class == 89
          || lpObj->Class == 95
          || lpObj->Class == 112
          || lpObj->Class == 118
          || lpObj->Class == 124
          || lpObj->Class == 130
          || lpObj->Class == 143 )
	{

		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = rand()%2+1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else if (	   lpObj->Class == 163
            || lpObj->Class == 165
            || lpObj->Class == 167
            || lpObj->Class == 169
            || lpObj->Class == 171
            || lpObj->Class == 173 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = 1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else if ( lpObj->Class == 66 || lpObj->Class == 73 || lpObj->Class == 77 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = 1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}

#pragma message("Delete this unuseful Code with ADDON gObjMonsterAttack")

	else if ( lpObj->Class == 66 || lpObj->Class == 73 || lpObj->Class == 77 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumber = 1;
		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else
	{
		switch ( AttackType ) 
		{
			case 0:
				{
					PMSG_ATTACK pAttackMsg;

					pAttackMsg.AttackAction = 120;
					pAttackMsg.DirDis = lpObj->Dir;
					pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
					pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);

					CGAttack(&pAttackMsg, lpObj->m_Index);
				}
				break;
		
			default:
				{
					PMSG_MAGICATTACK pAttackMsg;
					pAttackMsg.MagicNumber = 0;
					pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
					pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
					pAttackMsg.Dis = 0;

					CGMagicAttack(&pAttackMsg, lpObj->m_Index);
				}
		}
	}
}




BOOL PathFindMoveMsgSend(LPOBJ lpObj)
{
	if ( lpObj->m_SkillHarden )
		return FALSE;

	if ( lpObj->m_iSkillStunTime > 0 )
		return FALSE;

	PATH_t path;
	PMSG_MOVE pMove;
	unsigned char bPath[8];
	

	pMove.h.c = 0xC1;
	pMove.h.headcode = MOVE_PROTOCOL;
	pMove.h.size = sizeof(pMove);
	pMove.X = lpObj->X;
	pMove.Y = lpObj->Y;

	BOOL bPathFound = FALSE;

	if ( lpObj->Type == OBJ_MONSTER && lpObj->m_bIsInMonsterHerd != FALSE )
	{
		bPathFound = MapC[lpObj->MapNumber].PathFinding3(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY, &path);
	}
	else
	{
		bPathFound = MapC[lpObj->MapNumber].PathFinding2(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY, &path);
	}

	if ( bPathFound )
	{
		int tx;
		int ty;
		int sx;
		int sy;
		BYTE pos = 0;

		memset(bPath, 0, sizeof(bPath));
		bPath[0] = (lpObj->Dir *16) + ((path.PathNum-1)&0x0F);
		sx = lpObj->X;
		sy = lpObj->Y;
		lpObj->PathX[0] = lpObj->X;
		lpObj->PathY[0] = lpObj->Y;
		lpObj->PathDir[0] = lpObj->Dir;

		for (int n=1;n<path.PathNum;n++)
		{
			tx = path.PathX[n];
			ty = path.PathY[n];
			pos = GetPathPacketDirPos(tx-sx, ty-sy);
			lpObj->PathX[n] = tx;
			lpObj->PathY[n] = ty;
			lpObj->PathDir[n] = pos;
			sx = tx;
			sy = ty;

			if ( (n%2)==1 )
			{
				bPath[(n+1)/2] = (pos * 16);
			}
			else
			{
				bPath[(n+1)/2] |= pos;
			}
		}

		lpObj->Dir = bPath[0] >> 4;
		lpObj->PathCount = bPath[0] & 0x0F;
		lpObj->PathCur = 1;
		lpObj->PathTime = GetTickCount();
		bPath[0] &= 0x0F;
		bPath[0] |= pos*16;
		memcpy(pMove.Path, bPath, sizeof(pMove.Path));

		if ( lpObj->PathCount > 0 )
		{
			MapC[lpObj->MapNumber].ClearStandAttr(lpObj->m_OldX, lpObj->m_OldY);
			MapC[lpObj->MapNumber].SetStandAttr(sx, sy);
			lpObj->m_OldX = sx;
			lpObj->m_OldY = sy;
		}

		PMoveProc(&pMove, lpObj->m_Index);
		return TRUE;
	}

	return FALSE;
}



void gObjMonsterMoveAction(LPOBJ lpObj)
{
	if ( lpObj->m_SkillHarden )
		return;

	if ( lpObj->m_iSkillStunTime >0 )
		return;

	int maxmoverange = lpObj->m_MoveRange*2+1;
	int searchc=10;
	lpObj->NextActionTime = 1000;
	BYTE tpx;
	BYTE tpy;

	while ( searchc-- != 0 )
	{
		__try
		{
			tpx = (lpObj->X - lpObj->m_MoveRange) + (rand()%maxmoverange);
			tpy = (lpObj->Y - lpObj->m_MoveRange) + (rand()%maxmoverange);
		}
		__except(maxmoverange=1, 1)
		{

		}

		int mchk = gObjMonsterMoveCheck(lpObj, tpx, tpy);
		BYTE attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);

		if ( (lpObj->Class ==249 || lpObj->Class == 247) && mchk )	// Guard
		{
			if ( (attr&2)!=2)
			{
				lpObj->MTX = tpx;
				lpObj->MTY = tpy;
				lpObj->m_ActState.Move = 1;
				lpObj->NextActionTime = 3000;
				return;
			}
		}
		else
		{
			if ( (attr&1)!=1 && (attr&2)!=2 && (attr&4)!=4 && (attr&8)!= 8 && mchk )
			{
				lpObj->TargetNumber = -1;
				lpObj->m_ActState.Attack = 0;
				lpObj->NextActionTime = 500;
				lpObj->m_ActState.Emotion = 0;
				lpObj->MTX = tpx;
				lpObj->MTY = tpy;
				lpObj->m_ActState.Move = 1;
				return;
			}
		}
	}
}




void gObjMonsterBaseAct(LPOBJ lpObj)
{
	LPOBJ lpTargetObj = NULL;

	if ( lpObj->TargetNumber >= 0 )
		lpTargetObj = &gObj[lpObj->TargetNumber];
	else
		lpObj->m_ActState.Emotion = 0;

	if ( lpObj->m_ActState.Emotion == 0 )
	{
		if ( lpObj->m_Attribute )
		{
			if ( lpObj->m_ActState.Attack )
			{
				lpObj->m_ActState.Attack = 0;
				lpObj->TargetNumber = -1;
				lpObj->NextActionTime = 500;
			}

			int actcode1 = rand()%2;

			if ( lpObj->m_Attribute == 100 )
				actcode1 = 1;
			
			if ( actcode1 == 0 )
			{
				lpObj->m_ActState.Rest = 1;
				lpObj->NextActionTime = 500;
			}
			else if ( lpObj->m_MoveRange > 0 && !lpObj->m_SkillHarden && !lpObj->m_iSkillStunTime )
			{
				if ( lpObj->m_Attribute != 100 )
				{
					gObjMonsterMoveAction(lpObj);
				}
				else
				{
					int tx=0;
					int ty=0;

					if ( lpObj->m_RecallMon >= 0 )
					{
						if ( gObj[lpObj->m_RecallMon].Connected > PLAYER_LOGGED )
						{
							LPOBJ lpRecallObj = &gObj[lpObj->m_RecallMon];

							if ( lpRecallObj->m_Rest == FALSE )
							{
								if ( gObjGetTargetPos(lpObj, lpRecallObj->X, lpRecallObj->Y, tx, ty) == TRUE )
								{
									lpObj->MTX = tx;
									lpObj->MTY = ty;
									lpObj->m_ActState.Move = 1;
									lpObj->NextActionTime = 1000;
								}
							}
						}
					}
				}
			}

			if (lpObj->Class == 249 || lpObj->Class == 247 )	// Guard
			{
				if (Configs.gEvent1)
				{
					if ( !(rand()%30) )
					{
						if ( lpObj->m_PK_Count == 0 )
						{
							ChatSend(lpObj, "하트 아이템을 상점에 주세요. 푸짐한 경품 이벤트 중");	// Need Translation
							lpObj->m_PK_Count = 0;
						}
					}
				}

				lpObj->TargetNumber = gObjGuardSearchEnemy(lpObj);

				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Class >= 248 )
					{
						lpObj->TargetNumber = -1;
					}
				}
			}
			else 
			{
				if ( lpObj->m_Attribute == 100 )
					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_MONSTER);
				else
					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_USER);
			}

			if ( lpObj->TargetNumber >= 0 )
			{
				lpObj->m_ActState.EmotionCount = 30;
				lpObj->m_ActState.Emotion = 1;
			}
		}
	}
	else if ( lpObj->m_ActState.Emotion == 1 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		if ( lpObj->TargetNumber >= 0 && lpObj->PathStartEnd == 0)
		{
			if ( BC_MAP_RANGE(lpObj->MapNumber) )
			{
				int iRAND_CHANGE_TARGET = rand()%10;

				if ( iRAND_CHANGE_TARGET == 3 )
					lpObj->LastAttackerID = -1;

				if ( iRAND_CHANGE_TARGET == 1 )
				{
					if ( lpObj->LastAttackerID != -1 && lpObj->LastAttackerID != lpObj->TargetNumber )
					{
						if ( gObj[lpObj->LastAttackerID].Connected > PLAYER_LOGGED &&
							lpObj->MapNumber == gObj[lpObj->LastAttackerID].MapNumber )
						{
							lpObj->TargetNumber = lpObj->LastAttackerID;
							lpTargetObj = &gObj[lpObj->LastAttackerID];
						}
					}
				}
			}

			int dis = gObjCalDistance(lpObj, lpTargetObj);
			int attackrange;

			if ( lpObj->m_AttackType >= 100 )	// #warning Change this To Level
				attackrange = lpObj->m_AttackRange+2;
			else
				attackrange = lpObj->m_AttackRange;

			if ( dis <= attackrange )
			{
				int tuser = lpObj->TargetNumber;
				int map = gObj[tuser].MapNumber;
				BYTE attr;

				if ( MapC[map].CheckWall(lpObj->X, lpObj->Y, gObj[tuser].X, gObj[tuser].Y) == TRUE )
				{
					attr = MapC[map].GetAttr(gObj[tuser].X, gObj[tuser].Y);

					if ( (attr&1) != 1 )
					{
						lpObj->m_ActState.Attack = 1;
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.EmotionCount = 30;
						lpObj->m_ActState.Emotion = 1;
					}

					lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y);
					lpObj->NextActionTime = lpObj->m_AttackSpeed;
				}
			}
			else
			{
				if ( gObjMonsterGetTargetPos(lpObj) == TRUE )
				{
					if ( MapC[lpObj->MapNumber].CheckWall(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY) == TRUE )
					{
						lpObj->m_ActState.Move = 1;
						lpObj->NextActionTime = 400;
						lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y);
					}
					else
					{
						gObjMonsterMoveAction(lpObj);
						lpObj->m_ActState.Emotion = 3;
						lpObj->m_ActState.EmotionCount = 10;

					}
				}
				else
				{
					gObjMonsterMoveAction(lpObj);
				}
			}
		}
	}
	else if ( lpObj->m_ActState.Emotion == 2 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 1;
		lpObj->NextActionTime = 800;

		if ( lpTargetObj )
		{
			int tdir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y)*2;
			lpObj->MTX += RoadPathTable[tdir] * (-3);
			lpObj->MTY += RoadPathTable[tdir+1] * (-3);
		}
	}
	else if ( lpObj->m_ActState.Emotion == 3 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 0;
		lpObj->m_ActState.Attack = 0;
		lpObj->NextActionTime = 400;
	}
}





void gObjTrapAttackEnemySearchX(LPOBJ lpObj, int count)
{
	lpObj->TargetNumber = -1;
	int tObjNum;
	int pos = lpObj->X;
	int y = lpObj->Y;

	for(int n =0;n<count;n++)
	{
		pos++;
		for(int i =0; i< MAX_VIEWPORT_MONSTER; i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Type==OBJ_USER)
				{
					if(gObj[tObjNum].Live)
					{
						if(y == gObj[tObjNum].Y)
						{
							if(pos == gObj[tObjNum].X)
							{
								if((gObj[tObjNum].Authority&2)!=2)
								{
									lpObj->TargetNumber = tObjNum;
									return;
								}
							}
						}
					}
				}
			}
		}
	}
}






void gObjTrapAttackEnemySearchY(LPOBJ lpObj, int count)
{
	lpObj->TargetNumber = -1;
	int tObjNum;
	int pos = lpObj->Y;
	int x = lpObj->X;

	for(int n =0;n<count;n++)
	{
		pos--;
		for(int i =0; i< MAX_VIEWPORT_MONSTER; i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Type==1)
				{
					if(gObj[tObjNum].Live)
					{
						if(pos == gObj[tObjNum].Y)
						{
							if(x == gObj[tObjNum].X)
							{
								if((gObj[tObjNum].Authority&2)!=2)
								{
									lpObj->TargetNumber = tObjNum;
									return;
								}
							}
						}
					}
				}
			}
		}
	}
}





void gObjTrapAttackEnemySearch(LPOBJ lpObj)
{
	int tObjNum;
	lpObj->TargetNumber = -1;

	for(int i = 0; i < MAX_VIEWPORT_MONSTER;i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if(tObjNum >= 0)
		{
			if(gObj[tObjNum].Type==1)
			{
				if(gObj[tObjNum].Live)
				{
					if(lpObj->Y == gObj[tObjNum].Y)
					{
						if(lpObj->X == gObj[tObjNum].X)
						{
							if((gObj[tObjNum].Authority&2)!=2)
							{
								lpObj->TargetNumber = tObjNum;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void gObjMonsterTrapAct(LPOBJ lpObj)
{
	if(lpObj->VPCount2 < 1)
	{
		return;
	}

	if(lpObj->m_AttackRange > 0)
	{
		if(lpObj->Dir == 3)
		{
			gObjTrapAttackEnemySearchX(lpObj,lpObj->m_AttackRange+1);
		}
		else if(lpObj->Dir == 1)
		{
			gObjTrapAttackEnemySearchY(lpObj,lpObj->m_AttackRange+1);
		}
	}
	else
	{
		gObjTrapAttackEnemySearch(lpObj);
	}

	if(lpObj->TargetNumber >= 0)
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}




void gObjTrapAttackEnemySearchRange(LPOBJ lpObj,int iRange)
{
	int tObjNum = -1;
	int iTargetingRate = 0;
	int iSuccessRate = 0;

	lpObj->TargetNumber = -1;

	if(lpObj->VPCount <= 0)
	{
		return;
	}

	iTargetingRate = 100 / lpObj->VPCount;

	for(int i = 0; i < MAX_VIEWPORT_MONSTER;i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if(tObjNum >= 0)
		{
			if(gObj[tObjNum].Type==1)
			{
				if(gObj[tObjNum].Live)
				{
					if((lpObj->Y - iRange) <= gObj[tObjNum].Y && (lpObj->Y + iRange) >= gObj[tObjNum].Y)
					{
						if((lpObj->X - iRange) <= gObj[tObjNum].X && (lpObj->X + iRange) >= gObj[tObjNum].X)
						{
							if((gObj[tObjNum].Authority&2)!=2)
							{
								lpObj->TargetNumber = tObjNum;
								iSuccessRate = rand()%100;

								if(iSuccessRate < iTargetingRate)
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}


 


BYTE NewOptionRand(int level)
{
	BYTE NOption = 0;
	NOption = 1 << (rand() % 6);

	if ( (NOption &2) != 0 )
	{
		if ( (rand()%2) != 0 )
		{
			NOption = 1 << (rand()%6);
		}
	}

	if ( (rand()% 4) == 0 )
	{
		NOption |= 1 << (rand()%6);
	}

	return NOption;
}




void InventoryDropItem(LPOBJ lpObj, int DropItem)
{
	return;	// there is NO MACRO NOR CODE
}



#pragma message("Apply this to create SkyLandShielkds -> gObjSkylandBossSheildAttack ")


void gObjSkylandBossSheildAttack(LPOBJ lpObj)
{
	if ( lpObj->VPCount2 < 1 ) 
		return;

	if ( lpObj->m_SkyBossMonSheildLinkIndex == -1 )
		return;

	if ( lpObj->m_SkyBossMonSheild == 0 )
		return;

	lpObj->TargetNumber = -1;

	int tObjNum;
	int shieldindex = lpObj->m_SkyBossMonSheildLinkIndex;

	if ( gObj[shieldindex].Life < 0.0f )
		return;

	if ( lpObj->m_AttackRange > 0 )
	{
		for (int i=0;i<MAX_VIEWPORT_MONSTER;i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if ( tObjNum >= 0 )
			{
				if ( gObj[tObjNum].Type == OBJ_USER )
				{
					if ( gObj[tObjNum].Live )
					{
						if ( gObjCheckTileArea(gObj[tObjNum].m_Index, lpObj->X, lpObj->Y, 2) )
						{
							if ( (gObj[tObjNum].Authority&2) != 2 )
							{
								lpObj->TargetNumber = tObjNum;
							}
						}
					}
				}
			}
		}
	}
	
	if ( lpObj->TargetNumber >= 0 )
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}





BOOL IsCanNotItemDtopInDevilSquare(int ItemType)
{
	int checkitemtype = ItemType  /MAX_SUBTYPE_ITEMS;
	int checkitemindex = ItemType % MAX_SUBTYPE_ITEMS;

	if ( checkitemtype >= 7 && checkitemtype <= 11 )
	{
		if (checkitemindex== 17 ||checkitemindex == 18||checkitemindex== 19 )
		{
			return FALSE;
		}
	}
	else if ( checkitemtype == 0 )
	{
		if (checkitemindex == 17 || checkitemindex == 18)
		{
			return FALSE;
		}
	}
	else if (checkitemtype == 12 )
	{
		if (checkitemindex== 12 || checkitemindex == 13 || checkitemindex == 14||
	checkitemindex == 16 || checkitemindex == 17 || checkitemindex == 18||
	checkitemindex == 19)
		{
			return FALSE;
		}
	}
	else if ( ItemType == ITEMGET(4,17) || ItemType ==ITEMGET(5,9)  )
	{
		return FALSE;
	}

	return TRUE;

}


void gObjRefillMonsterHP(LPOBJ lpMonsterObj, int iRefillHPSec)
{
	int iMonsterHP = lpMonsterObj->Life;
	int iRefillHP = 0;

	if(lpMonsterObj->Live==0)
	{
		return;
	}

	if(lpMonsterObj->Class == 275)
	{
	LPOBJ lpObj;
	if (lpMonsterObj->iObjectSecTimer > Configs.giKundunRefillHPTime)
		{
			iRefillHP = rand() % ((Configs.giKundunRefillHP > 0) ? Configs.giKundunRefillHP : 1);

			lpMonsterObj->iObjectSecTimer = 0;

			KUNDUN_EVENT_LOG.Output("[KUNDUN] HP Log -> [%d]회복  [%d]회복시간  [%7.0f]현재HP",
				iRefillHP, Configs.giKundunRefillHPTime, lpMonsterObj->Life);	// Deathway Translation
			lpMonsterObj->iObjectSecTimer = 0;
		}
		else
		{
			lpMonsterObj->iObjectSecTimer++;
		}

	if (lpMonsterObj->iObjectSecTimer % Configs.giKundunHPLogSaveTime == 0)
		{
			LogAddTD("[KUNDUN][Status Log] HP:%d RefillHP:%d Map:%d X:%d Y:%d",
				iMonsterHP,iRefillHP,lpMonsterObj->MapNumber,lpMonsterObj->X,lpMonsterObj->Y);
			if(gObjIsConnected(lpMonsterObj->LastAttackerID))
			{
				lpObj = &gObj[lpMonsterObj->LastAttackerID];
				LogAddTD("[KUNDUN][Attacker Info] [%s][%s] HP:%d MP:%d X:%d Y:%d",
					lpObj->AccountID,lpObj->Name,lpObj->Life,lpObj->Mana,lpObj->X,lpObj->Y);
			}
		}

		if(!g_CrywolfSync.GetOccupationState())
		{
			if(g_CrywolfSync.GetKundunHPRefillState()==1)
			{
				if(Configs.g_iCrywolfApplyMvpBenefit!=0)
				{
					iRefillHP = 0;
					iRefillHPSec = 0;
				}
			}
		}
	}

	iMonsterHP = iMonsterHP + iRefillHP + iRefillHPSec;

	if(lpMonsterObj->MaxLife < iMonsterHP)
	{
		lpMonsterObj->Life = lpMonsterObj->MaxLife;
	}
	else
	{
		lpMonsterObj->Life = iMonsterHP;
	}
}


#pragma message("gObjMonsterDieRewardItems Can be activate with the gObjMonsterItemDropLoadScript")

void gObjMonsterDieRewardItems(LPOBJ lpObj, LPOBJ lpTargetObj,
						  int iCount,
						  int iDropRateCommonItem,
						  int iDropRateExcellentItem,
						  int iDropRateSetItem,
						  BOOL bMustHaveSkill,
						  BOOL bMustHaveLuck,
						  BOOL bMustHaveAdditionalOption)
{
	int store_count=0;
	int DropItemNum=0;
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	unsigned char NOption=0;
	int item_drop=0;
	int exitem_drop=0;
	CItem * DropItem=NULL;
	int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
	int iSetDropPer=iDropRateSetItem;
	int iExtDropPer=iDropRateExcellentItem;
	int iCommonDropPer=iDropRateCommonItem;

	for (int i=0;i<iCount;i++)
	{
		BYTE cDropX = lpObj->X;
		BYTE cDropY = lpObj->Y;

		if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
		{
			cDropX = lpObj->X;
			cDropY = lpObj->Y;
		}

		if ( (rand()%10000) < iExtDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level-25);

			if ( !DropItem )
			{
				item_drop = 0;
				exitem_drop=0;
			}
			else
			{
				item_drop = 1;
				exitem_drop=1;
			}
		}
		else if ( (rand()%10000) < iCommonDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level);

			if ( !DropItem )
			{
				item_drop = 0;
			}
			else
			{
				item_drop = 1;
			}
		}

		if ( item_drop )
		{
			type = DropItem->m_Type;
			level = DropItem->m_Level;
			dur = DropItem->m_Durability;
			x = cDropX;
			y = cDropY;

			int option1rand;
			int option2rand;
			int option3rand;
			int optionc;

			if ( exitem_drop )
			{
				option1rand = 100;
				option2rand = 1;
				option3rand = rand()%100;
				optionc = rand()%3;
				NOption = NewOptionRand(lpObj->Level);
				level = 0;
			}
			else
			{
				option1rand = 6;
				option2rand = 4;
				option3rand = rand()%100;
				optionc = rand()%3;
				NOption = 0;
			}

			if ( (rand()%100) < option1rand )
			{
				Option1 = 1;
			}

			if ( (rand()%100) < option2rand )
			{
				Option2 = 1;
			}

			switch ( optionc )
			{
				case 0:
					if ( option3rand < 4 )
						Option3=3;
					break;
				case 1:
					if ( option3rand < 8 )
						Option3=2;
					break;
				case 2:
					if ( option3rand < 12 )
						Option3=1;
					break;
			}

			if ( DropItem->m_serial )
			{
				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1, Option2, Option3, MaxHitUser, NOption, 0);
			}
			else
			{
				MapC[lpObj->MapNumber].MonsterItemDrop(type, level, dur, x, y,
					Option1, Option2, Option3, NOption, 0, MaxHitUser, 0, 0);
			}
		}
	}
}


void gObjMonsterDieGiveItem(LPOBJ lpObj, LPOBJ lpTargetObj)
{

	int store_count=0;
	int ExtDropPer=0;
	int DropItemNum=0;
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	unsigned char NOption=0;
	BOOL item_drop=0;
	int n;
	CItem * DropItem=NULL;

	if ( lpObj->Class == 340 )	// Dark Elf
	{
		if ( Configs.g_bCrywolfMonsterDarkElfItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= Configs.g_iCrywolfMonsterDarkElfItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ Crywolf ][Reward] Monster Dark Elf ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				CrywolfDarkElfItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}
	
	if ( lpObj->Class == 349 )	// Crywolf Boss Monster
	{
		if ( Configs.g_bCrywolfBossMonsterItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= Configs.g_iCrywolfBossMonsterItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ Crywolf ][Reward] Boss Monster ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				CrywolfBossMonsterItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}		
	 
	if ( lpObj->m_btCsNpcType )
		return;

	if ( lpObj->Class == 295 )
	{
		int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		int iMaxCount = 1;

		for ( int i=0; i<iMaxCount ; i++ )
		{
			BYTE cDropX = lpObj->X;
			BYTE cDropY = lpObj->Y;

			LogAddTD("[Castle HuntZone] Boss Monster ItemDrop MaxHitUser [%d][%s][%s]",
				i, lpTargetObj->AccountID, lpTargetObj->Name);

			if ( gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10) == FALSE )
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			if ( i == 0 )
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			CastleHuntZoneBossRewardOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
		}
		return;
	} 
	 
	if ( lpObj->Class == 362 || lpObj->Class == 363 )	// Maya Hand
	{
		if ( Configs.g_bKanturuMayaHandItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= Configs.g_iKanturuMayaHandItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ KANTURU ][ Reward ] MayaHand ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				KanturuMayaHandItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}
	
	if ( lpObj->Class == 361 )	// NightMare
	{
		if ( Configs.g_bKanturuNightmareItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= Configs.g_iKanturuNightmareItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ KANTURU ][ Reward ] Nightmare ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				KanturuNightmareItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}

		return;
	} 
	if ( lpObj->Class == 275 ) // Kundun 
	{
		LogAddTD("[Kundun EVENT] Kundun die, Killer [%s][%s]",
			lpTargetObj->AccountID, lpTargetObj->Name);

		KUNDUN_EVENT_LOG.Output("[Kundun EVENT] Kundun die, Killer [%s][%s]",
			lpTargetObj->AccountID, lpTargetObj->Name);

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		int iMaxNumOfRewardItem = 3;

		for ( int i=0;i<iMaxNumOfRewardItem;i++)
		{
			BYTE cDropX = lpObj->X;
			BYTE cDropY = lpObj->Y;

			if ( OBJMAX_RANGE(MaxHitUser) )
			{

				LogAddTD("[Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);

				KUNDUN_EVENT_LOG.Output("[Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
			}
			else
			{
				LogAddTD("[Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);

				KUNDUN_EVENT_LOG.Output("[Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
			}

			if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			if ( lpObj->Class == 275 ) // Kundun	// useless if
			{
				if ( (rand()%10000) < 2500 )
				{
					MakeRewardSetItem(MaxHitUser, cDropX, cDropY, 1, lpObj->MapNumber);

					LogAddTD("[○Kundun EVENT] Drop SetItem ");
					KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop SetItem ");

					continue;
				}
			}

			if ( OBJMAX_RANGE(MaxHitUser ))
			{
				LogAddTD("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
				KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
			}
			else
			{
				LogAddTD("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
				KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
			}

			KundunEventItemBoxOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
		}

		return;
	}
	
	if ( lpObj->Class == 249 || lpTargetObj->Class == 249 ||	// Guard
		lpObj->Class == 247 || lpTargetObj->Class == 247 )	// Guard
	{
		return;
	}

	if ( lpObj->m_RecallMon >= 0 )
	{
		return;
	}
	
	if ( lpObj->Class == 131 )	// Castle Gate
	{
		return;
	}
	
	if ( BC_STATUE_RANGE(lpObj->Class-132) )	// Blood Castle Statue
	{
		return;
	}
	
	if ( CC_MAP_RANGE(lpObj->MapNumber) )
	{
		g_ChaosCastle.SearchNDropMonsterItem(lpObj->MapNumber-MAP_INDEX_CHAOSCASTLE1, lpObj->m_Index, lpTargetObj->m_Index);
		gObjDel(lpObj->m_Index);
		return;
	}
	
	if ( lpObj->m_bIsInMonsterHerd )
	{
		MonsterHerd * lpMH = lpObj->m_lpMonsterHerd;

		if ( lpMH )
		{
			if ( lpMH->MonsterHerdItemDrop(lpObj) )
			{
				return;
			}
		}
	}
	
	int itemrate = lpObj->m_ItemRate;
	int moneyrate = lpObj->m_MoneyRate;

	if ( itemrate < 1 )
		itemrate = 1;

	if ( moneyrate < 1 )
		moneyrate = 1;

	if ( lpObj->Class == 44 ) // Dragon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;

		if ( (rand()%4) > 0 )
		{
			for ( int n=0;n<4;n++)
			{
				int x = lpObj->X-2;
				int y = lpObj->Y-2;
				x+= rand()%3;
				y+= rand()%3;

				MapC[lpObj->MapNumber].MoneyItemDrop(10000, x, y);
			}

			return;
		}
		
		if ( (rand()%3) < 2 )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			type = ItemGetNumberMake(14, 13);
			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, MaxHitUser, 0, 0);

			return;
		}

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		type = ItemGetNumberMake(14, 14);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}

	if ( lpObj->Class == 43 ) // Golden Budge Dragon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;
		type = ItemGetNumberMake(14, 11);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}

	if ( lpObj->Class == 53 ) // Golden Titan
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 9;
		type = ItemGetNumberMake(14, 11);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}

	if ( lpObj->Class == 55 )	// Death King
	{
		if ( AttackEvent55BagOpen(lpObj)==1 )
			return;

		itemrate = 1;
	}
	else if ( lpObj->Class == 78 ) // Golden Goblin
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 8;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
	else if ( lpObj->Class == 79 )	// Golden Derkon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 10;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;	
	}
	else if ( lpObj->Class == 80 )	//Golden Lizard King
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 11;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;	
	}
	else if ( lpObj->Class == 82 )	// Golden Tantalos
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 12;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;	
	}

	if ( gEventMonsterItemDrop(lpObj, lpTargetObj) )
		return;

	if ( g_QuestInfo.MonsterItemDrop(lpObj) )
		return;

	if ( lpTargetObj->Level <= 20 )
	{
		if ( (rand()%10000) < 2000 )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			x = lpObj->X;
			y = lpObj->Y;
			dur = 1.0f;
			level = 0;
			type = ItemGetNumberMake(14, 0);	// Apple
			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, MaxHitUser, 0, 0);
		}
	}

	ExtDropPer = rand()%2000;	// Excellent Drop Percent #warning
	int ItemDropPer = Configs.gItemDropPer;
	ItemDropPer += Configs.gItemDropPer * lpTargetObj->SetOpImproveItemDropRate / 100;
	ItemDropPer = ItemDropPer * (lpTargetObj->m_wItemDropRate / 100.0f);

	if ( ExtDropPer == TRUE )
	{
		DropItem = g_MonsterItemMng.GetItem(lpObj->Level-25);

		if ( !DropItem )
			item_drop = FALSE;
		else
		{
			int foundChangeupitem=0;
			
			for ( int i=0;i<MAX_TYPE_PLAYER-1;i++)	// #error Delete the -1
			{
				if ( DropItem->m_RequireClass[i] > 1 )
				{
					foundChangeupitem = TRUE;
					break;
				}
			}

			if ( foundChangeupitem )
				ExtDropPer = rand()%100;

			if ( ExtDropPer )
				if ( (rand()%itemrate) < ItemDropPer )
					item_drop=TRUE;
		}
	}
	else
	{
		if ( (rand()%itemrate) < ItemDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level);

			if ( !DropItem )
				item_drop = FALSE;
			else
				item_drop = TRUE;

		}
	}

	if ( item_drop )
	{
		if ( !DropItem->IsItem() )
		{
			item_drop = FALSE;
		}

		int I;

		if ( DropItem->m_Type >= ITEMGET(15,0)  && DropItem->m_Type <= ITEMGET(16,0) )
		{
			I = 0;
		}

		if ( DS_MAP_RANGE(lpObj->MapNumber ) )
		{
			if ( !IsCanNotItemDtopInDevilSquare(DropItem->m_Type) )
			{
				if ( (rand()%10) )
				{
					item_drop = FALSE;
				}
			}
		}

		if ( DropItem->m_Type == ITEMGET(13,14) && lpObj->MapNumber != MAP_INDEX_ICARUS) // Loch Feather
			item_drop = FALSE;

		if ( g_CrywolfSync.GetOccupationState() == 1 && Configs.g_iCrywolfApplyMvpPenalty )
		{
			// Jewels
			if ( DropItem->m_Type == ITEMGET(14,13) ||  DropItem->m_Type == ITEMGET(14,14) ||  DropItem->m_Type == ITEMGET(14,16) ||
				 DropItem->m_Type == ITEMGET(14,22) ||  DropItem->m_Type == ITEMGET(12,15) ||  DropItem->m_Type == ITEMGET(14,31) )
			{
				if ( (rand()%100) > g_CrywolfSync.GetGemDropPenaltiyRate() )
				{
					item_drop = FALSE;
				}

			}
		}
	}

	if ( item_drop)
	{
		type = DropItem->m_Type;
		level = DropItem->m_Level;

		if ( ExtDropPer == TRUE )
		{
			dur = ItemGetDurability(DropItem->m_Type, 0, 1, 0);
		}
		else
		{
			dur = DropItem->m_Durability;
		}

		x = lpObj->X;
		y = lpObj->Y;

		int option1rand;
		int option2rand;
		int option3rand;
		int optionc;

		if ( ExtDropPer == TRUE )
		{
			option1rand=100;
			option2rand=1;
			option3rand=rand()%100;
			optionc=rand()%3;
			NOption = NewOptionRand(lpObj->Level);
			level = 0;
		}
		else
		{
			option1rand=6;
			option2rand=4;
			option3rand=rand()%100;
			optionc=rand()%3;
			NOption = 0;
		}

		if ( (rand()%100) < option1rand )
			Option1 = 1;

		if ( (rand()%100) < option2rand )
			Option2 = 1;

		switch ( optionc )
		{
			case 0:
				if ( option3rand < 4 )
					Option3=3;
				break;
			case 1:
				if ( option3rand < 8 )
					Option3=2;
				break;
			case 2:
				if ( option3rand < 12 )
					Option3=1;
				break;
		}

		if ( lpObj->Class == 43 ) // Golden Budge Dragon
		{
			Option1 = DropItem->m_Option1;
			Option2 = DropItem->m_Option2;
			Option3 = DropItem->m_Option3;
		}

		if ( type == ITEMGET(12,15) ||	// Chaos
			 type == ITEMGET(14,13) ||	// Bless
			 type == ITEMGET(14,14) ||	// Soul
			 type == ITEMGET(14,31) ||	// Guardian
			 type == ITEMGET(14,16))	// Life
		{
			Option1=0;
			Option2=0;
			Option3=0;
			NOption=0;
		}

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

		if ( DropItem->m_serial )
		{
			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, MaxHitUser, NOption, 0);
		}
		else
		{
			MapC[lpObj->MapNumber].MonsterItemDrop(type, level, dur, x, y, 
				Option1, Option2, Option3, NOption, 0, MaxHitUser, 0, 0);
		}
	}
	else if ( lpObj->Money < 1 )
	{
		return;
	}
	else if ( (rand()%moneyrate) < 10 )
	{
		int x = lpObj->X;
		int y = lpObj->Y;
		float money = lpObj->Money;
		money += (money/100.0f)*lpTargetObj->MonsterDieGetMoney;
		money +=7.0f;

		if ( DS_MAP_RANGE(lpObj->MapNumber) )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			gObj[MaxHitUser].m_nEventMoney += (int)money;
		}
		else
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(money, x, y);
		}
	}

	if ( lpObj->Money < 1 )
		return;

	if ( DS_MAP_RANGE(lpObj->MapNumber) )
		return;
	
	if ( (rand()%400) == 1 )
	{
		for ( n=0;n<4;n++)
		{
			int x = lpObj->X-2;
			int y = lpObj->Y-2;
			x+= rand()%3;
			y+= rand()%3;

			MapC[lpObj->MapNumber].MoneyItemDrop(lpObj->Money, x, y);
		}
	}

	if (Configs.gEvent1ItemDropTodayPercent > 0)
	{
		if ((rand() % Configs.gEvent1ItemDropTodayPercent) == 0)
		{
			if (Configs.gEvent1ItemDropTodayCount < Configs.gEvent1ItemDropTodayMax)
			{
				Configs.gEvent1ItemDropTodayCount++;
				type = ItemGetNumberMake(14, 12);	// Heart
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;
				level = 1;
				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y,
					type, level, dur, 0, 0, 0, -1, 0, 0);
			}
		}
	}

}



BOOL gEventMonsterItemDrop(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;
		if ( lpTargetObj->MapNumber == 41 && lpTargetObj->m_Quest[1] == 0xF6 ) //Third Quest Huge Anti-Hack
	{
		return FALSE;
	}
	else if ( lpTargetObj->MapNumber == 42 && lpTargetObj->m_Quest[1] == 0xDA ) //Third Quest Huge Anti-Hack
	{
		return FALSE;
	}

	if ( Configs.g_bFenrirStuffItemDrop )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		BOOL bDropStuff=FALSE;

		if ( lpObj->Level >= Configs.g_iFenrirStuff_01_DropLv_Min && lpObj->Level <= Configs.g_iFenrirStuff_01_DropLv_Max &&
			lpObj->MapNumber == Configs.g_iFenrirStuff_01_DropMap &&
			bDropStuff == FALSE )
		{
			if ( (rand()%10000) < Configs.g_iFenrirStuff_01_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 32);
			}
		}

		if ( lpObj->Level >= Configs.g_iFenrirStuff_02_DropLv_Min && lpObj->Level <= Configs.g_iFenrirStuff_02_DropLv_Max &&
			lpObj->MapNumber == Configs.g_iFenrirStuff_02_DropMap &&
			bDropStuff == FALSE )
		{
			if ( (rand()%10000) < Configs.g_iFenrirStuff_02_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 33);
			}
		}

		if ( lpObj->Level >= Configs.g_iFenrirStuff_03_DropLv_Min && lpObj->Level <= Configs.g_iFenrirStuff_03_DropLv_Max &&
			lpObj->MapNumber == Configs.g_iFenrirStuff_03_DropMap &&
			bDropStuff == FALSE )
		{
			if ( (rand()%10000) < Configs.g_iFenrirStuff_03_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 34);
			}
		}

		if ( bDropStuff )
		{
			level = 0;
			x = lpObj->X;
			y = lpObj->Y;
			dur = 1.0f;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( Configs.g_CompoundPotionDropOn == TRUE )
	{
		BOOL bDropStuff = FALSE;
		int iType = 0;

		if ( lpObj->Level >= Configs.g_iCompoundPotionLv1DropLevel && (rand()%10000) <= Configs.g_iCompoundPotionLv1DropRate &&
			bDropStuff == FALSE )
		{
			bDropStuff = TRUE;
			iType = ItemGetNumberMake(14, 38);
		}

		if ( bDropStuff == FALSE && lpObj->Level >= Configs.g_iCompoundPotionLv2DropLevel && (rand()%10000) <= Configs.g_iCompoundPotionLv2DropRate  )
		{
			bDropStuff = TRUE;
			iType = ItemGetNumberMake(14, 39);
		}
		

		if ( !bDropStuff )
		{
			if ( lpObj->Level >= Configs.g_iCompoundPotionLv3DropLevel && (rand()%10000) <= Configs.g_iCompoundPotionLv3DropRate )
			{
				bDropStuff = TRUE;
				iType = ItemGetNumberMake(14, 40);
			}
		}

		if ( bDropStuff == 1 )
		{
			int level = 0;
			int dur = 1;
			int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, lpObj->X, lpObj->Y, iType, level, dur,
				0,0,0, iMaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if (Configs.gIsItemDropRingOfTransform)
	{
		if ((rand() % 10000) < Configs.gItemDropRingOfTransform)
		{
			LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

			if ( lpattr )
			{
				int level = lpattr->m_Level;
				int callbead_level = 0;

				if ( level < 0 )
					level = 0;

				callbead_level = level / 10;

				if ( callbead_level > 0 )
					callbead_level--;

				if ( callbead_level > 5 )
					callbead_level = 5;

				dur = rand()%100+100.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = callbead_level;
				type = ItemGetNumberMake(13, 10);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if (Configs.gFireCrackerEvent)
	{
		if (Configs.gLanguage == 0)	// If Korea
		{
			if ( lpObj->MapNumber < 7 )
			{
				LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

				if ( lpattr )
				{
					if ( lpattr->m_Level >= 17 )
					{
						if ((rand() % 10000) < Configs.gFireCrackerDropRate)
						{
							dur = 255.0f;
							x = lpObj->X;
							y = lpObj->Y;
							level = 2;
							type = ItemGetNumberMake(14, 11);
							int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

							ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
								Option1,Option2,Option3, MaxHitUser, 0, 0);

							return TRUE;
						}
					}
				}
			}
		}
		else	// Only Fall on Party
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			if ( MaxHitUser != -1 )
			{
				int partycount = gParty.GetPartyCount(gObj[MaxHitUser].PartyNumber);

				if ( partycount > 0 )
				{
					LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

					if ( lpattr )
					{
						if ( lpattr->m_Level >= 17 )
						{
							if ((rand() % 10000) < Configs.gFireCrackerDropRate)
							{
								dur = 255.0f;
								x = lpObj->X;
								y = lpObj->Y;
								level = 2;
								type = ItemGetNumberMake(14, 11);

								ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
									Option1,Option2,Option3, MaxHitUser, 0, 0);

								return TRUE;
							}
						}
					}
				}
			}
		}
	}

	if (Configs.gXMasEvent)
	{
		if ( !StarOfXMasItemBag )
			return FALSE;

		if ( StarOfXMasItemBag->DropEventItem(lpObj->m_Index) )
			return TRUE;
	}

	if (Configs.gHeartOfLoveEvent)
	{
		if (Configs.gLanguage == 2)
		{
			LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

			if ( lpattr )
			{
				if ( lpattr->m_Level >=15 )
				{
					if ((rand() % 10000) < Configs.gHeartOfLoveDropRate)
					{
						dur = 255.0f;
						x = lpObj->X;
						y = lpObj->Y;
						level = 3;
						type = ItemGetNumberMake(14, 11);
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);

						return TRUE;
					}
				}
			}
		}
		else
		{
			if ( lpObj->MapNumber < 7 )
			{
				LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

				if ( lpattr )
				{
					if ( lpattr->m_Level >=17 )
					{
						if ((rand() % 10000) < Configs.gHeartOfLoveDropRate)
						{
							dur = 255.0f;
							x = lpObj->X;
							y = lpObj->Y;
							level = 3;
							type = ItemGetNumberMake(14, 11);
							int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

							ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
								Option1,Option2,Option3, MaxHitUser, 0, 0);

							return TRUE;
						}
					}
				}
			}
		}
	}
	
	if (Configs.gMedalEvent)
	{
		if ( lpObj->MapNumber == 1 || lpObj->MapNumber == 2 )	// Silver Medal
		{
			if ((rand() % 10000) < Configs.gSilverMedalDropRate)
			{
				dur = 255.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = 5;
				type = ItemGetNumberMake(14, 11);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->MapNumber == 4 || lpObj->MapNumber == 7 || lpObj->MapNumber == 8 )	// Gold Medal
		{
			if ((rand() % 10000) < Configs.gGoldMedalDropRate)
			{
				dur = 255.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = 6;
				type = ItemGetNumberMake(14, 11);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if (Configs.gEventChipEvent)
	{
		if ((rand() % 10000) < Configs.gBoxOfGoldDropRate)
		{
			dur = 255.0f;
			x = lpObj->X;
			y = lpObj->Y;
			level = 7;
			type = ItemGetNumberMake(14, 11);
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1,Option2,Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( (rand()%10000) < Configs.g_iKundunMarkDropRate )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		dur = 1.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;

		if ( lpObj->Level < 25 )
			level = 0;
		else if ( lpObj->Level < 47 )
			level = 1;
		else if ( lpObj->Level < 66 )
			level = 2;
		else if ( lpObj->Level < 78 )
			level = 3;
		else if ( lpObj->Level < 84 )
			level = 4;
		else if ( lpObj->Level < 92 )
			level = 5;
		else if ( lpObj->Level < 114 )
			level = 6;
		else if ( lpObj->Level > 115 && lpObj->Level < MAX_CHAR_LEVEL+1 )
			level = 7;

		if ( level == 0 )
			return FALSE;

		type = ItemGetNumberMake(14, 29);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1,Option2,Option3, MaxHitUser, 0, 0);

		return TRUE;
	}

	if ( (rand()%10000) < Configs.g_iMarkOfTheLord )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		level = 3;
		dur = 1.0f;
		x = lpObj->X;
		y = lpObj->Y;
		type = ItemGetNumberMake(14, 21);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1,Option2,Option3, MaxHitUser, 0, 0);

		return TRUE;
	}

	if ( (rand()%10000) < Configs.g_iJapan1StAnivItemDropRate )
	{
		if ( lpTargetObj->PartyNumber >= 0 )
		{
			dur = 255.0f;
			x = lpObj->X;
			y = lpObj->Y;
			type = ItemGetNumberMake(14,20);	// Branch of Rmedy of Love

			switch ( lpObj->MapNumber )
			{
				case 0:
					{
						level = 1;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						
						return TRUE;
					}
				case 1:
					{
						level = 2;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 2:
					{
						level = 2;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 3:
					{
						level = 1;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 4:
					{
						level = 3;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 7:
					{
						level = 4;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 8:
					{
						level = 5;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
							Option1,Option2,Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
			}
		}
	}

	if (Configs.gIsDropDarkLordItem)
	{
		if (lpObj->Level >= Configs.gSleeveOfLordDropLevel)
		{
			if ((rand() % 10000) < Configs.gSleeveOfLordDropRate)
			{
				type = ItemGetNumberMake(13,14);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if (lpObj->Level >= Configs.gSoulOfDarkHorseropLevel)
		{
			if ((rand() % 10000) < Configs.gSoulOfDarkHorseDropRate)
			{
				type = ItemGetNumberMake(13,31);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if (lpObj->Level >= Configs.gSoulOfDarkSpiritDropLevel)
		{
			if ((rand() % 10000) < Configs.gSoulOfDarkSpiritDropRate)
			{
				type = ItemGetNumberMake(13,31);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if (Configs.gIsDropGemOfDefend)
	{
		if ( lpObj->MapNumber != MAP_INDEX_KALIMA7 && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE )
		{
		}
		else
		{
			if (lpObj->Level >= Configs.gGemOfDefendDropLevel)
			{
				if ((rand() % 10000)< Configs.gGemOfDefendDropRate)
				{
					type = ItemGetNumberMake(14,31);
					level = 0;
					x = lpObj->X;
					y = lpObj->Y;
					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
						Option1,Option2,Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if (Configs.gIsDropSetItemInCastleHuntZone)
	{
		if ( lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE )
		{
		}
		else
		{
			if (lpObj->Level >= Configs.gSetItemInCastleHuntZoneDropLevel)
			{
				if ((rand() % 10000) < Configs.gSetItemInCastleHuntZoneDropRate)
				{
					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					if ( CHECK_LIMIT(MaxHitUser, OBJMAX) )
					{
						LogAddTD("[Castle HuntZone] Drop SetItem [%s][%s] ",
							gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
			
						MakeRewardSetItem(MaxHitUser, lpObj->X, lpObj->Y, 0, lpObj->MapNumber);
						return TRUE;
					}
				}
			}
		}
	}
	if ( Configs.g_bKanturuSpecialItemDropOn )
	{
		if ( lpObj->MapNumber == MAP_INDEX_KANTURU2 )
		{
			if ( (rand()%10000) < Configs.g_iKanturuMoonStoneDropRate )
			{
				type = ItemGetNumberMake(13,38);	// Moon Stone
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if ( lpObj->MapNumber == MAP_INDEX_KANTURU1 ||
			 lpObj->MapNumber == MAP_INDEX_KANTURU2 ||
			 lpObj->MapNumber == MAP_INDEX_KANTURU_BOSS )
		{
			if ( (rand()%10000) < Configs.g_iKanturuJewelOfHarmonyDropRate )
			{
				type = ItemGetNumberMake(14,41);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}
	if ( lpObj->MapNumber == MAP_INDEX_AIDA || lpObj->MapNumber == MAP_INDEX_CRYWOLF_FIRSTZONE)
	{
		bool bDropMysteriousBead = false;

		switch ( lpObj->Class )
		{
			case 304:	case 305:	case 306:
			case 307:	case 308:	case 309:
				if ( (rand()%10000) < Configs.g_iMysteriousBeadDropRate1 )
					bDropMysteriousBead = true;
				break;

			case 310:	case 311:	case 312:	case 313:
				if ( (rand()%10000) < Configs.g_iMysteriousBeadDropRate2 )
					bDropMysteriousBead = true;
				break;
		}

		if ( bDropMysteriousBead == true )
		{
			type = ItemGetNumberMake(12,26);
			level = 0;
			x = lpObj->X;
			y = lpObj->Y;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1,Option2,Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( Configs.g_bBloodCastle )
	{
		if ( !BC_MAP_RANGE(lpObj->MapNumber ) )
		{
			Option1=0;
			Option2=0;
			Option3=0;

			if ( (rand()%10000) < Configs.g_iAngelKingsPaperDropRate )
			{
				dur = 128.0f;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level < 32 )
					level = 1;
				else if ( lpObj->Level < 45 )
					level = 2;
				else if ( lpObj->Level < 57 )
					level = 3;
				else if ( lpObj->Level < 68 )
					level = 4;
				else if ( lpObj->Level < 76 )
					level = 5;
				else if ( lpObj->Level < 84 )
					level = 6;
				else
					level = 7;

				type = ItemGetNumberMake(13,16);

				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}

			if ( (rand()%10000) < Configs.g_iBloodBoneDropRate )
			{
				dur = 128.0f;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level < 32 )
					level = 1;
				else if ( lpObj->Level < 45 )
					level = 2;
				else if ( lpObj->Level < 57 )
					level = 3;
				else if ( lpObj->Level < 68 )
					level = 4;
				else if ( lpObj->Level < 76 )
					level = 5;
				else if ( lpObj->Level < 84 )
					level = 6;
				else
					level = 7;

				type = ItemGetNumberMake(13,17);

				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( (rand()%10000) < Configs.g_iDarkLordHeartDropRate )
	{
		int iDropRate = 0;

		if ( lpTargetObj->MapNumber == 0 || lpTargetObj->MapNumber == 3 || lpTargetObj->MapNumber == 2 )
		{
			type = ItemGetNumberMake(14,11);
			level = 13;
			x = lpObj->X;
			y = lpObj->Y;
			dur = 0;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1,Option2,Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( Configs.g_bRibbonBoxEvent )
	{
		if ( lpObj->Level >= Configs.g_iRedRibbonBoxDropLevelMin && lpObj->Level <= Configs.g_iRedRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iRedRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,32);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iGreenRibbonBoxDropLevelMin && lpObj->Level <= Configs.g_iGreenRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iGreenRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,33);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iBlueRibbonBoxDropLevelMin && lpObj->Level <= Configs.g_iBlueRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iBlueRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,34);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( Configs.g_bChocolateBoxEvent )
	{
		if ( lpObj->Level >= Configs.g_iPinkChocolateBoxDropLevelMin && lpObj->Level <= Configs.g_iPinkChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iPinkChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,32);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iRedChocolateBoxDropLevelMin && lpObj->Level <= Configs.g_iRedChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iRedChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,33);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iBlueChocolateBoxDropLevelMin && lpObj->Level <= Configs.g_iBlueChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iBlueChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,34);
				level = 0;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( Configs.g_bCandyBoxEvent )
	{
		if ( lpObj->Level >= Configs.g_iLightPurpleCandyBoxDropLevelMin && lpObj->Level <= Configs.g_iLightPurpleCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iLightPurpleCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,32);
				level = 1;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iVermilionCandyBoxDropLevelMin && lpObj->Level <= Configs.g_iVermilionCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iVermilionCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,33);
				level = 1;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= Configs.g_iDeepBlueCandyBoxDropLevelMin && lpObj->Level <= Configs.g_iDeepBlueCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < Configs.g_iDeepBlueCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,34);
				level = 1;
				x = lpTargetObj->X;
				y = lpTargetObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpTargetObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( Configs.g_bHallowinDayEventOn )
	{
		bool bIsBossMonster = false;

		if ( lpObj->m_Index == 349 || lpObj->m_Index == 364 || lpObj->m_Index == 361 ||
			 lpObj->m_Index == 362 || lpObj->m_Index == 363 )
			bIsBossMonster = true;

		if ( !bIsBossMonster )
		{
			if ( (rand()%10000) < Configs.g_iHallowinDayEventItemDropRate  )
			{
				type = ItemGetNumberMake(14,45);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
					Option1,Option2,Option3, iMaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	return FALSE;
}





void CQeustNpcTeleport::Run(int aIndex)
{
	if ( this->RefCount > 0 )
	{
		return;
	}

	this->TimeCount++;

	if (this->TimeCount > Configs.gQuestNPCTeleportTime)
	{
		PMSG_MAGICATTACK_RESULT pMsg;

		this->TimeCount = 0;

		PHeadSetBE((LPBYTE)&pMsg, 0x19, sizeof(pMsg));
		pMsg.MagicNumber = 6;
		pMsg.SourceNumberH = SET_NUMBERH(aIndex);
		pMsg.SourceNumberL = SET_NUMBERL(aIndex);
		pMsg.TargetNumberH = SET_NUMBERH(aIndex);
		pMsg.TargetNumberL = SET_NUMBERL(aIndex);

		MsgSendV2(&gObj[aIndex], (UCHAR*)&pMsg, pMsg.h.size);
		gObjViewportListProtocolDestroy(&gObj[aIndex]);
		gObjClearViewport(&gObj[aIndex]);

		int tableindex;

		while ( true )
		{
			tableindex = rand() % MAX_QUEST_TELEPORT;

			if ( this->LastMapNumber != tableindex )
			{
				this->LastMapNumber = tableindex;
				break;
			}
		}

		gObj[aIndex].X = this->m_QuestNPCTeleportPos[tableindex].x;
		gObj[aIndex].Y = this->m_QuestNPCTeleportPos[tableindex].y;
		gObj[aIndex].TX = gObj[aIndex].X;
		gObj[aIndex].TY = gObj[aIndex].Y;
		gObj[aIndex].MTX = gObj[aIndex].X;
		gObj[aIndex].MTY = gObj[aIndex].Y;
		gObj[aIndex].m_OldX = gObj[aIndex].TX;
		gObj[aIndex].m_OldY = gObj[aIndex].TY;
		gObj[aIndex].MapNumber = this->m_QuestNPCTeleportPos[tableindex].mapnum;
		gObj[aIndex].Dir = this->m_QuestNPCTeleportPos[tableindex].dir;
		gObj[aIndex].StartX = gObj[aIndex].X;
		gObj[aIndex].StartY = gObj[aIndex].Y;
		gObj[aIndex].m_State = 1;
		gObj[aIndex].PathCount = 0;

		LogAdd("Marlon NPC Teleport Map: %d", tableindex);	// #warning Translation Deathway
	}
}


