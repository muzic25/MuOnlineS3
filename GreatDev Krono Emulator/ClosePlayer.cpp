#include "StdAfx.h"
#include "ClosePlayer.h"

Ccloseplayer::Ccloseplayer()
{
	return;	
}

Ccloseplayer::~Ccloseplayer()
{
	return;
}

void Ccloseplayer::Load(char* filename)
{
	int Token; 
	int aIndex;
	char closeplayerid[50];
	SMDFile=fopen(filename, "r");

	if (SMDFile == 0)
	{
		LogAdd(lMsg.Get(MSGGET(1, 213)), filename);
	}
	else
	{
		aIndex=0;
		while ( true )
		{
			Token=GetToken();
			if (Token == 2)
			{
				break;
			}
			memset(closeplayerid, 0, sizeof(closeplayerid) );
			strcpy(&closeplayerid[0], TokenString);

			if ( strlen(closeplayerid) > 0 )
			{
				aIndex=gObjGetIndex(closeplayerid);	
				if ( aIndex >= 0 )
				{
					LogAdd(lMsg.Get(MSGGET(1, 191)), closeplayerid);
					CloseClient(aIndex);
				}
			}
		}
		fclose(SMDFile);
	}
}


