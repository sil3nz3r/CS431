/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
    Assignment: Lab 1 - Windows Processes
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::setfill;
using std::left;

void showMenu();
void startApp(const TCHAR* appPath);

void main()
{
    while (true)
    {
        bool correctInput = true;

        // Show the main menu
        showMenu();

        // Get the input and convert it to lower case
        string input;
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);

        // Find System folder
        TCHAR windir[MAX_PATH];
        GetSystemDirectory(windir, MAX_PATH);

        // Switch statement to get the app name
        if (input == "c") wcscat_s(windir, TEXT("\\calc.exe"));
        else if (input == "i") wcscat_s(windir, TEXT("\\ipconfig.exe"));
        else if (input == "n") wcscat_s(windir, TEXT("\\netstat.exe"));
        else if (input == "p") wcscat_s(windir, TEXT("\\mspaint.exe"));
        else if (input == "s") wcscat_s(windir, TEXT("\\systeminfo.exe"));
        else if (input == "o") wcscat_s(windir, TEXT("\\notepad.exe"));
        else if (input == "e") return;
        else
        {
            cout << "invalid input";
            correctInput = false;
        }

        if (correctInput)
        {
            startApp(windir);
        }
    }
}

void startApp(const TCHAR* appPath)
{
    // Define necessary variables for CreateProcess
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // Get the full app path
    TCHAR szAppName[MAX_PATH];
    wcscpy_s(szAppName, appPath);

    printf("\n\n");

    // Launch the app
    printf("Ready to create process...\n");
    if (!CreateProcess(NULL, szAppName, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d). \n", GetLastError());
        return;
    }
    else
    {
        printf("App Launched...\n");
    }
    WaitForSingleObject(pi.hProcess, INFINITE);    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    printf("Process terminates...\n");

    printf("\n\n");
}

void showMenu()
{
    cout << setfill('-') << setw(40) << "-" << endl
        << setfill(' ') << setw(40) << left << "| Please select command to run" << endl
        << setfill('-') << setw(40) << "-" << endl;
    cout << setfill(' ');
    cout << setw(26) << left << "c - for calc.exe" << endl
        << setw(26) << left << "i - for ipconfig.exe" << endl
        << setw(26) << left << "n - for netstat.exe" << endl
        << setw(26) << left << "p - for mspaint.exe" << endl
        << setw(26) << left << "s - for systeminfo.exe" << endl
        << setw(26) << left << "o - for notepad.exe" << endl
        << setw(26) << left << "e - to exit" << endl;
}