#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rate)
                            : Savings_Account{name, balance,int_rate}, total_withdrawal{0}
                            { }
                            
//any deposit 5000 dollars or more will get 50 dollars bonus
bool Trust_Account::deposit(double amount)
{
    if(amount<0) return false;
    
    if(amount>=amount_for_bonus) {
        amount+=bonus;
    }
    
    return Savings_Account::deposit(amount);   
}  


// 3 withdrawal per year; each withdrawal cannot exceed 20% of the balance
bool Trust_Account::withdraw(double amount) 
{
    if(total_withdrawal>=max_withdrawal || amount>balance*withdrawal_limit) {         
        return false; 
    } else {
        ++total_withdrawal;
        return Savings_Account::withdraw(amount);  
    }
}

Trust_Account& Trust_Account::operator+=(double amount)
{
    if(this->deposit(amount))
        return *this;
    return *this;  
}

Trust_Account& Trust_Account::operator-=(double amount)
{
    if(this->withdraw(amount))
        return *this;
    return *this;  
}

void Trust_Account::print(std::ostream& os) const
{
    os.precision(2);
    os<<std::fixed;
    os<<"[Trust Account name: "<<name<<", Balance: "<<balance<<", interest: "<<int_rate
                <<", Total withdrawals: "<<total_withdrawal<<"]\n"; 
} 