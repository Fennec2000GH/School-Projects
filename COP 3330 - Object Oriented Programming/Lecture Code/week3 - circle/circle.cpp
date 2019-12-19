#include <iostream>
#include "circle.h"

using namespace std;
 
Circle::Circle()
{
    x = 0;
    y = 0;
    radius = 1.0;   
}

Circle::Circle(double r)
{
    x = 0;
    y = 0;
    radius = r;
}

Circle::Circle(double x_coor, double y_coor, double r)
{
    x = x_coor;
    y = y_coor;
    radius = r;
}
            
double Circle::getRadius()
{
    return radius;   
}

bool Circle::setRadius(double r)
{ 
    if (r < 0)
        return false;

    radius = r;  
    return true;
}

             
double Circle::getArea()
{
    return pi * radius * radius;
}
             
double Circle::getDiameter()
{
    return radius * 2;
}
             
double Circle::getCircumference()
{
    return 2 * pi * radius;  
}

void Circle::moveto_x(double obj_x)
{
    x = obj_x;
}

void Circle::moveto_y(double obj_y)
{
    y = obj_y;
}

void Circle::moveto(double obj_x, double obj_y)
{
    x = obj_x;
    y = obj_y;
}


void Circle::print_info()
{
    cout << "Circle Info: " << "x-coordinate = " << x << "; y-coordinate = " << y << "; radius = " << radius << "." << endl;
    cout << "Diameter = " << getDiameter() << endl;
    cout << "Circumference = " << getCircumference() << endl;
    cout << "Area = " << getArea() << endl;
}
