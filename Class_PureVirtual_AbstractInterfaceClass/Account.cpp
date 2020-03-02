#include "Account.hpp"

Account::Account(std::string nam, double bal): name{std::move(nam)}, balance{bal} 
                { 
                    //std::cout<<"Account Created:"<<name<<", balance: "<<balance<<'\n';
                }

bool Account::deposit(double amount) {
    if(amount<0) {
        std::cout<<"invalid amount entry...\n";
        return false;
    }
    balance+=amount;
    return true;
}

bool Account::withdraw(double amount) {
    if(balance-amount<0) {
        std::cout<<"insufficient balance: "<<balance<<'\n';
        return false;
    }        
    balance-=amount;
    return true;
}

void Account::print(std::ostream& os) const {
     os<<"Account name: "<<name<<", balance: "<<balance<<'\n';
 }

