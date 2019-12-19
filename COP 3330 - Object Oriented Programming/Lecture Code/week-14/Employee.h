// ----------EMPLOYEE.H----------
// Declarations for class Employee
// Class Employee has two directly derived subclasses,
// Temporary (employees who work on an hourly basis and get no company benefits)
// and Permanent (employees all of whom have a benefit deduction)
// Permanent are further subdivided into Hourly and Salaried classes.

// The ifndef ensures that the Employee class is only declared once during compilation,
// even thought the file being included multiple times in multiple files

#ifndef COP3330_EMPLOYEE_H
#define COP3330_EMPLOYEE_H

#include <iostream>      // for cin, cout
#include <cstring>       // for strcmp

using namespace std;

class Employee 
{
public:
    virtual ~Employee();                    // Needs to provide a virtual destructor
    virtual void printCheck()=0;		    // a pure virtual function

protected:                              	// accessible to derived classes only
    float netPay;
    Employee();                             // default constructor, users cannot explicitly create an employee
    Employee(char* n, char* a, char* ssn);  // constructor with parameters
    char name[30];
    char address[80];
    char socSecNumber[12];
};

//---------------------------------------------
class Temporary : public Employee
{
public:                                 // Public so that they can be invoked from main()
    Temporary();
    Temporary(char* n, char* a, char* ssn, float hw, float hr);
    void printCheck();

private:                               //  Temporary is an Employee with ...
    float hoursWorked;                 //  a number of hours worked, and
    float hourlyRate;                  //  an hourly rate of pay
};

//---------------------------------------------
class Permanent : public Employee 
{
// This is public so that it can be initialized externally
public:                              // Permanent is an Employee with ...
    static float benefitDeduction;   // a fixed deduction for benefits

// All is protected so that it is only accessible to derived classes
protected:
    Permanent();
    Permanent(char* n, char* a, char* ssn);
    virtual void printCheck() = 0;			// redeclared as pure virtual
};

//---------------------------------------------
class Hourly : public Permanent 
{
public:           // These must be public so that we can use them in main()
    Hourly();
    Hourly(char* n, char* a, char* ssn, float hw, float hr);
    void printCheck();

private:                              //   Hourly is a Permanent with ...
    float hoursWorked;                //   a number of hours worked, and
    float hourlyRate;                 //   an hourly rate

};

//---------------------------------------------
class Salaried : public Permanent 
{
public:           // These must be public so that we can use them in main()
    Salaried();
    Salaried(char* n, char* a, char* ssn, float wp);
    void printCheck();

private:			        // Salaried is a Permanent with ...
    float weeklyPay;		// a weekly salary

};

#endif //COP3330_EMPLOYEE_H
