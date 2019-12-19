#include "Employee.h"

using namespace std;
//-------------------------EMPLOYEE-------------------------------------------------------

// The default constructor for class Employee solicits from the
// standard input (keyboard) values for the data common to all employees.
Employee::Employee() 
{
    cout << "\nType employee name, followed by <Enter>: ";
    cin.getline(name,30);

    cout << "\nType employee address, followed by <Enter>: ";
    cin.getline(address,80);

    cout << "\nType employee social security number, followed by <Enter>: ";
    cin.getline(socSecNumber,12);
};

// This constructor is used when any kind of employee object is created
// with supplied parameters.
Employee::Employee(char* n, char* a, char* ssn) 
{
    strcpy(name,n);
    strcpy(address,a);
    strcpy(socSecNumber,ssn);
};

Employee::~Employee() 
{
}


//------------------------TEMPORARY--------------------------------------------------------

// This is the default constructor for a Temporary employee.  It solicits
// values from the user for the hours worked and hourly rate.
Temporary::Temporary() 
{
    cout << "\nType number of hours worked, followed by <Enter>: ";
    cin >> hoursWorked;

    cout << "\nType hourly rate, followed by <Enter>: ";
    cin >> hourlyRate;
};

// This is the constructor for Temporaries declared with parameters.
// It invokes the Employee constructor to retrieve the basic employee data.
Temporary::Temporary(char* n, char* a, char* ssn, float hw, float hr):
        Employee(n, a, ssn) 
{
    hoursWorked=hw;
    hourlyRate=hr;
};

void Temporary::printCheck() 
{
    netPay=hoursWorked*hourlyRate;
    cout << "\n\n________________________________________________________";
    cout << "\n\nPAY TO THE ORDER OF: " << '\t' << name;
    cout << "\n\t\t\t" << address;
    cout << "\n\t\t\t" << socSecNumber << '\n';
    cout << "\nEMPLOYEE CLASS: Temporary";
    cout << "\n\nHOURS: " << hoursWorked;
    cout << "\nRATE: " << hourlyRate;
    cout << "\n\nTHE AMOUNT OF ***************************$" << netPay << '\n';
    cout << "\n\n________________________________________________________\n\n";
};


//---------------------PERMANENT-----------------------------------------------------------

// define static variable from class Permanent
float Permanent::benefitDeduction=100.00;

Permanent::Permanent() 
{
    // the value of static member benefitDeduction is supplied above
}

// The parameterized constructor for Permanent employees merely invokes
// the Employee constructor to fill in the rest of the employee data.

Permanent::Permanent(char* n, char* a, char* ssn): Employee(n, a, ssn) 
{
}


//--------------------HOURLY------------------------------------------------------------

// The default constructor for Hourly employees.  This solicits values
// for the number of hours worked and the hourly rate.
Hourly::Hourly() 
{
    cout << "\nType number of hours worked, followed by <Enter>: ";
    cin >> hoursWorked;

    cout << "\nType hourly rate, followed by <Enter>: ";
    cin >> hourlyRate;
};

// The parameterized constructor for Hourly employees.  This function
// first invokes the Permanent employee constructor (which, in turn,
// invokes the Employee constructor) to fill in the Permanent employee
// data, and then fills in the hourly information from its parameters.

Hourly::Hourly(char* n, char* a, char* ssn, float hw, float hr):
        Permanent(n, a, ssn) 
{
    hoursWorked=hw;
    hourlyRate=hr;
};

// Prints an Hourly employee's check by: calculating the net pay, calling
// the printCheck function for Permanent employees, and then printing
// the rest of the check.
void Hourly::printCheck() 
{
    netPay=(hoursWorked*hourlyRate)-benefitDeduction;
    cout << "\n\n________________________________________________________";
    cout << "\n\nPAY TO THE ORDER OF: " << '\t' << name;
    cout << "\n\t\t\t" << address;
    cout << "\n\t\t\t" << socSecNumber << '\n';
    cout << "\nEMPLOYEE CLASS: Hourly";
    cout << "\n\nBENEFITS DEDUCTION: " << benefitDeduction;
    cout << "\nHOURS: " << hoursWorked;
    cout << "\nRATE: " << hourlyRate;
    cout << "\n\nTHE AMOUNT OF ***************************$" << netPay << '\n';
    cout << "\n\n________________________________________________________\n\n";
};


//---------------SALARIED-----------------------------------------------------------------

// The default constructor for Salaried employees.  This function
// solicits and records a value for the weekly salary.  The other
// member data for salaried employees is solicited by the constructors
// for Permanent and Employee classes, which are invoked implicitly
Salaried::Salaried() 
{
    cout << "\nType weekly salary, followed by <Enter>: ";
    cin >> weeklyPay;
};

// To construct a Salaried employee using parameters, we
// explicitly invoke the Permanent constructor, and then fill in
// the value for weekly pay.
Salaried::Salaried(char* n, char* a, char* ssn, float wp):
        Permanent(n, a, ssn) 
{
    weeklyPay=wp;
};

// This function calculates the net pay, prints the "Permament" employee
// part of the check, and fills in the data for the Salaried employee.
void Salaried::printCheck() 
{
    netPay=weeklyPay-benefitDeduction;
    cout << "\n\n________________________________________________________";
    cout << "\n\nPAY TO THE ORDER OF: " << '\t' << name;
    cout << "\n\t\t\t" << address;
    cout << "\n\t\t\t" << socSecNumber << '\n';
    cout << "\nEMPLOYEE CLASS: Salaried";
    cout << "\n\nBENEFITS DEDUCTION: " << benefitDeduction;
    cout << "\nSALARY: " << weeklyPay;
    cout << "\n\nTHE AMOUNT OF ***************************$" << netPay << '\n';
    cout << "\n\n________________________________________________________\n\n";
};
