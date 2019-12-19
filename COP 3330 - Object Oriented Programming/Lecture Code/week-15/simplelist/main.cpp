#include <iostream>
#include "simplelist.h"    

using namespace std;

int main()
{
    // create and work with a list of ints
    SimpleList< int > list1;       
    for (int i = 0; i < 8; i++)
       list1.Insert(i * 3);        // insert some numbers
       
    cout << "Element at index 4 = " << list1.GetElement(4) << '\n';
    cout << "Entire list is:\n";
    list1.Print();
    cout << "\n\n";
    
    // create a list of doubles
    SimpleList< double > list2;
    for (int i = 0; i < 10; i++)
        list2.Insert(i * 1.1);      // insert some doubles
    
    cout << "Element at index 6 = " << list2.GetElement(6) << '\n';
    cout << "Entire list is:\n";
    list2.Print();
    cout << "\n\n";
    
    return 0;
}
