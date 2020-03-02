#ifndef _MY_TRUST_ACCOUNT_H
#define _MY_TRUST_ACCOUNT_H

#include "Savings_Account.hpp"
#include "Account.hpp"
#include <string>

class Trust_Account: public Savings_Account
{
private:

    static constexpr const char * def_name="Checking Account";
    static constexpr double def_balance=0.; 
    static constexpr double def_int_rate=0.015;
    static constexpr double def_bonus=50;
    static constexpr double bonus_limit=5000;     // any deposit over 5000 USD gets 50 usd bonus
    static constexpr int withdrawal_limit=3;
    static constexpr double max_withdrawal_rate= 0.2; // no greater than 20% of the balance
public:
    Trust_Account(std::string name=def_name, double bal=def_balance, double int_rate=def_int_rate);
    
    virtual bool deposit(double amount) override;
    virtual bool withdraw(double amount) override;
    virtual void print(std::ostream& os) const override;
    
    Trust_Account& operator+=(double amount);     // overloaded operator for deposit
    Trust_Account& operator-=(double amount);     // overloaded operator for withdrawal
   
   const std::string&      get_name() const& {return name;}
   std::string             get_name() && { return std::move(name);}
   double                  get_balance() const { return balance;}
protected:
    int total_withdrawal;
};

#endif // _MY_TRUST_ACCOUNT_H
