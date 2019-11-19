/* Name: Caijun Qin
Date: 09/16/2018
Section: 6
Assignment: 2
Due Date: 09/21/2018
About this project:
This is a semester final grade calculator specifically for the course COP3363.
The user will be asked to provide specific numerical grades for homework,
recitations, tests, and extra credit. The program uses this information to
compute an average for each category of assignments.

Assumptions: Only valid homework scores, recitation grades (either 20,10 or 0),
and test grades will be entered by the user when prompted.
All work below was performed by Caijun Qin */


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    //sets % sign to be printable
    char percentSign = '%';

    /***VARIABLE DECLARATIONS FOR GRADES***/
    //HOMEWORK
    double hw1, hw2, hw3, hw4, hw5, hw6, hw7;

    //RECITATION
    double rec1, rec2, rec3, rec4, rec5, rec6;

    //TESTS
    double midTermI, midTermII, Final;

    //EXTRA CREDIT YES OR NO, and the number of points earned
    char extraCredit;
    double ecPoints;

    //welcome message to user
    cout << "Welcome to the Grade Calculator! \n \n";

    //prompts the user to list out homework grades
    cout << "HOMEWORK GRADES --> \n";

    cout << "Homework 1:" << "  ";
    cin >> hw1;
    cout << "Homework 2:" << "  ";
    cin >> hw2;
    cout << "Homework 3:" << "  ";
    cin >> hw3;
    cout << "Homework 4:" << "  ";
    cin >> hw4;
    cout << "Homework 5:" << "  ";
    cin >> hw5;
    cout << "Homework 6:" << "  ";
    cin >> hw6;
    cout << "Homework 7:" << "  ";
    cin >> hw7;

    cout << "\n";

    //prompts the user to list out recitation grades
    cout << "RECITATION GRADES -->" << "\n";
    cout << "Recitation 1:" << "  ";
    cin >> rec1;
    cout << "Recitation 2:" << "  ";
    cin >> rec2;
    cout << "Recitation 3:" << "  ";
    cin >> rec3;
    cout << "Recitation 4:" << "  ";
    cin >> rec4;
    cout << "Recitation 5:" << "  ";
    cin >> rec5;
    cout << "Recitation 6:" << "  ";
    cin >> rec6;

    cout << "\n";

    //prompts the user to list out test grades
    cout << "TEST GRADES -->" << "\n";
    cout << "Midterm I:" << "  ";
    cin >> midTermI;
    cout << "Midterm II:" << "  ";
    cin >> midTermII;
    cout << "Final:" << "  ";
    cin >> Final;

    cout << "\n";

    //extra credit inquiry and points
    cout << "Is there any extra credit to add in? (Y or N) -->";
    cin >> extraCredit;

    if(extraCredit == 'Y' || extraCredit == 'y'){
        cout << "How many extra credit points should be added? -->";
        cin >> ecPoints;
        cout << "\n";
    } else if (extraCredit == 'N' || extraCredit == 'n'){
        ecPoints = 0.00;
    } else {
        cout << "Invalid option, exiting program." << "\n";
    }

    //equations to calculate final averages and letter grade
    char letterGrade;

    double hwAvg = (((hw1 + hw2 + hw3 + hw4 + hw5 + hw6 + hw7) +
    (rec1 + rec2 + rec3 + rec4 + rec5 + rec6) + ecPoints) / 820) * 100;

    double testAvg = ((midTermI * 17.5) + (midTermII * 17.5) + (Final * 25))
    / 60;

    double courseAvg = ((midTermI * 0.175) + (midTermII * 0.175) + (Final * 0.25)
    + (hwAvg * 0.40));

    //designation of letter grade
    if (courseAvg >= 90.00){
        letterGrade = 'A';
    } else if (courseAvg < 90.00 && courseAvg >= 80.00){
        letterGrade = 'B';
    } else if (courseAvg < 80.00 && courseAvg >= 69.00){
        letterGrade = 'C';
    } else if (courseAvg < 69.00 && courseAvg >= 60.00){
        letterGrade = 'D';
    } else if (courseAvg < 60.00 && courseAvg >= 0.00){
        letterGrade = 'F';
    }

    //displays the grade averages by category
    if(extraCredit == 'Y' || extraCredit == 'y' || extraCredit == 'N' || extraCredit == 'n'){
    cout << "Homework Average:" << fixed << setprecision(2) << hwAvg << percentSign << "\n";
    cout << "Test Average:" << fixed << setprecision(2) << testAvg << percentSign << "\n";
    cout << "Course Average:" << fixed << setprecision(2) << courseAvg << percentSign << "\n";
    cout << "Course Grade:" << letterGrade << "\n";
    }

    return 0;
}
