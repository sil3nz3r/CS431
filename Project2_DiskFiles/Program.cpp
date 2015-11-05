/*
    Author:     Tu Vu
    Professor:  Gerald Doutt
    Class:      CS431
*/

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::string;
using std::left;
using std::endl;

void showMenu();
void record(const string &);
void playback(const string &);
void doStuff(const string &);
bool isFileExisted(const string &);
DWORD getCreationDisposition(const string &);

const size_t max_capacity = MAX_PATH;
const string invalidInputMsg = "***invalid input!";

void main()
{
    while (true)
    {
        showMenu();

        string input;
        cin >> input;
        if (input == "exit")
        {
            cout << "Thanks for using the program. Goodbye!";
            Sleep(7000);
            return;
        }
        else
        {
            doStuff(input);
        }
        //// Get the directory of the current process
        //char myCurrentDir[max_capacity];
        //GetCurrentDirectory(max_capacity, myCurrentDir);

        //// record and playback file
        //record(myCurrentDir);
        //playback(myCurrentDir);
    }
}

void showMenu()
{
    cout << setfill('-') << setw(40) << "-" << endl
        << setfill(' ') << setw(40) << left << "| Please choose an item to generate. Enter 'exit' to exit" << endl
        << setfill('-') << setw(40) << "-" << endl;
    cout << setfill(' ');
    cout << setw(26) << left << "h for hamburger" << endl
        << setw(26) << left << "p for pizza" << endl
        << setw(26) << left << "s for soup" << endl;
}

void doStuff(const string & selectedOption)
{
    char myCurrentDir[max_capacity];
    GetCurrentDirectory(max_capacity, myCurrentDir);

    if (selectedOption == "h") strcat_s(myCurrentDir, TEXT("\\hamburger.txt"));
    else if (selectedOption == "p") strcat_s(myCurrentDir, TEXT("\\pizza.txt"));
    else if (selectedOption == "s") strcat_s(myCurrentDir, TEXT("\\soup.txt"));
    else
    {
        cout << invalidInputMsg << endl;
        return;
    }
    record(myCurrentDir);
}

inline bool isFileExisted(const string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void record(const string & fileDir)
{
    // Declare necessary variables
    DWORD count;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> Enter some text. When you are done, enter 'done'.\n";
    HANDLE file, input, output;

    // Initialize handles and the necessary files
    input = GetStdHandle(STD_INPUT_HANDLE);
    output = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD creationDisposition = getCreationDisposition(fileDir);

    file = CreateFile(fileDir.c_str(), GENERIC_WRITE, 0, NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

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

DWORD getCreationDisposition(const string & fileDir)
{
    if (isFileExisted(fileDir))
    {
        while (true)
        {
            char input;
            cout << "The file has already exists. Enter 'o' to overwrite or 'a' append\n";
            input = cin.get();

            if (input == 'o') { return CREATE_ALWAYS; }
            else if (input == 'a') { return OPEN_EXISTING; }
            else
            {
                cout << invalidInputMsg << endl;
            }
        }
    }
    else
    {
        return CREATE_NEW;
    }
}

void playback(const string & fileDir)
{
    // Declare necessary variables
    DWORD count = -1;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> Here is the content of your last recording session:\n";
    HANDLE file, output;

    // Initialize handles and the necessary files
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    file = CreateFile((fileDir + "\\file1.txt").c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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