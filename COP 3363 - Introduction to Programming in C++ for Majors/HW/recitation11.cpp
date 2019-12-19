#include <iostream>
using namespace std;

int main(){
    int evens[10];
    int favorites[10];

    for(int counter = 0; counter < 10; counter++){
        evens[counter] = (counter + 1) * 2;
    }

    cout << "Enter favorites:  ";
    for(int counter = 0; counter < 10; counter++){
        cin >> favorites[counter];
    }

    for(int counter = 0; counter < 10; counter++){
        cout << evens[counter] << " ";
    }
    cout << "\n";

    for(int counter = 0; counter < 10; counter++){
        if(counter % 2 == 0){
            cout << favorites[counter] << favorites[counter + 1] << "\n";
        }
    }

    return 0;
}
