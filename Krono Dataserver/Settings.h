#pragma once


class Settings
{
public:
    bool Loading(char * File);
    int ServiceActive;
    u_short UpdatePort;
    u_short ServicePort;
    u_short EventPort;
    u_short RankingPort;
    u_short StartPort;
    int ServersCount;
    int JoinServer_Active;
    int EventServer_Active;
    int RankingServer_Active;
    int DataServer_Active;
    char SQLHost[256];
    char SQLDatabase[256];
    char SQLUser[256];
    char SQLPassword[256];
};
extern Settings gSettings;

