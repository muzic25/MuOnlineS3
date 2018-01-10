#include "StdAfx.h"
#include "ItemAddOption.h"

#define ADD_OPTION_SPEED	1
#define ADD_OPTION_ATTACK_DAMAGE	2
#define ADD_OPTION_DEFENSE	3
#define ADD_OPTION_LIFE	4
#define ADD_OPTION_MANA	5
#define ADD_OPTION_EXPERIENCE	6
#define ADD_OPTION_DROP_RATE	7

#define ADD_OPTION_STRENGTH	9
#define ADD_OPTION_DEXTERITY	10
#define ADD_OPTION_VITALITY	11
#define ADD_OPTION_ENERGY	12
#define ADD_OPTION_LEADERSHIP	13

CItemAddOption g_ItemAddOption;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemAddOption::CItemAddOption()
{
	this->Initialize();
}

CItemAddOption::~CItemAddOption()
{
	return;
}



void CItemAddOption::Load(PCHAR chFileName)
{
	SMDToken Token;

	this->Initialize();

	SMDFile = fopen(chFileName, "r");

	if ( SMDFile == NULL )
		return;

	int iItemAddOptionIndex = 0;

	while ( true )
	{
		Token = (SMDToken)GetToken();

		if ( Token == END )
			break;

		if ( Token == NUMBER )
		{
			int iType = TokenNumber;

			while ( true )
			{
				if ( iType == 0 )
				{
					Token = (SMDToken)GetToken();

					if ( strcmp("end", TokenString) == 0 )
						break;
				}

				if ( iType == 1 )
				{
					int iItemNumber = 0;
					int iItemType = 0;
					int iItemIndex = 0;
					int iItemOption1 = 0;
					int iItemValue1 = 0;
					int iItemOption2 = 0;
					int iItemValue2 = 0;
					int iItemValidTime = 0;

					Token = (SMDToken)GetToken();

					if ( !strcmp("end", TokenString))
						break;

					iItemType = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemIndex = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption1 = TokenNumber;					

					Token = (SMDToken)GetToken();
					iItemValue1 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption2 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValue2 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValidTime = TokenNumber;

					iItemNumber = ITEMGET(iItemType, iItemIndex);
					this->m_ItemAddOption[iItemAddOptionIndex].wOptionType = iType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemNumber = iItemNumber;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemType = iItemType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemIndex = iItemIndex;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType1 = iItemOption1;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue1 = iItemValue1;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType2 = iItemOption2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue2 = iItemValue2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValidTime = iItemValidTime;

					iItemAddOptionIndex++;

					if (iItemAddOptionIndex > MAX_ITEM_ADD_OPTION )
					{
						MsgBox("[ItemAddOption] Overflow ItemAddOption Table Index");
					}
				}
				else if ( iType == 2 )
				{
					int iItemNumber = 0;
					int iItemType = 0;
					int iItemIndex = 0;
					int iItemOption1 = 0;
					int iItemValue1 = 0;
					int iItemOption2 = 0;
					int iItemValue2 = 0;
					int iItemValidTime = 0;

					Token = (SMDToken)GetToken();

					if ( !strcmp("end", TokenString))
						break;

					iItemType = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemIndex = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption1 = TokenNumber;					

					Token = (SMDToken)GetToken();
					iItemValue1 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemOption2 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValue2 = TokenNumber;

					Token = (SMDToken)GetToken();
					iItemValidTime = TokenNumber;

					iItemNumber = ITEMGET(iItemType, iItemIndex);
					this->m_ItemAddOption[iItemAddOptionIndex].wOptionType = iType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemNumber = iItemNumber;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemType = iItemType;
					this->m_ItemAddOption[iItemAddOptionIndex].iItemIndex = iItemIndex;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType1 = iItemOption1;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue1 = iItemValue1;
					this->m_ItemAddOption[iItemAddOptionIndex].wEffectType2 = iItemOption2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValue2 = iItemValue2;
					this->m_ItemAddOption[iItemAddOptionIndex].iEffectValidTime = iItemValidTime;

					iItemAddOptionIndex++;

					if (iItemAddOptionIndex > MAX_ITEM_ADD_OPTION )
					{
						MsgBox("[ItemAddOption] Overflow ItemAddOption Table Index");
					}
				}
			}
		}
	}

	// #error need fclose here
}



void CItemAddOption::Initialize()
{
	for ( int i=0;i<MAX_ITEM_ADD_OPTION;i++)
	{
		this->m_ItemAddOption[i].iItemNumber = 0;
		this->m_ItemAddOption[i].iItemType = 0;
		this->m_ItemAddOption[i].iItemIndex = 0;
		this->m_ItemAddOption[i].wEffectType1 = 0;
		this->m_ItemAddOption[i].iEffectValue1 = 0;
		this->m_ItemAddOption[i].wEffectType2 = 0;
		this->m_ItemAddOption[i].iEffectValue2 = 0;
		this->m_ItemAddOption[i].iEffectValidTime = 0;
	}
}




bool CItemAddOption::PrevSetItemLastEffectForHallowin(LPOBJ lpObj)
{
	LPITEMEFFECT lpItemEffect = NULL;
	int iItemEffectType = lpObj->m_wItemEffectType;

	lpItemEffect = this->_SearchItemEffect(iItemEffectType);

	if ( lpItemEffect == NULL )
		return false;

	if ( lpItemEffect->wEffectType1 == ADD_OPTION_LIFE || lpItemEffect->wEffectType1 == ADD_OPTION_MANA )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	}

	return true;
}

bool CItemAddOption::NextSetItemLastEffectForHallowin(LPOBJ lpObj)
{
	LPITEMEFFECT lpItemEffect = NULL;
	int iItemEffectType = lpObj->m_wItemEffectType;

	lpItemEffect = this->_SearchItemEffect(iItemEffectType);

	if ( lpItemEffect == NULL )
		return false;

	if ( lpItemEffect->wEffectType1 != ADD_OPTION_LIFE && lpItemEffect->wEffectType1 != ADD_OPTION_MANA )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
	}

	return true;
}


void CItemAddOption::SendItemUse(LPOBJ lpObj, int iItemNumber, int iOptionType, int iEffectType, int iEffectValue, int iValidTime)
{
	if ( lpObj == NULL ) 
		return;
	
	if ( iItemNumber== 0 || iEffectType == 0 ) 
		return;

	GCUseEffectItem(lpObj, 0, iOptionType, iEffectType, iValidTime);
}


bool CItemAddOption::SetItemEffect(LPOBJ lpObj, int iItemNumber, int iItemUseTime)
{
	LPITEMEFFECT lpItemEffectBefore = NULL;
	LPITEMEFFECT lpItemEffect = NULL;

	if ( lpObj == NULL )
		return false;

	if ( lpObj->Type != OBJ_USER )
		return false;
	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if ( lpItemEffect ==NULL )
		return false;

	lpItemEffectBefore = this->GetCurrentEffectType(lpObj);

	if ( lpItemEffectBefore != NULL )
	{
		if ( lpItemEffectBefore->wOptionType == lpItemEffect->wOptionType )
		{
			this->ClearItemEffect(lpObj, 2);
		}
	}

	if ( iItemUseTime > 0 )
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType1,
			lpItemEffect->iEffectValue1, iItemUseTime * 60);

		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType2,
			lpItemEffect->iEffectValue2, iItemUseTime * 60);
	}
	else
	{
		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType1,
			lpItemEffect->iEffectValue1, lpItemEffect->iEffectValidTime);

		this->_SetItemEffect(lpObj, lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);
		this->SendItemUse(lpObj, iItemNumber, lpItemEffect->wOptionType, lpItemEffect->wEffectType2,
			lpItemEffect->iEffectValue2, lpItemEffect->iEffectValidTime);
	}

	if ( iItemUseTime > 0 )
	{
		lpObj->m_wItemEffectType = lpItemEffect->iItemNumber;
		lpObj->m_iItemEffectValidTime = iItemUseTime * 60;
	}
	else
	{
		lpObj->m_wItemEffectType = lpItemEffect->iItemNumber;
		lpObj->m_iItemEffectValidTime = lpItemEffect->iEffectValidTime;
	}
	return true;
}




bool CItemAddOption::_SetItemEffect(LPOBJ lpObj, int iEffectType, int iEffectValue)
{
	if ( iEffectType <= 0 )
		return false;

	switch ( iEffectType )
	{
		case ADD_OPTION_LIFE:
			lpObj->AddLife += iEffectValue;
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, -2, 0, lpObj->iMaxShield + lpObj->iAddShield);
			GCReFillSend(lpObj->m_Index, lpObj->Life, -1, 0, lpObj->iShield);
			break;

		case ADD_OPTION_MANA:
			lpObj->AddMana += iEffectValue;
			GCManaSend(lpObj->m_Index, lpObj->AddMana + lpObj->MaxMana, -2, 0, lpObj->MaxBP + lpObj->AddBP);
			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
			break;

		case ADD_OPTION_ATTACK_DAMAGE:
			lpObj->m_AttackDamageMaxLeft += iEffectValue;
			lpObj->m_AttackDamageMinLeft += iEffectValue;
			lpObj->m_AttackDamageMaxRight += iEffectValue;
			lpObj->m_AttackDamageMinRight += iEffectValue;
			lpObj->m_MagicDamageMin += iEffectValue;
			lpObj->m_MagicDamageMax += iEffectValue;
			break;

		case ADD_OPTION_SPEED:
			lpObj->m_AttackSpeed += iEffectValue;
			lpObj->m_MagicSpeed += iEffectValue;
			break;

		case ADD_OPTION_EXPERIENCE:
			lpObj->m_wExprienceRate = iEffectValue;
			lpObj->m_btMoveMapBound = 1;
			break;

		case ADD_OPTION_DROP_RATE:
			lpObj->m_wItemDropRate = iEffectValue;
			lpObj->m_btMoveMapBound = 1;
			break;

		case 8:
			lpObj->m_wExprienceRate = 0;
			lpObj->m_btMoveMapBound = 1;
			break;

		case ADD_OPTION_DEFENSE:
			lpObj->m_Defense += iEffectValue * 10 / 20;
			break;

		case ADD_OPTION_STRENGTH:
			lpObj->Strength += iEffectValue;
			break;

		case ADD_OPTION_DEXTERITY:
			lpObj->Dexterity += iEffectValue;
			break;

		case ADD_OPTION_VITALITY:
			lpObj->Vitality += iEffectValue;
			break;

		case ADD_OPTION_ENERGY:
			lpObj->Energy += iEffectValue;
			break;

		case ADD_OPTION_LEADERSHIP:
			lpObj->Leadership += iEffectValue;
			break;

		default:
			return false;
	}

	return true;
}




bool CItemAddOption::_ClearItemEffect(LPOBJ lpObj, int iEffectOption, int iOptionType, int iEffectType, int iEffectValue)
{
	if ( iEffectType <= 0 )
		return false;

	switch ( iEffectType )
	{
		case ADD_OPTION_LIFE:
			lpObj->AddLife -= iEffectValue;

			if ( (lpObj->AddLife + lpObj->MaxLife ) < lpObj->Life )
				lpObj->Life = lpObj->AddLife + lpObj->MaxLife;

			GCReFillSend(lpObj->m_Index, lpObj->Life, 0xFF, 0, lpObj->iShield);
			GCReFillSend(lpObj->m_Index, lpObj->MaxLife + lpObj->AddLife, 0xFE, 0, lpObj->iMaxShield + lpObj->iAddShield);
			break;

		case ADD_OPTION_MANA:
			lpObj->AddMana -= iEffectValue;

			if ( (lpObj->AddMana + lpObj->MaxMana ) < lpObj->Mana )
				lpObj->Mana = lpObj->AddMana + lpObj->MaxMana;


			GCManaSend(lpObj->m_Index, lpObj->Mana, -1, 0, lpObj->BP);
			GCManaSend(lpObj->m_Index, lpObj->AddMana + lpObj->MaxMana, 0xFE, 0, lpObj->MaxBP + lpObj->AddBP);
			break;

		case ADD_OPTION_ATTACK_DAMAGE:
			lpObj->m_AttackDamageMaxLeft -= iEffectValue;
			lpObj->m_AttackDamageMinLeft -= iEffectValue;
			lpObj->m_AttackDamageMaxRight -= iEffectValue;
			lpObj->m_AttackDamageMinRight -= iEffectValue;
			lpObj->m_MagicDamageMin -= iEffectValue;
			lpObj->m_MagicDamageMax -= iEffectValue;
			break;

		case ADD_OPTION_SPEED:
			lpObj->m_AttackSpeed -= iEffectValue;
			lpObj->m_MagicSpeed -= iEffectValue;
			break;

		case ADD_OPTION_EXPERIENCE:
			lpObj->m_wExprienceRate = 100;
			lpObj->m_btMoveMapBound = 0;
			break;

		case ADD_OPTION_DROP_RATE:
			lpObj->m_wItemDropRate = 100;
			lpObj->m_btMoveMapBound = 0;
			break;

		case 8:
			lpObj->m_wExprienceRate = 100;
			lpObj->m_btMoveMapBound = 0;
			break;

		case ADD_OPTION_DEFENSE:
			lpObj->m_Defense -= iEffectValue * 10 / 20;
			break;

		case ADD_OPTION_STRENGTH:
			lpObj->Strength -= iEffectValue;
			break;

		case ADD_OPTION_DEXTERITY:
			lpObj->Dexterity -= iEffectValue;
			break;

		case ADD_OPTION_VITALITY:
			lpObj->Vitality -= iEffectValue;
			break;

		case ADD_OPTION_ENERGY:
			lpObj->Energy -= iEffectValue;
			break;

		case ADD_OPTION_LEADERSHIP:
			lpObj->Leadership -= iEffectValue;
			break;

		default:
			return false;
	}

	GCUseEffectItem(lpObj, iEffectOption, iOptionType, iEffectType, 0);

	return true;
}



bool CItemAddOption::ClearItemEffect(LPOBJ lpObj, int iEffectOption)
{
	LPITEMEFFECT lpItemEffect = NULL;
	
	lpItemEffect = this->GetCurrentEffectType(lpObj);

	if ( lpItemEffect == NULL )
		return false;

	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType,
		lpItemEffect->wEffectType1, lpItemEffect->iEffectValue1);

	this->_ClearItemEffect(lpObj, iEffectOption, lpItemEffect->wOptionType,
		lpItemEffect->wEffectType2, lpItemEffect->iEffectValue2);

	lpObj->m_wItemEffectType = 0;
	lpObj->m_iItemEffectValidTime = 0;

	return true;
}


LPITEMEFFECT CItemAddOption::GetCurrentEffectType(LPOBJ lpObj)
{
	if ( lpObj->m_wItemEffectType <= 0 )
		return NULL;

	return this->_SearchItemEffect(lpObj->m_wItemEffectType);
}




LPITEMEFFECT CItemAddOption::_SearchItemEffect(int iItemNumber)
{
	for ( int i=0;i<MAX_ITEM_ADD_OPTION;i++)
	{
		if ( this->m_ItemAddOption[i].iItemNumber == iItemNumber )
			return &this->m_ItemAddOption[i];
	}

	return NULL;
}



bool CItemAddOption::SearchItemEffectType(int iItemNumber, int * iEffectType1, int * iEffectType2)
{
	LPITEMEFFECT lpItemEffect = NULL;

	lpItemEffect = this->_SearchItemEffect(iItemNumber);

	if ( lpItemEffect == NULL )
		return false;

	*iEffectType1 = lpItemEffect->wEffectType1;
	*iEffectType2 = lpItemEffect->wEffectType2;

	return true;
}

BYTE CItemAddOption::SearchForClearItemEffect(int iItemNumber)
{
	if (this->_SearchItemEffect(iItemNumber) == NULL)
	{
		return 0;
	}

	return 1;
}

LPITEMEFFECT CItemAddOption::SearchItemEffectType1(int iItemNumber)
{
	return this->_SearchItemEffect(iItemNumber);
}