#include "StdAfx.h"
#include "CashShop.h"
#include "DSProtocol.h"
BOOL g_bUseCashShop = FALSE;
BOOL g_bConnectShopServer = FALSE;
BOOL g_bShopServerConnectState = FALSE;
BOOL g_bUseLotteryEvent = FALSE;
char g_ShopServerIP[16] ={0};
BOOL g_bUseMoveMapBound = FALSE;
WNDPROC CCashShop::m_lpOldProc = NULL;

CCashShop g_CashShop;
wsShopServerCli g_ShopServerClient;
//#TODO ÑÐÀÂÍÈÒÜ ÔÀÉËÛ
int g_ShopserverPort = 0;	// Belong to anithr part of GameMain?



void ShopServerProtocolCore(DWORD protoNum, LPBYTE aRecv, int aLen)
{
	switch ( protoNum )
	{
		case 0x200:SGAnsCashPoint((protocol::MSG_STOG_USER_CASH_ANS *)aRecv);break;
		case 0x400:SGAnsCashItemList((protocol::MSG_STOG_ITEM_LIST_ANS *)aRecv);break;
		case 0x600:SGAnsPackageItemList((protocol::MSG_STOG_PACKAGE_LIST_ANS *)aRecv);break;
		case 0x800:SGAnsBranchItemList((protocol::MSG_STOG_BRANCH_ITEM_LIST_ANS *)aRecv);break;
		case 0xE00:g_CashShop.CashShopOptioNReload();break;
		case 0xA00:SGAnsBuyCashItem((protocol::MSG_STOG_BUY_ITEM_ANS *)aRecv);break;
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CCashShop::CCashShop()
{
	return;
}

CCashShop::~CCashShop()
{
	return;
}



void CCashShop::Initialize()
{
	int i = 0;
	int j = 0;
	int k = 0;

	this->iCashItemCount = 0;
	this->iCashItemPageNumber = 0;
	this->bCashItemListReload = FALSE;
	this->iBranchItemCount = 0;
	this->MapUserObject.clear();
	this->MapCashItemList.clear();
	this->MapCashItemStatus.clear();

	for ( i=0; i<MAX_CASH_SHOP_CATEGORY;i++)
		this->iCashItemCountInCategory[i] = 0;

	for ( i=0; i<MAX_CASH_SHOP_CATEGORY;i++)
	{
		for (j=0;j<MAX_CASH_SHOP_PROTOCOL;j++)
		{
			this->CashItemProtocol[i][j].btItemCount =0;
			this->CashItemProtocol[i][j].btCategoryIndex = 0;
			this->CashItemProtocol[i][j].btPageIndex = 0;

			for ( k=0;k<MAX_CASH_SHOP_PROTOCOL_DATA;k++)
			{
				this->CashItemProtocol[i][j].ItemInfo[k].dwItemGuid = 0;
				this->CashItemProtocol[i][j].ItemInfo[k].btCategoryCode = 0;
				this->CashItemProtocol[i][j].ItemInfo[k].btItemSaleRatio = 0;
				this->CashItemProtocol[i][j].ItemInfo[k].wItemPrice = 0;
				memset(this->CashItemProtocol[i][j].ItemInfo[k].btItemInfo, 0, sizeof(this->CashItemProtocol[i][j].ItemInfo[k].btItemInfo));
			}
		}
	}

	for ( i=0; i<MAX_CASH_SHOP_CATEGORY;i++)
	{
		for (j=0;j<MAX_CASH_SHOP_ITEM;j++)
		{
			this->CashItemList[i][j].dwItemGuid = 0;
			this->CashItemList[i][j].dwPriceGuid = 0;
			this->CashItemList[i][j].btCategoryCode = 0;
			this->CashItemList[i][j].btItemType = 0;
			this->CashItemList[i][j].wItemIndex = 0;
			this->CashItemList[i][j].btItemLevel = 0;
			this->CashItemList[i][j].btItemDuration = 0;
			this->CashItemList[i][j].btItemLuckOption = 0;
			this->CashItemList[i][j].btItemSkillOpion = 0;
			this->CashItemList[i][j].btItemAddOption = 0;
			this->CashItemList[i][j].btItemSaleRatio = 0;
			this->CashItemList[i][j].wItemPrice = 0;
			memset(this->CashItemList[i][j].btItemInfo, 0, sizeof(this->CashItemList[i][j].btItemInfo));
		}
	}

	for ( i=0; i<MAX_CASH_ITEM_BRANCH;i++)
	{
		this->BranchItemList[i].dwItemGuid = 0;
		this->BranchItemList[i].iBranchType = -1;
	}
}




void CCashShop::CashShopOptioNReload() //GS-CS Decompiled 100%
{
	this->bCashItemListReload = TRUE;

	LogAddTD("[CashShop][OptionLoad] - CashShop Option Load Begin");

	this->LoadShopOption(gDirPath.GetNewPath("CashShopOption.dat"));
	this->Load(gDirPath.GetNewPath("CashShopList.txt"));
	this->ReConnectShopServer(); //Good
	this->GSReqBranchItemList();
	this->GSReqCashItemList();
	this->GSReqPackageItemList();

	LogAddTD("[CashShop][OptionLoad] - CashShop Option Load finish");

	this->bCashItemListReload = FALSE;
}




void CCashShop::Load(LPSTR pchFilename)
{
	SMDToken Token;

	SMDFile = fopen(pchFilename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("[CashItemList] Cash Item List load failed. [%s]", pchFilename);
		return;
	}

	this->Initialize();

	int iType = 0;
	int iItemCode = 0;
	BYTE btItemType = 0;
	WORD wItemIndex = 0;
	BYTE btItemLevel = 0;
	BYTE btItemSkillOpion = 0;
	BYTE btItemLuckOption = 0;
	BYTE btItemAddOption = 0;
	BYTE btItemExOption = 0;
	BYTE btItemX = 0;
	BYTE btItemY = 0;
	BYTE btItemScale = 0;
	CASHSHOP_ITEM_STATUS ItemStatus;
	BOOL bResult = 0;

	while ( true )
	{
		Token = (SMDToken)GetToken();

		if ( Token == END )
			break;

		iType = TokenNumber;

		while ( true )
		{
			Token = (SMDToken)GetToken();

			if ( Token == END )
				break;
		
			if ( iType == 1 )
			{
				if ( !strcmp("end", TokenString) )
					break;

				ItemStatus.btItemType = TokenNumber;

				Token = (SMDToken)GetToken();
				ItemStatus.wItemIndex = TokenNumber;

				Token = (SMDToken)GetToken();
				ItemStatus.btItemLevel = TokenNumber;


				Token = (SMDToken)GetToken();
				ItemStatus.btSkillOption = TokenNumber;

				Token = (SMDToken)GetToken();
				ItemStatus.btLuckOption = TokenNumber;

				Token = (SMDToken)GetToken();
				ItemStatus.btAddOption = TokenNumber;

				BYTE btExOptionValue = 0;
				BYTE btExOption = 0;

				Token = (SMDToken)GetToken();
				ItemStatus.btExOption = TokenNumber;
/*
				if ( btItemExOption > 0 )
				{
					btExOptionValue = 1 << (int)(btItemExOption-1);
					btExOption |= btExOptionValue;
					ItemStatus.btExOption = btExOption;
				}
				else
				{
					ItemStatus.btExOption = 0;
				}
*/
				Token = (SMDToken)GetToken();
				btItemX = TokenNumber;

				Token = (SMDToken)GetToken();
				btItemY = TokenNumber;

				Token = (SMDToken)GetToken();
				btItemScale = TokenNumber;

				iItemCode = ITEMGET(ItemStatus.btItemType , ItemStatus.wItemIndex);
				ItemStatus.btDurability = ItemGetDurability(iItemCode, ItemStatus.btItemLevel, ItemStatus.btExOption, 0);

				ItemByteConvert(ItemStatus.btItemInfo, iItemCode, ItemStatus.btSkillOption,
					ItemStatus.btLuckOption, ItemStatus.btAddOption,
					ItemStatus.btItemLevel, 1, ItemStatus.btExOption, 0, 0, 0);
				
				LogAddTD("[CashShop][Load Cash Item List] - Add List - (%d/%d) Level:%d, Dur:%d, Skill:%d, Luck:%d, Add:%d, Ex:%d, X:%d, Y:%d, Scale:%d",
					ItemStatus.btItemType, ItemStatus.wItemIndex, ItemStatus.btItemLevel, ItemStatus.btDurability,
					ItemStatus.btSkillOption, ItemStatus.btLuckOption, ItemStatus.btAddOption, ItemStatus.btExOption, 
					btItemX, btItemY, btItemScale);

				this->InsertItemStatus(&ItemStatus);
			}
		}
	}

	LogAddTD("[CashShop][Load Cash Item List] - Complete! - Total:%d",
		this->MapCashItemStatus.size());

	if ( g_bConnectShopServer == TRUE && g_bShopServerConnectState == FALSE)
	{
		g_bShopServerConnectState = this->ConnectShopServer(g_ShopServerIP, g_ShopserverPort);

		if ( g_bShopServerConnectState == FALSE )
		{
			MsgBox("[CashShop] Shop Server Connect Failed!!");
		}
	}
}




void CCashShop::LoadShopOption(LPSTR pchFilename)
{
	LogAddTD("[CashShop][ShopOption] - Shop Option Reload '%s'", pchFilename);

	g_bUseCashShop = GetPrivateProfileInt("CashShopOption", "UseCashShop", 0, pchFilename);
	g_bConnectShopServer = GetPrivateProfileInt("CashShopOption", "ConnectShopServer", 0, pchFilename);
	g_bUseLotteryEvent = GetPrivateProfileInt("CashShopOption", "UseLotteryEvent", 0, pchFilename);
	GetPrivateProfileString("CashShopOption", "ShopServerIP", "0", g_ShopServerIP, 16, pchFilename);
	g_ShopserverPort = GetPrivateProfileInt("CashShopOption", "ShopServerPort", 0, pchFilename);
	g_bUseMoveMapBound = GetPrivateProfileInt("CashShopOption", "MapMoveBoundCheck", 0, pchFilename);
}




void CCashShop::LoadTestScript(LPSTR pchFilename)
{
	SMDToken Token;

	SMDFile = fopen(pchFilename, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("[CashItemList] Cash Item List load failed. [%s]", pchFilename);
		return;
	}

	//this->Initialize();

	int iType = 0;
	int iGuid = 0;
	int iCategory = 0;
	BYTE btItemType = 0;
	WORD wItemIndex = 0;
	BYTE btSaleRatio = 0;
	BYTE btDuration = 0;
	WORD wPrice = 0;
	int iItemInfoCount = 1;
	protocol::MSG_STOG_ITEM_LIST_ANS pMsg;

	while ( true )
	{
		Token = (SMDToken)GetToken();

		if ( Token == END )
		{
			break;
		}

		iType = TokenNumber;

		while ( true )
		{

			Token = (SMDToken)GetToken();

			if ( Token == END )
			{
				break;
			}

			if ( iType == 1 )
			{
				if ( !strcmp("end", TokenString) )
					break;

				iGuid = TokenNumber;
				iGuid = iItemInfoCount;

				Token = (SMDToken)GetToken();
				iCategory = TokenNumber;

				Token = (SMDToken)GetToken();
				btItemType = TokenNumber;

				Token = (SMDToken)GetToken();
				wItemIndex = TokenNumber;

				Token = (SMDToken)GetToken();
				btSaleRatio = TokenNumber;

				Token = (SMDToken)GetToken();
				btDuration = TokenNumber;

				Token = (SMDToken)GetToken();
				wPrice = TokenNumber;

				pMsg.dwItemCount = 1;
				pMsg.sellItems[0].dwItemGuid = iItemInfoCount;
				pMsg.sellItems[0].dwCategoryID = iCategory;
				pMsg.sellItems[0].dwItemCODE = ITEMGET(btItemType, wItemIndex);
				pMsg.sellItems[0].dwCoolTime = 0;
				pMsg.sellItems[0].dwBuyType = 1;
				pMsg.sellItems[0].dwLimitSellCount = 100;
				pMsg.sellItems[0].dwPriceCount = 1;
				pMsg.sellItems[0].dwState = 1;
				pMsg.sellItems[0].dwUseType = 2;
				pMsg.sellItems[0].itemPrice[0].dwItemGuid = iItemInfoCount;
				pMsg.sellItems[0].itemPrice[0].dwPrice = wPrice;
				pMsg.sellItems[0].itemPrice[0].dwPriceGuid = iGuid;
				pMsg.sellItems[0].itemPrice[0].dwSellRate = btSaleRatio;
				pMsg.sellItems[0].itemPrice[0].dwUseTime = 1;
				pMsg.sellItems[0].itemPrice[0].dwAmount = btDuration;

				this->SetItemInfoFromShop(&pMsg);
				this->MakeItemListProtocol();
				iItemInfoCount++;
			}
		}
	}
}


BOOL CCashShop::ConnectShopServer(LPSTR pchIpAddress, int iPortNumber)
{
	if ( g_ShopServerClient.CreateSocket(ghWnd) == FALSE )
		return FALSE;

	if ( !g_ShopServerClient.SetProtocolCore(ShopServerProtocolCore) )
		return FALSE;

	CCashShop::m_lpOldProc = (WNDPROC)SetWindowLong(ghWnd, GWL_WNDPROC, (LONG)CCashShop::ParentWndProc);

	if ( !g_ShopServerClient.Connect(pchIpAddress, iPortNumber, 0x41E) )
		return FALSE;

	return TRUE;
}



BOOL CCashShop::ReConnectShopServer()
{
	g_ShopServerClient.Close();

	if ( g_ShopServerClient.CreateSocket(ghWnd) == FALSE )
		return FALSE;

	if ( !g_ShopServerClient.SetProtocolCore(ShopServerProtocolCore) )
		return FALSE;

	if ( !g_ShopServerClient.Connect(g_ShopServerIP, g_ShopserverPort, 0x41E) )
		return FALSE;

	return TRUE;
}


long CCashShop::ParentWndProc(HWND hWnd, UINT iMessage, UINT wParam, long lParam)
{
	switch( iMessage )
	{
		case 0x41E:
			switch ( lParam & 0xFFFF & 0xFFFF )
			{
				case 1:
					g_ShopServerClient.DataRecv();
					return 0;

				case 16:
					LogAddTD("[ShopServer] - Connect To Shop Server!!");
					g_bShopServerConnectState = TRUE;
					return 0;

				case 32:
					g_ShopServerClient.Close();
					LogAddC(2, "[ShopServer] - Disconnect From Shop Server!!");
					g_bShopServerConnectState = FALSE;
					return 0;

			}
			return 0;

		default:
			return CallWindowProc(CCashShop::m_lpOldProc, hWnd, iMessage, wParam, lParam);
	}
}




void CCashShop::CheckShopServerConnectState()
{
	if ( g_bConnectShopServer == FALSE )
		return;

	if ( (GetTickCount()-this->dwCheckShopServerConnectStatePeriod) > 10000 )
	{
		this->dwCheckShopServerConnectStatePeriod = GetTickCount();

		if ( g_bShopServerConnectState == FALSE )
		{
			g_bShopServerConnectState = this->ReConnectShopServer();

			if ( g_bShopServerConnectState == FALSE )
			{
				LogAddC(2, "[CashShop][ShopServer] - Disconnect From Shop Server!!");
			}
		}
	}
}



BOOL CCashShop::InsertItemStatus(CASHSHOP_ITEM_STATUS * lpItemStatus)
{
	int iItemCode = 0;
	CASHSHOP_ITEM_STATUS * lpNewItemStatus = new CASHSHOP_ITEM_STATUS;

	memcpy(lpNewItemStatus, lpItemStatus, sizeof(CASHSHOP_ITEM_STATUS));

	iItemCode = ITEMGET(lpItemStatus->btItemType, lpItemStatus->wItemIndex);

	this->MapCashItemStatus.insert(std::pair<int, CASHSHOP_ITEM_STATUS *>(iItemCode, lpNewItemStatus));

	return TRUE;
}


BOOL CCashShop::SetItemInfoFromShop(protocol::MSG_STOG_ITEM_LIST_ANS * lpMsg)
{
	int iItemCount = 0;
	iItemCount = lpMsg->dwItemCount;


	if ( iItemCount == 0 )
		return FALSE;

	int iItemCode = 0;
	int iItemPriceCount = 0;
	CASHSHOP_ITEM_STATUS * lpItemStatus = NULL;

	for (int i=0;i<iItemCount;i++)
	{
		if ( this->CheckValidItemInfo(&lpMsg->sellItems[i]) == FALSE )
		{
			LogAddTD("[CashShop] Invalid Item Info from ShopServer (GUID:%d,Category:%d,ItemCode:%d,Price:%d)",
				lpMsg->sellItems[i].dwItemGuid, lpMsg->sellItems[i].dwCategoryID, lpMsg->sellItems[i].dwItemCODE,
				lpMsg->sellItems[i].itemPrice[0].dwPrice);	// #error Apply Deathwya Fix  HEre

			continue;
		}

		iItemCode = lpMsg->sellItems[i].dwItemCODE;
		lpItemStatus = this->GetCashItemStatus(iItemCode);

		if ( lpItemStatus == NULL )
		{
			LogAddTD("[CashShop] Can not Find Item Status (Code : %d)", iItemCode);
			continue;
		}

		this->MakeItemList(lpItemStatus, &lpMsg->sellItems[i]);
	}

	return TRUE;
}




BOOL CCashShop::SetPackageItemInfoFromShop(protocol::MSG_STOG_PACKAGE_LIST_ANS * lpMsg)
{
	return TRUE;
}



BOOL CCashShop::CheckValidItemInfo(sellItem * lpItemInfo)
{
	if ( lpItemInfo->dwItemGuid < 0 )
		return FALSE;

	if ( lpItemInfo->dwPriceCount <= 0 || lpItemInfo->dwPriceCount > 8 )
		return FALSE;

	if ( lpItemInfo->dwCategoryID < 0 || lpItemInfo->dwCategoryID > MAX_CASH_SHOP_CATEGORY )
	{
		lpItemInfo->dwCategoryID = 0;
		return FALSE;
	}

	return TRUE;
}


CASHSHOP_ITEM_STATUS * CCashShop::GetCashItemStatus(int iItemCode)
{
	CASHSHOP_ITEM_STATUS * lpReturn = NULL;
	std::map<int, CASHSHOP_ITEM_STATUS *>::iterator Iter;

	Iter = this->MapCashItemStatus.find(iItemCode);

	if ( Iter == this->MapCashItemStatus.end() )
	{
		return FALSE;
	}

	lpReturn = Iter->second;

	return lpReturn;
}



BOOL CCashShop::IsGetAmountFromShopItem(int iItemCode) //GS-CS Weird Compilation
{
	switch ( iItemCode )
	{
		case ITEMGET(14,53):

		case ITEMGET(13,46):
		case ITEMGET(13,47):
		case ITEMGET(13,48):

		case ITEMGET(14,70): //CashShop HP Potion
	
		return TRUE;
	}

	return FALSE;
}




void CCashShop::MakeItemList(CASHSHOP_ITEM_STATUS * lpItemStatus, sellItem * lpItemSellInfo)
{
	int iIndex = 0;
	int iItemCount = lpItemSellInfo->dwPriceCount;
	int iCategory = lpItemSellInfo->dwCategoryID;
	int iItemIndex = this->iCashItemCountInCategory[iCategory];
	int iBranchType = 0;
	int iItemPrice = 0;
	int iItemSaleRate = 0;

	for ( iIndex=0;iIndex<iItemCount;iIndex++)
	{
		iBranchType = this->GetBranchType(lpItemSellInfo->dwItemGuid);
		this->CashItemList[iCategory][iItemIndex+iIndex].dwItemGuid = lpItemSellInfo->dwItemGuid;
		this->CashItemList[iCategory][iItemIndex+iIndex].dwPriceGuid = lpItemSellInfo->itemPrice[iIndex].dwPriceGuid;
		this->CashItemList[iCategory][iItemIndex+iIndex].btCategoryCode = iCategory;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemType = lpItemStatus->btItemType;
		this->CashItemList[iCategory][iItemIndex+iIndex].wItemIndex = lpItemStatus->wItemIndex;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemLevel = lpItemStatus->btItemLevel;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemAddOption = lpItemStatus->btAddOption;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemLuckOption = lpItemStatus->btLuckOption;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemSkillOpion = lpItemStatus->btSkillOption;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemExOption = lpItemStatus->btExOption;
		this->CashItemList[iCategory][iItemIndex+iIndex].btItemUsedType = lpItemSellInfo->dwUseType;
		this->CashItemList[iCategory][iItemIndex+iIndex].btSpecialOption = iBranchType;


		if ( this->IsGetAmountFromShopItem(ITEMGET(lpItemStatus->btItemType, lpItemStatus->wItemIndex)) == TRUE )
		{
			this->CashItemList[iCategory][iItemIndex+iIndex].btItemDuration = lpItemSellInfo->itemPrice[iIndex].dwAmount;
		}
		else
		{
			this->CashItemList[iCategory][iItemIndex+iIndex].btItemDuration = lpItemStatus->btDurability;
		}

		this->CashItemList[iCategory][iItemIndex+iIndex].btItemSaleRatio = lpItemSellInfo->itemPrice[iIndex].dwSellRate;
		this->CashItemList[iCategory][iItemIndex+iIndex].wItemPrice = lpItemSellInfo->itemPrice[iIndex].dwPrice;
		this->CashItemList[iCategory][iItemIndex+iIndex].dwItemUsePeriod = lpItemSellInfo->itemPrice[iIndex].dwUseTime;
		memcpy(this->CashItemList[iCategory][iItemIndex+iIndex].btItemInfo, lpItemStatus->btItemInfo, sizeof(lpItemStatus->btItemInfo));


		this->CashItemList[iCategory][iItemIndex+iIndex].ItemInfo.Convert(ITEMGET(lpItemStatus->btItemType, lpItemStatus->wItemIndex),
			lpItemStatus->btSkillOption, lpItemStatus->btLuckOption, lpItemStatus->btAddOption, lpItemStatus->btExOption, 0, 0, CURRENT_DB_VERSION);

		this->MapCashItemList.insert(std::pair<int, CASHSHOP_ITEMLIST *>(this->CashItemList[iCategory][iItemIndex+iIndex].dwPriceGuid, &this->CashItemList[iCategory][iItemIndex+iIndex]));

		this->CashItemListCompress[iCategory][iItemIndex+iIndex].dwItemGuid = lpItemSellInfo->itemPrice[iIndex].dwPriceGuid;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].btCategoryCode = iCategory;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].btItemDuration = this->CashItemList[iCategory][iItemIndex+iIndex].btItemDuration;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].btItemSaleRatio = lpItemSellInfo->itemPrice[iIndex].dwSellRate;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].wItemPrice = lpItemSellInfo->itemPrice[iIndex].dwPrice;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].btSpecialOption = iBranchType;
		this->CashItemListCompress[iCategory][iItemIndex+iIndex].dwItemUsePeriod = lpItemSellInfo->itemPrice[iIndex].dwUseTime;
		memcpy(this->CashItemListCompress[iCategory][iItemIndex+iIndex].btItemInfo, lpItemStatus->btItemInfo, sizeof(lpItemStatus->btItemInfo));

		this->iAddItemCountInCategory[iCategory]++;
		this->iCashItemCountInCategory[iCategory]++;

		LogAddTD("[CashShop][ShopList] (Category:%d, Guid:%d) ItemInfo(Type : %d, Index : %d, Name : %s, Price : %d(%d) Amount : %d, UseTime : %d, SPOP:%d ",
			iCategory, this->CashItemListCompress[iCategory][iItemIndex+iIndex].dwItemGuid,
			this->CashItemList[iCategory][iItemIndex+iIndex].btItemType,
			this->CashItemList[iCategory][iItemIndex+iIndex].wItemIndex,
			ItemAttribute[ITEMGET(this->CashItemList[iCategory][iItemIndex+iIndex].btItemType, this->CashItemList[iCategory][iItemIndex+iIndex].wItemIndex)].Name,
			this->CashItemListCompress[iCategory][iItemIndex+iIndex].wItemPrice,
			this->CashItemListCompress[iCategory][iItemIndex+iIndex].btItemSaleRatio,
			this->CashItemListCompress[iCategory][iItemIndex+iIndex].btItemDuration,
			this->CashItemList[iCategory][iItemIndex+iIndex].dwItemUsePeriod,
			iBranchType);

		if ( (iItemIndex+iIndex-1) > MAX_CASH_SHOP_ITEM )
			break;

	}
}



void CCashShop::MakeItemListProtocol()
{
	int iCategory = 0;
	int iPageIndex = 0;
	int iItemIndex = 0;
	int iItemCount = 0;
	int iAddItemCount = 0;
	int iAddItemIndex = 0;
	int iAddItemListIndex = 0;
	PMSG_ANS_CASHITEMLIST * lpMsg = NULL;

	for ( iCategory=0;iCategory < MAX_CASH_SHOP_CATEGORY;iCategory++)
	{
		iItemCount = this->iCashItemCountInCategory[iCategory];
		iAddItemCount = this->iAddItemCountInCategory[iCategory];
		iAddItemIndex = iItemCount - iAddItemCount;
		iAddItemListIndex = iAddItemIndex;

		iPageIndex = iAddItemIndex / MAX_CASH_SHOP_PROTOCOL_DATA;

		iItemIndex = this->CashItemProtocol[iCategory][iPageIndex].btItemCount;

		for ( int i=0;i<iAddItemCount;i++)
		{
			this->CashItemProtocol[iCategory][iPageIndex].btCategoryIndex = iCategory;
			this->CashItemProtocol[iCategory][iPageIndex].btPageIndex = iPageIndex;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].dwItemGuid = this->CashItemListCompress[iCategory][iAddItemListIndex].dwItemGuid;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btCategoryCode = this->CashItemListCompress[iCategory][iAddItemListIndex].btCategoryCode;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btItemDuration = this->CashItemListCompress[iCategory][iAddItemListIndex].btItemDuration;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btItemSaleRatio = this->CashItemListCompress[iCategory][iAddItemListIndex].btItemSaleRatio;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].wItemPrice = this->CashItemListCompress[iCategory][iAddItemListIndex].wItemPrice;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btSpecialOption = this->CashItemListCompress[iCategory][iAddItemListIndex].btSpecialOption;
			this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].dwItemUsePeriod = this->CashItemListCompress[iCategory][iAddItemListIndex].dwItemUsePeriod;
			memcpy(this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btItemInfo, this->CashItemListCompress[iCategory][iAddItemListIndex].btItemInfo, sizeof(this->CashItemProtocol[iCategory][iPageIndex].ItemInfo[iItemIndex+i].btItemInfo));

			this->CashItemProtocol[iCategory][iPageIndex].btItemCount++;
			this->iAddItemCountInCategory[iCategory]--;
			iAddItemListIndex++;

			if ( this->CashItemProtocol[iCategory][iPageIndex].btItemCount >= MAX_CASH_SHOP_PROTOCOL_DATA )
			{
				iAddItemCount -= i+1;
				i=-1;
				iPageIndex++;
			}

			PHeadSubSetB((LPBYTE)&this->CashItemProtocol[iCategory][iPageIndex], 0xF5, 0x06, sizeof(PMSG_ANS_CASHITEMLIST));
		}
	}
}



LPBYTE CCashShop::GetItemList(int iCategory, int iPageCount)
{
	if ( iPageCount < 0 || iPageCount >= MAX_CASH_SHOP_PROTOCOL )
		return NULL;

	return (LPBYTE)&this->CashItemProtocol[iCategory][iPageCount];
}




BOOL CCashShop::AddUser(LPOBJ lpObj)
{
	if ( this->SearchUser(lpObj->DBNumber) )
		return FALSE;

	lpObj->m_wCashPoint = 10000;
	this->MapUserObject.insert(std::pair<int, LPOBJ>(lpObj->DBNumber, lpObj));
	return TRUE;
}



BOOL CCashShop::DeleteUser(LPOBJ lpObj)
{
	std::map<int, OBJECTSTRUCT *>::iterator Iter;

	Iter = this->MapUserObject.find(lpObj->DBNumber);
	
	if ( Iter == this->MapUserObject.end() )
		return FALSE;

	this->MapUserObject.erase(Iter);
	return TRUE;
}


LPOBJ CCashShop::SearchUser(int iUserGuid)
{
	LPOBJ lpReturnObj = NULL;

	std::map<int, OBJECTSTRUCT *>::iterator Iter;
	Iter = this->MapUserObject.find(iUserGuid);

	if ( Iter == this->MapUserObject.end() )
		return FALSE;

	lpReturnObj = Iter->second;

	return lpReturnObj;
}



struct PMSG_ANS_CASHSHOPOPEN
{
	PBMSG_HEAD2 head;	// C1:F5:02
	BYTE btResult;	// 4
};




BOOL CCashShop::CGCashShopOpen(LPOBJ lpObj, PMSG_REQ_CASHSHOPOPEN * lpMsg)
{
	BYTE btResult = 0;

	if ( this->bCashItemListReload == TRUE )
	{
		btResult = 6;
	}

	if ( g_bConnectShopServer == TRUE && g_bShopServerConnectState == FALSE )
	{
		btResult = 6;
	}

	if ( !gObjIsAccontConnect(lpObj->m_Index, lpObj->AccountID))
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 175)), lpObj->AccountID, lpObj->m_Index);
		return FALSE;
	}

	if ( lpObj->Connected <= PLAYER_LOGGED || lpObj->CloseCount != -1 )
		return FALSE;

	if ( lpMsg->btShopOpenType == 1 )
	{
		if ( lpObj->m_IfState.use > 0 )
		{
			btResult = 8;
		}

		if ( btResult == 0 )
		{
			lpObj->m_IfState.use = 1;
			lpObj->m_IfState.type = 18;
			lpObj->m_IfState.state = 1;
			this->CGCashPoint(lpObj);
		}
	}
	else if ( lpMsg->btShopOpenType == 0 )
	{
		lpObj->m_IfState.use = 0;
		lpObj->m_IfState.type = 0;
		lpObj->m_IfState.state = 0;
	}

	PMSG_ANS_CASHSHOPOPEN pMsg;

	pMsg.btResult = btResult;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF5, 0x02, sizeof(PMSG_ANS_CASHSHOPOPEN));

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.head.size);

	return TRUE;
}




BOOL CCashShop::CGCashPoint(LPOBJ lpObj)
{
	DWORD dwUserGuid = 0;
	
	if ( g_bConnectShopServer == TRUE && g_bShopServerConnectState == FALSE )
	{
		return FALSE;
	}

	if ( !gObjIsAccontConnect(lpObj->m_Index, lpObj->AccountID))
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 175)), lpObj->AccountID, lpObj->m_Index);
		return FALSE;
	}

	if ( lpObj->Connected !=PLAYER_PLAYING && lpObj->Type != OBJ_USER )
		return FALSE;

	dwUserGuid = lpObj->DBNumber;
	this->GSReqCashPoint(dwUserGuid);

	return TRUE;
}


struct PMSG_ANS_CASHPOINT
{
	PBMSG_HEAD2 head;	// C1:F5:04
	int iCashPoint;	// 4
};


void CCashShop::GCCashPoint(LPOBJ lpObj, DWORD dwCashPoint)
{
	if ( !gObjIsAccontConnect(lpObj->m_Index, lpObj->AccountID))
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 175)), lpObj->AccountID, lpObj->m_Index);
		return;
	}

	PMSG_ANS_CASHPOINT pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF5, 0x04, sizeof(PMSG_ANS_CASHPOINT));
	lpObj->m_wCashPoint = dwCashPoint;
	pMsg.iCashPoint = dwCashPoint;

	if ( dwCashPoint < 0 )
		return;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.head.size);
}






BOOL CCashShop::GCCashItemListSend(LPOBJ lpObj, PMSG_REQ_CASHITEMLIST *lpMsg)
{
	BOOL bResult = FALSE;
	LPBYTE lpSendMsg = NULL;
	int iCategory = 0;
	int iPageIndex = 0;

	if ( this->bCashItemListReload == TRUE )
		return FALSE;

	if ( g_bConnectShopServer == TRUE && g_bShopServerConnectState == FALSE )
	{
		return FALSE;
	}

	iCategory = lpMsg->btCategoryIndex;
	iPageIndex = lpMsg->btPageIndex;

	if ( !lpMsg->btPageLoaded )
		return FALSE;

	lpSendMsg = this->GetItemList(iCategory, iPageIndex);

	if ( lpSendMsg == NULL )
		return FALSE;

	DataSend(lpObj->m_Index, lpSendMsg, sizeof(PMSG_ANS_CASHITEMLIST));

	return TRUE;
}



void CCashShop::CGCashItemBuy(LPOBJ lpObj, PMSG_REQ_CASHITEM_BUY *lpMsg)
{
	int iCategoryIndex = 0;
	BYTE btResult = 0;
	BYTE btPosition = 0;
	BOOL bItemEmptySpace = FALSE;
	int iItemCode = 0;
	CASHSHOP_ITEMLIST* lpCashItemInfo = NULL;

	if ( this->bCashItemListReload == TRUE )
		btResult = 7;

	if ( g_bConnectShopServer == TRUE && g_bShopServerConnectState == FALSE )
	{
		btResult = 6;
	}

	if ( !gObjIsAccontConnect(lpObj->m_Index, lpObj->AccountID))
	{
		LogAddC(2, lMsg.Get(MSGGET(1, 175)), lpObj->AccountID, lpObj->m_Index);
		btResult = 9;
	}

	if ( lpObj->Connected !=PLAYER_PLAYING && lpObj->Type != OBJ_USER )
		btResult = 9;

	iCategoryIndex = lpMsg->btCategoryIndex;

	if ( iCategoryIndex < 0 || iCategoryIndex > MAX_CASH_SHOP_CATEGORY )
		btResult = 3;

	lpCashItemInfo = this->SearchItemList(lpMsg->dwItemPriceGuid);

	if ( lpCashItemInfo == NULL )	// #error, It Must Send and Return coz if it is null it can crash
		btResult = 3;

	iItemCode = ITEMGET(lpCashItemInfo->btItemType, lpCashItemInfo->wItemIndex);

	if ( this->CheckPeriodItem(iItemCode) == TRUE )
	{
		if ( this->CheckPeriodItemUsed(lpObj, iItemCode) == TRUE )
		{
			btResult = 4;
		}
	}
	else if ( this->CheckInventoryEmptySpace(lpObj, lpCashItemInfo) == FALSE )
	{
		btResult = 2;
	}

	LogAddTD("[CashShop][Buy Request] User(ID:%s, Name:%s) Item(Name:%s,Guid:%d,Category:%d,Price:%d,SaleRate:%d) Result:%d",
		lpObj->AccountID, lpObj->Name, ItemAttribute[iItemCode].Name, lpMsg->dwItemPriceGuid, iCategoryIndex,
		lpCashItemInfo->wItemPrice, lpCashItemInfo->btItemSaleRatio, btResult);

	if ( btResult == 0 )
	{
		this->GSReqBuyCashItem(gGameServerCode, lpObj->DBNumber, lpObj->m_Index, lpObj->Name, 1, lpMsg->dwItemPriceGuid);
	}
	else
	{
		this->GCCashItemBuyResult(lpObj, btResult);
	}
}

struct PMSG_ANS_CASHITEM_BUY
{
	PBMSG_HEAD2 head;	// C1:F5:08
	BYTE btResult;	// 4
};


void CCashShop::GCCashItemBuyResult(LPOBJ lpObj, BYTE btResult)
{
	PMSG_ANS_CASHITEM_BUY pMsg;

	pMsg.btResult = btResult;
	PHeadSubSetB((LPBYTE)&pMsg, 0xF5, 0x08, sizeof(PMSG_ANS_CASHITEM_BUY));

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.head.size);
}





BOOL CCashShop::CheckPeriodItemUsed(LPOBJ lpObj, int iItemCode) //GS-CS Fine 100% Decompiled
{
	if ( lpObj->m_iPeriodItemEffectIndex != -1 )
	{
		if ( iItemCode == ITEMGET(13,43) || 
			 iItemCode == ITEMGET(13,44) || 
			 iItemCode == ITEMGET(13,45) ||
			 iItemCode == ITEMGET(14,72) || //Fine
			 iItemCode == ITEMGET(14,73) || //Fine
			 iItemCode == ITEMGET(14,74) || //Fine
			 iItemCode == ITEMGET(14,75) || //Fine
			 iItemCode == ITEMGET(14,76) || //Fine
			 iItemCode == ITEMGET(14,77) ) //Fine
		{
			return TRUE;
		}
	}

	return FALSE;
}



BOOL CCashShop::CheckPeriodItem(int iItemCode) //GS-CS Fine 100% Decompiled
{
	if ( iItemCode == ITEMGET(13,43) || 
		 iItemCode == ITEMGET(13,44) || 
		 iItemCode == ITEMGET(13,45) ||
		 iItemCode == ITEMGET(13,59) || //Seal of Mobility, (Season2 is 13,52 & Season3 is 13,59)
		 iItemCode == ITEMGET(14,72) ||
		 iItemCode == ITEMGET(14,73) ||
		 iItemCode == ITEMGET(14,74) ||
		 iItemCode == ITEMGET(14,75) ||
		 iItemCode == ITEMGET(14,76) ||
		 iItemCode == ITEMGET(14,77) )
		{
			return TRUE;
		}

	return FALSE;
}




BOOL CCashShop::CheckInventoryEmptySpace(LPOBJ lpObj, CASHSHOP_ITEMLIST *lpItemInfo)
{
	int h = 0;
	int w = 0;
	unsigned char blank = 0;
	int iItemHeight = 0;
	int iItemWidth = 0;

	lpItemInfo->ItemInfo.GetSize(iItemWidth, iItemHeight);

	for ( h=0;h<8;h++)
	{
		for ( w=0;w<8;w++)
		{
			if ( *(BYTE *)(lpObj->pInventoryMap + h*8 + w ) == 0xFF )
			{
				blank = gObjOnlyInventoryRectCheck(lpObj->m_Index, w, h, iItemWidth, iItemHeight);

				if ( blank == 0xFE )
					return FALSE;

				if ( blank != 0xFF )
					return TRUE;
			}
		}
	}

	return FALSE;
}



CASHSHOP_ITEMLIST * CCashShop::SearchItemList(int iItemGuid)
{
	CASHSHOP_ITEMLIST* lpItemInfo = NULL;
	std::map<int,CASHSHOP_ITEMLIST *>::iterator Iter;

	Iter = this->MapCashItemList.find(iItemGuid);
	if ( Iter == this->MapCashItemList.end() )
	{
		return FALSE;
	}

	lpItemInfo = Iter->second;
	return lpItemInfo;
}



BOOL CCashShop::GiveBuyItemToInventory(LPOBJ lpObj, int iItemGuid)
{
	BYTE btPosition = 0;
	BYTE btResult = 0;
	BOOL bEmptySpace = FALSE;
	CASHSHOP_ITEMLIST* lpItemInfo = NULL;
	CItem pItem;
	int iItemCode = 0;
	BYTE ExOption[MAX_EXOPTION_SIZE];

	lpItemInfo = this->SearchItemList(iItemGuid);
	iItemCode = ITEMGET(lpItemInfo->btItemType, lpItemInfo->wItemIndex);
	bEmptySpace = this->CheckInventoryEmptySpace(lpObj, lpItemInfo);

	if ( bEmptySpace == FALSE )
		return FALSE;

	pItem.Convert(iItemCode, lpItemInfo->btItemSkillOpion, lpItemInfo->btItemLuckOption, lpItemInfo->btItemAddOption,
		lpItemInfo->btItemExOption, 0, 0, CURRENT_DB_VERSION);

	pItem.m_Level = lpItemInfo->btItemLevel;
	pItem.m_Durability = lpItemInfo->btItemDuration;

	ItemIsBufExOption(ExOption, &pItem);
	ItemSerialCreateSend(lpObj->m_Index, 0xEC, lpObj->X, lpObj->Y, pItem.m_Type, pItem.m_Level,
		pItem.m_Durability, pItem.m_Option1, pItem.m_Option2, pItem.m_Option3, lpObj->m_Index,
		pItem.m_NewOption, 0);

	LogAddTD("[CashShop][Buy Item Create in Inven] - User(ID:%s,Name:%s) Item(Name:%s,Code:%d,Skill:%d,Luck:%d,Add:%d,Ex(%d:%d:%d:%d:%d:%d))",
		lpObj->AccountID, lpObj->Name, ItemAttribute[iItemCode].Name, iItemCode, 
		pItem.m_Option1, pItem.m_Option2, pItem.m_Option3, ExOption[0], ExOption[1], ExOption[2],
		ExOption[3], ExOption[4], ExOption[5]);

	return TRUE;
}




void CCashShop::GSReqCashPoint(DWORD dwUserGuid)
{
	protocol::MSG_GTOS_USER_CASH_REQ pMsg;

	pMsg.dwUserGuid = dwUserGuid;
	g_ShopServerClient.DataSend((PCHAR)&pMsg, sizeof(protocol::MSG_GTOS_USER_CASH_REQ));
}



void CCashShop::GSReqCashItemList()
{
	protocol::MSG_GTOS_ITEM_LIST_REQ  pMsg;
	g_ShopServerClient.DataSend((PCHAR)&pMsg, sizeof(protocol::MSG_GTOS_ITEM_LIST_REQ));

	LogAddTD("[CashShop] Request Cash Item List to ShopServer.");

}



void CCashShop::GSReqPackageItemList()
{
	protocol::MSG_GTOS_PACKAGE_LIST_REQ pMsg;
	g_ShopServerClient.DataSend((PCHAR)&pMsg, sizeof(protocol::MSG_GTOS_PACKAGE_LIST_REQ));

	LogAddTD("[CashShop] Request Cash Package Item List to ShopServer.");

}



void CCashShop::SetBranchItem(DWORD dwItemGuid, int iBranchType)
{
	if ( this->iBranchItemCount >= MAX_CASH_ITEM_BRANCH )
		return;

	this->BranchItemList[this->iBranchItemCount].dwItemGuid = dwItemGuid;
	this->BranchItemList[this->iBranchItemCount].iBranchType = iBranchType;
	this->iBranchItemCount++;
}



int CCashShop::GetBranchType(DWORD dwItemGuid)
{
	for ( int i=0;i<MAX_CASH_ITEM_BRANCH;i++)
	{
		if ( this->BranchItemList[i].dwItemGuid == dwItemGuid )
		{
			return this->BranchItemList[i].iBranchType;
		}
	}

	return 0;
}



void CCashShop::GSReqBuyCashItem(DWORD dwServerGuid, DWORD dwUserGuid, DWORD dwCharacterGuid, LPSTR szCharacterName, DWORD dwCount, DWORD dwPriceGuid)
{
	protocol::MSG_GTOS_BUY_ITEM_REQ pMsg;

	pMsg.dwServerGuid = dwServerGuid;
	pMsg.dwUserGuid =dwUserGuid;
	pMsg.dwCharGuid = dwCharacterGuid;
	pMsg.dwCount = 1;
	pMsg.dwPriceGuids[0] = dwPriceGuid;
	memset(pMsg.szCharName, 0, sizeof(pMsg.szCharName));
	strcpy(pMsg.szCharName, szCharacterName);

	g_ShopServerClient.DataSend((PCHAR)&pMsg, sizeof(protocol::MSG_GTOS_BUY_ITEM_REQ));
}




void CCashShop::GSNtfBuyCashItem(protocol::MSG_GTOS_BUY_ITEM_NTF * pMsg)
{
	pMsg->resize();
	g_ShopServerClient.DataSend((PCHAR)pMsg, pMsg->size);	// #warning this should be pMsg->size
}




/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*:::::::::::::::::::::::::::::::: :INDIVIDUAL PACKETS :::::::::::::::::::::::::::::::::::::*/
/*::::::::::::::::::::::::::::::::: ( From Shop Server ) :::::::::::::::::::::::::::::::::::*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


void SGAnsCashPoint(protocol::MSG_STOG_USER_CASH_ANS* aRecv)
{
	LPOBJ lpObj = NULL;

	lpObj = g_CashShop.SearchUser(aRecv->dwUserGuid);

	if ( lpObj == NULL )
		return;

	g_CashShop.GCCashPoint(lpObj, aRecv->dwUserCash);
}



void  SGAnsCashItemList(protocol::MSG_STOG_ITEM_LIST_ANS* aRecv)
{
	LogAddTD("[CashShop] Receive Cash Item List from ShopServer. (%d)", aRecv->dwItemCount);
	
	if ( g_CashShop.SetItemInfoFromShop(aRecv) == FALSE )
		return;

	g_CashShop.MakeItemListProtocol();
}




void SGAnsPackageItemList(protocol::MSG_STOG_PACKAGE_LIST_ANS* aRecv)
{
	LogAddTD("[CashShop] Receive Cash Package Item List from ShopServer. (%d)", aRecv->dwPackageCount);

	if ( g_CashShop.SetPackageItemInfoFromShop(aRecv) == FALSE )
		return;

	g_CashShop.MakeItemListProtocol();
}




void CCashShop::GSReqBranchItemList()
{
	LogAddTD("[CashShop] Request Cash Branch Item List to ShopServer.");
	
	protocol::MSG_GTOS_BRANCH_ITEM_LIST_REQ pMsg;
	g_ShopServerClient.DataSend((PCHAR)&pMsg, sizeof(protocol::MSG_GTOS_BRANCH_ITEM_LIST_REQ));	
}


void SGAnsBranchItemList(protocol::MSG_STOG_BRANCH_ITEM_LIST_ANS* lpMsg)
{
	int iBranchItemCount = 0;
	int iItemGuid = 0;
	CASHSHOP_ITEMLIST* lpItemInfo = NULL;

	iBranchItemCount = lpMsg->dwItemCount;

	for (int i=0;i<iBranchItemCount;i++)
	{
		if ( lpMsg->branchItems[i].dwItemType == 1 )
		{
			g_CashShop.SetBranchItem(lpMsg->branchItems[i].dwGuid, lpMsg->branchItems[i].dwBranchID);
		}
	}
}





void SGAnsBuyCashItem( protocol::MSG_STOG_BUY_ITEM_ANS* aRecv)
{
	int iItemBuyTransactionCount = 0;
	LPOBJ lpObj = NULL;
	CASHSHOP_ITEMLIST* lpItemList = NULL;
	int iItemCode = 0;
	int iItemUsePeriod = 0;
	protocol::MSG_GTOS_BUY_ITEM_NTF pMsg;
	int iResult = 1;

	lpObj = g_CashShop.SearchUser(aRecv->dwUserGuid);

	if ( lpObj == NULL )
		return;

	lpObj->m_wCashPoint = aRecv->dwUserCash;
	iItemBuyTransactionCount = aRecv->dwCount;
	pMsg.dwServerGuid = gGameServerCode;
	pMsg.dwUserGuid = lpObj->DBNumber;
	pMsg.dwCharGuid = lpObj->m_Index;
	pMsg.dwCount = iItemBuyTransactionCount;

	for ( int i=0;i<iItemBuyTransactionCount;i++)
	{
		if ( aRecv->transactions[i].dwResult == 1 )
		{
			lpItemList = g_CashShop.SearchItemList(aRecv->transactions[i].dwPriceGuid);
			iItemCode = ITEMGET(lpItemList->btItemType, lpItemList->wItemIndex);

			if ( g_CashShop.CheckPeriodItem(iItemCode) == TRUE )
			{
				g_CashItemPeriodSystem.GDReqPeriodItemInsert(lpObj, iItemCode, lpItemList->dwItemUsePeriod);
			}
			else if(iItemCode == ITEMGET(14,91)) //Season3 add-on (Summoner Character Card)
			{
				GDSummonerStateUpdate(lpObj, lpObj->m_Index);
			}
			else if ( g_CashShop.GiveBuyItemToInventory(lpObj, aRecv->transactions[i].dwPriceGuid) == FALSE )
			{
				iResult = 0;
			}


			pMsg.transactions[i].dwPriceGuid = aRecv->transactions[i].dwPriceGuid;
			pMsg.transactions[i].dwResult = iResult;
			pMsg.transactions[i].dwTransactionGuid = aRecv->transactions[i].dwTransactionGuid;
		}
	}

	g_CashShop.GCCashPoint(lpObj, aRecv->dwUserCash);
	g_CashShop.GSNtfBuyCashItem(&pMsg);


	switch ( aRecv->dwResult )
	{
		case 1:	iResult =0;	break;
		case 0:	iResult =7;	break;
		case 8:	iResult =1;	break;
		case 9:	iResult =5;	break;
		case 10:	iResult =3;	break;
		case 11:	iResult =7;	break;
		case 12:	iResult =7;	break;
		case 13:	iResult =7;	break;
		case 14:	iResult =7;	break;
	}

	LogAddTD("[CashShop][Buy Answer] User(ID:%s, Name:%s) Result:%d",
		lpObj->AccountID, lpObj->Name, iResult);

	g_CashShop.GCCashItemBuyResult(lpObj, iResult);

}




BOOL IsCashItem(int iItemCode) //GS-CS Weird Compilation
{
	switch ( iItemCode )
	{
		case ITEMGET(13,43): return TRUE;
		case ITEMGET(13,44): return TRUE;
		case ITEMGET(13,45): return TRUE;
		case ITEMGET(13,46): return TRUE;
		case ITEMGET(13,47): return TRUE;
		case ITEMGET(13,48): return TRUE;
		case ITEMGET(13,52): return TRUE;
		case ITEMGET(13,53): return TRUE;
		case ITEMGET(13,54): return TRUE;
		case ITEMGET(13,55): return TRUE;
		case ITEMGET(13,56): return TRUE;
		case ITEMGET(13,57): return TRUE;
		case ITEMGET(13,58): return TRUE;
		case ITEMGET(14,53): return TRUE;
		case ITEMGET(14,54): return TRUE;
		case ITEMGET(14,58): return TRUE;
		case ITEMGET(14,59): return TRUE;
		case ITEMGET(14,60): return TRUE;
		case ITEMGET(14,61): return TRUE;
		case ITEMGET(14,62): return TRUE;
		case ITEMGET(14,70): return TRUE;
		case ITEMGET(14,71): return TRUE;
		case ITEMGET(14,72): return TRUE;
		case ITEMGET(14,73): return TRUE;
		case ITEMGET(14,74): return TRUE;
		case ITEMGET(14,75): return TRUE;
		case ITEMGET(14,76): return TRUE;
		case ITEMGET(14,77): return TRUE;
		case ITEMGET(14,78): return TRUE;
		case ITEMGET(14,79): return TRUE;
		case ITEMGET(14,80): return TRUE;
		case ITEMGET(14,81): return TRUE;
		case ITEMGET(14,82): return TRUE;

	}

	return FALSE;
}		
