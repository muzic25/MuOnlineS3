#include "StdAfx.h"
#include "ChaosBox.h"

#define NO_CHECK_LVL 0
#define NULL_ENDID 0
#define STARTIDITEMS 0x0000 // ITEMGET(0,0)
#define ENDIDITEMS 0x17FF   // ITEMGET(12,0) - 1

#define KRONO_CHAOSMIX "..\\Data\\ChaosMix.ini"

cChaosBox ChaosBox;

cChaosBox::cChaosBox() { /*Конструктор*/ this->LoadConfigs(); }
cChaosBox::~cChaosBox() { /*Деструктор*/ }

#pragma message("#TODO Fix Enum Chaos_Type_Msg")
void ChaosEventProtocolCore(BYTE protoNum, unsigned char* aRecv, int aLen)
{
#ifdef TRACE_PROTOCOL
	LogAddHeadHex("CHAOS_EVENT", aRecv, aLen);
#endif

	switch ( protoNum )
	{
	case 0x01:
		ChaosBox.CBUPR_ItemRequestRecv( (CB_PMSG_REQ_PRESENT_RESULT *)aRecv);
		break;
	}
}

void cChaosBox::CBUPR_ItemRequestRecv( CB_PMSG_REQ_PRESENT_RESULT * lpMsg)
{
	struct PMSG_PRIZE_INFO
	{
		PBMSG_HEAD h;
		char AccountID[10];	// 3
		char GameID[10];	// D
		int servernumber;	// 18
		char present;	// 1C
		int Seq_present;	// 20
	}pMsg;

	LPOBJ lpObj;
	char szId[11];
	char szName[11];
	char szPresentName[51];
	int aIndex;

	szId[10] = 0;
	szName[10] = 0;
	memset(szPresentName, 0, sizeof(szPresentName));
	memcpy(szId, lpMsg->AccountId, sizeof(lpMsg->AccountId));
	memcpy(szName, lpMsg->GameId, sizeof(lpMsg->GameId));
	memcpy(szPresentName, lpMsg->presentname, sizeof(lpMsg->presentname));
	aIndex = lpMsg->Sequence;

	if (gObjIsConnectedGP(aIndex) == FALSE )
	{
		LogAddC(2, "error-L3 [%s][%d]", __FILE__, __LINE__);
		return;
	}

	lpObj = &gObj[aIndex];

	if ( strcmp(szId, lpObj->AccountID) != 0 )
	{
		LogAddC(2, "error-L3 [%s][%d][%s == %s]", __FILE__, __LINE__, szId, lpObj->AccountID);
		return;
	}

	if ( strcmp(szName, lpObj->Name) != 0 )
	{
		LogAddC(2, "error-L3 [%s][%d]", __FILE__, __LINE__);
		return;
	}

	if ( lpMsg->present != -1 )
	{
		char szTemp[256]="";

		wsprintf(szTemp, lMsg.Get(MSGGET(6, 65)), szName, szPresentName);
		AllSendServerMsg(szTemp);

		pMsg.h.c = 0xC1;
		pMsg.h.headcode = 0x02;
		pMsg.h.size = sizeof(pMsg);
		pMsg.present = lpMsg->present;
		pMsg.Seq_present = lpMsg->Seq_present;
		pMsg.servernumber = Configs.gGameServerCode;
		memcpy(pMsg.AccountID, lpMsg->AccountId, sizeof(pMsg.AccountID));
		memcpy(pMsg.GameID, lpMsg->GameId, sizeof(pMsg.GameID));

		gUdpSocCE.SendData((LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DevilSquare] Present Prize Notice %d(%s) %d %s %s",
			lpMsg->present, szPresentName, lpMsg->Seq_present, szId, szName);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, 0x1FF, 0, 255, 0, 0, 0, -1, 0, 0);
		lpObj->Money -= 10000;
		GCMoneySend(lpObj->m_Index, lpObj->Money);

		PMSG_CHAOSMIXRESULT pMsg;

		PHeadSetB((LPBYTE)&pMsg, 0x86, sizeof(pMsg));
		pMsg.Result = 5;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}
	else
	{
		int in = ITEMGET(14,19); // Devil Square Invitation
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, in, 0, 0, 0, 0, 0, -1, 0, 0);
		lpObj->Money -= 10000;
		GCMoneySend(lpObj->m_Index, lpObj->Money);
		lpObj->ChaosLock = FALSE;

		LogAddTD("[DevilSquare] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, lpObj->ChaosMoney);
	}
};

void cChaosBox::LoadConfigs()
{
	/************************************************************************/
	/*                               Load Rate Mix                          */
	/************************************************************************/

	ConfRates.ChaosWeapon		=	GetPrivateProfileIntA("MaxRate","ChaosWeaponRate",	100,KRONO_CHAOSMIX);
	ConfRates.FirstWings		=	GetPrivateProfileIntA("MaxRate","FirstWingsRate",	100,KRONO_CHAOSMIX);
	ConfRates.SecondWings		=	GetPrivateProfileIntA("MaxRate","SecondWingsRate",	90,KRONO_CHAOSMIX);
	ConfRates.CapeOfLord		=	GetPrivateProfileIntA("MaxRate","CapeOfLordRate",	90,KRONO_CHAOSMIX);
	ConfRates.Condor			=	GetPrivateProfileIntA("MaxRate","CondorRate",		60,KRONO_CHAOSMIX);
	ConfRates.ThirdWings		=	GetPrivateProfileIntA("MaxRate","ThirdWingsRate",	40,KRONO_CHAOSMIX);
	ConfRates.DarkHourse		=	GetPrivateProfileIntA("MaxRate","DarkHourseRate",	60,KRONO_CHAOSMIX);
	ConfRates.DarkRaven			=	GetPrivateProfileIntA("MaxRate","DarkRavenRate",	60,KRONO_CHAOSMIX);
	ConfRates.Dinorant			=	GetPrivateProfileIntA("MaxRate","DinorantRate",		70,KRONO_CHAOSMIX);

	ConfRates.DevilSquare[0]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate0",	60,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[1]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate1",	75,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[2]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate2",	70,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[3]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate3",	65,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[4]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate4",	60,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[5]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate5",	55,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[6]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate6",	50,KRONO_CHAOSMIX);
	ConfRates.DevilSquare[7]	=	GetPrivateProfileIntA("MaxRate","DevilSquareRate7",	45,KRONO_CHAOSMIX);

	ConfRates.BloodCastle[0]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate1",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[1]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate2",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[2]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate3",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[3]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate4",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[4]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate5",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[5]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate6",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[6]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate7",	80,KRONO_CHAOSMIX);
	ConfRates.BloodCastle[7]	=	GetPrivateProfileIntA("MaxRate","BloodCastleRate8",	80,KRONO_CHAOSMIX);

	ConfRates.Illusion[0]		=	GetPrivateProfileIntA("MaxRate","IllusionRate1",	70,KRONO_CHAOSMIX);
	ConfRates.Illusion[1]		=	GetPrivateProfileIntA("MaxRate","IllusionRate2",	70,KRONO_CHAOSMIX);
	ConfRates.Illusion[2]		=	GetPrivateProfileIntA("MaxRate","IllusionRate3",	70,KRONO_CHAOSMIX);
	ConfRates.Illusion[3]		=	GetPrivateProfileIntA("MaxRate","IllusionRate4",	70,KRONO_CHAOSMIX);
	ConfRates.Illusion[4]		=	GetPrivateProfileIntA("MaxRate","IllusionRate5",	70,KRONO_CHAOSMIX);
	ConfRates.Illusion[5]		=	GetPrivateProfileIntA("MaxRate","IllusionRate6",	70,KRONO_CHAOSMIX);

	ConfRates.PlusLevel10		=	GetPrivateProfileIntA("MaxRate","PlusLevelRate10",	50,KRONO_CHAOSMIX);
	ConfRates.PlusLevel11		=	GetPrivateProfileIntA("MaxRate","PlusLevelRate11",	45,KRONO_CHAOSMIX);
	ConfRates.PlusLevel12		=	GetPrivateProfileIntA("MaxRate","PlusLevelRate12",	45,KRONO_CHAOSMIX);
	ConfRates.PlusLevel13		=	GetPrivateProfileIntA("MaxRate","PlusLevelRate13",	45,KRONO_CHAOSMIX);
	ConfRates.AddLuckItems		=	GetPrivateProfileIntA("MaxRate","AddRateLuckItems",	25,KRONO_CHAOSMIX);

	ConfRates.BlessPotion		=	GetPrivateProfileIntA("MaxRate","BlessPotionRate",	100,KRONO_CHAOSMIX);
	ConfRates.SoulPotion		=	GetPrivateProfileIntA("MaxRate","SoulPotionRate",	100,KRONO_CHAOSMIX);
	ConfRates.Fruit				=	GetPrivateProfileIntA("MaxRate","FruitRate",		90,KRONO_CHAOSMIX);
	ConfRates.LifeStone			=	GetPrivateProfileIntA("MaxRate","LifeStoneRate",	100,KRONO_CHAOSMIX);

	ConfRates.FenrirLvl1		=	GetPrivateProfileIntA("ZenCost","FenrirRatePart1",		70,KRONO_CHAOSMIX);
	ConfRates.FenrirLvl2		=	GetPrivateProfileIntA("ZenCost","FenrirRatePart2",		50,KRONO_CHAOSMIX);
	ConfRates.FenrirLvl3		=	GetPrivateProfileIntA("ZenCost","FenrirRatePart3",		30,KRONO_CHAOSMIX);
	ConfRates.FenrirLvl4		=	GetPrivateProfileIntA("ZenCost","FenrirRatePart4",		79,KRONO_CHAOSMIX);

	ConfRates.ShieldPotionLvl1	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		50,KRONO_CHAOSMIX);
	ConfRates.ShieldPotionLvl2	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		30,KRONO_CHAOSMIX);
	ConfRates.ShieldPotionLvl3	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		30,KRONO_CHAOSMIX);

	/************************************************************************/
	/*                               Load Cost Mix                          */
	/************************************************************************/

	ConfCostZen.ChaosWeapon		=	GetPrivateProfileIntA("ZenCost","ChaosWeaponZen",	10000,KRONO_CHAOSMIX);
	ConfCostZen.FirstWings		=	GetPrivateProfileIntA("ZenCost","FirstWingsZen",	10000,KRONO_CHAOSMIX);
	ConfCostZen.SecondWings		=	GetPrivateProfileIntA("ZenCost","SecondWingsZen",	5000000,KRONO_CHAOSMIX);
	ConfCostZen.CapeOfLord		=	GetPrivateProfileIntA("ZenCost","CapeOfLordZen",	5000000,KRONO_CHAOSMIX);
	ConfCostZen.Condor			=	GetPrivateProfileIntA("ZenCost","CondorZen",		200000,KRONO_CHAOSMIX);
	ConfCostZen.ThirdWings		=	GetPrivateProfileIntA("ZenCost","ThirdWingsZen",	200000,KRONO_CHAOSMIX);
	ConfCostZen.DarkHourse		=	GetPrivateProfileIntA("ZenCost","DarkHourseZen",	5000000,KRONO_CHAOSMIX);
	ConfCostZen.DarkRaven		=	GetPrivateProfileIntA("ZenCost","DarkRavenZen",		1000000,KRONO_CHAOSMIX);
	ConfCostZen.Dinorant		=	GetPrivateProfileIntA("ZenCost","DinorantZen",		500000,KRONO_CHAOSMIX);

	ConfCostZen.DevilSquare[0]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen0",	100000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[1]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen1",	100000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[2]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen2",	200000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[3]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen3",	400000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[4]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen4",	700000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[5]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen5",	1100000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[6]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen6",	1600000,KRONO_CHAOSMIX);
	ConfCostZen.DevilSquare[7]	=	GetPrivateProfileIntA("ZenCost","DevilSquareZen7",	2100000,KRONO_CHAOSMIX);

	ConfCostZen.BloodCastle[0]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen1",	50000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[1]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen2",	80000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[2]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen3",	150000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[3]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen4",	250000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[4]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen5",	400000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[5]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen6",	600000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[6]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen7",	850000,KRONO_CHAOSMIX);
	ConfCostZen.BloodCastle[7]	=	GetPrivateProfileIntA("ZenCost","BloodCastleZen8",	1000000,KRONO_CHAOSMIX);

	ConfCostZen.Illusion[0]		=	GetPrivateProfileIntA("ZenCost","IllusionZen1",		3000000,KRONO_CHAOSMIX);
	ConfCostZen.Illusion[1]		=	GetPrivateProfileIntA("ZenCost","IllusionZen2",		5000000,KRONO_CHAOSMIX);
	ConfCostZen.Illusion[2]		=	GetPrivateProfileIntA("ZenCost","IllusionZen3",		7000000,KRONO_CHAOSMIX);
	ConfCostZen.Illusion[3]		=	GetPrivateProfileIntA("ZenCost","IllusionZen4",		9000000,KRONO_CHAOSMIX);
	ConfCostZen.Illusion[4]		=	GetPrivateProfileIntA("ZenCost","IllusionZen5",		11000000,KRONO_CHAOSMIX);
	ConfCostZen.Illusion[5]		=	GetPrivateProfileIntA("ZenCost","IllusionZen6",		13000000,KRONO_CHAOSMIX);

	ConfCostZen.PlusLevel10		=	GetPrivateProfileIntA("ZenCost","PlusLevelZen10",	2000000,KRONO_CHAOSMIX);
	ConfCostZen.PlusLevel11		=	GetPrivateProfileIntA("ZenCost","PlusLevelZen11",	4000000,KRONO_CHAOSMIX);
	ConfCostZen.PlusLevel12		=	GetPrivateProfileIntA("ZenCost","PlusLevelZen12",	6000000,KRONO_CHAOSMIX);
	ConfCostZen.PlusLevel13		=	GetPrivateProfileIntA("ZenCost","PlusLevelZen13",	8000000,KRONO_CHAOSMIX);

	ConfCostZen.BlessPotion		=	GetPrivateProfileIntA("ZenCost","BlessPotionZen",	100000,KRONO_CHAOSMIX);
	ConfCostZen.SoulPotion		=	GetPrivateProfileIntA("ZenCost","SoulPotionZen",	50000,KRONO_CHAOSMIX);
	ConfCostZen.Fruit			=	GetPrivateProfileIntA("ZenCost","FruitZen",			3000000,KRONO_CHAOSMIX);
	ConfCostZen.LifeStone		=	GetPrivateProfileIntA("ZenCost","LifeStoneZen",		5000000,KRONO_CHAOSMIX);

	ConfCostZen.FenrirLvl1		=	GetPrivateProfileIntA("ZenCost","FenrirZenPart1",		0,KRONO_CHAOSMIX);
	ConfCostZen.FenrirLvl2		=	GetPrivateProfileIntA("ZenCost","FenrirZenPart2",		0,KRONO_CHAOSMIX);
	ConfCostZen.FenrirLvl3		=	GetPrivateProfileIntA("ZenCost","FenrirZenPart3",		10000000,KRONO_CHAOSMIX);
	ConfCostZen.FenrirLvl4		=	GetPrivateProfileIntA("ZenCost","FenrirZenPart4",		10000000,KRONO_CHAOSMIX);

	ConfCostZen.ShieldPotionLvl1	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		100000,KRONO_CHAOSMIX);
	ConfCostZen.ShieldPotionLvl2	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		500000,KRONO_CHAOSMIX);
	ConfCostZen.ShieldPotionLvl3	=	GetPrivateProfileIntA("ZenCost","ShieldPotionMixLvl1",		1000000,KRONO_CHAOSMIX);

	/************************************************************************/
	/*								Div Values                              */
	/************************************************************************/
	DivValues.DivChaosWeapon	=	GetPrivateProfileIntA("DivValueRate","DivChaosWeapon",		20000	,KRONO_CHAOSMIX);
	DivValues.DivFirstWings		=	GetPrivateProfileIntA("DivValueRate","DivFirstWings",		20000	,KRONO_CHAOSMIX);
	DivValues.MainDivSecondWings=	GetPrivateProfileIntA("DivValueRate","MainDivSecondWings",	4000000 ,KRONO_CHAOSMIX);
	DivValues.SubDivSecondWings =	GetPrivateProfileIntA("DivValueRate","SubDivSecondWings",	40000	,KRONO_CHAOSMIX);
	DivValues.DivCondor			=	GetPrivateProfileIntA("DivValueRate","DivCondor",			300000	,KRONO_CHAOSMIX);
	DivValues.DivThirdWings		=	GetPrivateProfileIntA("DivValueRate","DivThirdWings",		3000000	,KRONO_CHAOSMIX);
	DivValues.FisrtDivFenrir4	=	GetPrivateProfileIntA("DivValueRate","FisrtDivFenrirPart4",	100		,KRONO_CHAOSMIX);
	DivValues.SecondDivFenrir4	=	GetPrivateProfileIntA("DivValueRate","SecondDivFenrirPart4",3000000	,KRONO_CHAOSMIX);

	/************************************************************************/
	/*                           LoadSubConfig                              */
	/************************************************************************/
	this->SecondWingsExcRate	=	GetPrivateProfileIntA("MaxRate","SecondWingsExcRate",30,KRONO_CHAOSMIX);
	this->SecondWingsMaxOpt		=	GetPrivateProfileIntA("MaxRate","SecondWingsMaxOpt",3,KRONO_CHAOSMIX);
	this->ThirdWingsExcRate		=	GetPrivateProfileIntA("MaxRate","ThirdWingsExcRate",20,KRONO_CHAOSMIX);
	this->ThirdWingsMaxOpt		=	GetPrivateProfileIntA("MaxRate","ThirdWingsMaxOpt",2,KRONO_CHAOSMIX);
}

int cChaosBox::ChaosBoxInit(LPOBJ lpObj)
{
	if (this->ChaosBoxClear(lpObj) == TRUE)
		return TRUE;
	
	lpObj->pChaosBox = new CItem[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBox == NULL )
		return FALSE;

	lpObj->pChaosBoxMap = new unsigned char[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBoxMap == NULL )
	{
		delete lpObj->pChaosBox;
		return FALSE;
	}

	for (int n = 0; n < CHAOS_BOX_SIZE; n++)
		lpObj->pChaosBoxMap[n] = -1;

	return TRUE;
}

BOOL cChaosBox::ChaosBoxClear(LPOBJ lpObj)
{
	if ( lpObj->pChaosBox != NULL )
	{
		for (BYTE n = 0; n < CHAOS_BOX_SIZE; n++)
			lpObj->pChaosBox[n].Clear();

		for (BYTE n = 0; n < CHAOS_BOX_SIZE; n++)
			lpObj->pChaosBoxMap[n] = -1;

		return TRUE;
	}
	return FALSE;
}

void cChaosBox::MessageDataSend(LPOBJ lpObj,CHAOS_TYPE_MSG TypeMsg)
{
	PMSG_CHAOSMIXRESULT pMsg;

	lpObj->ChaosLock = FALSE;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = TypeMsg;
	DataSend(lpObj->m_Index, (BYTE *)&pMsg, pMsg.h.size);
}

BYTE cChaosBox::CheckChaosItems(LPOBJ lpObj,short StartType,short EndType,BYTE MinLvl,BOOL CheckExc,BOOL CheckAnc)
{
	if (EndType == -1 || EndType < StartType ) EndType = StartType;

	BYTE CountItems = 0;

	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
	{
		if (lpObj->pChaosBox[i].IsItem() && lpObj->pChaosBox[i].m_Type >= StartType && lpObj->pChaosBox[i].m_Type <= EndType)
		{
			if (lpObj->pChaosBox[i].m_Level < MinLvl) continue;
			if (CheckExc && !lpObj->pChaosBox[i].m_NewOption) continue;
			if (CheckAnc && !lpObj->pChaosBox[i].m_SetOption) continue;
			if (lpObj->pChaosBox[i].m_Type == ITEMGET(14,53)) continue;
			CountItems++;
		}
	}
	return CountItems;
}

BYTE cChaosBox::CheckChaosItems(LPOBJ lpObj,short TypeItem)
{
	BYTE CountItems = 0;

	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
		if (lpObj->pChaosBox[i].m_Type == TypeItem && lpObj->pChaosBox[i].m_Type != ITEMGET(14,53))
			CountItems++;

	return CountItems;
}

DWORD cChaosBox::GetBuyMoneyItems(LPOBJ lpObj, BOOL ActiveOld,short StartType, short EndType)
{
	if (EndType == -1 || StartType > EndType) EndType = StartType;

	DWORD CountMoney = 0;

	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
	{
		if (lpObj->pChaosBox[i].IsItem() && lpObj->pChaosBox[i].m_Type >= StartType && lpObj->pChaosBox[i].m_Type <= EndType)
		{
			if (ActiveOld == TRUE) 
			{
				lpObj->pChaosBox[i].OldValue();
				CountMoney += lpObj->pChaosBox[i].m_OldBuyMoney;
			}
			else
			{
				CountMoney += lpObj->pChaosBox[i].m_BuyMoney;
			}
		}
	}
	return CountMoney;
}

BOOL cChaosBox::AddSuccessCharmSystem(LPOBJ lpObj)
{
	BYTE AmountCharm = 0;

	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
	{
		if (lpObj->pChaosBox[i].m_Type == ITEMGET(14,53))
		{
			lpObj->ChaosSuccessRate += lpObj->pChaosBox[i].m_Durability;
			AmountCharm++;
		}
	}

	if (AmountCharm > 10)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_SHARM_OF_BOX_MSG);
		return FALSE;
	}

	return TRUE;
}

BYTE cChaosBox::GetItemLevel(LPOBJ lpObj,short Type)
{	
	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
		if (lpObj->pChaosBox[i].m_Type == Type)
			return lpObj->pChaosBox[i].m_Level;
	return -1;
}

BYTE cChaosBox::GetItemCount(LPOBJ lpObj)
{
	DWORD CountDur = 0;

	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
		if (lpObj->pChaosBox[i].IsItem() && lpObj->pChaosBox[i].m_Type != ITEMGET(14,53))
			CountDur++;

	return CountDur;
}

BYTE cChaosBox::GetDurability(LPOBJ lpObj,short Type)
{
	for (BYTE i = 0; i < CHAOS_BOX_SIZE; i++)
		if (lpObj->pChaosBox[i].m_Type == Type)
			return lpObj->pChaosBox[i].m_Durability;
	return -1;
}

BOOL cChaosBox::DecZenChaosSystem(LPOBJ lpObj,DWORD StartZen)
{
	DWORD ChaosTaxMoney = StartZen * (g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100 );

	if (ChaosTaxMoney < 0 ) ChaosTaxMoney = 0;
	StartZen += ChaosTaxMoney;
	if (StartZen < 0 ) StartZen = 0;

	if (lpObj->Money < StartZen )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_NOT_ENOUGH_ZEN);
		return FALSE;
	}
	else
	{
		lpObj->Money  -= StartZen;
		GCMoneySend(lpObj->m_Index, lpObj->Money);
		g_CastleSiegeSync.AddTributeMoney(ChaosTaxMoney);
		return TRUE;
	}
}

/************************************************************************/
/*                      Методы для варки                                */
/************************************************************************/

void cChaosBox::BlessPoitonMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	/*Проверяем вещи*/
	int AmountItems = this->GetItemCount(lpObj);
	int AmountBless = this->CheckChaosItems(lpObj,ITEMGET(14,13));

	if (AmountBless == 0 || AmountItems > AmountBless)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	if (AmountBless > 25)
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
		return;
	}

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.BlessPotion) != TRUE) return;

	lpObj->ChaosSuccessRate = ConfRates.BlessPotion;

	srand(GetTickCount());

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(14,7), 0,  AmountBless * 10 , 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::SoulPotionMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int AmountItems = this->GetItemCount(lpObj);
	int AmountSoul = this->CheckChaosItems(lpObj,ITEMGET(14,14));

	if (AmountSoul == 0 || AmountItems > AmountSoul)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	if (AmountSoul > 25)
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.SoulPotion) != TRUE) return;

	lpObj->ChaosSuccessRate = ConfRates.SoulPotion;

	srand(GetTickCount());

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(14,7), 1,  AmountSoul * 10 , 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::DlPetChaosMix(LPOBJ lpObj, int ModeMix)
{
	lpObj->ChaosLock = TRUE;

	if ( ModeMix == CHAOS_TYPE::CHAOS_TYPE_DARKHORSE ) ModeMix = 0;
	if ( ModeMix == CHAOS_TYPE::CHAOS_TYPE_DARKSPIRIT) ModeMix = 1;
	//ModeMix == false - this DarkHourse (Spirit + 0)
	//ModeMix == true - this DarkSpirit (Spirit + 1)
	BYTE AmountBless = this->CheckChaosItems(lpObj,ITEMGET(14,13));
	BYTE AmountSoul = this->CheckChaosItems(lpObj,ITEMGET(14,14));
	BYTE AmoutCreat = this->CheckChaosItems(lpObj,ITEMGET(14,22));
	BYTE AmoutChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmoutSpirit = this->CheckChaosItems(lpObj,ITEMGET(13,31));

	BYTE ItemCount = this->GetItemCount(lpObj);
	BYTE CheckSum = AmountBless + AmountSoul + AmoutCreat + AmoutChaos + AmoutSpirit;

	BYTE LevelSpirit = this->GetItemLevel(lpObj,ITEMGET(13,31));

	if (!ModeMix && ( LevelSpirit != 0 || ItemCount != CheckSum || AmountBless != 5 || AmountSoul != 5 
		|| AmoutChaos != 1 || AmoutCreat != 1 || AmoutSpirit != 1 ) )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	if (ModeMix && (LevelSpirit != 1 || ItemCount != CheckSum || AmountBless != 2 || AmountSoul != 2 
		|| AmoutChaos != 1 || AmoutCreat != 1 || AmoutSpirit != 1) )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	lpObj->ChaosSuccessRate = (!ModeMix) ? ConfRates.DarkHourse : ConfRates.DarkRaven;

	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;

	int NeedZen = (!ModeMix) ? ConfCostZen.DarkHourse : ConfCostZen.DarkRaven;

	if (this->DecZenChaosSystem(lpObj,NeedZen) != TRUE ) return;

	srand(GetTickCount());

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int Type = (!ModeMix) ? ITEMGET(13,4) : ITEMGET(13,5);

		int Option1 = ( (rand()%5) == 0 ) ? 1 : 0;
		int Option2 = 0;
		int Add = ( (rand()%100) < (lpObj->ChaosSuccessRate/5+6) ) ? 1 : 0;

		int lc22 = rand()%100; 	
		int lc23 = rand()%3;

		switch ( lc23 )
		{
		case 0:
			if ( lc22 <  4 ) Option2 = 3;
			break;

		case 1:
			if ( lc22 <  10 ) Option2 = 2;
			break;

		case 2:
			if ( lc22 <  20 ) Option2 = 1;
			break;
		}

		PetItemSerialCreateSend(lpObj->m_Index, -2, 0, 0, Type, 0, 0, Add, Option1, 0, -1, 0, 0); 
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::DevilSqueareMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountKeys = this->CheckChaosItems(lpObj,ITEMGET(14,18));
	BYTE AmountEyes = this->CheckChaosItems(lpObj,ITEMGET(14,17));
	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE ItemCount = this->GetItemCount(lpObj);

	BYTE CheckSum = AmountKeys + AmountEyes + AmountChaos;

	if (CheckSum != ItemCount || AmountKeys != 1 || AmountEyes != 1 || AmountChaos != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	BYTE LevelEye = this->GetItemLevel(lpObj,ITEMGET(14,17));
	BYTE LevelKey = this->GetItemLevel(lpObj,ITEMGET(14,18));
	BYTE LevelTicket = (LevelEye == LevelKey) ? LevelKey : -1;

	if (LevelTicket == -1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	/*Высечление Rate*/

	lpObj->ChaosSuccessRate = ConfRates.DevilSquare[LevelTicket];

	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;

	if (g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit)
		lpObj->ChaosSuccessRate += g_CrywolfSync.GetPlusChaosRate();
	
	/*Cнятие зен*/

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.DevilSquare[LevelTicket]) != TRUE ) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(14,19), LevelTicket, 0, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::BloodCastleTicketMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountScroll = this->CheckChaosItems(lpObj,ITEMGET(13,16));
	BYTE AmountBone = this->CheckChaosItems(lpObj,ITEMGET(13,17));
	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE ItemCount = this->GetItemCount(lpObj);

	BYTE CheckSum = AmountScroll + AmountBone + AmountChaos;

	if (CheckSum != ItemCount || AmountBone != 1 || AmountScroll != 1 || AmountChaos != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	BYTE LevelScrool = this->GetItemLevel(lpObj,ITEMGET(13,16));
	BYTE LevelBone = this->GetItemLevel(lpObj,ITEMGET(13,17));

	BYTE LevelTicket = (LevelBone == LevelScrool) ? LevelScrool : -1;

	if (LevelTicket == -1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	/*Вычисление Rate*/

	lpObj->ChaosSuccessRate = ConfRates.BloodCastle[LevelTicket-1];

	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;

	if (g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit)
		lpObj->ChaosSuccessRate += g_CrywolfSync.GetPlusChaosRate();

	/*Снятие Zen*/

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.BloodCastle[LevelTicket-1]) == FALSE) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,18), LevelTicket, 0, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::IllusionTicketMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountScroll = this->CheckChaosItems(lpObj,ITEMGET(13,49));
	BYTE AmountPotion = this->CheckChaosItems(lpObj,ITEMGET(13,50));
	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE ItemCount = this->GetItemCount(lpObj);

	BYTE CheckSum = AmountScroll + AmountPotion + AmountChaos;

	if (CheckSum != ItemCount || AmountPotion != 1 || AmountScroll != 1 || AmountChaos != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	BYTE LevelScroll = this->GetItemLevel(lpObj,ITEMGET(13,49));
	BYTE LevelPotion = this->GetItemLevel(lpObj,ITEMGET(13,50));

	BYTE LevelTicket = (LevelScroll == LevelPotion) ? LevelPotion : -1;

	if (LevelTicket == -1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	/*Вычесление Rate*/

	lpObj->ChaosSuccessRate = ConfRates.Illusion[LevelTicket-1];
	
	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;

	if (g_CrywolfSync.GetOccupationState() == 0 && Configs.g_iCrywolfApplyMvpBenefit)
		lpObj->ChaosSuccessRate += g_CrywolfSync.GetPlusChaosRate();

	/*Снятие Зен*/

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.Illusion[LevelTicket-1]) == FALSE) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,51), LevelTicket, 1, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}
	lpObj->ChaosLock = FALSE;
}

void cChaosBox::DefaultMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	/*Проверяем количество*/
	BYTE AmountChaos = CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmountItems = CheckChaosItems(lpObj,STARTIDITEMS,ENDIDITEMS,NO_CHECK_LVL,FALSE,FALSE);
	BYTE AmountJewels = CheckChaosItems(lpObj,ITEMGET(14,13),ITEMGET(14,14),NO_CHECK_LVL,FALSE,FALSE);

	BYTE CountCheckSum = AmountChaos + AmountItems + AmountJewels;

	if (CountCheckSum != GetItemCount(lpObj) || AmountChaos < 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	/*Вычесление Rate*/

	DWORD iOldMoney = GetBuyMoneyItems(lpObj,TRUE,STARTIDITEMS,ENDIDITEMS);
	iOldMoney += GetBuyMoneyItems(lpObj,TRUE,ITEMGET(12,15),NULL_ENDID);
	iOldMoney += GetBuyMoneyItems(lpObj,TRUE,ITEMGET(14,13),ITEMGET(14,14));

	lpObj->ChaosSuccessRate = iOldMoney / DivValues.DivChaosWeapon;
	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;
	if (lpObj->ChaosSuccessRate > ConfRates.ChaosWeapon) lpObj->ChaosSuccessRate = ConfRates.ChaosWeapon;


	/*Снятие Zen*/

	if (this->DecZenChaosSystem(lpObj,lpObj->ChaosSuccessRate * ConfCostZen.ChaosWeapon) == FALSE) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		//Сварилось
		BYTE RandLevel = rand()%5;
		BYTE RandLuck = rand()%2;
		BYTE RandOpt = rand()%4;
		int Type;
		
		BYTE RandWings = rand()%3;

		if (RandWings == 0 ) Type = ITEMGET(2,6); //Chaos Dragon Axe
		if (RandWings == 1 ) Type = ITEMGET(4,6); //Chaos Nature Bow
		if (RandWings == 2 ) Type = ITEMGET(5,7); //Chaos Lighting Staff

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Type, RandLevel, 0, 0, RandLuck, RandOpt, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		//Сгорело
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::FirstWingsMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountChaosWeapon = this->CheckChaosItems(lpObj,ITEMGET(2,6));
	AmountChaosWeapon +=  this->CheckChaosItems(lpObj,ITEMGET(4,6));
	AmountChaosWeapon +=  this->CheckChaosItems(lpObj,ITEMGET(5,7));
	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmountJewels = this->CheckChaosItems(lpObj,ITEMGET(14,13),ITEMGET(14,14),NO_CHECK_LVL,FALSE,FALSE);
	BYTE AmountSubItem = this->CheckChaosItems(lpObj,STARTIDITEMS, ENDIDITEMS,NO_CHECK_LVL,FALSE,FALSE);

	BYTE AmountItems = this->GetItemCount(lpObj);

	BYTE CountCheckSum = AmountChaosWeapon + AmountChaos + AmountJewels + (AmountSubItem - AmountChaosWeapon);

	if (AmountItems != CountCheckSum || AmountChaosWeapon != 1 || AmountChaos < 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	/*Вычесление Rate*/

	DWORD BuyMoney = GetBuyMoneyItems(lpObj,TRUE,STARTIDITEMS, ENDIDITEMS);
	BuyMoney += GetBuyMoneyItems(lpObj,TRUE,ITEMGET(12,15),NULL_ENDID);
	BuyMoney += GetBuyMoneyItems(lpObj,TRUE,ITEMGET(14,13),ITEMGET(14,14));

	lpObj->ChaosSuccessRate = BuyMoney / DivValues.DivFirstWings;

	if ( lpObj->ChaosSuccessRate > ConfRates.FirstWings ) lpObj->ChaosSuccessRate = ConfRates.FirstWings;

	if (this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	/*Снятие Zen*/

	if (this->DecZenChaosSystem(lpObj,lpObj->ChaosSuccessRate * ConfCostZen.FirstWings) == FALSE )	return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		//Сварилось
		BYTE RandLevel = rand()%5;
		BYTE RandLuck = rand()%2;
		BYTE RandOpt = rand()%4;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,rand()%3), RandLevel, 0, 0, RandLuck, RandOpt, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		//Сгорело
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::SecondWingsMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountItems = this->GetItemCount(lpObj);
	BYTE AmountFistWings = this->CheckChaosItems(lpObj,ITEMGET(12,0),ITEMGET(12,2),NULL_ENDID,FALSE,FALSE);
	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmountLochsFeather = this->CheckChaosItems(lpObj,ITEMGET(13,14));
	BYTE AmountSubItem = this->CheckChaosItems(lpObj,STARTIDITEMS, ENDIDITEMS,NULL_ENDID,FALSE,FALSE);
	
	DWORD iMainMoney = this->GetBuyMoneyItems(lpObj,FALSE,ITEMGET(12,0),ITEMGET(12,2));
	DWORD iSubMoney = this->GetBuyMoneyItems(lpObj,FALSE,STARTIDITEMS, ENDIDITEMS);

	BYTE CountCheckSum =  AmountFistWings + AmountChaos + AmountLochsFeather + AmountSubItem;

	if (CountCheckSum != AmountItems || AmountChaos != 1 || AmountFistWings != 1 || AmountLochsFeather != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	// Проверяем начилие Creast of Monarch ( Lochs of Feather + 1 )
	BOOL CrstofMonarch = this->GetItemLevel(lpObj,ITEMGET(13,14));

	lpObj->ChaosSuccessRate = (iMainMoney / DivValues.MainDivSecondWings) + (iSubMoney / DivValues.SubDivSecondWings);
	if ( lpObj->ChaosSuccessRate > ConfRates.SecondWings ) lpObj->ChaosSuccessRate = ConfRates.SecondWings;
	if (this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.SecondWings) == FALSE) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		//Сварилось
		BYTE RandLevel = rand()%5;
		BYTE RandLuck = rand()%2;
		BYTE RandOpt = rand()%4;
		int Type;

		if (CrstofMonarch)
			Type = ITEMGET(13,30); //Cape Of Lord
		else
			Type = ITEMGET(12, rand()%4 + 3 );

		BYTE Exc = 0;

		BYTE RandExcOpt = rand()%100;

		if (RandExcOpt < this->SecondWingsExcRate)
		{
			BYTE CountOpt;
			RandExcOpt = rand()%100;

			if (RandExcOpt < 16) CountOpt = 6;
			else
				if (RandExcOpt < 32 ) CountOpt = 5;
				else
					if (RandExcOpt < 48 ) CountOpt = 4;
					else
						if (RandExcOpt < 64 ) CountOpt = 3;
						else
							if (RandExcOpt < 80 ) CountOpt = 2;
							else
								CountOpt = 1;

			if (CountOpt > this->SecondWingsMaxOpt ) CountOpt = this->SecondWingsMaxOpt;

			Exc = this->GetExcOpt(CountOpt);			
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Type, RandLevel, 0, 0, RandLuck, RandOpt, -1, Exc, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		//Сгорело
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::CondorMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountWings	= this->CheckChaosItems(lpObj, ITEMGET(12,3), ITEMGET(12,6), 9, FALSE, FALSE);
	BYTE AmountBundled	= this->CheckChaosItems(lpObj,ITEMGET(12,31));
	BYTE AmountCreation = this->CheckChaosItems(lpObj,ITEMGET(14,22));
	BYTE AmountChaos	= this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmountAncItem	= this->CheckChaosItems(lpObj,STARTIDITEMS,ENDIDITEMS,9,FALSE,TRUE);

	BYTE ItemCount = this->GetItemCount(lpObj);

	BYTE CheckSumItem = AmountWings + AmountBundled + AmountCreation + AmountChaos + AmountAncItem;
	
	if (CheckSumItem != ItemCount || AmountWings != 1 || AmountBundled != 1 || AmountCreation != 1 || AmountChaos != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}
	/*Вычесление Rate*/

	DWORD dBuyMoney2 = this->GetBuyMoneyItems(lpObj,FALSE,STARTIDITEMS,ENDIDITEMS);
	dBuyMoney2 = ( dBuyMoney2 + ( DivValues.DivCondor - (dBuyMoney2 % DivValues.DivCondor) ) );

	lpObj->ChaosSuccessRate =   dBuyMoney2 / DivValues.DivCondor;

	if (lpObj->ChaosSuccessRate > ConfRates.Condor ) lpObj->ChaosSuccessRate = ConfRates.Condor;

	if ( this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	/*Cнятие Zen*/

	if ( this->DecZenChaosSystem(lpObj,lpObj->ChaosSuccessRate * ConfCostZen.Condor) == FALSE ) return;

	srand(GetTickCount());

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,53), 0, 0, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		//Сгорело
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::ThirdWingsMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE AmountBundledSoul	= this->CheckChaosItems(lpObj,ITEMGET(12,31));
	BYTE AmountBundledBless = this->CheckChaosItems(lpObj,ITEMGET(12,30));
	BYTE AmountCreation = this->CheckChaosItems(lpObj,ITEMGET(14,22));
	BYTE AmountChaos	= this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE AmountFlameCondors  = this->CheckChaosItems(lpObj,ITEMGET(13,52));
	BYTE AmountFeatherCondors  = this->CheckChaosItems(lpObj,ITEMGET(13,53));
	BYTE AmountExcItems = this->CheckChaosItems(lpObj,STARTIDITEMS,ENDIDITEMS,9,TRUE,FALSE);

	BYTE ItemCount = this->GetItemCount(lpObj);

	BYTE CheckSum = AmountBundledSoul + AmountBundledBless + AmountCreation + AmountChaos + AmountFlameCondors + AmountFeatherCondors + AmountExcItems;

	if (CheckSum != ItemCount || AmountBundledSoul != 1 || AmountBundledBless != 1 	|| AmountCreation != 1 
		|| AmountChaos != 1 || AmountFlameCondors != 1 || AmountFeatherCondors != 1 )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	/*Вычесление Rate*/

	DWORD dBuyMoney = this->GetBuyMoneyItems(lpObj,FALSE,ITEMGET(0,0),ITEMGET(12,0) - 1);
	dBuyMoney = dBuyMoney + ( DivValues.DivThirdWings - (dBuyMoney % DivValues.DivThirdWings) );

	lpObj->ChaosSuccessRate = dBuyMoney / DivValues.DivThirdWings;

	if (lpObj->ChaosSuccessRate > ConfRates.ThirdWings) lpObj->ChaosSuccessRate = ConfRates.ThirdWings;

	if ( this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	/*Снятие Zen*/

	if (this->DecZenChaosSystem(lpObj,lpObj->ChaosSuccessRate * ConfCostZen.ThirdWings) != TRUE) return;

	srand(GetTickCount());

	if ( rand()%100 < lpObj->ChaosSuccessRate)
	{
		//Сварилось !!!!
		BYTE TypeWings = ITEMGET(12,rand()%5 + 36);
		BYTE Level = rand()%5;
		BYTE Opt = rand()%4 * 4;
		BYTE Luck = rand()%2;
		BYTE Exc = 0;

		BYTE RandExcOpt = rand()%100;

		if (RandExcOpt < this->ThirdWingsExcRate)
		{
			BYTE CountOpt;
			RandExcOpt = rand()%100;

			if (RandExcOpt < 16) CountOpt = 6;
			else
				if (RandExcOpt < 32 ) CountOpt = 5;
				else
					if (RandExcOpt < 48 ) CountOpt = 4;
					else
						if (RandExcOpt < 64 ) CountOpt = 3;
						else
							if (RandExcOpt < 80 ) CountOpt = 2;
							else
								CountOpt = 1;

			if (CountOpt > this->ThirdWingsMaxOpt ) CountOpt = this->ThirdWingsMaxOpt;

			Exc = this->GetExcOpt(CountOpt);			
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, TypeWings, Level, 0, 0, Luck, Opt, -1, Exc, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::DinorantMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	BYTE AmountUniria = 0;

	//Check Durability Uniria
	for (BYTE n = 0; n < 32; n ++)
		if (lpObj->pChaosBox[n].m_Type == ITEMGET(13,2) && lpObj->pChaosBox[n].m_Durability == 255.0f )
			AmountUniria++;

	BYTE AmountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE CheckSum = AmountUniria + AmountChaos;

	if (CheckSum != this->GetItemCount(lpObj) || AmountUniria != 10 || AmountChaos != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	lpObj->ChaosSuccessRate = ConfRates.Dinorant;
	if (this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.Dinorant) == FALSE ) return;

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		int Dinorant = ITEMGET(13,3);
		int Option3 = 0;

		if ( (rand()% 100) < 30 )
		{
			Option3 = 1 <<  ((rand()%3)) ;

			if ( (rand()%5) == 0 )  Option3 |= 1 << (rand()%3);
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Dinorant, 0, 255, 1, 0, Option3, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::UpgradeItemLevel(LPOBJ lpObj, BYTE MixType)
{
	BYTE NeedLevel;

	switch (MixType)
	{
	case 0x03:
		NeedLevel = 9;
		lpObj->ChaosSuccessRate = ConfRates.PlusLevel10;
		lpObj->ChaosMoney = ConfCostZen.PlusLevel10;
		break;
	case 0x04:
		NeedLevel = 10;
		lpObj->ChaosSuccessRate = ConfRates.PlusLevel11;;
		lpObj->ChaosMoney = ConfCostZen.PlusLevel11;
		break;
	case 0x16:
		NeedLevel = 11;
		lpObj->ChaosSuccessRate = ConfRates.PlusLevel12;;
		lpObj->ChaosMoney = ConfCostZen.PlusLevel12;
		break;
	case 0x17:
		NeedLevel = 12;
		lpObj->ChaosSuccessRate = ConfRates.PlusLevel13;;
		lpObj->ChaosMoney = ConfCostZen.PlusLevel13;
		break;
	default:
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
		return;
	}

	BYTE CountUpgItem = this->CheckChaosItems(lpObj,STARTIDITEMS,ENDIDITEMS,NO_CHECK_LVL,FALSE,FALSE);
	BYTE CountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE CountBless = this->CheckChaosItems(lpObj,ITEMGET(14,13));
	BYTE CountSoul = this->CheckChaosItems(lpObj,ITEMGET(14,14));

	BYTE NeedBlessSoul = NeedLevel - 8;

	if (CountBless != CountSoul || NeedBlessSoul != CountSoul || CountChaos != 1 || CountUpgItem != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	BYTE Source = 0;

	//Search Item
	for (BYTE n = 0; n < 32; n ++)
	{
		if (lpObj->pChaosBox[n].m_Type >= STARTIDITEMS && lpObj->pChaosBox[n].m_Type <= ENDIDITEMS)
			Source = n;
	}

	if (lpObj->pChaosBox[Source].m_Level != NeedLevel)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INVALID_ITEM_LEVEL);
		return;
	}

	if (lpObj->pChaosBox[Source].m_Option2 ) lpObj->ChaosSuccessRate += ConfRates.AddLuckItems;
	if (this->AddSuccessCharmSystem(lpObj) == FALSE) return;

	if (this->DecZenChaosSystem(lpObj,lpObj->ChaosMoney) == FALSE ) return;

	if (rand()%100 < lpObj->ChaosSuccessRate)
	{
		lpObj->pChaosBox[Source].m_Level++;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0,
			lpObj->pChaosBox[Source].m_Type,
			lpObj->pChaosBox[Source].m_Level,
			lpObj->pChaosBox[Source].m_Durability,
			lpObj->pChaosBox[Source].m_Option1,
			lpObj->pChaosBox[Source].m_Option2,
			lpObj->pChaosBox[Source].m_Option3,
			-1,
			lpObj->pChaosBox[Source].m_NewOption,
			lpObj->pChaosBox[Source].m_SetOption);

		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}
}

void cChaosBox::FruitMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE CreationCount = this->CheckChaosItems(lpObj,ITEMGET(14,22));
	BYTE ChaosCount = this->CheckChaosItems(lpObj,ITEMGET(14,22));

	if (CreationCount != 1 && ChaosCount != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.Fruit) == FALSE ) return;

	lpObj->ChaosSuccessRate = ConfRates.Fruit;

	if (this->AddSuccessCharmSystem(lpObj) == FALSE ) return;

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0,  ITEMGET(13,15), rand()%100 / 20, 255, 1, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::LifeStoneMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE CountBless = this->CheckChaosItems(lpObj,ITEMGET(14,13));
	BYTE CountSoul = this->CheckChaosItems(lpObj,ITEMGET(14,14));
	BYTE CountGuardian = this->CheckChaosItems(lpObj,ITEMGET(14,31));
	BYTE CountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));

	BYTE CountItems = this->GetItemCount(lpObj);

	BYTE CheckSum = CountChaos + CountGuardian + CountSoul + CountBless;

	if (CheckSum != CountItems || CountChaos != 1 || CountGuardian != 1 || CountSoul != 5 || CountBless != 5)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	if (this->DecZenChaosSystem(lpObj,ConfCostZen.LifeStone) == FALSE ) return; 

	lpObj->ChaosSuccessRate = ConfRates.LifeStone;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,11) , 1, 0, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

/*Неработает! Рецепта нету в mix.bmd Кристалов нету в самом клиенте*/
void cChaosBox::HTBoxMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE BlueCrystal = 0;
	BYTE RedCrystal = 0;
	BYTE BlackCrystal = 0;

	for (BYTE n = 0; n < CHAOS_BOX_SIZE; n++)
	{
		if (lpObj->pChaosBox[n].m_Type == ITEMGET(12,26))
		{
			if (lpObj->pChaosBox[n].m_Level == 1 ) RedCrystal++;
			if (lpObj->pChaosBox[n].m_Level == 2 ) BlueCrystal++;
			if (lpObj->pChaosBox[n].m_Level == 3 ) BlackCrystal++;
		}
	}

	if (RedCrystal + BlueCrystal + BlackCrystal != this->GetItemCount(lpObj))
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	BYTE bCrystalMixType = -1;

	if (BlueCrystal == 7 && !RedCrystal && !BlackCrystal) bCrystalMixType = 0;
	if (!BlueCrystal && RedCrystal == 5 && !BlackCrystal) bCrystalMixType = 1;
	if (!BlueCrystal && !RedCrystal && BlackCrystal == 3) bCrystalMixType = 2;
	if (BlueCrystal == 1 && RedCrystal == 1 && BlackCrystal == 1) bCrystalMixType = 3;

	lpObj->ChaosSuccessRate = 100;
	//Неработает микс, пока конфиг выносить ненада!

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		switch ( bCrystalMixType )
		{
		case 0:	case 1:	case 2:
			ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 4, 1, 0, 0, 0, -1, 0, 0);
			break;
		case 3:
			ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 5, 1, 0, 0, 0, -1, 0, 0);
			break;
		default:
			this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
			return;
		}

		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}
	lpObj->ChaosLock = FALSE;
}

//Скопипастил (не переписанный)
void cChaosBox::CastleItemMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int iDefendGemCount = 0;
	int iBlessGemMixCount = 0;
	int iSoulGemMixCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( g_CastleSiegeSync.CheckCastleOwnerMember(lpObj->m_Index) )
	{
		if ( lpObj->GuildStatus != GUILD_MASTER )
		{
			LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - No Auth",
				lpObj->AccountID, lpObj->Name);

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			return;
		}
	}
	else
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - No Auth",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if (Configs.g_iCastleItemMixLimit <= 0)
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Mix Count Limit Over",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	for ( int n = 0; n<CHAOS_BOX_SIZE ; n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,30) )
			{
				iBlessGemMixCount += lpObj->pChaosBox[n].m_Level+1;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,31) )
			{
				iSoulGemMixCount += lpObj->pChaosBox[n].m_Level+1;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,31) )
			{
				iDefendGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iBlessGemMixCount != 3 || iSoulGemMixCount != 3 || iDefendGemCount != 30 || iInvalidItemCount > 0 )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Item Error (DG:%d, BGx10:%d, SGx10:%d, Other:%d)",	// #error Deathway wrong Translation
			lpObj->AccountID, lpObj->Name, iBlessGemMixCount, iSoulGemMixCount, iDefendGemCount, iInvalidItemCount);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	//LogChaosItem(lpObj, "Castle Special Mix");
	LogAddTD("[CastleSpecialMix] [%s][%s] Chaos Mix Start",
		lpObj->AccountID, lpObj->Name);

	lpObj->ChaosSuccessRate = 100;
	int nChaosNeedMoney = 1000000000;
	if ( lpObj->Money < nChaosNeedMoney )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Lack of Money (%d/%d)",
			lpObj->AccountID, lpObj->Name, lpObj->Money, nChaosNeedMoney);

		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	CItem objTempItem;
	int nItemIndex;
	int iPickLoopCount = 500;
	bool bItemPickSuccess = false;

	while ( iPickLoopCount-- )
	{
		if ( CastleItemMixItemBag->PickItem(objTempItem, nItemIndex) == FALSE )
		{
			LogAddTD("[CastleSpecialMix] [%s][%s] Item Pick Failed - Data Error",
				lpObj->AccountID, lpObj->Name);

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			return;
		}

		int iMinLevel = CastleItemMixItemBag->GetMinLevel(nItemIndex);
		if ( iMinLevel < (rand()%100) )
		{
			bItemPickSuccess = true;
			break;
		}
	}

	if ( bItemPickSuccess == false )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Pick Failed - Loop Count Over",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	objTempItem.m_Level = 0;

	if ( objTempItem.m_NewOption )
	{
		objTempItem.m_NewOption = 0;
		int iRND = (rand() % 3) + 2;

		while ( iRND )
		{
			int iExcOptionType = rand() % 6;
			BYTE btExcOption = 1  << iExcOptionType;

			if ( (objTempItem.m_NewOption & btExcOption ) == 0 )
			{
				objTempItem.m_NewOption |= btExcOption;
				iRND--;
			}
		}

		objTempItem.m_Option1 = 1;
		if ( (rand()%100) < 20 )
			objTempItem.m_Option2 = 1;
		else
			objTempItem.m_Option2 = 0;
	}
	else
	{
		objTempItem.m_Option2 = 1;
	}

	objTempItem.m_Durability = ItemGetDurability(objTempItem.m_Type,
		objTempItem.m_Level,objTempItem.m_NewOption,0);
	lpObj->Money -= nChaosNeedMoney;

	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, 0xFF, 0, 0, objTempItem.m_Type, objTempItem.m_Level,
			objTempItem.m_Durability, objTempItem.m_Option1, objTempItem.m_Option2,
			objTempItem.m_Option3, -1, objTempItem.m_NewOption, 0);

		gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[CastleSpecialMix] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney);

		Configs.g_iCastleItemMixLimit--;
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[CastleSpecialMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::FenrirMixPart1(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE SplinterofArmor = this->GetDurability(lpObj,ITEMGET(13,32));
	BYTE BlessOfGuardian = this->GetDurability(lpObj,ITEMGET(13,33));
	BYTE ChaosCount = this->CheckChaosItems(lpObj,ITEMGET(12,15));

	if ( this->GetItemCount(lpObj) != 3 || SplinterofArmor != 20 || BlessOfGuardian != 20 || ChaosCount != 1 )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	lpObj->ChaosSuccessRate = ConfRates.FenrirLvl1;

	if (!this->DecZenChaosSystem(lpObj,ConfCostZen.FenrirLvl1)) return;
	if (!this->AddSuccessCharmSystem(lpObj)) return;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,35) , 0, 1, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		this->ChaosBoxClear(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::FenrirMixPart2(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE FragmentCount = this->CheckChaosItems(lpObj,ITEMGET(13,35));
	BYTE ClawOfBeast = this->GetDurability(lpObj,ITEMGET(13,34));
	BYTE ChaosCount = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE CheckSum = FragmentCount  + ChaosCount;

	if (this->GetItemCount(lpObj) != 7 || FragmentCount != 5 || ClawOfBeast != 10 || ChaosCount != 1 )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	lpObj->ChaosSuccessRate = ConfRates.FenrirLvl2;

	if (!this->DecZenChaosSystem(lpObj,ConfCostZen.FenrirLvl2)) return;
	if (!this->AddSuccessCharmSystem(lpObj)) return;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,36) , 0, 1, 0, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::FenrirMixPart3(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	BYTE BrokenHorn = this->CheckChaosItems(lpObj,ITEMGET(13,36));
	BYTE LifeCount = this->CheckChaosItems(lpObj,ITEMGET(14,16));
	BYTE ChaosCount = this->CheckChaosItems(lpObj,ITEMGET(12,15));
	BYTE CheckSumItem = BrokenHorn + LifeCount + ChaosCount;

	if (CheckSumItem != this->GetItemCount(lpObj) || BrokenHorn != 1 || LifeCount != 3 || ChaosCount != 1)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	lpObj->ChaosSuccessRate = ConfRates.FenrirLvl3;

	if (!this->AddSuccessCharmSystem(lpObj)) return;

	if (!this->DecZenChaosSystem(lpObj,ConfCostZen.FenrirLvl3)) return;

	if ( rand()%100 < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,37) , 0, 255, 1, 0, 0, -1, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::FenrirMixPart4(LPOBJ lpObj)
{
	BYTE CountFenrir = this->CheckChaosItems(lpObj,ITEMGET(13,37));
	BYTE CountLife = this->CheckChaosItems(lpObj,ITEMGET(14,16));
	BYTE CountChaos = this->CheckChaosItems(lpObj,ITEMGET(12,15));

	BYTE CountWeapons = this->CheckChaosItems(lpObj,STARTIDITEMS,ITEMGET(11,511),4,FALSE,FALSE);
	BYTE CountDefItems = this->CheckChaosItems(lpObj,ITEMGET(6,0),ENDIDITEMS,4,FALSE,FALSE);

	DWORD AttackStuffPrice = this->GetBuyMoneyItems(lpObj,FALSE,STARTIDITEMS,ITEMGET(11,511));
	DWORD DefStuffPrice = this->GetBuyMoneyItems(lpObj,FALSE,ITEMGET(6,0),ENDIDITEMS);

	BYTE CheckSumm = CountFenrir + CountLife + CountChaos + CountWeapons + CountDefItems;

	if (CheckSumm != this->GetItemCount(lpObj) | CountFenrir != 1 || CountLife != 5 || CountChaos != 1 
		|| (CountDefItems + CountWeapons) == 0 || (CountDefItems > 0 && CountWeapons > 0 ) )
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	/*Узнаем какой фенрир будет (для атаки или защиты)*/
	BOOL bFenrirDamageInc =  (CountWeapons > 0 ) ? TRUE : FALSE;
	/*Выбираем BuyMoney Итема в зависимости bFenrirDamageInc*/
	DWORD ChaosMoney = (bFenrirDamageInc) ? AttackStuffPrice : DefStuffPrice;

	/*Формула вычесления рейта*/

	lpObj->ChaosSuccessRate = ChaosMoney * DivValues.FisrtDivFenrir4 / DivValues.SecondDivFenrir4;

	/*Не вышел ли рейт за предел ?*/
	if (lpObj->ChaosSuccessRate > ConfRates.FenrirLvl4 ) lpObj->ChaosSuccessRate = ConfRates.FenrirLvl4;

	/*Charm System*/
	if (!this->AddSuccessCharmSystem(lpObj)) return;

	if (!this->DecZenChaosSystem(lpObj,ConfCostZen.FenrirLvl4)) return;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		BYTE nop = (bFenrirDamageInc) ? 1 : 2;		
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,37) , 0, 255, 1, 0, 0, -1, nop, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

void cChaosBox::ShieldPotionMix(LPOBJ lpObj,int MixType)
{
	lpObj->ChaosLock = TRUE;

	int SearchType = 0;
	DWORD dNeedMoney = 0;
	int PrizeType = 0;

	switch (MixType)
	{
	case CHAOS_TYPE_COMPOUNDPOTION_LV1: /*Small SD Potion*/
		SearchType = ITEMGET(14,3);
		lpObj->ChaosSuccessRate = ConfRates.ShieldPotionLvl1;
		dNeedMoney = ConfCostZen.ShieldPotionLvl1;
		PrizeType = ITEMGET(14,35);
		break;
	case CHAOS_TYPE_COMPOUNTPOTION_LV2: /*Medium SD Potion*/
		SearchType = ITEMGET(14,38);
		lpObj->ChaosSuccessRate = ConfRates.ShieldPotionLvl2;
		dNeedMoney = ConfCostZen.ShieldPotionLvl2;
		PrizeType = ITEMGET(14,36);
		break;
	case CHAOS_TYPE_COMPOUNTPOTION_LV3: /*Large SD Potion*/
		SearchType = ITEMGET(14,39);
		lpObj->ChaosSuccessRate = ConfRates.ShieldPotionLvl3;
		dNeedMoney = ConfCostZen.ShieldPotionLvl3;
		PrizeType = ITEMGET(14,37);
		break;
	default:
		return;
	}

	BYTE HealthPotionCount = this->GetDurability(lpObj,SearchType);
	BYTE PotionItems = this->CheckChaosItems(lpObj,SearchType);

	if (this->GetItemCount(lpObj) != PotionItems && HealthPotionCount != 3)
	{
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_INCORRECT_MIX_ITEMS);
		return;
	}

	if (!this->DecZenChaosSystem(lpObj,dNeedMoney)) return;

	if (!this->AddSuccessCharmSystem(lpObj)) return;

	if ( rand()%100 < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, PrizeType, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		this->MessageDataSend(lpObj,CHAOS_TYPE_MSG::CB_ERROR);
	}

	lpObj->ChaosLock = FALSE;
}

int cChaosBox::GetExcOpt(int amount)
{
	// User input errors
	if (amount > 6) amount = 6;
	if (amount < 1) amount = 1;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	std::random_shuffle(opt_db, opt_db + 6);

	for(int n=0; n < amount; n++)
	{
		exc += opt_db[n];
	}

	return exc;
}