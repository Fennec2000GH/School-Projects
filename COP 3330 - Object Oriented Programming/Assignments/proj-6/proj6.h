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
#ifndef PROJ6_H
#define PROJ6_H
#include <string>
using namespace std;

enum type {Savings, Checking, Investment};
class Account
{
public:
    //CONSTRUCTORS
    Account(string & fn, string & ln, type t);

    //ACCESSORS
    type getType() const;
    string getFN() const;
    string getLN() const;
    virtual double projectedBalance() const = 0;

protected:
    string firstName;
    string lastName;
    type T;

};

class savingsAccount : public Account
{
public:
    savingsAccount(string & fn, string & ln, double & cb, double & ir);
    double getCB() const;
    double projectedBalance() const;

protected:
    double currentBalance, interestRate;

};

class checkingAccount : public Account
{
public:
    checkingAccount(string & fn, string & ln, double & cb);
    double getCB() const;
    double projectedBalance() const;

protected:
    double currentBalance;

};

//BONUS #2
class ETF
{
public:
    friend class investmentAccount;
    ETF(double a = 0, double ivs = 0, double cvs = 0, double i = 0);
    double projectedBalance() const;

protected:
    double A;
    double IVS;
    double CVS;
    double I;
    double CV;
    double DIV;
};

class investmentAccount : public Account
{
public:
    investmentAccount(string & fn, string & ln, ETF * ptr);
    double getSumA() const;
    double projectedBalance() const;

protected:
    ETF etfList[5];

};

class Portfolio
{
public:
    //CONSTRUCTORS
    Portfolio();

    //DESTRUCTORS
    ~Portfolio();

    //ACCESSORS
    void showAccounts() const;
    void sort();
    string capitalize(string str) const;

    //MUTATORS
    bool importFile(const char* filename);
    bool createReportFile(const char* filename) const;
    void swap(Account * & a, Account * & b);

protected:
    unsigned int size;
    Account** portfolioList;


};


#endif
