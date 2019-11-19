/* Name: Caijun Qin
Date: 11/12/2018
Section: 6
Assignment: 6
Due Date: 11/20/2018
About this project:
This program allows the user to enter and edit a string with
a variety of options. The user may capitalize, uncaptitalize, replace specific
characters with new characters, rewrite the string, or generate a random string.
The user can even analyze the character type count in the string, ie the number
of letters, digits, punctuation marks, and white spaces.
Assumptions: The user will only enter real numbers and no characters.
All work below was performed by Caijun Qin */

#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;

//FUNCTION DECLARATIONS
void printMenu();
void print(string str);
void uppercase(string &str);
void lowercase(string &str);
void replaceChar(string &str);
void printStats(string str);
void newString(string &str);
void jazz(string &str);

int main(){
    double menuChoice = -1;
    string choice;

    //starts the program here
    cout << "To get started, enter anything you'd like, then hit enter:  \n";
    getline(cin, choice);
    printMenu();

    while(menuChoice != 0){
        //selects for the menu option
        cout << "Selection -----> ";
        cin >> menuChoice;

        //check for invalid numerical input, out of range, or character input
        while(menuChoice != (int) menuChoice || menuChoice < 0 || menuChoice > 8){
            cout << "Invalid Choice." << "\n\n";
            cout << "Selection -----> ";
            cin >> menuChoice;
        }

        //executes function based on menu option selected
        switch((int) menuChoice){
            case 1:
                print(choice);
                break;
            case 2:
                uppercase(choice);
                break;
            case 3:
                lowercase(choice);
                break;
            case 4:
                replaceChar(choice);
                break;
            case 5:
                printStats(choice);
                break;
            case 6:
                newString(choice);
                break;
            case 7:
                jazz(choice);
                break;
            case 8:
                printMenu();
        }
    }
    cout << "Bye!" << "\n\n";

    return 0;
}

//FUNCTION DEFINITIONS
//option 1
void print(string str){
    cout << "Current String:  " << str << "\n\n\n";
    return;
}

//option 2
void uppercase(string &str){
    for(int counter = 0; counter < str.size(); counter++){
        str[counter] = toupper(str[counter]);
    }

    return;
}

//option 3
void lowercase(string &str){
    for(int counter = 0; counter < str.size(); counter++){
        str[counter] = tolower(str[counter]);
    }

    return;
}

//option 4
void replaceChar(string &str){
    char a;
    char b;
    int replaceCounter = 0;
    cout << "Replace all of these characters:  ";
    cin >> a;
    cout << "To these characters:  ";
    cin >> b;
    for(int counter = 0; counter < str.size(); counter++){
        if(str[counter] == a){
            str[counter] = b;
            replaceCounter++;
        }
    }
    cout << replaceCounter << " characters replaced.";
    cout << "\n\n";

    return;
}

//option 5
void printStats(string str){
    //keeps count of each statistic
    int letters = 0;
    int punctuations = 0;
    int digits = 0;
    int whitespace = 0;
    for(int counter = 0; counter < str.size(); counter++){
        if(isalpha(str[counter]) != false){
            letters++;
        } else if(ispunct(str[counter]) != false){
            punctuations++;
        } else if(isdigit(str[counter]) != false){
            digits++;
        } else if(isspace(str[counter]) != false){
            whitespace++;
        }
    }

    //prints out the stats
    cout << "Letters:  " << letters << "\n";
    cout << "Punctuation:  " << punctuations << "\n";
    cout << "Digits:  " << digits << "\n";
    cout << "Whitespace:  " << whitespace << "\n";
    cout << "\n";

    return;
}

//option 6
void newString(string &str){
    str.clear();
    cout << "Enter a new string:  \n";
    cin.ignore();
    getline(cin, str);
    cout << "\n";

    return;
}

//option 7
void jazz(string &str){
    srand(time(0));
    int size = rand() % 50 + 1;
    str.clear();
    for(int counter = 0; counter < size; counter++){
        str += (char) (rand() % 91 + 32);
    }
    cout << "Your string is now:  " << str;
    cout << "\n\n";

    return;
}

//option 8
void printMenu(){
    cout << "\n";
    cout << "String Manipulator Options Menu \n";
    cout << "------------------------------- \n";
    cout << "1 - Print the current string \n";
    cout << "2 - Make the string all Uppercase \n";
    cout << "3 - Make the string all Lowercase \n";
    cout << "4 - Replace a character \n";
    cout << "5 - Show string statistics \n";
    cout << "6 - Enter a new string \n";
    cout << "7 - Jazz things up... (You'll lose your current string!) \n";
    cout << "8 - Show this menu \n";
    cout << "0 - Quit \n";
    cout << "\n\n";

    return;
}
