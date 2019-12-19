#include <iostream>
#include "circle.h"

using namespace std;

void test1()
{

    cout << "**********" << endl;
    Circle c1;
    c1.print_info();
    
    cout << "**********" << endl;
    c1.moveto(1, 1);
    c1.print_info();

    cout << "**********" << endl;
    Circle c2(5, 0, 2);
    c2.print_info();

    cout << "**********" << endl;
    Circle c3(0, -1);
    c3.print_info();

    // Circle c4();
    // c4.print_info();
    
    cout << "**********" << endl;
    Circle c5;
    c5 = Circle();
    c5.print_info();
}

int main()
{
    test1();
    return 0;
}
