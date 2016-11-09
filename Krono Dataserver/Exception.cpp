#include "stdafx.h"

typedef BOOL(WINAPI* MINIDUMPWRITEDUMP)(HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
                                        CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                        CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                        CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam
                                       );


CMiniDump::CMiniDump()
{
    Enable();
}

CMiniDump::~CMiniDump()
{
    Disable();
}

LONG WINAPI CMiniDump::UnhandledExceptionFilter(_EXCEPTION_POINTERS* lpTopLevelExceptionFilter)
{
    HMODULE DllHandle = LoadLibrary(_T("DBGHELP.DLL"));

    if (DllHandle)
    {
        MINIDUMPWRITEDUMP Dump = (MINIDUMPWRITEDUMP)GetProcAddress(DllHandle, "MiniDumpWriteDump");

        if (Dump)
        {
            TCHAR        DumpPath[MAX_PATH] = { 0, };
            SYSTEMTIME    SystemTime;

            GetLocalTime(&SystemTime);

            _sntprintf(DumpPath, MAX_PATH, _T("%d-%d-%d_%dh%dm%ds.dmp"),
                       SystemTime.wYear,
                       SystemTime.wMonth,
                       SystemTime.wDay,
                       SystemTime.wHour,
                       SystemTime.wMinute,
                       SystemTime.wSecond);

            HANDLE FileHandle = CreateFile(
                                    DumpPath,
                                    GENERIC_WRITE,
                                    FILE_SHARE_WRITE,
                                    NULL, CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL);

            if (FileHandle != INVALID_HANDLE_VALUE)
            {
                _MINIDUMP_EXCEPTION_INFORMATION MiniDumpExceptionInfo;

                MiniDumpExceptionInfo.ThreadId = GetCurrentThreadId();
                MiniDumpExceptionInfo.ExceptionPointers = lpTopLevelExceptionFilter;
                MiniDumpExceptionInfo.ClientPointers = FALSE;

                BOOL Success = Dump(
                                   GetCurrentProcess(),
                                   GetCurrentProcessId(),
                                   FileHandle,
                                   MiniDumpNormal,
                                   &MiniDumpExceptionInfo,
                                   NULL,
                                   NULL);

                if (Success)
                {
                    CloseHandle(FileHandle);
                    FreeLibrary(DllHandle);

                    if (gSettings.JoinServer_Active == 1)
                    {
                        gDataBase.ExecFormat("UPDATE MEMB_STAT SET ConnectStat = 0");
                        gDataBase.Clear();
                    }

                    return EXCEPTION_EXECUTE_HANDLER;
                }
            }
            CloseHandle(FileHandle);
        }
        FreeLibrary(DllHandle);
    }

    if (gSettings.JoinServer_Active == 1)
    {
        gDataBase.ExecFormat("UPDATE MEMB_STAT SET ConnectStat = 0");
        gDataBase.Clear();
    }

    return EXCEPTION_CONTINUE_SEARCH;
}