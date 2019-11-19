#include <iostream>
#include <iomanip>
#include <cmath>
#include "diamond.h"
using namespace std;

//FUNCTION DEFINITIONS
//constructor
Diamond::Diamond(int s, char b, char f)
{
    //size restrictions
    if(s < 1){
        size = 1;
    } else if(s > 39){
        size = 39;
    } else {
        size = s;
    }

    //character restrictions
    if(int (b) < 33 || int (b) > 126){
        border = '#';
    } else {
        border = b;
    }
    if(int (f) < 33 || int (f) > 126){
        fill = '*';
    } else {
        fill = f;
    }
}

//getters
int Diamond::GetSize()
{
    return size;
}

int Diamond::Perimeter()
{
    return (size * 4);
}

//diamond_area = 2 * triangle_area = 2 * (size^2 * sqrt(3) / 4)
double Diamond::Area()
{
    return (pow(size, 2) * pow(3, 0.5) / 2);
}

//increments size by 1
void Diamond::Grow()
{
    if(size + 1 <= 39){
        ++size;
    }
    return;
}

//decrements size by 1
void Diamond::Shrink()
{
    if(size - 1 >= 1){
        --size;
    }
    return;
}

//next two functions sets the border and fill characters
void Diamond::SetBorder(char b)
{
    if(int (b) >= 33 && int (b) <= 126){
        border = b;
    } else {
        border = '#';
    }
    return;
}

void Diamond::SetFill(char f){
    if(int (f) >= 33 && int (f) <= 126){
        fill = f;
    } else {
        fill = '*';
    }
    return;
}

//prints out the diamond
void Diamond::Draw()
{
    //index of the last row (bottom vertex of diamond)
    int last_row = size * 2 - 2;

    for(int row = 0; row <= last_row; row++){

        //prints spacing to left of diamond
        for(int left = 0; left < abs(size - (row + 1)); left++){
            cout << " ";
        }

        //prints first/top vertex
        if(row == 0){
            cout << border << endl;
        } else if(row < last_row){
            cout << border << " ";

            //fills up interior of diamond
            int interior = size - abs(size - row - 1) - 2;
            for(int counter = 0; counter < interior; counter++){
                cout << fill << " ";
            }
            cout << border << endl;
        }

        //the bottom vertex
        else if(row == last_row){
            cout << border << endl;
        }
    }
    return;
}

//prints out statistics, e.g. size, perimeter, area
void Diamond::Summary()
{
    cout << fixed << showpoint << setprecision(2);
    cout << "Size of diamond's side: " << size << " units. " << endl;
    cout << "Perimeter of diamond: " << Perimeter() << " units. " << endl;
    cout << "Area of diamond: " << Area() << " units. " << endl;
    cout << "Diamond looks like: " << endl;
    Draw();
    return;
}
