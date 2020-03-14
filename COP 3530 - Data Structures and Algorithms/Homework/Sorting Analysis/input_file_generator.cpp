#include <chrono>
#include <random>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
    //mersenne  twister random generation function for randomized shuffling
    random_device rd;
    mt19937_64 generator(rd());

    //SIZE: 10000
    //ascending
    vector<int> v(10000);
    iota(v.begin(), v.end(), 0);
    ofstream os("ascending_10000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //descending
    reverse(v.begin(), v.end());
    os.open("descending_10000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //random
    shuffle(v.begin(), v.end(), generator);
    os.open("random_10000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //SIZE: 20000
    //ascending
    v.resize(20000, 0);
    iota(v.begin(), v.end(), 0);
    os.open("ascending_20000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //descending
    reverse(v.begin(), v.end());
    os.open("descending_20000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //random
    shuffle(v.begin(), v.end(), generator);
    os.open("random_20000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //SIZE: 50000
    //ascending
    v.resize(50000);
    iota(v.begin(), v.end(), 0);
    os.open("ascending_50000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //descending
    reverse(v.begin(), v.end());
    os.open("descending_50000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //random
    shuffle(v.begin(), v.end(), generator);
    os.open("random_50000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //SIZE: 100000
    //ascending
    v.resize(100000);
    iota(v.begin(), v.end(), 0);
    os.open("ascending_100000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //descending
    reverse(v.begin(), v.end());
    os.open("descending_100000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();

    //random
    shuffle(v.begin(), v.end(), generator);
    os.open("random_100000.txt", fstream::out);
    copy(v.cbegin(), v.cend(), ostream_iterator<int>(os, " "));
    os.close();
    v.clear();

    return 0;
}
