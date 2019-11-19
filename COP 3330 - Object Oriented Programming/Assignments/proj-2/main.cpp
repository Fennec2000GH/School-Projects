#include <iostream>
#include "date.h"
#include "date.cpp"
using namespace std;

int main(){
    Date b(3, 9, 2019);
    Date g(2, 14, 2019);

    cout << g.GetMonth() << endl;
    cout << g.GetDay() << endl;
    cout << g.GetYear() << endl;
    cout << g.DayofWeek() << endl;
    cout << b.Compare(g) << endl;
    g.ShowByDay();
    g.ShowByMonth();

    cout << "\n\n\n\n";
    cout << b.GetMonth() << endl;
    cout << b.GetDay() << endl;
    cout << b.GetYear() << endl;
    cout << b.DayofWeek() << endl;
    b.ShowByDay();
    b.ShowByMonth();

    b.Set(3, 31, 2019);
    b.ShowByDay();
    b.Increment();
    b.ShowByDay();

    cout << "\n\n\n\n";
    b.Input();
    b.ShowByDay();
    b.ShowByMonth();

    return 0;
}
