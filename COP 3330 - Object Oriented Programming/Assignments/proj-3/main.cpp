#include "bigint.h"
#include "bigint.cpp"
#include <string>

int main()
{
    bigint a;
    bigint b;
    bigint X = {6};
    cout << a << " " << b << " " << X << endl;
    cout << (a == b) << " " << (a > b) << " " << (a <= b && a <= X) << endl;
    cout << endl << endl;

    bigint c = {8888, 6666, 4444, 2222};
    bigint d = {8888, 8888, 8888, 4444};
    cout << c << endl;
    cout << d << endl;
    cout << (c >= d) << endl;
    cout << "c + d = " << endl << c + d << endl;
    cout << endl << endl;

    cout << d << endl;
    cout << c << endl;
    cout << "d - c = " << endl;
    cout << d - c << endl;
    cout << endl << endl;

    cout << c << endl;
    cout << d << endl;
    cout << "c - d = " << endl;
    cout << c - d << endl;
    cout << endl << endl;

    bigint x1(123456789, 111, 111, 111, 111);
    cout << x1 << endl;
    cout << endl << endl;

    bigint e = {999999999, 999999999, 999999999, 999999999, 99999999};
    bigint f = {999999999, 999999999, 999999999, 999999999, 899999999};
    bigint g = {999999999, 999999999, 999999999, 999999999, 999999999};
    cout << e << endl << f << endl << g << endl;
    cout << endl << endl;

    cout << "e + f = " << endl;
    cout << e + f << endl;
    cout << endl << endl;

    cout << "g + g = " << endl;
    cout << g + g << endl;
    cout << endl << endl;

    cout << "g - e = " << endl;
    cout << g - e << endl;

    string rat = "rat";
    cout << rat.substr(2, 6) << endl;

    string num = "0123456789";
    cout << stoi(num) << endl;
    cout << stoi(num.substr(6)) << endl;
    cout << stoi(num.substr(2, 12)) << endl;
    cout << stoi(num.substr(0)) << endl; 


    return 0;
}
