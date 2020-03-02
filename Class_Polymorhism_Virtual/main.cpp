#include <iostream>
#include <vector>
#include <memory>


/* Virtual destructors must be used otherwise base pointers will 
// not be able identify will use base class destructor and will cause undefined behaviour 
// for base pointers pointing to derived classes
*/

/* Override specifier sholud be used for virtual functions 
// to make sure signatures of functions to match; 
// if the signatures of virtual functions dont match they will be statically bind
// if override specifier is used then compiler will warn if the signatures dont match; SO USE IT
*/

/* Final Specifier;
// if use after a class name ; that classed cannot be derived from
// if used after a function ; that function cannot be overriden
*/


class Account 
{
public:
    Account& operator=(const Account& other)=default;
    virtual void withdraw(double amount) {
        std::cout<<"Account: "<<amount<<'\n';
    }
    virtual ~Account(){std::cout<<"deleting Base Account..\n";};
};

class Savings_Account: public Account
{
public:
    Savings_Account()=default;
    virtual void withdraw(double amount) override {
        std::cout<<"Savings_Account: "<<amount<<'\n';
    }
    virtual ~Savings_Account() {std::cout<<"deleting Savings Account..\n";}
 
};

class Checking_Account: public Account
{
public:
    Checking_Account()=default;
    virtual void withdraw(double amount) override {
        std::cout<<"Checking Account: "<<amount<<'\n';
    }
    virtual ~Checking_Account(){std::cout<<"deleting Checking Account..\n";};
    
};

class Trust_Account: public Savings_Account
{
public:
    Trust_Account()=default;
    virtual void withdraw(double amount) override {
        std::cout<<"Trust Account: "<<amount<<'\n';
    }
   virtual ~Trust_Account(){std::cout<<"deleting Trust Account..\n";};
    
};

// example uses raw pointer for simplicty but DON' USE THEM IF YOU DONT HAVE TOO..

int main()
{
    Account a;
    Account &aa=a;
    aa.withdraw(1000);

    
    
    std::shared_ptr<Account> sp1=std::make_shared<Account>();
    std::shared_ptr<Account> sp2=std::make_shared<Savings_Account>();
    std::shared_ptr<Account> sp3=std::make_shared<Checking_Account>();
    std::shared_ptr<Account> sp4=std::make_shared<Trust_Account>();
    
    std::vector vec2={sp1, sp2,sp3,sp4};
    for(auto& i:vec2)    
        i->withdraw(550);
    std::cout<<'\n';

    Account* p1=new Account();
    Account* p2=new Savings_Account(); 
    Account* p3=new Checking_Account();
    Account* p4=new Trust_Account(); 
    
//    p1->withdraw(1000);
//    p2->withdraw(1500);
//    p3->withdraw(2000);
//    p4->withdraw(3000);
    
    Account* acc[]={p1,p2,p3,p4};
    
    for(auto&i :acc)
        i->withdraw(2200);
    std::cout<<'\n';
    
    std::vector<Account*>vec1={p1,p2,p3,p4};
    for(auto& i:vec1)    
        i->withdraw(3560);
    std::cout<<'\n';
      
      delete p1;
      delete p2;
      delete p3;
      delete p4;
    
    return 0;
}
