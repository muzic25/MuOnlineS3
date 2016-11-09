#include "stdafx.h"
DataServer_Protocol gDataServer_Protocol;

void DataServer_Protocol::ProtocolCore(DataServer_Manager * Service, int aIndex, BYTE HeadCode, LPBYTE aRecv, int iSize)
{
    g_ServerInfoDisplayer.CheckEVDSConnection(1);

    switch (HeadCode)
    {
    case 0x00: // COMPLETE - 100%
    {
        this->DataServerLogin(Service, aIndex, reinterpret_cast<SDHP_SERVERINFO *>(aRecv));
    }
    break;

    case 0x01: // COMPLETE - 100%
    {
        this->JGPGetCharList(Service, aIndex, reinterpret_cast<SDHP_GETCHARLIST *>(aRecv));
    }
    break;

    case 0x02: // COMPLETE - 100%
    {
        this->GDCharacterClose(Service, aIndex, reinterpret_cast<SDHP_USERCLOSE *>(aRecv));
    }
    break;

    case 0x04: // COMPLETE - 100%
    {
        this->JGCharacterCreateRequest(Service, aIndex, reinterpret_cast<SDHP_CREATECHAR *>(aRecv));
    }
    break;

    case 0x05: // COMPLETE - 100%
    {
        this->JGCharDelRequest(Service, aIndex, reinterpret_cast<SDHP_CHARDELETE *>(aRecv));
    }
    break;

    case 0x06: // COMPLETE - 100%
    {
        this->JGGetCharacterInfo(Service, aIndex, reinterpret_cast<SDHP_DBCHARINFOREQUEST *>(aRecv));
    }
    break;

    case 0x07: // COMPLETE - 100%
    {
        this->GJSetCharacterInfo(Service, aIndex, reinterpret_cast<SDHP_DBCHAR_INFOSAVE *>(aRecv));
    }
    break;

    case 0x08: // COMPLETE - 100%
    {
        this->DGGetWarehouseList(Service, aIndex, reinterpret_cast<SDHP_GETWAREHOUSEDB *>(aRecv));
    }
    break;

    case 0x09: // COMPLETE - 100%
    {
        this->GDSetWarehouseList(Service, aIndex, reinterpret_cast<SDHP_GETWAREHOUSEDB_SAVE *>(aRecv));
    }
    break;

    case 0x11: // COMPLETE - 100%
    {
        this->GDUserItemSave(Service, aIndex, reinterpret_cast<SDHP_DBCHAR_ITEMSAVE *>(aRecv));
    }
    break;

    case 0x12: // COMPLETE - 100%
    {
        this->GDSetWarehouseMoney(Service, aIndex, reinterpret_cast<SDHP_WAREHOUSEMONEY_SAVE *>(aRecv));
    }
    break;

    case 0x13: // COMPLETE - 100%
    {
        this->DGGetQuestMonsterKill(Service, aIndex, reinterpret_cast<SDHP_GETQUESTMONSTER_KILL*>(aRecv));
    }
    break;

    case 0x14: // COMPLETE - 100%
    {
        this->GDQuestMonsterKillSave(Service, aIndex, reinterpret_cast<SDHP_DBQUEST_KILLSAVE*>(aRecv));
    }
    break;

    case 0x16: // COMPLETE - 100%
    {
        this->DGChangeName(Service, aIndex, reinterpret_cast<SDHP_CHANGE_NAME*>(aRecv));
    }
    break;
    case 0x17: // COMPLETE - 100%
    {
        this->GDMacroLoad(Service, aIndex, reinterpret_cast<SDHP_MACRODATA*>(aRecv));
    }
    break;
    case 0x18: // COMPLETE - 100%
    {
        this->GDMacroSave(Service, aIndex, reinterpret_cast<SDHP_MACRODATA*>(aRecv));
    }
    break;
    case 0x20: // COMPLETE - 100%
    {
        this->GetGameServerInfo(Service, aIndex, reinterpret_cast<SDHP_GAMESERVERINFO *>(aRecv));
    }
    break;

    case 0x2D: // COMPLETE - 100%
    {
        this->GDLoadMedalInfo(Service, aIndex, reinterpret_cast<SDHP_LOAD_MEDALINFO *>(aRecv));
    }
    break;

    case 0x30: // COMPLETE - 100%
    {
        this->RequestMasterLevelInfoLoad(Service, aIndex, reinterpret_cast<PMSG_REQ_ML_INFO_LOAD *>(aRecv));
    }
    break;

    case 0x31: // COMPLETE - 100%
    {
        this->RequestMasterLevelInfoSave(Service, aIndex, reinterpret_cast<PMSG_REQ_ML_INFO_SAVE *>(aRecv));
    }
    break;

    case 0x60: // COMPLETE - 100%
    {
        this->DGOptionDataRecv(Service, aIndex, reinterpret_cast<SDHP_SKILLKEYDATA *>(aRecv));
    }
    break;

    case 0x52: // COMPLETE - 100%
    {
        this->ItemSerialCreateRecv(Service, aIndex, reinterpret_cast<SDHP_ITEMCREATE *>(aRecv));
    }
    break;

    case 0x54: // COMPLETE - 100%
    {
        this->GDPropertyItemCreate(Service, aIndex, reinterpret_cast<SDHP_PROPERTY_ITEMCREATE *>(aRecv));
    }
    break;

    case 0x55: // COMPLETE - 100%
    {
        this->PetItemSerialCreateRecv(Service, aIndex, reinterpret_cast<SDHP_PET_ITEMCREATE *>(aRecv));
    }
    break;

    case 0x56: // COMPLETE - 100%
    {
        this->DGRecvPetItemInfo(Service, aIndex, reinterpret_cast<SDHP_REQUEST_PETITEM_INFO *>(aRecv));
    }
    break;

    case 0x57: // [OK] - [Revised]
    {
        this->GDSavePetItemInfo(Service, aIndex, reinterpret_cast<SDHP_SAVE_PETITEM_INFO *>(aRecv));
    }
    break;

    case 0x80: // [TODO] Need check revise all cases and check varibles
    {
        PMSG_DEFAULT2 * lpDef1 = reinterpret_cast<PMSG_DEFAULT2 *>(aRecv);

        switch (lpDef1->subcode)
        {
        case 0x00:
        {
            this->DS_GDReqCastleTotalInfo(Service, aIndex, aRecv);
        }
        break;

        case 0x01:
        {
            this->GS_DGAnsOwnerGuildMaster(Service, aIndex, aRecv);
        }
        break;

        case 0x03:
        {
            this->GS_DGAnsCastleNpcBuy(Service, aIndex, aRecv);
        }
        break;

        case 0x04:
        {
            this->GS_DGAnsCastleNpcRepair(Service, aIndex, aRecv);
        }
        break;

        case 0x05:
        {
            this->GS_DGAnsCastleNpcUpgrade(Service, aIndex, aRecv);
        }
        break;

        case 0x06:
        {
            this->GS_DGAnsTaxInfo(Service, aIndex, reinterpret_cast<CSP_REQ_TAXINFO *>(aRecv));
        }
        break;

        case 0x07:
        {
            this->GS_DGAnsTaxRateChange(Service, aIndex, reinterpret_cast<CSP_REQ_TAXRATECHANGE *>(aRecv));
        }
        break;

        case 0x08:
        {
            this->GS_DGAnsCastleMoneyChange(Service, aIndex, reinterpret_cast<CSP_REQ_MONEYCHANGE *>(aRecv));
        }
        break;

        case 0x09:
        {
            this->GS_DGAnsSiegeDateChange(Service, aIndex, reinterpret_cast<CSP_REQ_SDEDCHANGE *>(aRecv));
        }
        break;

        case 0x0A:
        {
            this->GS_DGAnsGuildMarkRegInfo(Service, aIndex, reinterpret_cast<CSP_REQ_GUILDREGINFO *>(aRecv));
        }
        break;

        case 0x0B:
        {
            this->GS_DGAnsSiegeEndedChange(Service, aIndex, reinterpret_cast<CSP_REQ_SIEGEENDCHANGE *>(aRecv));
        }
        break;

        case 0x0C:
        {
            this->GS_DGAnsCastleOwnerChange(Service, aIndex, aRecv);
        }
        break;

        case 0x0D:
        {
            this->GS_DGAnsRegAttackGuild(Service, aIndex, reinterpret_cast<CSP_REQ_REGATTACKGUILD *>(aRecv));
        }
        break;

        case 0x0E:
        {
            this->GS_DGAnsRestartCastleState(Service, aIndex, reinterpret_cast<CSP_REQ_CASTLESIEGEEND *>(aRecv));
        }
        break;

        case 0x0F:
        {
            this->GS_DGAnsMapSvrMsgMultiCast(Service, aIndex, reinterpret_cast<CSP_REQ_MAPSVRMULTICAST *>(aRecv));
        }
        break;

        case 0x10:
        {
            this->GS_DGAnsRegGuildMark(Service, aIndex, reinterpret_cast<CSP_REQ_GUILDREGMARK *>(aRecv));
        }
        break;

        case 0x11:
        {
            this->GS_DGAnsGuildMarkReset(Service, aIndex, reinterpret_cast<CSP_REQ_GUILDRESETMARK *>(aRecv));
        }
        break;

        case 0x12:
        {
            this->GS_DGAnsGuildSetGiveUp(Service, aIndex, reinterpret_cast<CSP_REQ_GUILDSETGIVEUP *>(aRecv));
        }
        break;

        case 0x16:
        {
            this->GS_DGAnsNpcRemove(Service, aIndex, aRecv);
        }
        break;

        case 0x17:
        {
            this->GS_DGAnsCastleStateSync(Service, aIndex, reinterpret_cast<CSP_REQ_CASTLESTATESYNC *>(aRecv));
        }
        break;

        case 0x18:
        {
            this->GS_DGAnsCastleTributeMoney(Service, aIndex, reinterpret_cast<CSP_REQ_CASTLETRIBUTEMONEY *>(aRecv));
        }
        break;

        case 0x19:
        {
            this->GS_DGAnsResetCastleTaxInfo(Service, aIndex, reinterpret_cast<CSP_REQ_RESETCASTLETAXINFO *>(aRecv));
        }
        break;

        case 0x1A:
        {
            this->GS_DGAnsResetSiegeGuildInfo(Service, aIndex, reinterpret_cast<CSP_REQ_RESETSIEGEGUILDINFO *>(aRecv));
        }
        break;

        case 0x1B:
        {
            this->GS_DGAnsResetRegSiegeInfo(Service, aIndex, reinterpret_cast<CSP_REQ_RESETREGSIEGEINFO *>(aRecv));
        }
        break;
        }
    }
    break;

    case 0x81:
    {
        this->GS_DGAnsCastleInitData(Service, aIndex, aRecv);
    }
    break;

    case 0x82:
    {
        this->DS_GDReqCastleNpcInfo(Service, aIndex, aRecv);
    }
    break;

    case 0x83:
    {
        this->GS_DGAnsAllGuildMarkRegInfo(Service, aIndex, aRecv);
    }
    break;

    case 0x84:
    {
        this->GS_DGAnsFirstCreateNPC(Service, aIndex, aRecv);
    }
    break;

    case 0x85:
    {
        this->GS_DGAnsCalcRegGuildList(Service, aIndex, aRecv);
    }
    break;

    case 0x86:
    {
        this->GS_DGAnsCsGulidUnionInfo(Service, aIndex, aRecv);
    }
    break;

    case 0x87:
    {
        this->GS_DGAnsCsSaveTotalGuildInfo(Service, aIndex, aRecv);
    }
    break;

    case 0x88:
    {
        this->GS_DGAnsCsLoadTotalGuildInfo(Service, aIndex, aRecv);
    }
    break;

    case 0x89:
    {
        this->GS_DGAnsCastleNpcUpdate(Service, aIndex, (CSP_REQ_NPCUPDATEDATA *)aRecv);
    }
    break;

    case 0xB0:
    {
        this->DGAnsCrywolfSync(Service, aIndex, reinterpret_cast<CWP_REQ_CRYWOLFSYNC *>(aRecv));
    }
    break;

    case 0xB1:
    {
        this->DGAnsCrywolfInfoLoad(Service, aIndex, reinterpret_cast<CWP_REQ_CRYWOLFINFOLOAD *>(aRecv));
    }
    break;

    case 0xB2: // [OK]
    {
        this->GDReqCrywolfInfoSave(Service, aIndex, reinterpret_cast<CWP_REQ_CRYWOLFINFOSAVE *>(aRecv));
    }
    break;

    case 0xCF: // [OK] - [Revised]
    {
        this->DGMoveOtherServer(Service, aIndex, reinterpret_cast<SDHP_CHARACTER_TRANSFER *>(aRecv));
    }
    break;

    case 0xCE: //Need To Test this
    {
        this->GDDeleteTempUserInfo(Service, aIndex, reinterpret_cast<SDHP_DELETE_TEMPUSERINFO *>(aRecv));
    }
    break;

    case 0xD0:
    {
        PMSG_DEFAULT2 * lpDef1 = reinterpret_cast<PMSG_DEFAULT2 *>(aRecv);

        switch (lpDef1->subcode)
        {
        case 0x03: // [OK]
        {
            this->PeriodItemInsert(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEM_INSERT *>(aRecv));
        }
        break;

        case 0x05: // [OK]
        {
            this->PeriodItemList(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEM_LIST *>(aRecv));
        }
        break;

        case 0x07: // [OK]
        {
            this->PeriodItemUpdate(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEM_UPDATE *>(aRecv));
        }
        break;

        case 0x09: // [OK]
        {
            this->PeriodItemDelete(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEM_DELETE *>(aRecv));
        }
        break;
        }
    }
    break;

    case 0xA2: // [OK]
    {
        this->SummonerStateUpdate(Service, aIndex, reinterpret_cast<PMSG_REQ_SUMMONER_CREATE *>(aRecv));
    }
    break;

    case 0xB4:
    {
        this->SetGameMasterEvent(Service, aIndex, reinterpret_cast<SDHP_SETGMEVENT *>(aRecv));
    }
    break;

    case 0xD1:
    {
        PMSG_DEFAULT2* lpDef = (PMSG_DEFAULT2*)aRecv;

        switch (lpDef->subcode)
        {
        case 1:
            GDReqPeriodItemExInsert(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEMEX_INSERT *>(aRecv));
            break;
        case 2:
            GDReqPeriodItemExDelete(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEMEX_DELETE *>(aRecv));
            break;
        case 3:
            GDReqPeriodItemExSelect(Service, aIndex, reinterpret_cast<PMSG_REQ_PERIODITEMEX_SELECT *>(aRecv));
            break;
        case 0x20:
            GDReqLuckyItemSelect(Service, aIndex, reinterpret_cast<PMSG_REQ_LUCKYITEM_SELECT *>(aRecv));
            break;
        case 0x22:
            GDReqLuckyItemInsert(Service, aIndex, reinterpret_cast<PMSG_REQ_LUCKYITEM_INSERT *>(aRecv));
            break;
        case 0x23:
            GDReqLuckyItemDelete(Service, aIndex, reinterpret_cast<PMSG_REQ_LUCKYITEM_DELETE *>(aRecv));
            break;
        case 0x24:
            GDReqLuckyItemInsert2nd(Service, aIndex, reinterpret_cast<PMSG_REQ_LUCKYITEM_INSERT_2ND *>(aRecv));
            break;
        }
    }

    case 0xD3:
    {
        PMSG_DEFAULT2* lpDef = (PMSG_DEFAULT2*)aRecv;

        switch (lpDef->subcode)
        {
        case 1:
            GDReqUserID(Service, aIndex, reinterpret_cast<PMSG_REQ_USERID *>(aRecv));
            break;
        }
    }
    break;

    case 0xD5://miss of 'qSQL.Empty' check this!!
        GDSetExtendedInvenCount(Service, aIndex, reinterpret_cast<SDHP_REQ_SET_EXTENDEDINVEN_COUNT *>(aRecv));
        break;
    case 0xD6:
        GDSetExtendedWarehouseCount(Service, aIndex, reinterpret_cast<SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT *>(aRecv));
        break;
    case 0xF6:
        GDReqQuestExpInfoSave(Service, aIndex, reinterpret_cast<_PMSG_QUESTEXP_INFO *>(aRecv));
        break;
    case 0xF7:
        GDReqQuestExpInfoLoad(Service, aIndex, reinterpret_cast<PMSG_REQ_QUESTEXP_INFO *>(aRecv));
        break;
    //	case 0xA2: //check this shit (same as on top)
    //	GJPSetAccountInfo(Service, aIndex, reinterpret_cast<SDHP_REQ_SETACCOUNTINFO *>(aRecv));
    //	 break;
    case 0xA6:
        GDSetExGameServerCode(Service, aIndex, reinterpret_cast<SDHP_REQ_SET_EXGAMESERVERCODE *>(aRecv));
        break;

	case 0x0E:
	{
		PMSG_DEFAULT2* lpDef = (PMSG_DEFAULT2*)aRecv;
		switch (lpDef->subcode)
		{
		case 0x00:
			GDNpcLeoTheHelperRecv(Service, reinterpret_cast<SDHP_NPC_LEO_THE_HELPER_RECV *>(aRecv), aIndex);
			break;
		case 0x01:
			GDNpcLukeTheHelperRecv(Service, reinterpret_cast<SDHP_NPC_LUKE_THE_HELPER_RECV *>(aRecv), aIndex);
			break;
		case 0x30:
			GDNpcLeoTheHelperSaveRecv(Service, reinterpret_cast<SDHP_NPC_LEO_THE_HELPER_SAVE_RECV *>(aRecv));
			break;
		case 0x31:
			GDNpcLukeTheHelperSaveRecv(Service, reinterpret_cast<SDHP_NPC_LUKE_THE_HELPER_SAVE_RECV *>(aRecv));
			break;
		}
	}
	break;

    default:
    {
        LogAddC(eDebug, "[Debug] DataServer Recv: 0x%02x", HeadCode);
        Service->CloseClient(aIndex);
    }
    break;
    }

    g_ServerInfoDisplayer.CheckEVDSConnection(0);
}


void DataServer_Protocol::DataServerLogin(DataServer_Manager * Service, int aIndex, SDHP_SERVERINFO * lpMsg)
{
    SDHP_RESULT pResult = { 0 };

    pResult.h.Set(0x00, sizeof(pResult));
    pResult.Result = 1;

    if (gDataBase.ExecFormat("SELECT ItemCount FROM GameServerInfo WHERE Number=0") == true)
    {
        gDataBase.Fetch();
        pResult.ItemCount = gDataBase.GetInt("ItemCount");
        gDataBase.Clear();
    }

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::JGPGetCharList(DataServer_Manager * Service, int aIndex, SDHP_GETCHARLIST * aRecv)
{
    char cBUFFER[10000] = { 0 };
    char szAccountID[11] = { 0 };
    TCHAR CharName[5][11] = { 0 };
    BYTE iCharCount = 0;
    int lOfs = sizeof(SDHP_CHARLISTCOUNT);

    BYTE btInvetory[3776] = { 0 };
    memcpy(szAccountID, aRecv->Id, 10);

    SDHP_ANS_ACCOUNTINFO InfoResult = { 0 };

    memset(InfoResult.AccountId, 0, sizeof(InfoResult.AccountId));
    memcpy(InfoResult.AccountId, aRecv->Id, 10);
    InfoResult.h.Set(0xA1, sizeof(SDHP_ANS_ACCOUNTINFO));

    gDataBase.ExecFormat("SELECT Summoner FROM AccountCharacter WHERE Id = '%s'", szAccountID);
    gDataBase.Fetch();

    InfoResult.Number = aRecv->Number;
    InfoResult.bSummoner = (BYTE)gDataBase.GetInt("Summoner");
    InfoResult.Result = 0;

    gDataBase.Clear();

    SDHP_CHARLISTCOUNT * pCount = reinterpret_cast<SDHP_CHARLISTCOUNT *>(cBUFFER);
    SDHP_CHARLIST * pCL = reinterpret_cast<SDHP_CHARLIST *>(cBUFFER + sizeof(SDHP_CHARLISTCOUNT));

    pCount->Number = aRecv->Number;

    lstrcpy(pCount->AccountId, szAccountID);

    gDataBase.ExecFormat("SELECT Id FROM AccountCharacter WHERE Id='%s'", szAccountID);

    if (gDataBase.Fetch() == SQL_NO_DATA)
    {
        gDataBase.ExecFormat("INSERT INTO AccountCharacter (Id) VALUES ('%s')", szAccountID);
    }
    gDataBase.Clear();

#if (SEASON > 5)

    if (gDataBase.ExecFormat("SELECT ExtendedWarehouseCount FROM AccountCharacter WHERE Id = '%s'", aRecv->Id) == true && gDataBase.Fetch() != SQL_NO_DATA)
    {
        BYTE btExtendedWarehouseCount = gDataBase.GetInt(1);
        if (btExtendedWarehouseCount > 1)
        {
            btExtendedWarehouseCount = 1;
        }

        pCount->ExtendedWarehouseCount = btExtendedWarehouseCount;
    }
    gDataBase.Clear();
#endif

    gDataBase.ExecFormat("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);

    gDataBase.Fetch();

    pCount->MoveCnt = (BYTE)gDataBase.GetInt("MoveCnt");

    gDataBase.GetStr("GameID1", CharName[0]);
    gDataBase.GetStr("GameID2", CharName[1]);
    gDataBase.GetStr("GameID3", CharName[2]);
    gDataBase.GetStr("GameID4", CharName[3]);
    gDataBase.GetStr("GameID5", CharName[4]);

    gDataBase.Clear();

    for (BYTE i = 0; i < 5; i++)
    {
        if(gFunc.CheckSQLSyntex(CharName[i]) == true)
        {
            if (CharName[i][0] != 0)
            {
                if (lstrlen(CharName[i]) >= 4)
                {
                    if (gDataBase.ExecFormat("SELECT cLevel, Class, CtlCode, DbVersion FROM Character WHERE Name='%s'", CharName[i]) == true)
                    {
                        gDataBase.Fetch();
                        char szTemp[200];
                        pCL = reinterpret_cast<SDHP_CHARLIST *>(cBUFFER + lOfs);
                        pCL->Level = (WORD)gDataBase.GetInt("cLevel");
                        pCL->Class = (BYTE)gDataBase.GetInt("Class");

                        if (pCL->Level >= 150 && pCount->Magumsa == 0)
                        {
                            pCount->Magumsa = 1;
                        }
                        if (pCL->Level >= 220 && (pCount->Magumsa == 0 || pCount->Magumsa == 1))
                        {
                            pCount->Magumsa = 2;
                        }
                        if (pCL->Level >= 250 && (pCount->Magumsa == 0 || pCount->Magumsa == 1 || pCount->Magumsa == 2))
                        {
                            pCount->Magumsa = 3;
                        }

                        pCL->CtlCode = (BYTE)gDataBase.GetInt("CtlCode");
                        pCL->DbVersion = (BYTE)gDataBase.GetInt("DbVersion");

                        gDataBase.Clear();

                        sprintf(szTemp, "SELECT Inventory FROM Character WHERE Name='%s'", CharName[i]);
                        gDataBase.Fetch();
                        gDataBase.GetAsBinary(szTemp, btInvetory);
                        gDataBase.Clear();

                        memset(pCL->dbInventory, -1, sizeof(pCL->dbInventory));

                        if (pCL->DbVersion == 0)
                        {
                            for (int c = 0; c < 12; c++)
                            {
                                memcpy(&pCL->dbInventory[2 * c], &btInvetory[7 * c], 2);
                            }
                        }
                        else if (pCL->DbVersion == 1 || pCL->DbVersion == 2)
                        {
                            for (int k = 0; k < 12; k++)
                            {
                                memcpy(&pCL->dbInventory[3 * k], &btInvetory[10 * k], 2);
                                pCL->dbInventory[3 * k + 2] = btInvetory[10 * k + 7];
                            }
                        }
                        else
                        {
                            for (int j = 0; j < 12; j++)
                            {
                                memcpy(&pCL->dbInventory[4 * j], &btInvetory[16 * j], 2);
                                pCL->dbInventory[4 * j + 2] = btInvetory[16 * j + 7];
                                pCL->dbInventory[4 * j + 3] = btInvetory[16 * j + 9];
                            }
                        }

                        gDataBase.ExecFormat("SELECT G_Status FROM GuildMember WHERE Name='%s'", CharName[i]);

                        if (gDataBase.Fetch() != SQL_NO_DATA)
                        {
                            pCL->btGuildStatus = (BYTE)gDataBase.GetInt("G_Status");
                        }
                        else
                        {
                            pCL->btGuildStatus = 0xFF;
                        }

                        pCL->Index = i;
                        lstrcpy(pCL->Name, CharName[i]);

                        iCharCount++;
                        lOfs += sizeof(SDHP_CHARLIST);
                    }

                    gDataBase.Clear();
                }
            }
        }
    }

    gFunc.PHeadSetW((LPBYTE)pCount, 0x01, sizeof(SDHP_CHARLISTCOUNT)+sizeof(SDHP_CHARLIST)* iCharCount);
    pCount->Count = iCharCount;

    Service->DataSend(aIndex, (LPBYTE)cBUFFER, sizeof(SDHP_CHARLISTCOUNT)+sizeof(SDHP_CHARLIST)* iCharCount);
    Service->DataSend(aIndex, (unsigned char*)&InfoResult, InfoResult.h.Size);
}


void DataServer_Protocol::JGCharacterCreateRequest(DataServer_Manager * Service, int aIndex, SDHP_CREATECHAR * aRecv)
{
    SDHP_CREATECHARRESULT pResult = { 0 };
    char szAccountID[11] = { 0 };
    char szName[11] = { 0 };
    BYTE btInvetory[3776] = { 0 };;
    BYTE iIndex = 0;

    pResult.ClassSkin = aRecv->ClassSkin;
    pResult.Number = aRecv->Number;

    memcpy(pResult.AccountId, aRecv->AccountId, 10);
    memcpy(szAccountID, aRecv->AccountId, 10);
    memcpy(szName, aRecv->Name, 10);
    pResult.Result = 1;

    if (gFunc.CheckSQLSyntex(szName) == FALSE)
    {
        pResult.Result = 0;
    }

    if (gDataBase.ExecFormat("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID) == true)
    {
        gDataBase.Fetch();
        TCHAR CharName[5][11] = { 0 };
        gDataBase.GetStr("GameID1", CharName[0]);
        gDataBase.GetStr("GameID2", CharName[1]);
        gDataBase.GetStr("GameID3", CharName[2]);
        gDataBase.GetStr("GameID4", CharName[3]);
        gDataBase.GetStr("GameID5", CharName[4]);

        for (iIndex = 0; iIndex < 5; iIndex++)
        {
            if (CharName[iIndex][0] == 0)
            {
                break;
            }
        }
        gDataBase.Clear();
    }
    else
    {
        pResult.Result = 2;
        gDataBase.Clear();
    }

    if (iIndex >= 5)
    {
        pResult.Result = 2;
    }

    if (gDataBase.ExecFormat("WZ_CreateCharacter '%s', '%s', '%d'", szAccountID, szName, pResult.ClassSkin) == true && gDataBase.Fetch() != SQL_NO_DATA)
    {
        if (gFunc.CheckSQLSyntex(szName) == true)
        {
            pResult.Result = (UCHAR)gDataBase.GetInt(0);
        }
        else
        {
            pResult.Result = 0;
        }
    }
    gDataBase.Clear();

    if (pResult.Result == 1)
    {
        memcpy(pResult.Name, aRecv->Name, 10);
        pResult.Pos = iIndex;

        if ((pResult.ClassSkin >> 4) < 0 || (pResult.ClassSkin >> 4) > 6)
        {
            pResult.ClassSkin = 1;
        }

        pResult.Level = 1;
        char szTemp[200] = { 0 };
        sprintf(szTemp, "SELECT Inventory FROM DefaultClassType WHERE Class=%d", pResult.ClassSkin);
        gDataBase.Fetch();
        gDataBase.GetAsBinary(szTemp, btInvetory);
        gDataBase.Clear();

        gDataBase.ExecFormat("UPDATE AccountCharacter Set GameID%d='%s' WHERE Id='%s'", iIndex + 1, szName, szAccountID);
        gDataBase.Clear();


        memset(pResult.Equipment, -1, sizeof(pResult.Equipment));

        for (int i = 0; i < 2; i++)
        {
            if (btInvetory[0 + i * 16] == 0xFF)
            {
                pResult.Equipment[i * 12 + 0] = 0xFF;
                pResult.Equipment[i * 12 + 1] = 0xFF;
                pResult.Equipment[i * 12 + 2] = 0xFF;
                pResult.Equipment[i * 12 + 3] = 0xFF;
                pResult.Equipment[i * 12 + 4] = 0xFF;
                pResult.Equipment[i * 12 + 5] = 0xFF;
                pResult.Equipment[i * 12 + 6] = 0xFF;
                pResult.Equipment[i * 12 + 7] = 0xFF;
                pResult.Equipment[i * 12 + 8] = 0xFF;
                pResult.Equipment[i * 12 + 9] = 0xFF;
                pResult.Equipment[i * 12 + 10] = 0xFF;
                pResult.Equipment[i * 12 + 11] = 0xFF;
            }
            else
            {
                BYTE OptionData = 0;
                OptionData = (btInvetory[1 + (i * 16)]);
                pResult.Equipment[i * 12 + 0] = (btInvetory[0 + (i * 16)]);	// Item
                pResult.Equipment[i * 12 + 1] = ((OptionData) >> 3) & 15;	// Level
                pResult.Equipment[i * 12 + 2] = (btInvetory[2 + (i * 16)]);	// Durability
                pResult.Equipment[i * 12 + 3] = 0xFF;
                pResult.Equipment[i * 12 + 4] = 0xFF;
                pResult.Equipment[i * 12 + 5] = 0xFF;
                pResult.Equipment[i * 12 + 6] = 0xFF;
                pResult.Equipment[i * 12 + 7] = 0xFF;
                pResult.Equipment[i * 12 + 8] = 0xFF;
                pResult.Equipment[i * 12 + 9] = 0xFF;
                pResult.Equipment[i * 12 + 10] = 0xFF;
                pResult.Equipment[i * 12 + 11] = 0xFF;
            }
        }
    }

    pResult.h.Set(0x04, sizeof(pResult));
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::JGCharDelRequest(DataServer_Manager * Service, int aIndex, SDHP_CHARDELETE * aRecv)
{
    SDHP_CHARDELETERESULT pResult = { 0 };
    char szAccountID[11] = { 0 };
    char szName[11] = { 0 };

    pResult.h.Set(0x05, sizeof(pResult));

    pResult.Number = aRecv->Number;
    pResult.Result = 1;

    memcpy(pResult.AccountID, aRecv->AccountID, 10);
    memcpy(szAccountID, aRecv->AccountID, 10);
    memcpy(szName, aRecv->Name, 10);


    if (strlen(aRecv->AccountID) > 1 && strlen(aRecv->Name) > 1)
    {
        if (gFunc.CheckSQLSyntex(szAccountID) == true && gFunc.CheckSQLSyntex(szName) == true)
        {
            if (gDataBase.ExecFormat("DELETE FROM Character WHERE AccountID='%s' AND Name='%s'", szAccountID, szName) == TRUE)
            {
                gDataBase.Clear();

                gDataBase.ExecFormat("SELECT * FROM AccountCharacter WHERE Id='%s'", szAccountID);
                gDataBase.Fetch();

                TCHAR CharName[5][11] = { 0 };
                gDataBase.GetStr("GameID1", CharName[0]);
                gDataBase.GetStr("GameID2", CharName[1]);
                gDataBase.GetStr("GameID3", CharName[2]);
                gDataBase.GetStr("GameID4", CharName[3]);
                gDataBase.GetStr("GameID5", CharName[4]);

                int iIndex = 0;
                for (iIndex = 0; iIndex < 5; iIndex++)
                {
                    if (lstrcmp(CharName[iIndex], szName) == 0)
                    {
                        break;
                    }
                }

                gDataBase.Clear();

                gDataBase.ExecFormat("UPDATE AccountCharacter Set GameID%d = NULL WHERE Id = '%s'", iIndex + 1, szAccountID);
                gDataBase.Clear();

                gDataBase.ExecFormat("DELETE FROM T_SkillTree_Info WHERE CHAR_NAME = '%s'", szName);
                gDataBase.Clear();
            }
            else
            {
                pResult.Result = 0;
            }
        }
    }
    else
    {
        pResult.Result = 0;
    }


    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::JGGetCharacterInfo(DataServer_Manager * Service, int aIndex, SDHP_DBCHARINFOREQUEST * aRecv)
{
    SDHP_DBCHAR_INFORESULT pResult = { 0 };
    char szAccountID[11] = { 0 };
    char szAccountID2[11] = { 0 };
    char szName[11] = { 0 };
    char szTemp[256] = { 0 };
    BYTE btTemp[3776] = { 0 };

    gFunc.PHeadSetW((LPBYTE)&pResult, 0x06, sizeof(pResult));
    gFunc.BuxConvert(aRecv->Name, 10);

    memcpy(szAccountID, aRecv->AccountID, 10);
    memcpy(pResult.AccountID, szAccountID, 10);
    memcpy(szName, aRecv->Name, 10);
    memcpy(pResult.Name, aRecv->Name, 10);

    pResult.Number = aRecv->Number;
    pResult.result = 1;

    if ( gFunc.CheckSQLSyntex(szName) == FALSE )
    {
        return;
    }

    bool bRet = gDataBase.ExecFormat("SELECT AccountID, cLevel, Class, LevelUpPoint, Experience, Strength, Dexterity, Vitality, Energy, Money, Life, MaxLife, Mana, MaxMana, MapNumber, MapPosX, MapPosY, MapDir, PkCount, PkLevel, PkTime, CtlCode, DbVersion, Leadership, ChatLimitTime, FruitPoint FROM Character WHERE Name = '%s'", szName);
    if (bRet == true && gDataBase.Fetch() != SQL_NO_DATA)
    {
        gDataBase.GetStr("AccountID", szAccountID2);
        pResult.Level = (short)gDataBase.GetInt("cLevel");
        pResult.Class = (BYTE)gDataBase.GetInt("Class");
        pResult.LevelUpPoint = gDataBase.GetInt("LevelUpPoint");
        pResult.Exp = gDataBase.GetInt("Experience");
        pResult.Str = (short)gDataBase.GetInt("Strength");
        pResult.Dex = (short)gDataBase.GetInt("Dexterity");
        pResult.Vit = (short)gDataBase.GetInt("Vitality");
        pResult.Energy = (short)gDataBase.GetInt("Energy");
        pResult.Money = gDataBase.GetInt("Money");
        pResult.Life = (WORD)gDataBase.GetFloat("Life");
        pResult.MaxLife = (WORD)gDataBase.GetFloat("MaxLife");
        pResult.Mana = (WORD)gDataBase.GetFloat("Mana");
        pResult.MaxMana = (WORD)gDataBase.GetFloat("MaxMana");
        pResult.MapNumber = (BYTE)gDataBase.GetInt("MapNumber");
        pResult.MapX = (BYTE)gDataBase.GetInt("MapPosX");
        pResult.MapY = (BYTE)gDataBase.GetInt("MapPosY");
        pResult.Dir = (BYTE)gDataBase.GetInt("MapDir");
        pResult.PkCount = gDataBase.GetInt("PkCount");
        pResult.PkLevel = gDataBase.GetInt("PkLevel");
        pResult.PkTime = gDataBase.GetInt("PkTime");
        pResult.CtlCode = (BYTE)gDataBase.GetInt("CtlCode");
        pResult.DbVersion = (BYTE)gDataBase.GetInt("DbVersion");
        pResult.Leadership = (WORD)gDataBase.GetInt("Leadership");
        pResult.ChatLitmitTime = (WORD)gDataBase.GetInt("ChatLimitTime");
        pResult.iFruitPoint = gDataBase.GetInt("FruitPoint");
#if (SEASON > 5)
        pResult.btExtendedInvenCount = gDataBase.GetInt("ExtendedInvenCount");
        pResult.btExtendedWarehouseCount = gDataBase.GetInt("ExtendedWarehouseCount");
        pResult.sExGameServerCode = gDataBase.GetInt("ExGameServerCode");
#endif
    }
    else
    {
        pResult.result = 0;
    }
    gDataBase.Clear();

    if(strcmp(szAccountID2, szAccountID) != 0)
    {
        LogAddC(eError,"[DataServer] %s Try to Hack Account %s",szAccountID,szAccountID2);
        pResult.result = 0;
    }
    // ----
    memcpy(pResult.AccountID,szAccountID2,10);

    if(pResult.result == 1)
    {
        sprintf(szTemp, "SELECT Inventory FROM Character WHERE Name = '%s'", pResult.Name);
        gDataBase.Fetch();

        if (gDataBase.GetAsBinary(szTemp, btTemp) == -1)
        {
            pResult.result = 0;
            memset(btTemp, -1, sizeof(btTemp));
        }

        memcpy(pResult.dbInventory, btTemp, sizeof(pResult.dbInventory));
        memset(btTemp, 0, sizeof(btTemp));
        gDataBase.Clear();

        sprintf(szTemp, "SELECT MagicList FROM Character WHERE Name = '%s'", pResult.Name);
        gDataBase.Fetch();

        if (gDataBase.GetAsBinary(szTemp, btTemp) == -1)
        {
            pResult.result = 0;
            memset(btTemp, -1, sizeof(btTemp));
        }
        memcpy(pResult.dbMagicList, btTemp, sizeof(pResult.dbMagicList));
        memset(btTemp, 0, sizeof(btTemp));
        gDataBase.Clear();

        sprintf(szTemp, "SELECT Quest FROM Character WHERE Name = '%s'", pResult.Name);
        gDataBase.Fetch();

        if (gDataBase.GetAsBinary(szTemp, btTemp) == -1)
        {
            pResult.result = 0;
            memset(btTemp, -1, sizeof(btTemp));
        }

        memcpy(pResult.dbQuest, btTemp, sizeof(pResult.dbQuest));
        memset(btTemp, 0, sizeof(btTemp));

        gDataBase.Clear();
    }

    if(pResult.result == 1)
    {
        gDataBase.ExecFormat("UPDATE AccountCharacter SET GameIDC='%s' WHERE Id = '%s'", szName, szAccountID);
        gDataBase.Fetch();
        gDataBase.Clear();
    }

    Service->DataSend(aIndex, (unsigned char*)&pResult, sizeof(pResult));

    if (pResult.result == 1)
    {
        SDHP_SKILLKEYDATA_SEND pSkillData = { 0 };

        pSkillData.h.Set(0x60, sizeof(pSkillData));
        pSkillData.aIndex = pResult.Number;

        gDataBase.ExecFormat("SELECT * FROM OptionData WHERE Name='%s'", pResult.Name);

        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            memcpy(pSkillData.Name, pResult.Name, 10);
            pSkillData.GameOption = (BYTE)gDataBase.GetInt("GameOption");
            pSkillData.QkeyDefine = (BYTE)gDataBase.GetInt("QKey");
            pSkillData.WkeyDefine = (BYTE)gDataBase.GetInt("WKey");
            pSkillData.EkeyDefine = (BYTE)gDataBase.GetInt("EKey");
            pSkillData.ChatWindow = (BYTE)gDataBase.GetInt("ChatWindow");
#if (Season > 3)
            pSkillData.RkeyDefine = (BYTE)gDataBase.GetInt("RKey");
            pSkillData.QWERLevel = (BYTE)gDataBase.GetInt("QWERLevel");
#endif
            gDataBase.Clear();

            sprintf(szTemp, "SELECT SkillKey from OptionData where Name='%s'", pResult.Name);
            gDataBase.GetAsBinary(szTemp, pSkillData.SkillKeyBuffer);
            gDataBase.Clear();
        }
        gDataBase.Clear();
        Service->DataSend(aIndex, (unsigned char*)&pSkillData, sizeof(pSkillData));
    }
}


void DataServer_Protocol::GJSetCharacterInfo(DataServer_Manager * Service, int aIndex, SDHP_DBCHAR_INFOSAVE * aRecv)
{
    char szName[11] = { 0 };
    char szAccountID[11] = { 0 };
    char szTemp[128] = { 0 };

    if (strlen(aRecv->Name) < 1)
    {
        return;
    }
    memcpy(szName, aRecv->Name, 10);

    gDataBase.ExecFormat("SELECT AccountID FROM Character WHERE Name = '%s'", szName);
    gDataBase.Fetch();

    gDataBase.GetStr("AccountID", szAccountID);

    gDataBase.Clear();

    gDataBase.ExecFormat("UPDATE Character SET cLevel = %d, Class = %d, LevelUpPoint = %d, Experience = %d, Strength = %d, Dexterity = %d, Vitality = %d, Energy = %d, Money = %d, Life = %d, MaxLife = %d, Mana = %d, MaxMana = %d, MapNumber = %d WHERE Name = '%s'",
                         aRecv->Level, aRecv->Class, aRecv->LevelUpPoint, aRecv->Exp, aRecv->Str, aRecv->Dex, aRecv->Vit, aRecv->Energy, aRecv->Money, aRecv->Life, aRecv->MaxLife, aRecv->Mana, aRecv->MaxMana, aRecv->MapNumber, szName);
    gDataBase.Clear();

#if (SEASON > 5)
    gDataBase.ExecFormat("UPDATE Character SET MapPosX = %d, MapPosY = %d, MapDir = %d, PkCount = %d, PkLevel = %d, PkTime = %d, DbVersion = 3, Leadership = %d, ChatLimitTime = %d, FruitPoint = %d, ExGameServerCode = %d WHERE Name = '%s'",
                         aRecv->MapX, aRecv->MapY, aRecv->Dir, aRecv->PkCount, aRecv->PkLevel, aRecv->PkTime, aRecv->Leadership, aRecv->ChatLitmitTime, aRecv->iFruitPoint, aRecv->sExGameServerCode, szName);
#else
    gDataBase.ExecFormat("UPDATE Character SET MapPosX = %d, MapPosY = %d, MapDir = %d, PkCount = %d, PkLevel = %d, PkTime = %d, DbVersion = 3, Leadership = %d, ChatLimitTime = %d, FruitPoint = %d WHERE Name = '%s'",
                         aRecv->MapX, aRecv->MapY, aRecv->Dir, aRecv->PkCount, aRecv->PkLevel, aRecv->PkTime, aRecv->Leadership, aRecv->ChatLitmitTime, aRecv->iFruitPoint, szName);
#endif
    gDataBase.Clear();

    sprintf(szTemp, "UPDATE Character SET Inventory = ? WHERE Name = '%s'", szName);
    gDataBase.SetAsBinary(szTemp, aRecv->dbInventory, sizeof(aRecv->dbInventory));
    gDataBase.Clear();

    sprintf(szTemp, "UPDATE Character SET MagicList = ? WHERE Name = '%s'", szName);
    gDataBase.SetAsBinary(szTemp, aRecv->dbMagicList, sizeof(aRecv->dbMagicList));
    gDataBase.Clear();

    sprintf(szTemp, "UPDATE Character SET Quest = ? WHERE Name = '%s'", szName);
    gDataBase.SetAsBinary(szTemp, aRecv->dbQuest, sizeof(aRecv->dbQuest));
    gDataBase.Clear();

    if (aRecv->CharInfoSave == 1)
    {
        gDataBase.ExecFormat("INSERT INTO T_CurCharName (Name) VALUES('%s')", szName);
        gDataBase.Clear();
    }
}


void DataServer_Protocol::DGGetWarehouseList(DataServer_Manager * Service, int aIndex, SDHP_GETWAREHOUSEDB * aRecv)
{
    SDHP_GETWAREHOUSEDB_SAVE pResult = { 0 };
    SDHP_GETWAREHOUSEDB_RESULT pMsg = { 0 };
    char szAccountID[11] = { 0 };
    char szTemp[128] = { 0 };

    gFunc.PHeadSetW((LPBYTE)&pResult, 0x08, sizeof(pResult));
    pMsg.h.Set(0x10, sizeof(pMsg));

    memcpy(szAccountID, aRecv->AccountID, 10);
    memcpy(pResult.AccountID, szAccountID, 10);
    memcpy(pMsg.AccountID, szAccountID, 10);

    pMsg.aIndex = aRecv->aIndex;
    pResult.aIndex = aRecv->aIndex;

    int len = strlen(szAccountID);
    if (len > 10 || len <= 0)
    {
        return;
    }

    bool bRet = gDataBase.ExecFormat("SELECT AccountID FROM warehouse WHERE AccountID = '%s'", szAccountID);

    if (gDataBase.Fetch() == SQL_NO_DATA || bRet == false)
    {
        gDataBase.ExecFormat("INSERT INTO warehouse (AccountID, Money, EndUseDate, DbVersion) VALUES ('%s', 0, getdate(), 3)", szAccountID);
        gDataBase.Clear();

        Service->DataSend(aIndex, (unsigned char*)&pMsg, pMsg.h.Size);
        return;
    }

    gDataBase.Clear();

    gDataBase.ExecFormat("SELECT Money, DbVersion, pw FROM warehouse WHERE AccountID = '%s'", szAccountID);
    gDataBase.Fetch();

    pResult.Money = gDataBase.GetInt("Money");
    pResult.DbVersion = (BYTE)gDataBase.GetInt("DbVersion");
    pResult.pw = (__int16)gDataBase.GetInt("pw");

    gDataBase.Clear();

    sprintf(szTemp, "SELECT Items FROM warehouse WHERE AccountID = '%s'", szAccountID);
    gDataBase.Fetch();

    if (gDataBase.GetAsBinary(szTemp, pResult.dbItems) < 0)
    {
        memset(pResult.dbItems, -1, sizeof(pResult.dbItems));
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, sizeof(pResult));
}


void DataServer_Protocol::GDSetWarehouseList(DataServer_Manager * Service, int aIndex, SDHP_GETWAREHOUSEDB_SAVE * aRecv)
{
    char szAccountID[11] = { 0 };
    char szTemp[128] = { 0 };

    memcpy(szAccountID, aRecv->AccountID, 10);

    int len = strlen(szAccountID);
    if (len <= 0 || len > 10)
    {
        return;
    }

    gDataBase.ExecFormat("UPDATE warehouse SET Money = %d, pw = %d, DbVersion = 3 WHERE AccountID = '%s'",
                         aRecv->Money, aRecv->pw, szAccountID);
    gDataBase.Clear();

    sprintf(szTemp, "UPDATE warehouse SET Items = ? WHERE AccountID = '%s'", szAccountID);
    gDataBase.SetAsBinary(szTemp, aRecv->dbItems, sizeof(aRecv->dbItems));
    gDataBase.Clear();
}


void DataServer_Protocol::DGGetQuestMonsterKill(DataServer_Manager * Service, int aIndex, SDHP_GETQUESTMONSTER_KILL* aRecv)
{
    if (aRecv == NULL)
    {
        return;
    }

    SDHP_DBQUEST_KILLSAVE pResult = { 0 };
    pResult.h.Set(0x14, sizeof(pResult));

    char szName[11] = { 0 };

    bool bRet = false;

    pResult.aIndex = aRecv->aIndex;
    memcpy(szName, aRecv->Name, 10);
    memcpy(pResult.Name, szName, 10);

    int len = strlen(szName);

    if (len <= 0 || len > 10)
    {
        LogAddC(eError, "[%s] Error on name lenght", __FUNCTION__);
        return;
    }

    bRet = gDataBase.ExecFormat("EXEC WZ_QMK_InfoLoad '%s'", szName);

    if (bRet == true)
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            pResult.QuestDBIndex = gDataBase.GetInt("QUEST_INDEX");
            pResult.QuestMonsterIndex1 = gDataBase.GetInt("MON_INDEX_1");
            pResult.QuestMonsterKillCount1 = gDataBase.GetInt("KILL_COUNT_1");
            pResult.QuestMonsterIndex2 = gDataBase.GetInt("MON_INDEX_2");
            pResult.QuestMonsterKillCount2 = gDataBase.GetInt("KILL_COUNT_2");
            pResult.QuestMonsterIndex3 = gDataBase.GetInt("MON_INDEX_3");
            pResult.QuestMonsterKillCount3 = gDataBase.GetInt("KILL_COUNT_3");
            pResult.QuestMonsterIndex4 = gDataBase.GetInt("MON_INDEX_4");
            pResult.QuestMonsterKillCount4 = gDataBase.GetInt("KILL_COUNT_4");
            pResult.QuestMonsterIndex5 = gDataBase.GetInt("MON_INDEX_5");
            pResult.QuestMonsterKillCount5 = gDataBase.GetInt("KILL_COUNT_5");
        }
    }
    else
    {
        pResult.QuestDBIndex = -1;
        pResult.QuestMonsterIndex1 = -1;
        pResult.QuestMonsterKillCount1 = -1;
        pResult.QuestMonsterIndex2 = -1;
        pResult.QuestMonsterKillCount2 = -1;
        pResult.QuestMonsterIndex3 = -1;
        pResult.QuestMonsterKillCount3 = -1;
        pResult.QuestMonsterIndex4 = -1;
        pResult.QuestMonsterKillCount4 = -1;
        pResult.QuestMonsterIndex5 = -1;
        pResult.QuestMonsterKillCount5 = -1;
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GDQuestMonsterKillSave(DataServer_Manager * Service, int aIndex, SDHP_DBQUEST_KILLSAVE* aRecv)
{
    if (aRecv == NULL)
    {
        return;
    }

    char szId[11] = { 0 };

    memcpy(szId, aRecv->Name, 10);

    int len = strlen(szId);

    if (len <= 0 || len > 10)
    {
        LogAddC(eError, "[%s] Error on name lenght", __FUNCTION__);
        return;
    }

    gDataBase.ExecFormat("EXEC WZ_QMK_InfoSave '%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                         szId,
                         aRecv->QuestDBIndex,
                         aRecv->QuestMonsterIndex1, aRecv->QuestMonsterKillCount1,
                         aRecv->QuestMonsterIndex2, aRecv->QuestMonsterKillCount2,
                         aRecv->QuestMonsterIndex3, aRecv->QuestMonsterKillCount3,
                         aRecv->QuestMonsterIndex4, aRecv->QuestMonsterKillCount4,
                         aRecv->QuestMonsterIndex5, aRecv->QuestMonsterKillCount5);

    gDataBase.Clear();
}

void DataServer_Protocol::DGChangeName(DataServer_Manager * Service, int aIndex, SDHP_CHANGE_NAME* aRecv)
{
    int Result = 0;

    SDHP_CHANGE_NAME_RESULT pResult = { 0 };

    char accountId[11] = { 0 };
    char OldName[11] = { 0 };
    char NewName[11] = { 0 };

    memcpy(accountId, aRecv->AccountId, 10);
    memcpy(OldName, aRecv->OldName, 10);
    memcpy(NewName, aRecv->NewName, 10);

    if (gFunc.CheckSQLSyntex(NewName) == false)
    {
        Result = 1;
    }

    if (Result == 0)
    {
        if (gDataBase.ExecFormat("WZ_ChangeCharacterName '%s', '%s', '%s'", accountId, OldName, NewName) == FALSE)
        {
            gDataBase.Clear();
            Result = 5;
        }

        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            Result = gDataBase.GetInt(1);
        }
        gDataBase.Clear();
    }

    pResult.h.Set(0x16, sizeof(SDHP_CHANGE_NAME_RESULT));
    pResult.btResult = (BYTE)Result;
    pResult.aIndex = aRecv->aIndex;

    memcpy(pResult.AccountId, aRecv->AccountId, 10);
    memcpy(pResult.OldName, aRecv->OldName, 10);
    memcpy(pResult.NewName, aRecv->NewName, 10);

    Service->DataSend(aIndex, (unsigned char*)&pResult, sizeof(PMSG_ANS_USERID));
}

void DataServer_Protocol::GDMacroLoad(DataServer_Manager * Service, int aIndex, SDHP_MACRODATA* aRecv)
{
    SDHP_MACRODATA pMsg = { 0 };
    pMsg.h.Set(0x17, sizeof(SDHP_MACRODATA));

    if (gDataBase.ExecFormat("EXEC WZ_MACROINFO_LOAD '%s', '%s'", aRecv->AccountID, aRecv->Name) == FALSE)
    {
        char tmp[256] = { 0 };
        sprintf(tmp, "EXEC WZ_MACROINFO_LOAD '%s', '%s'", aRecv->AccountID, aRecv->Name);
        gDataBase.GetAsBinary(tmp, pMsg.btMacroData);
        for (int n = 0; n < 256; n++)
        {
            aRecv->btMacroData[n] = 0xFF;
        }
        pMsg.btResult = 0;
    }
    else
    {
        pMsg.btResult = 1;
    }

    memcpy(pMsg.AccountID, aRecv->AccountID, 11);
    memcpy(pMsg.Name, aRecv->Name, 11);
    pMsg.aIndex = aRecv->aIndex;

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(SDHP_MACRODATA));
}

void DataServer_Protocol::GDMacroSave(DataServer_Manager * Service, int aIndex, SDHP_MACRODATA* aRecv)
{
    char tmp[256] = { 0 };
    gDataBase.ExecFormat("EXEC WZ_MACROINFO_SAVE '%s', '%s', ?", aRecv->AccountID, aRecv->Name);
    sprintf(tmp, "EXEC WZ_MACROINFO_SAVE '%s', '%s', ?", aRecv->AccountID, aRecv->Name);
    gDataBase.SetAsBinary(tmp, aRecv->btMacroData, sizeof(aRecv->btMacroData));
}


void DataServer_Protocol::GDUserItemSave(DataServer_Manager * Service, int aIndex, SDHP_DBCHAR_ITEMSAVE * aRecv)
{
    char szName[11] = { 0 };
    memcpy(szName, aRecv->Name, 10);

    if (strlen(szName) <= 0)
    {
        return;
    }

    if (gDataBase.ExecFormat("UPDATE Character SET DbVersion = 3 WHERE Name = '%s'", szName) == true)
    {
        char szTemp[128] = { 0 };
        sprintf(szTemp, "UPDATE Character SET Inventory = ? WHERE Name = '%s'", szName);
        gDataBase.SetAsBinary(szTemp, aRecv->dbInventory, sizeof(aRecv->dbInventory));
        gDataBase.Clear();
    }
}


void DataServer_Protocol::GDSetWarehouseMoney(DataServer_Manager * Service, int aIndex, SDHP_WAREHOUSEMONEY_SAVE * aRecv)
{
    // Revised 18.07.2012 -> All like orinal, but added connection clear

    char szId[11] = { 0 };

    memcpy(szId, aRecv->AccountID, 10);

    int len = strlen(szId);

    if (len <= 0 || len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    gDataBase.ExecFormat("UPDATE warehouse SET Money = %d WHERE AccountID = '%s'", aRecv->Money, szId);
    gDataBase.Clear();
}


void DataServer_Protocol::ItemSerialCreateRecv(DataServer_Manager * Service, int aIndex, SDHP_ITEMCREATE * aRecv)
{
    SDHP_ITEMCREATERECV pResult = { 0 };
    DWORD					Number = 0;

    pResult.h.Set(0x52, sizeof(pResult));

  /*  if(aRecv->NewOption == 63 || aRecv->MapNumber == 236)
        Number = gWzItemSerial.GetSerial();
		   */
	gDataBase.ExecFormat("EXEC WZ_GetItemSerial");
	gDataBase.Fetch();
	// ----
	Number = gDataBase.GetInt(0);
	// ----
	gDataBase.Clear();

    pResult.m_Number = Number;
    pResult.aIndex = aRecv->aIndex;
    pResult.Dur = aRecv->Dur;
    pResult.Level = aRecv->Level;
    pResult.lootindex = aRecv->lootindex;
    pResult.MapNumber = aRecv->MapNumber;
    pResult.NewOption = aRecv->NewOption;
    pResult.Op1 = aRecv->Op1;
    pResult.Op2 = aRecv->Op2;
    pResult.Op3 = aRecv->Op3;
    pResult.SetOption = aRecv->SetOption;
    pResult.Type = aRecv->Type;
    pResult.x = aRecv->x;
    pResult.y = aRecv->y;
    pResult.lDuration = aRecv->lDuration;
    pResult.dwEventIndex = aRecv->dwEventIndex;
	LogAdd("[Item Serial] Type(%d) Serial(%u)", aRecv->Type, Number);
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GDPropertyItemCreate(DataServer_Manager * Service, int aIndex, SDHP_PROPERTY_ITEMCREATE * aRecv)
{
    SDHP_PROPERTY_ITEMRECV pMsg = { 0 };
    DWORD s_num = 0;

    if(aRecv->NewOption == 63 || aRecv->MapNumber == 236)
        s_num = gWzItemSerial.GetSerial();

    pMsg.h.Set(0x54, sizeof(pMsg));

    bool Return = gDataBase.ExecFormat("INSERT INTO T_PropertyItemInfo (ItemSerial,Name1,Level1,Class1,Name2,Level2,Class2,RemainTime,CDate) VALUES(%u,'%s',%d,%d,'%s',%d,%d,%d,getdate())", s_num, aRecv->szName, aRecv->wLevel, aRecv->btClass, aRecv->szName_T, aRecv->wLevel_T, aRecv->btClass_T, aRecv->wRemainTime); //

    if (Return == true)
    {
        pMsg.Dur = aRecv->Dur;
        pMsg.Level = aRecv->Level;
        pMsg.MapNumber = aRecv->MapNumber;
        pMsg.Type = aRecv->Type;
        pMsg.x = aRecv->x;
        pMsg.y = aRecv->y;
        pMsg.Op1 = aRecv->Op1;
        pMsg.Op2 = aRecv->Op2;
        pMsg.Op3 = aRecv->Op3;
        pMsg.aIndex = aRecv->aIndex;
        pMsg.NewOption = aRecv->NewOption;
        pMsg.m_Number = s_num;
        pMsg.lootindex = aRecv->lootindex;
        pMsg.SetOption = aRecv->SetOption;
        pMsg.dwTime = aRecv->dwTime;
        memcpy(pMsg.szName, aRecv->szName, 10);
        memcpy(pMsg.szName_T, aRecv->szName_T, 10);
        pMsg.btClass = aRecv->btClass;
        pMsg.btClass_T = aRecv->btClass_T;
        pMsg.wLevel = aRecv->wLevel;
        pMsg.wLevel_T = aRecv->wLevel_T;
        pMsg.wItemIndex = aRecv->wItemIndex;
        pMsg.wRemainTime = aRecv->wRemainTime;

        Service->DataSend(aIndex, (unsigned char*)&pMsg, pMsg.h.Size);
    }
    else
        LogAddC(eError, "error-L1 : CreatePropertyItemInfo %u", s_num);

    gDataBase.Clear();
}


void DataServer_Protocol::PetItemSerialCreateRecv(DataServer_Manager * Service, int aIndex, SDHP_PET_ITEMCREATE * aRecv)
{
    SDHP_PET_ITEMCREATERECV pResult = { 0 };
    DWORD					Number = 0;

    pResult.h.Set(0x52, sizeof(pResult));

    if(aRecv->NewOption == 63 || aRecv->MapNumber == 236)
        Number = gWzItemSerial.GetSerial();

    gDataBase.ExecFormat("INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES (%d, %d, %d)",Number, 1, 0);

    pResult.m_Number = Number;
    pResult.aIndex = aRecv->aIndex;
    pResult.Dur = aRecv->Dur;
    pResult.Level = aRecv->Level;
    pResult.lootindex = aRecv->lootindex;
    pResult.MapNumber = aRecv->MapNumber;
    pResult.NewOption = aRecv->NewOption;
    pResult.Op1 = aRecv->Op1;
    pResult.Op2 = aRecv->Op2;
    pResult.Op3 = aRecv->Op3;
    pResult.SetOption = aRecv->SetOption;
    pResult.Type = aRecv->Type;
    pResult.x = aRecv->x;
    pResult.y = aRecv->y;

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);

    gDataBase.Clear();
}


void DataServer_Protocol::DGRecvPetItemInfo(DataServer_Manager * Service, int aIndex, SDHP_REQUEST_PETITEM_INFO * aRecv)
{
    if (aRecv->nCount < 1)
    {
        return;
    }

    int lOfs1 = sizeof(SDHP_REQUEST_PETITEM_INFO);
    int lOfs2 = sizeof(SDHP_RECV_PETITEM_INFO);

    char szAccountID[11] = { 0 };
    char cBUFFER[4096] = { 0 };

    Request_PetItem_Info	* pRequestPetInfo = { 0 };
    Recv_PetItem_Info		* pRecvPetInfo = { 0 };
    SDHP_RECV_PETITEM_INFO	* pRecvPetInfoCount = reinterpret_cast<SDHP_RECV_PETITEM_INFO *>(cBUFFER);


    memcpy(szAccountID, aRecv->AccountID, 10);

    for (int i = 0; i < aRecv->nCount; i++)
    {
        pRequestPetInfo = reinterpret_cast<Request_PetItem_Info *>((LPBYTE)aRecv + lOfs1);
        pRecvPetInfo = reinterpret_cast<Recv_PetItem_Info *>((LPBYTE)cBUFFER + lOfs2);

        gDataBase.ExecFormat("SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial = %d",
                             pRequestPetInfo->nSerial);

        if (gDataBase.Fetch() == SQL_NO_DATA)
        {
            gDataBase.Clear();

            gDataBase.ExecFormat("INSERT INTO T_PetItem_Info (ItemSerial, Pet_Level, Pet_Exp) VALUES (%d, %d, %d)",
                                 pRequestPetInfo->nSerial, 1, 0);
            gDataBase.Clear();

            gDataBase.ExecFormat("SELECT Pet_Level, Pet_Exp FROM T_PetItem_Info WHERE ItemSerial = %d",
                                 pRequestPetInfo->nSerial);
            gDataBase.Fetch();
        }

        pRecvPetInfo->Level = (BYTE)gDataBase.GetInt("Pet_Level");
        pRecvPetInfo->Exp = gDataBase.GetInt("Pet_Exp");
        pRecvPetInfo->nPos = pRequestPetInfo->nPos;
        pRecvPetInfo->nSerial = pRequestPetInfo->nSerial;

        if (pRecvPetInfo->Exp < 0)
        {
            pRecvPetInfo->Exp = 0;

        }
        gDataBase.Clear();
        pRecvPetInfoCount->nCount++;

        lOfs1 += sizeof(Request_PetItem_Info);
        lOfs2 += sizeof(Recv_PetItem_Info);
    }

    gFunc.PHeadSetW((LPBYTE)pRecvPetInfoCount, 0x56, sizeof(SDHP_RECV_PETITEM_INFO)+pRecvPetInfoCount->nCount * sizeof(Recv_PetItem_Info));

    pRecvPetInfoCount->InvenType = aRecv->InvenType;
    pRecvPetInfoCount->Number = aRecv->Number;
    pRecvPetInfoCount->nCount = aRecv->nCount;

    memcpy(pRecvPetInfoCount->AccountID, szAccountID, 10);

    Service->DataSend(aIndex, (unsigned char*)cBUFFER, sizeof(SDHP_RECV_PETITEM_INFO)+pRecvPetInfoCount->nCount * sizeof(Recv_PetItem_Info));
}


void DataServer_Protocol::GDSavePetItemInfo(DataServer_Manager * Service, int aIndex, SDHP_SAVE_PETITEM_INFO * aRecv)
{
    int lOfs = sizeof(SDHP_SAVE_PETITEM_INFO);

    for (int i = 0; i < aRecv->nCount; i++)
    {
        Save_PetItem_Info * pSavePetInfo = reinterpret_cast<Save_PetItem_Info *>((LPBYTE)aRecv + lOfs);

        gDataBase.ExecFormat("UPDATE T_PetItem_Info SET Pet_Level = %d, Pet_Exp = %d WHERE ItemSerial = %d",
                             pSavePetInfo->Level, pSavePetInfo->Exp, pSavePetInfo->nSerial);
        gDataBase.Fetch();
        gDataBase.Clear();
    }
}


void DataServer_Protocol::DGOptionDataRecv(DataServer_Manager * Service, int aIndex, SDHP_SKILLKEYDATA * aRecv)
{
    char szName[11] = { 0 };
    char szTemp[100] = { 0 };

    memcpy(szName, aRecv->Name, 10);

    gDataBase.ExecFormat("SELECT Name FROM OptionData WHERE Name = '%s'", szName);
    if (gDataBase.Fetch() == SQL_NO_DATA)
    {
        gDataBase.Clear();

#if(SEASON > 3)
        gDataBase.ExecFormat("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow, Rkey, QWERLevel) VALUES ('%s', %d, %d, %d, %d, %d, %d, %d)",
                             szName, aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow, aRecv->RkeyDefine, aRecv->QWERLevel);
#else
        gDataBase.ExecFormat("INSERT INTO OptionData (Name, GameOption, Qkey, Wkey, Ekey, ChatWindow) VALUES ('%s', %d, %d, %d, %d, %d)",
                             szName, aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow);
#endif
        gDataBase.Clear();
        return;
    }
    gDataBase.Clear();

#if(SEASON > 3)
    if (gDataBase.ExecFormat("UPDATE OptionData SET GameOption = %d, Qkey = %d, Wkey = %d, Ekey = %d, ChatWindow = %d, Rkey = %d, QWERLevel=%d  WHERE Name = '%s'",
                             aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow, aRecv->RkeyDefine, aRecv->QWERLevel, szName) == false)
#else
    if (gDataBase.ExecFormat("UPDATE OptionData SET GameOption = %d, Qkey = %d, Wkey = %d, Ekey = %d, ChatWindow = %d WHERE Name = '%s'",
                             aRecv->GameOption, aRecv->QkeyDefine, aRecv->WkeyDefine, aRecv->EkeyDefine, aRecv->ChatWindow, szName) == false)
#endif
    {
        return;
    }

    gDataBase.Clear();

    sprintf(szTemp, "UPDATE OptionData SET SkillKey = ? WHERE Name = '%s'", szName);

    gDataBase.SetAsBinary(szTemp, aRecv->SkillKeyBuffer, sizeof(aRecv->SkillKeyBuffer));
    gDataBase.Clear();
}


void DataServer_Protocol::DGMoveOtherServer(DataServer_Manager * Service, int aIndex, SDHP_CHARACTER_TRANSFER * aRecv)
{
    SDHP_CHARACTER_TRANSFER_RESULT pResult = { 0 };
    pResult.h.Set(0xCF, sizeof(pResult));

    char AccountID[11] = { 0 };

    memcpy(AccountID, aRecv->Account, 10);

    pResult.Result = 1;

    if (strlen(AccountID) > 1)
    {
        bool Return = gDataBase.ExecFormat("EXEC SP_CHARACTER_TRANSFER '%s'", AccountID);

        if (Return == false)
        {
            pResult.Result = 1;
        }

        if (gDataBase.Fetch() == SQL_NO_DATA)
        {
            gDataBase.Clear();
            pResult.Result = 1;
        }

        int Check = gDataBase.GetInt(1);
        gDataBase.Clear();

        if (Check != 0)
        {
            pResult.Result = (UCHAR)Check;
        }
    }

    memcpy(pResult.Account, aRecv->Account, 10);

    pResult.Number = aRecv->Number;

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}

BOOL DSDB_QueryCastleTotalInfo(int iMapSvrGroup, int iCastleEventCycle, CASTLE_DATA* lpCastleData)
{
    if(lpCastleData == NULL)
    {
        return TRUE;
    }

    CString qSql;

    qSql.Format("EXEC WZ_CS_GetCastleTotalInfo %d, %d", iMapSvrGroup, iCastleEventCycle);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if(sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    lpCastleData->wStartYear = gDataBase.GetInt("SYEAR");
    lpCastleData->btStartMonth = gDataBase.GetInt("SMONTH");
    lpCastleData->btStartDay = gDataBase.GetInt("SDAY");
    lpCastleData->wEndYear = gDataBase.GetInt("EYEAR");
    lpCastleData->btEndMonth = gDataBase.GetInt("EMONTH");
    lpCastleData->btEndDay = gDataBase.GetInt("EDAY");
    lpCastleData->btIsSiegeGuildList = gDataBase.GetInt("SIEGE_GUILDLIST_SETTED");
    lpCastleData->btIsSiegeEnded = gDataBase.GetInt("SIEGE_ENDED");
    lpCastleData->btIsCastleOccupied = gDataBase.GetInt("CASTLE_OCCUPY");
    lpCastleData->i64CastleMoney = gDataBase.GetInt64("MONEY");
    lpCastleData->iTaxRateChaos = gDataBase.GetInt("TAX_RATE_CHAOS");
    lpCastleData->iTaxRateStore = gDataBase.GetInt("TAX_RATE_STORE");
    lpCastleData->iTaxHuntZone = gDataBase.GetInt("TAX_HUNT_ZONE");
    lpCastleData->iFirstCreate = gDataBase.GetInt("FIRST_CREATE");
    gDataBase.GetStr("OWNER_GUILD", lpCastleData->szCastleOwnGuild);
    gDataBase.Clear();
    return FALSE;
}


void DataServer_Protocol::DS_GDReqCastleTotalInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CASTLEDATA* lpMsg = (CSP_REQ_CASTLEDATA*)aRecv;
    CASTLE_DATA pCastleData = {0};
    CSP_ANS_CASTLEDATA pMsgSend = {0};

    gFunc.PHeadSubSetB((LPBYTE)&pMsgSend, 0x80, 0x00, sizeof(CSP_ANS_CASTLEDATA));

    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

    int iRES = DSDB_QueryCastleTotalInfo(lpMsg->wMapSvrNum, lpMsg->iCastleEventCycle, &pCastleData );

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
        Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CASTLEDATA));
    }
    else
    {
        pMsgSend.iResult = 1;
        pMsgSend.wStartYear = pCastleData.wStartYear;
        pMsgSend.btStartMonth = pCastleData.btStartMonth;
        pMsgSend.btStartDay = pCastleData.btStartDay;
        pMsgSend.wEndYear = pCastleData.wEndYear;
        pMsgSend.btEndMonth = pCastleData.btEndMonth;
        pMsgSend.btEndDay = pCastleData.btEndDay;
        pMsgSend.btIsSiegeGuildList = pCastleData.btIsSiegeGuildList;
        pMsgSend.btIsSiegeEnded = pCastleData.btIsSiegeEnded;
        pMsgSend.btIsCastleOccupied = pCastleData.btIsCastleOccupied;
        pMsgSend.i64CastleMoney = pCastleData.i64CastleMoney;
        pMsgSend.iTaxRateChaos = pCastleData.iTaxRateChaos;
        pMsgSend.iTaxRateStore = pCastleData.iTaxRateStore;
        pMsgSend.iTaxHuntZone = pCastleData.iTaxHuntZone;
        pMsgSend.iFirstCreate = pCastleData.iFirstCreate;

        memset(pMsgSend.szCastleOwnGuild, 0, 8);
        memcpy(pMsgSend.szCastleOwnGuild, pCastleData.szCastleOwnGuild, 8);

        Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CASTLEDATA));
    }
}


BOOL DSDB_QueryOwnerGuildMaster(int iMapSvrGroup, CSP_ANS_OWNERGUILDMASTER* lpOwnerGuildMaster)
{
    if (lpOwnerGuildMaster == NULL)
    {
        return TRUE;
    }

    CString qSql;

    qSql.Format("EXEC WZ_CS_GetOwnerGuildMaster %d", iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA )
    {
        gDataBase.Clear();
        return NULL;
    }

    char szOwnerGuild[9] = "";
    char szOwnerGuildMaster[11] = "";

    lpOwnerGuildMaster->iResult = gDataBase.GetInt("QueryResult");

    gDataBase.GetStr("OwnerGuild", szOwnerGuild);
    gDataBase.GetStr("OwnerGuildMaster", szOwnerGuildMaster);

    memcpy(lpOwnerGuildMaster->szCastleOwnGuild, szOwnerGuild, 8);
    memcpy(lpOwnerGuildMaster->szCastleOwnGuildMaster, szOwnerGuildMaster, 10);

    gDataBase.Clear();
    return FALSE;
}


void DataServer_Protocol::GS_DGAnsOwnerGuildMaster(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_OWNERGUILDMASTER* lpMsg = (CSP_REQ_OWNERGUILDMASTER*)aRecv;
    CSP_ANS_OWNERGUILDMASTER pMsgSend;

    gFunc.PHeadSubSetB((LPBYTE)&pMsgSend, 0x80, 0x01, sizeof(CSP_ANS_OWNERGUILDMASTER));

    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
    pMsgSend.iIndex = lpMsg->iIndex;

    int iRES = DSDB_QueryOwnerGuildMaster(lpMsg->wMapSvrNum, &pMsgSend);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_OWNERGUILDMASTER));
}

int DSDB_QueryCastleNpcBuy(int iMapSvrGroup, CSP_REQ_NPCBUY* lpNpcBuy, int* lpiResult)
{
    if (lpiResult == NULL || lpNpcBuy == NULL)
    {
        return TRUE;
    }

    CString qSql;

    qSql.Format("EXEC WZ_CS_ReqNpcBuy %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                iMapSvrGroup, lpNpcBuy->iNpcNumber, lpNpcBuy->iNpcIndex, lpNpcBuy->iNpcDfLevel,
                lpNpcBuy->iNpcRgLevel, lpNpcBuy->iNpcMaxHp, lpNpcBuy->iNpcHp, lpNpcBuy->btNpcX, lpNpcBuy->btNpcY, lpNpcBuy->btNpcDIR);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA )
    {
        gDataBase.Clear();
        return TRUE;
    }

    *lpiResult = gDataBase.GetInt("QueryResult");

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsCastleNpcBuy(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCBUY* lpMsg = (CSP_REQ_NPCBUY*)aRecv;
    CSP_ANS_NPCBUY pMsgSend;

    pMsgSend.h.set(0x80, 0x03, sizeof(CSP_ANS_NPCBUY));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

    pMsgSend.iIndex = lpMsg->iIndex;
    pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
    pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
    pMsgSend.iBuyCost = lpMsg->iBuyCost;

    int iQueryResult = 0;

    int iRES = DSDB_QueryCastleNpcBuy(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }
    else
    {
        pMsgSend.iResult = iQueryResult;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCBUY));
}

BOOL DSDB_QueryCastleNpcRepair(int iMapSvrGroup, CSP_REQ_NPCREPAIR* lpNpcRepair, CSP_ANS_NPCREPAIR* lpNpcRepairResult, int* lpiResult)
{
    if (lpNpcRepair == NULL || lpNpcRepairResult == NULL)
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_ReqNpcRepair %d, %d, %d",
                iMapSvrGroup, lpNpcRepair->iNpcNumber, lpNpcRepair->iNpcIndex);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA )
    {
        gDataBase.Clear();
        return TRUE;
    }

    *lpiResult = gDataBase.GetInt("QueryResult");

    lpNpcRepairResult->iNpcHp = gDataBase.GetInt("NPC_HP");
    lpNpcRepairResult->iNpcMaxHp = gDataBase.GetInt("NPC_MAXHP");

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsCastleNpcRepair(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCREPAIR* lpMsg = (CSP_REQ_NPCREPAIR*)aRecv;
    CSP_ANS_NPCREPAIR pMsgSend;

    pMsgSend.h.set(0x80, 0x04, sizeof(CSP_ANS_NPCREPAIR));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
    pMsgSend.iIndex = lpMsg->iIndex;
    pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
    pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
    pMsgSend.iRepairCost = lpMsg->iRepairCost;

    int iQueryResult = 0;

    int iRES = DSDB_QueryCastleNpcRepair(lpMsg->wMapSvrNum, lpMsg, &pMsgSend, &iQueryResult);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }
    else
    {
        pMsgSend.iResult = iQueryResult;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCREPAIR));
}

BOOL DSDB_QueryCastleNpcUpgrade(int iMapSvrGroup, CSP_REQ_NPCUPGRADE* lpNpcUpgrade)
{
    if (lpNpcUpgrade == NULL)
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_ReqNpcUpgrade %d, %d, %d, %d, %d", iMapSvrGroup, lpNpcUpgrade->iNpcNumber, lpNpcUpgrade->iNpcIndex, lpNpcUpgrade->iNpcUpType, lpNpcUpgrade->iNpcUpValue);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    int iResult = gDataBase.GetInt("QueryResult");

    if (iResult == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();

    return FALSE;
}


void DataServer_Protocol::GS_DGAnsCastleNpcUpgrade(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCUPGRADE* lpMsg = (CSP_REQ_NPCUPGRADE*)aRecv;
    CSP_ANS_NPCUPGRADE pMsgSend;

    pMsgSend.h.set(0x80, 0x05, sizeof(CSP_ANS_NPCUPGRADE));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
    pMsgSend.iIndex = lpMsg->iIndex;
    pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
    pMsgSend.iNpcIndex = lpMsg->iNpcIndex;
    pMsgSend.iNpcUpType = lpMsg->iNpcUpType;
    pMsgSend.iNpcUpValue = lpMsg->iNpcUpValue;
    pMsgSend.iNpcUpIndex = lpMsg->iNpcUpIndex;

    int iRES = DSDB_QueryCastleNpcUpgrade(lpMsg->wMapSvrNum, lpMsg);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }
    else
    {
        pMsgSend.iResult = 1;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCUPGRADE));
}


void DataServer_Protocol::GS_DGAnsTaxInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_TAXINFO * aRecv)
{
    CSP_ANS_TAXINFO pResult = { 0 };

    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x06, sizeof(pResult));

    pResult.iIndex = aRecv->iIndex;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;
    pResult.i64CastleMoney = 0;
    pResult.iResult = 0;
    pResult.iTaxHuntZone = 0;
    pResult.iTaxRateChaos = 0;
    pResult.iTaxRateStore = 0;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_GetCastleTaxInfo %d", aRecv->wMapSvrNum);

    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = 1;
        pResult.i64CastleMoney = gDataBase.GetInt64("MONEY");
        pResult.iTaxRateChaos = gDataBase.GetInt("TAX_RATE_CHAOS");
        pResult.iTaxRateStore = gDataBase.GetInt("TAX_RATE_STORE");
        pResult.iTaxHuntZone = gDataBase.GetInt("TAX_HUNT_ZONE");
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsTaxRateChange(DataServer_Manager * Service, int aIndex, CSP_REQ_TAXRATECHANGE * aRecv)
{
    CSP_ANS_TAXRATECHANGE pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x07, sizeof(pResult));

    pResult.iIndex = aRecv->iIndex;
    pResult.iResult = 0;
    pResult.iTaxKind = aRecv->iTaxKind;
    pResult.iTaxRate = aRecv->iTaxRate;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyTaxRate %d,%d,%d", aRecv->wMapSvrNum, aRecv->iTaxKind, aRecv->iTaxRate);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
        pResult.iTaxKind = gDataBase.GetInt("TaxKind");
        pResult.iTaxRate = gDataBase.GetInt("TaxRate");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsCastleMoneyChange(DataServer_Manager * Service, int aIndex, CSP_REQ_MONEYCHANGE * aRecv)
{
    CSP_ANS_MONEYCHANGE pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x08, sizeof(pResult));

    pResult.i64CastleMoney = 0;
    pResult.iIndex = aRecv->iIndex;
    pResult.iMoneyChanged = aRecv->iMoneyChanged;
    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyMoney %d,%d", aRecv->wMapSvrNum, aRecv->iMoneyChanged);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
        pResult.i64CastleMoney = gDataBase.GetInt64("MONEY");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsSiegeDateChange(DataServer_Manager * Service, int aIndex, CSP_REQ_SDEDCHANGE * aRecv)
{
    CSP_ANS_SDEDCHANGE pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x09, sizeof(pResult));

    pResult.btEndDay = aRecv->btEndDay;
    pResult.btEndMonth = aRecv->btEndMonth;
    pResult.btStartDay = aRecv->btStartDay;
    pResult.btStartMonth = aRecv->btStartMonth;
    pResult.iIndex = aRecv->iIndex;
    pResult.iResult = 0;
    pResult.wEndYear = aRecv->wEndYear;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;
    pResult.wStartYear = aRecv->wStartYear;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyCastleSchedule %d, '%d-%d-%d 00:00:00', '%d-%d-%d 00:00:00'", aRecv->wMapSvrNum, aRecv->wStartYear, aRecv->btStartMonth, aRecv->btStartDay, aRecv->wEndYear, aRecv->btEndMonth, aRecv->btEndDay);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsGuildMarkRegInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDREGINFO * aRecv)
{
    CSP_ANS_GUILDREGINFO pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x0A, sizeof(pResult));

    char szGuildName[9] = {'\0'};
    pResult.bIsGiveUp = 0;
    pResult.btRegRank = 0;
    pResult.iIndex = aRecv->iIndex;
    pResult.iRegMarkCount = 0;
    pResult.iResult = 0;
    memcpy(szGuildName, aRecv->szGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_GetGuildMarkRegInfo %d, '%s'", aRecv->wMapSvrNum, szGuildName);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = 1;
        pResult.iRegMarkCount = gDataBase.GetInt("REG_MARKS");
        pResult.btRegRank = (BYTE)gDataBase.GetInt("SEQ_NUM");
        pResult.bIsGiveUp = (gDataBase.GetInt("IS_GIVEUP") > 0)?true:false;
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsSiegeEndedChange(DataServer_Manager * Service, int aIndex, CSP_REQ_SIEGEENDCHANGE * aRecv)
{
    CSP_ANS_SIEGEENDCHANGE pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x0B, sizeof(pResult));

    pResult.bIsSiegeEnded = aRecv->bIsSiegeEnded;
    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifySiegeEnd %d, %d", aRecv->wMapSvrNum, aRecv->bIsSiegeEnded);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}

BOOL DSDB_QueryCastleOwnerChange(int iMapSvrGroup, CSP_REQ_CASTLEOWNERCHANGE* lpCastleOwnerInfo, CSP_ANS_CASTLEOWNERCHANGE* lpCastleOwnerInfoResult, int* lpiResult)
{
    if (lpCastleOwnerInfo == NULL || lpCastleOwnerInfoResult == NULL || lpiResult == NULL)
    {
        return TRUE;
    }

    char szGuildName[9] = {'\0'};
    memcpy(szGuildName, lpCastleOwnerInfo->szOwnerGuildName, 8);

    if (gFunc.CheckSQLSyntex(szGuildName) == FALSE)
    {
        return TRUE;
    }

    lpCastleOwnerInfoResult->bIsCastleOccupied = lpCastleOwnerInfo->bIsCastleOccupied;
    memcpy(lpCastleOwnerInfoResult->szOwnerGuildName, lpCastleOwnerInfo->szOwnerGuildName, 8);

    CString qSql;
    qSql.Format("EXEC WZ_CS_ModifyCastleOwnerInfo %d, %d, '%s'", iMapSvrGroup, lpCastleOwnerInfo->bIsCastleOccupied,szGuildName);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA )
    {
        gDataBase.Clear();
        return TRUE;
    }

    *lpiResult = gDataBase.GetInt("QueryResult");

    gDataBase.Clear();
    return FALSE;
}


void DataServer_Protocol::GS_DGAnsCastleOwnerChange(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CASTLEOWNERCHANGE* lpMsg = (CSP_REQ_CASTLEOWNERCHANGE*)aRecv;
    CSP_ANS_CASTLEOWNERCHANGE pMsgSend;

    gFunc.PHeadSubSetB((LPBYTE)&pMsgSend, 0x80, 0x0C, sizeof(CSP_ANS_CASTLEOWNERCHANGE));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

    int iQueryResult = 0;

    int iRES = DSDB_QueryCastleOwnerChange(lpMsg->wMapSvrNum, lpMsg, &pMsgSend, &iQueryResult);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }
    else
    {
        pMsgSend.iResult = iQueryResult;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CASTLEOWNERCHANGE));
}


void DataServer_Protocol::GS_DGAnsRegAttackGuild(DataServer_Manager * Service, int aIndex, CSP_REQ_REGATTACKGUILD * aRecv)
{
    CSP_ANS_REGATTACKGUILD pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x0D, sizeof(pResult));

    pResult.iIndex = aRecv->iIndex;
    pResult.iResult = 0;
    memcpy(pResult.szEnemyGuildName, aRecv->szEnemyGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    if (gFunc.CheckSQLSyntex(aRecv->szEnemyGuildName) == FALSE)
    {
        return;
    }
    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ReqRegAttackGuild %d, '%s'", aRecv->wMapSvrNum, aRecv->szEnemyGuildName);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsRestartCastleState(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLESIEGEEND * aRecv)
{
    CSP_ANS_CASTLESIEGEEND pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x0E, sizeof(pResult));

    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ResetCastleSiege %d", aRecv->wMapSvrNum);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsMapSvrMsgMultiCast(DataServer_Manager * Service, int aIndex, CSP_REQ_MAPSVRMULTICAST * aRecv)
{
    CSP_ANS_MAPSVRMULTICAST pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x0F, sizeof(pResult));

    memcpy(pResult.szMsgText, aRecv->szMsgText, 128);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;



    Service->DataSendAll((unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsRegGuildMark(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDREGMARK * aRecv)
{
    CSP_ANS_GUILDREGMARK pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x10, sizeof(pResult));

    pResult.iIndex = aRecv->iIndex;
    pResult.iItemPos = aRecv->iItemPos;
    pResult.iRegMarkCount = 0;
    pResult.iResult = 0;
    memcpy(pResult.szGuildName, aRecv->szGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    if (gFunc.CheckSQLSyntex(aRecv->szGuildName) == FALSE)
    {
        return;
    }
    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ReqRegGuildMark %d, '%s'", aRecv->wMapSvrNum, aRecv->szGuildName);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
        pResult.iRegMarkCount = gDataBase.GetInt("REG_MARKS");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsGuildMarkReset(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDRESETMARK * aRecv)
{
    CSP_ANS_GUILDRESETMARK pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x11, sizeof(pResult));

    pResult.iIndex = aRecv->iIndex;
    pResult.iRegMarkCount = 0;
    pResult.iResult = 0;
    memcpy(pResult.szGuildName, aRecv->szGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    if (gFunc.CheckSQLSyntex(aRecv->szGuildName) == FALSE)
    {
        return;
    }
    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyGuildMarkReset %d, '%s'", aRecv->wMapSvrNum, aRecv->szGuildName);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
        pResult.iRegMarkCount = gDataBase.GetInt("DEL_MARKS");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsGuildSetGiveUp(DataServer_Manager * Service, int aIndex, CSP_REQ_GUILDSETGIVEUP * aRecv)
{
    CSP_ANS_GUILDSETGIVEUP pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x12, sizeof(pResult));

    pResult.bIsGiveUp = aRecv->bIsGiveUp;
    pResult.iIndex = aRecv->iIndex;
    pResult.iRegMarkCount = 0;
    pResult.iResult = 0;
    memcpy(pResult.szGuildName, aRecv->szGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    if (gFunc.CheckSQLSyntex(aRecv->szGuildName) == FALSE)
    {
        return;
    }
    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyGuildGiveUp %d, '%s', %d", aRecv->wMapSvrNum, aRecv->szGuildName, aRecv->bIsGiveUp);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
        pResult.iRegMarkCount = gDataBase.GetInt("DEL_MARKS");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}

BOOL DSDB_QueryCastleNpcRemove(int iMapSvrGroup, CSP_REQ_NPCREMOVE* lpNpcRemove, int* lpiResult)
{
    if (lpNpcRemove == NULL)
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_ReqNpcRemove %d, %d, %d",iMapSvrGroup,lpNpcRemove->iNpcNumber,lpNpcRemove->iNpcIndex);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    if (sqlRet == SQL_NO_DATA || sqlRet == SQL_NULL_DATA )
    {
        gDataBase.Clear();
        return TRUE;
    }

    *lpiResult = gDataBase.GetInt("QueryResult");

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsNpcRemove(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCREMOVE* lpMsg = (CSP_REQ_NPCREMOVE*)aRecv;
    CSP_ANS_NPCREMOVE pMsgSend;

    pMsgSend.h.set(0x80, 0x16, sizeof(CSP_ANS_NPCREMOVE));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;
    pMsgSend.iNpcNumber = lpMsg->iNpcNumber;
    pMsgSend.iNpcIndex = lpMsg->iNpcIndex;

    int iQueryResult = 0;

    int iRES = DSDB_QueryCastleNpcRemove(lpMsg->wMapSvrNum, lpMsg, &iQueryResult);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
    }
    else
    {
        pMsgSend.iResult = iQueryResult;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCREMOVE));
}


void DataServer_Protocol::GS_DGAnsCastleStateSync(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLESTATESYNC * aRecv)
{
    CSP_ANS_CASTLESTATESYNC pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x17, sizeof(pResult));

    pResult.iCastleState = aRecv->iCastleState;
    pResult.iTaxHuntZone = aRecv->iTaxHuntZone;
    pResult.iTaxRateChaos = aRecv->iTaxRateChaos;
    pResult.iTaxRateStore = aRecv->iTaxRateStore;
    memcpy(pResult.szOwnerGuildName, aRecv->szOwnerGuildName, 8);
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    Service->DataSendAll((unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsCastleTributeMoney(DataServer_Manager * Service, int aIndex, CSP_REQ_CASTLETRIBUTEMONEY * aRecv)
{
    CSP_ANS_CASTLETRIBUTEMONEY pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x18, sizeof(pResult));

    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    if (aRecv->iCastleTributeMoney < 0)aRecv->iCastleTributeMoney = 0;
    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ModifyMoney %d, %d", aRecv->wMapSvrNum, aRecv->iCastleTributeMoney);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsResetCastleTaxInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETCASTLETAXINFO * aRecv)
{
    CSP_ANS_RESETCASTLETAXINFO pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x19, sizeof(pResult));

    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ResetCastleTaxInfo %d", aRecv->wMapSvrNum);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsResetSiegeGuildInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETSIEGEGUILDINFO * aRecv)
{
    CSP_ANS_RESETSIEGEGUILDINFO pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x1A, sizeof(pResult));

    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ResetSiegeGuildInfo %d", aRecv->wMapSvrNum);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::GS_DGAnsResetRegSiegeInfo(DataServer_Manager * Service, int aIndex, CSP_REQ_RESETREGSIEGEINFO * aRecv)
{
    CSP_ANS_RESETREGSIEGEINFO pResult;
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0x80, 0x1B, sizeof(pResult));

    pResult.iResult = 0;
    pResult.wMapSvrNum = aRecv->wMapSvrNum;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CS_ResetRegSiegeInfo %d", aRecv->wMapSvrNum);
    if ((bRet == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.iResult = gDataBase.GetInt("QueryResult");
    }
    gDataBase.Clear();
    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}

int DSDB_QueryCastleNpcInfo(int iMapSvrGroup, CSP_NPCDATA* lpNpcData, int* lpiCount)
{
    if (lpNpcData == NULL || lpiCount == NULL)
    {
        return TRUE;
    }

    int iMAX_COUNT = *lpiCount;
    *lpiCount=0;

    CString qSql;
    qSql.Format("EXEC WZ_CS_GetCastleNpcInfo %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    while(sqlRet != SQL_NO_DATA && sqlRet != SQL_NULL_DATA)
    {
        if (*lpiCount > iMAX_COUNT)
        {
            break;
        }

        lpNpcData[*lpiCount].iNpcNumber = gDataBase.GetInt("NPC_NUMBER");
        lpNpcData[*lpiCount].iNpcIndex = gDataBase.GetInt("NPC_INDEX");
        lpNpcData[*lpiCount].iNpcDfLevel = gDataBase.GetInt("NPC_DF_LEVEL");
        lpNpcData[*lpiCount].iNpcRgLevel = gDataBase.GetInt("NPC_RG_LEVEL");
        lpNpcData[*lpiCount].iNpcMaxHp = gDataBase.GetInt("NPC_MAXHP");
        lpNpcData[*lpiCount].iNpcHp = gDataBase.GetInt("NPC_HP");
        lpNpcData[*lpiCount].btNpcX = gDataBase.GetInt("NPC_X");
        lpNpcData[*lpiCount].btNpcY = gDataBase.GetInt("NPC_Y");
        lpNpcData[*lpiCount].btNpcDIR = gDataBase.GetInt("NPC_DIR");

        *lpiCount = *lpiCount + 1;

        sqlRet = gDataBase.Fetch();
    }

    if (sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsCastleInitData(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CSINITDATA* lpMsg = (CSP_REQ_CSINITDATA*)aRecv;
    CASTLE_DATA pCastleData = {0};

    char cBUFFER[5920] = "";

    CSP_ANS_CSINITDATA* lpMsgSend = (CSP_ANS_CSINITDATA*)cBUFFER;
    CSP_NPCDATA* lpMsgSendBody = (CSP_NPCDATA *)&cBUFFER[64];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

    int iDataCount = 200;

    lpMsgSend->iCount = 0;

    int iRES = DSDB_QueryCastleTotalInfo(lpMsg->wMapSvrNum, lpMsg->iCastleEventCycle, &pCastleData);

    if ( iRES != 0)
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->h.Set(0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
    }
    else
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->wStartYear = pCastleData.wStartYear;
        lpMsgSend->btStartMonth = pCastleData.btStartMonth;
        lpMsgSend->btStartDay = pCastleData.btStartDay;
        lpMsgSend->wEndYear = pCastleData.wEndYear;
        lpMsgSend->btEndMonth = pCastleData.btEndMonth;
        lpMsgSend->btEndDay = pCastleData.btEndDay;
        lpMsgSend->btIsSiegeGuildList = pCastleData.btIsSiegeGuildList;
        lpMsgSend->btIsSiegeEnded = pCastleData.btIsSiegeEnded;
        lpMsgSend->btIsCastleOccupied = pCastleData.btIsCastleOccupied;
        lpMsgSend->i64CastleMoney = pCastleData.i64CastleMoney;
        lpMsgSend->iTaxRateChaos = pCastleData.iTaxRateChaos;
        lpMsgSend->iTaxRateStore = pCastleData.iTaxRateStore;
        lpMsgSend->iTaxHuntZone = pCastleData.iTaxHuntZone;
        lpMsgSend->iFirstCreate = pCastleData.iFirstCreate;

        memset(lpMsgSend->szCastleOwnGuild, 0, 8);
        memcpy(lpMsgSend->szCastleOwnGuild, pCastleData.szCastleOwnGuild, 8);

        iRES = DSDB_QueryCastleNpcInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

        if ( iRES != 0)
        {
            lpMsgSend->iResult = 0;
            lpMsgSend->h.Set(0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
            Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
        }
        else
        {
            lpMsgSend->iResult = 1;
            lpMsgSend->iCount = iDataCount;
            lpMsgSend->h.Set(0x81, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
            Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSINITDATA));
        }
    }
}

BOOL DSDB_QueryAllGuildMarkRegInfo(int iMapSvrGroup, CSP_GUILDREGINFO* lpGuildRegInfo, int* lpiCount)
{
    if (lpGuildRegInfo == NULL || lpiCount == NULL)
    {
        return TRUE;
    }

    int iMAX_COUNT = *lpiCount;

    if ( iMAX_COUNT > 100 )
    {
        iMAX_COUNT = 100;
    }

    *lpiCount=0;

    CString qSql;
    qSql.Format("EXEC WZ_CS_GetAllGuildMarkRegInfo %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    while(sqlRet != SQL_NO_DATA && sqlRet != SQL_NULL_DATA)
    {
        if (*lpiCount > iMAX_COUNT)
        {
            break;
        }

        gDataBase.GetStr("REG_SIEGE_GUILD", lpGuildRegInfo[*lpiCount].szGuildName);
        lpGuildRegInfo[*lpiCount].iRegMarkCount = gDataBase.GetInt("REG_MARKS");
        lpGuildRegInfo[*lpiCount].bIsGiveUp = (gDataBase.GetInt("IS_GIVEUP") > 0)?true:false;
        lpGuildRegInfo[*lpiCount].btRegRank = gDataBase.GetInt("SEQ_NUM");

        *lpiCount = *lpiCount + 1;

        sqlRet = gDataBase.Fetch();
    }

    if (sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsAllGuildMarkRegInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_ALLGUILDREGINFO* lpMsg = (CSP_REQ_ALLGUILDREGINFO*)aRecv;

    char cBUFFER[1876];

    CSP_ANS_ALLGUILDREGINFO* lpMsgSend = (CSP_ANS_ALLGUILDREGINFO*)cBUFFER;
    CSP_GUILDREGINFO* lpMsgSendBody = (CSP_GUILDREGINFO *)&cBUFFER[20];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;
    lpMsgSend->iIndex = lpMsg->iIndex;

    int iDataCount = 100;

    lpMsgSend->iCount = 0;

    int iRES = DSDB_QueryAllGuildMarkRegInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

    if (iRES != 0)
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->h.Set(0x83, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
    }
    else
    {
        lpMsgSend->iResult = 1;
        lpMsgSend->iCount = iDataCount;
        lpMsgSend->h.Set(0x83, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_GUILDREGINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_ALLGUILDREGINFO));
    }
}

BOOL DSDB_QueryFirstCreateNPC(int iMapSvrGroup, CSP_REQ_NPCSAVEDATA* lpNpcSaveData)
{
    if (lpNpcSaveData == NULL)
    {
        return TRUE;
    }

    CSP_NPCSAVEDATA* lpMsgBody = (CSP_NPCSAVEDATA*)&lpNpcSaveData[1];

    gDataBase.ExecFormat("DELETE MuCastle_NPC WHERE MAP_SVR_GROUP = %d",iMapSvrGroup);
    gDataBase.Clear();

    LogAddC(eDebug,"DSDB_QueryFirstCreateNPC");

    for (int iNPC_COUNT = 0; iNPC_COUNT < lpNpcSaveData->iCount; iNPC_COUNT++)
    {
        gDataBase.ExecFormat("EXEC WZ_CS_ReqNpcBuy %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                             iMapSvrGroup,lpMsgBody[iNPC_COUNT].iNpcNumber,lpMsgBody[iNPC_COUNT].iNpcIndex,
                             lpMsgBody[iNPC_COUNT].iNpcDfLevel,lpMsgBody[iNPC_COUNT].iNpcRgLevel,
                             lpMsgBody[iNPC_COUNT].iNpcMaxHp,lpMsgBody[iNPC_COUNT].iNpcHp,
                             lpMsgBody[iNPC_COUNT].btNpcX,lpMsgBody[iNPC_COUNT].btNpcY,
                             lpMsgBody[iNPC_COUNT].btNpcDIR);

        gDataBase.Clear();
    }

    return FALSE;
}

void DataServer_Protocol::GS_DGAnsFirstCreateNPC(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCSAVEDATA* lpMsg = (CSP_REQ_NPCSAVEDATA*)aRecv;

    CSP_ANS_NPCSAVEDATA pMsgSend;
    pMsgSend.h.Set(0x84, sizeof(CSP_ANS_NPCSAVEDATA));
    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

    int iRES = DSDB_QueryFirstCreateNPC(lpMsg->wMapSvrNum,lpMsg);

    if (iRES != 0)
    {
        pMsgSend.iResult = 0;
        Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCSAVEDATA));
    }
    else
    {
        pMsgSend.iResult = 1;
        Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_NPCSAVEDATA));
    }
}

BOOL DSDB_QueryCalcRegGuildList(int iMapSvrGroup, CSP_CALCREGGUILDLIST* lpCalcRegGuildList, int* lpiCount)
{
    if (lpCalcRegGuildList == NULL || lpiCount == NULL)
    {
        return TRUE;
    }

    int iMAX_COUNT = *lpiCount;

    if ( iMAX_COUNT > 100 )
    {
        iMAX_COUNT = 100;
    }

    *lpiCount=0;

    CString qSql;
    qSql.Format("EXEC WZ_CS_GetCalcRegGuildList %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    while(sqlRet != SQL_NO_DATA && sqlRet != SQL_NULL_DATA)
    {
        if (*lpiCount > iMAX_COUNT)
        {
            break;
        }

        char szGuildName[9] = {'\0'};

        gDataBase.GetStr("REG_SIEGE_GUILD", szGuildName);

        memcpy(&lpCalcRegGuildList[*lpiCount], szGuildName, 8);

        lpCalcRegGuildList[*lpiCount].iRegMarkCount = gDataBase.GetInt("REG_MARKS");
        lpCalcRegGuildList[*lpiCount].iGuildMemberCount = gDataBase.GetInt("GUILD_MEMBER");
        lpCalcRegGuildList[*lpiCount].iGuildMasterLevel = gDataBase.GetInt("GM_LEVEL");
        lpCalcRegGuildList[*lpiCount].iSeqNum = gDataBase.GetInt("SEQ_NUM");

        *lpiCount = *lpiCount + 1;

        sqlRet = gDataBase.Fetch();
    }

    if (sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}

void DataServer_Protocol::GS_DGAnsCalcRegGuildList(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CALCREGGUILDLIST* lpMsg = (CSP_REQ_CALCREGGUILDLIST*)aRecv;
    char cBUFFER[2672];

    CSP_ANS_CALCREGGUILDLIST* lpMsgSend = (CSP_ANS_CALCREGGUILDLIST*)cBUFFER;
    CSP_CALCREGGUILDLIST* lpMsgSendBody = (CSP_CALCREGGUILDLIST *)&cBUFFER[16];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

    int iDataCount = 100;

    lpMsgSend->iCount = 0;

    int iRES = DSDB_QueryCalcRegGuildList(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

    if (iRES != 0)
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->h.Set(0x85, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
    }
    else
    {
        lpMsgSend->iResult = 1;
        lpMsgSend->iCount = iDataCount;
        lpMsgSend->h.Set(0x85, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CALCREGGUILDLIST) * lpMsgSend->iCount) + sizeof(CSP_ANS_CALCREGGUILDLIST));
    }
}


BOOL DSDB_QueryCsGuildUnionInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID, CSP_CSGUILDUNIONINFO* lpCsGuildUnionInfo, int* lpiCount)
{
    if (lpszGuildName == NULL || lpCsGuildUnionInfo == NULL || lpiCount == NULL)
    {
        return TRUE;
    }

    int iRET_COUNT = *lpiCount;

    if ( iRET_COUNT < 0 )
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_GetCsGuildUnionInfo '%s'",lpszGuildName);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    short sqlRet = gDataBase.Fetch();

    while(sqlRet != SQL_NO_DATA && sqlRet != SQL_NULL_DATA)
    {
        if (iRET_COUNT > 100)
        {
            break;
        }

        char szGuildName[9] = {'\0'};

        gDataBase.GetStr("GUILD_NAME", szGuildName);

        memcpy(&lpCsGuildUnionInfo[iRET_COUNT], szGuildName, 8);
        lpCsGuildUnionInfo[iRET_COUNT].iCsGuildID = iCsGuildID;

        iRET_COUNT++;

        sqlRet = gDataBase.Fetch();
    }

    if (sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();

    *lpiCount = iRET_COUNT;

    return FALSE;
}


void DataServer_Protocol::GS_DGAnsCsGulidUnionInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CSGUILDUNIONINFO* lpMsg = (CSP_REQ_CSGUILDUNIONINFO*)aRecv;
    CSP_CSGUILDUNIONINFO* lpMsgBody = (CSP_CSGUILDUNIONINFO*)&aRecv[12];

    char cBUFFER[1472];

    CSP_ANS_CSGUILDUNIONINFO* lpMsgSend = (CSP_ANS_CSGUILDUNIONINFO*)cBUFFER;
    CSP_CSGUILDUNIONINFO* lpMsgSendBody = (CSP_CSGUILDUNIONINFO *)&cBUFFER[16];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

    if (lpMsg->iCount < 0)
    {
        lpMsg->iCount = 0;
    }

    int iRET_COUNT = 0;

    for (int iGCNT=0; iGCNT < lpMsg->iCount; iGCNT++)
    {
        char szGuildName[9] = {'\0'};
        memcpy(szGuildName, lpMsgBody[iGCNT].szGuildName, 8);

        int iRES = DSDB_QueryCsGuildUnionInfo(lpMsg->wMapSvrNum, szGuildName, lpMsgBody[iGCNT].iCsGuildID, lpMsgSendBody, &iRET_COUNT);

        if (iRES != 0)
        {
            lpMsgSend->iResult = 0;
            lpMsgSend->iCount = 0;
            lpMsgSend->h.Set(0x86, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
            Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
            return;
        }
    }

    lpMsgSend->iResult = 1;
    lpMsgSend->iCount = iRET_COUNT;
    lpMsgSend->h.Set(0x86, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
    Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CSGUILDUNIONINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSGUILDUNIONINFO));
}

BOOL DSDB_QueryCsClearTotalGuildInfo(int iMapSvrGroup)
{
    CString qSql;
    qSql.Format("DELETE MuCastle_SIEGE_GUILDLIST WHERE MAP_SVR_GROUP = %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}

BOOL DSDB_QueryCsSaveTotalGuildInfo(int iMapSvrGroup, char* lpszGuildName, int iCsGuildID, int iCsGuildInvolved, int iCsGuildScore)
{
    if (lpszGuildName == NULL)
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_SetSiegeGuildInfo %d, '%s', %d, %d",
                iMapSvrGroup, lpszGuildName, iCsGuildID, iCsGuildInvolved);

    //qSql.Format("EXEC WZ_CS_SetSiegeGuildInfo %d, '%s', %d, %d, %d",
    //	iMapSvrGroup, lpszGuildName, iCsGuildID, iCsGuildInvolved, iCsGuildScore);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}

BOOL DSDB_QueryCsSaveTotalGuildOK(int iMapSvrGroup, int* lpiResult)
{
    if (lpiResult == NULL)
    {
        return TRUE;
    }

    CString qSql;
    qSql.Format("EXEC WZ_CS_SetSiegeGuildOK %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }

    *lpiResult = gDataBase.GetInt("QueryResult");

    gDataBase.Clear();
    return FALSE;
}


void DataServer_Protocol::GS_DGAnsCsSaveTotalGuildInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CSSAVETOTALGUILDINFO* lpMsg = (CSP_REQ_CSSAVETOTALGUILDINFO*)aRecv;
    CSP_CSSAVETOTALGUILDINFO* lpMsgBody = (CSP_CSSAVETOTALGUILDINFO*)&aRecv[12];

    CSP_ANS_CSSAVETOTALGUILDINFO pMsgSend;

    pMsgSend.wMapSvrNum = lpMsg->wMapSvrNum;

    int iRES = DSDB_QueryCsClearTotalGuildInfo(lpMsg->wMapSvrNum);

    if ( iRES != 0)
    {
        pMsgSend.iResult = 0;
        pMsgSend.h.Set(0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
        Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
    }
    else
    {
        for (int iGCNT = 0; iGCNT < lpMsg->iCount; iGCNT++)
        {
            char szGuildName[9] = {'\0'};
            memcpy(szGuildName, lpMsgBody[iGCNT].szGuildName, 8);

            iRES = DSDB_QueryCsSaveTotalGuildInfo(lpMsg->wMapSvrNum, szGuildName, lpMsgBody[iGCNT].iCsGuildID,lpMsgBody[iGCNT].iGuildInvolved,lpMsgBody[iGCNT].iGuildScore);

            if (iRES != 0)
            {
                pMsgSend.iResult = 0;
                pMsgSend.h.Set(0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
                Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
                return;
            }
        }

        int iQueryResult = 0;

        iRES = DSDB_QueryCsSaveTotalGuildOK(lpMsg->wMapSvrNum, &iQueryResult);

        if ( iRES != 0)
        {
            pMsgSend.iResult = 0;
            pMsgSend.h.Set(0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
            Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
        }
        else
        {
            pMsgSend.iResult = 1;
            pMsgSend.h.Set(0x87, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
            Service->DataSend(aIndex, (unsigned char*)&pMsgSend, sizeof(CSP_ANS_CSSAVETOTALGUILDINFO));
        }
    }
}

BOOL DSDB_QueryCsLoadTotalGuildInfo(int iMapSvrGroup, CSP_CSLOADTOTALGUILDINFO* lpLoadTotalGuildInfo, int* lpiCount)
{
    if (lpLoadTotalGuildInfo == NULL || lpiCount == NULL)
    {
        return TRUE;
    }

    int iMAX_COUNT = *lpiCount;

    if ( iMAX_COUNT > 100 )
    {
        iMAX_COUNT = 100;
    }

    *lpiCount=0;

    CString qSql;
    qSql.Format("EXEC WZ_CS_GetSiegeGuildInfo %d",iMapSvrGroup);

    if (gDataBase.Exec(qSql) == FALSE)
    {
        gDataBase.Clear();
        return TRUE;
    }
    short sqlRet = gDataBase.Fetch();

    while(sqlRet != SQL_NO_DATA && sqlRet != SQL_NULL_DATA)
    {
        if (*lpiCount > iMAX_COUNT)
        {
            break;
        }

        char szGuildName[9] = {'\0'};

        gDataBase.GetStr("GUILD_NAME", szGuildName);

        memcpy(&lpLoadTotalGuildInfo[*lpiCount], szGuildName, 8);

        lpLoadTotalGuildInfo[*lpiCount].iCsGuildID = gDataBase.GetInt("GUILD_ID");
        lpLoadTotalGuildInfo[*lpiCount].iGuildInvolved = gDataBase.GetInt("GUILD_INVOLVED");
        lpLoadTotalGuildInfo[*lpiCount].iGuildScore = gDataBase.GetInt("GUILD_SCORE");

        *lpiCount = *lpiCount + 1;

        sqlRet = gDataBase.Fetch();
    }

    if (sqlRet == SQL_NULL_DATA)
    {
        gDataBase.Clear();
        return TRUE;
    }

    gDataBase.Clear();
    return FALSE;
}


void DataServer_Protocol::GS_DGAnsCsLoadTotalGuildInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_CSLOADTOTALGUILDINFO* lpMsg = (CSP_REQ_CSLOADTOTALGUILDINFO*)aRecv;
    char cBUFFER[2272];

    CSP_ANS_CSLOADTOTALGUILDINFO* lpMsgSend = (CSP_ANS_CSLOADTOTALGUILDINFO*)cBUFFER;
    CSP_CSLOADTOTALGUILDINFO* lpMsgSendBody = (CSP_CSLOADTOTALGUILDINFO *)&cBUFFER[16];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

    int iDataCount = 100;

    lpMsgSend->iCount = 0;

    int iRES = DSDB_QueryCsLoadTotalGuildInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

    if (iRES != 0)
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->h.Set(0x88, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
    }
    else
    {
        lpMsgSend->iResult = 1;
        lpMsgSend->iCount = iDataCount;
        lpMsgSend->h.Set(0x88, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_CSLOADTOTALGUILDINFO) * lpMsgSend->iCount) + sizeof(CSP_ANS_CSLOADTOTALGUILDINFO));
    }
}

BOOL DSDB_QueryCastleNpcUpdate(int iMapSvrGroup, CSP_REQ_NPCUPDATEDATA* lpNpcSaveData)
{
    if (lpNpcSaveData == NULL)
    {
        return TRUE;
    }

    CSP_NPCSAVEDATA* lpMsgBody = (CSP_NPCSAVEDATA*)&lpNpcSaveData[1];

    gDataBase.ExecFormat("DELETE MuCastle_NPC WHERE MAP_SVR_GROUP = %d",iMapSvrGroup);
    gDataBase.Clear();

    LogAddC(eDebug,"DSDB_QueryCastleNpcUpdate");

    for (int iNPC_COUNT = 0; iNPC_COUNT < lpNpcSaveData->iCount; iNPC_COUNT++)
    {
        gDataBase.ExecFormat("EXEC WZ_CS_ReqNpcUpdate %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
                             iMapSvrGroup,lpMsgBody[iNPC_COUNT].iNpcNumber,lpMsgBody[iNPC_COUNT].iNpcIndex,
                             lpMsgBody[iNPC_COUNT].iNpcDfLevel,lpMsgBody[iNPC_COUNT].iNpcRgLevel,
                             lpMsgBody[iNPC_COUNT].iNpcMaxHp,lpMsgBody[iNPC_COUNT].iNpcHp,
                             lpMsgBody[iNPC_COUNT].btNpcX,lpMsgBody[iNPC_COUNT].btNpcY,
                             lpMsgBody[iNPC_COUNT].btNpcDIR);

        gDataBase.Clear();
    }

    return FALSE;
}

void DataServer_Protocol::GS_DGAnsCastleNpcUpdate(DataServer_Manager * Service, int aIndex, CSP_REQ_NPCUPDATEDATA * aRecv)
{
    CSP_ANS_NPCUPDATEDATA pResult = {0};
    gFunc.PHeadSetW((LPBYTE)&pResult, 0x89, sizeof(pResult));
    pResult.wMapSvrNum = aRecv->wMapSvrNum;
    pResult.iResult = 0;

    int lOfs=sizeof(CSP_REQ_NPCUPDATEDATA);

    BOOL bRet = gDataBase.ExecFormat("DELETE FROM MuCastle_NPC WHERE MAP_SVR_GROUP = %d",aRecv->wMapSvrNum);
    if (bRet != FALSE )
    {
        if(aRecv->iCount > 0)
        {
            int Counter = 0;
            while(Counter<aRecv->iCount)
            {
                gDataBase.Clear();
                CSP_NPCUPDATEDATA * NPCInfo = (CSP_NPCUPDATEDATA*)((LPBYTE)aRecv + lOfs);
                bRet = gDataBase.ExecFormat("EXEC WZ_CS_ReqNpcUpdate %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",aRecv->wMapSvrNum,NPCInfo->iNpcNumber,NPCInfo->iNpcIndex,NPCInfo->iNpcDfLevel,NPCInfo->iNpcRgLevel,NPCInfo->iNpcMaxHp,NPCInfo->iNpcHp,NPCInfo->btNpcX,NPCInfo->btNpcY,NPCInfo->btNpcDIR);
                if (bRet == FALSE )
                {
                    gDataBase.Clear();
                    break;
                }
                Counter++;
                lOfs+=sizeof(CSP_NPCUPDATEDATA);
            }
            pResult.iResult = 1;
        }
    }
    Service->DataSend(aIndex, (unsigned char*)&pResult,sizeof(pResult));
}


void DataServer_Protocol::DGAnsCrywolfSync(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFSYNC * aRecv)
{
    if (aRecv == NULL)
    {
        return;
    }
    CWP_ANS_CRYWOLFSYNC pResult = { 0 };

    pResult.h.Set(0xB0, sizeof(pResult));

    pResult.iCrywolfState = aRecv->iCrywolfState;
    pResult.iOccupationState = aRecv->iOccupationState;
    pResult.btResult = 1;

    Service->DataSendAll((unsigned char*)&pResult, sizeof(pResult));
}


void DataServer_Protocol::DGAnsCrywolfInfoLoad(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFINFOLOAD * aRecv)
{
    CWP_ANS_CRYWOLFINFOLOAD pResult = { 0 };
    pResult.h.Set(0xB1, sizeof(pResult));

    pResult.btResult = 0;
    pResult.iCrywolfState = 0;
    pResult.iOccupationState = 0;

    bool bRet = gDataBase.ExecFormat("EXEC WZ_CW_InfoLoad %d", aRecv->wMapSvrNum);

    if (bRet == TRUE)
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            pResult.btResult = 1;
            pResult.iCrywolfState = gDataBase.GetInt("CRYWOLF_STATE");
            pResult.iOccupationState = gDataBase.GetInt("CRYWOLF_OCCUFY");
        }
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::RequestMasterLevelInfoLoad(DataServer_Manager * Service, int aIndex, PMSG_REQ_ML_INFO_LOAD * aRecv)
{
    PMSG_ANS_ML_INFO_LOAD pResult = { 0 };
    pResult.h.Set(0x30, sizeof(pResult));

    if (aRecv == NULL)
    {
        return;
    }

    char szId[11] = { 0 };

    memcpy(szId, aRecv->chCharacterName, 10);

    int len = strlen(szId);

    if (len <= 0 || len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    bool Return = gDataBase.ExecFormat("EXEC WZ_MLS_InfoLoad '%s'", szId);

    if (Return == true)
    {
        if (gDataBase.Fetch() != SQL_NO_DATA)
        {
            pResult.Result = 1;

            pResult.Index = aRecv->iUserIndex;
            pResult.MLevel = (__int16)gDataBase.GetInt("MASTER_LEVEL");
            pResult.MLExp = (__int64)gDataBase.GetInt("ML_EXP");
            pResult.MLNextExp = (__int64)gDataBase.GetInt("ML_NEXTEXP");
            pResult.MLPoint = (__int16)gDataBase.GetInt("ML_POINT");

            memcpy(pResult.szName, szId, 10);
        }
    }
    else
    {
        pResult.Result = 0;
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::RequestMasterLevelInfoSave(DataServer_Manager * Service, int aIndex, PMSG_REQ_ML_INFO_SAVE * aRecv)
{
    if (aRecv == NULL)
    {
        return;
    }

    char szId[11] = { 0 };

    memcpy(szId, aRecv->chCharacterName, 10);

    int len = strlen(szId);

    if (len <= 0 || len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    gDataBase.ExecFormat("WZ_MLS_InfoSave '%s', %d, %I64d, %I64d, %d",
                         szId, aRecv->MLevel, aRecv->MLExp, aRecv->MLNextExp, aRecv->MLPoint);

    gDataBase.Clear();
}


void DataServer_Protocol::PeriodItemInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_INSERT * aRecv)
{
    PMSG_ANS_PERIODITEM_INSERT pResult = { 0 };
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0xD0, 0x04, sizeof(pResult));

    char UserID[11] = { 0 };
    char ExpireDate[21] = { 0 };

    memcpy(UserID, aRecv->chUserID, 10);
    memcpy(ExpireDate, aRecv->chExpireDate, 20);

    int Len = strlen(UserID);

    if (Len <= 0 || Len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    bool Return = gDataBase.ExecFormat("EXEC WZ_PeriodItemInsert %d, '%s', %d, %d, %d, %d, %d, '%s'",
                                       aRecv->iUserGuid, UserID, aRecv->iItemCode, aRecv->btOptionType,
                                       aRecv->btItemEffectType1, aRecv->btItemEffectType2, aRecv->iItemPeriodDate, ExpireDate);

    if ((Return == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.btResult = 1;

        pResult.iUserIndex = aRecv->iUserIndex;
        pResult.iItemCode = aRecv->iItemCode;
        pResult.btItemEffectType1 = (__int16)aRecv->btItemEffectType1;
        pResult.btItemEffectType2 = (__int16)aRecv->btItemEffectType2;
        pResult.iItemPeriodDate = aRecv->iItemPeriodDate;
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::PeriodItemDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_DELETE * aRecv)
{
    char CharacterName[11] = { 0 };

    memcpy(CharacterName, aRecv->chCharacterName, 10);

    int Len = strlen(CharacterName);

    if (Len <= 0 || Len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    gDataBase.ExecFormat("EXEC WZ_PeriodItemDelete %d, '%s'", aRecv->iUserGuid, CharacterName);

    gDataBase.Clear();
}


void DataServer_Protocol::PeriodItemUpdate(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_UPDATE * aRecv)
{
    PMSG_ANS_PERIODITEM_UPDATE pResult = { 0 };
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0xD0, 0x08, sizeof(pResult));

    char CharacterName[11] = { 0 };

    memcpy(CharacterName, aRecv->chCharacterName, 10);

    int Len = strlen(CharacterName);

    if (Len <= 0 || Len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    bool Return = gDataBase.ExecFormat("EXEC WZ_PeriodItemUpdate %d, '%s', %d, %d, %d", 1, CharacterName, 2, 3, 4);

    if ((Return == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.btResult = 1;

        pResult.iUserIndex = aRecv->iUserIndex;
        pResult.iItemCode = aRecv->iItemCode;
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::PeriodItemList(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEM_LIST * aRecv)
{
    PMSG_ANS_PERIODITEM_LIST pResult = { 0 };
    gFunc.PHeadSubSetB((LPBYTE)&pResult, 0xD0, 0x06, sizeof(pResult));

    char CharacterName[11] = { 0 };

    memcpy(CharacterName, aRecv->chCharacterName, 10);

    int Len = strlen(CharacterName);

    if (Len <= 0 || Len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    BYTE Repeat = 0;

    bool Return = gDataBase.ExecFormat("EXEC WZ_PeriodItemSelect %d, '%s'", aRecv->iUserGuid, CharacterName);

    if (Return == true && gDataBase.Fetch() != SQL_NO_DATA)
    {
        char ExpireDateDB[21] = { 0 };
        do
        {
            gDataBase.GetStr("ExpireDate", ExpireDateDB);

            pResult.m_ListItem[Repeat].iItemCode = gDataBase.GetInt("ItemCode");
            pResult.m_ListItem[Repeat].btEffectType1 = (BYTE)gDataBase.GetInt("EffectType1");
            pResult.m_ListItem[Repeat].btEffectType2 = (BYTE)gDataBase.GetInt("EffectType2");
            pResult.m_ListItem[Repeat].btOptionType = (BYTE)gDataBase.GetInt("OptionType");
            pResult.m_ListItem[Repeat].iItemPeriodLeftTime = (UINT)Service->GetPeriodLeftTime(ExpireDateDB);//gDataBase.GetInt("LeftTime");
            pResult.m_ListItem[Repeat].iItemPeriodUsedTime = gDataBase.GetInt("UsedTime");
            pResult.m_ListItem[Repeat].btInUse = (BYTE)gDataBase.GetInt("UsedInfo");

            Repeat++;
        } while (Repeat < 10 && gDataBase.Fetch() != SQL_NO_DATA);
    }

    pResult.btResult = 1;
    pResult.iUserGuid = aRecv->iUserGuid;
    pResult.iUserIndex = aRecv->iUserIndex;
    pResult.btCountItems = Repeat;

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}


void DataServer_Protocol::SummonerStateUpdate(DataServer_Manager * Service, int aIndex, PMSG_REQ_SUMMONER_CREATE * aRecv)
{
    PMSG_ANS_SUMMONER_CREATE pResult = { 0 };
    pResult.h.Set(0xA2, sizeof(pResult));

    char AccountID[11] = { 0 };
    memcpy(AccountID, aRecv->szAccountID, 10);

    int Len = strlen(AccountID);

    if (Len <= 0 || Len > 10)
    {
        LogAddC(eError, "[%s] Error on lenght", __FUNCTION__);
        return;
    }

    bool Return = gDataBase.ExecFormat("UPDATE AccountCharacter SET Summoner = 1 WHERE Id = '%s'", AccountID);

    if ((Return == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.btResult = 1;
    }

    pResult.aIndex = aRecv->aIndex;
    memcpy(pResult.szAccountID, AccountID, 10);

    gDataBase.Clear();
}


void DataServer_Protocol::GDCharacterClose(DataServer_Manager * Service, int aIndex, SDHP_USERCLOSE * aRecv)
{
    char CharName[11] = { 0 };
    char GuildName[9] = { 0 };

    memcpy(CharName, aRecv->CharName, 10);
    memcpy(GuildName, aRecv->GuildName, 8);

    for (int n = 0; n < 20; n++)
    {
        if (Service->isConnected(n) == true)
        {
            Service->DataSend(n, (unsigned char*)aRecv, aRecv->h.Size);
        }
    }
}

void DataServer_Protocol::DS_GDReqCastleNpcInfo(DataServer_Manager * Service, int aIndex, BYTE * aRecv)
{
    if ( aRecv == NULL)
    {
        return;
    }

    CSP_REQ_NPCDATA* lpMsg = (CSP_REQ_NPCDATA*)aRecv;

    char cBUFFER[5876];

    CSP_ANS_NPCDATA* lpMsgSend = (CSP_ANS_NPCDATA*)cBUFFER;
    CSP_NPCDATA* lpMsgSendBody = (CSP_NPCDATA *)&cBUFFER[20];

    lpMsgSend->wMapSvrNum = lpMsg->wMapSvrNum;

    int iDataCount = 200;

    lpMsgSend->iCount = 0;

    int iRES = DSDB_QueryCastleNpcInfo(lpMsg->wMapSvrNum, lpMsgSendBody, &iDataCount);

    if (iRES != 0)
    {
        lpMsgSend->iResult = 0;
        lpMsgSend->h.Set(0x82, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
    }
    else
    {
        lpMsgSend->iResult = 1;
        lpMsgSend->iCount = iDataCount;
        lpMsgSend->h.Set(0x82, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
        Service->DataSend(aIndex, (unsigned char*)lpMsgSend, (sizeof(CSP_NPCDATA) * lpMsgSend->iCount) + sizeof(CSP_ANS_NPCDATA));
    }
}


void DataServer_Protocol::GDReqCrywolfInfoSave(DataServer_Manager * Service, int aIndex, CWP_REQ_CRYWOLFINFOSAVE * aRecv)
{
    // [TODO] Maybe need write MapSrvGroup a not MapSrvNum

    CWP_ANS_CRYWOLFINFOSAVE pResult = { 0 };
    pResult.h.Set(0xB2, sizeof(pResult));

    bool Return = gDataBase.ExecFormat("EXEC WZ_CW_InfoSave %d, %d, %d", aRecv->wMapSvrNum, aRecv->iCrywolfState, aRecv->iOccupationState);

    if ((Return == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        pResult.btResult = 1;
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
}

void DataServer_Protocol::GDReqPeriodItemExInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_INSERT * aRecv)
{
    PMSG_ANS_PERIODITEMEX_INSERT pMsg = { 0 };
    pMsg.head.set(0xD1, 0x01, sizeof(PMSG_ANS_PERIODITEMEX_INSERT));

    if (gDataBase.ExecFormat("EXEC WZ_PeriodItemInsertEx %d, '%s', %d, %d, %d, %d, %d, %u, %d, %d, %d", aRecv->dwUserGuid, aRecv->chCharacterName, aRecv->btItemType, aRecv->wItemCode, aRecv->btOptionType, aRecv->btEffectType1, aRecv->btEffectType2, aRecv->dwSerial, aRecv->dwDuration, aRecv->lBuyDate, aRecv->lExpireDate) == true && gDataBase.Fetch() != SQL_NO_DATA)
        pMsg.btResultCode = gDataBase.GetInt(1);
    else
        pMsg.btResultCode = -1;
    gDataBase.Clear();

    pMsg.dwUserGuid = aRecv->dwUserGuid;
    pMsg.wUserIndex = aRecv->wUserIndex;
    pMsg.btItemtype = aRecv->btItemType;
    pMsg.wItemCode = aRecv->wItemCode;
    pMsg.btOptionType = aRecv->btOptionType;
    pMsg.btEffectType1 = aRecv->btEffectType1;
    pMsg.btEffectType2 = aRecv->btEffectType2;
    pMsg.dwSerial = aRecv->dwSerial;
    pMsg.dwDuration = aRecv->dwDuration;
    pMsg.lBuyDate = aRecv->lBuyDate;
    pMsg.lExpireDate = aRecv->lExpireDate;

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(PMSG_ANS_PERIODITEMEX_INSERT));
}

void DataServer_Protocol::GDReqPeriodItemExDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_DELETE * aRecv)
{
    PMSG_ANS_PERIODITEMEX_DELETE pMsg = { 0 };
    pMsg.head.set(0xD1, 0x02, sizeof(PMSG_ANS_PERIODITEMEX_DELETE));

    /*
    missing sql syntax check
    */

    if (gDataBase.ExecFormat("EXEC WZ_PeriodItemDeleteEx %d, '%s', %d, %d, %u", aRecv->dwUserGuid, aRecv->chCharacterName, aRecv->wItemCode, aRecv->btItemType, aRecv->dwSerial) == false)
        pMsg.btResultCode = 2;

    else if (gDataBase.Fetch() == SQL_NO_DATA)
        pMsg.btResultCode = 1;

    else
        pMsg.btResultCode = 0;

    gDataBase.Clear();

    pMsg.dwUserGuid = aRecv->dwUserGuid;
    pMsg.wUserIndex = aRecv->wUserIndex;

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(PMSG_ANS_PERIODITEMEX_DELETE));
}


void DataServer_Protocol::GDReqPeriodItemExSelect(DataServer_Manager * Service, int aIndex, PMSG_REQ_PERIODITEMEX_SELECT * aRecv)
{
    PMSG_ANS_PERIODITEMEX_LIST_COUNT pListCount = { 0 };
    PMSG_ANS_PERIODITEMEX_LIST pList = { 0 };

    PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST pExpiredList = { 0 };
    PERIOD_EXPIRED_ITEMLIST ExpiredItemList = { 0 };

    pList.head.set(0xD1, 0x05, sizeof(PMSG_ANS_PERIODITEMEX_LIST));
    pListCount.head.set(0xD1, 0x04, sizeof(PMSG_ANS_PERIODITEMEX_LIST_COUNT));
    pExpiredList.head.set(0xD1, 0x03, sizeof(PMSG_ANS_PERIODITEMEX_EXPIRED_ITEMLIST));

    int iReturnCode = 0;

    if (gDataBase.ExecFormat("EXEC WZ_PeriodItemExpiredItemSelectEx %d, '%s'", aRecv->dwUserGuid, aRecv->chCharacterName) == true && gDataBase.Fetch() == SQL_SUCCESS)
    {
        short sqlReturn = gDataBase.Fetch();
        int iItemCount = 0;
        while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
        {
            ExpiredItemList.ExpiredItem[iItemCount].wItemCode = gDataBase.GetInt("ItemCode");
            ExpiredItemList.ExpiredItem[iItemCount].dwSerial = (DWORD)gDataBase.GetInt64("SerialCode");
            iItemCount++;

            sqlReturn = gDataBase.Fetch();

            if (iItemCount >= 30)
            {
                break;
            }

            gDataBase.Clear();

            ExpiredItemList.btItemCount = iItemCount;

            iReturnCode = iItemCount;
        }
    }
    else
    {
        gDataBase.Clear();
        iReturnCode = -3;
    }

    if (iReturnCode > 0)
    {
        pExpiredList.wUserIndex = aRecv->wUserIndex;
        pExpiredList.btExpiredItemCount = iReturnCode;

        for (int i = 0; i < pExpiredList.btExpiredItemCount; i++)
        {
            pExpiredList.wItemCode[i] = ExpiredItemList.ExpiredItem[i].wItemCode;
            pExpiredList.dwSerial[i] = ExpiredItemList.ExpiredItem[i].dwSerial;
        }

        Service->DataSend(aIndex, (unsigned char*)&pExpiredList, pExpiredList.head.Size);
    }

    PERIOD_ITEMLIST ItemData = { 0 };
    ItemData.dwUserGuid = aRecv->dwUserGuid;
    memcpy(ItemData.chCharacterName, aRecv->chCharacterName, 11);

    if (gDataBase.ExecFormat("EXEC WZ_PeriodItemSelectEx %d, '%s'", ItemData.dwUserGuid, ItemData.chCharacterName) == true)
    {
        int ItemCount = 0;
        short i = gDataBase.Fetch();
        while (i != SQL_NO_DATA && i != SQL_NULL_DATA)
        {
            iReturnCode = gDataBase.GetInt(1);

            if (iReturnCode < 0)
            {
                break;
            }

            ItemData.ItemData[ItemCount].btUsedInfo = 1;
            ItemData.ItemData[ItemCount].wItemCode = gDataBase.GetInt("ItemCode");
            ItemData.ItemData[ItemCount].btItemType = gDataBase.GetInt("ItemType");
            ItemData.ItemData[ItemCount].btEffectType1 = gDataBase.GetInt("EffectType1");
            ItemData.ItemData[ItemCount].btEffectType2 = gDataBase.GetInt("EffectType2");
            ItemData.ItemData[ItemCount].btEffectCategory = gDataBase.GetInt("OptionType");
            ItemData.ItemData[ItemCount].dwSerial = (DWORD)gDataBase.GetInt64("SerialCode");
            ItemData.ItemData[ItemCount].lItemBuyDate = gDataBase.GetInt("BuyDateConvert");
            ItemData.ItemData[ItemCount].lItemExpireDate = gDataBase.GetInt("ExpireDateConvert");
            ItemCount++;

            if (ItemCount >= 100)
            {
                break;
            }

            i = gDataBase.Fetch();
        }

        gDataBase.Clear();

        ItemData.btItemCount = ItemCount;
        pListCount.btResult = iReturnCode;
    }
    else
    {
        gDataBase.Clear();
        pListCount.btResult = -3;
    }

    pListCount.btListCount = ItemData.btItemCount;
    pListCount.dwUserGuid = aRecv->dwUserGuid;
    pListCount.wUserIndex = aRecv->wUserIndex;

    for (int Count = 0; Count < pListCount.btListCount; Count++)
    {
        pList.dwUserGuid = aRecv->dwUserGuid;
        pList.wUserIndex = aRecv->wUserIndex;
        pList.wItemCode = ItemData.ItemData[Count].wItemCode;
        pList.btEffectCategory = ItemData.ItemData[Count].btEffectCategory;
        pList.btEffectType1 = ItemData.ItemData[Count].btEffectType1;
        pList.btEffectType2 = ItemData.ItemData[Count].btEffectType2;
        pList.btItemType = ItemData.ItemData[Count].btItemType;
        pList.btUsedInfo = ItemData.ItemData[Count].btUsedInfo;
        pList.dwSerial = ItemData.ItemData[Count].dwSerial;
        pList.lItemBuyDate = ItemData.ItemData[Count].lItemBuyDate;
        pList.lItemExpireDate = ItemData.ItemData[Count].lItemExpireDate;

        Service->DataSend(aIndex, (unsigned char*)&pList, pList.head.Size);
    }
    Service->DataSend(aIndex, (unsigned char*)&pListCount, pListCount.head.Size);
}


void DataServer_Protocol::GDReqLuckyItemSelect(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_SELECT * aRecv)
{
    char sendbuf[2048] = { 0 };

    PMSG_LUCKYITME_DB_INFO LuckyItemInfo[45] = { 0 };

    int iResult = -3;
    if (gDataBase.ExecFormat("WZ_LuckyItemSelect '%s'", aRecv->chCharacterName) == true)
    {
        int iItemCount = 0;
        short sqlReturn = gDataBase.Fetch();

        while (sqlReturn != SQL_NO_DATA && sqlReturn != SQL_NULL_DATA)
        {
            LuckyItemInfo[iItemCount].wItemCode = gDataBase.GetInt("ItemCode");
            LuckyItemInfo[iItemCount].dwSerial = (DWORD)gDataBase.GetInt64("ItemSerial");
            LuckyItemInfo[iItemCount].wDurabilitySmall = (WORD)gDataBase.GetInt64("DurabilitySmall");
            iItemCount++;

            sqlReturn = gDataBase.Fetch();

            if (iItemCount >= 45)
            {
                break;
            }
        }

        gDataBase.Clear();

        iResult = iItemCount;
    }
    else
    {
        gDataBase.Clear();
        iResult = -3;
    }


    if (iResult > 0)
    {
        int lOfs = 8;

        PMSG_ANS_LUCKYITEM_SELECT pMsg;
        pMsg.btItemCnt = iResult;
        pMsg.wUserIndex = aRecv->wUserIndex;

        memcpy(&sendbuf[lOfs], LuckyItemInfo, pMsg.btItemCnt * 12);

        lOfs += (pMsg.btItemCnt * 12);

        pMsg.head.Set(0xD4, lOfs);
        memcpy(sendbuf, &pMsg, 8);
        Service->DataSend(aIndex, (unsigned char*)&sendbuf, lOfs);
    }
}

void DataServer_Protocol::GDReqLuckyItemInsert(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_INSERT * aRecv)
{
    if (gDataBase.ExecFormat("EXEC WZ_LuckyItemInsert %d, '%s', %d, %u, %d", aRecv->dwUserGuid, aRecv->szCharName, aRecv->LuckyItemDBInfo.wItemCode, aRecv->LuckyItemDBInfo.dwSerial, aRecv->LuckyItemDBInfo.wDurabilitySmall) == true && gDataBase.Fetch() != SQL_NULL_DATA)
    {
        gDataBase.GetInt(1);
    }
    gDataBase.Clear();
}


void DataServer_Protocol::GDReqLuckyItemDelete(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_DELETE * aRecv)
{
    if (gDataBase.ExecFormat("WZ_LuckyItemDelete '%s', %d, %u", aRecv->szCharName, aRecv->wItemCode, aRecv->dwSerial) == true && gDataBase.Fetch() != SQL_NO_DATA)
    {
        gDataBase.GetInt(1);
    }
    gDataBase.Clear();
}

void DataServer_Protocol::GDReqLuckyItemInsert2nd(DataServer_Manager * Service, int aIndex, PMSG_REQ_LUCKYITEM_INSERT_2ND * aRecv)
{
    int iItemCnt = aRecv->btItemCnt;

    if (iItemCnt <= 0)
        return;

    for (int i = 0; i < iItemCnt; i++)
    {
        if (gDataBase.ExecFormat("EXEC WZ_LuckyItemInsert %d, '%s', %d, %u, %d", aRecv->dwUserGuid, aRecv->szCharName, aRecv->LuckyItemDBInfo[i].wItemCode, aRecv->LuckyItemDBInfo[i].dwSerial, aRecv->LuckyItemDBInfo[i].wDurabilitySmall) == true && gDataBase.Fetch() != SQL_NULL_DATA)
        {
            gDataBase.GetInt(1);
        }
        gDataBase.Clear();
    }
}

void DataServer_Protocol::GDReqUserID(DataServer_Manager * Service, int aIndex, PMSG_REQ_USERID * aRecv)
{
    PMSG_ANS_USERID pMsg = { 0 };

    char chBuffer[11] = { 0 };
    memcpy(chBuffer, aRecv->chUserName, 10);

    pMsg.head.set(0xD3, 0x01, sizeof(pMsg));
    pMsg.dwKey = aRecv->dwKey;
    pMsg.dwUserGUID = aRecv->dwUserGUID;

    if (gDataBase.ExecFormat("SELECT AccountID FROM Character WHERE Name = '%s'", aRecv->chUserName) == true)
    {
        if (gDataBase.Fetch() == SQL_NO_DATA)
        {
            gDataBase.Clear();
            pMsg.btResult = 2;
        }
        else
        {
            gDataBase.GetStr(1, chBuffer);
            memcpy(pMsg.chUserID, chBuffer, 11);
            gDataBase.Clear();
            pMsg.btResult = 0;
        }
    }
    else
    {
        pMsg.btResult = 1;
    }

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(PMSG_ANS_USERID));
}


void DataServer_Protocol::GetGameServerInfo(DataServer_Manager * Service, int aIndex, SDHP_GAMESERVERINFO * aRecv)
{
    gDataBase.ExecFormat("UPDATE GameServerInfo SET ItemCount = %d WHERE Number = 0", aRecv->ItemCount);
    gDataBase.Clear();
}


void DataServer_Protocol::GDLoadMedalInfo(DataServer_Manager * Service, int aIndex, SDHP_LOAD_MEDALINFO * aRecv)
{

    SDHP_LOAD_MEDALINFO_RESULT pResult = { 0 };
    pResult.h.Set(0x2D, sizeof(pResult));

    pResult.wIndex = aRecv->wIndex;
    pResult.dwItemSerial = aRecv->dwItemSerial;
    pResult.wItemIndex = aRecv->wItemIndex;

    bool Return = gDataBase.ExecFormat("SELECT * FROM T_PropertyItemInfo WHERE ItemSerial = %u", aRecv->dwItemSerial);

    if ((Return == true) && (gDataBase.Fetch() != SQL_NO_DATA))
    {
        char AccountID[11] = { 0 };
        gDataBase.GetStr("Name1", AccountID);
        memcpy(pResult.szName, AccountID, 10);
        gDataBase.GetStr("Name2", AccountID);
        memcpy(pResult.szName_T, AccountID, 10);
        pResult.wLevel = (WORD)gDataBase.GetInt("Level1");
        pResult.btClass = (BYTE)gDataBase.GetInt("Class1");
        pResult.wLevel_T = (WORD)gDataBase.GetInt("Level2");
        pResult.btClass_T = (BYTE)gDataBase.GetInt("Class2");
        pResult.wRemainTime = (WORD)gDataBase.GetInt("RemainTime");

        Service->DataSend(aIndex, (unsigned char*)&pResult, pResult.h.Size);
    }
    else
    {
        LogAddC(eError, "[ERROR-L2] GDLoadMedalInfo() Serial: %u, Index: %d", aRecv->dwItemSerial, aRecv->wIndex);
    }

    gDataBase.Clear();
}


void DataServer_Protocol::SetGameMasterEvent(DataServer_Manager * Service, int aIndex, SDHP_SETGMEVENT * aRecv)
{
    gDataBase.ExecFormat("UPDATE Character SET CtlCode = 32 WHERE Name = '%s'", aRecv->CharName);

    gDataBase.Clear();
}

void DataServer_Protocol::GDDeleteTempUserInfo(DataServer_Manager * Service, int aIndex, SDHP_DELETE_TEMPUSERINFO *lpMsg)
{
    SDHP_DELETE_TEMPUSERINFO_RESULT pMsg = { 0 };

    pMsg.h.c = 0xC1;
    pMsg.h.headcode = 0xCE;
    pMsg.h.Size = sizeof(SDHP_DELETE_TEMPUSERINFO_RESULT);

    memcpy(pMsg.CharName, lpMsg->CharName, 10);

    for (int n = 0; n < 20; n++)
    {
        Service->DataSend(n, (unsigned char*)&pMsg, pMsg.h.Size);
    }
}

void DataServer_Protocol::GDSetExtendedInvenCount(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXTENDEDINVEN_COUNT * aRecv)
{
    SDHP_ANS_SET_EXTENDEDINVEN_COUNT pMsg = { 0 };
    pMsg.h.Set(0xD5, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));

    pMsg.Number = aRecv->Number;
    pMsg.Result = 1;
    pMsg.ExtendedInvenCount = 0;
    pMsg.EventIndex = aRecv->EventIndex;
    pMsg.ItemPos = aRecv->ItemPos;
    pMsg.BuyAtInGameShop = aRecv->BuyAtInGameShop;
    pMsg.IsReplace = aRecv->IsReplace;

    if ((aRecv->ItemPos > 203 || aRecv->ItemPos < 0) && aRecv->BuyAtInGameShop == 0 && aRecv->IsReplace == 0)
    {
        pMsg.Result = 0;

        if (gDataBase.ExecFormat("SELECT ExtendedInvenCount FROM Character WHERE Name = '%s'", aRecv->szCharName) == true)
        {
            gDataBase.Fetch();
            pMsg.ExtendedInvenCount = gDataBase.GetInt(1);

            if (pMsg.ExtendedInvenCount > 2)
            {
                pMsg.ExtendedInvenCount = 2;
            }
        }

        gDataBase.Clear();

        Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
        return;
    }

    if (aRecv->IsReplace == 1)
    {
        if (gDataBase.ExecFormat("SELECT ExtendedInvenCount FROM Character WHERE Name = '%s'", aRecv->szCharName) == true && gDataBase.Fetch() != SQL_NO_DATA)
        {
            gDataBase.Clear();
            if (aRecv->ExtendedInvenCount > 2)
            {
                pMsg.Result = 0;
            }
            else
            {
                if (gDataBase.ExecFormat("UPDATE Character SET ExtendedInvenCount = %d WHERE Name = '%s'", aRecv->ExtendedInvenCount, aRecv->szCharName) == true)
                {
                    gDataBase.Clear();
                    pMsg.Result = 1;
                }
                else
                {
                    pMsg.Result = 0;
                }
            }
        }
        else
        {
            pMsg.Result = 0;
        }
    }
    else
    {
        if (gDataBase.ExecFormat("SELECT ExtendedInvenCount FROM Character WHERE Name = '%s'", aRecv->szCharName) == true && gDataBase.Fetch() != SQL_NO_DATA)
        {
            BYTE btSlotCount = gDataBase.GetInt(1);

            gDataBase.Clear();

            if (btSlotCount + aRecv->ExtendedInvenCount > 2)
            {
                pMsg.Result = 0;
            }
            else
            {
                if (gDataBase.ExecFormat("UPDATE Character SET ExtendedInvenCount = %d WHERE Name = '%s'", btSlotCount + aRecv->ExtendedInvenCount, aRecv->szCharName) == true)
                {
                    pMsg.Result = 1;
                }
                else
                {
                    pMsg.Result = 0;
                }
            }
        }
        else
        {
            gDataBase.Clear();
            pMsg.Result = 0;
        }
    }

    if (gDataBase.ExecFormat("SELECT ExtendedInvenCount FROM Character WHERE Name = '%s'", aRecv->szCharName) == true)
    {
        gDataBase.Fetch();
        pMsg.ExtendedInvenCount = gDataBase.GetInt(1);
        if (pMsg.ExtendedInvenCount > 2)
        {
            pMsg.ExtendedInvenCount = 2;
        }
    }
    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDINVEN_COUNT));
}

void DataServer_Protocol::GDSetExtendedWarehouseCount(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXTENDEDWAREHOUSE_COUNT * aRecv)
{
    SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT pMsg = { 0 };
    pMsg.h.Set(0xD6, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));

    pMsg.Number = aRecv->Number;
    pMsg.Result = 1;
    pMsg.ExtendedWarehouseCount = 0;
    pMsg.EventIndex = aRecv->EventIndex;
    pMsg.ItemPos = aRecv->ItemPos;
    pMsg.BuyAtInGameShop = aRecv->BuyAtInGameShop;
    pMsg.IsReplace = aRecv->IsReplace;

    if ((aRecv->ItemPos > 203 || aRecv->ItemPos < 0) && aRecv->BuyAtInGameShop == 0 && aRecv->IsReplace == 0)
    {
        pMsg.Result = 0;

        if (gDataBase.ExecFormat("SELECT ExtendedWarehouseCount FROM AccountCharacter WHERE Id = '%s'", aRecv->AccountId) == TRUE && gDataBase.Fetch() != SQL_NO_DATA)
        {
            pMsg.ExtendedWarehouseCount = gDataBase.GetInt(1);

            if (pMsg.ExtendedWarehouseCount > 1)
            {
                pMsg.ExtendedWarehouseCount = 1;
            }
        }

        gDataBase.Clear();

        Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));
        return;
    }

    if (aRecv->IsReplace == 1)
    {
        if (gDataBase.ExecFormat("SELECT ExtendedWarehouseCount FROM AccountCharacter WHERE Id = '%s'", aRecv->AccountId) == TRUE && gDataBase.Fetch() != SQL_NO_DATA)
        {
            gDataBase.Clear();
            if (aRecv->ExtendedWarehouseCount > 1)
            {
                pMsg.Result = FALSE;
            }
            else
            {
                if (gDataBase.ExecFormat("UPDATE AccountCharacter SET ExtendedWarehouseCount = %d WHERE Id = '%s'", aRecv->ExtendedWarehouseCount, aRecv->AccountId) == TRUE)
                {
                    pMsg.Result = TRUE;
                }
                else
                {
                    pMsg.Result = FALSE;
                }
            }
        }
        else
        {
            pMsg.Result = FALSE;
        }
    }
    else
    {
        if (gDataBase.ExecFormat("SELECT ExtendedWarehouseCount FROM AccountCharacter WHERE Id = '%s'", aRecv->AccountId) == TRUE && gDataBase.Fetch() != SQL_NO_DATA)
        {
            BYTE btSlotCount = gDataBase.GetInt(1);
            gDataBase.Clear();

            if (btSlotCount + aRecv->ExtendedWarehouseCount > 1)
            {
                pMsg.Result = FALSE;
            }
            else
            {
                if (gDataBase.ExecFormat("UPDATE AccountCharacter SET ExtendedWarehouseCount = %d WHERE Id = '%s'", btSlotCount + aRecv->ExtendedWarehouseCount, aRecv->AccountId) == TRUE)
                {
                    pMsg.Result = TRUE;
                }
                else
                {
                    pMsg.Result = FALSE;
                }
            }
        }
        else
        {
            pMsg.Result = FALSE;
        }
    }

    pMsg.Result = 0;

    if (gDataBase.ExecFormat("SELECT ExtendedWarehouseCount FROM AccountCharacter WHERE Id = '%s'", aRecv->AccountId) != FALSE && gDataBase.Fetch() != SQL_NO_DATA)
    {
        pMsg.ExtendedWarehouseCount = gDataBase.GetInt(1);

        if (pMsg.ExtendedWarehouseCount > 1)
        {
            pMsg.ExtendedWarehouseCount = 1;
        }
    }

    gDataBase.Clear();

    Service->DataSend(aIndex, (unsigned char*)&pMsg, sizeof(SDHP_ANS_SET_EXTENDEDWAREHOUSE_COUNT));
}

void DataServer_Protocol::GDReqQuestExpInfoSave(DataServer_Manager * Service, int aIndex, _PMSG_QUESTEXP_INFO * aRecv)
{
}

void DataServer_Protocol::GDReqQuestExpInfoLoad(DataServer_Manager * Service, int aIndex, PMSG_REQ_QUESTEXP_INFO * aRecv)
{

}

void DataServer_Protocol::GDSetExGameServerCode(DataServer_Manager * Service, int aIndex, SDHP_REQ_SET_EXGAMESERVERCODE * aRecv)
{
    if (gDataBase.ExecFormat("SELECT ExtendedInvenCount FROM Character WHERE Name = '%s'", aRecv->szCharName) == TRUE && gDataBase.Fetch() != SQL_NO_DATA)
    {
        gDataBase.Clear();
        gDataBase.ExecFormat("UPDATE Character SET ExGameServerCode = %d WHERE Name = '%s'", aRecv->sExGameServerCode, aRecv->szCharName);
    }
}

void DataServer_Protocol::GDNpcLeoTheHelperRecv(DataServer_Manager * Service, SDHP_NPC_LEO_THE_HELPER_RECV* lpMsg, int index) // OK
{
	SDHP_NPC_LEO_THE_HELPER_SEND pMsg;

	gFunc.PHeadSubSetB((LPBYTE)&pMsg, 0x0E, 0x00, sizeof(SDHP_NPC_LEO_THE_HELPER_SEND));
	pMsg.index = lpMsg->index;
	memcpy(pMsg.account, lpMsg->account, sizeof(pMsg.account));
	memcpy(pMsg.name, lpMsg->name, sizeof(pMsg.name));
	if (gDataBase.ExecFormat("SELECT Status FROM LeoTheHelper WHERE Name='%s'", lpMsg->name) == 0 || (gDataBase.Fetch() == SQL_NO_DATA))
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("INSERT INTO LeoTheHelper (Name,Status) VALUES ('%s',0)", lpMsg->name);
		gDataBase.Clear();

		pMsg.status = 0;
	}
	else
	{
		pMsg.status = (BYTE)gDataBase.GetInt("Status");

		gDataBase.Clear();
	}
	Service->DataSend(index, (BYTE*)&pMsg, pMsg.header.Size);
}

void DataServer_Protocol::GDNpcLeoTheHelperSaveRecv(DataServer_Manager * Service, SDHP_NPC_LEO_THE_HELPER_SAVE_RECV* lpMsg) // OK
{
	if (gDataBase.ExecFormat("SELECT Name FROM LeoTheHelper WHERE Name='%s'", lpMsg->name) == 0 || gDataBase.Fetch() == SQL_NO_DATA)
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("INSERT INTO LeoTheHelper (Name,Status) VALUES ('%s',%d)", lpMsg->name, lpMsg->status);
		gDataBase.Clear();
	}
	else
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("UPDATE LeoTheHelper SET Status=%d WHERE Name='%s'", lpMsg->status, lpMsg->name);
		gDataBase.Clear();
	}
}

void DataServer_Protocol::GDNpcLukeTheHelperRecv(DataServer_Manager * Service, SDHP_NPC_LUKE_THE_HELPER_RECV* lpMsg, int index) // OK
{

	SDHP_NPC_LUKE_THE_HELPER_SEND pMsg;

	gFunc.PHeadSubSetB((LPBYTE)&pMsg, 0x0E, 0x01, sizeof(SDHP_NPC_LUKE_THE_HELPER_SEND));
	pMsg.index = lpMsg->index;
	memcpy(pMsg.account, lpMsg->account, sizeof(pMsg.account));
	memcpy(pMsg.name, lpMsg->name, sizeof(pMsg.name));
	if (gDataBase.ExecFormat("SELECT Status FROM LukeTheHelper WHERE Name='%s'", lpMsg->name) == 0 || (gDataBase.Fetch() == SQL_NO_DATA))
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("INSERT INTO LukeTheHelper (Name,Status) VALUES ('%s',0)", lpMsg->name);
		gDataBase.Clear();
		pMsg.status = 0;
	}
	else
	{
		pMsg.status = (BYTE)gDataBase.GetInt("Status");
		gDataBase.Clear();
	}
	Service->DataSend(index, (BYTE*)&pMsg, pMsg.header.Size);
}

void DataServer_Protocol::GDNpcLukeTheHelperSaveRecv(DataServer_Manager * Service, SDHP_NPC_LUKE_THE_HELPER_SAVE_RECV* lpMsg) // OK
{
	if (gDataBase.ExecFormat("SELECT Name FROM LukeTheHelper WHERE Name='%s'", lpMsg->name) == 0 || gDataBase.Fetch() == SQL_NO_DATA)
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("INSERT INTO LukeTheHelper (Name,Status) VALUES ('%s',%d)", lpMsg->name, lpMsg->status);
		gDataBase.Clear();
	}
	else
	{
		gDataBase.Clear();
		gDataBase.ExecFormat("UPDATE LukeTheHelper SET Status=%d WHERE Name='%s'", lpMsg->status, lpMsg->name);
		gDataBase.Clear();
	}
}