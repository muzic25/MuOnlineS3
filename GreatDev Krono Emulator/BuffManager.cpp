// BuffManager.cpp: implementation of the CBuffManager class.
//	GS-N	1.00.90	JPN	0xXXXXXXXX - Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BuffEffect.h"
#include "user.h"
#include "BuffManager.h"
#include "ViewportSkillState.h"
#include "ItemAddOption.h"
#include "protocol.h"
#include "winutil.h"
#include "logproc.h"

CBuffManager g_BuffManager;

CBuffManager::CBuffManager()
{

}

CBuffManager::~CBuffManager()
{

}

//Identical -> 3 Calls
BOOL CBuffManager::InsertEffect(LPOBJ lpObj, int iEffectIndex, BYTE btEffectType1, BYTE btEffectType2, int iValue1, int iValue2, int iDuration) //0063ECE0
{
	LPBUFF_EFFECT_DATA pEffectIndex = 0; //loc2
	LPBUFF_EFFECT_DATA pEffectIndex2 = 0; //loc3

	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;

	if(lpObj == NULL)
	{
		return -1;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return -1;
	}

	if(g_BuffEffect.IsValidIndex(iEffectIndex) == FALSE)
	{
		return -1;
	}

	pEffectIndex = g_BuffEffect.GetBuffData(iEffectIndex);

	if(pEffectIndex == NULL)
	{
		return -1;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if( lpObj->m_BuffEffectState[i].btBuffIndex != NULL )
		{
			pEffectIndex2 = g_BuffEffect.GetBuffData(lpObj->m_BuffEffectState[i].btBuffIndex);

			if(pEffectIndex2 == NULL) //season4 add-on (wz fix)
			{
				continue;
			}
			
			if(pEffectIndex2->btViewPortIndex == pEffectIndex->btViewPortIndex )
			{
				this->ClearEffect(lpObj,lpObj->m_BuffEffectState[i].btBuffIndex);
				loc6 = pEffectIndex2->btIndex;
			}

			if(pEffectIndex2->btType == 0)
			{
				loc4 +=1;
			}
			else if(pEffectIndex2->btType == 1)
			{
				loc5 += 1;	
			}

			if(i > lpObj->m_btViewStateCount)
			{
				break;
			}
		}
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex == NULL)
		{
			lpObj->m_BuffEffectState[i].btBuffIndex = iEffectIndex;
			lpObj->m_BuffEffectState[i].btVpIndex = pEffectIndex->btViewPortIndex;
			lpObj->m_BuffEffectState[i].btEffectType1 = btEffectType1;
			lpObj->m_BuffEffectState[i].btEffectType2 = btEffectType2;
			lpObj->m_BuffEffectState[i].iValue1 = iValue1;
			lpObj->m_BuffEffectState[i].iValue2 = iValue2;
			lpObj->m_BuffEffectState[i].iDuration = iDuration;
			lpObj->m_BuffEffectState[i].dwBuffTickCount = GetTickCount();

			g_ViewportSkillState.AddBuffEffect(lpObj,btEffectType1,iValue1); //first
			g_ViewportSkillState.AddBuffEffect(lpObj,btEffectType2,iValue2); //second
			break;
		}
	}

	return loc6;
}

//Identical -> 5 Calls
BYTE CBuffManager::ClearEffect(LPOBJ lpObj,int iEffectIndex)
{
	BYTE btResult = 0;

	if(lpObj == NULL)
	{
		return 0;
	}
	
	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	if(g_BuffEffect.IsValidIndex(iEffectIndex) == FALSE)
	{
		return 0;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(btResult == 1)
		{
			if( (lpObj->m_BuffEffectState[i].btBuffIndex != 0) && (i > 0) )
			{
				memcpy(&lpObj->m_BuffEffectState[i-1],&lpObj->m_BuffEffectState[i],sizeof(lpObj->m_BuffEffectState[i])); //Change the Buff Slot to the removed one...
				memset(&lpObj->m_BuffEffectState[i],0,sizeof(lpObj->m_BuffEffectState[i]));
			}
		}
		
		if(lpObj->m_BuffEffectState[i].btBuffIndex == iEffectIndex ) //Will Clear the Effect
		{
			g_ViewportSkillState.RemoveBuffEffect(lpObj,lpObj->m_BuffEffectState[i].btEffectType1,lpObj->m_BuffEffectState[i].iValue1);
			g_ViewportSkillState.RemoveBuffEffect(lpObj,lpObj->m_BuffEffectState[i].btEffectType2,lpObj->m_BuffEffectState[i].iValue2);
			memset(&lpObj->m_BuffEffectState[i],0,sizeof(lpObj->m_BuffEffectState[i]));
			btResult = 1;
		}
	}

	return btResult;
}

//Identical -> 2 Calls
BYTE CBuffManager::SearchActiveEffect(LPOBJ lpObj,int iEffectIndex)
{
	if( g_BuffEffect.IsValidIndex(iEffectIndex) == FALSE )
	{
		return 0;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex == iEffectIndex)
		{
			return 1;
		}
	}

	return 0;
}

//Identical -> 1 Calls
void CBuffManager::RemoveIceEffect(LPOBJ lpObj,int iEffectIndex)
{
	int iEffectID = iEffectIndex;

	if(iEffectID != AT_ICE) //56	28	255	255	Ice	1	1	1	Diminui velocidade de mobilidade
	{
		return;
	}

	lpObj->DelayActionTime = 0;
	lpObj->DelayLevel = 0;
	lpObj->m_IceType = 0;
}

//Identical -> 1 Calls
int CBuffManager::SearchAndClearEffect(LPOBJ lpObj,int iEffectClearType)
{
	LPBUFF_EFFECT_DATA pEffect = NULL;

	int loc3 = 0; //clear count
	
	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if( this->SearchActiveEffect(lpObj,lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE )
		{
			pEffect = g_BuffEffect.GetBuffData(lpObj->m_BuffEffectState[i].btBuffIndex); //Get Buff Info

			if(pEffect == NULL)
			{
				continue;
			}

			if(pEffect->btClearType == iEffectClearType)
			{
				if( this->ClearEffect(lpObj,lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
				{
					loc3 += 1;
					i -= 1;
				}
			}

			if(iEffectClearType == AT_GENERAL)
			{
				if( this->ClearEffect(lpObj,lpObj->m_BuffEffectState[i].btBuffIndex ) == TRUE)
				{
					loc3 += 1;
					i -= 1;
				}
			}

			if(iEffectClearType == AT_MONSTER_GENERAL)
			{
				if( this->ClearEffect(lpObj,lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
				{
					loc3 += 1;
					i -= 1;
				}
			}
		}
	}
	return loc3;
}

//Identical -> 4 Calls
LPBUFF_EFFECT_DATA CBuffManager::GetBuffInfo(int iEffectIndex)
{
	LPBUFF_EFFECT_DATA pEffect = NULL;

	if(g_BuffEffect.IsValidIndex(iEffectIndex) == FALSE)
	{
		return NULL;
	}
	
	pEffect = g_BuffEffect.GetBuffData(iEffectIndex);

	return pEffect;
}

//Identical -> 0 Calls
int CBuffManager::GetBuffClearType(BYTE btEffectIndex)
{
	LPBUFF_EFFECT_DATA pEffect = NULL;

	if(g_BuffEffect.IsValidIndex(btEffectIndex) == FALSE)
	{
		return -1;
	}

	pEffect = g_BuffEffect.GetBuffData(btEffectIndex);

	return pEffect->btClearType;
}

//Identical -> 1 Calls (Control the Buffs)
void gObjBuffEffectUseProc(LPOBJ lpObj)
{
	if(lpObj == NULL)
	{
		return;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return;
	}

	if( (lpObj->Type == OBJ_USER && lpObj->Connected >= PLAYER_PLAYING) || lpObj->Type == OBJ_MONSTER) //Connected Users or Monsters General
	{
		for(int i = 0; i < MAX_STATE_COUNT; i++)
		{
			if(lpObj->m_BuffEffectState[i].iDuration == -10) //Infinite Buff
			{
				continue;
			}

			if(lpObj->m_BuffEffectState[i].btBuffIndex == NULL) //No Buff in the Slot
			{
				continue;
			}

			switch(lpObj->m_BuffEffectState[i].btBuffIndex)
			{
			case AT_POISON: //55	27	255	255	Poison	1	1	1	Poisoned status of condition
				{
					if((lpObj->m_BuffEffectState[i].iDuration % 3) == 0) //Rand type??
					{
						g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType1, lpObj->m_BuffEffectState[i].iValue1);
						g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType2, lpObj->m_BuffEffectState[i].iValue2);
					}
				}
				break;
			default:
				{
					g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType1, lpObj->m_BuffEffectState[i].iValue1);
					g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType2, lpObj->m_BuffEffectState[i].iValue2);
				}
				break;
			}
			
			lpObj->m_BuffEffectState[i].iDuration--; //Reduce Time per Second

			if(lpObj->m_BuffEffectState[i].iDuration <= 0) //Clear if Zero!
			{
				gObjRemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[i].btBuffIndex);
			}
		}
	}
}

//Identical -> 5 Calls
BYTE gObjSetItemEffect(LPOBJ lpObj, int iEffectIndex)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	int iEffectOption = 0; //loc1
	LPITEMEFFECT lpItemEffect = NULL; //loc2
	LPBUFF_EFFECT_DATA pEffect = NULL; //loc3

	pEffect = g_BuffManager.GetBuffInfo(iEffectIndex);

	if(pEffect == NULL)
	{
		return 0;
	}

	iEffectOption = (pEffect->btItemType << 9) + pEffect->btItemIndex;

	if(g_ItemAddOption.SearchForClearItemEffect(iEffectOption) == FALSE)
	{
		return 0;
	}

	lpItemEffect = g_ItemAddOption.SearchItemEffectType1(iEffectOption);

	int InsertEffectResult = 0; //loc4

	InsertEffectResult = g_BuffManager.InsertEffect(lpObj, iEffectIndex, lpItemEffect->wEffectType1, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue1, lpItemEffect->iEffectValue2, lpItemEffect->iEffectValidTime);

	if(InsertEffectResult != -1)
	{
		if(InsertEffectResult > 0)
		{
			GCUseBuffEffect(lpObj, InsertEffectResult, 2, lpItemEffect->wOptionType, 0, 0);
		}
		else
		{
			lpObj->m_btViewStateCount++;
		}

		GCUseBuffEffect(lpObj, iEffectIndex, 0, lpItemEffect->wOptionType, lpItemEffect->wEffectType1, lpItemEffect->iEffectValidTime);
		return 1;
	}
	
	return 0;
}

//Identical -> 62 calls
BYTE gObjApplyBuffEffectDuration(LPOBJ lpObj, int iEffectIndex, BYTE btEffectType1, int iValue1, BYTE btEffectType2, int iValue2, int iDuration)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	LPBUFF_EFFECT_DATA pEffect = NULL; //loc1

	pEffect = g_BuffManager.GetBuffInfo(iEffectIndex);

	int InsertEffectResult = 0; //loc2

	InsertEffectResult = g_BuffManager.InsertEffect(lpObj, iEffectIndex, btEffectType1, btEffectType2, iValue1, iValue2, iDuration);

	if(InsertEffectResult != -1)
	{
		if(InsertEffectResult > 0)
		{
			GCUseBuffEffect(lpObj, InsertEffectResult, 2, pEffect->btViewPortIndex, 0, 0);
		}
		else
		{
			lpObj->m_btViewStateCount++;
		}

		GCUseBuffEffect(lpObj, iEffectIndex, 0, pEffect->btViewPortIndex, btEffectType1, iDuration);
#if(DEBUG_BUFF_EFFECT == 1)
	char szTemp[256];
	sprintf(szTemp, "[BUFFMANAGER] Insert Common-Buff Name %s Effect1[%d] Value1[%d] Effect2[%d] Value2[%d] Dur[%d]", pEffect->szBuffName, btEffectType1, iValue1, btEffectType2, iValue2, iDuration);
	LogAddTD(szTemp);

	switch(lpObj->Type)
	{
	case OBJ_USER:
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		break;
	case OBJ_MONSTER:
	case OBJ_NPC:
		GCServerMsgStringSend(szTemp, lpObj->lpAttackObj->m_Index, 1);
		break;
	}
#endif
		return 1;
	}

	return 0;
}

//Identical -> 1 Call
BYTE gObjApplyBuffEffectItemPeriod(LPOBJ lpObj, int iEffectIndex, int iDuration)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	int iEffectOption = 0; //loc1
	LPITEMEFFECT lpItemEffect = NULL; //loc2
	LPBUFF_EFFECT_DATA pEffect = NULL; //loc3

	pEffect = g_BuffManager.GetBuffInfo(iEffectIndex);

	if(pEffect == NULL)
	{
		return 0;
	}

	iEffectOption = (pEffect->btItemType << 9) + pEffect->btItemIndex;

	if(g_ItemAddOption.SearchForClearItemEffect(iEffectOption) == FALSE)
	{
		return 0;
	}

	lpItemEffect = g_ItemAddOption.SearchItemEffectType1(iEffectOption);

	int InsertEffectResult = 0; //loc4

	InsertEffectResult = g_BuffManager.InsertEffect(lpObj, iEffectIndex, lpItemEffect->wEffectType1, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue1, lpItemEffect->iEffectValue2, iDuration);

	if(InsertEffectResult != -1)
	{
		if(InsertEffectResult > 0)
		{
			GCUseBuffEffect(lpObj, InsertEffectResult, 2, lpItemEffect->wOptionType, 0, 0);
		}
		else
		{
			lpObj->m_btViewStateCount++;
		}

		GCUseBuffEffect(lpObj, iEffectIndex, 0, lpItemEffect->wOptionType, lpItemEffect->wEffectType1, iDuration);
#if(DEBUG_BUFF_EFFECT == 1)
	char szTemp[256];
	sprintf(szTemp, "[BUFFMANAGER] Insert CashShop-Buff Name %s ItemAddOption-IDX[%d] Effect1[%d] Value1[%d] Effect2[%d] Value2[%d] Dur[%d]", pEffect->szBuffName, iEffectOption, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2, iDuration);
	LogAddTD(szTemp);

	switch(lpObj->Type)
	{
	case OBJ_USER:
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		break;
	case OBJ_MONSTER:
	case OBJ_NPC:
		GCServerMsgStringSend(szTemp, lpObj->lpAttackObj->m_Index, 1);
		break;
	}
#endif
		return 1;
	}

	return 0;
}

//Identical
BYTE gObjRemoveBuffEffect(LPOBJ lpObj, int iEffectIndex)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	LPBUFF_EFFECT_DATA pEffect = NULL; //loc1

	pEffect = g_BuffManager.GetBuffInfo(iEffectIndex);

	if(pEffect == NULL)
	{
		return 0;
	}

	if(g_BuffManager.ClearEffect(lpObj, iEffectIndex) == TRUE)
	{
		g_BuffManager.RemoveIceEffect(lpObj, iEffectIndex); //For Ice Effect Only
		lpObj->m_btViewStateCount--;
		GCUseBuffEffect(lpObj, iEffectIndex, 1, 0, pEffect->btViewPortIndex, 0);
#if(DEBUG_BUFF_EFFECT == 1)
	char szTemp[256];
	sprintf(szTemp, "[BUFFMANAGER] Remove Buff Name %s", pEffect->szBuffName);
	LogAddTD(szTemp);

	switch(lpObj->Type)
	{
	case OBJ_USER:
		GCServerMsgStringSend(szTemp, lpObj->m_Index, 1);
		break;
	case OBJ_MONSTER:
	case OBJ_NPC:
		GCServerMsgStringSend(szTemp, lpObj->lpAttackObj->m_Index, 1);
		break;
	}
#endif
		return 1;
	}

	return 0;
}

//Identical -> 9 Calls
BYTE gObjClearStandardBuffEffect(LPOBJ lpObj, int iEffectClearType) //0063FD80
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	int RemovedCount = 0; //ebp-4
	int i = 0; //ebp-8
	
	switch(iEffectClearType)
	{
	case AT_SIEGE_GENERAL: //Siege ??
		{
			for(i = 0; i < MAX_STATE_COUNT; i++)
			{
				switch(lpObj->m_BuffEffectState[i].btBuffIndex)
				{
				case AT_WATCHING_TOWER:
				case AT_ATTACKING_GUILD1:
				case AT_ATTACKING_GUILD2:
				case AT_ATTACKING_GUILD3:
					{
						if(gObjRemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
						{
							RemovedCount++;
							i--;
						}
					}
					break;
				default:
					{
						break;
					}
					break;
				}
			}
		}
		break;
	case AT_PCBANG_GENERAL://PcBang General
		{
			for(i = 0; i < MAX_STATE_COUNT; i++)
			{
				switch(lpObj->m_BuffEffectState[i].btBuffIndex)
				{
				case AT_PCBANG_SEAL_OF_ASCENSION:
				case AT_PCBANG_SEAL_OF_WEALTH:
				case AT_PCBANG_SEAL_OF_SUSTENANCE:
				case AT_PCBANG_SEAL_OF_BALANCE: //season 4.5 add-on
					{
						if(gObjRemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
						{
							RemovedCount++;
							i--;
						}
					}
					break;
				default:
					{
						break;
					}
					break;
				}
			}
		}
		break;
	case AT_GENERAL_NOPERIOD_ITEM: //CashShop + PcBang General
		{
			for(i = 0; i < MAX_STATE_COUNT; i++)
			{
				switch(lpObj->m_BuffEffectState[i].btBuffIndex)
				{
				case AT_PCBANG_SEAL_OF_ASCENSION:
				case AT_PCBANG_SEAL_OF_WEALTH:
				case AT_PCBANG_SEAL_OF_SUSTENANCE:

				case AT_CSHOP_SEAL_OF_ASCENSION:
				case AT_CSHOP_SEAL_OF_WEALTH:
				case AT_CSHOP_SEAL_OF_SUSTENANCE:
				case AT_CSHOP_SEAL_OF_MOBILITY:

				case AT_CSHOP_SCROLL_OF_QUICKNESS:
				case AT_CSHOP_SCROLL_OF_DEFENSE:
				case AT_CSHOP_SCROLL_OF_WRATH:
				case AT_CSHOP_SCROLL_OF_WIZARDRY:
				case AT_CSHOP_SCROLL_OF_HEALTH:
				case AT_CSHOP_SCROLL_OF_MANA:

				case AT_CSHOP_LEAP_OF_STRENGTH:
				case AT_CSHOP_LEAP_OF_QUICKNESS:
				case AT_CSHOP_LEAP_OF_HEALTH:
				case AT_CSHOP_LEAP_OF_ENERGY:
				case AT_CSHOP_LEAP_OF_CONTROL:

				case AT_CSHOP_SEAL_OF_HEALING:
				case AT_CSHOP_SEAL_OF_DIVINITY:

				case AT_CSHOP_SCROLL_OF_BATTLE:
				case AT_CSHOP_SCROLL_OF_STRENGTHENER:

					//Season 4.5 add-on
				case AT_CSHOP_GUARDIAN_AMULET:
				case AT_CSHOP_PROTECT_AMULET:
				case AT_CSHOP_MASTER_SEAL_OF_ASCENSION:
				case AT_CSHOP_MASTER_SEAL_OF_WEALTH:
				case AT_PCBANG_SEAL_OF_BALANCE:
					break;
				default:
					{
						if(gObjRemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
						{
							RemovedCount++;
							i--;
						}
					}
					break;
				}
			}
		}
		break;
	case AT_GENERAL: //All??
		{
			for(i = 0; i < MAX_STATE_COUNT; i++)
			{
				if(gObjRemoveBuffEffect(lpObj, lpObj->m_BuffEffectState[i].btBuffIndex) == TRUE)
				{
					RemovedCount++;
					i--;
				}
			}
			lpObj->m_btViewStateCount = 0;
		}
		break;
	default: //Other
		{
			RemovedCount = g_BuffManager.SearchAndClearEffect(lpObj, iEffectClearType);
		}
		break;
	}

	if(lpObj->m_btViewStateCount < 0 || lpObj->m_btViewStateCount > MAX_STATE_COUNT)
	{
		lpObj->m_btViewStateCount = 0;
	}

	gObjNotifyUserViewportBuffEffect(lpObj);
	return 1;
}

//Identical
BYTE gObjSearchActiveEffect(LPOBJ lpObj, int iEffectIndex)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->m_Index < 0 || lpObj->m_Index > OBJMAX)
	{
		return 0;
	}

	return g_BuffManager.SearchActiveEffect(lpObj, iEffectIndex);
}

//Identical
BYTE gObjUpdateSpecificBuffEffectDuration(LPOBJ lpObj, int iEffectIndex, int iDuration)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	DWORD dwTick = GetTickCount(); //loc1

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(i > lpObj->m_btViewStateCount)
		{
			return 0;
		}

		if(lpObj->m_BuffEffectState[i].btBuffIndex == iEffectIndex)
		{
			lpObj->m_BuffEffectState[i].iDuration += iDuration;

			if(lpObj->m_BuffEffectState[i].iDuration < 0)
			{
				gObjRemoveBuffEffect(lpObj, iEffectIndex);
			}
			return 1;
		}
	}
	return 0;
}

//Identical -> 0 Calls
void gObjApplyBuffEffectDamageType(LPOBJ lpObj)
{
	int loc1 = 0; //??

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex != NULL)
		{
			g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType1, lpObj->m_BuffEffectState[i].iValue1);
			g_ViewportSkillState.SetDamageType(lpObj, lpObj->m_BuffEffectState[i].btEffectType2, lpObj->m_BuffEffectState[i].iValue2);
		}
	}
}

//Identical
int gObjCountAppliedBuffEffect(LPOBJ lpObj, BYTE * btEffectIndex)
{
	if(lpObj == NULL)
	{
		return -1;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return -1;
	}

	int count = 0; //loc1 ebp-4

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(count >= MAX_STATE_COUNT || count >= lpObj->m_btViewStateCount)
		{
			break;
		}

		if(lpObj->m_BuffEffectState[i].btBuffIndex == NULL)
		{
			continue;
		}

		switch(lpObj->m_BuffEffectState[i].btBuffIndex)
		{
		case 0: //NULL
			break;
		default:
			btEffectIndex[count] = lpObj->m_BuffEffectState[i].btBuffIndex;
			count++;
			break;
		}		
	}

	return count;
}

//Identical
BYTE gObjCheckBuffEffectValue(LPOBJ lpObj, int iEffectIndex, int iValue1, int iValue2)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex == iEffectIndex)
		{
			if(lpObj->m_BuffEffectState[i].iValue1 > iValue1)
			{
				return 1;
			}

			if(lpObj->m_BuffEffectState[i].iValue2 > iValue2)
			{
				return 1;
			}			
		}
	}

	return 0;
}

//Identical
int gObjGetActiveEffect(LPOBJ lpObj, int iEffectType)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	int iIndex = 0;

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex == NULL)
		{
			continue;
		}

		if(lpObj->m_BuffEffectState[i].btEffectType1 == iEffectType)
		{
			iIndex += lpObj->m_BuffEffectState[i].iValue1;
		}

		if(lpObj->m_BuffEffectState[i].btEffectType2 == iEffectType)
		{
			iIndex += lpObj->m_BuffEffectState[i].iValue2;
		}
	}

	return iIndex;
}

//Identical
BYTE gObjUpdateAppliedBuffEffect(LPOBJ lpObj, int iEffectIndex, int *iValue1, int *iValue2)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return 0;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex == iEffectIndex)
		{
			*iValue1 = lpObj->m_BuffEffectState[i].iValue1;

			if(iValue2 != 0)
			{
				*iValue2 = lpObj->m_BuffEffectState[i].iValue2;
			}

			return 1;
		}
	}

	return 0;
}

//Identical -> 7 Calls
void GCUseBuffEffect(LPOBJ lpObj, BYTE btEffectIndex, BYTE btEffectUseOption, WORD wOptionType, WORD wEffectType, int iLeftTime)
{
	PMSG_SEND_BUFF_ICON pMsg;

	PHeadSetB((LPBYTE)&pMsg, 0x2D, sizeof(PMSG_SEND_BUFF_ICON));

	pMsg.btEffectIndex = btEffectIndex;
	pMsg.byEffectOption = btEffectUseOption;
	pMsg.wOptionType = wOptionType;
	pMsg.wEffectType = wEffectType;
	pMsg.iLeftTime = iLeftTime;

	if ( lpObj->Type == OBJ_USER )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}

	if(btEffectUseOption == 0)
	{
		GCStateInfoSend(lpObj, 1, btEffectIndex);
	}
	else
	{
		GCStateInfoSend(lpObj, 0, btEffectIndex);
	}
}

//Identical -> 1 Calls
void gObjNotifyUserViewportBuffEffect(LPOBJ lpObj)
{
	if(lpObj == NULL)
	{
		return;
	}

	if(lpObj->Type != OBJ_USER)
	{
		return;
	}

	if(lpObj->m_btViewStateCount <= 0)
	{
		return;
	}

	for(int i = 0; i < MAX_STATE_COUNT; i++)
	{
		if(lpObj->m_BuffEffectState[i].btBuffIndex != NULL)
		{
			GCStateInfoSend(lpObj, 1, lpObj->m_BuffEffectState[i].btBuffIndex);
		}
	}
}

//00640890
BOOL gObjGiveRewardBuff(LPOBJ lpObj, int dis, int * count, int EffectIndex, BYTE btEffectType1, int iValue1, BYTE btEffectType2, int iValue2, int iDuration)
{
	if(lpObj == NULL)
	{
		return FALSE;
	}

	for(int iIndex = OBJ_STARTUSERINDEX; iIndex < OBJMAX; iIndex++)
	{
		LPOBJ lpTargetObj = &gObj[iIndex];

		if(lpTargetObj->Type == OBJ_USER && gObjIsConnected(iIndex) != FALSE)
		{
			if(lpTargetObj->MapNumber == lpObj->MapNumber)
			{
				if(gObjCalDistance(lpObj, lpTargetObj) < dis)
				{
					gObjApplyBuffEffectDuration(lpTargetObj, EffectIndex, btEffectType1, iValue1, btEffectType2, iValue2, iDuration);
					*count+= 1;
				}
			}
		}
	}
	return TRUE;
}


//Identical
void gObjSealUserSetExp(LPOBJ lpObj, __int64 & Experience, BOOL bDisableExtraGainExp) //006409A0
{
	__int64 iCAL_EXP = Experience; //loc2

	if( gObjSearchActiveEffect(lpObj, AT_CSHOP_SEAL_OF_SUSTENANCE) != FALSE || //Seal of Sustenance
		gObjSearchActiveEffect(lpObj, AT_PCBANG_SEAL_OF_SUSTENANCE) != FALSE) 
	{
		iCAL_EXP = 0;
	}
	else if( gObjSearchActiveEffect(lpObj, AT_CSHOP_SEAL_OF_ASCENSION) != FALSE || 
		     gObjSearchActiveEffect(lpObj, AT_CSHOP_SEAL_OF_WEALTH) != FALSE ||
			 
			 //Season 4.5 fix
			 gObjSearchActiveEffect(lpObj, AT_PCBANG_SEAL_OF_ASCENSION) != FALSE ||
			 gObjSearchActiveEffect(lpObj, AT_PCBANG_SEAL_OF_WEALTH) != FALSE ||
			
			 gObjSearchActiveEffect(lpObj, AT_CSHOP_SEAL_OF_HEALING) != FALSE ||

			 //Season 4.5 update
			 gObjSearchActiveEffect(lpObj, AT_CSHOP_MASTER_SEAL_OF_ASCENSION) != FALSE ||
			 gObjSearchActiveEffect(lpObj, AT_CSHOP_MASTER_SEAL_OF_WEALTH) != FALSE ) //Seal of Ascension & Seal of Wealth & Seal of Healing
	{
		int iGAIN_EXP = 0; //Set Gain Exp Disable (Dangerous should be 100 = Default)

		iGAIN_EXP = gObjGetActiveEffect(lpObj, ADD_OPTION_EXPERIENCE); //#define ADD_OPTION_EXPERIENCE	6

		iCAL_EXP = iCAL_EXP * iGAIN_EXP / 100;
	}

	Experience = iCAL_EXP; //Apply the new Experience
}