// Test program and general support functions
// for phone directory

#include <cctype>			// for toupper
#include <iostream>		    // for cin, cout
//#include "directory.h"		// for class Directory
#include "directory.cpp"
#include "entry.cpp"
using namespace std;

void ShowMenu()
// Display the main program menu.
{
   cout << "\n\t\t*** PHONE Book ***";
   cout << "\n\tI \tInsert a new entry into the directory";
   cout << "\n\tL \tLook up an entry";
   cout << "\n\tR \tRemove an entry";
   cout << "\n\tU \tUpdate an entry";
   cout << "\n\tD \tDisplay the entire directory";
   cout << "\n\t? \tDisplay this menu";
   cout << "\n\tQ \tQuit";
}

char GetAChar(const char* promptString)
// Prompt the user and get a single character,
// discarding the Return character.
// Used in GetCommand.
{
   char response;			// the char to be returned

   cout << promptString;    // Prompt the user
   cin >> response;			        // Get a char,
   response = toupper(response);	// and convert it to uppercase
   cin.get();				// Discard newline char from input.
   return response;
}

bool Legal(char c)
// Determine if a particular character, c, corresponds
// to a legal menu command.  Returns true if legal, false if not.
// Used in GetCommand.
{
	return	((c == 'I') || (c == 'L') || (c == 'R') || (c == 'U') ||
			 (c == 'D') || (c == '?') || (c == 'Q'));
}

char GetCommand()
// Prompts the user for a menu command until a legal
// command character is entered.  Return the command character.
// Calls GetAChar, Legal, ShowMenu.
{
   char cmd = GetAChar("\n\n>");	// Get a command character.

   while (!Legal(cmd))		// As long as it's not a legal command,
   {				// display menu and try again.
	cout << "\nIllegal command, please try again . . .";
	ShowMenu();
	cmd = GetAChar("\n\n>");
   }
   return cmd;
}

int main()
{
   Directory d;			// Create and initialize a new directory.

   ShowMenu();				// Display the menu.

   char command;			// menu command entered by user
   do
   {
	command = GetCommand();		// Retrieve a command.
	switch (command)
	{
		case 'I': d.Insert();				break;
		case 'L': d.Lookup();				break;
		case 'R': d.Remove();				break;
		case 'U': d.Update();				break;
		case 'D': d.DisplayDirectory();	break;
		case '?': ShowMenu();				break;
		case 'Q':					break;
	}
   } while (command != 'Q');

   return 0;
}
