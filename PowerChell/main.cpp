#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#include "../PowerChellLib/powershell.h"

typedef struct _POWERCHELL_OPTIONS
{
    LPWSTR Script;
    LPWSTR Command; // Add a command-line field.
} POWERCHELL_OPTIONS, *PPOWERCHELL_OPTIONS;

void PowerChellMain();
BOOL ParseCommandLine(PPOWERCHELL_OPTIONS pOptions);

#ifdef _WINDLL

extern "C" __declspec(dllexport) void APIENTRY Start();
void StartPowerShellInNewConsole();

HANDLE g_hEvent = NULL;

#pragma warning(disable : 4100)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        g_hEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartPowerShellInNewConsole, NULL, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

void APIENTRY Start()
{
    WaitForSingleObject(g_hEvent, INFINITE);
}

void StartPowerShellInNewConsole()
{
    AllocConsole();
    PowerChellMain();
    SetEvent(g_hEvent);
    CloseHandle(g_hEvent);
    FreeConsole();
}

#else

int main()
{
    PowerChellMain();

    return 0;
}

#endif // #ifdef _WINDLL

void PowerChellMain()
{
    POWERCHELL_OPTIONS pOptions = { 0 };
    
    ParseCommandLine(&pOptions);

    if (pOptions.Script != NULL)
    {
        ExecutePowerShellScript(pOptions.Script);
        return;
    }

    if (pOptions.Command != NULL) {
        ExecutePowerShellCommand(pOptions.Command);
        return;
    }
    CreatePowerShellConsole();
    
}

BOOL ParseCommandLine(PPOWERCHELL_OPTIONS pOptions)
{
    int iArgc = 0;
    LPWSTR* ppwszArgv = NULL;

    ppwszArgv = CommandLineToArgvW(GetCommandLineW(), &iArgc);
    if (ppwszArgv == NULL)
    {
        return FALSE;
    }

    for (int i = 0; i < iArgc; i++)
    {
        // Execute PowerShell from a file.
        if (_wcsicmp(ppwszArgv[i], L"-f") == 0)
        {
            i += 1;
            if (i < iArgc && ppwszArgv[i] != NULL)
            {
                pOptions->Script = ppwszArgv[i];
            }
        }
        // Execute PowerShell from the command line.
        if (_wcsicmp(ppwszArgv[i], L"-c") == 0)
        {
            i += 1;
            if (i < iArgc && ppwszArgv[i] != NULL)
            {
                pOptions->Command = ppwszArgv[i];
            }
        }
    }

    return TRUE;
}