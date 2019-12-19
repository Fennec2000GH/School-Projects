//-------------- timer.cpp --------------

#include <iostream>       // for cout, cin
#include "timer.h"        // for Display and Timer declarations

using namespace std;

//-------------- Definition of member functions for class Display

Display::Display(int lim) : LIMIT(lim), value(0)
// Initialize a new Display object.
{
   //value = 0;
}

void Display::increment()
// Add 1 to value.  If incrementing makes value
// equal to limit, reset value to zero.
{
   value++;
   if (value == LIMIT)
      value = 0;
}

bool Display::setValue(int val)
// Set the value on the timer to "val", as long as it's valid returns true for success, and false for failure.  On failure, current display value is unchanged
{
   if (val < 0 || val >= LIMIT)
      return false;

   value = val;
   return true;			// success
}

int Display::getValue() const
// Return the current value.
{
   return value;
}

int Display::getLimit() const
// Return the limit for this display
{
   return LIMIT;
}

void Display::show() const
// Show the value of a Display.
{
   if (value < 10)          // Pad with a leading zero, if needed,
      cout << '0';

   cout << value;           // and in any case, display the value.
}

//-------------- Definition of member functions for class Timer

Timer::Timer() : hours(24), minutes(60), seconds(60)
// Initialize a new Timer object, setting hours limit to 24 and minutes/seconds limit to 60.
{
   // All the work is done by the two constructor calls in the header.
}

Timer::Timer(int h, int m, int s) : hours(24), minutes(60), seconds(60)
// initializes Timer value to h hours, m minutes, and s seconds, if h, m, and s valid.  If invalid data, defaults to 00:00:00
{
   if (set(h,m,s) == false)	
      set(0,0,0);
}

void Timer::increment()
// Add 1 second to timer.
{
    seconds.increment();
    if(seconds.getValue() == 0)
    {
        minutes.increment();
        if (minutes.getValue() == 0) 
            hours.increment();        
    }
}

bool Timer::set(int h, int m, int s)
// Set hours to h, minutes to m, and seconds to s, if they are valid.
// If h, m, and s represent an invalid timer setting, no change
// returns true for success, false for failure
{
   if (h < 0 || h >= hours.getLimit())
       return false;
   if (m < 0 || m >= minutes.getLimit())
       return false;
   if (s < 0 || s >= seconds.getLimit())
      return false;

   hours.setValue(h);
   minutes.setValue(m);
   seconds.setValue(s);
   return true;
}

void Timer::show() const
// Show the current timer's settings.
{
   hours.show();
   cout << ':';
   minutes.show();
   cout << ':';
   seconds.show();
}

Timer Timer::add(const Timer& t) const
{
    int spillover = 0;
    int s = seconds.getValue() + t.seconds.getValue();
    if (s >= seconds.getLimit())
    {
        s -= seconds.getLimit();
        spillover = 1;
    }

    // add minutes
    int m = minutes.getValue() + t.minutes.getValue() + spillover;	
    spillover = 0;
    if (m >= minutes.getLimit())		
    {					
        m = m - minutes.getLimit();
        spillover = 1;
    }

    // add hours
    int h = hours.getValue() + t.hours.getValue() + spillover;	  
    if (h >= hours.getLimit())		
        h = h - hours.getLimit();

   return Timer(h,m,s);		// build and return result object
}


