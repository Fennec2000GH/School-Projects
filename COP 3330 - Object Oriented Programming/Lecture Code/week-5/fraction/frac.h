#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>
using namespace std;

class Fraction
{
     //  friend bool Equals(const Fraction& x, const Fraction& y);
     //  friend Fraction Add(const Fraction& x, const Fraction& y);
     //  friend Fraction operator+ (const Fraction& x, const Fraction& y);
      friend bool operator== (const Fraction& x, const Fraction& y);
      friend ostream& operator<< (ostream& s, const Fraction& f);
      friend istream& operator>> (istream& s, Fraction& f);

public:
    Fraction();                   // Default constructor 
    Fraction(int n, int d=1);     // Constructor with parameters (can be used as a conversion constructor)

    explicit Fraction(const string& s);  // No automatic conversion from string
    
    //standard input/output routines
    void Input();                 // Input a fraction from keyboard.
    void Show();                  // Display a fraction on screen

    bool Equals(const Fraction& rhs);
    Fraction Add(const Fraction& rhs) const;
    Fraction operator+ (const Fraction& rhs) const;
    Fraction& operator++();
    Fraction operator++(int);
    
    // Accessors
    int GetNumerator();
    int GetDenominator();
   
    // Mutator
    bool SetValue(int n, int d);   // Set the fraction's value through parameters
    double Evaluate();             // Return the decimal value of a fraction
    void Normalize();
private:
    int numerator;                 // Top part (any integer)
    int denominator;               // Denom must be non-zero
    inline int gcd(int a, int b) {return b == 0 ? a: gcd(b, a % b);};
    
};

#endif
