#include "StdAfx.h"
#include "ConMember.h"

CConMember ConMember;

CConMember::CConMember()
{
	return;
}

CConMember::~CConMember()
{
	return;
}


void CConMember::Init()
{
	this->m_szAccount.clear();
}

BOOL CConMember::IsMember(char * AccountID )
{
	if ( (AccountID == NULL ) || ( strcmp(AccountID, "") == 0 ) )
	{
		return FALSE;
	}

	std::map<std::string, int>::iterator it = this->m_szAccount.find( (std::string) AccountID );
	
	if ( it != this->m_szAccount.end() )
	{
		return TRUE;
	}

	return FALSE;
}

void CConMember::Load(char* filename)
{
	int count=0;
	int Token;

	this->Init();

	SMDFile = fopen( filename, "r");

	if ( SMDFile == 0 )
	{
		MsgBox( lMsg.Get( MSGGET( 0, 112 ) ), filename );
		return;
	}

	int n = 0;

	while ( true ) 
	{
		Token = GetToken();

		if ( Token == 2 )
		{
			break;
		}
		else
		{
			if ( Token == 0 )
			{
				this->m_szAccount.insert( std::pair<std::string, int>( (std::string)TokenString, 0 ) );
			}
		}
	}

	fclose( SMDFile );
}