#include "Checking_Account.hpp"

Checking_Account::Checking_Account(std::string name, double bal, double fee_amnt):
                                    Account{std::move(name), bal}, fee{fee_amnt} { }

bool Checking_Account::deposit(double amount) {      
    return Account::deposit(amount);
}

bool Checking_Account::withdraw(double amount) {
    if(amount<0) throw NegativeAmountException{ };
    amount+=fee;
    return Account::withdraw(amount);          // we use the Account' withdraw method as well to add the exception
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
