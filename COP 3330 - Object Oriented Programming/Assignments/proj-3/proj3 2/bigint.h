/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 3
Summary: This program aims to store nonnegative whole numbers
with as many as 45 digits. This serves to surmount the 32-bit
size constraint of int.
*/
#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>
using namespace std;

class bigint
{
public:
    //CONSTRUCTORS
    bigint();
    bigint(int x0, int x1 = 0, int x2 = 0, int x3 = 0, int x4 = 0);

    //OVERLOADED OPERATORS
    friend istream & operator >> (istream & input, bigint & obj);
    friend ostream & operator << (ostream & output, const bigint & obj);
    friend bigint operator + (const bigint & obj1, const bigint & obj2);
    friend bigint operator - (const bigint & obj1, const bigint & obj2);
    friend bool operator < (const bigint & obj1, const bigint & obj2);
    friend bool operator > (const bigint & obj1, const bigint & obj2);
    friend bool operator <= (const bigint & obj1, const bigint & obj2);
    friend bool operator >=(const bigint & obj1, const bigint & obj2);
    friend bool operator == (const bigint & obj1, const bigint & obj2);
    friend bool operator != (const bigint & obj1, const bigint & obj2);

private:
    int v[5];

};

#endif
