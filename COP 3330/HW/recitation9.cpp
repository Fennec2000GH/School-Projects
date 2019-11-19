#include <iostream>
#include <cmath>
using namespace std;

//FUNCTION DECLARATIONS
int SumDigits(int num);

int main(){
    int number = 0;
    cout << "Please enter a positive integer value:  ";
    cin >> number;
    cout << "The sum of the digits of " << number << " is " << SumDigits(number);
    cout << ". \n";

    return 0;
}

//FUNCTION DEFINITIONS

//calculates the sum of the digits of a positive integer
int SumDigits(int num){
    //variables
    int sum = 0;
    int size = 0;
    int mag = abs(num);
    int power = pow(10, size);
    int sizeCheck = mag % power;

    //finds the number of digits in the number
    do{
        size++;
        cout << size << "\n";
    } while(sizeCheck != mag);

    //adds each digit to the sum variable
    for(int counter = 0; counter < size; counter++){
        int nextDigit = floor(mag / pow(10, counter));
        sum += nextDigit % 10;
    }
    return sum;
}
