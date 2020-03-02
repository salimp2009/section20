#ifndef _MY_ACCOUNT_H_
#define _MY_ACCOUNT_H_

#include <string>
#include <iostream>

class Account
{
private:
    static constexpr const char * def_name="Base Account";
    static constexpr double def_balance=0.; 
public:
    Account(std::string nam=def_name, double bal=def_balance);

    bool deposit(double amount);
    bool withdraw(double amount);
    
    const std::string&  get_name() const& { return name;}
    std::string         get_name()&& {
        std::cout<<"get_name with r-value; Stealing the name...";  // steals the value and returns the R value;
        return std::move(name);                                    // this is used when the name is not need any more
        }     
                                                           
    Account& operator+=(double amount);     // overloaded operator for deposit
    Account& operator-=(double amount);     // overloaded operator for withdrawal


    double              get_balance() const { return balance;} 

    friend std::ostream& operator<<(std::ostream& os, const Account& acc);
    
protected:
    std::string name;
    double balance;
};

#endif // _MY_ACCOUNT_H_
