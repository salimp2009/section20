#include <iostream> 
#include "Account_Utility.h"


// Utility functions for Account class
void display(const std::vector<Account*> &accounts)
{
    std::cout<<"\n===========Accounts=========================\n";
   for(const auto acct:accounts)
        std::cout<<*acct<<'\n';    
}

void deposit(std::vector<Account*> &accounts, double amount)
{
    std::cout<<"\n===========Depositing to Accounts=========================\n";
    for(auto acct:accounts) {
        if(acct->deposit(amount))
            std::cout<<"\nDeposited "<<amount<<" to "<<*acct<<'\n';
        else
            std::cout<<"\nFailed Deposit of "<<amount<<" to "<<*acct<<'\n';
    }
}
void withdraw(std::vector<Account*> &accounts, double amount)
{
    std::cout<<"\n===========Withdrawing from Accounts=========================\n";
    for(auto acct:accounts) {
        if(acct->withdraw(amount))
            std::cout<<"\nWithdrew "<<amount<<" from "<<*acct<<'\n';
        else
            std::cout<<"\nFailed Withdrawal "<<amount<<" from "<<*acct<<'\n';      
    }        
}

