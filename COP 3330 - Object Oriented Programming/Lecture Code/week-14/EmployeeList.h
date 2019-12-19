#ifndef COP3330_EMPLOYLIST_H
#define COP3330_EMPLOYLIST_H

// Including base class and all the derived classes
#include <cstddef>
#include "Employee.h"

class EmployeeList {

    friend ostream& operator<< (ostream& os, const EmployeeList &el);

public:
    EmployeeList();
    ~EmployeeList();
    void add(Employee* e); // Takes an address to an Employee and puts it into the array
                           // this is prone to a segmentation fault since the address
                           // is not guaranteed to have been dynamically allocated

    void addEmployee(char type); // This takes a parameter and dynamically allocates
                                // the correct type of employee. We are ensuring that
                                // the employee is dynamically allocated

private:
    int size;
    Employee** emps;        //This array of pointers is dynamically created
};


#endif //COP3330_EMPLOYLIST_H
