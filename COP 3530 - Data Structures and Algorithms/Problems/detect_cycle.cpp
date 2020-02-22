// Given a undirected graph, the task is to complete the method isCyclic() to detect if there is a cycle in the undirected graph or not.
//
// Input:
// The first line of the input contains an integer 'T' denoting the number of test cases. Then 'T' testcases follow. Each testcase consists of two lines.
// Description of testcases are as follows: The First line of each testcase contains two integers 'N' and 'M' which denotes the no of vertices and no of edges respectively.
// The Second line of each test case contains 'M'  space separated pairs u and v denoting that there is a bidirectional  edge from u to v .
//
// Output:
// The method should return 1 if there is a cycle else it should return 0.
//
// User task:
// Since this is a functional problem you don't have to worry about input, you just have to complete the function isCyclic.
//
// Constraints:
// 1 <= T <= 100
// 1 <= N,M <= 100
// 0 <= u,v <=  N-1

#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
using namespace std;

//FUNCTION DECLARATIONS
int isCyclicU(const vector<int> & v);

int main() {
    //loads the file
    string file = "detect_cycle.txt";
    fstream in;
    in.open(file.c_str(), ios::in);
    if(in.is_open() == false){
        cerr << "Error!" << endl;
        return 1;
    }
    int n;

    //reads in # of test cases
    in >> n;
    in.ignore();
    cout << n << endl;
    if(n < 1)
        cout << 0 << endl;

    //record of boolean values (0s and 1s) of isCyclicU function
    //in the same order as entries in vector v
    for(unsigned int i = 0; i < n; i++){
        //importing metadata
        int N, M;
        in >> N >> M;
        in.ignore();

        //checcking early for
        if(N < 3 || M < 3)
            return 0;

        vector<int> v;
        for(unsigned int i = 0; i < M * 2; i++)
            in >> v.at(i);
        in.ignore();

        for(auto & item : v)
            cout << item << " ";
        cout << endl;

        isCyclicU(v);

    }

    return 0;
}

//FUNCTION DEFINITIONS
int isCyclicU(const vector<int> & v) {
    int numEdges = v.size() / 2, numVertices;

    //set up
    struct Neighborhood {
        vector<pair<int, Neighborhood*>> neighbors;
    };

    vector<pair<int, int> > edges(numEdges);
    for(unsigned int i = 0; i < numEdges * 2; i++) {
        if(i % 2 == 0)
            edges.at(i / 2).first = v.at(i);
        else
            edges.at(i / 2).second = v.at(i);
    }

    for(auto & e : edges)
        cout << e.first << " " << e.second << " ";
    cout << endl;

    //creating a record of the vertices
    set<pair<int, Neighborhood*> > vertices;
    for(auto & e : edges){
        if(vertices.find(pair<int, Neighborhood*>(e.first, nullptr)) == vertices.end())
            vertices.insert({e.first, nullptr});
        if(vertices.find(pair<int, Neighborhood*>(e.second, nullptr)) == vertices.end())
            vertices.insert({e.second, nullptr});
    }

    for(auto & v : vertices)
        cout << v.first << " ";
    cout << endl;

    return 0;
}
