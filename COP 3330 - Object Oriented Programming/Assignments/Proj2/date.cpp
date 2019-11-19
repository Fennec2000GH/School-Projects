/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 2
Summary: This program aims to calculate and display the relations between any
real date and the components, including the month, day of the week, and year.
A calendar of the month that the date is in can also be displayed. The user can
adjust or reset the date any time.
*/

#include <iostream>
#include <algorithm> //needed to run in linprog, not necessary to run on my computer 
#include "date.h"
using namespace std;

//CONSTRUCTORS
Date::Date()
{
    month = 1;
    day = 1;
    year = 2019;
}

Date::Date(int m, int d, int y)
{
    //initializations of values
    month = m;
    day = d;
    year = y;

    //IF ANYTHING IS WRONG, DEFAULT CONSTRUCTOR TAKES OVER BELOW
    //months with even days - excludes February
    const int evenMonths[4] = {4, 6, 9, 11};

    //checks the month
    if(m < 1 || m > 12)
        *this = Date();

    //checks the day
    if(d < 1 || d > 31)
        *this = Date();

    //checks maximum for even-day months
    if(find(begin(evenMonths), end(evenMonths), m) != end(evenMonths) && d > 30)
        *this = Date();

    //checks for maximum for February
    if(m == 2)
    {
        bool leapYear = (y % 4 == 0);
        if(leapYear && d > 29)
            *this = Date();
        else if(leapYear == false && d > 28)
            *this = Date();
    }

    //checks the year
    if(y < 1900)
        *this = Date();
}

//MEMBER FUNCTIONS
//ACCESSORS
int Date::GetMonth() const
{
    return month;
}

int Date::GetDay() const
{
    return day;
}

int Date::GetYear() const
{
    return year;
}

//OTHER NON-MUTATORS
int Date::DayofWeek() const
{
    int d = day;
    int m = month;
    int y = year;

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int Date::Compare(const Date & d) const
{
    if(year > d.GetYear())
        return 1;
    else if(year < d.GetYear())
        return -1;
    else if(month > d.GetMonth())
        return 1;
    else if(month < d.GetMonth())
        return -1;
    else if(day > d.GetDay())
        return 1;
    else if(day < d.GetDay())
        return -1;
    else
        return 0;

}

void Date::ShowByDay() const
{
    //map of days of week for converstion between integer and string equivalents
    const string dow[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


    cout << dow[DayofWeek()] << " " << GetMonth() << "/" << GetDay();
    cout << "/" << GetYear() << endl;

}

void Date::ShowByMonth() const
{
    //assigns integer to days of week
    const string dow[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    //prints the header labels
    const string header[7] = {"Su\t", "Mo\t", "Tu\t", "We\t", "Th\t", "Fr\t", "Sa\t"};
    for(int counter = 0; counter < sizeof(header) / sizeof(string); ++counter)
    {
        cout << header[counter];
        if(counter == 6)
            cout << endl;
    }

    //sets up starting point for printing dates of the month
    Date temp(month, 1, year);
    for(int counter = 0; counter < temp.DayofWeek(); ++counter)
        cout << "  \t";

    //months with even/odd days - excludes February
    const int evenMonths[4] = {4, 6, 9, 11};
    const int oddMonths[7] = {1, 3, 5, 7, 8, 10, 12};

    //printing the date numbers
    int limit = 0; //number of days in that month
    if (month == 2)
    {
        bool leapYear = (year % 4 == 0);
        if(leapYear)
            limit = 29;
        else
            limit = 28;
    }
    else if(find(begin(oddMonths), end(oddMonths), month) != end(oddMonths))
        limit = 31;
    else if(find(begin(evenMonths), end(evenMonths), month) != end(evenMonths))
        limit = 30;
    for(int counter = 1; counter <= limit; ++counter)
    {
        if(counter < 10)
            cout << "0" + to_string(counter) + "\t";
        else
            cout << to_string(counter) + "\t";
        if((temp.DayofWeek() + counter - 1) % 7 == 6 || counter == limit)
            cout << endl;
    }
}


//MUTATORS
void Date::Input()
{
    //initial values of month, day, year
    const int unchanged[3] = {month, day, year};

    //accepts values from user input
    int m,d,y;
    char s1, s2;

    //checks if no mistakes on first try
    bool firstIteration = true;

    do{
        if(firstIteration == false)
        {
            *this = Date(unchanged[0], unchanged[1], unchanged[2]);
            cout << "Invalid date. Try again: ";
        }
        cin >> m >> s1 >> d >> s2 >> y;

        //sets the date and error checks using constructor
        *this = Date(m, d, y);
        firstIteration = false;
    } while(month != m || day != d || year != y);

    return;
}

bool Date::Set(int m, int d, int y)
{
    const int unchanged[3] = {month, day, year};
    *this = Date(m, d, y);
    if(month != m || day != d || year != y)
    {
        month = unchanged[0];
        day = unchanged[1];
        year = unchanged[2];
        return false;
    } else
        return true;
}

void Date::Increment()
{
    //months with even days - excludes February
    const int evenMonths[4] = {4, 6, 9, 11};

    //tests for extreme outlier values
    if(month == 12 && day == 31) //new year
    {
        month = 1;
        day = 1;
        ++year;
    }

    //February
    if(month == 2)
    {
        bool leapYear = (year % 4 == 0);
        if((leapYear && day == 29) || (leapYear == false && day == 28))
        {
            month = 3;
            day = 1;
        } else
            ++day;
    }

    //even months
    if(find(begin(evenMonths), end(evenMonths), month) != end(evenMonths) && month != 2)
        (day == 30)?(day = 1 && ++month):(++day);
    else if(month != 2)//the month has odd days
        (day == 31)?(day = 1 && ++month):(++day);
    return;
}
