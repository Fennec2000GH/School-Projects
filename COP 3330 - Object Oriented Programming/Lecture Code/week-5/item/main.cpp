#include <iostream>
#include "item.h"

using namespace std;

int main()
{
    Item t;
    t.Show();
    cout << "\n";

    Item t1(12, 100);    
    t1.Show();
    cout << '\n';

    t1.Set(3,400);
    t1.Show();
    cout << '\n';

    return 0;
}
