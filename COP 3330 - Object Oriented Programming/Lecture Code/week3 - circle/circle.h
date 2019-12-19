#ifndef __CIRCLE_H
#define __CIRCLE_H
 
class Circle
{
    public:
        Circle();
        Circle(double r);
        Circle(double, double, double=1);

        
        double getRadius();
        bool setRadius(double r);

        double getArea();
        double getDiameter();
        double getCircumference();

        void moveto_x(double obj_x);
        void moveto_y(double obj_y);
        void moveto(double obj_x, double obj_y);

        void print_info();
    
    private:
        double x, y;        // Coordinates of the center
        double radius;
        static const double pi = 3.14159;     
};
 
#endif
