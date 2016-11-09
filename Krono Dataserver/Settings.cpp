#include "stdafx.h"


bool Settings::Loading(char * File)
{
    FILE * IniConfig = fopen(File, "r");

    if (!IniConfig)
    {
        LogAddC(eError, "[Failure] Loading configs [%s]", File);
        return false;
    }
    else
    {
        LogAddC(eLoading, "KronoDataserver 0.0.0.2 Season %d", SEASON);

        this->ServiceActive = 0;

        this->JoinServer_Active = GetPrivateProfileIntA("JoinServer", "Active", 1, File);
        this->ServicePort = (u_short)GetPrivateProfileIntA("JoinServer", "ServerPort", 55970, File);
        this->UpdatePort = (u_short)GetPrivateProfileIntA("JoinServer", "UpdatePort", 55557, File);

        this->EventServer_Active = GetPrivateProfileIntA("EventServer", "Active", 1, File);
        this->EventPort = (u_short)GetPrivateProfileIntA("EventServer", "EventPort", 44456, File);

        this->RankingServer_Active = GetPrivateProfileIntA("RankingServer", "Active", 1, File);
        this->RankingPort = (u_short)GetPrivateProfileIntA("RankingServer", "RankingPort", 44455, File);

        this->DataServer_Active = GetPrivateProfileIntA("DataServer", "Active", 1, File);
        this->StartPort = (u_short)GetPrivateProfileIntA("DataServer", "StartPort", 55960, File);
        this->ServersCount = GetPrivateProfileIntA("DataServer", "ServersCount", 2, File);

        GetPrivateProfileString("Database", "Server", "(local)", this->SQLHost, sizeof(this->SQLHost), File);
        GetPrivateProfileString("Database", "Database", "MuOnline", this->SQLDatabase, sizeof(this->SQLDatabase), File);
        if (GetPrivateProfileIntA("Database", "TrustedConnect", 1, File) == 0)
            GetPrivateProfileString("Database", "Username", "sa", this->SQLUser, sizeof(this->SQLUser), File);
        GetPrivateProfileString("Database", "Password", "1234", this->SQLPassword, sizeof(this->SQLPassword), File);

        LogAddC(eLoading, "[Config] Load from : [%s]", File);
        fclose(IniConfig);
    }

    return true;
}

