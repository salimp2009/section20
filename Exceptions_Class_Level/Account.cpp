#include "Account.hpp"

Account::Account(std::string nam, double bal): name{std::move(nam)}, balance{bal} 
                { 
                    if(balance<0) throw IllegalBalanceException{};
                }

bool Account::deposit(double amount) {
    if(amount<0) throw NegativeAmountException{};
    balance+=amount;
    return true;
}

bool Account::withdraw(double amount) {
    if(amount<0) throw NegativeAmountException{};
    if(balance-amount<0)  throw InsufficientFundsException{};
    balance-=amount;
    return true;
}

void Account::print(std::ostream& os) const {
     os<<"Account name: "<<name<<", balance: "<<balance<<'\n';
 }

