// ProbabilityItemBag.cpp: implementation of the CProbabilityItemBag class.
//	GS-N	1.00.90	JPN	0xXXXXXXXX			- Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProbabilityItemBag.h"
#include "SetItemOption.h"
#include "gObjMonster.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "readscript.h"
#include "winutil.h"
#include "logproc.h"

CProbabilityItemBag::CProbabilityItemBag()
{
	return;
}

CProbabilityItemBag::~CProbabilityItemBag()
{
	return;
}

void CProbabilityItemBag::Init(char* name)
{
	this->m_bLoad = FALSE;
	this->m_sEventName[0] = 0;
	this->m_iEventItemType = -1;
	this->m_iEventItemLevel = 0;
	this->m_iDropZen = 0;
	this->m_iEventItemDropRate = 0;
	this->m_iItemDropRate = 0;
	this->m_iExItemDropRate = 0;
	this->m_iBagObjectCount = 0;
	this->m_iRateKindCount = 0;

	this->LoadItem(gDirPath.GetNewPath(name));
}

void CProbabilityItemBag::LoadItem(char* script_file)
{
	int Token;

	this->m_bLoad = FALSE;
	SMDFile = fopen(script_file, "r");

	if ( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 197)), script_file);
		return;
	}

	int n=0;
	int	iProbability=0;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			int st = TokenNumber;	// script_type

			if ( st == 0 )
			{
				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					int map = TokenNumber;

					if ( MAX_MAP_RANGE(map) == FALSE )
					{
						MsgBox("ExEvent ItemBag LoadFail [%s]", script_file);
						return;
					}

					Token = GetToken();
					this->DropMapInfo[map].m_bIsDrop = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MinMonsterLevel = TokenNumber;

					Token = GetToken();
					this->DropMapInfo[map].m_MaxMonsterLevel = TokenNumber;
				}
			
			}
			else if ( st == 1 )
			{
				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					strcpy(this->m_sEventName, TokenString);

					Token = GetToken();
					this->m_iDropZen = TokenNumber;

					Token = GetToken();
					int type = TokenNumber;

					Token = GetToken();
					int index = TokenNumber;

					this->m_iEventItemType = ITEMGET(type, index);

					Token = GetToken();
					this->m_iEventItemLevel = TokenNumber;

					Token = GetToken();
					this->m_iEventItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iItemDropRate = TokenNumber;

					Token = GetToken();
					this->m_iExItemDropRate = TokenNumber;

					char szTemp[256];

					wsprintf(szTemp, "[%s] Eventitemnum = %d,EventItemLevel = %d, EventItemDropRate = %d, ItemDropRate = %d, ExItemDropRate = %d", this->m_sEventName, this->m_iEventItemType, this->m_iEventItemLevel, this->m_iEventItemDropRate, this->m_iItemDropRate, this->m_iExItemDropRate);
					LogAddTD(szTemp);
				}
			}
			else if ( st == 2 )
			{
				iProbability = 0; //ebp-10

				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					if( iProbability == 0) //good
					{
						this->m_iEventItemDropRateEx[iProbability] = (int)TokenNumber; //good
					}
					else
					{
						this->m_iEventItemDropRateEx[iProbability] = this->m_iEventItemDropRateEx[iProbability-1] + (int)TokenNumber; //great
					}

					n = 0;

					while ( true )
					{
						Token = GetToken();

						if ( Token == 0 )
						{
							if ( strcmp("end", TokenString) == 0 )
							{
								this->m_iDropRatePerItemCount[iProbability] = n;
								break;
							}
						}

						this->BagObject[this->m_iBagObjectCount].m_type = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_index = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_minLevel = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_maxLevel = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_isskill = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_isluck = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_isoption = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_isexitem = TokenNumber;

						if(this->BagObject[this->m_iBagObjectCount].m_minLevel > this->BagObject[this->m_iBagObjectCount].m_maxLevel)
						{
							MsgBox("Load Script Error %s", script_file);
							return;
						}
						
						n++;
						this->m_iBagObjectCount++;

						if ( this->m_iBagObjectCount > MAX_ITEMBAG_ATTR-1 )
						{
							break;
						}
					}

					iProbability++;

					if(iProbability > 19)
					{
						break;
					}
					continue;
				}
				this->m_iRateKindCount = iProbability;
			}
			else if ( st == 3 )
			{
				iProbability = this->m_iRateKindCount;

				while ( true )
				{
					Token = GetToken();

					if ( Token == 0 )
					{
						if ( strcmp("end", TokenString) == 0 )
						{
							break;
						}
					}

					if( iProbability == 0) //good
					{
						this->m_iEventItemDropRateEx[iProbability] = (int)TokenNumber; //good
					}
					else
					{
						this->m_iEventItemDropRateEx[iProbability] = this->m_iEventItemDropRateEx[iProbability-1] + (int)TokenNumber; //great
					}

					n = 0;

					while ( true )
					{
						Token = GetToken();

						if ( Token == 0 )
						{
							if ( strcmp("end", TokenString) == 0 )
							{
								this->m_iDropRatePerItemCount[iProbability] = n;
								break;
							}
						}

						this->BagObject[this->m_iBagObjectCount].m_type = TokenNumber;

						Token = GetToken();
						this->BagObject[this->m_iBagObjectCount].m_index = TokenNumber;

						this->BagObject[this->m_iBagObjectCount].m_issetitem = 1; //season 3.5 add-on
						this->BagObject[this->m_iBagObjectCount].m_minLevel = 0;
						this->BagObject[this->m_iBagObjectCount].m_maxLevel = 0;
						this->BagObject[this->m_iBagObjectCount].m_isskill = 0;
						this->BagObject[this->m_iBagObjectCount].m_isluck = 0;
						this->BagObject[this->m_iBagObjectCount].m_isoption = 0;
						this->BagObject[this->m_iBagObjectCount].m_isexitem = 0;

						if(this->BagObject[this->m_iBagObjectCount].m_minLevel > this->BagObject[this->m_iBagObjectCount].m_maxLevel)
						{
							MsgBox("Load Script Error %s", script_file);
							return;
						}
						
						n++;
						this->m_iBagObjectCount++;

						if ( this->m_iBagObjectCount > MAX_ITEMBAG_ATTR-1 )
						{
							break;
						}
					}

					iProbability++;

					if(iProbability > 19)
					{
						break;
					}
					continue;
				}
				this->m_iRateKindCount = iProbability;
			}
		}
	}

	fclose(SMDFile);
	LogAdd(lMsg.Get(MSGGET(1, 198)), script_file);
	this->m_bLoad = TRUE;
}

BYTE CProbabilityItemBag::GetLevel(int n)
{
	if ( n <0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	if ( this->BagObject[n].m_minLevel == this->BagObject[n].m_maxLevel )
	{
		return this->BagObject[n].m_minLevel;
	}

	int sub = (this->BagObject[n].m_maxLevel - this->BagObject[n].m_minLevel) + 1;
	int level = this->BagObject[n].m_minLevel + (rand()%sub);

	return level;
}


BOOL CProbabilityItemBag::IsEnableEventItemDrop(int aIndex)
{
	int iMapNumber = gObj[aIndex].MapNumber;

	if ( this->DropMapInfo[iMapNumber].m_bIsDrop == FALSE )
	{
		return FALSE;
	}

	int iLevel = gObj[aIndex].Level;

	if  ( iLevel < this->DropMapInfo[iMapNumber].m_MinMonsterLevel || iLevel > this->DropMapInfo[iMapNumber].m_MaxMonsterLevel)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CProbabilityItemBag::SortItem(int n)
{
	int loc2 = this->m_iRateKindCount;

	int loc3 = 0;

	int loc4 = this->GetBagCount()-1;

	while(loc2-- != 0)
	{
		if(loc2 == 0)
		{
			loc3 = rand()%this->m_iDropRatePerItemCount[0];
			break;
		}

		if(n >= 10000 - this->m_iEventItemDropRateEx[loc2] && n < 10000 - this->m_iEventItemDropRateEx[loc2-1])
		{
			loc3 = loc4 - rand()%this->m_iDropRatePerItemCount[loc2];
			break;
		}
		loc4 = loc4 - this->m_iDropRatePerItemCount[loc2];
	}

	return loc3;
}

char * CProbabilityItemBag::GetEventName()
{
	return m_sEventName;
}

BOOL CProbabilityItemBag::DropNewYearLuckMonsterReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if ( this->m_bLoad == FALSE )
		return FALSE;

	float dur = 0;
	int type = 0; 
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if ( this->GetBagCount() > 0 )
	{
		loc14 = rand()%10000;
		if ( this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount-1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[ NewYearLuckyBagMonsterEvent ] NewYearLuckyBagDrop [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name,this->m_iDropZen);
			return 1;
		}
			
		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if ( cX == 0 && cY == 0 )
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if ( type == -1 )
		{
			return FALSE;
		}

		if ( this->BagObject[loc16].m_isskill != 0 )
		{
			Option1 =1;
		}

		if ( this->BagObject[loc16].m_isluck != 0 )
		{
			Option2 = 0;

			if ( (rand()%2) == 0 )
			{
				Option2 = 1;
			}
		}

		if ( this->BagObject[loc16].m_isoption != 0 )
		{
			if ( rand()%5 < 1 )
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand()%3;
			}
		}

		if ( this->BagObject[loc16].m_isexitem != 0 )
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14))	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[ NewYearLuckyBagMonsterEvent ] NewYearLuckyBagDrop [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
				lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}

BOOL CProbabilityItemBag::DropGMPresentBoxReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if ( this->m_bLoad == FALSE )
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if ( this->GetBagCount() > 0 )
	{
		loc14 = rand()%10000;
		if ( this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount-1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, lpObj->X, lpObj->Y);
			LogAddTD("[ GMPresentBox ] GMPresentBoxItemDrop [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name,this->m_iDropZen);
			return 1;
		}
			
		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if ( cX == 0 && cY == 0 )
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if ( type == -1 )
		{
			return FALSE;
		}

		if ( this->BagObject[loc16].m_isskill != 0 )
		{
			Option1 =1;
		}

		if ( this->BagObject[loc16].m_isluck != 0 )
		{
			Option2 = 0;

			if ( (rand()%2) == 0 )
			{
				Option2 = 1;
			}
		}

		if ( this->BagObject[loc16].m_isoption != 0 )
		{
			if ( rand()%5 < 1 )
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand()%3;
			}
		}

		if ( this->BagObject[loc16].m_isexitem != 0 )
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14))	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		if ( type == ITEMGET(13,20) )
		{
			level = 0;
			dur = 255;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[ GMPresentBox ] GMPresentBoxItemDrop [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
				lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}

BOOL CProbabilityItemBag::DropPCBangGreenChaosBoxReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY) //004B12C0
{
	if (this->m_bLoad == FALSE)
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if (this->GetBagCount() > 0)
	{
		loc14 = rand() % 10000;
		if (this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount - 1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[PCBangPointSystem] DropBoxOfGreenChaosItem [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name, this->m_iDropZen);
			return 1;
		}

		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if (cX == 0 && cY == 0)
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if (type == -1)
		{
			return FALSE;
		}

		if (this->BagObject[loc16].m_isskill != 0)
		{
			Option1 = 1;
		}

		if (this->BagObject[loc16].m_isluck != 0)
		{
			Option2 = 0;

			if ((rand() % 2) == 0)
			{
				Option2 = 1;
			}
		}

		if (this->BagObject[loc16].m_isoption != 0)
		{
			if (rand() % 5 < 1)
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand() % 3;
			}
		}

		if (this->BagObject[loc16].m_isexitem != 0)
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if (type == ITEMGET(12, 15) || type == ITEMGET(14, 13) || type == ITEMGET(14, 14))	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[PCBangPointSystem] DropBoxOfGreenChaosItem [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
			lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}

BOOL CProbabilityItemBag::DropPCBangRedChaosBoxReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if (this->m_bLoad == FALSE)
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if (this->GetBagCount() > 0)
	{
		loc14 = rand() % 10000;
		if (this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount - 1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[PCBangPointSystem] DropBoxOfRedChaosItem [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name, this->m_iDropZen);
			return 1;
		}

		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if (cX == 0 && cY == 0)
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if (type == -1)
		{
			return FALSE;
		}

		if (this->BagObject[loc16].m_isskill != 0)
		{
			Option1 = 1;
		}

		if (this->BagObject[loc16].m_isluck != 0)
		{
			Option2 = 0;

			if ((rand() % 2) == 0)
			{
				Option2 = 1;
			}
		}

		if (this->BagObject[loc16].m_isoption != 0)
		{
			if (rand() % 5 < 1)
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand() % 3;
			}
		}

		if (this->BagObject[loc16].m_isexitem != 0)
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if (type == ITEMGET(12, 15) || type == ITEMGET(14, 13) || type == ITEMGET(14, 14))	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[PCBangPointSystem] DropBoxOfRedChaosItem [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
			lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}

BOOL CProbabilityItemBag::DropPCBangPurpleChaosBoxReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if (this->m_bLoad == FALSE)
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if (this->GetBagCount() > 0)
	{
		loc14 = rand() % 10000;
		if (this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount - 1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[PCBangPointSystem] DropBoxOfPurpleChaosItem [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name, this->m_iDropZen);
			return 1;
		}

		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if (cX == 0 && cY == 0)
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if (type == -1)
		{
			return FALSE;
		}

		if (this->BagObject[loc16].m_isskill != 0)
		{
			Option1 = 1;
		}

		if (this->BagObject[loc16].m_isluck != 0)
		{
			Option2 = 0;

			if ((rand() % 2) == 0)
			{
				Option2 = 1;
			}
		}

		if (this->BagObject[loc16].m_isoption != 0)
		{
			if (rand() % 5 < 1)
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand() % 3;
			}
		}

		if (this->BagObject[loc16].m_isexitem != 0)
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if (type == ITEMGET(12, 15) || type == ITEMGET(14, 13) || type == ITEMGET(14, 14))	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[PCBangPointSystem] DropBoxOfPurpleChaosItem [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
			lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}


BOOL CProbabilityItemBag::DropIllusionTempleEventReward(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if ( this->m_bLoad == FALSE )
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if ( this->GetBagCount() > 0 )
	{
		loc14 = rand()%10000;
		if ( this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount-1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[ ILLUSIONTempleEvent ] ILLUSIONTempleEventDrop [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name,this->m_iDropZen);
			return 1;
		}
			
		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if ( cX == 0 && cY == 0 )
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if ( type == -1 )
		{
			return FALSE;
		}

		if ( this->BagObject[loc16].m_isskill != 0 )
		{
			Option1 =1;
		}

		if ( this->BagObject[loc16].m_isluck != 0 )
		{
			Option2 = 0;

			if ( (rand()%2) == 0 )
			{
				Option2 = 1;
			}
		}

		if ( this->BagObject[loc16].m_isoption != 0 )
		{
			if ( rand()%5 < 1 )
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand()%3;
			}
		}

		if ( this->BagObject[loc16].m_isexitem != 0 )
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14) || type == ITEMGET(14,22) )	// Chaos, Bless, Soul, Creation
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[ ILLUSIONTempleEvent ] ILLUSIONTempleEventDrop [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
				lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}


BOOL CProbabilityItemBag::DropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY) //0048CA00
{	
	if ( this->m_bLoad == FALSE )
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if ( this->GetBagCount() > 0 )
	{
		loc14 = rand()%10000;
		if ( this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount-1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[%s] Drop Zen [%s][%s] [%d Zen]", this->GetEventName(), lpObj->AccountID, lpObj->Name,this->m_iDropZen);
			return 0;
		}
			
		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if ( cX == 0 && cY == 0 )
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if ( type == -1 )
		{
			return FALSE;
		}

		if ( this->BagObject[loc16].m_issetitem == 1 ) //season3 add-on
		{
			this->DropSetItem(aIndex, type, btMapNumber, x , y);
			return TRUE;
		}

		if ( this->BagObject[loc16].m_isskill != 0 )
		{
			Option1 =1;
		}

		if ( this->BagObject[loc16].m_isluck != 0 )
		{
			Option2 = 0;

			if ( (rand()%2) == 0 )
			{
				Option2 = 1;
			}
		}

		if ( this->BagObject[loc16].m_isoption != 0 )
		{
			if ( rand()%5 < 1 )
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand()%3;
			}
		}

		if ( this->BagObject[loc16].m_isexitem != 0 )
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14) || type == ITEMGET(14,22) )	// Chaos, Bless, Soul, Creation
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		if ( type == ITEMGET(13,0) ||
			 type == ITEMGET(13,1) ||
			 type == ITEMGET(13,2) ||
			 type == ITEMGET(13,8) ||
			 type == ITEMGET(13,9) ||
			 type == ITEMGET(13,12) ||
			 type ==ITEMGET(13,13) ||
			 type ==ITEMGET(13,38) ||
			 type ==ITEMGET(13,39) ||
			 type ==ITEMGET(13,40) ||
			 type ==ITEMGET(13,41) )
		{
			level = 0;
			dur = 255;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[%s] Drop Item [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
				this->GetEventName(), lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);

	}
	return 1;
}

void CProbabilityItemBag::DropSetItem(int aIndex, int itemnum, BYTE btMapNumber, int cX, int cY)
{
	int SetOption = gSetItemOption.GenSetOption(itemnum);

	int option1rand;
	int option2rand;
	int option3rand;
	int optionc;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;

	option1rand = 6;
	option2rand = 4;

	option3rand = rand()%100;
	optionc = rand()%3;

	if(rand()%100 < option2rand)
	{
		Option2 = 1;
	}

	switch(optionc)
	{
	case 0: 
		if(option3rand < 4)
		{
			Option3 = 3;
		}
		break;
	case 1:
		if(option3rand < 8)
		{
			Option3 = 2;
		}
		break;
	case 2: 
		if(option3rand < 12)
		{
			Option3 = 1;
		}
		break;
	default: break;
	}

	Option1 = 1;

	ItemSerialCreateSend(aIndex,btMapNumber,cX,cY,itemnum,0,0,Option1,Option2,Option3,aIndex,0,SetOption);

	int loc10 = 0;

	if((SetOption&0x01) != 0)
	{
		loc10 = 1;
	}
	else if((SetOption&0x02) != 0)
	{
		loc10 = 2;
	}

	LogAddTD("[%s] Drop Set Item [%s][%s] : (%d)(%d/%d) Itemnum:[%d] skill:[%d] luck:[%d] option:[%d] SetOption:[%d], SetName:[%s]",this->GetEventName(), gObj[aIndex].AccountID,gObj[aIndex].Name,
		btMapNumber, cX, cY, itemnum,Option1,Option2,Option3,SetOption, gSetItemOption.GetSetOptionName(itemnum, loc10));
}

int CProbabilityItemBag::DropItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY, int * iDropZen)
{	
	if ( this->m_bLoad == FALSE )
		return FALSE;

	float dur = 0;
	int type = 0;
	int level = 0;
	int x = 0;
	int y = 0;
	int Option1 = 0;
	int Option2 = 0;
	int Option3 = 0;
	int DropItemNum = 0;
	int ExOption = 0;
	int loc12 = 0;
	LPOBJ lpObj = &gObj[aIndex];
	int loc14;
	int loc15;
	int loc16;

	if ( this->GetBagCount() > 0 )
	{
		loc14 = rand()%10000;
		if ( this->m_iRateKindCount == 0 || loc14 < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount-1])
		{
			if(btMapNumber == 0xFF)
			{
				*iDropZen = this->m_iDropZen;
				return FALSE;
			}

			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[%s] Drop Zen [%s][%s] [%d Zen]", this->GetEventName(), lpObj->AccountID, lpObj->Name,this->m_iDropZen);
			return 1;
		}
			
		loc15 = this->m_iRateKindCount;
		loc16 = this->SortItem(loc14);

		if ( cX == 0 && cY == 0 )
		{
			x = lpObj->X;
			y = lpObj->Y;
		}
		else
		{
			x = cX;
			y = cY;
		}

		if(btMapNumber == 0xFF)
		{
			x = 0;
			y = 0;
		}

		level = this->GetLevel(loc16);
		type = ItemGetNumberMake(this->BagObject[loc16].m_type, this->BagObject[loc16].m_index);

		if ( type == -1 )
		{
			return FALSE;
		}

		if ( this->BagObject[loc16].m_issetitem == 1 ) //season3 add-on
		{
			this->DropSetItem(aIndex, type, btMapNumber, x , y);
			return TRUE;
		}

		if ( this->BagObject[loc16].m_isskill != 0 )
		{
			Option1 =1;
		}

		if ( this->BagObject[loc16].m_isluck != 0 )
		{
			Option2 = 0;

			if ( (rand()%2) == 0 )
			{
				Option2 = 1;
			}
		}

		if ( this->BagObject[loc16].m_isoption != 0 )
		{
			if ( rand()%5 < 1 )
			{
				Option3 = 3;
			}
			else
			{
				Option3 = rand()%3;
			}
		}

		if ( this->BagObject[loc16].m_isexitem != 0 )
		{
			loc12 = NewOptionRand(0);
			Option2 = 0;
			Option1 = 1;
			level = 0;
		}

		if ( type == ITEMGET(12,15) || type == ITEMGET(14,13) || type == ITEMGET(14,14) )	// Chaos, Bless, Soul
		{
			Option1 = 0;
			Option2 = 0;
			Option3 = 0;
			level = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index, btMapNumber, x, y, type, level, dur, Option1, Option2, Option3, lpObj->m_Index, loc12, 0);
		LogAddTD("[%s] Drop Item [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",	this->GetEventName(), lpObj->AccountID, lpObj->Name, btMapNumber, x, y, ItemAttribute[type].Name, type, level, Option1, Option2, Option3, loc12);
	}
	return 1;
}


BOOL CProbabilityItemBag::DropNewYearLuckyBagEventItem(int aIndex, BYTE btMapNumber, BYTE cX, BYTE cY)
{
	if (!this->m_bLoad)
	{
		return FALSE;
	}

	int iOption1 = 0;
	int iOption2 = 0;
	int iOption3 = 0;
	int iExOption = 0;
	int X = 0;
	int Y = 0;
	LPOBJ lpObj = &gObj[aIndex];

	if (this->GetBagCount() > 0)
	{
		int nDropItemRate = rand() % 10000;
		
		if (this->m_iRateKindCount == 0 || nDropItemRate < 10000 - this->m_iEventItemDropRateEx[this->m_iRateKindCount - 1])
		{
			MapC[lpObj->MapNumber].MoneyItemDrop(this->m_iDropZen, cX, cY);
			LogAddTD("[ NewYearLuckyBagMonsterEvent ] NewYearLuckyBagDrop [%s][%s] [%d Zen]", lpObj->AccountID, lpObj->Name, this->m_iDropZen);
			return TRUE;
		}

		int nRateCnt = this->m_iRateKindCount;
		int n = this->SortItem(nDropItemRate);

		if (cX == 0 && cY == 0)
		{
			X = lpObj->X;
			Y = lpObj->Y;
		}
		else
		{
			X = cX;
			Y = cY;
		}

		int iLevel = this->GetLevel( n);
		int iType = ItemGetNumberMake(this->BagObject[n].m_type, this->BagObject[n].m_index);
		if (iType == -1)
		{
			return 0;
		}
		if (this->BagObject[n].m_isskill)
		{
			iOption1 = 1;
		}
		if (this->BagObject[n].m_isluck)
		{
			iOption2 = 0;
			if (!(rand() % 2))
				iOption2 = 1;
		}
		if (this->BagObject[n].m_isoption)
		{
			if (rand() % 5 >= 1)
				iOption3 = rand() % 3;
			else
				iOption3 = 3;
		}
		if (this->BagObject[n].m_isexitem)
		{
			iExOption = NewOptionRand(0);
			iOption2 = 0;
			iOption1 = 1;
			iLevel = 0;
		}

		if (iType == ITEMGET(12, 15) || iType == ITEMGET(14, 13) || iType == ITEMGET(14, 14))	// Chaos, Bless, Soul
		{
			iOption1 = 0;
			iOption2 = 0;
			iOption3 = 0;
			iLevel = 0;
		}

		ItemSerialCreateSend(lpObj->m_Index,btMapNumber,X,Y,iType,iLevel,0.0,iOption1,iOption2,iOption3,lpObj->m_Index,iExOption,0);
		LogAddTD(
			"[ NewYearLuckyBagMonsterEvent ] NewYearLuckyBagDrop [%s][%s] : (%d)(%d/%d) Item:(%s)%d Level:%d op1:%d op2:%d op3:%d ExOp:%d",
			lpObj->AccountID,lpObj->Name,btMapNumber,X,Y,ItemAttribute[iType].Name,iType,iLevel,iOption1,iOption2,iOption3,iExOption);
	}
	return TRUE;
}