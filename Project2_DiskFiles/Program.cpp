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
#include <exception>

using std::cin;
using std::cout;
using std::setw;
using std::setfill;
using std::string;
using std::left;
using std::endl;

string showMenu();
void showGoodbye();
void record(const string &);
void playback(const string &);
void startProgram(const string &);
bool isFileExisted(const string &);
DWORD getCreationDisposition(const string &);

const size_t max_capacity = MAX_PATH;
const string invalidInputMsg = "***invalid input!";

void main()
{
    while (true)
    {
        string input = showMenu();
        if (input == "exit")
        {
            showGoodbye();
            return;
        }
        else
        {
            try
            {
                startProgram(input);
            }
            catch (const std::exception&)
            {
                showGoodbye();
                return;
            }
        }
    }
}

string showMenu()
{
    cout << setfill('-') << setw(40) << "-" << endl
        << setfill(' ') << setw(40) << left << "| Please choose an item to generate. Enter 'exit' to exit" << endl
        << setfill('-') << setw(40) << "-" << endl;
    cout << setfill(' ');
    cout << setw(26) << left << "+++ h for hamburger" << endl
        << setw(26) << left << "+++ p for pizza" << endl
        << setw(26) << left << "+++ s for soup" << endl;
    string selection;
    cin >> selection;
    return selection;
}

void startProgram(const string & selectedOption)
{
    // Get the current director of the project
    char myCurrentDir[max_capacity];
    GetCurrentDirectory(max_capacity, myCurrentDir);

    // 
    if (selectedOption == "h") strcat_s(myCurrentDir, TEXT("\\hamburger.txt"));
    else if (selectedOption == "p") strcat_s(myCurrentDir, TEXT("\\pizza.txt"));
    else if (selectedOption == "s") strcat_s(myCurrentDir, TEXT("\\soup.txt"));
    else
    {
        cout << invalidInputMsg << endl;
        return;
    }
    record(myCurrentDir);
    playback(myCurrentDir);
}

inline bool isFileExisted(const string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

DWORD getCreationDisposition(const string & fileDir)
{
    if (isFileExisted(fileDir))
    {
        while (true)
        {
            string input;
            cout << ">>> The file has already exists.\n";
            playback(fileDir);
            cout << ">>> What do you want to do? 'o' to overwrite or 'i' to insert.\n";
            cin >> input;

            if (input == "o") { return CREATE_ALWAYS; }
            else if (input == "i") { return OPEN_EXISTING; }
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

    // Set the file creation disposition type
    DWORD creationDisposition = getCreationDisposition(fileDir);

    // get a hold of the file we need
    file = CreateFile(fileDir.c_str(), GENERIC_WRITE, 0, NULL, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    // Prompt the user and read file
    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(input, data, max_capacity, &count, NULL);

    while (strncmp(data, "done", 4) != 0)
    {
        if (strncmp(data, "exit", 4) == 0)
        {
            throw std::exception();
        }

        WriteFile(file, data, count, &count, NULL);
        ReadFile(input, data, max_capacity, &count, NULL);
    }
    CloseHandle(file);
}

void playback(const string & fileDir)
{
    // Declare necessary variables
    DWORD count = -1;
    char data[max_capacity] = { 0 };
    char prompt[] = ">>> Here is the current content of the file:\n";
    HANDLE file, output;

    // Initialize handles and the necessary files
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    file = CreateFile(fileDir.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Prompt the user and read file
    WriteFile(output, prompt, sizeof(prompt) - 1, &count, NULL);
    ReadFile(file, data, max_capacity, &count, NULL);

    while (count != 0)
    {
        WriteFile(output, data, count, &count, NULL);
        ReadFile(file, data, max_capacity, &count, NULL);
    }
    CloseHandle(file);
}

void showGoodbye()
{
    cout << "Thanks for using the program. Goodbye!";
    Sleep(7000);
}