#include <iostream>
#include  "Account.hpp"
#include "Savings_Account.hpp"
#include "Checking_Account.hpp"
#include "Trust_Account.hpp"
#include <iomanip>
#include <initializer_list>
#include "Account_Utility.hpp"

void hexafloat_list() {
/*      example for floating point decimals in C++17;  
//  0xAp2 is a way to specify the decimal value 40 (10 multiplied by “2 to the power of 2”). 
//    The value could also be expressed as 0x1.4p+5, which is 1.25 multiplied by 32 
//    (0.4 is a hexadecimal quarter and 2 to the power of 5 is 32).
*/

    std::initializer_list<double> values {
        0x1p4, 0xA, 0x1.4p+5, 0xAp2, 5e0, 0x1.4p+2, 1e5, 0x1.86Ap+16, 0xC.68p+2, 0x1.4p+5, 
    };
    
    for (double d: values) {
        std::cout<<"dec: "<<std::setw(6)<<std::defaultfloat<<d
                 <<", hexfloat: "<<std::hexfloat<<d<<'\n';
    }
}

class Base {
public:
    Base():x{0} { std::cout<<x<<", Base no-args constructor..\n"; }
    Base(int xx): x{xx} {std::cout<<x<<", Base constructor..\n";}
    Base(const Base& other): x{other.x}{std::cout<<x<<"Base copy constructor..\n";}
    
    Base& operator=(const Base& rhs) {
            if(this!=&rhs) x=rhs.x;
            std::cout<<x<<"Base Copy Assignment..\n";
            return *this; }
    ~Base() {std::cout<<"Base Destructor....\n";}
    
private:
    int x;
};

class Derived: public Base {
public:
    Derived(): Base{}, doubled_value{0} {std::cout<<doubled_value<<", Derived no-args constructor..\n";}
    Derived(int value): Base{value}, doubled_value{2*value} {std::cout<<doubled_value<<", Derived constructor..\n";}
    Derived(const Derived& other): Base{other}, doubled_value{other.doubled_value}
                                    {std::cout<<doubled_value<<"Derived Copy constructor..\n";}
                                    
    // if a copy assignment is defined in Derived class then we need to provide
    // a copy assingment in Base class as well and call it from the Derived assignment
    // otherwise the Base part of the derived will not be copy-assigned
    // but if we dont define a copy assignment in derived class then compiler
    // will create base class copy assignment and call it for the derived automatically
    Derived& operator=(const Derived& rhs)  {
        if(this==&rhs) return *this;
        
        Base::operator=(rhs);
        doubled_value=rhs.doubled_value;
        std::cout<<doubled_value<<"Derived Copy Assignment..\n";
        return *this;}
    ~Derived() {std::cout<<"Derived Destructor...\n";}
    
private:
 int doubled_value;
};

int main()
{
 //   hexafloat_list();
 
//    Base b1{100};
//    Base b2{b1};
//    b1=b2;
        
//    Derived d1{100};
//    Derived d2{d1};
//    d1=d2;

    Account salim_base{"Salim", 1000};
    Savings_Account salim_saving{"Salim Saving", 10000};
    
    salim_base.deposit(1000);
    salim_saving.deposit(5000);
    
    salim_saving.withdraw(7000);
    
    std::cout<<salim_saving<<'\n';
    std::cout<<salim_base<<'\n';
    
    salim_saving.withdraw(9000);
    std::cout<<salim_saving.get_name()<<'\n';
//    
//    std::vector<Account>acc_list;
//    acc_list.reserve(20);
//    
//    acc_list.emplace_back("Demir", 2000);
//    acc_list.emplace_back("Sema", 5000);            
//    acc_list.emplace_back(std::move(salim_base)); 
//   
//    //std::cout<<salim_base<<'\n';   // just to see the effect of the std::move
//    display(acc_list);
//    
//    deposit(acc_list, "Demir", 25000);
//    display(acc_list);
//    
//     withdraw(acc_list, "Salim", 255);
//     display(acc_list);
//    
//    withdraw(acc_list, "xxxxx", 255);
//    deposit(acc_list, "xxxxx", 255);
//    
//    display(acc_list);
//    
//    std::cout<<"\n------------SAVING ACCOUNT INFO----------------\n";
    
//    std::vector<Savings_Account>saving_list;
//    saving_list.reserve(20);
//    
//    saving_list.emplace_back("Demir", 2000);
//    saving_list.emplace_back("Sema", 5000);            
//    saving_list.emplace_back(std::move(salim_saving)); 
//    
//    display(saving_list);
//    deposit(saving_list, "Demir", 25000);
//    display(saving_list);
//    
//    withdraw(saving_list, "Salim Saving", 255);
//    display(saving_list);
//    
//    withdraw(saving_list, "xxxxx", 255);
//    deposit(saving_list, "xxxxx", 255);
 
 
// std::cout<<"\n------------CHECKING ACCOUNT INFO----------------\n";
//    
//    std::vector<Checking_Account>checking_list;
//    checking_list.reserve(20);
//    Checking_Account salim_checking{"Salim Checking", 4500, 1.8};
//    
//    salim_checking+=500;
//    salim_checking-=1000;
//    std::cout<<salim_checking<<'\n';
//    
//    
//    checking_list.emplace_back("Demir", 2000);
//    checking_list.emplace_back("Sema", 5000);            
//    checking_list.emplace_back(std::move(salim_checking)); 
//    
//    std::cout<<"Salim Checking after the move: "<<salim_checking<<'\n';
//    
//    display(checking_list);
//    deposit(checking_list, "Demir", 25000);
//    display(checking_list);
//    
//    withdraw(checking_list, "Salim Checking", 255);
//    display(checking_list);
//   
//    withdraw(checking_list, "xxxxx", 255);
//    deposit(checking_list, "xxxxx", 255);
    
    std::cout<<"\n------------TRUST ACCOUNT INFO----------------\n";
    
    std::vector<Trust_Account>trust_list;
    trust_list.reserve(20);
    Trust_Account salim_trust{"Salim Trust", 4500};
    
    salim_trust+=500;
    salim_trust-=1000;
    std::cout<<salim_trust<<'\n';
//    
    
    trust_list.emplace_back("Demir", 2000);
    trust_list.emplace_back("Sema", 5000);            
    trust_list.emplace_back(std::move(salim_trust)); 
    
    std::cout<<"Salim Checking after the move: "<<salim_trust<<'\n';
    
    display(trust_list);
    deposit(trust_list, "Demir", 25000);
    display(trust_list);
    
    withdraw(trust_list, "Salim Trust", 255);
    withdraw(trust_list, "Salim Trust", 255);
    withdraw(trust_list, "Salim Trust", 255);
    display(trust_list);
   
    withdraw(trust_list, "xxxxx", 255);
    deposit(trust_list, "xxxxx", 255);
    
    
    return 0;
}
