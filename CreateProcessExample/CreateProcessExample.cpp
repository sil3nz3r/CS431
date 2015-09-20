#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>

//#ifndef UNICODE
//typedef std::string String;
//#else
//typedef std::wstring String;
//#endif

typedef std::basic_string <TCHAR> StringType;

void main(void)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));
    TCHAR szAppName[] = TEXT("C:\\windows\\system32\\calc.exe");
    printf("\n\nReady to craete process\n\n");
    if (!CreateProcess(NULL, szAppName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d). \n", GetLastError());
        return;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    printf("\n\nProcess terminates\n\n");
}