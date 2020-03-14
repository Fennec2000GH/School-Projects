
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

//gets left child index
int getLeftChildIndex(int parentIndex) {
    //edge case: invalid parent index
    if(parentIndex < 0) { throw out_of_range("Parent index cannot be negative!"); }
    return 2 * parentIndex + 1;
}

//gets right child index
int getRightChildIndex(int parentIndex) {
    //edge case: invalid parent index
    if(parentIndex < 0) { throw out_of_range("Parent index cannot be negative!"); }
    return 2 * parentIndex + 2;
}

//get parent index
int getParentIndex(int childIndex) {
    if(childIndex < 0) { throw out_of_range("Index index cannot be negative!"); }
    return (childIndex - 1) / 2;
}

//places root at correct node, assuming that the root is the only node breaking max heap property
//only considers the first n elements as part of max heap
// O(log n) time
void heapify(vector<int> &v, int rootIndex, int n) {
    //edge case: invalid index for root
    if(rootIndex < 0 || rootIndex >= n) { throw out_of_range("rootIndex is out of range!"); }

    //edge case: invalid length n
    if(n < 0 || n > v.size()) { throw out_of_range("Custom heap length is out of range!"); }

    int local_max_index = rootIndex; //index of node (parent, left child, or right child) having largest value among the three (3)
    int leftIndex = getLeftChildIndex(rootIndex); //index of left child of root
    int rightIndex = getRightChildIndex(rootIndex); //index of right child of root
    if(leftIndex < n && v[leftIndex] > v[local_max_index]) { local_max_index = leftIndex; }
    if(rightIndex < n && v[rightIndex] > v[local_max_index]) { local_max_index = rightIndex; }

    if(rootIndex != local_max_index) {
        swap(v[rootIndex], v[local_max_index]);
        heapify(v, local_max_index, n);

    }

}

//heapify considering all elements in vector
// O(log n) time
void heapify(vector<int> &v) { heapify(v, 0, v.size()); }

//creates max heap from any vector of ints in place
// O(n log n) time
void build_max_heap(vector<int> &v) {
    //edge case: empty vector
    if(v.empty()) { return; }

    for(int index = getParentIndex(v.size() - 1); index >= 0; index--) { heapify(v, index, v.size()); }
}

// best/average/worst case: O(n log n) time
void heap_sort(vector<int> &v) {
    //edge case: empty vector
    if(v.empty()) { return; }

    int insert_index = v.size() - 1; //index to insert next largest element
    build_max_heap(v); //convert v to a vector-based max heap in place
    while(insert_index > 0) {
        swap(v[0], v[insert_index]);
        heapify(v, 0, insert_index);
        --insert_index;
    }
}

/*
int main() {
    //testing heap functions with range [0, 9]
    vector<int> heap(10);
    iota(heap.begin(), heap.end(), 0);
    random_shuffle(heap.begin(), heap.end());
    cout << "before building max heap: { ";
    copy(heap.cbegin(), heap.cend(), ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;
    build_max_heap(heap);
    cout << "after building max heap: { ";
    copy(heap.cbegin(), heap.cend(), ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;

    heap_sort(heap);
    cout << "sorted: { ";
    copy(heap.cbegin(), heap.cend(), ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;

    return 0;
}
*/

//testing range [0, 99]
/*
int main() {
    //ascending
    vector<int> v(100);
    iota(v.begin(), v.end(), 0);

    cout << "v: { ";
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;

    chrono::time_point start = chrono::high_resolution_clock::now();
    heap_sort(v);
    chrono::time_point end = chrono::high_resolution_clock::now();
    cout << "ascending time taken (ns): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    //descending
    reverse(v.begin(), v.end());
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "descending time taken (ns): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    //random
    random_shuffle(v.begin(), v.end());
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "random time taken (ns): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    return 0;
}
*/


//inputs content from file into vector of ints
void setup(vector<int> &v, string filepath) {
    //edge case: empty vector
    if(v.empty()) { return; }

    //current element being inputted from file to vector
    string num_str;

    //input file stream to read from
    ifstream ifs(filepath.c_str(), fstream::in);

    //check for open file
    if(!ifs.is_open()) { throw out_of_range("File path does not exist!"); }
    for(int i = 0; i < v.size() && !ifs.eof(); i++) {
        getline(ifs, num_str, ' ');
        v[i] = stoi(num_str);
    }
    ifs.close();

}

int main() {
    //range [0, 9999] (10000 elements)
    //ascending
    vector<int> v(10000);
    setup(v, "ascending_10000.txt");
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    heap_sort(v);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_10000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;


    //random
    setup(v, "random_10000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 19999] (20000 elements)
    //ascending
    v.resize(20000, 0);
    setup(v, "ascending_20000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_20000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_20000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 49999] (50000 elements)
    //ascending
    v.resize(50000, 0);
    setup(v, "ascending_50000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_50000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_50000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 99999] (100000 elements)
    //ascending
    v.resize(100000, 0);
    setup(v, "ascending_100000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_100000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_100000.txt");
    start = chrono::high_resolution_clock::now();
    heap_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    return 0;
}





