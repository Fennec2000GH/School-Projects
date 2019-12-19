#ifndef FRACTION_H
#define FRACTION_H

#include <string>
using namespace std;

class Fraction
{
      friend bool Equals(const Fraction& x, const Fraction& y);
      friend Fraction Add(const Fraction& x, const Fraction& y);
public:
    Fraction();                   // Default constructor 
    Fraction(int n, int d=1);     // Constructor with parameters (can be used as a conversion constructor)

    explicit Fraction(const string& s);  // No automatic conversion from string
    
    //standard input/output routines
    void Input();                 // Input a fraction from keyboard.
    void Show();                  // Display a fraction on screen

    bool Equals(const Fraction& rhs);
    Fraction Add(const Fraction& rhs) const;
    
    // Accessors
    int GetNumerator();
    int GetDenominator();
   
    // Mutator
    bool SetValue(int n, int d);   // Set the fraction's value through parameters
    double Evaluate();             // Return the decimal value of a fraction

private:
    int numerator;                 // Top part (any integer)
    int denominator;               // Denom must be non-zero
};

#endif
