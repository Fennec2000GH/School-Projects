// Main program to test class Employee and its derived classes.

#include <iostream>		        // for cin, cout
#include "EmployeeList.h"		// for EmployeeList class
#include "Utility.h"	 	    // for SetNumeric, WaitForUser, Terminate

using namespace std;

int main() 
{
    // Create an array to hold (pointers to) our Employees
    EmployeeList employeeList;

    /*

    // samples of static objects being attached to the array
    cout << "\n\nCreating a temporary employee pay record . . .";
    Temporary t("Clipper Decker", "Clinton, NY", "123456789", 40.0, 5.25);
    employeeList.add(&t);

    cout << "\n\nCreating an hourly employee pay record . . .";
    Hourly h("Sparky Hirshfield", "Deansboro, NY", "234567890", 30.5, 8.50);
    employeeList.add(&h);

    cout << "\n\nCreating a salaried employee pay record . . .";
    Salaried s("Fenton Sugarman", "Boston, MA", "345678901", 500.00);
    employeeList.add(&s);
    waitForUser();
    // Everything will work fine until the destructor to EmployeeList is called
    // By passing statically allocated addresses a call to delete during the
    // constructor will result in an error as the addresses stored in the EmployeeList
    // array were not dynamically allocated.

    */

    // examples of dynamic objects, attached to the array

    cout << "\n\nEnter data for a temporary employee pay record . . .";
    Temporary* tEmp = new Temporary("Zhao","FSU","111-11-1111",45.0,15.45);
    employeeList.add(tEmp);

    cout << "\n\nEnter data for an hourly employee pay record . . .";
    employeeList.addEmployee('H');

    cout << "\n\nEnter data for a salaried employee pay record . . .";
    if (cin.peek() == '\n') 
    {
        cin.get();
    }
    employeeList.addEmployee('S');

    // Set format flags for numeric output
    setNumeric();

    // Now, print all checks, letting C++ determine the
    // appropriate version of PrintCheck depending upon
    // the type of the Employee
    cout << employeeList;
    waitForUser();

    terminateProgram();
    cout<< '\n';

    return 0;
};
