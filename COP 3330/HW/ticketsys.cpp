
/* Name: Caijun Qin
Date: 09/06/2018
Section: 6
Assignment: 1
Due Date: 09/12/2018
About this project:

This program serves as a price calculator to attend a
football game at Florida State University. The task is subdivided into
calculations of costs based the number of visitors from each of three age
brackets. The final cost includes these individual costs and the tax.
Assumptions: The user will only input whole integer values of 0 or greater.

All work below was performed by Caijun Qin */





#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    //set ticket prices per person based on age bracket
    const double adultPrice = 28.50;
    const double childPrice = 12.50;
    const double seniorPrice = 16.50;

    //the tax percentage in decimal form
    const double taxRate = 0.07;

    //number of people in each age bracket
    int numAdult = 0;
    int numChild = 0;
    int numSenior = 0;

    cout << "***FSU Football Ticket Calculator*** \n";
    cout << "Please enter the number of: \n";

    cout << "\t Adults \n";
    cout << "\t Children(up to age 9) \n";
    cout << "\t Seniors(55+) \n";

    //asks the user how many tickets by age bracket to purchase
    cout << "Adults -->";
    cin >> numAdult;
    cout << "\n";

    cout <<  "Children -->";
    cin >> numChild;
    cout << "\n";

    cout << "Seniors -->";
    cin >> numSenior;

    cout << "\n";

    cout << "----------------------------";

    cout << "\n";

    //defines variables for the pre-tax total, tax amount, and total with tax
    double totalPreTax = adultPrice*numAdult + childPrice*numChild + seniorPrice*numSenior;
    double taxAmount = taxRate*totalPreTax;
    double totalCost = totalPreTax + taxAmount;

    //prints out the pre-tax total, the tax amount, and total with tax
    cout << fixed << setprecision(2) << "TOTAL (before tax) = $" << totalPreTax << "\n";
    cout << fixed << setprecision(2) << "Tax = $" << taxAmount << "\n";
    cout << fixed << setprecision(2) << "TOTAL COST (after tax) = $" << totalCost << "\n";

    //thank you ending statement
    cout << "\n";
    cout << "Thanks for using the ticket system! \n";

    return 0;
}
