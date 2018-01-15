#ifndef _GMSYSTEM_H
#define _GMSYSTEM_H
// ---
// ---
enum GM_COMMANDS
{
	COMMAND_DROP,
	COMMAND_GG,
	COMMAND_SETZEN,
	COMMAND_STATS,
	COMMAND_MOVE,
	COMMAND_SETPK,
	COMMAND_PKCLEAR,
	COMMAND_BANPLAYER,
	COMMAND_RELOAD,
	COMMAND_SKIN,
	COMMAND_BANCHAT,
	COMMAND_UNBANCHAT,
	COMMAND_DISK,
	COMMAND_TRACE,
};
// ---
struct GMSYSTEM_DATA
{
	int   iType;
	char  szName[11];
	int   iCommand[20];
};
// ---
class CGMSystem
{
public:
	CGMSystem();
	virtual ~CGMSystem();
	void LoadIniConfig(char * filename);
	void Load(char * filename);
	// ---
	// ---
	// ---
	bool IsCommand(LPOBJ lpObj, int Command);
	// ---
	int  iDataCount;
	int  IsGMSystem;
	// ---
	GMSYSTEM_DATA m_Data[30];
};
extern CGMSystem GMSystem;
#endif