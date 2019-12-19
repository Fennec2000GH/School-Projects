#ifndef __SHAPE_H
#define __SHAPE_H

#include <string>
using namespace std;

/*
 * Class Shape is a base class, which will store just a color setting.
 *  We will derive a few subtypes frome Shape
 *
*/

class Shape
{
public:
   Shape();		            // default constructor - default color is black
   Shape(string c);	        // constructor taking in color (with the type string) as param
   void SetColor(string c);	// set the color
   string GetColor() const;	// accessor

   virtual void Print() const;		        // "Print" the shape.
   virtual double Area() const = 0;	        // pure virtual (no def)

protected:
   string color;	        // every shape can be set to a color, regardles of what subtype of shape it is
};


/* class Circle is a subtype of class Shape. Circle adds in a radius and center */

class Circle : public Shape
{
public:
   Circle();		                            // default constructor -- sets to unit circle
   Circle(int cx, int cy, int r);	            // pass in center points and radius
   Circle(string c, int cx, int cy, int r);     // pass in color, center, radius

   // mutators
   bool SetRadius(int r);
   void SetCenter(int x, int y);

   // accessors
   int GetRadius() const;
   int GetCenterX() const;
   int GetCenterY() const;

   void Print() const;			// "Print" the circle.
   double Area() const;			// compute and return the area

private:
   int radius;
   int center_x;
   int center_y;
};


/*   class Rectangle is a subtype of class Shape
 *   Rectangle adds in an origin (x,y) coordinates
 *   and a length and width
 */

class Rectangle : public Shape
{
public:
   Rectangle();		// default to (0,0) origin, (10x10 for length/width)

   // this constructor takes origin and dimensions as params
   Rectangle(int ox, int oy, int w, int h);

   // this constructor takes color, origin, and dimensions
   Rectangle(string c, int ox, int oy, int w, int h);

   // mutators
   void SetOrigin(int ox, int oy);
   bool SetDimensions(int w, int h);

   // accessors
   int GetX() const;
   int GetY() const;
   int GetWidth() const;   
   int Height() const;   


   void Print() const;		// "print" the rectangle
   double Area() const;		// compute and return the area

private:
   int x, y;		// origin -- upper left of rectangle
   int width, height;	// width and height of rectangle
};

#endif
