#include "EmployeeList.h"

ostream &operator<<(ostream &os, const EmployeeList &el) 
{
    for (int i=0; i<el.size; i++) 
    {
        cout << "\n";
        el.emps[i]->printCheck();
        cout << "\n";
    }
    return os;
}

EmployeeList::EmployeeList() 
{
    size = 0;
    emps = new Employee*[10]; //dynamically allocate 10 employee pointers
}

EmployeeList::~EmployeeList() 
{

    if(emps != nullptr) 
    { 
        for (int i = 0; i < size; i++) 
        {
            delete emps[i];
            emps[i] = nullptr;
        }
        delete[] emps;
        emps = nullptr;
    }
}


void EmployeeList::add(Employee* e)
{
    emps[size] = e;
    size++;
}

void EmployeeList::addEmployee(char type) 
{
    switch(type) 
    {
        case 'H':
            emps[size] = new Hourly;
            break;

        case 'S':
            emps[size] = new Salaried;
            break;
    }
    size++;
}
