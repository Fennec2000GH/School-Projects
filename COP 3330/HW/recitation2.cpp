#include <iostream>
using namespace std;

int main(){
    /***VARIABLE DECLARATIONS***/
    //asks y or n to order food
    char order;
    char foodSelection;

    //welcome message to customer
    cout << "Welcome to Cheeseburger Queen! \n";
    cout << "Would you like some food?" << "<y or n>:";
    cin >> order;
    cout << "\n";

    //processes customer responses
    if(order == 'Y' || order == 'y'){
        cout << "Hamburger or Cheeseburger?";
        cout << "<h or c>:";
        cin >> foodSelection;

        if(foodSelection == 'h'){
            cout << "Hamburger coming right up!";
        } else if (foodSelection == 'c'){
            cout << "Cheeseburger coming right up!";
        } else {
            cout << "Error! Invalid input.";
        }
    } else if (order == 'N' || order == 'n'){
        cout << "You're missing out!";
    } else {
        cout << "Error! Invalid input.";
    }

    //thank you statement ending
    cout << "\n";
    cout << "Thanks for stopping at Cheeseburger Queen! \n";


    return 0;
}
