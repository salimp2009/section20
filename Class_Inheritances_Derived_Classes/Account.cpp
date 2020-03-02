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

Account& Account::operator+=(double amount) {    // overloaded operator for deposit
    if(this->deposit(amount))
         return *this;
    return *this;
}

Account& Account::operator-=(double amount) {    // overloaded operator for withdrawal
    if(this->withdraw(amount))
         return *this;
    return *this;
}


    std::ostream& operator<<(std::ostream& os, const Account& acc) {
        os<<"Account name: "<<acc.name<<", balance: "<<acc.balance<<'\n';
        return os;
    }
    



