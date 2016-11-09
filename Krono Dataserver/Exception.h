#pragma once

class CMiniDump
{
public:
    CMiniDump();
    ~CMiniDump();

    static void Enable() {
        SetUnhandledExceptionFilter(UnhandledExceptionFilter);
    }
    static void Disable() {
        SetUnhandledExceptionFilter(NULL);
    }

private:
    static LONG WINAPI UnhandledExceptionFilter(_EXCEPTION_POINTERS* lpTopLevelExceptionFilter);
};
