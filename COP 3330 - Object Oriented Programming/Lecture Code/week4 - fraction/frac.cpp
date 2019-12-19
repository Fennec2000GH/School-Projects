#include <iostream>
#include "frac.h"

using namespace std;

// friend functions
bool Equals(const Fraction& x, const Fraction& y)
{
    return (x.numerator * y.denominator == y.numerator * x.denominator);
}

Fraction Add(const Fraction& x, const Fraction& y)
{
    int num = x.numerator*y.denominator + y.numerator*x.denominator;
    int denom = x.denominator * y.denominator;
    return Fraction(num, denom);  
}

bool Fraction::Equals(const Fraction& rhs)
{
    return (numerator * rhs.denominator == rhs.numerator * denominator);
}

Fraction Fraction::Add(const Fraction& rhs) const
{
   int num = numerator * rhs.denominator + rhs.numerator * denominator;
   int denom = denominator * rhs.denominator;
    return Fraction(num, denom);    // construct fraction and return
}

// Default constructor.  Initializes fraction to 0/1
Fraction::Fraction()
{
    numerator = 0;
    denominator = 1;

    // cout << "Running the default constructor." << endl;
}

// initializes fraction to n/d
Fraction::Fraction(int n, int d)
{
    if (SetValue(n,d) == false)
        SetValue(0,1);

    // cout << "Running the parameterized constructor." << endl;
}

// dummy definition -- NOT trying to convert s to an equivalent fraction in this example

Fraction::Fraction(const string& s)
{
    numerator = 0;
    denominator = 1;
    
    cout << "Inside explicit." << endl;
}

// Get a fraction from standard input, in the form "numerator/denominator."
void Fraction::Input()
{
    char divSign;    // used to consume the '/' character during input
    do
    {
        cin >> numerator >> divSign >> denominator;
        if (denominator == 0)
            cout << "Illegal Fraction.  Try again: ";
    } while (denominator == 0);
}

// Display a fraction, in the form "numerator/denominator."
void Fraction::Show()
{
    cout << numerator << '/' << denominator;
}

int Fraction::GetNumerator()
{
    return numerator;
}

int Fraction::GetDenominator()
{
    return denominator;
}

bool Fraction::SetValue(int n, int d)
{
    if (d == 0)
        return false;
    else
    {
        numerator = n;
        denominator = d;
    }
    return true;
}


// Calculates and returns the decimal value of a fraction
double Fraction::Evaluate()
{
    double n = numerator;   // convert numerator to double
    double d = denominator; // convert denominator to double
    return (n / d);         // compute and return double representation
}
