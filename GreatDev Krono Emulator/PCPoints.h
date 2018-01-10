              //==============================================================================================//
              //										PcPoints System								          //
              //										 Krono Project							              //
			  //								Source Base: GreatDev Knono Emulator						  //
              //                           Season 2.5 (Kor: 3.0) ~ GameServer 1.00.56                         //
              //                                  Codded by: Knight 2016 ~ 2018                               //
              //==============================================================================================//

#include "StdAfx.h"

struct PCShopItemConfig
{	
	BYTE ItemIndex;
	BYTE ItemID;	
	BYTE X;
	BYTE Y;
	BYTE Skill;
	BYTE Level;
	BYTE Luck;
	BYTE Opt;
	BYTE Dur;
	BYTE Exc;
	BYTE Ancient;
	BYTE SlotX;
	short Reward;
	int Cost;
};
struct PCPointIncreseMobStruct
{
	int Mob;
	int Pontos;
};

#define MaxPCPointItems 120
#define MaxMobs 512

class PCPointShop
{
public:
	virtual ~PCPointShop();
	PCPointShop();
	UINT ReadFile(char * file);
	int CalcItemXY(int X,int Y);
	int MakePacket();
	void Init();
	void OpenShop(DWORD PlayerID);
	void BuyItem(DWORD PlayerID,int Position);
	void SendPoints(DWORD PlayerID,int Points);
	void DecreasePoints(DWORD PlayerID,int Points);
	void IncresePointMonster(int aIndex,int MobIndex);
	

	//Vars
	BOOL IsPCPointSystem;
	BYTE PCPointPacket[4680];
	BYTE PC_Shop[MaxPCPointItems];
	short AmountRecords[3];
	PCShopItemConfig Items[MaxPCPointItems];
	PCPointIncreseMobStruct MonstrosSTC[MaxMobs];
	int OnlyForGM;
	int AddWhenKillMobs;
    int MaxPCBangPoint;
    int EnabledMobGivePCPoint;
	//variaveis
	int ItemIndex;
	int ItemID;	
	int X;
	int Y;
	int Skill;
	int Level;
	int Luck;
	int Opt;
	int Dur;
	int Exc;
	int Anci;
	int SlotX;
	int Cost;
	int MaxPlayerPoints;
private:
	
	int HowManyItems;
	int MobPointRecords;
	int PacketSizes;
	int SearchIndex(int Position);

	int Mob;
	int Pontos;
	int tLengMonster;
	int leestatus;
	bool ArrayFiledItems[15][8];
};

extern PCPointShop PCPoint;