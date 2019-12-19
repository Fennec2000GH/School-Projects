#include <iostream>
#include "thing.h"

using namespace std;

void func()
{
    Thing a(17);
}

int main()
{
    Thing a;        // a: *data = 0;
    Thing b(7);     // b: *data = 6;

    cout << "Calling the function func() " << endl;
    func();
    cout << "Left the function func() " << endl;

    {
        cout << "Entering a local block " << endl;
        Thing c(27);
    }

    cout << "Left the local block " << endl;

    return 0;
}
