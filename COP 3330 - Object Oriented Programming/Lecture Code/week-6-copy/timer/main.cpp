#include <iostream>
#include <ctime>
#include "timer.h"

using namespace std;

void test1()
{
    Timer t1;
    t1.show();
    cout << endl;

    Timer t2(23, 59, 59);
    t2.show();
    cout << endl;

    t2.increment();
    t2.show();
    cout << endl;

    Timer t3(12, 23, 45);
    Timer t4(2, 30, 58);
    Timer t5 = t3.add(t4);
    t5.show();
    cout << endl;
}

void test2()
{
    Timer t;
    t.show();
    cout << endl;
    int a=clock()/CLOCKS_PER_SEC;//this gets the time in sec.
    while(true)
    {
       while(clock()/CLOCKS_PER_SEC-a<1);
       t.increment();
       t.show();
       cout << endl;

       a=clock()/CLOCKS_PER_SEC;
    } 
}

int main()
{
    // test1();
    test2();
}
