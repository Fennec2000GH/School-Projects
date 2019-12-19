#include <iostream>       // for cout
#include "frac.h"         // for Fraction declarations

using namespace std;

void test1()
{
    // These declarations use the default constructor
    Fraction f1, f2;
    
    //These declarations use the constructor with parameters
    Fraction f3(3,4), f4(6);

    // Use the objects
    cout << "\n The fraction f1 is ";
    f1.Show();

    cout << "\n The fraction f2 is ";
    f2.Show();
    
    cout << "\n The fraction f3 is ";
    f3.Show();

    cout << "\n The fraction f4 is ";
    f4.Show();

    cout << "\n Now enter first fraction: ";
    f1.Input();
    cout << "\nYou entered ";
    f1.Show();
    cout << endl;

    cout << "\n Now enter second fraction: ";
    f2.Input();
    cout << "\nYou entered ";
    f2.Show();
    cout << endl;

    // Finally, find the floating-point value of f1 and f2
    cout << "\n The value of fraction 1 is " << f1.Evaluate() << '\n';
    cout << "\n The value of fraction 2 is " << f2.Evaluate() << '\n';
}

void test2()
{
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    Fraction f3(3, 7);

    if(Equals(f1, f2))
        cout << "Two fractions are equal." << endl;
    else
        cout << "Two fractions are NOT equal." << endl;

    if(Equals(f2, f3))
        cout << "Two fractions are equal." << endl;
    else
        cout << "Two fractions are NOT equal." << endl;

    if(f1.Equals(f2))
        cout << "Two fractions are equal." << endl;
    else
        cout << "Two fractions are NOT equal." << endl;

    if(f2.Equals(f3))
        cout << "Two fractions are equal." << endl;
    else
        cout << "Two fractions are NOT equal." << endl;


    Fraction f4 = Add(f1, f2);
    f4.Show();
    cout << endl;

    f4 = f1.Add(f2);
    f4.Show();
    cout << endl;

    Fraction f5 = Add(f1, f3);
    f5.Show();
    cout << endl;

    f5 = f1.Add(f3);
    f5.Show();
    cout << endl;
}

void test3()
{
    Fraction f1, f2, f3, f4;
    f1 = 5;               // uses conversion constructor: f1 = Fraction(5)
    f2 = Fraction(6);     // explicit use of constructor
    f3.SetValue(3,8);      // set f3 to 3/8

    f4 = Add(f3, 10);       // uses conversion constructor on 10
                            // The above call is equivalent to:
                            // f4 = Add(f3, Fraction(10));
    cout << "\nf1 = ";
    f1.Show();
    cout << "\nf2 = ";
    f2.Show();
    cout << "\nf3 = ";
    f3.Show();
    cout << "\nf4 = ";
    f4.Show();
    cout << endl;

    // Try the "explicit" constructor
    // Fraction f1;
    // f1 = "abc";          // this will NOT work 
    // Fraction f1;
    f1 = Fraction("abc");   // this WILL work (explicit constructor call)
    f1.Show();
    cout << endl;
}

int main()
{
        // test1();
        test2();
        // test3();

        cout << "Goodbye!\n";
}
