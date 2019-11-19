/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 6
Summary: This program renders a pseudo-heterogeneous array of
bank accounts taking on the following categories: Savings,
Checking, and Investment. Each investment account consists of
5 Exchange-Traded Funds. The program is mainly used to store the
accounts of different users, but it can also project the future
growth of each account based on appropriate measures.
*/
#include <iostream>
#include <fstream> 
#include "proj6.h"
//#include "proj6.cpp"

//MAIN FUNCTION DECLARATIONS
void showMenu();
void quit();

int main()
{
    Portfolio P1;
    char choice = ' ';
    showMenu();
    while(choice != 'Q')
    {
        cout << "> ";
        cin.get(choice);
        cin.ignore();
        choice = toupper(choice);
        switch(choice){
            case 'I':
            {
                string input = "";
                cout << "Enter filename: ";
                getline(cin, input);
                if(P1.importFile(input.c_str()) == false)
                    cout << "Invalid file. No data imported" << endl;
                cout << endl;
                break;
            }
            case 'S':
            {
                P1.showAccounts();
                cout << endl;
                break;
            }
            case 'E':
            {
                string output = "";
                cout << "Enter filename: ";
                getline(cin, output);
                P1.createReportFile(output.c_str());
                cout << endl;
                break;
            }
            case 'M':
            {
                showMenu();
                break;
            }
            case 'O':
            {
                P1.sort();
            }
        }
    }
    quit();

    return 0;
}

//MAIN FUNCTION DEFINITIONS
void showMenu()
{
    cout << "\t*** Portfolio Management menu ***" << endl;
    cout << "I \tImport accounts from a file" << endl;
    cout << "S \tShow accounts (brief)" << endl;
    cout << "E \tExport a banking report (to file)" << endl;
    cout << "M \tShow this menu" << endl;
    cout << "Q \tQuit program" << endl;
    cout << "O \tSort accounts" << endl;

    return;
}

void quit()
{
    cout << endl << "Goodbye!" << endl;
    return;
}
