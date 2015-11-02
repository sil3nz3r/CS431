/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
*/

#include <windows.h>

void record();

void main()
{
    record();
}

void record()
{
    DWORD count;
    char data[250] = {0};
    char prompt[] = "Enter some text. When you are done, enter quit.\n";
    HANDLE file, input, output;

    /*
        Notes: The actual drive location where this lab writes the file
        may be dependent upon your computer access privileges so you may
        have to change the drive letter from H: to whatever
    */
    TCHAR fileName[] = TEXT("C:\\record.out");

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