#include <iostream>
#include "thing.h"

using namespace std;

Thing::Thing()
{
    data = new int;
    *data = 0;
    cout << "Running default constructor: data = " << *data << endl;
}

Thing::Thing(int x)
{
    data = new int;
    *data = x;
    cout << "Running constructor with parameters: data = " << *data << endl;
}

Thing::~Thing()
{
    if(data)
    {
        delete data;
        data = nullptr;
    }

    cout << "Running destructor." << endl;
}
