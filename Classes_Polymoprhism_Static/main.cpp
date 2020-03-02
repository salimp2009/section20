#include <iostream>
#include <vector>

class Account 
{
public:
    virtual void withdraw(double amount) {
        std::cout<<"Account: "<<amount<<'\n';
    }
    ~virtual Account()=default;
};

class Savings_Account: public Account
{
public:
    virtual void withdraw(double amount) {
        std::cout<<"Savings_Account: "<<amount<<'\n';
    }
    ~virtual Account()=default;
};

class Checking_Account: public Account
{
public:
    virtual void withdraw(double amount) {
        std::cout<<"Checking Account: "<<amount<<'\n';
    }
    ~virtual Account()=default;
};

class Trust_Account: public Savings_Account
{
public:
    virtual void withdraw(double amount) {
        std::cout<<"Checking Account: "<<amount<<'\n';
    }
    ~virtual Account()=default;
};

int main()
{
    Account* p1=new Account();
    Account* p2=new Savings_Account(); 
    Account* p3=new Checking_Account();
    Account* p4=new Trust_Account(); 
    
    p1->withdraw(1000);
    p2->withdraw(1500);
    p3->withdraw(2000);
    p4->withdraw(3000);
    
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    
    return 0;
}
