#include <iostream>
#include "geom.h"

using namespace std;

int main() {

   cout << "\n Declaring r \n\n";
   Rectangle r;

   cout << endl;

   cout << "\n Declaring r1 (with parameters) \n\n";
   Rectangle r1(1,2,3,4,5,6,7);
   cout << endl;
   r.draw();
    
   cout << endl;

   cout << "\n Declaring a circle \n\n";
   Circle c;
   cout << "area = " << c.area() << endl;
   cout << "circumference = " << c.circumference() << endl;
   cout << endl;

   return 0;

}
