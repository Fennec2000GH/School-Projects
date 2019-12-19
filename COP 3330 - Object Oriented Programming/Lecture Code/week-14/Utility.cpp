// ---------- UTILITY.CPP ----------


// This file contains the definitions for
// a few functions that are useful for controlling the
// running of C++ programs.

#include <iostream>      	    // for cin, cout
#include <cctype>           	// for toupper
#include <iomanip>				// for setf, setw, setprecision
#include "Utility.h"

using namespace std;

// This function displays a terminating message and freezes the
// standard output device (screen) until the user hits a key
// on the keyboard.  It is useful for reviewing a program's output
// after all processing is completed.
void terminateProgram() 
{
    char any;
    cout << "\nPress 'x' followed by ENTER to exit the program...";
    cin >> any;
    cout << "\nPROCESSING COMPLETED . . . GOOD BYE";
}

// This function prompts the user of a program to see if the user
// wants to run the current program again.  It continues prompting
// until the user enters a valid response (Y/y/N/n).
int readyToQuit() 
{
    char ans;                          // holds the user's response
    cout << "\nDo you wish to run the program again (Y for yes, N for no)? ";
    cin >> ans;
    ans = toupper(ans);

    while ((ans !='Y') && (ans!='N'))  // Keep prompting until an
    {                                  // acceptable character is entered.
        cout << "\nPlease answer again with Y or N";
        cout << "\n\tRun the program again? ";
        cin >> ans;
        ans = toupper(ans);
    }
    return(ans =='N');                  // returns 1 when ready to quit; else 0
}

// This function displays a message and freezes the
// standard output device (screen) until the user hits a key
// on the keyboard.  It is useful for pausing the output
// screen while a program is processing.
void waitForUser(void) 
{
    cout << "\nPress 'c' followed by Enter to continue . . .";
    char any;
    cin >> any;
    cin.get();		// pick up newline
    cout << '\n';
}

// This function sets C++ format flags for numeric output.
void setNumeric(void) 
{
    cout << setw(8) << setprecision(2);     //number width=8; precision=2
    cout.setf(ios::fixed, ios::floatfield); //show floats in decimal format
    cout.setf(ios::showpoint);              //show decimal and trailing 0's
}

void swap(int &thingOne, int &thingTwo) 
{
    int temp=thingOne;
    thingOne=thingTwo;
    thingTwo=temp;
}

