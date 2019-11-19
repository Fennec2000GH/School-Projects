/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 2
Summary: This program aims to calculate and display the relations between any
real date and the components, including the month, day of the week, and year.
A calendar of the month that the date is in can also be displayed. The user can
adjust or reset the date any time.
*/

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    //CONSTRUCTORS
    Date();
    Date(int a, int b, int c);

    //ACCESSORS
    int GetMonth() const;
    int GetDay() const;
    int GetYear() const;

    //OTHER NON-MUTATORS
    int DayofWeek() const;
    int Compare(const Date & d) const;
    void ShowByDay() const;
    void ShowByMonth() const;

    //MUTATORS
    void Input();
    bool Set(int m, int d, int y);
    void Increment();

private:
    int month, day, year;

};

#endif
