#include "Checking_Account.h"

// one arg constructor with default values
Checking_Account::Checking_Account(std::string name, double balance)
                    : Account{name, balance}{ }
                    
// withdraw needs to charge 1.5dollars at every transaction
bool Checking_Account::withdraw(double amount)  // virtual & override specifier is used only in declaration
{                       
    amount+=fee;
    return Account::withdraw(amount);
}

 bool Checking_Account::deposit(double amount) // virtual & override specifier is used only in declaration
{
    return Account::deposit(amount);
}

Checking_Account& Checking_Account::operator+=(double amount)
{
    if(Account::deposit(amount))
        return *this;
    return *this;
}

Checking_Account& Checking_Account::operator-=(double amount)
{
    if(this->withdraw(amount))
        return *this;
    return *this;
}

void Checking_Account::print(std::ostream& os) const
{
    os.precision(2);
    os<<std::fixed;
    os<<"[Checking Account name: "<<name<<", Balance :"<<balance
                                    <<", Withdrawal Fee: "<<fee<<"]\n";  
}

                    
                
                    