// ================================================== //
// # GameServer 1.00.90 WzAG.dll					# //
// # RMST Storm & Tornado Projects 2010-2011		# //
// ================================================== //


#include "StdAfx.h"
#include "GmSystem.h"
#include "Logger.h"
cGmSystem GMS;

#define KRONO_GM_SYSTEM ".\\GMSystem.txt"

cGmSystem::cGmSystem()
{

}

cGmSystem::~cGmSystem()
{
}

void cGmSystem::LoadIniConfig()
{
	IsGMSystem = GetPrivateProfileInt("GMSystem","IsGMSystem",1,KRONO_GM_SYSTEM);
	IsGMInDB = GetPrivateProfileInt("GMSystem","IsGMInDB",1,KRONO_GM_SYSTEM);
}

void cGmSystem::LoadGMSystem()
{
	FILE *fp;
	BOOL bRead = FALSE;
	DWORD dwArgv = 0;
	char sLineTxt[256];
	GMCount = 0;
	BOOL bResult = FALSE;

	fp = fopen(KRONO_GM_SYSTEM,"r");

	rewind(fp);
	int CFG = -1;
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')continue;
		if(sLineTxt[0] == ';')continue;
		if(sLineTxt[0] == 'e' && sLineTxt[1] == 'n' && sLineTxt[2] == 'd')
		{
			CFG = -1;
			continue;
		}
		
		if(strlen(sLineTxt) < 3)
		{	 			
            UINT q = 0;
            sscanf(sLineTxt, "%d", &q);
			CFG = q;
			continue;
		}										

		if(CFG == 1)
		{
			int n[14];
			char GetGMName[11];
			int isAdmin;

			sscanf(sLineTxt, "%d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&isAdmin, &GetGMName, &n[0], &n[1], &n[2], &n[3], &n[4], &n[5],  &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13]);
			GM[GMCount].IsAdmin		= isAdmin;
			sprintf(GM[GMCount].Name,"%s",GetGMName);
			GM[GMCount].Drop		= n[0];
			GM[GMCount].Gg			= n[1];
			GM[GMCount].SetZen		= n[2];
			GM[GMCount].Status		= n[3];
			GM[GMCount].Gmove		= n[4];
			GM[GMCount].SetPK		= n[5];		 
			GM[GMCount].PkClear		= n[6];	 	
			GM[GMCount].BanPlayer	= n[7];   
			GM[GMCount].Reload		= n[8];
			GM[GMCount].Skin		= n[9];			 
			GM[GMCount].BanPost		= n[10];
			GM[GMCount].Voskl		= n[11];  
			GM[GMCount].Disconnect	= n[12];
			GM[GMCount].Trace		= n[13];
			GMCount++;
		}
	}

	rewind(fp);
	fclose(fp);	
	//Log.LogOutPut(true, Log.c_Blue, Log.t_NULL,"[GMSystem] Load sucsessfully. Total GMs: %d",GMCount);
}

													   
int cGmSystem::IsCommand(Commands Cmd, char Character[11])
{	
	switch (Cmd)
	{
		case NONE:
			return 1;
	}
	if(IsGMBD(Character))
	{
		if (this->IsGMSystem)
		{
			for(int x=0; x < GMCount; x++)
				if(!strcmp(GM[x].Name, Character))
				{
					switch (Cmd)
					{
					case cDrop:
						return GM[x].Drop;
					case cGg:
						return GM[x].Gg;
					case cSetZen:
						return GM[x].SetZen;
					case cStatus:
						return GM[x].Status;
					case cGmove:
						return GM[x].Gmove;	 
					case cSetPK:
						return GM[x].SetPK;	   
					case cPkClear:
						return GM[x].PkClear;		 
					case cBanPlayer:
						return GM[x].BanPlayer;
					case cReload:
						return GM[x].Reload;
					case cSkin:
						return GM[x].Skin;	  	
					case cBanPost:
						return GM[x].BanPost;
					case cVoskl:
						return GM[x].Voskl;		
					case cDisconnect:
						return GM[x].Disconnect;
					case cTrace:
						return GM[x].Trace;
					}
				}
			return 0; 
		}
		else
			return 1;
	}
	else
		return 0;
}

int cGmSystem::IsAdmin(char Character[11])
{	
	if(IsGMBD(Character))
	{
		if (this->IsGMSystem)
		{
			for(int x=0; x < GMCount; x++)
				if(!strcmp(GM[x].Name, Character))
				{
					switch (GM[x].IsAdmin)
					{
					case 0: 
						return 0;
					case 1: 
						return 1;
					case 2:
						return 2;					
					}
				}
			return 0; 
		}
		else
			return 2;
	}
	else return 0;
}					  
	
bool cGmSystem::IsGMBD(char Character[11])
{
	for(int i = OBJMAX - OBJMAXUSER; i <= OBJMAX; i++)
	{  	 
		if(gObj[i].Connected < 3) continue;
		if(!strcmp(gObj->Name, Character) && (gObj->Authority == 32 || gObj->Authority == 8))
			return true;
	}
	return false;
}
