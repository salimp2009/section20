#include "Account.hpp"


void Account::set_name(std::string nm) 
{
    name=std::move(nm);
}

std::string Account::get_name() const
{
    return name;
}

bool Account::deposit(double amount) 
{
    if(amount<0) {
        std::cout<<"invalid amount..!!!\n";
        return false;
    }
    balance+=amount;
    return true;
}

bool Account::with_draw(double amount)
{
    if(balance<amount) {
        std::cout<<"Insufficient Funds: "<<balance<<'\n';
        return false;
    }
    balance-=amount;
    std::cout<<"New balance: "<<balance<<'\n';
    return true;
}