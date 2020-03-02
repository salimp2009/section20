#include <iostream>
#include "Account.hpp"
#include "Savings_Account.hpp"
#include "Checking_Account.hpp"
#include "Trust_Account.hpp"
#include "Account_Utility.hpp"
#include <memory>


int main()
{
    std::shared_ptr<Account>acc1=std::make_shared<Savings_Account>("Salim Savings");
    std::shared_ptr<Account>acc2=std::make_shared<Checking_Account>("Sema Checking", 25000);
    std::shared_ptr<Account>acc3=std::make_shared<Trust_Account>("Demir Trust", 5000);
    std::shared_ptr<Account>acc4=std::make_shared<Savings_Account>("Didem Savings", 75000, 0.02);
    
//    std::cout<<*acc1<<'\n';
//    std::cout<<*acc2<<'\n';
//    std::cout<<*acc3<<'\n';
//    std::cout<<*acc4<<'\n';
    
//    acc1->deposit(5000);
//    std::cout<<*acc1<<'\n';
//    
//    acc4->withdraw(5000);
//    std::cout<<*acc4<<'\n';
//    
//    acc3->withdraw(1000);
//    std::cout<<*acc3<<'\n';
//    
//    acc4->deposit(3520);
//    std::cout<<*acc4<<'\n';
    
[[maybe_unused]]    typedef std::shared_ptr<Account> AccPtr;
    std::vector<AccPtr> accounts{std::move(acc1), std::move(acc2), 
                                std::move(acc3), std::move(acc4)};
    display(accounts);
    
    deposit(accounts, "Salim Savings", 50000);    
    display(accounts);

    withdraw(accounts, "Sema Checking", 2500);
    display(accounts);
    
    withdraw(accounts, "Demir Trust", 1000);
    display(accounts);
    
    return 0;
}
