#ifndef _MY_CHECKING_ACCOUNT_H
#define _MY_CHECKING_ACCOUNT_H

#include "Account.hpp"
#include <string>

class Checking_Account:public Account
{
     static constexpr const char* def_name="Checking Account";
     static constexpr double def_balance=0.0;
     static constexpr double def_fee=1.50;   // withdrawal fee per transaction
public:
    Checking_Account(std::string name=def_name, double=def_balance, double fee=def_fee);
    
    virtual bool deposit(double amount) override;        // override needed to make it a concrete class
    virtual bool withdraw(double amount) override;
    virtual void print(std::ostream& os) const override;
    
    Checking_Account& operator+=(double amount);     // overloaded operator for deposit
    Checking_Account& operator-=(double amount);     // overloaded operator for withdrawal
  
   const std::string&  get_name() const& { return name;}
   std::string         get_name() && {return std::move(name);}  // overloaded get_name to steal the value; 
   double              get_balance() const { return balance;} 

protected:
    double fee;
};

#endif // _MY_CHECKING_ACCOUNT_H
