#include <iostream>
//#include <string>
#include <memory>
#include <vector>
//#include <initializer_list>
#include "Account.hpp"
#include <limits>

// basic class example 

// another example for perfect forwarding
// display function expects T&& but
// we use std::forward<T>() which allows us either to lvalue or rvalue
// the best case to use another function that has std::forward<> and call display function
// so we dont have to repeat it again 

template<typename T>
void display_Acc_name(const T&& acc)
{
    std::cout<<"Display function Account name: "<<acc.get_name()<<'\n';
}


int main()
{
    // Example for perfect forwarding using template function and std::forward<>()
    Account blank;
    display_Acc_name(std::forward<Account>(blank));
    display_Acc_name(std::forward<Account>({"Jedi", 200000}));
    
    
    std::string s1{"Semos_Account"};
    Account semos{s1};
    
    Account didos{"Didos_Account"};
    
    Account didem{didos};
    
    Account sema=semos;
    sema.set_name(s1);
    std::cout<<sema.get_name()<<", s1: "<<s1<<'\n';
    
    Account salims_acc;
    //std::cout<<"salim_acct with no arg constructor: "<<salims_acc.get_name()<<'\n';
    salims_acc.set_name("Salim");

    std::cout<<salims_acc.get_name()<<", balance: "<<salims_acc.get_balance()<<'\n';
    
    salims_acc.deposit(1000);
    std::cout<<salims_acc.get_name()<<", balance: "<<salims_acc.get_balance()<<'\n';
    
    std::cout<<std::boolalpha<<salims_acc.with_draw(1000.01)<<'\n';
    
    std::cout<<"machine epsilon: "<<std::numeric_limits<double>::epsilon()<<'\n';
    
    double draw_amount=salims_acc.get_balance()+std::numeric_limits<double>::epsilon();
    
    std::cout<<std::boolalpha<<salims_acc.with_draw(draw_amount)<<'\n';
    
    std::cout<<"\n------------------------------------------------\n";
    
    
    
//    std::unique_ptr<Player> Player1=std::make_unique<Player>("Salim", 100, 0);
//    std::unique_ptr<Player> Player2=std::make_unique<Player>("Demir", 100, 0);
//    Player1->display();
//    Player2->display();
//    Player1->walk();
//    Player2->talk("Hey watch out.!!!!");
//    
//    
//    std::vector<Player>my_buddies{Player{"Didem", 100, 8}};
//    
//    my_buddies.push_back(Player{"Sema"});
//    for(const auto& players: my_buddies)
//        players.display();
    return 0;
}
