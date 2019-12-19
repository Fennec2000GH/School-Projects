#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

void PrintAndArea(int ident, const Shape& s)
// call the print function and area functino of any shape
//  child object can be passed into parent function
//
// NOTE that the calling variable is a Shape variable
// Note that now the base class fucntions ARE virtual
{
   cout << "\nShape " << ident << "  ";
   s.Print();
   cout << "\nShape " << ident << "'s area is: " << s.Area() << '\n';
}

int main()
{
   Circle c1("magenta", 18, 21, 53);
   Rectangle r1("tan", 2, 4, 7, 9);

   cout << "c1 ";
   c1.Print();
   cout << "\nr1 ";
   r1.Print();
   cout << "\nc1's area is: " << c1.Area();
   cout << "\nr1's area is: " << r1.Area() << '\n';
   cout << endl;
  
   // now we'll do the heterogeneous list

   Shape* sList[10];		    // array of 10 shapes

   sList[0] = new Circle;		// default constructor
   sList[1] = new Circle(10, 20, 100);
   sList[2] = new Circle("red", 4, -1, 30);
   sList[3] = new Rectangle;    // default constructor
   sList[4] = new Rectangle(5, 10, 100, 200);		
   sList[5] = new Rectangle("mauve", -5, -20, 50, 40);
   sList[6] = new Circle(-5, -10, 41);
   sList[7] = new Rectangle("white", 1, 2, 6, 7);
   sList[8] = new Circle;
   sList[9] = new Rectangle(2, 2, 9, 9);


   for (int i = 0; i < 10; i++)
   {
       cout << "Shape " << i << "  ";
       sList[i]->Print();
       cout << '\n';
   }

   cout << "\n**Now using PrintAndArea() funtion**\n";

   // Now we attempt to print and compute area of each shape, 
   //  by calling the function at the top of this file
   for (int i = 0; i < 10; i++)
       PrintAndArea(i, *sList[i]);	// pass in target of each pointer

   return 0;
}
