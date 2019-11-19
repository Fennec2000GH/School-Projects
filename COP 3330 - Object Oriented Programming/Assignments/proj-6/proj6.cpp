/*
Name: Caijun Qin
Course and Section: COP3330-0009
Project: 6
Summary: This program renders a pseudo-heterogeneous array of
bank accounts taking on the following categories: Savings,
Checking, and Investment. Each investment account consists of
5 Exchange-Traded Funds. The program is mainly used to store the
accounts of different users, but it can also project the future
growth of each account based on appropriate measures.
*/
#include <cctype>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include "proj6.h"

//ACCOUNT CLASS FUNCTIONS
Account::Account(string & fn, string & ln, type t):
firstName(fn), lastName(ln), T(t){}

type Account::getType() const
{
    return T;
}

string Account::getFN() const
{
    return firstName;
}

string Account::getLN() const
{
    return lastName;
}

//SAVINGS ACCOUNT CLASS FUNCTIONS
savingsAccount::savingsAccount(string & fn, string & ln, double & cb, double & ir):
Account(fn, ln, Savings), currentBalance(cb), interestRate(ir){}

double savingsAccount::getCB() const
{
    return currentBalance;
}

double savingsAccount::projectedBalance() const
{
    return currentBalance * (1 + interestRate);
}

//CHECKING ACCOUNT CLASS FUNCTIONS
checkingAccount::checkingAccount(string & fn, string & ln, double & cb):
Account(fn, ln, Checking), currentBalance(cb){}

double checkingAccount::getCB() const
{
    return currentBalance;
}

double checkingAccount::projectedBalance() const
{
    return currentBalance + 0.1;
}

//ETF AUXILIARY CLASS USED FOR INVESTMENT ACCOUNT CLASS
ETF::ETF(double a, double ivs, double cvs, double i):
A(a), IVS(ivs), CVS(cvs), I(i)
{
    CV = (a / ivs) * cvs;
    DIV = i * a;
}

//INVESTMENT ACCOUNT CLASS FUNCTIONS
investmentAccount::investmentAccount(string & fn, string & ln, ETF * arr):
Account(fn, ln, Investment)
{
    for(unsigned int i = 0; i < 5; i++)
        etfList[i] = *(arr + i);
}

double investmentAccount::getSumA() const
{
    double sum = 0;
    for(unsigned int i = 0; i < 5; i++)
        sum += etfList[i].A;
    return sum;
}

double investmentAccount::projectedBalance() const
{
    double PB = 0;
    for(unsigned int i = 0; i < 5; i++)
        PB += etfList[i].CV + etfList[i].DIV;
    return PB;
}

//PORTFOLIO CLASS FUNCTIONS
Portfolio::Portfolio()
{
    size = 0;
    portfolioList = nullptr;
}

Portfolio::~Portfolio()
{
    delete [] portfolioList;
}

bool Portfolio::importFile(const char* filename)
{
    //setting up portfolioList and importing the input file
    unsigned int numAccounts;
    unsigned int prevSize;
    ifstream input;
    input.open(filename, ios::in);
    bool open = input.is_open();

    if(input.is_open()){
        input >> numAccounts;
        input.ignore();
        prevSize = size;
        size += numAccounts;

        //appending to pre-existing list of accounts
        if(size > 0){
            Account** temp = new Account*[prevSize];
            for(unsigned int i = 0; i < prevSize; i++)
                temp[i] = portfolioList[i];
            portfolioList = new Account*[size];
            for(unsigned int i = 0; i < prevSize; i++)
                portfolioList[i] = temp[i];
        } else
            portfolioList = new Account*[size];

        //extracts characters by line from input
        for(unsigned int i = prevSize; i < size; i++)
        {
            //NOT ALL DATA ENTRIES BELOW WILL BE NEEDED EVERY TIME
            //parent class data entries - needed for all accounts
            string ln;// = "";                 //last name
            string fn;// = "";                 //first name
            string accountType = "";        //type of account

            //extracting data from the user
            getline(input, ln, ',');        //gets the last name
            input.ignore();
            getline(input, fn);             //gets the first name
            getline(input, accountType, ' ');   //gets the type of account
            if(accountType == "Savings")
            {
                double cb = 0;              //current balance
                double ir = 0;              //interest rate
                input >> cb >> ir;
                input.ignore();
                portfolioList[i] = new savingsAccount(fn, ln, cb, ir);
            } else if(accountType == "Checking"){
                double cb = 0;              //current balance
                input >> cb;
                input.ignore();
                portfolioList[i] = new checkingAccount(fn, ln, cb);
            } else if(accountType == "Investment"){
                ETF arr[5];
                for(unsigned int n = 0; n < 5; n++)
                {
                    double a = 0;
                    double ivs = 0;
                    double cvs = 0;
                    double i = 0;
                    input >> a >> ivs >> cvs >> i;
                    arr[n] = ETF(a, ivs, cvs, i);
                }
                input.ignore();
                portfolioList[i] = new investmentAccount(fn, ln, arr);
            }

        }
    }
    input.close();

    return open;
}

bool Portfolio::createReportFile(const char* filename) const
{
    //title of the output report
    ofstream output;
    output.open(filename, ios::out | ios::trunc);
    bool open = output.is_open();
    if(output.is_open()){
        output << "Banking Summary" << endl;
        output << "---------------------";

        //measurement variables
        double savingsTotal = 0, checkingTotal = 0, investmentTotal = 0;
        unsigned int savingsCount = 0, checkingCount = 0, investmentCount = 0;

        //prints out acconts by category
        string name = "";
        for(unsigned int i = 0; i < size; i++){
            if(portfolioList[i] -> getType() == Savings){
                if(savingsCount == 0){
                    output << endl << endl << "Saving Accounts" << endl << endl;
                    output << left << setw(45) << "Holder's Name" << right << setw(15) << "Initial Balance" << right << setw(20) << "Projected Balance" << endl;
                    output << "--------------------------------------------------------------------------------" << endl;
                }
                name = portfolioList[i] -> getFN() + " " + portfolioList[i] -> getLN();
                output << left << setw(45) << name;
                output << right << setw(15) << fixed << setprecision(2) << static_cast<savingsAccount*>(portfolioList[i]) -> getCB();
                output << right << setw(20) << fixed << setprecision(2) << static_cast<savingsAccount*>(portfolioList[i]) -> projectedBalance() << endl;
                ++savingsCount;
                savingsTotal += static_cast<savingsAccount*>(portfolioList[i]) -> projectedBalance();
            }
        } for(unsigned int i = 0; i < size; i++){
            if(portfolioList[i] -> getType() == Checking){
                if(checkingCount == 0){
                    output << endl << endl << endl << "Checking Accounts" << endl << endl;
                    output << left << setw(45) << "Holder's Name" << right << setw(15) << "Initial Balance" << right << setw(20) << "Projected Balance" << endl;
                    output << "--------------------------------------------------------------------------------" << endl;
                }
                name = portfolioList[i] -> getLN() + " " + portfolioList[i] -> getFN();
                output << left << setw(45) << name;
                output << right << setw(15) << fixed << setprecision(2) << static_cast<checkingAccount*>(portfolioList[i]) -> getCB();
                output << right << setw(20) << fixed << setprecision(2) << static_cast<checkingAccount*>(portfolioList[i]) -> projectedBalance() << endl;
                ++checkingCount;
                checkingTotal += static_cast<checkingAccount*>(portfolioList[i]) -> projectedBalance();
            }
        } for(unsigned int i = 0; i < size; i++){
            if(portfolioList[i] -> getType() == Investment){
                if(investmentCount == 0){
                    output << endl << endl << endl << "Investment Accounts" << endl << endl;
                    output << left << setw(45) << "Holder's Name" << right << setw(15) << "Initial Balance" << right << setw(20) << "Projected Balance" << endl;
                    output << "--------------------------------------------------------------------------------" << endl;
                }
                name = portfolioList[i] -> getLN() + " " + portfolioList[i] -> getFN();
                output << left << setw(45) << name;
                output << right << setw(15) << fixed << setprecision(2) << static_cast<investmentAccount*>(portfolioList[i]) -> getSumA();
                output << right << setw(20) << fixed << setprecision(2) << static_cast<investmentAccount*>(portfolioList[i]) -> projectedBalance() << endl;
                ++investmentCount;
                investmentTotal += static_cast<investmentAccount*>(portfolioList[i]) -> projectedBalance();
            }
        }

        double savingsAvg = savingsCount == 0 ? 0 : savingsTotal / savingsCount;
        double checkingAvg = checkingCount == 0 ? 0 : checkingTotal / checkingCount;
        double investmentAvg = investmentCount == 0 ? 0 : investmentTotal / investmentCount ;
        output << endl << endl << endl << endl << "Overall Account distribution" << endl << endl;
        output << left << setw(16) << "Savings:" << savingsCount << "   -" << right << setw(11) << fixed << setprecision(2) <<  savingsAvg << endl;
        output << left << setw(16) << "Checking:" << checkingCount << "   -" << right << setw(11) << fixed << setprecision(2) << checkingAvg << endl;
        output << left << setw(16) << "Investment:" << investmentCount << "   -" << right << setw(11) << fixed << setprecision(2) << investmentAvg;
    }
    output.close();

    return open;
}

void Portfolio::showAccounts() const
{
    cout << left << setw(41) << "Holder" << left << setw(17) << "Type" << left << setw(7) << "Balance" << endl;
    for(unsigned int i = 0; i < size; i++){
        cout << left << setw(21) << portfolioList[i] -> getLN() << left << setw(21) << portfolioList[i] -> getFN();
        switch(portfolioList[i] -> getType()){
            case Savings:
            {
                cout << left << setw(17) << "Savings";
                cout << right << setw(7) << fixed << setprecision(2) << static_cast<savingsAccount*>(portfolioList[i]) -> getCB();
                break;
            }
            case Checking:
            {
                cout << left << setw(17) << "Checking";
                cout << right << setw(7) << fixed << setprecision(2) << static_cast<checkingAccount*>(portfolioList[i]) -> getCB();
                break;
            }
            case Investment:
            {
                cout << left << setw(17) << "Investment";
                cout << right << setw(7) << fixed << setprecision(2) << static_cast<investmentAccount*>(portfolioList[i]) -> getSumA();
            }
        }
    }
    cout << endl;

    return;
}

string Portfolio::capitalize(string str) const
{
    string newStr = str;
    for(unsigned int i = 0; i < newStr.length(); i++)
        newStr[i] = toupper(newStr[i]);
    return newStr;
}

void Portfolio::swap(Account * & a, Account * & b)
{
    Account* temp = b;
    b = a;
    a = temp;
    return;
}

//BONUS #1
void Portfolio::sort()
{
    for(unsigned int current = 0; current < size; current++)
        for(unsigned int i = current; i < size; i++)
        {
            if(capitalize(portfolioList[current] -> getLN()).compare(capitalize(portfolioList[i] -> getLN())) > 0)
                swap(portfolioList[current], portfolioList[i]);
            else if(capitalize(portfolioList[current] -> getLN()).compare(capitalize(portfolioList[i] -> getLN())) == 0
                    && capitalize(portfolioList[current] -> getFN()).compare(capitalize(portfolioList[i] -> getFN())) > 0)
                swap(portfolioList[current], portfolioList[i]);
        }

    return;
}
