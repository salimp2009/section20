#include <iostream>
#include "Account.hpp"
#include "Savings_Account.hpp"
#include "Checking_Account.hpp"
#include "Trust_Account.hpp"
#include "Account_Utility.hpp"
#include <memory>

int main()
{
    std::unique_ptr<Account> salimsAccount;
    
    try {
        salimsAccount=std::make_unique<Checking_Account>("Salim", -1000);
        std::cout<<*salimsAccount<<'\n';
    
    } catch(IllegalBalanceException& ex) {
        std::cerr<<ex.what()<<'\n';
    }
    
    try {
        // since the first try block fails the account will not be created
        // therefore re-create the Account and try to withdraw more than balanace
        // or - negative value
        salimsAccount=std::make_unique<Checking_Account>("Salim", 1000);
        salimsAccount->withdraw(1500);
        std::cout<<*salimsAccount<<'\n';
    
    } catch(IllegalBalanceException& ex) {
        std::cerr<<ex.what()<<'\n';
    } catch(InsufficientFundsException& ex) {
       std::cerr<<ex.what()<<'\n'; 
    } catch(NegativeAmountException& ex) {
       std::cerr<<ex.what()<<'\n'; 
    }
    
    // this line will be displayed to show the main will finish properly even if 
    // the other part fail; results will not be as expected but the error will be caought and identified
    // prefer to do this assert that runs during the debug only with a defined macro 
    // so that it can be stripped out for the release versions
    
    std::cout<<"Finishing main...\n";
    
    return 0;
}
