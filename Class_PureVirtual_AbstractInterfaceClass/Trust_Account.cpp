#include "Trust_Account.hpp"

      
Trust_Account::Trust_Account(std::string name, double balance, double int_rate):
                            Savings_Account{std::move(name), balance, int_rate}, total_withdrawal{0} { }                 

bool Trust_Account::deposit(double amount) {
    if(amount>=bonus_limit) amount+=def_bonus;
   return Savings_Account::deposit(amount);
}

bool Trust_Account::withdraw(double amount) {
    // check if you do not exceed the total amount of withdrawal and maximum withdrawal amount
    if(total_withdrawal>=withdrawal_limit || amount>max_withdrawal_rate*balance) 
        return false;
    // if eveything is OK do the withdraw and increase the total num of withdrawals
    ++total_withdrawal;                     
    return Savings_Account::withdraw(amount);
}

Trust_Account& Trust_Account::operator+=(double amount) {     // overloaded operator for deposit
    if(this->deposit(amount))
        return *this;
    return *this;
}

Trust_Account& Trust_Account::operator-=(double amount) {    // overloaded operator for withdrawal
    if(this->withdraw(amount) )
        return *this;
    return *this;
}
void Trust_Account::print(std::ostream& os) const {
    os<<"[Trust Account: "<<name<<", balance: "<<balance<<", interest rate: "<<int_rate
                          <<", bonus amount: "<<def_bonus<<"]\n";
}