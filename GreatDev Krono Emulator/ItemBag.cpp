#include "StdAfx.h"
#include "ItemBag.h"

CItemBag::CItemBag()
{
	return;
}

CItemBag::~CItemBag()
{
	return;
}

void CItemBag::Init(char* name)
{
	this->BagObjectCount = 0;
	this->BagNormalItemCount = 0;
	this->BagExItemCount = 0;

	this->LoadItem( gDirPath.GetNewPath(name));
}

void CItemBag::LoadItem(char* script_file)
{
	SMDFile = fopen(script_file, "r");

	if ( SMDFile == NULL )
	{
		LogAdd(lMsg.Get(MSGGET(1, 197)), script_file);
		return ;
	}

	int Token;
	int n = 0;

	while ( true )
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}

		if ( Token == 1 )
		{
			n = this->BagObjectCount;

			this->BagObject[n].m_type = TokenNumber;

			Token = GetToken();
			this->BagObject[n].m_index = TokenNumber;

			Token = GetToken();
			this->BagObject[n].m_level = TokenNumber;

			Token = GetToken();
			this->BagObject[n].m_op1 = TokenNumber;

			Token = GetToken();
			this->BagObject[n].m_op2 = TokenNumber;

			Token = GetToken();
			this->BagObject[n].m_op3 = TokenNumber;

			if ( this->BagObject[n].m_op2 != 0 )
			{
				this->BagExItemCount++;
			}
			else
			{
				this->BagNormalItemCount++;
			}

			this->BagObjectCount++;

			if ( this->BagObjectCount > MAX_ITEMBAG_ATTR-1 )
			{
				break;
			}
		}
	}

	fclose(SMDFile);

	LogAdd(lMsg.Get(MSGGET(1, 198)), script_file);
}


BYTE CItemBag::GetType(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_type;
}

BYTE CItemBag::GetIndex(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_index;
}


BYTE CItemBag::GetLevel(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_level;
}


BYTE CItemBag::GetOp1(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op1;
}


BYTE CItemBag::GetOp2(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op2;
}


BYTE CItemBag::GetOp3(int n)
{
	if ( n< 0 || n > MAX_ITEMBAG_ATTR-1 )
	{
		return 0;
	}

	return this->BagObject[n].m_op3;
}