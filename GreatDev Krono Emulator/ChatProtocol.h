#ifndef _CHATPROC_
#define _CHATPROC_

#include "protocol.h"
#include "Logger.h"
#include "GmSystem.h"

class cChat
{
public:
	cChat();
	~cChat();
	void LoadConfigs();
	void ChatProtocol(PMSG_CHATDATA * lpChat, short aIndex);
	void GetNumberProtocol(char * msgChat,short &numcmd,short &lencmd);

/*Фунция проверки синтаксиса*/
	bool cChat::CheckCommand(LPOBJ lpObj, int lConfig, cGmSystem::Commands Command, 
						int NeedZen, int NeedPcPoint, int NeedWCoin,
						int NeedLvl, int Filled, int CheckPlayer, 
						char *CommandName, char *CommandUsage, char *Msg);


/*Функции вывода*/
	void __cdecl Message(BYTE Type,short aIndex,char*msg,...);
	void __cdecl Message(short aIndex,char*msg,...);
	void MessageServer(char* Sender,char* message,BYTE Type);
	void __cdecl MessageAll(BYTE TypeMsg,BYTE MsgSrvType,char * Sender ,char*msg,...);

	void __cdecl MessageLog(bool ,cLog::eColor, cLog::eTypeFile, BYTE  ,short ,char*,...);
	void __cdecl MessageAllLog(bool ,cLog::eColor, cLog::eTypeFile, BYTE ,BYTE ,char *  ,char*,...);

/*Чат*/
	void GuildMasterChat(PMSG_CHATDATA * lpChat,LPOBJ lpObj);
	void PartyChat(PMSG_CHATDATA *lpChat,LPOBJ lpObj);
	void GuildChat(PMSG_CHATDATA *lpChat,LPOBJ lpObj);
	void PostChat(char *chatmsg,LPOBJ lpObj);

/*GM Commands*/

	void DropCmd(char *chatmsg,LPOBJ lpObj);
	//Move Commands
	void GMoveCmd(char *chatmsg,LPOBJ lpObj);
	void GuildMoveCmd(char *chatmsg,LPOBJ lpObj);
	void TraceCmd(char *chatmsg,LPOBJ lpObj);
	//Disconnect Commands
	void Disconnect(char* chatmsg,LPOBJ lpObj);
	void GuildDisconnectCmd(char *chatmsg,LPOBJ lpObj);
	//Monitoring Commands
	void ConnectionStateCmd(char* chatmsg,LPOBJ lpObj);
	void UserWatchingCmd(char* chatmsg,LPOBJ lpObj);
	//Ban Commands
	void DisableChatCmd(char *chatmsg,LPOBJ lpObj);
	void EnableChatCmd(char *chatmsg,LPOBJ lpObj);
	void BanPost(char *chatmsg,LPOBJ lpObj);
	void UnBanPost(char *chatmsg,LPOBJ lpObj);
	void BanChar(char *chatmsg,LPOBJ lpObj);
	void UnBanChar(char *chatmsg,LPOBJ lpObj);
	void BanAcc(char *chatmsg,LPOBJ lpObj);
	void UnBanAcc(char *chatmsg,LPOBJ lpObj);
	//Set Commands
	void SetPK(char *chatmsg,LPOBJ lpObj);
	void SetChar(char *chatmsg,LPOBJ lpObj);
	void SetZen(char *chatmsg,LPOBJ lpObj);
	//Reload Cmd
	void Reload(char *chatmsg,LPOBJ lpObj);
	/*GM Commands Without GM System*/
	void GuildWarStart(char *chatmsg,LPOBJ lpObj);
	void GuildWarStop(char *chatmsg,LPOBJ lpObj);
	void GuildWarEnd(char *chatmsg,LPOBJ lpObj);

/*Commands For Playes*/
	void MoveCmd(char *chatmsg,LPOBJ lpObj);
	void GuildWarCmd(char* chatmsg,LPOBJ lpObj);
	void BattleSoccerCmd(char* chatmsg,LPOBJ lpObj);
	void RequestCmd(char* chatmsg,LPOBJ lpObj);
	
	void OnlineCmd(char *chatmsg,LPOBJ lpObj);
	void StatusCmd(char *chatmsg,LPOBJ lpObj);
	void LevelCmd(char *chatmsg,LPOBJ lpObj);
	void TimeCmd(char *chatmsg,LPOBJ lpObj);
	void SkinCmd(char *chatmsg,LPOBJ lpObj);
	void PKClearCmd(char *chatmsg,LPOBJ lpObj);

	void AddCmd(char *chatmsg,LPOBJ lpObj,int TypeAdd);

	int WatchTargetIndex;

private:
	struct sConfigCmd
	{
		struct sPost
		{
			BYTE PostEnabled;
			short PostLevelReq;
			int	PostPriceZen;
			int	PostPricePcPoint;
			int	PostPriceWCoin;
			BYTE PostColor;
			int	PostDelay;	
		}Post;

		struct sAdd
		{
			BYTE AddPointEnabled;
			short AddPointLevelReq;
			int	AddPriceZen;
			int	AddPricePcPoint;
			int	AddPriceWCoin;
			short MaxAddedStats;
			BYTE Enable65kStats;	
		}Add;

		struct sPkClear
		{
			BYTE PkClearEnabled;		
			BYTE PkClearOnlyForGm;
			short PkClearLevelReq;
			BYTE PKClearType;
			int PkClearPriceZen;
			int PkClearPriceZenForAll;
			int PkClearPricePcPoints;
			int PkClearPricePcPointsForAll;
			int PkClearPriceWCoins;
			int PkClearPriceWCoinsForAll;
		}PkClear;

		struct sSkin
		{
			BYTE SkinEnabled;
			BYTE SkinOnlyForGm;
			short SkinLevelReq;
			int SkinPriceZen;
			int SkinPricePcPoint;
			int SkinPriceWCoin;
		}Skin;

		struct sBan
		{
			BYTE BanChat;
			BYTE UnBanChat;
			BYTE BanChar;
			BYTE UnBanChar;
			BYTE BanAcc;
			BYTE UnBanAcc;
			BYTE BanPost;
			BYTE UnBanPost;
		}Ban;
		//GM Cmd
		BYTE Drop;
		BYTE Gmove;
		BYTE GuildMove;
		BYTE Trace;
		BYTE Disconnect;
		BYTE GuildDisconnect;
		BYTE Monitoring;
		BYTE ConnectState;
		BYTE SetChar;
		BYTE SetPK;
		BYTE SetZen;
		BYTE Reload;

	}Config;
};

extern cChat Chat;

#endif