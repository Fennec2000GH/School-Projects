#ifndef __GEOM_H
#define __GEOM_H

#define PI 3.1416

class GeometricObject 
{
public:
   GeometricObject();
   GeometricObject(int t, int l, int b, int r);
   ~GeometricObject();

   void draw();
   void erase();
   void move(int h, int v);
   void boundaries();
   int getTop();
   int getLeft();

protected:      //Accessed by this and derived classes
   int top,
       left,
       bottom,
       right;

private:
                // any private members are declared here
                // and are inaccessible outside this class
};

// derived from GeometricObject
class Two_D_Object : public GeometricObject 
{
public:
   Two_D_Object();
   Two_D_Object(int t, int l, int b, int r, int fill);
   ~Two_D_Object();

   void findCenter(int&, int&);
   void draw();
   void boundaries();
   double area();

protected:

   int fillPattern;
};

class Rectangle : public Two_D_Object 
{
public:
   Rectangle();
   Rectangle(int t, int l, int b, int r, int f, int len, int wid);
   ~Rectangle();

   void findCenter(int&, int&);
   void draw();
   double area();
   int perimeter();

private:
   int length, width;
};

class Circle : public Two_D_Object 
{
public:
   Circle();
   Circle(int t, int l, int b, int r, int f, int cx, int cy, int rad);
   ~Circle();

   void findCenter(int&, int&);
   void draw();
   double area();
   double circumference();

private:
   int center_x;
   int center_y;
   int radius;
};

#endif
