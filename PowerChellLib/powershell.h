#pragma once
#include "clr.h"

void CreatePowerShellConsole();
void ExecutePowerShellScript(LPWSTR pwszScript);
void ExecutePowerShellCommand(LPWSTR pwszCommand);
BOOL DisablePowerShellEtwProvider(mscorlib::_AppDomain* pAppDomain);
void PatchAllTheThings(mscorlib::_AppDomain* pAppDomain);

BOOL CreateInitialRunspaceConfiguration(mscorlib::_AppDomain* pAppDomain, VARIANT* pvtRunspaceConfiguration);
BOOL StartConsoleShell(mscorlib::_AppDomain* pAppDomain, VARIANT vtRunspaceConfiguration, LPCWSTR pwszBanner, LPCWSTR pwszHelp, LPCWSTR* ppwszArguments, DWORD dwArgumentCount);

BOOL PowerShellCreate(mscorlib::_AppDomain* pAppDomain, VARIANT* pvtPowerShellInstance);
BOOL PowerShellDispose(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance);
BOOL PowerShellAddScript(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, LPWSTR pwszScript);
BOOL PowerShellAddCommand(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, LPCWSTR pwszCommand);
BOOL PowerShellAddArgument(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, VARIANT vtArgument);
BOOL PowerShellInvoke(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, VARIANT* pvtInvokeResult);
BOOL PowerShellGetStream(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, LPCWSTR pwszStreamName, VARIANT* pvtStream);
BOOL PowerShellHadErrors(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance, PBOOL pbHadErrors);

void PrintPowerShellInvokeResult(mscorlib::_AppDomain* pAppDomain, VARIANT vtInvokeResult);
void PrintPowerShellInvokeInformation(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance);
void PrintPowerShellInvokeErrors(mscorlib::_AppDomain* pAppDomain, VARIANT vtPowerShellInstance);
void PrintInformationRecord(mscorlib::_AppDomain* pAppDomain, VARIANT vtInformationRecord);
void PrintErrorRecord(mscorlib::_AppDomain* pAppDomain, VARIANT vtErrorRecord);
void PrintPowerShellInformationStream(mscorlib::_AppDomain* pAppDomain, VARIANT vtInformationStream);
void PrintPowerShellErrorStream(mscorlib::_AppDomain* pAppDomain, VARIANT vtErrorStream);
void PrintPowerShellInvocationStateInfoReason(mscorlib::_AppDomain* pAppDomain, VARIANT vtReason);
void SetConsoleTextColor(WORD wColor, PWORD pwOldColor);