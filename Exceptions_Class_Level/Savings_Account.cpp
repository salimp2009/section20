#include "Savings_Account.hpp"

Savings_Account::Savings_Account(std::string nam, double bal, double rate): 
                        Account{std::move(nam), bal}, int_rate{rate} { }
                       

bool Savings_Account::deposit(double amount) {
    amount+=amount*int_rate;
    return Account::deposit(amount); 
}

Savings_Account& Savings_Account::operator+=(double amount) {     // overloaded operator for deposit
     if(this->deposit(amount))      // the if statement might be unneccessary
         return *this;              // just call the deposit() function and return *this
    return *this;
}

Savings_Account& Savings_Account::operator-=(double amount) {    // overloaded operator for withdrawal
   if(this->withdraw(amount))
        return *this;
    return *this;
}

bool Savings_Account::withdraw(double amount) {
    Account::withdraw(amount);
    return true;
}

void Savings_Account::print(std::ostream& os) const {
    os<<"[Savings Account: "<<name<<", balance: "<<balance
                            <<", interest rate: "<<int_rate<<"]\n";
}
    
