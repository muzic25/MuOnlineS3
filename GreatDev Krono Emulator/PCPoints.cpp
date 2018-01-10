#include "stdafx.h"
/*#include "user.h"
#include "PCPoints.h"
#include "Logproc.h"
#include "DSProtocol.h"
#include "dirpath.h"
*/
PCPointShop PCPoint;

PCPointShop::~PCPointShop()
{

}
PCPointShop::PCPointShop()
{

}

UINT PCPointShop::ReadFile(char * file)
{
	DWORD dwArgv=0;
	FILE *fp;
	char sLineTxt[255] = {0};
	BOOL bRead = FALSE;
	this->HowManyItems = 0;
	this->tLengMonster = 0;

	srand((unsigned)time(NULL));
	fp=fopen(file, "r");
	if(!fp)
	{		
		IsPCPointSystem = FALSE;
		return 0;
	}

	IsPCPointSystem = TRUE;

	rewind(fp);
	
	leestatus= -1;
	
	while(fgets(sLineTxt, 255, fp) != NULL)
	{
		if(sLineTxt[0] == '/')
			continue;  
		
		if(bRead == FALSE && (UINT)(sLineTxt[0]-0x30) == dwArgv) bRead = TRUE;			

		if(bRead==TRUE && strlen(sLineTxt)<3)
		{
			UINT q = 0;
			sscanf(sLineTxt, "%d", &q);
			leestatus = q;
		}

		if(leestatus == 0)
		{
			if(bRead==TRUE && strlen(sLineTxt)>3)
			{
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
				{
					leestatus = 1;
				} else {
					if(HowManyItems > MaxPCPointItems)
					{
						MessageBoxA(NULL, "To many Items!!", "[PCPoint]Error", 0);
						::ExitProcess(1);
					}
					sscanf(sLineTxt, "%d %d %d %d %d %d %d %d %d %d %d %d", &ItemIndex , &ItemID, &X, &Y, &Level, &Opt,&Luck, &Skill,&Dur,&Exc,&Anci,&Cost);
					Items[HowManyItems].ItemIndex	=	this->ItemIndex;
					Items[HowManyItems].ItemID		=	this->ItemID;
					Items[HowManyItems].X			=	this->X;
					Items[HowManyItems].Y			=	this->Y;
					Items[HowManyItems].Level		=	this->Level;
					Items[HowManyItems].Opt			=	this->Opt;
					Items[HowManyItems].Luck		=	this->Luck;
					Items[HowManyItems].Skill		=	this->Skill;
					Items[HowManyItems].Dur			=	this->Dur;
					Items[HowManyItems].Exc			=	this->Exc;
					Items[HowManyItems].Ancient		=	this->Anci;
					Items[HowManyItems].Cost		=	this->Cost;

					Items[HowManyItems].SlotX=CalcItemXY(Items[HowManyItems].X,Items[HowManyItems].Y);
					this->HowManyItems++;

					LogAddC(2,"[PCPoint]: item:[%d][%d][%d][%d][%d][%d][%d][%d][%d] Cost: [%d]",ItemIndex,ItemID,Level,Opt,Luck,Skill,Dur,Exc,Anci,Cost);
				}
			}
		}
		if(leestatus == 1)
		{
			if(bRead==TRUE && strlen(sLineTxt)>3)
			{
				if ((sLineTxt[0] == 'e')&&(sLineTxt[1] == 'n')&&(sLineTxt[2] == 'd'))
				{
					leestatus = -1;
				} else 
				{
					if(tLengMonster > MaxMobs)
					{
						MessageBoxA(NULL, "Monsters overloaded!! Delete some lines", "[PCPoint]Error", 0);
						::ExitProcess(1);
					}
					sscanf(sLineTxt, "%d %d", &Mob , &Pontos);
					MonstrosSTC[tLengMonster].Mob = Mob;
					MonstrosSTC[tLengMonster].Pontos = Pontos;
					tLengMonster++;
					LogAddC(2,"[PCPoint]: MOB:[%d][%d]",Mob , Pontos,tLengMonster);
				}

			}
		}
	}

	rewind(fp);
	fclose(fp);

LogAddC(2,"[PCPoint]: PCPoint System succesfully loaded, Total items: %d Total Monsters: %d",HowManyItems, tLengMonster);

	return 1;
}

void PCPointShop::IncresePointMonster(int aIndex,int MobIndex)
{
	LPOBJ lpObjEx = &gObj[aIndex];
	LPOBJ MosterObj = &gObj[MobIndex];

	if(PCPoint.EnabledMobGivePCPoint == 1)
	{
		for(int i = 0; i< tLengMonster;i++)
		{
			int	Pontos = MonstrosSTC[i].Pontos;

			if(MosterObj->Class == MonstrosSTC[i].Mob)
			{
				lpObjEx->PCPoint += Pontos;
				this->SendPoints(aIndex,lpObjEx->PCPoint);
			}
		}
	}
}
int PCPointShop::SearchIndex(int Position)
{
/*	int IndexItem = -1;

	for(int i=0;i< HowManyItems; i++)
	{
		if(Position==Items[i].SlotX)
			IndexItem = i;
	}
	retur* -1 ;
	*/
/*	for(int i=0;i< HowManyItems; i++)
	{
		if(Position==Items[i].SlotX)
			return i;
	}
	return -1 ;
	*/

/*	for(int i=0;i< HowManyItems; i++)
	{
		if(Position==Items[i].SlotX)
			return i;
	}
	*/return 0;
}

int PCPointShop::CalcItemXY(int X,int Y)
{
/*	   for (int i = 0; i < 15; i++)
        for (int j = 0; j < 8; j++)
            if (ArrayFiledItems[i][j] == false)
            {
                bool bFlag = true;

                for (short kX = 0; kX < X; kX++)
                    for(short kY = 0; kY < Y; kY++)
                        if ( i + kY > 14 || j + kX > 7 || ArrayFiledItems[i+kY][j+kX])
                            bFlag = false;

                if (bFlag)
                {
                    for (short kX = 0; kX < X; kX++)
                        for(short kY = 0; kY < Y; kY++)
                            ArrayFiledItems[i+kY][j+kX] = true;
                    return i*8 + j;
                }
            }
    return -1;*/

	int YPos=0;
	int XPos=0;
	int j=-1;
	Y-=1;

	while(YPos<15)
	{
		XPos=0;
		while(XPos<8)
		{
			if((PC_Shop[XPos+(YPos*8)]==0) && (PC_Shop[XPos+(YPos*8)+X-1]==0) && (XPos+X-1<8))
			{
				if(Y==0)
				{
					for(j=0;j<X;j++)
						PC_Shop[XPos+(YPos*8)]=1;
					return (XPos+(YPos*8));
				}else
				{

					if((PC_Shop[(XPos+(YPos*8))+(Y*8)]==0) /*&& (PC_Shop[(XPos+(YPos*8)+X)+(Y*8)]==0)*/ && (XPos+X-1<8))
					{
						for(j=0;j<X;j++)
						{
							for(int z=1;z<=Y;z++)
							{
								PC_Shop[XPos+(YPos*8)+j+z*8]=1;
							}
							PC_Shop[XPos+(YPos*8)+j]=1;
						}
						return (XPos+(YPos*8));
					}
				}
			}
			XPos++;
		}
		YPos++;
	}

	return j;
}

int PCPointShop::MakePacket()
{
	int PacketSize=0;
	int PacketFlag=0;
	int Size=0;

	BYTE Packet1[11]={0xC1,0x05,0xD0,0x06,0x00,0xC2,0x00,0x36,0x31,HIBYTE(HowManyItems),LOBYTE(HowManyItems)};
	BYTE Packet2[4680];

	for(int i= 0 ; i < HowManyItems; i++)
	{
		int LuckOptLevel=((Items[i].Opt/4)+(Items[i].Luck*4)+(Items[i].Level*8) + (Items[i].Skill*128));
		int ItemIndex=Items[i].ItemIndex*16;

		BYTE BetaPacket[8]=
		{
		Items[i].SlotX,
		Items[i].ItemID,
		LuckOptLevel,
		Items[i].Dur,
		Items[i].Exc,
		Items[i].Ancient,
		ItemIndex,0x00
		};
		PacketSize=(sizeof(BetaPacket)*(i+1));
		memcpy(&Packet2[PacketFlag],BetaPacket,PacketSize );
		PacketFlag=PacketSize;
	}

	Size=(sizeof(Packet1)+PacketSize);
	memcpy(&PCPointPacket,Packet1, sizeof(Packet1));
	memcpy(&PCPointPacket[sizeof(Packet1)],Packet2, sizeof(Packet1)+PacketSize);
	PCPointPacket[6]=HIBYTE(Size);
	PCPointPacket[7]=LOBYTE(Size);

	return (sizeof(Packet1)+PacketSize);
}

/*
DWORD WINAPI Timer(LPVOID lpParam)
{
	Sleep(4100);

	PCPoint.ReadFile();

	return 1;
}*/

void PCPointShop::Init()
{
	//PC Points
	this->IsPCPointSystem = GetPrivateProfileInt("PCPoints", "Enabled", 1, gDirPath.GetNewPath("commonserver.cfg"));
	this->OnlyForGM = GetPrivateProfileInt("PCPoints", "OnlyForGM", 1, gDirPath.GetNewPath("commonserver.cfg"));
	this->MaxPlayerPoints = GetPrivateProfileInt("PCPoints", "PCBangMaxPoint", 10000, gDirPath.GetNewPath("commonserver.cfg"));
	this->EnabledMobGivePCPoint = GetPrivateProfileInt("PCPoints", "PCBangPointKillMob", 1, gDirPath.GetNewPath("commonserver.cfg"));

	if (!IsPCPointSystem)
	{
		return;
	}

	for (int i = 0; i < MaxPCPointItems; i++)
	{
		PC_Shop[i] = 0x00;
	}

	this->ReadFile(gDirPath.GetNewPath("PCPoints.ini"));
	
	//CloseHandle(CreateThread(NULL,0,Timer,NULL,0,NULL));

	PacketSizes=MakePacket();

}

void PCPointShop::OpenShop(DWORD PlayerID)
{
	if (!IsPCPointSystem)
	{
		return;
	}

	LPOBJ lpObj = &gObj[PlayerID];

	if (lpObj->CloseType != -1)
	{
		return;
	}

	if (gObjIsConnectedGP(PlayerID) == 0)
	{
		LogAddTD("[ANTI-HACK][PCBangPointShopOpen] Couldn't Open.. (%s)(%s)", lpObj->AccountID, lpObj->Name);
		return;
	}

	if(lpObj->Level < 6)
	{
		GCServerMsgStringSend("You must level 6 and above to open Pc Point shop.", lpObj->m_Index, 1);
		return;
	}

	if (lpObj->MapNumber != 0 && lpObj->MapNumber != 2 && lpObj->MapNumber != 3 && lpObj->MapNumber != 4 && lpObj->MapNumber != 34 && lpObj->MapNumber != 6)
	{
		GCServerMsgStringSend("You can't open Pc Point shop at this location.", lpObj->m_Index, 1);
		return;
	}
	
	DataSend(PlayerID, PCPointPacket, PacketSizes);
	
	
}

void PCPointShop::BuyItem(int aIndex,int Position)
{
	if (!IsPCPointSystem)
	{
		return;
	}

	LPOBJ lpObjEx = &gObj[aIndex];
	LPOBJ pObj    = &gObj[aIndex];

	int IndexItem = 0; //SearchIndex(Position);
	//int i=SearchIndex(Position);
	BOOL IfBuy = FALSE;
	DWORD SealAscencion = ITEMGET(13,43);
	DWORD SealWealt = ITEMGET(13,44);
	DWORD SealSustenance = ITEMGET(13,45);
	char pMsg[MAX_CHAT_LEN];

	for (int i = 0; i < HowManyItems; i++)
	{
		if (Position == Items[i].SlotX)
		{
			IndexItem = i;
		}
	}

	if(IndexItem != -1)
	{
		if(Items[IndexItem].Cost <= lpObjEx->PCPoint )
		{
			IfBuy = TRUE;
			DWORD RewardItem = ITEMGET(Items[IndexItem].ItemIndex, Items[IndexItem].ItemID);

			if (RewardItem == SealAscencion || RewardItem == SealWealt || RewardItem == SealSustenance)
			{
				if (RewardItem == SealWealt)
				{
					g_ItemAddOption.SetItemEffect(&gObj[aIndex], ITEMGET(13, 44), 600);
				}
				if (RewardItem == SealAscencion)
				{
					g_ItemAddOption.SetItemEffect(&gObj[aIndex], ITEMGET(13, 43), 600);
				}
				if (RewardItem == SealSustenance)
				{
					g_ItemAddOption.SetItemEffect(&gObj[aIndex], ITEMGET(13, 45), 600);
				}
				sprintf(pMsg, "[PCPoint] You spend %d points.", Items[IndexItem].Cost);
				GCServerMsgStringSend(pMsg, lpObjEx->m_Index, 1);
			}
			else
			{
				ItemSerialCreateSend(pObj->m_Index, 236, pObj->X, pObj->Y, RewardItem, Items[IndexItem].Level, Items[IndexItem].Dur, Items[IndexItem].Skill, Items[IndexItem].Luck, Items[IndexItem].Opt, -1, Items[IndexItem].Exc, Items[IndexItem].Ancient);
				IfBuy = TRUE;
				sprintf(pMsg, "[PCPoint] You spend %d points.", Items[IndexItem].Cost);
				GCServerMsgStringSend(pMsg, lpObjEx->m_Index, 1);
			}
			DecreasePoints(aIndex, Items[IndexItem].Cost);
		}
		else
		{
			IfBuy = FALSE;
			char pMsg[MAX_CHAT_LEN];
			sprintf(pMsg, "[PCPoint] Not enough PC Points. Item cost: %d", Items[IndexItem].Cost);
			GCServerMsgStringSend(pMsg, lpObjEx->m_Index, 1);
		}
	}

	if((IfBuy==TRUE) && (IndexItem != -1))
	{
		LogAddC(3,"[PCPointShop] BuyItem [%s][%s] Cost: %d",lpObjEx->AccountID,lpObjEx->Name, Items[IndexItem].Cost);
	} 
	else 
	{
		LogAddC(2,"[PCPointShop] Attempt to BuyItem [%s][%s] Cost: %d",lpObjEx->AccountID,lpObjEx->Name,Items[IndexItem].Cost);
	}

}

void PCPointShop::SendPoints(DWORD PlayerID,int Points)
{
	LPOBJ lpObjEx = &gObj[PlayerID];

	if (Points > MaxPlayerPoints)
	{
		MaxPlayerPoints = Points;
	}

	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(lpObjEx->PCPoint) , HIBYTE(lpObjEx->PCPoint) , LOBYTE(MaxPlayerPoints) , HIBYTE(MaxPlayerPoints)};
	DataSend(PlayerID,(PBYTE)Packet,Packet[1]);

	LogAddC(2,"[PCPointShop] SendPoints [%s] Points: %d",lpObjEx->AccountID,lpObjEx->PCPoint);
}

void PCPointShop::DecreasePoints(DWORD PlayerID,int Points)
{
	LPOBJ pObj = &gObj[PlayerID];
	LPOBJ lpObjEx = &gObj[PlayerID];

	if(lpObjEx->PCPoint - Points < 0) 
	{
		lpObjEx->PCPoint = 0;
	}
	else
	{
		lpObjEx->PCPoint -= Points;
	}

	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(lpObjEx->PCPoint) , HIBYTE(lpObjEx->PCPoint) , LOBYTE(MaxPlayerPoints) , HIBYTE(MaxPlayerPoints)};
	DataSend(PlayerID,(PBYTE)Packet,Packet[1]);
}

void PCPointShop::GCSendPcBangUserPoint(int aIndex) //0049A1E0 (identical)
{
	if (!IsPCPointSystem)
	{
		return;
	}

	LPOBJ pObj = &gObj[aIndex];
	PMSG_ANS_PCBANG_POINT_INFO pMsg = { 0 };

	PHeadSubSetB((LPBYTE)&pMsg, 0xD0, 0x04, sizeof(pMsg));

	pMsg.m_sPoint = pObj->PCPoint;
	pMsg.m_sMaxPoint = MaxPlayerPoints;
	pMsg.m_btType = this->IsPCPointSystem;

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	LogAddC(2, "[PCPointShopConnect] SendPoints [%s] Points: %d", pObj->AccountID, pObj->PCPoint);
}