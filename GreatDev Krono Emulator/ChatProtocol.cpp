#include "StdAfx.h"
#include "ChatProtocol.h"

cChat Chat;

cChat::cChat(){ this->LoadConfigs();}
cChat::~cChat(){}

#define GOLD_MESSAGE	0
#define DEFAULT_MESSAGE	1

#define KRONO_COMMANDS	"..\\Data\\Commands.ini"
enum ePostColor
{
	POST_COLOR_DEF = 1,
	POST_COLOR_GREEN,
	POST_COLOR_BLUE
	
};

enum eChatTypes
{
	CHAT_DEFAULT,
	CHAT_POST,
	CHAT_GUILD,
	CHAT_PARTY,
	CHAT_GUILDMASTER
};

enum eChatCommand
{
	CMD_DEFAULT = CHAT_GUILDMASTER + 1,
	CMD_TEST,
	//Cmd For GM
	CMD_DROP,

	CMD_GMOVE,
	CMD_GUILDMOVE,
	CMD_TRACE,
	
	CMD_BANCHAT,
	CMD_UNBANCHAT,
	CMD_BANPOST,
	CMD_UNBANPOST,
	CMD_BANCHAR,
	CMD_UNBANCHAR,
	CMD_BANACC,
	CMD_UNBANACC,

	CMD_DISCONNECT,
	CMD_GUILD_DISCON,

	CMD_MONITORING,
	CMD_CONNECT_STATE,

	CMD_SETCHAR,
	CMD_SETPK,
	CMD_SETZEN,

	CMD_RELOAD,

	CMD_GUILDWAR_START,
	CMD_GUILDWAR_STOP,
	CMD_GUILDWAR_END,
	//Cmd for Player
	CMD_MOVE,
	CMD_GUILD_WAR,
	CMD_BATTLE_SOCCER,
	CMD_REQUEST,

	CMD_ONLINE,
	CMD_STATUS,
	CMD_LEVEL,
	CMD_TIME,
	CMD_SKIN,
	CMD_PKCLEAR,

	CMD_ADDSTR,
	CMD_ADDAGI,
	CMD_ADDVIT,
	CMD_ADDENE,
	CMD_ADDCMD,

	//Castle Siege Cmd
	CMD_CS_CHANGE_OWNER,
	CMD_CS_SET_REG_SIEGE,
	CMD_CS_SET_REG_MARK,
	CMD_CS_SET_NOTIFY,
	CMD_CS_SET_START,
	CMD_CS_SET_END,
	CMD_CS_CUR_OWNER,
	CMD_CS_CUR_STATE,
	CMD_CS_CHANGE_SIDE,
	//CryWold Cmd
	CMD_CRYWOLF_1,
	CMD_CRYWOLF_2,
	CMD_CRYWOLF_3,
	CMD_CRYWOLF_4
};

void cChat::LoadConfigs()
{
	Config.Add.AddPointEnabled = GetPrivateProfileInt("AddCommand","AddPointEnabled",1,KRONO_COMMANDS);
	Config.Add.AddPointLevelReq = GetPrivateProfileInt("AddCommand","AddPointLevelReq",10,KRONO_COMMANDS);
	Config.Add.AddPricePcPoint = GetPrivateProfileInt("AddCommand","AddPricePcPoint",0,KRONO_COMMANDS);
	Config.Add.AddPriceWCoin = GetPrivateProfileInt("AddCommand","AddPriceWCoint",0,KRONO_COMMANDS);
	Config.Add.AddPriceZen = GetPrivateProfileInt("AddCommand","AddPriceZen",100000,KRONO_COMMANDS);
	Config.Add.Enable65kStats = GetPrivateProfileInt("AddCommand","Enable65kStats",0,KRONO_COMMANDS);
	Config.Add.MaxAddedStats = GetPrivateProfileInt("AddCommand","MaxAddedStats",100,KRONO_COMMANDS);

	Config.Post.PostEnabled = GetPrivateProfileInt("Post","PostEnabled",1,KRONO_COMMANDS);
	Config.Post.PostLevelReq = GetPrivateProfileInt("Post","PostLevelReq",100,KRONO_COMMANDS);
	Config.Post.PostPriceZen = GetPrivateProfileInt("Post","PostPriceZen",100000,KRONO_COMMANDS);
	Config.Post.PostPricePcPoint = GetPrivateProfileInt("Post","PostPricePcPoint",0,KRONO_COMMANDS);
	Config.Post.PostPriceWCoin = GetPrivateProfileInt("Post","PostPriceWCoin",0,KRONO_COMMANDS);
	Config.Post.PostColor = GetPrivateProfileInt("Post","PostColor",1,KRONO_COMMANDS);			
	Config.Post.PostDelay = GetPrivateProfileInt("Post","PostDelay",60,KRONO_COMMANDS);

	Config.PkClear.PkClearEnabled = GetPrivateProfileInt("PkClear","PkClearEnabled",1,KRONO_COMMANDS);
	Config.PkClear.PkClearOnlyForGm = GetPrivateProfileInt("PkClear","PkClearOnlyForGm",0,KRONO_COMMANDS);
	Config.PkClear.PkClearLevelReq = GetPrivateProfileInt("PkClear","PkClearLevelReq",100,KRONO_COMMANDS);
	Config.PkClear.PKClearType = GetPrivateProfileInt("PkClear","PKClearType",2,KRONO_COMMANDS);
	Config.PkClear.PkClearPriceZen = GetPrivateProfileInt("PkClear","PkClearPriceZen",100000,KRONO_COMMANDS);
	Config.PkClear.PkClearPriceZenForAll = GetPrivateProfileInt("PkClear","PkClearPriceZenForAll",1000000,KRONO_COMMANDS);
	Config.PkClear.PkClearPricePcPoints = GetPrivateProfileInt("PkClear","PkClearPricePcPoints",2,KRONO_COMMANDS);
	Config.PkClear.PkClearPricePcPointsForAll = GetPrivateProfileInt("PkClear","PkClearPricePcPointsForAll",20,KRONO_COMMANDS);
	Config.PkClear.PkClearPriceWCoins = GetPrivateProfileInt("PkClear","PkClearPriceWCoins",2,KRONO_COMMANDS);
	Config.PkClear.PkClearPriceWCoinsForAll = GetPrivateProfileInt("PkClear","PkClearPriceWCoinsForAll",20,KRONO_COMMANDS);

	Config.Skin.SkinEnabled			= GetPrivateProfileInt("Skin","SkinEnabled",1,KRONO_COMMANDS);
	Config.Skin.SkinOnlyForGm		= GetPrivateProfileInt("Skin","SkinOnlyForGm",0,KRONO_COMMANDS);
	Config.Skin.SkinLevelReq		= GetPrivateProfileInt("Skin","SkinLevelReq",100,KRONO_COMMANDS);
	Config.Skin.SkinPriceZen		= GetPrivateProfileInt("Skin","SkinPriceZen",100000,KRONO_COMMANDS);
	Config.Skin.SkinPricePcPoint	= GetPrivateProfileInt("Skin","SkinPricePcPoint",0,KRONO_COMMANDS);
	Config.Skin.SkinPriceWCoin		= GetPrivateProfileInt("Skin","SkinPriceWCoin",0,KRONO_COMMANDS);
	
	Config.Ban.BanChat				= GetPrivateProfileInt("Bans","BanChatEnabled",1,KRONO_COMMANDS);
	Config.Ban.UnBanChat			= GetPrivateProfileInt("Bans","UnBanChatEnabled",1,KRONO_COMMANDS);
	Config.Ban.BanChar				= GetPrivateProfileInt("Bans","BanCharEnabled",1,KRONO_COMMANDS);
	Config.Ban.UnBanChar			= GetPrivateProfileInt("Bans","UnBanCharEnabled",1,KRONO_COMMANDS);
	Config.Ban.BanAcc				= GetPrivateProfileInt("Bans","BanAccEnabled",1,KRONO_COMMANDS);
	Config.Ban.UnBanAcc				= GetPrivateProfileInt("Bans","UnBanAccEnabled",1,KRONO_COMMANDS);
	Config.Ban.BanPost				= GetPrivateProfileInt("Bans","BanPostEnabled",1,KRONO_COMMANDS);
	Config.Ban.UnBanPost			= GetPrivateProfileInt("Bans","UnBanPost",1,KRONO_COMMANDS);

	Config.Drop						= GetPrivateProfileInt("GameMasterCMD","Drop",1,KRONO_COMMANDS);
	Config.Gmove					= GetPrivateProfileInt("GameMasterCMD","Gmove",1,KRONO_COMMANDS);
	Config.GuildMove				= GetPrivateProfileInt("GameMasterCMD","GuildMove",1,KRONO_COMMANDS);
	Config.Trace					= GetPrivateProfileInt("GameMasterCMD","Trace",1,KRONO_COMMANDS);
	Config.Disconnect				= GetPrivateProfileInt("GameMasterCMD","Disconnect",1,KRONO_COMMANDS);
	Config.GuildDisconnect			= GetPrivateProfileInt("GameMasterCMD","GuildDisconnect",1,KRONO_COMMANDS);
	Config.Monitoring				= GetPrivateProfileInt("GameMasterCMD","Monitoring",1,KRONO_COMMANDS);
	Config.ConnectState				= GetPrivateProfileInt("GameMasterCMD","ConnectState",1,KRONO_COMMANDS);
	Config.SetChar					= GetPrivateProfileInt("GameMasterCMD","SetChar",1,KRONO_COMMANDS);
	Config.SetPK					= GetPrivateProfileInt("GameMasterCMD","SetPK",1,KRONO_COMMANDS);
	Config.SetZen					= GetPrivateProfileInt("GameMasterCMD","SetZen",1,KRONO_COMMANDS);
	Config.Reload					= GetPrivateProfileInt("GameMasterCMD","Reload",1,KRONO_COMMANDS);

	this->WatchTargetIndex = -1;
}



void __cdecl cChat::Message(BYTE Type,short aIndex,char*msg,...)
{
	char szBuffer[128];
	va_list pArguments;
	va_start(pArguments, msg);
	vsprintf(szBuffer, msg, pArguments);
	va_end(pArguments);
	GCServerMsgStringSend(szBuffer,aIndex,Type);
}

void __cdecl cChat::Message(short aIndex,char*msg,...)
{
	char szBuffer[128];
	va_list pArguments;
	va_start(pArguments, msg);
	vsprintf(szBuffer, msg, pArguments);
	va_end(pArguments);
	GCServerMsgStringSend(szBuffer,aIndex,DEFAULT_MESSAGE);
}

void cChat::MessageServer(char* Sender,char* message,BYTE Type)
{
	PMSG_CHATDATA lpChat;
	memcpy(lpChat.chatid,Sender,strlen(lpChat.chatid));
	memcpy(lpChat.chatmsg,Sender,strlen(lpChat.chatmsg));
	lpChat.h.size = sizeof(PMSG_CHATDATA);
	Type = (Type > 0) ?  0x02 : 0x00;
	PHeadSetB((LPBYTE)&lpChat.h, Type, lpChat.h.size);
	DataSendAll((LPBYTE)&lpChat, lpChat.h.size);
}

void __cdecl cChat::MessageAll(BYTE TypeMsg,BYTE MsgSrvType,char * Sender ,char*msg,...)
{
	char szBuffer[128];
	va_list pArguments;
	va_start(pArguments, msg);
	vsprintf(szBuffer, msg, pArguments);
	va_end(pArguments);

	if (TypeMsg == 0x02 )
	{
		MessageServer(Sender,msg,MsgSrvType);
		return;
	}

	for (short i = OBJMAX - OBJMAXUSER; i <= OBJMAX; i++)
	{
		if (gObj[i].Connected >= 3)		
			GCServerMsgStringSend(szBuffer,gObj[i].m_Index,TypeMsg);
	}
}

void __cdecl cChat::MessageLog(bool Date,cLog::eColor color, cLog::eTypeFile typefile,
					BYTE TypeMsg ,short aIndex,char*msg,...)
{
	char szBuffer[128];
	va_list pArguments;
	va_start(pArguments, msg);
	vsprintf(szBuffer, msg, pArguments);
	va_end(pArguments);
	this->Message(TypeMsg,aIndex,szBuffer);
	Log.LogOutPut(Date,color,typefile,szBuffer);
}

void __cdecl cChat::MessageAllLog(bool Date ,cLog::eColor color, cLog::eTypeFile typefile,
						BYTE TypeMsg,BYTE MsgSrvType ,char * sender,char* msg,...)
{
	char szBuffer[128];
	va_list pArguments;
	va_start(pArguments, msg);
	vsprintf(szBuffer, msg, pArguments);
	va_end(pArguments);
	this->MessageAll(TypeMsg,MsgSrvType,sender,szBuffer);
	Log.LogOutPut(Date,color,typefile,szBuffer);
}



bool cChat::CheckCommand(LPOBJ lpObj, int lConfig, cGmSystem::Commands Command, 
	int NeedZen, int NeedPcPoint, int NeedWCoin,
	int NeedLvl, int Filled, int CheckPlayer, 
	char *CommandName, char *CommandUsage, char *Msg)
{
	bool bResult = false;

	int spaces = 0;
	for(unsigned int i = 0; i < strlen(Msg); i++)
		if(Msg[i]==' ' && Msg[i-1]!=' ')spaces++;

	if((Filled > 0) && ((Filled > spaces) || (((strlen(Msg) < 1) || (strlen(Msg) == 1)) && (Msg[0] == ' '))))
	{				
		Message(lpObj->m_Index,"[%s] Usage: %s", CommandName, CommandUsage);
		return true;
	}

	if (lConfig == 0)
	{
		Message(lpObj->m_Index, "[%s] Function temporarily disabled.", CommandName);
		return true;
	}

	if (!GMS.IsCommand(Command, lpObj->Name))
	{
		Message(lpObj->m_Index, "[%s] You can't use this command.", CommandName);
		return true;
	}		

	if (NeedLvl > 0 && lpObj->Level < NeedLvl)
	{
		Message(lpObj->m_Index, "[%s] You haven't got enougth level.", CommandName);
		bResult = true;
	}

	if (NeedZen > 0 && NeedZen > lpObj->Money)
	{
		Message(lpObj->m_Index, "[%s] You haven't got enougth money.", CommandName);
		bResult = true;
	}					  
	/*
	if (NeedPcPoint > 0 && NeedPcPoint > AddTab[gObj->m_Index].PCPlayerPoints)
	{
		Message(lpObj->m_Index, "[%s] You need %d more PcPoints.", CommandName, NeedPcPoint - AddTab[lpObj->m_Index].PCPlayerPoints);
		bResult = true;
	}*/

	if (NeedWCoin > 0 && NeedWCoin > lpObj->m_wCashPoint)
	{
		Message(lpObj->m_Index, "[%s] You need %d more WCoins.", CommandName, NeedWCoin - lpObj->m_wCashPoint);
		bResult = true;
	}

	if(CheckPlayer > 0)
	{						
		char Target[11], Target2[11];
		int Index = 0, Index2 = 0;
		if(CheckPlayer == 1)
		{
			sscanf(Msg,"%s",&Target);
			Index = gObjGetIndex(Target);
		}
		else if(CheckPlayer == 2)
		{	 
			sscanf(Msg,"%s %s",&Target,&Target2);	  
			Index = gObjGetIndex(Target);
			Index2 = gObjGetIndex(Target2);
		}

		if(Index == -1 || Index2 == -1)
		{													
			Message(lpObj->m_Index,"[%s] Player offline or doesn't exist!", CommandName);
			bResult = true;
		}
	}		 
	return bResult;
}	

void cChat::ChatProtocol(PMSG_CHATDATA * lpChat, short aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	short numproc,lencmd;
	GetNumberProtocol(lpChat->chatmsg,numproc,lencmd);
	switch (numproc)
	{
	case CHAT_DEFAULT:
		if ( (lpObj->Penalty&2)==2)
		{
			Message(aIndex,"Chat for you banned");
			return;
		}
		MsgSendV2(lpObj,(LPBYTE)lpChat,lpChat->h.size);
		DataSend(aIndex,(LPBYTE)lpChat,lpChat->h.size);
		break;
	case CHAT_POST:
		this->PostChat(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CHAT_GUILD:
		this->GuildChat(lpChat,lpObj);
		break;
	case CHAT_PARTY:
		this->PartyChat(lpChat,lpObj);
		break;
	case CHAT_GUILDMASTER:
		this->GuildMasterChat(lpChat,lpObj);
		break;
/************************************************************************/
/*							 Команды									*/
/*																		*/
/*		1.	Чтобы добавить команду, обозвите её константой с префиком	*/
/*			CMD_	и занесите его в enum eChatCommand					*/
/*				(например CMD_TEST)										*/
/*																		*/
/*		2.	Создайте новый метод с передачей таких агрументов			*/
/*				void TestCmd(lpChat,lpObj);								*/
/*			~Если нада будет отправлять пакет с структурой, или			*/
/*				void TestCmd(lpChat->chatmsg[lencmd], lpObj);			*/
/*			~Если ненужно отправлять пакет								*/
/*																		*/
/*		3.	Добавьте в протокол case с новой конатантой из enum			*/
/*			case CMD_TEST:												*/
/*				this->TestCmd(lpChat,lpObj);							*/
/*				break;													*/
/*																		*/
/*		4. Добавьте в метод	 cChat::GetNumberProtocol	строчку вида	*/
/*			if (!strncmp(msgChat,"/test",strlen("/test"))				*/
/*					return CMD_TEST;									*/
/*																		*/
/************************************************************************/
	case CMD_TEST:
		//this->TestCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
#if GS_CASTLE == 1
	case CMD_CS_CHANGE_OWNER:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 0, &lpChat->chatmsg[lencmd]);
		break;
	case CMD_CS_SET_REG_SIEGE:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 1, NULL);
		break;
	case CMD_CS_SET_REG_MARK:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 2, NULL);
		break;
	case CMD_CS_SET_NOTIFY:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 3, NULL);
		break;
	case CMD_CS_SET_START:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 4, NULL);
		break;
	case CMD_CS_SET_END:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 5, NULL);
		break;
	case CMD_CS_CUR_OWNER:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 6, NULL);
		break;
	case CMD_CS_CUR_STATE:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 7, NULL);
		break;
	case CMD_CS_CHANGE_SIDE:
		g_CastleSiege.OperateGmCommand(lpObj->m_Index, 8, &lpChat->chatmsg[lencmd]);
		break;
	case CMD_CRYWOLF_1:
		g_Crywolf.OperateGmCommand(lpObj->m_Index,1);
		break;
	case CMD_CRYWOLF_2:
		g_Crywolf.OperateGmCommand(lpObj->m_Index,2);
		break;
	case CMD_CRYWOLF_3:
		g_Crywolf.OperateGmCommand(lpObj->m_Index,3);
		break;
	case CMD_CRYWOLF_4:
		g_Crywolf.OperateGmCommand(lpObj->m_Index,0);
		break;
#endif
	case CMD_DROP:
		this->DropCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_GMOVE: 
		this->GMoveCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_GUILDMOVE: 
		this->GuildMoveCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_TRACE: 
		this->TraceCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_BANCHAT: 
		this->DisableChatCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_UNBANCHAT:
		this->EnableChatCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_BANPOST: 
		this->BanPost(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_UNBANPOST: 
		this->UnBanPost(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_BANCHAR:
		this->BanChar(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_UNBANCHAR: 
		this->UnBanChar(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_BANACC:
		this->BanAcc(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_UNBANACC:
		this->UnBanAcc(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_DISCONNECT: 
		this->Disconnect(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_GUILD_DISCON: 
		this->GuildDisconnectCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_MONITORING: 
		this->UserWatchingCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_CONNECT_STATE: 
		this->ConnectionStateCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_SETCHAR: 
		this->SetChar(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_SETPK:
		this->SetPK(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_SETZEN: 
		this->SetZen(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_RELOAD: 
		this->Reload(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_GUILDWAR_START:
		this->GuildWarStart(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_GUILDWAR_STOP:
		this->GuildWarStop(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_GUILDWAR_END:
		this->GuildWarEnd(&lpChat->chatmsg[lencmd],lpObj);
		break;

		//case CMD for Player

	case CMD_MOVE:
		this->MoveCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_GUILD_WAR: 
		this->GuildWarCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_BATTLE_SOCCER: 
		this->BattleSoccerCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_REQUEST: 
		this->RequestCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_ONLINE:
		this->OnlineCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_STATUS: 
		this->StatusCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_LEVEL: 
		this->LevelCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_TIME: 
		this->TimeCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_SKIN: 
		this->SkinCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;
	case CMD_PKCLEAR: 
		this->PKClearCmd(&lpChat->chatmsg[lencmd],lpObj);
		break;

	case CMD_ADDSTR: 
	case CMD_ADDAGI: 
	case CMD_ADDVIT: 
	case CMD_ADDENE:
	case CMD_ADDCMD:
		this->AddCmd(&lpChat->chatmsg[lencmd],lpObj,numproc);
		break;
	}
}

void cChat::GetNumberProtocol(char * msgChat,short &numcmd,short &lencmd)
{
	numcmd = CHAT_DEFAULT;
	lencmd = 0;

	if (!strncmp(msgChat,"@",		strlen("@")))		numcmd = CHAT_GUILD,		lencmd = strlen("@");
	if (!strncmp(msgChat,"~",		strlen("~")))		numcmd = CHAT_PARTY,		lencmd = strlen("~");
	if (!strncmp(msgChat,"!",		strlen("!")))		numcmd = CHAT_GUILDMASTER,	lencmd = strlen("!");
	if (!strncmp(msgChat,"/post",	strlen("/post")))	numcmd = CHAT_POST,			lencmd = strlen("/post");
	if (!strncmp(msgChat,"/gg",		strlen("/gg")))

	if (!strncmp(msgChat,"/",strlen("/")))
	{
		numcmd = CMD_DEFAULT;	lencmd = strlen("/");
		
		//////////////////////////////////////////////////////////////////////////
		/*							GameMaster Commands							*/
		//////////////////////////////////////////////////////////////////////////
		if (!strncmp(msgChat,"/drop",			strlen("/drop")))				numcmd =  CMD_DROP,				lencmd = strlen("/drop");
		if (!strncmp(msgChat,"/gmove",			strlen("/gmove")))				numcmd =  CMD_GMOVE,			lencmd = strlen("/gmove");
		if (!strncmp(msgChat,"/guildmove",		strlen("/guildmove")))			numcmd =  CMD_GUILDMOVE,		lencmd = strlen("/guildmove");
		if (!strncmp(msgChat,"/trace",			strlen("/trace")))				numcmd =  CMD_TRACE,			lencmd = strlen("/trace");

		if (!strncmp(msgChat,"/banchat",		strlen("/banchat")))			numcmd =  CMD_BANCHAT,			lencmd = strlen("/banchat");
		if (!strncmp(msgChat,"/unbanchat",		strlen("/unbanchat")))			numcmd =  CMD_UNBANCHAT,		lencmd = strlen("/unbanchat");
		if (!strncmp(msgChat,"/banpost",		strlen("/banpost")))			numcmd =  CMD_BANPOST,			lencmd = strlen("/banpost");		
		if (!strncmp(msgChat,"/unbanpost",		strlen("/unbanpost")))			numcmd =  CMD_UNBANPOST,		lencmd = strlen("/unbanpost");
		if (!strncmp(msgChat,"/banchar",		strlen("/banchar")))			numcmd =  CMD_BANCHAR,			lencmd = strlen("/banchar");
		if (!strncmp(msgChat,"/unbanchar",		strlen("/unbanchar")))			numcmd =  CMD_UNBANCHAR,		lencmd = strlen("/unbanchar");
		if (!strncmp(msgChat,"/banacc",			strlen("/banacc")))				numcmd =  CMD_BANACC,			lencmd = strlen("/banacc");
		if (!strncmp(msgChat,"/unbanacc",		strlen("/unbanacc")))			numcmd =  CMD_UNBANACC,			lencmd = strlen("/unbanacc");

		if (!strncmp(msgChat,"/disconnect",		strlen("/disconnect")))			numcmd =  CMD_DISCONNECT,		lencmd = strlen("/disconnect");
		if (!strncmp(msgChat,"/disconguild",	strlen("/disconguild")))		numcmd =  CMD_GUILD_DISCON,		lencmd = strlen("/disconguild");

		if (!strncmp(msgChat,"/setchar",		strlen("/setchar")))			numcmd =  CMD_SETCHAR,			lencmd = strlen("/setchar");
		if (!strncmp(msgChat,"/setpk",			strlen("/setpk")))				numcmd =  CMD_SETPK,			lencmd = strlen("/setpk");
		if (!strncmp(msgChat,"/setzen",			strlen("/setzen")))				numcmd =  CMD_SETZEN,			lencmd = strlen("/setzen");

		if (!strncmp(msgChat,"/reload",			strlen("/reload")))				numcmd =  CMD_RELOAD,			lencmd = strlen("/reload");

		if (!strncmp(msgChat,"/monitoring",		strlen("/monitoring")))			numcmd =  CMD_MONITORING,		lencmd = strlen("/monitoring");
		if (!strncmp(msgChat,"/connectionstate",strlen("/connectionstate")))	numcmd =  CMD_CONNECT_STATE,	lencmd = strlen("/connectionstate");
		
		if (!strncmp(msgChat,"/guildwarstart",	strlen("/guildwarstart")))		numcmd =  CMD_GUILDWAR_START,	lencmd = strlen("/guildwarstart");
		if (!strncmp(msgChat,"/guildwarstop",	strlen("/guildwarstop")))		numcmd =  CMD_GUILDWAR_STOP,	lencmd = strlen("/guildwarstop");
		if (!strncmp(msgChat,"/guildwarend",	strlen("/guildwarend")))		numcmd =  CMD_GUILDWAR_END,		lencmd = strlen("/guildwarend");


		//////////////////////////////////////////////////////////////////////////
		/*							Commands For Players						*/
		//////////////////////////////////////////////////////////////////////////
		
		if (!strncmp(msgChat,"/move",			strlen("/move")))				numcmd =  CMD_MOVE,				lencmd = strlen("/move");

		if (!strncmp(msgChat,"/guildwar",		strlen("/guildwar")))			numcmd =  CMD_GUILD_WAR,		lencmd = strlen("/guildwar");
		if (!strncmp(msgChat,"/battlesoccer",	strlen("/battlesoccer")))		numcmd =  CMD_BATTLE_SOCCER,	lencmd = strlen("/battlesoccer");
		if (!strncmp(msgChat,"/request",		strlen("/request")))			numcmd =  CMD_REQUEST,			lencmd = strlen("/request");
		
		if (!strncmp(msgChat,"/online",			strlen("/online")))				numcmd =  CMD_ONLINE,			lencmd = strlen("/online");
		if (!strncmp(msgChat,"/status",			strlen("/status")))				numcmd =  CMD_STATUS,			lencmd = strlen("/status");
		if (!strncmp(msgChat,"/level",			strlen("/level")))				numcmd =  CMD_LEVEL,			lencmd = strlen("/level");
		if (!strncmp(msgChat,"/time",			strlen("/time"))) 				numcmd =  CMD_TIME,				lencmd = strlen("/time");

		if (!strncmp(msgChat,"/skin",			strlen("/skin")))				numcmd =  CMD_SKIN,				lencmd = strlen("/skin");
		if (!strncmp(msgChat,"/pkclear",		strlen("/pkclear")))			numcmd =  CMD_PKCLEAR,			lencmd = strlen("/pkclear");

		if (!strncmp(msgChat,"/addstr",			strlen("/addstr")))				numcmd =  CMD_ADDSTR,			lencmd = strlen("/addstr");
		if (!strncmp(msgChat,"/addagi",			strlen("/addagi")))				numcmd =  CMD_ADDAGI,			lencmd = strlen("/addagi");
		if (!strncmp(msgChat,"/addvit",			strlen("/addvit")))				numcmd =  CMD_ADDVIT,			lencmd = strlen("/addvit");
		if (!strncmp(msgChat,"/addene",			strlen("/addene")))				numcmd =  CMD_ADDENE,			lencmd = strlen("/addene");
		if (!strncmp(msgChat,"/addcmd",			strlen("/addcmd")))				numcmd =  CMD_ADDCMD,			lencmd = strlen("/addcmd");
		
		//////////////////////////////////////////////////////////////////////////
		/*					GastleSiege & Crywolf Commands						*/
		//////////////////////////////////////////////////////////////////////////

		if (!strncmp(msgChat,"/cschangeowner",	strlen("/cschangeowner")))		numcmd = CMD_CS_CHANGE_OWNER ,	lencmd = strlen("/cschangeowner");
		if (!strncmp(msgChat,"/cssetregsiege",	strlen("/cssetregsiege")))		numcmd = CMD_CS_SET_REG_SIEGE , lencmd = strlen("/cssetregsiege");
		if (!strncmp(msgChat,"/cssetregmark",	strlen("/cssetregmark")))		numcmd = CMD_CS_SET_REG_MARK,	lencmd = strlen("/cssetregmark");
		if (!strncmp(msgChat,"/cssetnotify",	strlen("/cssetnotify")))		numcmd = CMD_CS_SET_NOTIFY,		lencmd = strlen("/cssetnotify");
		if (!strncmp(msgChat,"/cssetstart",		strlen("/cssetstart")))			numcmd = CMD_CS_SET_START,		lencmd = strlen("/cssetstart");
		if (!strncmp(msgChat,"/cssetend",		strlen("/cssetend")))			numcmd = CMD_CS_SET_END ,		lencmd = strlen("/cssetend");
		if (!strncmp(msgChat,"/cscurowner",		strlen("/cscurowner")))			numcmd = CMD_CS_CUR_OWNER,		lencmd = strlen("/cscurowner");
		if (!strncmp(msgChat,"/cscurstate",		strlen("/cscurstate")))			numcmd = CMD_CS_CUR_STATE,		lencmd = strlen("/cscurstate");
		if (!strncmp(msgChat,"/cschangeside",	strlen("/cschangeside")))		numcmd = CMD_CS_CHANGE_SIDE,	lencmd = strlen("/cschangeside");
		/*CryWolfCmd*/
		if (!strncmp(msgChat,"/crywolf1",		strlen("/crywolf1")))			numcmd = CMD_CRYWOLF_1,			lencmd = strlen("/crywolf1");
		if (!strncmp(msgChat,"/crywolf2",		strlen("/crywolf2")))			numcmd = CMD_CRYWOLF_2,			lencmd = strlen("/crywolf2");
		if (!strncmp(msgChat,"/crywolf3",		strlen("/crywolf3")))			numcmd = CMD_CRYWOLF_3,			lencmd = strlen("/crywolf3");
		if (!strncmp(msgChat,"/crywolf4",		strlen("/crywolf4")))			numcmd = CMD_CRYWOLF_4,			lencmd = strlen("/crywolf4");
	}
	
}

/************************************************************************/
/*                        Chat Commands                                 */
/************************************************************************/

void cChat::GuildMasterChat(PMSG_CHATDATA * lpChat,LPOBJ lpObj)
{
	if (lpObj->AuthorityCode == 8 && lpObj->AuthorityCode == 32)
		AllSendServerMsg(&lpChat->chatmsg[1]);
	else
		this->Message(lpObj->m_Index,"You can not write gold message");

}

void cChat::PartyChat(PMSG_CHATDATA *lpChat,LPOBJ lpObj)
{
	if ( lpObj->PartyNumber >= 0 && gParty.GetPartyCount(lpObj->PartyNumber) >= 0 )
	{
		for (BYTE n = 0; n < MAX_USER_IN_PARTY; n++ )
		{
			BYTE num = gParty.m_PartyS[lpObj->PartyNumber].Number[n];
			if ( num >= 0 )	
				DataSend(num, (LPBYTE)lpChat, lpChat->h.size);
		}
	}
}

void cChat::GuildChat(PMSG_CHATDATA *lpChat,LPOBJ lpObj)
{
	if ( lpObj->GuildNumber > 0 )
	{
/* Notice */
		if ( lpChat->chatmsg[1] == '>' && !strcmp(lpObj->Name, lpObj->lpGuild->Names[0] ) )
			GDGuildNoticeSave(lpObj->lpGuild->Name, &lpChat->chatmsg[2]);

/* Aliances*/
		if ( lpChat->chatmsg[1] == '@' && lpObj->lpGuild->iGuildUnion )
		{
			int iGuildCount = 0;
			int iGuildList[MAX_UNION_GUILD] ={0};

			if ( UnionManager.GetGuildUnionMemberList(lpObj->lpGuild->iGuildUnion, iGuildCount, iGuildList) )
			{
				for ( int i=0;i<iGuildCount;i++)
				{
					_GUILD_INFO_STRUCT *lpGuildInfo = Guild.SearchGuild_Number(iGuildList[i]);

					if ( lpGuildInfo == NULL)
						continue;

					for (BYTE n=0;n<MAX_USER_GUILD;n++)
					{
						if ( lpGuildInfo->Use[n] )
						{
							short number = lpGuildInfo->Index[n];
							BYTE bRez = strcmp(lpGuildInfo->Names[n], gObj[number].Name);

							if ( number >= 0 && !bRez)
								DataSend(number, (LPBYTE)lpChat, lpChat->h.size);
						}
					}
				}
			}

			if ( g_iServerGroupUnionChatting )
			{
				GDUnionServerGroupChattingSend(lpObj->lpGuild->iGuildUnion, lpChat);
			}
/*Guild*/	else
			{
				int count = lpObj->lpGuild->Count;

				if ( count >= 0 )
				{
					for (BYTE n=0;n<MAX_USER_GUILD;n++)
					{
						if ( lpObj->lpGuild->Use[n] )
						{
							short number = lpObj->lpGuild->Index[n];
							BYTE bRez = strcmp(lpObj->lpGuild->Names[n], gObj[number].Name);

							if ( number >= 0 && !bRez )
								DataSend(number, (LPBYTE)lpChat, lpChat->h.size);
						}
					}
				}

				if (  g_iServerGroupGuildChatting && lpObj->lpGuild->Count > 1 )	
					GDGuildServerGroupChattingSend(lpObj->lpGuild->Number, lpChat);
			}
		}
	}
}

void cChat::PostChat(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Post.PostEnabled,GMS.NONE,Config.Post.PostPriceZen,Config.Post.PostPricePcPoint,
		Config.Post.PostPriceWCoin,Config.Post.PostLevelReq,0,0,"POST","/post <msg>",chatmsg)) return;

	switch(Config.Post.PostColor)
	{
	case POST_COLOR_DEF:
		this->MessageAll(2,1,lpObj->Name,"[POST] %s",chatmsg);
		break;
	case POST_COLOR_BLUE:
		this->MessageAll(2,1,lpObj->Name,"~[POST] %s",chatmsg);
		break;
	case POST_COLOR_GREEN:
		this->MessageAll(2,1,lpObj->Name,"@[POST] %s",chatmsg);
		break;
	}
}


/************************************************************************/
/*                      GM Commands                                     */
/************************************************************************/

void cChat::DropCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Drop,GMS.cDrop,0,0,0,0,3,0,"Drop",
				"/drop <Amount> <Type> <Index> <Level> <Skill> <Luck> <Opt> <Exc> <Anc>",chatmsg)) return;

	BYTE Amount = 0;
	BYTE Type = 0;
	BYTE Index = 0;
	BYTE Level = 0;
	BYTE Skill = 0;
	BYTE Luck = 0;
	BYTE Opt = 0;
	BYTE Exc = 0;
	BYTE Anc = 0;

	sscanf(chatmsg,"%d %d %d %d %d %d %d %d %d",&Amount,&Type,&Index,&Level,&Skill,&Luck,&Opt,&Exc,&Anc);
	
	short item = ITEMGET(Type,Index);

	if ( (item < 0 && item > 0x1FFF) || Amount < 0 || Level < 0  || Skill < 0 || Luck < 0 || Opt < 0 || Exc < 0 || Anc < 0)
	{
		this->Message(lpObj->m_Index,"[Drop] No correctly params");
		return;
	}
	if (Amount > 20) Amount = 1;
	if (Level > 13) Amount = 13;
	if (Skill > 1 ) Skill = 1;
	if (Luck > 1) Luck = 1;
	if (Opt > 7 ) Opt = 7;
	if (Exc > 63) Exc = 63;
	if (Anc > 0 ) Anc = 5;
	if (Anc > 10) Anc = 10;

	for (BYTE n = 0; n < Amount; n++)
		ItemSerialCreateSend(lpObj->m_Index,lpObj->MapNumber,lpObj->X,lpObj->Y,item,Level,0,Skill,Luck,Opt,lpObj->m_Index,Exc,Anc);

	Chat.MessageLog(true, Log.c_Navy, Log.t_COMMANDS, 1 ,lpObj->m_Index,
		"[Drop] %d Item Created to %s [%d %d %d %d %d %d %d %d] - Success",
		Amount, lpObj->Name,Type, Index, Level, Skill, Luck, Opt, Exc, Anc);
	
}

/***Move Commands***/

void cChat::GMoveCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Gmove,GMS.cGmove,0,0,0,0,4,1,"GMove","/gmove <NickName> <MapName> <x> <y>",chatmsg))
		return;

	char Target[11];
	char MapName[20];
	BYTE x = 0, y = 0;

	sscanf(chatmsg,"%s %d %d %d",Target,&MapName,&x,&y);

	short TargetIndex = gObjGetIndex(Target);
	BYTE IndexMap = gMoveCommand.FindIndex(MapName);

	if (IndexMap != -1)
		gObjTeleport(TargetIndex, IndexMap, x, y);
	else
		Chat.Message(lpObj->m_Index,"[GMove] %s map not exist",MapName);
	
}

void cChat::GuildMoveCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.GuildMove,GMS.cGuildMove,0,0,0,0,4,0,"GuildMove","/guildmove <GuildName> <MapNumber> <x> <y>",chatmsg))
		return;

	char GuildName[11];
	int MapNumber,x,y;

	sscanf(chatmsg,"%s %d %d %d",GuildName,&MapNumber,&x,&y);

	_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(GuildName);

	for ( BYTE i=0;i<MAX_USER_GUILD;i++)
	{
		if (lpGuild->Index[i] >= 0 && lpGuild != NULL)
		{
			gObjTeleport(lpGuild->Index[i], MapNumber, x++, y);
		}
	}
}

void cChat::TraceCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Trace,GMS.cTrace,0,0,0,0,1,1,"Trace","/trace <Player>",chatmsg))
		return;

	LPOBJ lpTargetObj = gObjFind(chatmsg);
	if (lpTargetObj == NULL) return;

	gObjTeleport(lpObj->m_Index, lpTargetObj->MapNumber, lpTargetObj->X, lpTargetObj->Y);
}

/***Disconnect Commands***/

void cChat::Disconnect(char* chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Disconnect,GMS.cDisconnect,0,0,0,0,1,1,"Disconnect","/disconnect <Player>",chatmsg))
		return;

	int TargetIndex = gObjGetIndex(chatmsg);
	CloseClient(TargetIndex);
}

void cChat::GuildDisconnectCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.GuildDisconnect,GMS.cGuildDisconnect,0,0,0,0,1,0,"GuildDisconnect","/disconguild <GuildName>",chatmsg))
		return;

	_GUILD_INFO_STRUCT* lpGuild = Guild.SearchGuild(chatmsg);

	for ( BYTE i=0;i<MAX_USER_GUILD;i++)
	{
		if (lpGuild->Index[i] >= 0 && lpGuild != NULL)
		{
			this->Message(lpGuild->Index[i],"[GuildDisconnect] %s disconnect our guild",lpObj->Name);
			CloseClient(lpGuild->Index[i]);
		}
	}
	this->Message(lpObj->m_Index,"[GuildDisconnect] %s disconnect successfully",chatmsg);
}

/*Ban Commands*/

void cChat::DisableChatCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.BanChat,GMS.cDisableChat,0,0,0,0,1,1,"BanChat","/banchat <Player>",chatmsg))
		return;

	int Index = gObjGetIndex(chatmsg);
	gObj[Index].Penalty |= 2;
}

void cChat::EnableChatCmd(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.UnBanChat,GMS.cEnableChat,0,0,0,0,1,1,"BanChat","/unbanchat <Player>",chatmsg))
		return;

	int Index = gObjGetIndex(chatmsg);
	gObj[Index].Penalty &= ~2;
}

void cChat::BanPost(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.BanPost,GMS.cBanPost,0,0,0,0,1,1,"BanPost","/banpost <player>",chatmsg))
		return;

}

void cChat::UnBanPost(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.UnBanPost,GMS.cBanPost,0,0,0,0,1,1,"UnBanPost","/unbanpost <player>",chatmsg))
		return;
}

void cChat::BanChar(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.BanChar,GMS.cBanPlayer,0,0,0,0,1,1,"BanChar","/banchar <player>",chatmsg))
		return;
}

void cChat::UnBanChar(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.UnBanChar,GMS.cBanPlayer,0,0,0,0,1,1,"BanChar","/unbanchar <player>",chatmsg))
		return;
}

void cChat::BanAcc(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.BanAcc,GMS.cBanPlayer,0,0,0,0,1,1,"BanChar","/banacc <player>",chatmsg))
		return;
}

void cChat::UnBanAcc(char *chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.Ban.UnBanAcc,GMS.cBanPlayer,0,0,0,0,1,1,"BanChar","/unbanacc <player>",chatmsg))
		return;
}

/*Set Commands*/

void cChat::SetChar(char *chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(lpObj, Config.SetChar, GMS.cSetZen, 0, 0, 0, 0, 2, 1,
		"SetChar", "/setchar <Nick> <Zen> <PCPnt> <WCoins> <AddPnt> <lvl> <Prof>", chatmsg))
		return;

	DWORD Zen = 0, PCPnt = 0, WCoin = 0, AddPnt = 0, Lvl = 0, Prof = 0;
	char Target[11]; 	 
	sscanf(chatmsg, "%s %d %d %d %d %d %d", &Target, &Zen, &PCPnt, &WCoin, &AddPnt, &Lvl, &Prof);

	if(Zen < 0 || Zen > 2000000000)
	{
		Message(lpObj->m_Index, "[SetChar] Zen can't be less than 0 and more than 2000000000!");
		return;
	}	

	/*if(PCPnt < 0 || PCPnt > PCPoint.sPoints.MaximumPCPoints)
	{
		Message(lpObj->m_Index, "[SetChar] PCPnt can't be less than 0 and more than %d!", PCPoint.sPoints.MaximumPCPoints);
		return true;
	}	

	if(WCoin < 0 || WCoin > 10000)
	{
		Message(lpObj->m_Index, "[SetChar] WCoin can't be less than 0 and more than %d!", 10000);
		return;
	}*/

	int MaximumAddPnt;
	if(Config.Add.MaxAddedStats == 0)
		MaximumAddPnt = 32000;
	else
		MaximumAddPnt = 65000;

	if(AddPnt < 0 || AddPnt > MaximumAddPnt)
	{
		Message(lpObj->m_Index, "[SetChar] AddPnt can't be less than 0 and more than %d!", MaximumAddPnt);
		return ;
	}	

	if(Lvl < 0 || Lvl > 400)
	{
		Message(lpObj->m_Index,  "[SetChar] Lvl can't be less than 0 and more than 400!");
		return;
	}

	if(Prof < 0 || Prof > 3)
	{
		Message(lpObj->m_Index,  "[SetChar] Lvl can't be less than 0 and more than 3!");
		return;
	}

	int Index = gObjGetIndex(Target);
	
	if(Zen > 0)
	{
		gObj[Index].Money = Zen;
		GCMoneySend (gObj[Index].m_Index, Zen);
	}

	/*
	if(PCPnt > 0 )	PCPoint.UpdatePoints(tObj,PCPnt,PC_ADD,PCPOINT);
	if(WCoin > 0)	PCPoint.UpdatePoints(tObj,WCoin,PC_ADD,WCOIN);*/

	if(AddPnt > 0)	gObj[Index].LevelUpPoint += AddPnt;
	if(Lvl > 0)		gObj[Index].Level	= Lvl;

	if(Prof > 0)
	{
		switch(Prof)
		{
		case 0:
			break;
		case 1:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 0;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 16;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 32;
			if(gObj->DbClass >= 48 && gObj->DbClass <= 50)gObj->DbClass = 48;
			if(gObj->DbClass >= 64 && gObj->DbClass <= 66)gObj->DbClass = 64;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 80;
			else
				break;
		case 2:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 1;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 17;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 33;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 81;
			else
				break;
		case 3:
			if(gObj->DbClass >= 0 && gObj->DbClass <= 3)gObj->DbClass = 3;
			if(gObj->DbClass >= 16 && gObj->DbClass <= 19)gObj->DbClass = 19;
			if(gObj->DbClass >= 32 && gObj->DbClass <= 35)gObj->DbClass = 35;
			if(gObj->DbClass >= 48 && gObj->DbClass <= 50)gObj->DbClass = 50;
			if(gObj->DbClass >= 64 && gObj->DbClass <= 66)gObj->DbClass = 66;
			if(gObj->DbClass >= 80 && gObj->DbClass < 83)gObj->DbClass = 83;
			else
				break;
		}
	}
	Message(lpObj->m_Index,"[SetChar] You successfully changed %s character.", gObj[Index].Name);
	Message(Index, "[SetChar] Your character was edited by %s, you must relogin!", lpObj->Name);
}

void cChat::SetPK(char *chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(lpObj, Config.SetPK, GMS.cSetPK, 0, 0, 0, 0, 2, 1, "SetPK", "/setpk <nick> <pklvl>", chatmsg))
		return;

	char Target[11];
	int SetLevel;
	sscanf(chatmsg,"%s %d",&Target, &SetLevel);		

	if(SetLevel < 0 || SetLevel > 100)
	{
		this->Message(lpObj->m_Index, "[SetPK] PK lvl can't be less than 0 and more than 100!");
		return;
	}			 

	int Index = gObjGetIndex(Target); 
	
	gObj[Index].m_PK_Level = SetLevel;
	if(SetLevel >= 3)
		gObj[Index].m_PK_Count = SetLevel - 3;
	GCPkLevelSend(Index,SetLevel);	 

	this->Message(lpObj->m_Index, "[SetPK] You successfully changed %s pk.", gObj[Index].Name);
	this->Message(Index, "[SetPK] Your pk was changed to %d by %s.", SetLevel, lpObj->Name);
}

void cChat::SetZen(char *chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(gObj, Config.SetZen, GMS.cSetZen, 0, 0, 0, 0, 2, 1, "SetZen", "/setzen <nick> <value>", chatmsg))
		return;

	int Value;
	char Target[11]; 	 
	sscanf(chatmsg, "%s %d", &Target, &Value);	 	

	if(Value < 0 || Value > 2000000000)
	{
		this->Message(lpObj->m_Index,"[SetZen] Value can't be less than 0 and more than 2000000000!");
		return;
	}			 

	int Index = gObjGetIndex(Target); 
	gObj[Index].Money = Value;
	GCMoneySend (Index, Value);		

	this->Message(lpObj->m_Index, "[SetZen] You sucsessfully changed %s zen.", gObj[Index].Name);
	this->Message(Index, "[SetZen] Your zen was changed to %d by %s.", Value, lpObj->Name);
}

/*Monitoring Commands*/

void cChat::UserWatchingCmd(char* chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(lpObj,Config.Monitoring,GMS.cMonitoring,0,0,0,0,1,1,"Monitoring","/monitoring <Player>",chatmsg))
		return;

	LPOBJ lpTargetObj = gObjFind(chatmsg);

	if ( lpTargetObj == NULL )	return;

	if ( this->WatchTargetIndex == lpTargetObj->m_Index )
	{
		this->WatchTargetIndex = -1;
		this->Message(lpObj->m_Index,"[Monitoring] User %s monitoring disable", lpTargetObj->Name);
	}
	else
	{
		this->Message(lpObj->m_Index,"[Monitoring] User %s Monitoring", lpTargetObj->Name);
		this->WatchTargetIndex = lpTargetObj->m_Index;
	}
}

void cChat::ConnectionStateCmd(char* chatmsg,LPOBJ lpObj)
{
	if (CheckCommand(lpObj,Config.ConnectState,GMS.cConnectState,0,0,0,0,2,0,
		"ConnectState","/connectionstate <Player1> <Player2>",chatmsg))
		return;

	int iTokenNumber,iTokenNumber2;

	sscanf(chatmsg,"%d %d",&iTokenNumber,&iTokenNumber2);

	int lc151 = 0;
	int lc152 = 400;

	if ( iTokenNumber > 0 ) lc151 = iTokenNumber;
	if ( iTokenNumber2 > 0 ) lc152 = iTokenNumber2;

	gObjSendUserStatistic(lpObj->m_Index, lc151, lc152);
}

void cChat::Reload(char *chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(gObj, Config.Reload, GMS.cReload, 0, 0, 0, 0, 1, 0, "Reload", "/reload <number>", chatmsg))
		return; 

	int NumberReload;
	sscanf(chatmsg,"%d",&NumberReload);

	switch (NumberReload)
	{
	case 0:
		{
			
			break;
		}
	case 1:
		{
			
			break;
		}
	case 2:
		{
			
			break;
		}
	case 3:
		{
			if (GMS.IsGMSystem >= 1)
			{
				Message(lpObj->m_Index,"[Reload] GMSystem is disabled");
				return;
			}

			GMS.LoadIniConfig();
			GMS.LoadGMSystem();
			MessageLog(1, Log.c_Blue, Log.t_COMMANDS, 0,lpObj->m_Index, "[Reload] GMSystem Reloaded.");				
			break;
		}
	case 4:
		{
			break;
		}
	case 5:
		{
			break;
		}
	case 6:
		{
			break;
		}
	default:
		{
			Message(lpObj->m_Index, "[Reload] Usage: /reload <Number>.");
			break;
		}
	} 
	return;
}

/*(Without Game Master System)
			Guild Manipulate Commands */

void cChat::GuildWarStart(char *chatmsg,LPOBJ lpObj)
{
	if ( (lpObj->Authority &2)== 2 )
		BattleSoccerGoalStart(0);
}

void cChat::GuildWarStop(char *chatmsg,LPOBJ lpObj)
{
	if ( (lpObj->Authority &2) == 2 )
		BattleSoccerGoalEnd(0);
}

void cChat::GuildWarEnd(char *chatmsg,LPOBJ lpObj)
{
	if ( (lpObj->Authority & 2) == 2  )
		GCManagerGuildWarEnd(chatmsg);
}

/************************************************************************/
/*                  Commands For Player                                 */
/************************************************************************/

void cChat::MoveCmd(char *chatmsg,LPOBJ lpObj)
{
	char pId[25];
	sscanf(chatmsg,"%s",pId);

	if (gMoveCommand.FindIndex(pId) == -1)
	{
		Chat.Message(lpObj->m_Index,"[Move] Usage: /move <MapName>");
		return;
	}

	if ( (lpObj->m_IfState.use) != 0 && lpObj->m_IfState.type  == 3)
	{
		lpObj->TargetShopNumber = -1;
		lpObj->m_IfState.type = lpObj->m_IfState.use = 0;
	}

	if ( lpObj->m_IfState.use > 0 || lpObj->IsInBattleGround || lpObj->Teleport != 0)
	{
		this->Message(lpObj->m_Index,lMsg.Get(MSGGET(6, 68)));
		return;
	}

	if ( lpObj->m_PK_Level >= 6 )
	{
		this->Message(lpObj->m_Index,lMsg.Get(MSGGET(4, 101)));
		return;
	}

	gMoveCommand.Move(lpObj, pId);
}

void cChat::GuildWarCmd(char* chatmsg,LPOBJ lpObj)
{
	if ( strlen(chatmsg) >= 1 )
		GCGuildWarRequestResult(chatmsg, lpObj->m_Index, 0);
}

void cChat::BattleSoccerCmd(char* chatmsg,LPOBJ lpObj)
{
	if ( (lpObj->Authority & 2 ) == 2 )
	{
		char pId[11],Rival[11];
		sscanf(chatmsg,"%s %s",pId,Rival);

		if ( strlen(pId) >= 1 && strlen(Rival) >= 1 )
			::GCManagerGuildWarSet(pId, Rival, 1);
	}
	else
	{
		if ( gEnableBattleSoccer != FALSE && strlen(chatmsg) >= 1  )
			::GCGuildWarRequestResult(chatmsg, lpObj->m_Index, 1);
	}
}

void cChat::RequestCmd(char* chatmsg,LPOBJ lpObj)
{
	BOOL bState = -1;

	if ( strstr(chatmsg, "on" ) != NULL)
		bState = TRUE;

	if ( strstr(chatmsg, "off") != NULL )
		bState = FALSE;

	if ( bState >= FALSE && bState <= TRUE )
	{
		::gObjSetTradeOption(lpObj->m_Index, bState);
		::gObjSetDuelOption(lpObj->m_Index, bState);
	}
}

void cChat::OnlineCmd(char *chatmsg,LPOBJ lpObj)
{
	int totGMs = 0;
	int totPlayers = 0;
	for (short i = OBJMAX - OBJMAXUSER; i< OBJMAX; i++)
	{
		if (gObj[i].Connected == PLAYER_PLAYING)
		{
			if (gObj[i].Authority == 8 || gObj[i].Authority == 32)	totGMs++;
			if (gObj[i].Authority == 0)								totPlayers++;
		}
	}
	Message(lpObj->m_Index , "[ONLINE]: %d Player(s), %d GM(s)",totPlayers, totGMs);
}

void cChat::StatusCmd(char *chatmsg,LPOBJ lpObj)
{
	if(CheckCommand(gObj, 1, GMS.cStatus, 0, 0, 0, 0, 1, 1, "Status", "/status <name>", chatmsg))
		return;

	char Target[11];
	sscanf(chatmsg,"%s",&Target);
	int Index = gObjGetIndex(Target);   
	
	Message(lpObj->m_Index, "IP Address: %s",gObj[Index].Ip_addr);
	Message(lpObj->m_Index, "Account: %s | Character: %s",gObj[Index].AccountID,gObj[Index].Name);
	Message(lpObj->m_Index, "Level: %d | Zen: %d | Resets: %d",gObj[Index].Level,gObj[Index].Money, 0);
	Message(lpObj->m_Index, "Map: %d(%d,%d)",gObj[Index].MapNumber,gObj[Index].MapNumber,gObj[Index].X,gObj[Index].Y); 
	Message(Index, "[Status][GM] %s get your status!", lpObj->Name);	  
}

void cChat::LevelCmd(char *chatmsg,LPOBJ lpObj)
{
	Message(lpObj->m_Index, "Level: %d, Master Level: %d", gObj->Level, 0);
}

void cChat::TimeCmd(char *chatmsg,LPOBJ lpObj)
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	Message(lpObj->m_Index, "Server Time & Date: %02d:%02d:%02d %02d-%02d-%02d.",
		t.wHour, t.wMinute, t.wSecond, t.wDay, t.wMonth, t.wYear);
}

void cChat::SkinCmd(char *chatmsg,LPOBJ lpObj)
{
	if (Config.Skin.SkinOnlyForGm)
	{
		if(CheckCommand(lpObj, Config.Skin.SkinEnabled, GMS.cSkin, 0, 0, 0, 0, 1, 1, "Skin", "/skin <Name> <num>", chatmsg))
			return;

		int NumSkin = 0;			
		char Target[11];
		sscanf(chatmsg,"%s %d",&Target, &NumSkin);
		int Index = gObjGetIndex(Target);
		LPOBJ tObj = &gObj[Index];
		gObj[Index].m_Change = NumSkin;
		gObjViewportListProtocolCreate(tObj);
		Message(lpObj->m_Index,"[Skin] You successfully change %s Skin.",gObj[Index].Name);
		Message(Index,"Your Skin was changed by %s.",lpObj->Name);
	}
	else
	{
		if(CheckCommand(lpObj, Config.Skin.SkinEnabled, GMS.NONE,Config.Skin.SkinPriceZen,Config.Skin.SkinPricePcPoint,
			Config.Skin.SkinPriceWCoin,Config.Skin.SkinLevelReq,1,0, "Skin", "/skin <num>", chatmsg))
			return;

		int NumSkin = 0;
		sscanf(chatmsg,"%d",&NumSkin);
		lpObj->m_Change = NumSkin;
		gObjViewportListProtocolCreate(lpObj);
		Message(lpObj->m_Index, "[Skin] Your Skin successfully changed!");
	}
}

void cChat::PKClearCmd(char *chatmsg,LPOBJ lpObj)
{
	BOOL bRez = -1;

	if (Config.PkClear.PkClearOnlyForGm)
	{
		int Index;

		if(CheckCommand(gObj, Config.PkClear.PkClearEnabled, GMS.NONE, 0, 0, 0, 0, 1, 0, "PKClear", "/pkclear <NickName>", chatmsg))
			Index = lpObj->m_Index;
		else
			Index = gObjGetIndex(chatmsg);

		if (gObj[Index].m_PK_Level <= 3)
		{
			Message(lpObj->m_Index, "[PkClear] %s is not pk!",gObj[Index].Name);
			return;
		}
		gObj[Index].m_PK_Level = 3;
		gObj[Index].m_PK_Count = 0;
		GCPkLevelSend (gObj->m_Index, 3);
		if (lpObj->m_Index != Index)
		{
			Message(lpObj->m_Index, "[PkClear] %s Pk successfully cleared!",gObj[Index].Name);
			Message(lpObj->m_Index, "Your pk was cleared by %s.",lpObj->m_Index);
		}
		else
			Message(lpObj->m_Index, "[PkClear] Your Pk successfully cleared!");
		
	}
	else
	{
		if (gObj->m_PK_Level <=3)
		{												
			Message(lpObj->m_Index, "[PkClear] Your are not pk!");			
			return;
		}			
		int PriceZen;
		int PricePcPoint;
		int PriceWCoin;
		switch(Config.PkClear.PKClearType)
		{	   
		case 1:	
			PriceZen = Config.PkClear.PkClearPriceZen * gObj->m_PK_Count; 		 
			PricePcPoint = Config.PkClear.PkClearPricePcPoints * gObj->m_PK_Count;
			PriceWCoin = Config.PkClear.PkClearPriceWCoins * gObj->m_PK_Count;
			break;
		case 2:	
			PriceZen = Config.PkClear.PkClearPriceZenForAll;			 
			PricePcPoint = Config.PkClear.PkClearPricePcPointsForAll;
			PriceWCoin = Config.PkClear.PkClearPriceWCoinsForAll;
			break;
		case 0: 
			PriceZen = 0;					 
			PricePcPoint = 0;
			PriceWCoin = 0;
			break;
		}

		if(CheckCommand(lpObj, Config.PkClear.PkClearEnabled, GMS.NONE, PriceZen,PricePcPoint,PriceWCoin,
			Config.PkClear.PkClearLevelReq,0,0,"PKClear", "/pkclear", chatmsg))
			return;

		gObj->m_PK_Level = 3;
		gObj->m_PK_Count = 0;
		GCPkLevelSend (gObj->m_Index, 3);	 
		Message(lpObj->m_Index, "[PkClear] Your Pk successfully cleared!");
	}
}

void cChat::AddCmd(char *chatmsg,LPOBJ lpObj,int TypeAdd)
{
	switch(TypeAdd)
	{
	case CMD_ADDSTR:		  
		if(CheckCommand(lpObj, Config.Add.AddPointEnabled, GMS.NONE, Config.Add.AddPriceZen, Config.Add.AddPricePcPoint, 
			Config.Add.AddPriceWCoin, Config.Add.AddPointLevelReq,1, 0, "AddStats", "/addstr <num>", chatmsg))	return;
		break;

	case CMD_ADDAGI:	  
		if(CheckCommand(lpObj, Config.Add.AddPointEnabled, GMS.NONE, Config.Add.AddPriceZen, Config.Add.AddPricePcPoint, 
			Config.Add.AddPriceWCoin, Config.Add.AddPointLevelReq,1, 0, "AddStats", "/addagi <num>", chatmsg))	return;
		break;

	case CMD_ADDVIT:
		if(CheckCommand(lpObj, Config.Add.AddPointEnabled, GMS.NONE, Config.Add.AddPriceZen, Config.Add.AddPricePcPoint, 
			Config.Add.AddPriceWCoin, Config.Add.AddPointLevelReq,1, 0, "AddStats", "/addvit <num>", chatmsg))	return;
		break;

	case CMD_ADDENE:
		if(CheckCommand(lpObj, Config.Add.AddPointEnabled, GMS.NONE, Config.Add.AddPriceZen, Config.Add.AddPricePcPoint, 
			Config.Add.AddPriceWCoin, Config.Add.AddPointLevelReq,1, 0, "AddStats", "/addene <num>", chatmsg))	return;
		break;

	case CMD_ADDCMD:
		if(CheckCommand(lpObj, Config.Add.AddPointEnabled, GMS.NONE, Config.Add.AddPriceZen, Config.Add.AddPricePcPoint, 
			Config.Add.AddPriceWCoin, Config.Add.AddPointLevelReq,1, 0, "AddStats", "/addcmd <num>", chatmsg))	return;
		break;
	}

	DWORD Points;
	sscanf(chatmsg,"%d",&Points);		  


	int MaxPoints = 32000;
	if(Config.Add.Enable65kStats >= 1)
		MaxPoints = -536;	

	int Stats = 0;
	bool bResult = false;

	switch (TypeAdd)
	{
	case 0x00:
		Stats = lpObj->Strength;
		break;
	case 0x01:
		Stats = lpObj->Dexterity;  
		break;
	case 0x02:	  
		Stats = lpObj->Vitality; 
		break;	  
	case 0x03:
		Stats = lpObj->Energy;	 			 
		break;
	case 0x04: 
		Stats = lpObj->Leadership;	
		MaxPoints = 32000;
		break;
	}

	int MaxPointsTemp = MaxPoints; 
	if(MaxPoints > 32767)
		MaxPoints = -32768 + (MaxPoints - 32767);

	if((MaxPoints > 0) && (Stats >= MaxPoints || Stats < 0))
	{
		Message(lpObj->m_Index, "[AddStats] You have max points for this type!!!");
		return;								 
	}
	else if ((MaxPoints < 0) && (Stats < 0) && (Stats >= MaxPoints))
	{
		Message(lpObj->m_Index, "[AddStats] You have max points for this type!!!");
		return;
	}

	int StatsTemp = Stats; 
	Stats += Points;
#pragma warning(disable: 4018)
	if(gObj->LevelUpPoint < Points)
	{	
		Message(lpObj->m_Index, "[AddStats] You don't have enough points to add. Need %d more.", Points - gObj->LevelUpPoint);
		return;
	}

	if((MaxPoints > 0) && (Stats > MaxPoints || Stats < 0))
	{
		Message(lpObj->m_Index, "[AddStats] You can't add more than %d points for this type!!!", MaxPoints - StatsTemp);
		return;								 
	}
	else if ((MaxPoints < 0) && (Stats < 0) && (Stats > MaxPoints))
	{
		Message(lpObj->m_Index, "[AddStats] You can't add more than %d points for this type!!!", MaxPoints - StatsTemp);
		return;
	}		

	if(Points > 200)
	{
		switch (TypeAdd)
		{
		case CMD_ADDSTR:
			lpObj->Strength += Points;
			break;
		case CMD_ADDAGI:
			lpObj->Dexterity += Points;  
			break;
		case CMD_ADDVIT:	  
			lpObj->Vitality += Points; 
			break;	  
		case CMD_ADDENE:
			lpObj->Energy += Points;	 			 
			break;
		case CMD_ADDCMD:
			lpObj->Leadership += Points;	  
			break;
		}
		gObj->LevelUpPoint -= Points;
		GCLevelUpMsgSend(gObj->m_Index, 0);
		Message(lpObj->m_Index, "[AddStats] Your %d stats added, please relogin!", Points);
	}
	else
	{
		BYTE lpMsg[5] = {0xC1,0x05,0xF3,0x06,TypeAdd-CMD_ADDSTR};
		for(UINT i = 0; i < Points; i++)
			CGLevelUpPointAdd((PMSG_LVPOINTADD*)lpMsg, gObj->m_Index); 
		GCLevelUpMsgSend(lpObj->m_Index, 0);	  
		Message(lpObj->m_Index, "[AddStats] Your %d stats added, %d points left!", Points, gObj->LevelUpPoint);
	}
}