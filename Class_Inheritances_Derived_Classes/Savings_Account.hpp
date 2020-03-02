#ifndef _MY_SAVINGS_ACCOUNT_H
#define _MY_SAVINGS_ACCOUNT_H
 #include "Account.hpp"

class Savings_Account: public Account
{
private:
    static constexpr const char * def_name="Savings Account";
    static constexpr double def_balance=0.; 
    static constexpr double def_int_rate=0.015;
public:
    Savings_Account(std::string nam=def_name, double bal=def_balance, double int_rate=def_int_rate);

    bool deposit(double amount);  
//    bool withdraw(double amount);   // not needed because the base class has the same functionality
    
    Savings_Account& operator+=(double amount);     // overloaded operator for deposit
    Savings_Account& operator-=(double amount);     // overloaded operator for withdrawal
    
   const std::string&  get_name() const& { return name;}
   double              get_balance() const { return balance;} 
    
 friend std::ostream& operator<<(std::ostream& os, const Savings_Account& saving);

protected:
    double int_rate;
};

#endif // _MY_SAVINGS_ACCOUNT_H
