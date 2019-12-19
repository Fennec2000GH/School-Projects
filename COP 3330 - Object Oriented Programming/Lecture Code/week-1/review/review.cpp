#include <iostream>

using namespace std;

void condition_test()
{
    int i = 5;
    if (i == 5)
        cout << "I am supposed to be here." << endl;
    else
        cout << "I will NEVER be here." << endl;

    int j = 0;
    if (j == 0)
        cout << "I am supposed to be here." << endl;
    else
        cout << "I will NEVER be here." << endl;

    int k = 0;
    if (k == 1)
        cout << "I am supposed to be here." << endl;
    else
        cout << "I will NEVER be here." << endl;

}

void type_cast_test()
{
    char ch = 'C';
    cout << ch << " is " << (int)ch << endl;
    cout << ch << " is " << int(ch) << endl;
    cout << ch << " is " << static_cast<int>(ch) << endl;

    int yearly_salary= 100;
    double monthly_salary = yearly_salary/12;
    cout << "Monthly salary = " << monthly_salary << endl;

    monthly_salary = static_cast<double>(yearly_salary)/12;
    cout << "Monthly salary = " << monthly_salary << endl;
}

void linear_search()
{
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(array)/sizeof(array[0]);

    int target = 5;

    bool found = false;
    int pos = 0;        // C++ array starts from the index 0 !!!
    while((!found) && (pos < size))
    {
       if(array[pos] == target)
       {
           found = true;
           cout << " I find you! " << endl;
       }
       else pos++;
    }

    if(!found)
        cout << target << " is not in the array." << endl;

}


void loop_behavior_test()
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if (j == 8)
                // break;
                // continue;
                // return;

            cout << j << "\t";
        }

        cout << endl;
    }
}

void swap_by_value(int x, int y)
{
    int temp =x;
    x = y;
    y = temp;
}

void swap_by_reference(int& x, int& y)
{
    int temp =x;
    x = y;
    y = temp;
}

void swap_by_pointer(int* x, int* y)
{
    int temp =*x;
    *x = *y;
    *y = temp;
}

void swap_test()
{
    int a = 0;
    int b = 100;

    cout << "a = " << a << " b = " << b << endl;
    // swap_by_value(a, b);
    // swap_by_reference(a, b);
    // swap_by_pointer(&a, &b);
    cout << "a = " << a << " b = " << b << endl;
}

int main()
{
    condition_test();
    //type_cast_test();
    // linear_search();
    // loop_behavior_test();
    // swap_test();

    return 0;
}
