/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
*/

#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string>

void record();
void playback();

void main()
{
    char buffer[MAX_PATH];
    wchar_t wtext[MAX_PATH];
    size_t size = 260;
    //mbstowcs_s(size, wtext, buffer, strlen(buffer) + 1, size);

    GetModuleFileName(NULL, wtext, MAX_PATH);

    //size_t pos = 

    record();
    //playback();
}

void record()
{
    DWORD count;
    char data[250] = { 0 };
    char prompt[] = "Enter some text. When you are done, enter quit.\n";
    HANDLE file, input, output;

    /*
        Notes: The actual drive location where this lab writes the file
        may be dependent upon your computer access privileges so you may
        have to change the drive letter to whatever you desire
    */
    TCHAR fileName[] = TEXT("D:\\record.out");

    input = GetStdHandle(STD_INPUT_HANDLE);
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(input, data, 250, &count, NULL);

    while (strncmp(data, "quit", 4) != 0)
    {
        WriteFile(file, data, count, &count, NULL);
        ReadFile(input, data, 250, &count, NULL);
    }
    CloseHandle(file);
}

void playback()
{
    DWORD count = -1;
    char data[250] = { 0 };
    char prompt[] = "Here is the content of your last recording session:\n";
    HANDLE file, output;
    output = GetStdHandle(STD_OUTPUT_HANDLE);

    /*
        Note: the actual drive location where this lab writes the file
        may be dependent upon your computer access priviledges so you may
        have to change the drive letter to whatever you desire
    */
    TCHAR fileName[] = TEXT("D:\\record.out");

    file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(file, data, 250, &count, NULL);

    while (count != 0)
    {
        WriteFile(output, data, count, &count, NULL);
        ReadFile(file, data, 250, &count, NULL);
    }
    CloseHandle(file);
    Sleep(5000);
}