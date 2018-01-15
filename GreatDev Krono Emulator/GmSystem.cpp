#include "StdAfx.h"

CGMSystem::CGMSystem()
{
	ZeroMemory(this->m_Data, sizeof(this->m_Data));
}

CGMSystem::~CGMSystem()
{
}

CGMSystem GMSystem;

void CGMSystem::LoadIniConfig(char * filename)
{
	IsGMSystem = GetPrivateProfileInt("GMSystem", "IsGMSystem", 1, filename);
	this->Load(filename);
}

void CGMSystem::Load(char * filename)
{
	SMDToken Token;
	SMDFile = fopen(filename, "r");
	// ---
	this->iDataCount = 0;
	// ---
	if (!SMDFile)
	{
		MsgBox("[%s] file not found", filename);
		ExitProcess(0);
	}
	// ---
	while (true)
	{
		Token = GetToken();
		// ---
		if (Token == SMDToken::END)
		{
			break;
		}
		// ---
		if (Token == SMDToken::NUMBER)
		{
			int Section = TokenNumber;
			// ---
			if (Section == 0)
			{
				while (true)
				{
					Token = GetToken();
					// ---
					if (Token == SMDToken::NAME)
					{
						if (strcmp("end", TokenString) == 0)
						{
							break;
						}
					}
					// ---
					memcpy(this->m_Data[this->iDataCount].szName, TokenString, MAX_ACCOUNT_LEN);
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_DROP] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_GG] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_SETZEN] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_STATS] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_MOVE] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_SETPK] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_PKCLEAR] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_BANPLAYER] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_RELOAD] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_SKIN] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_BANCHAT] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_UNBANCHAT] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_DISK] = TokenNumber;
					// ---
					GetToken();
					this->m_Data[this->iDataCount].iCommand[COMMAND_TRACE] = TokenNumber;
					// ---
					this->iDataCount++;
				}
			}
		}
	}
	// ---
	LogAdd("[%s] Uploaded Successfully", filename);
	// ---
	fclose(SMDFile);
}

bool CGMSystem::IsCommand(LPOBJ lpObj, int Command)
{
	if (lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		for (int i = 0; i < this->iDataCount; i++)
		{
			if (!strcmp(this->m_Data[i].szName, lpObj->Name))
			{
				switch (Command)
				{
				case 0:
					return this->m_Data[i].iCommand[COMMAND_DROP];
				case 1:
					return this->m_Data[i].iCommand[COMMAND_GG];
				case 2:
					return this->m_Data[i].iCommand[COMMAND_SETZEN];
				case 3:
					return this->m_Data[i].iCommand[COMMAND_STATS];
				case 4:
					return this->m_Data[i].iCommand[COMMAND_MOVE];
				case 5:
					return this->m_Data[i].iCommand[COMMAND_SETPK];
				case 6:
					return this->m_Data[i].iCommand[COMMAND_PKCLEAR];
				case 7:
					return this->m_Data[i].iCommand[COMMAND_BANPLAYER];
				case 8:
					return this->m_Data[i].iCommand[COMMAND_RELOAD];
				case 9:
					return this->m_Data[i].iCommand[COMMAND_SKIN];
				case 10:
					return this->m_Data[i].iCommand[COMMAND_BANCHAT];
				case 11:
					return this->m_Data[i].iCommand[COMMAND_UNBANCHAT];
				case 12:
					return this->m_Data[i].iCommand[COMMAND_DISK];
				case 13:
					return this->m_Data[i].iCommand[COMMAND_TRACE];
				}
			}
		}
	}
	// ---
	return false;
}