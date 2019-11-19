#include <iostream>
#include <cmath>
using namespace std;
/***FUNCTION DECLARATIONS***/
double DegreesToRadians(double degrees);

int main(){
    /***VARIABLE DECLARATIONS***/
    double user_input, radians;

    cout << "Enter a value in degrees:  ";
    cin >> user_input;
    cout << "\n";
    radians = DegreesToRadians(user_input);
    cout << "sin(" << radians << ") = " << sin(radians) << "\n";


}
double DegreesToRadians(double degrees){
    return M_PI / 180 * degrees;
}
