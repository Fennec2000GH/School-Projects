
#include <iostream>
#include "deque.h"
using namespace std;


int main(){
    cop3530::deque<int> dq;
    dq.push_front(3);
    dq.push_front(2);
    dq.push_front(1);
    cout << dq.front() << endl;
    dq.pop_front();
    cout << dq.front() << endl;
    cout << "size = " << dq.size() << endl;
    cout << "empty = " << dq.empty() << endl;
    dq.pop_front();
    dq.pop_front();
    cout << "empty now = " << dq.empty() << endl;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    cout << dq.back() << endl;
    dq.pop_front();
    dq.pop_back();
    dq.pop_back();
    cout << "size 2nd time = " << dq.size() << endl;
    return 0;
}

