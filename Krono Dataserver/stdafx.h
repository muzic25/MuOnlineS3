#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#define _WIN32_WINNT 0x0502

#include <windows.h>
#include <iostream>
#include <map>
#include <atltime.h>
#include <sqlext.h>
#include <vector>
#include <DbgHelp.h>
#include <Commctrl.h>

#include "KronoDS.h"
#include "LogProc.h"
#include "TServerInfoDisplayer.h"
#include "Defines.h"
#include "Settings.h"
#include "DataBase.h"
#include "IOCP.h"
#include "Structure.h"
#include "Functions.h"
#include "resource.h"
#include "Exception.h"
#include "prodef.h"
#include "Serial.h"

#define SEASON 3

#if(SEASON > 5)
#define INVERTORY_SIZE 3776
#define MAGICLIST_SIZE 450
#else
#define INVERTORY_SIZE 1728
#define MAGICLIST_SIZE 180
#endif

#include "JoinServer_Manager.h"
#include "JoinServer_Protocol.h"
#include "WzUpdSocket.h"
#include "EventServer_Manager.h"
#include "EventServer_Protocol.h"
#include "RankingServer_Manager.h"
#include "RankingServer_Protocol.h"
#include "DataServer_Manager.h"
#include "DataServer_Protocol.h"