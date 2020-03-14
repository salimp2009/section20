#ifndef _MY_ACCOUNT_H_
#define _MY_ACCOUNT_H_

#include <string>
#include <iostream>
#include "I_Print.hpp"
#include "IllegalBalanceException.hpp"

class Account:public I_Print
{
private:
    static constexpr const char * def_name="Base Account";
    static constexpr double def_balance=0.; 
public:
    Account(std::string nam=def_name, double bal=def_balance);
    virtual bool deposit(double amount)=0;
    virtual bool withdraw(double amount)=0;
    virtual void print(std::ostream& os) const override;
    double       get_balance() const { return balance;} 
    const std::string&  get_name() const& { return name;}
    virtual ~Account()=default;
protected:
    std::string name;
    double balance;
};

#endif // _MY_ACCOUNT_H_
