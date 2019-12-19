#ifndef __TIMER_H
#define __TIMER_H
//-------------- timer.h --------------

// Declarations of classes Display and Timer

class Display
// A Display object stores and displays a single integer.
// That integer is always in the range 0 .. limit-1, where limit
// is also stored in the class.
{
public:
   Display(int lim);		// Initialize a new Display object.

   void increment();		// Add 1 to value.
   bool setValue(int val);	// Set the value.

   int getValue() const;	// Return the current value.
   int getLimit() const;	// Return the limit

   void show() const;		// Show the current value.

private:
   const int LIMIT;		    // largest possible value
   int value;			    // current value (0 .. limit - 1)
};

class Timer
// A Timer object consists of three Displays,one for hours, one for minutes, and one for seconds. When the timer is incremented and second becomes 60, second is reset to 0 and minute is incremented. Simlar rules hold for minutes and hours.
{
private:
   Display hours,		// three displays, one for hours,
           minutes,		// one for minutes
           seconds;     // and one for seconds
public:
   Timer();			            // Initialize a new Timer object 00:00:00
   Timer(int h, int m, int s);  // Initialize a new Timer object to h hours and m minutes
   void increment();	            	// Add 1 second to timer.
   bool set(int h, int m, int s);	    // Set Timer to h hours m minutes and s seconds

   void show() const;		    // Show hours minutes and seconds.

   Timer add(const Timer& t) const;  // add two Timer objects together
};

#endif
