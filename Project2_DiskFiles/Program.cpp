/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>

using std::string;

void record(const string &);
void playback(const string &);

const size_t max_capacity = MAX_PATH;

void main()
{
    // Declare necessary variables
    DWORD count;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> How many files do you want to generate?\n";
    HANDLE file, input, output;

    // Initialize I/O handles
    input = GetStdHandle(STD_INPUT_HANDLE);
    output = GetStdHandle(STD_OUTPUT_HANDLE);

    // Prompt the user and read file
    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(input, data, max_capacity, &count, NULL);

    // Get the directory of the current process
    char myCurrentDir[max_capacity];
    GetCurrentDirectory(max_capacity, myCurrentDir);

    // record and playback file
    record(myCurrentDir);
    playback(myCurrentDir);
}

void record(const string & currentDir)
{
    // Declare necessary variables
    DWORD count;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> Enter some text. When you are done, enter quit.\n";
    HANDLE file, input, output;

    // Initialize handles and the necessary files
    input = GetStdHandle(STD_INPUT_HANDLE);
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    file = CreateFile((currentDir + "\\file1.txt").c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Prompt the user and read file
    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(input, data, max_capacity, &count, NULL);

    while (strncmp(data, "quit", 4) != 0)
    {
        WriteFile(file, data, count, &count, NULL);
        ReadFile(input, data, max_capacity, &count, NULL);
    }
    CloseHandle(file);
}

void playback(const string & currentDir)
{
    // Declare necessary variables
    DWORD count = -1;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> Here is the content of your last recording session:\n";
    HANDLE file, output;

    // Initialize handles and the necessary files
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    file = CreateFile((currentDir + "\\file1.txt").c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Prompt the user and read file
    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(file, data, max_capacity, &count, NULL);

    while (count != 0)
    {
        WriteFile(output, data, count, &count, NULL);
        ReadFile(file, data, max_capacity, &count, NULL);
    }
    CloseHandle(file);
    Sleep(5000);
}