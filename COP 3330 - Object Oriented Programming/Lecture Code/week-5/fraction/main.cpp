#include <iostream>       // for cout
#include "frac.h"         // for Fraction declarations

using namespace std;

void test1()
{
    Fraction f1(1, 2), f2(2, 3), f3(3, 4);
    Fraction f4 = f1 + f2 + f3;

    f1.Show();
    cout << " + ";
    f2.Show();
    cout << " + ";
    f3.Show();
    cout << " = ";
    f4.Show();
    cout << endl;

    f4 = f1 + 5;
    f4.Show();
    cout << endl;
  
/*    f4 = 5 + f1;
    f4.Show();
    cout << endl;
    */
}

void test2()
{
    Fraction f1(1, 2);
    Fraction f2(2, 4);

    if(f1 == f2)
        cout << "They are equal" << endl;
    else
        cout << "They are NOT equal" << endl;

    cout  << "Please input f1" << endl;
    cin >> f1;
    cout  << "Please input f2" << endl;
    cin >> f2;

    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
}

void test3()
{
    Fraction f1(1, 2);
    cout << "f1 = " << ++f1 << endl;
    cout << "f1 = " << f1++ << endl;
    cout << "f1 = " << f1 << endl;
}

void test4()
{
    Fraction f1(2, 4);
    f1.Show();
    cout << endl;

    Fraction f2(24, 18);
    f2.Show();
    cout << endl;

}

int main()
{
        // test1();
        test2();
        // test3();
        // test4();

        cout << "Goodbye!\n";
}
