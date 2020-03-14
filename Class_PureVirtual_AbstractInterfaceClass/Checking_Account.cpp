#include "Checking_Account.hpp"

Checking_Account::Checking_Account(std::string name, double bal, double fee_amnt):
                                    Account{std::move(name), bal}, fee{fee_amnt} { }

bool Checking_Account::deposit(double amount) {      
    return Account::deposit(amount);
}

bool Checking_Account::withdraw(double amount) {
    if(amount<0) return false;
    amount+=fee;
    return Account::withdraw(amount);          // we can use the Account' withdraw method as well

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

void Checking_Account::print(std::ostream& os) const {
    os<<"[Checking Account: "<<name<<", balance: "<<balance
                             <<", Withdrawal fee: "<<fee<<"]\n";
}
