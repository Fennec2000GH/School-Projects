#ifndef __ENTRY_H
#define __ENTRY_H

#include <iostream>		// so that we can overload << and >>

using namespace std;

// Declarations for class Entry for a phone directory

class Entry
{
   friend istream& operator >> (istream& a, Entry& e);
   friend ostream& operator << (ostream& a, const Entry& e);

public:
   Entry();			            // initializes all values to blanks
   const char* GetName();		// returns name in an entry
	
private:
   char name[16];		    
   char phoneNumber[16];	
   char address[64];		
};

#endif
