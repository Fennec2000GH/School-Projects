
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

//best/average/worst case: O(n^2) time
void selection_sort(vector<int> &v) {
    //edge case: empty vector
    if(v.empty()) { return; } // O(1) time

    vector<int>::iterator min;
    for(auto it = v.begin(); it != v.end() - 1; it++) { // O(n) time
        min = min_element(it, v.end()); // O(n) time
        swap(*it, *min); // O(1)
    }
}

//test on range [0, 99]
/*
int main() {
    //ascending
    vector<int> v(100);
    iota(v.begin(), v.end(), 0);

    cout << "v: { ";
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(cout, ", "));
    cout << "} " << endl;

    chrono::time_point start = chrono::high_resolution_clock::now();
    selection_sort(v);
    chrono::time_point end = chrono::high_resolution_clock::now();
    cout << "ascending time taken (ns): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    //descending
    reverse(v.begin(), v.end());
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "descending time taken (ns): " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;

    //random
    random_shuffle(v.begin(), v.end());
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
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
    selection_sort(v);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_10000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;


    //random
    setup(v, "random_10000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 10000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 19999] (20000 elements)
    //ascending
    v.resize(20000, 0);
    setup(v, "ascending_20000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_20000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_20000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 20000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 49999] (50000 elements)
    //ascending
    v.resize(50000, 0);
    setup(v, "ascending_50000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_50000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_50000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 50000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //range [0, 99999] (100000 elements)
    //ascending
    v.resize(100000, 0);
    setup(v, "ascending_100000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (asc 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //descending
    setup(v, "descending_100000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (desc 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    //random
    setup(v, "random_100000.txt");
    start = chrono::high_resolution_clock::now();
    selection_sort(v);
    end = chrono::high_resolution_clock::now();
    cout << "time taken (random 100000): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl << endl;

    return 0;
}
