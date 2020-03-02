#include <iostream>
#include <vector>
#include <memory>

#include "Account_Utility.h"
#include "Account.h"
#include "Savings_Account.h"
#include "Checking_Account.h"
#include "Trust_Account.h"

class Test
{
private:
    int data{};
public:
    Test(): data{0} 
            {std::cout<<"\nTest constructor ("<<data<<")\n";}
    Test(int data): data{data}
            {std::cout<<"\nTest constructor ("<<data<<")\n";}
    int get_data() const{ return data;}
    ~Test() {std::cout<<"\nTest destructor ("<<data<<")\n";}
};

void func(const std::shared_ptr<Test> p)
{
    std::cout<<"\npointer value :"<<(p->get_data())<<'\n'; 
    std::cout<<"Use count: "<<p.use_count()<<'\n';
}

int main()
{
//    std::shared_ptr<int>p1{new int{100}};
//    std::cout<<"\nUse count p1: "<<p1.use_count()<<'\n';
//    std::cout<<"p1: "<<(*p1)<<'\n';
//    
//    std::shared_ptr<int>p2{p1};
//    std::cout<<"\nUse count p1 : "<<p1.use_count()<<'\n';
//    std::cout<<"p2: "<<(*p2)<<'\n';
//    
//    p1.reset();
//    std::cout<<"\nUse count p1: "<<p1.use_count()<<'\n';
//    std::cout<<"\nUse count p2: "<<p2.use_count()<<'\n';

//      std::shared_ptr<Test>ptr=std::make_shared<Test>(10);
//      std::cout<<"\nptr: "<<(ptr->get_data())<<'\n';
//      std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';
//      func(ptr);
//      
//      std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';
//      
//      {
//          std::shared_ptr<Test>ptr1{ptr};
//          std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';
//          {
//            std::shared_ptr<Test>ptr2{ptr};
//            std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';
//            ptr.reset();
//          }
//         std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';
//      }
//      
//      std::cout<<"ptr use count: "<<ptr.use_count()<<'\n';

    
    std::cout<<"\n===============Shared Pointer-Accounts=====================\n";

    std::shared_ptr<Account>acc1=std::make_shared<Savings_Account>("Salim", 6000, 5);
    std::shared_ptr<Account>acc2=std::make_shared<Checking_Account>("Sema", 8000);
    std::shared_ptr<Account>acc3=std::make_shared<Trust_Account>("Didem", 10000, 8);
 
    std::vector<std::shared_ptr<Account>>accounts;
    accounts.push_back(acc1);
    accounts.push_back(acc2);
    accounts.push_back(acc3);
    
    for(const auto&  acc:accounts) {
        std::cout<<(*acc)<<'\n';
        std::cout<<"acc Use count: "<<acc.use_count()<<'\n';
    }
     
    std::cout<<"\n===============Shared Pointer-Revised Accounts=====================\n";
    
    acc1->deposit(1000);
    acc2->withdraw(500);
    acc3->deposit(6000);
    
    for(const auto&  acc:accounts) {
        std::cout<<(*acc)<<'\n';
        std::cout<<"acc Use count: "<<acc.use_count()<<'\n';
    }
    
    std::cout<<'\n';
//    std::shared_ptr<Account>a2=std::make_shared<Trust_Account>("Salim", 10000, 9);
//    std::shared_ptr<Account>a3{a2};
//    std::cout<<(*a3)<<'\n';
//    std::cout<<"\n a2 use count: "<<a2.use_count()<<'\n';
//     a2->withdraw(1000);
//    std::cout<<(*a2)<<'\n';
//    a2.reset();
//    std::cout<<"\n a3 use count: "<<a3.use_count()<<'\n';


 return 0;
}