/* Name: Caijun Qin
Date: 09/24/2018
Section: 6
Assignment: 3
Due Date: 10/01/2018
About this project:
This program is an automated order processor for the Krusty Krab. The customer
will be able to select any whole number quantities of each of four food options
listed in the menu. The customer will be able to see a receipt of the order at
the end.

Assumptions: User only enters real numbers.
All work below was performed by Caijun Qin */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/***FUNCTION DECLARATIONS***/
void menu();
double OrderTotal(int patty, int drink, int fries, int pizza);

int main(){
    /***VARIABLE DECLARATIONS***/
    //food choice number in the menu
    int menuChoice = 1;

    //number of each food ordered
    int patty = 0;
    int fries = 0;
    int drink = 0;
    int pizza = 0;

    //placeholder for number of menu items when one item is currently being ordered
    int numOrders = 0;

    /***WHAT ACTUALLY APPEARS ON THE SCREEN TO THE USER***/
    cout << "\n";
    cout << "Welcome to the Krusty Krab! \n\n";

    while(menuChoice != 0){
        //displays the menu
        menu();
        cout << "\n\n";

        //prompts for orders
        cout << "What would you like? (Enter 0 to finish order!):  ";
        cin >> menuChoice;

        //checks if input is on the menu
        if(menuChoice == 1 || menuChoice == 2 || menuChoice == 3 || menuChoice == 4){

        //takes the order
        switch(menuChoice){
            //number of krabby patties
            case 1:
                cout << "How many:  ";
                cin >> numOrders;
                //checks for nonnegative whole number
                while(numOrders != abs(numOrders) || numOrders != round(numOrders)){
                    if(numOrders != abs(numOrders)){
                        cout << "You can't order a negative amount of food! \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    } else if(numOrders != round(numOrders)){
                        cout << "You can only order whole numbers of food!  \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    }
                }
                patty += numOrders;
                numOrders = 0;
                cout << "\n\n";
                break;
            //number of barnacle fries
            case 2:
                cout << "How many:  ";
                cin >> numOrders;
                //checks for nonnegative whole number
                while(numOrders != abs(numOrders) || numOrders != round(numOrders)){
                    if(numOrders != abs(numOrders)){
                        cout << "You can't order a negative amount of food! \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    } else if(numOrders != round(numOrders)){
                        cout << "You can only order whole numbers of food!  \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    }
                }
                fries += numOrders;
                numOrders = 0;
                cout << "\n\n";
                break;
            //number of kelp shakes
            case 3:
                cout << "How many:  ";
                cin >> numOrders;
                //checks for nonnegative whole number
                while(numOrders != abs(numOrders) || numOrders != round(numOrders)){
                    if(numOrders != abs(numOrders)){
                        cout << "You can't order a negative amount of food! \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    } else if(numOrders != round(numOrders)){
                        cout << "You can only order whole numbers of food!  \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    }
                }
                drink += numOrders;
                numOrders = 0;
                cout << "\n\n";
                break;
            //number of krusty krab pizzas
            case 4:
                cout << "How many:  ";
                cin >> numOrders;
                //checks for nonnegative whole number
                while(numOrders != abs(numOrders) || numOrders != round(numOrders)){
                    if(numOrders != abs(numOrders)){
                        cout << "You can't order a negative amount of food! \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    } else if(numOrders != round(numOrders)){
                        cout << "You can only order whole numbers of food!  \n";
                        cout << "Try Again:  ";
                        cin >> numOrders;
                    }
                }
                pizza += numOrders;
                numOrders = 0;
                cout << "\n\n";
                break;
            //checks if order is complete
            case 0:
                break;
        }
    } else {
        cout << "That isn't on the menu! Try again. \n\n";
        break;
    }
    }

    //reviews what the customer has ordered under the condition that s/he
    //actually ordered at least one menu item
    double total = OrderTotal(patty, drink, fries, pizza);
    if(total > 0){
        cout << "\n\n";
        cout << "Your order: \n";
        //lists number of krabby patties ordered, if any
        if(patty == 1){
            cout << "1  krabby patty. \n";
        } else if(patty > 1){
            cout << patty << " krabby patties. \n";
        }

        //lists number of barnacle fries ordered, if any
        if(fries == 1){
            cout << "1 barnacle fries. \n";
        } else if(fries > 1){
            cout << fries << " barnacle fries. \n";
        }

        //lists number of kelp shakes ordered, if any
        if(drink == 1){
            cout << "1 kelp shake. \n";
        } else if(drink > 1){
            cout << fries << " kelp shakes. \n";
        }

        //lists number of krusty krab pizzas ordered, if any
        if(pizza == 1){
            cout << "1 krust krab pizza. \n";
        } else if(pizza > 1){
            cout << pizza << " krusty krab pizzas. \n";
        }
        cout << "\n";

        cout << fixed << showpoint << setprecision(2) <<"Your total is $" << total << "\n";
        cout << "Enjoy the food!" << "\n\n";
    } else if(total == 0){
        cout << "Guess you aren't hungry." << "\n\n";
    }

    return 0;
}

/***FUNCTION DEFINITIONS***/
void menu()
{
    cout << "----------- Menu -----------\n";
    cout << "1. \tKrabby Patty ...... $3.50\n";
    cout << "2. \tBarnicle Fries .... $1.50\n";
    cout << "3. \tKelp Shake ........ $1.00\n";
    cout << "4. \tKrusty Krab Pizza . $5.00\n";
}

double OrderTotal(int patty, int drink, int fries, int pizza)
{
    double total = patty * 3.50 + drink * 1.00 + fries * 1.50 + pizza * 5.00;
    return total;
}
