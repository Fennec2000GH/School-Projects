#include <iostream>
#include <list>
using namespace std;

int main(){
    //variables
    int N = 12;
    int sum = 0;
    list<int> Nlist = {};

    //asks for N
    cout << "Enter a positive integer N:  ";
    cin >> N;
    cout << "\n";

    //calcluations
    for(int counter = 1; counter < N + 1; counter++){
        Nlist.push_back(counter);
    }
    for(int number : Nlist){
        cout << number << "\n";
        sum += number;
    }

    cout << sum << "\n";


    return 0;
}
