#include <iostream>
#include <vector>
using namespace std;

//LINEAR SEARCH
template <typename T>
int linearSearch(const vector<T> & v, int l, int r, const T & item) {
    for(unsigned int i = l; l <= r; i++)
        if(v.at(i) == item)
            return i;

    return -1;
}

//BINARY SEARCH (assumes that the vector is pre-sorted)
template <typename T>
int binarySeatch(const vector<T> & v, int l, int r, const T & item) {

    int mid = l + ((r - l) / 2);

    if(v.at(mid) == item)
        return mid;
    else if(r - l == 1)
        return -1;
    else if(v.at(mid) < item)
        binarySeatch(v, mid, r, item);
    else if(v.at(mid) > item)
        binarySeatch(v, l, mid, item);

}
