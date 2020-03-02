#ifndef _MY_ACCOUNT_UTILIT_H
#define _MY_ACCOUNT_UTILIT_H

#include <vector>
#include <type_traits>


// Basic Utility functions for Account Class Containers

template<typename Cont>
void display(const Cont& accounts) {
 //   typename Cont::const_iterator pos=accounts.cbegin();   // alternative way
    for(const typename Cont::value_type& acc : accounts)     // when we use Cont::value_type, it refers to type of the elements inside the container
        std::cout<<acc<<'\n';                               // the type of container is Cont and the type of the elements inside a container is Cont:value_type
}

template<typename Cont, typename T>
bool deposit(Cont& accounts, T&& name, double amount)
{
    typename Cont::iterator pos=accounts.begin();
    for(; pos!=accounts.end(); ++pos)
        if(pos->get_name()==name) {
            pos->deposit(amount);
            std::cout<<"Deposit Info: "<<*pos<<'\n';
            return true;
        }
        std::cout<<name<<" Not in the account list ..Sorry...\n";
        return false;
}

template<typename Cont, typename T>
bool withdraw(Cont& accounts, T&& name, double amount)
{
    for(typename Cont::value_type& acc:accounts)
        if(acc.get_name()==name) {
            acc.withdraw(amount);
             std::cout<<"Withdraw Info: "<<acc<<'\n';
            return true;
        }
        std::cout<<name<<" Not in the account list ..Sorry...\n";
        return false;
}

// Utility functions




#endif // _MY_ACCOUNT_UTILIT_H