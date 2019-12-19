#include <iostream>
#include <string>
#include "shape.h"

using namespace std;

// Shape class member functions

Shape::Shape()
{
   color = "black";
}

Shape::Shape(const string& c)
{
   SetColor(c);
}

void Shape::SetColor(string c)
{
    color = c;
}

string Shape::GetColor() const
{
    return color;
}

void Shape::Print() const
{
    cout << "\tcolor = " << color << '\n';
}

// No Area() imeplementation because this is pure virtual function


//////////////////////////////////////////////////

// Circle class member functions

Circle::Circle()
// note that this constructor calls the parent class' default constructor
{
   radius = 1;
   center_x = center_y = 0;
}

Circle::Circle(int cx, int cy, int r)
// note that this constructor calls the parent class' default constructor
{
   if (SetRadius(r) == false)	// try to set radius to r
	SetRadius(1);		        // else default to 1

   SetCenter(cx, cy);		    // set center to cx, cy
}

Circle::Circle(string c, int cx, int cy, int r) : Shape(c)
// note that this constructor calls the parent constructor with param: c
{
   if (SetRadius(r) == false)	// try to set radius to r
       SetRadius(1);		    // else default to 1

   SetCenter(cx, cy);		// set center to cx, cy
}

bool Circle::SetRadius(int r)
{
   if (r < 0)
	return false;		// negative radius illegal

   radius = r;			// else set radius to r
   return true;
}

void Circle::SetCenter(int x, int y)
// all x,y points are legal in cartesian plane
{
    center_x = x;  
    center_y = y;  
}

int Circle::GetRadius() const
{   return radius;  }

int Circle::GetCenterX() const
{   return center_x;   }

int Circle::GetCenterY() const
{   return center_y;   }

void Circle::Print() const
{
    cout << "Circle info:\n";
    Shape::Print();		// call parent to print the color

    cout << "\tcenter = " << "(" << center_x << "," << center_y
		<< ")\n";
    cout << "\tradius = " << radius << '\n';
}

double Circle::Area() const
{
   return (3.1416 * radius * radius);
}

//////////////////////////////////////////////////////////

// Rectangle member functions

Rectangle::Rectangle()
// note that this function calls the parent's default constructor,
//  but we're going to alter the color here to blue
{
   color = "blue";
   x = y = 0;			// origin is 0,0
   width = height = 10;		// default width and height to 10
}

Rectangle::Rectangle(int ox, int oy, int w, int h) : Shape("green")
// calls parent constructor with param, sets color to green
{
   SetOrigin(ox, oy);
   if (SetDimensions(w, h) == false)	// try to set to w by h
       SetDimensions(10,10);	    	// else default to 10x10
}

Rectangle::Rectangle(string c, int ox, int oy, int w, int h) : Shape(c)
// this constructor calls the parent constructor with param, 
//  sets color to c
{
   SetOrigin(ox, oy);
   if (SetDimensions(w, h) == false)	// try to set to w by h
       SetDimensions(10,10);	    	// else default to 10x10
}

   // mutators
void Rectangle::SetOrigin(int ox, int oy)
// any values are legal on the cartesian plane
{
   x = ox;
   y = oy;
}

bool Rectangle::SetDimensions(int w, int h)
// dimensions must be positive
{
   if (w <= 0)	return false;
   if (h <= 0)  return false;

   width = w;
   height = h;
   return true;
}

int Rectangle::GetX() const
{  return x;  }

int Rectangle::GetY() const
{  return y;  }

int Rectangle::GetWidth() const
{   return width;  }

int Rectangle::Height() const
{   return height;  }


void Rectangle::Print() const
{
    cout << "Rectangle info:\n";
    Shape::Print();			// call parent to print color

    cout << "\torigin = " << "(" << x << "," << y << ")\n";
    cout << "\tdimensions = " << width << " X " << height << '\n';
}

double Rectangle::Area() const
{
   return width * height;
}
