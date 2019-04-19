
#include "Account.h"

Account::Account(std::string name, double balance)
            : name{name}, balance{balance} { }
            
bool Account::deposit(const double amount)
{
    if(amount<0) 
        return false;
    else {
        balance+=amount;
        return true;
    }
}

bool Account::withdraw(const double amount)
{
    if(balance-amount>=0) {
        balance-=amount;
        return true;   
    } else 
        return false;     
}
  
double Account::get_balance() const
{
    return balance;
}


void Account::print(std::ostream& os) const
{
    os.precision(2);
    os<<std::fixed;
    os<<"[Account: "<<name<<", Balance: "<<balance<<"]";
}
  