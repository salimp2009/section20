#ifndef _MY_ACCOUNT_UTILIT_H
#define _MY_ACCOUNT_UTILIT_H

#include <vector>
#include <type_traits>
#include <iostream>

// Basic Utility functions for Account Class Containers

template<typename Cont>
void display(const Cont& accounts) {
//   typename Cont::const_iterator pos=accounts.cbegin();   // alternative way; for practice purposes only
//    for(;pos!=accounts.end(); ++pos)                      // below method is or even using and range is best way to go
//        std::cout<<*(*pos)<<'\n';

    for(const typename Cont::value_type& acc:accounts)     // when we use Cont::value_type, it refers to type of the elements inside the container
        std::cout<<*acc<<'\n';                               // the type of container is Cont and the type of the elements inside a container is Cont:value_type
}

template<typename Cont, typename T>
bool deposit(Cont& accounts, T&& name, double amount)
{
    for(typename Cont::value_type& acc:accounts) {
        if(acc->get_name()==name) {
            acc->deposit(amount);
            return true;
        }
    }
        std::cout<<name<<" Not in the account list ..Sorry...\n";
        return false;
}

template<typename Cont, typename T>
bool withdraw(Cont& accounts, T&& name, double amount)
{
    for(typename Cont::value_type& acc:accounts)
        if(acc->get_name()==name) {
            acc->withdraw(amount);
             std::cout<<"Withdraw Info: "<<*acc<<'\n';
            return true;
        }
        std::cout<<name<<" Not in the account list ..Sorry...\n";
        return false;
}

#endif // _MY_ACCOUNT_UTILIT_H