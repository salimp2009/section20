#include "Checking_Account.hpp"

Checking_Account::Checking_Account(std::string name, double bal, double fee_amnt):
                                    Account{std::move(name), bal}, fee{fee_amnt} { }

//bool Checking_Account::deposit(double amount) {       // not used since base Account has same functionality
//    Account::deposit(amount);
//}

bool Checking_Account::withdraw(double amount) {
    if(balance-amount-fee<0) return false;
    amount+=fee;
    balance-=amount;
    return true;
}

Checking_Account& Checking_Account::operator+=(double amount) {     // overloaded operator for deposit
     if(this->deposit(amount))
            return *this;
       return *this;
}

Checking_Account& Checking_Account::operator-=(double amount) {    // overloaded operator for withdrawal
    if(this->withdraw(amount))
         return *this;
       return *this;
}

std::ostream&  operator<<(std::ostream& os, const Checking_Account& obj) {
    os<<"Checking Accnt Name: "<<obj.name<<", balance: "<<obj.balance<<", Withdraw fee: "<<obj.fee<<'\n';
    return os;
}
