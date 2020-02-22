#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
using namespace std;

//SWAP 2 ENTRIES IN A VECTOR AT INDICES i AND j
template <class T>
void swap(vector<T> & v, const int & i, const int & j) {
    int temp = i;
    v.at(i) = v.at(j);
    v.at(j) = temp;
    return;
}

//MOVE INDEX i ENTRY IN A VECTOR TO BE THE INDEX j ENTRY
template <class T>
void move(vector<T> & v, const int & i, const int & j) {
    auto from = next(v.begin(), i);
    auto to = next(v.begin(), j);
    v.insert(to, v.at(i));
    v.erase(from);
    return;
}

//BUBBLE SORT
template <class T>
void bubbleSort(vector<T> & v) {
    for(unsigned int i = 0; i < v.size() / 2; i++)
        for(unsigned int j = 0; j < v.size() - 1; i++)
            if(v.at(j) < v.at(j + 1))
                swap(v, j, j + 1);
    return;
}

//INSERTION SORT
template <class T>
void insertionSort(vector<T> & v) {
    int wall = 1, current = 1;
    while(wall < v.size()) {
        while(v.at(current - 1) > v.at(current))
            --current;
        move(v, wall, current);
        ++wall;
        current = wall;
    }
    return;
}

//SELECTION SORT
template <class T>
void selectionSort(vector<T> & v) {
    int wall = v.size() - 1, max_dist;
    while(wall >= 0) {
        max_dist = distance(v.begin(), max_element(v.begin(), next(v.begin(), wall)));
        move(v, max_dist, wall + 1);
        --wall;
    }
    return;
}

//SHELL SORT
template <class T>
void shellSort(vector<T> & v) {
    int interval = v.size() / 2;
    while(interval > 0) {
        for(unsigned int i = 0; i < v.size() - interval; i++)
            if(v.at(i) > v.at(i + interval))
                swap(v, i, i + interval);
        interval = interval / 2;
    }
    return;
}

//QUICK SORT
template <class T>
vector<T> quickSort(vector<T> v) {
    int pivot, pivot_index;



}

//PIVOT ALGORITHMS FOR QUICKSORT
//FIND THE MEAN OF MIN AND MAX
template <class T>
T MMM(const vector<T> & v) {
    T min = *min_element(v.begin(), v.end());
    T max = *max_element(v.begin(), v.end());
    return (min + max) / 2; 

}

//HEAP SORT

//MERGE SORT
