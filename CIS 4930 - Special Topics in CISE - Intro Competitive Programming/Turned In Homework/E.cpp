
#include <iostream>
//#include <chrono>
#include <vector>
using namespace std;
 
int main(){
//    chrono::time_point start = chrono::high_resolution_clock::now();
    int n, m;
    cin >> n >> m;
 
    // temporary variables for re-use
    int temp;
    vector<short> dummy;
    vector<short>& v_ref = dummy;
 
    long long globalMax = LLONG_MIN, localMax = 0;
    vector <vector<short>> records(n + 1);  // keeps record of each distinct small array
//    vector<int> sums(n + 1);  // keeps sum of eall elements per each distinct small array
    short l;  // length of each small array
    for (int i = 1; i <= n; i++) {
        cin >> l;
        for (short j = 0; j < l; j++) {
            cin >> temp;
            records[i].push_back(temp);
        }
//        sums[i] = accumulate(records[i].cbegin(), records[i].cend(), 0);
    }
 
    //delete
//    int counter = 0;
    for (int i = 0; i < m; i++) {
        cin >> temp;
        v_ref = records[temp];
        for(short j = 0; j < v_ref.size(); j++) {
            localMax += v_ref[j];
//            cout << counter << ": (" << v_ref[j] << ", " << localMax << ", ";
            if (localMax > globalMax) { globalMax = localMax; }
            if(localMax < 0) { localMax = 0; }
 
            //delete
//            ++counter;
//            cout << globalMax << "), ";
        }
    }
 
//    cout << endl;
    cout << globalMax;
 
//    chrono::time_point end = chrono::high_resolution_clock::now();
//    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
 
    return 0;
}
