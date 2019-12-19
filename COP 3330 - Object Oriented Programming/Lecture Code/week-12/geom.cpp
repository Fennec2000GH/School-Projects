#include <iostream>
#include "geom.h"

using namespace std;

// member function definitions for GeometricObject class

// default constructor
GeometricObject::GeometricObject() 
{
   cout << "Running GeometricObject default constructor\n";

   top = 0;
   left = 0;
   bottom = 0;
   right = 0;
}

// constructor with parameters

GeometricObject::GeometricObject(int t, int l, int b, int r) 
{
   cout << "Runnning GeometricObject constructor with parameters\n";

   top = t;
   left = l;
   bottom = b;
   right = r;
}


GeometricObject::~GeometricObject() 
{
   cout << "Runnning GeometricObject destructor\n";
}

// any part of the drawing task that can be done by the base class
// should be done here (i.e. part of draw that applies to ALL geometric objects)
void GeometricObject::draw() 
{
   cout << "Running GeometricObject::draw() function\n";
}

void GeometricObject::erase() 
{
   cout << "Running GeometricObject::Erase() function\n";
}

void GeometricObject::move(int h, int v) 
{
   cout << "Running GeometricObject::Move() function\n";
}


// function to re-calculate boundaries after a change
void GeometricObject::boundaries() 
{
   // recomputations that adjust top, left, right, bottom go here

   cout << "Running GeometricObject::Boundaries() function\n";
}

int GeometricObject::getTop() 
{
   return top;
}

int GeometricObject::getLeft() 
{
   return left;
}


// member functions for class Two_D_Object


Two_D_Object::Two_D_Object() 
{
   cout << "Running Two_D_Object default constructor\n";
   fillPattern = 0;		// default setting
}

Two_D_Object::Two_D_Object(int t, int l, int b, int r, int fill) : GeometricObject(t, l, b, r) 
{
   cout << "Running Two_D_Object constructor with parameters\n";
   fillPattern = fill;
}


Two_D_Object::~Two_D_Object() 
{
   cout << "Running Two_D_Object destructor\n";
}

void Two_D_Object::findCenter(int& row, int& col) 
{
   cout << "Running Two_D_Object::FindCenter()\n";
}


void Two_D_Object::draw() 
{
   cout << "Running Two_D_Object::draw()\n";

   // we can call upon the base class version of draw here
   GeometricObject::draw();
   
   // and do any processing specific to this class' data

   cout << "Finishing Two_D_Object::draw()\n";
}

double Two_D_Object::area() 
{
   cout << "Running Two_D_Object::Area()\n";
}

void Two_D_Object::boundaries() 
{
   cout << "Running Two_D_Object::Boundaries()\n";
}


// member functions for class Rectangle


// sets up default rectangle
Rectangle::Rectangle() 
{
   cout << "Running Rectangle default constructor\n";
   length = 1;
   width = 1;
}

// version with parameters
Rectangle::Rectangle(int t, int l, int b, int r, int f, int len,
             int wid) : Two_D_Object(t,l,b,r,f) 
{
   cout << "Running Rectangle constructor with parameters\n";
   length = len;
   width = wid;
}

Rectangle::~Rectangle() 
{
   cout << "Running Rectangle destructor\n";
}

void Rectangle::findCenter(int& row, int& col) 
{
   cout << "Running Rectangle::FindCenter()\n";
   
   // we can invoke the Two_D_Object version
   Two_D_Object::findCenter(row, col);

   cout << "Leaving Rectangle::FindCenter()\n";
}

void Rectangle::draw() 
{
   cout << "Running Rectangle::draw()\n";

   Two_D_Object::draw();	// do any pre-processing

   // actual drawing of the rectangle goes here (w/ length, width)

   cout << "Finishing Rectangle::draw()\n";
}

double Rectangle::area()
{
   cout << "Running Rectangle::Area()\n";
   return length*width;
}

int Rectangle::perimeter() 
{
   cout << "Running Rectangle::Perimeter()\n";
   return (2*length + 2*width);
}


// member functions for class Circle

Circle::Circle() 
{
   radius = 1;
   center_x = 0;
   center_y = 0;
}


Circle::Circle(int t, int l, int b, int r, int f, int cx, int cy, int rad) : Two_D_Object(t,l,b,r,f) 
{
   center_x = cx;
   center_y = cy;
   radius = rad;
}

Circle::~Circle() 
{
   cout << "Running Circle destructor\n";
}
    
void Circle::findCenter(int& row, int& col) 
{
    row = center_x;
    col = center_y;
}

void Circle::draw() 
{

}

double Circle::area() 
{
    return PI*radius*radius;
}

double Circle::circumference()
{
    return PI*2*radius;
}

