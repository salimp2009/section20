#include "Savings_Account.hpp"

Savings_Account::Savings_Account(std::string nam, double bal, double rate): 
                        Account{std::move(nam), bal}, int_rate{rate} { }
                       

bool Savings_Account::deposit(double amount) {
    if(amount<0) {
        std::cout<<"invalid amount entry...\n";
        return false;
    }
    amount+=amount*int_rate;
    Account::deposit(amount); 
    return true;
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

//bool Savings_Account::withdraw(double amount) {
//    if(balance-amount<0) {
//        std::cout<<"Insufficient Balance; "<<"requested: "<<amount
//                 <<", balance: "<<balance<<'\n';
//        return false;
//    }
//    Account::withdraw(amount);
//    return true;
//}

std::ostream& operator<<(std::ostream& os, const Savings_Account& saving) {
    os<<"Saving Accounts name: "<<saving.name<<", balance:"<<saving.balance
                                <<", interest rate: "<<saving.int_rate<<'\n';
    return os;
}
    
