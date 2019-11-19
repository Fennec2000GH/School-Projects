/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 3
Summary: This program aims to store nonnegative whole numbers
with as many as 45 digits. This serves to surmount the 32-bit
size constraint of int.
*/
#include <iostream>
#include <iomanip>
#include "bigint.h"
using namespace std;

//CONSTRUCTORS
bigint::bigint(){for(int & i : v){i = 0;}}
bigint::bigint(int x0, int x1, int x2, int x3, int x4){v[0] = x0; v[1] = x1; v[2] = x2; v[3] = x3; v[4] = x4;}

//OVERLOADED OPERATORS
istream & operator >> (istream & in, bigint & obj)
{
    string allDigits;                                                                          //stores the whole number as a string
    getline(in, allDigits, '\n');
    for(int i = 0; i < int(allDigits.length() / 2); ++i)                                       //reverses the order of allDigits
    {
        int temp = allDigits[i];
        allDigits[i] = allDigits[(allDigits.length() - 1) - i];
        allDigits[(allDigits.length() - 1) - i] = temp;
    }
    for(int i = 0; i < 5; ++i)
    {
        if(i * 9 > allDigits.length() - 1){break;}                                             //allDigits.length() - 1 is the final index of the number in string format
        string sub = allDigits.substr(i * 9, 9);                                               //reverses each 9-digit chunk separately to face the right direction in array v
        for(int s = 0; s < int(sub.length() / 2); ++s)
        {
            int temp = sub[s];
            sub[s] = sub[(sub.length() - 1) - s];
            sub[(sub.length() - 1) - s] = temp;
        }
        obj.v[i] = stoi(sub);
    }
    allDigits.clear();
    return in;
}

ostream & operator << (ostream & out, const bigint & obj)
{
    bool allZero = true;                                                                       //checks if the number is zero (0)
    for(int i : obj.v){if(i != 0){allZero = false;}}
    if(allZero != false){out << 0;}                                                            //prints out 0 if all elements of v are 0
    else
    {
        int startIndex = 0;                                                                    //largest index of v that is nonzero
        for(int i = 4; i >= 0; --i){if(obj.v[i] != 0){startIndex = i; break;}}
        for(int i = startIndex; i >= 0; --i)
        {
            if(i < startIndex){out << setw(9) << setfill('0');}
            out << obj.v[i];
        }
    }
    return out;
}

bigint operator + (const bigint & obj1, const bigint & obj2)
{
    bigint obj3 = {0, 0, 0, 0, 0};
    for(int i = 0; i < 5; ++i)                                                                //sums corresponding elements of obj.v and obj2.v
    {
        string sum = to_string(obj1.v[i] + obj2.v[i] + obj3.v[i]);
        if(sum.length() > 9)                                                                  //deals with carry over if the sum of two numbers has 10 digits
        {
            if(i != 4){obj3.v[i + 1] += 1;}
            obj3.v[i] = stoi(sum.substr(1));
        } else {obj3.v[i] += (obj1.v[i] + obj2.v[i]);}
    }
    return obj3;
}

bigint operator - (const bigint & obj1, const bigint & obj2)
{
    bigint obj3 = {0, 0, 0, 0, 0};
    if(obj1 > obj2)                                                                           //difference is positive only if obj1 > obj2
    {
        for(int i = 0; i < 5; ++i)                                                            //computes individual difference for each element of v
        {
            int diff = obj1.v[i] - obj2.v[i] + obj3.v[i];
            if(diff < 0){obj3.v[i] = diff + 1000000000; obj3.v[i + 1] -= 1;}
            else {obj3.v[i] = diff;}
        }
    }
    return obj3;
}

bool operator < (const bigint & obj1, const bigint & obj2)
{
    bool b = false;
    for(int i = 0; i != 5; ++i){if(obj1.v[i] != obj2.v[i]){b = obj1.v[i] < obj2.v[i]?true:false;}}
    return b;
}

bool operator > (const bigint & obj1, const bigint & obj2){return (!(obj1 < obj2) && !(obj1 == obj2));}

bool operator <= (const bigint & obj1, const bigint & obj2){return ((obj1 < obj2) || (obj1 == obj2));}

bool operator >= (const bigint & obj1, const bigint & obj2){return ((obj1 > obj2) || (obj1 == obj2));}

bool operator == (const bigint & obj1, const bigint & obj2)
{
    bool b = true;
    for(int i = 0; i != 5; ++i){if(obj1.v[i] != obj2.v[i]){b = false;}}
    return b;
}

bool operator != (const bigint & obj1, const bigint & obj2){return (!(obj1 == obj2));}
