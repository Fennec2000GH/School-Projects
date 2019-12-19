#include <iostream> 
#include "item.h"

using namespace std;

// member functions

Item::Item()  : LIMIT(10)   //  <-- initialization of const member
{
    height = 0;
    weight = 0;
    cout << "The limit = " << SIZE << endl;
}

Item::Item(int h, int w) : LIMIT(h)  // <--- initialization of const
{
    height = h;
    weight = w;
    if (weight > LIMIT)
        weight = LIMIT;
}

void Item::Show() const
{
    cout << "Height = " << height << "\t\tWeight = " << weight << "\t\tLimit = " << LIMIT << '\n';
}

void Item::Set(int h, int w)
{
    height = h;
    weight = w;
    if (height > LIMIT)
        height = LIMIT;
    if (weight > LIMIT)
        weight = LIMIT;
}

int Item::GetHeight() const
{
    return height;
}

int Item::GetWeight() const
{
    return weight;
}
