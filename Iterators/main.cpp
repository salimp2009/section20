#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <iterator>
#include <algorithm>

void display(const std::vector<int>& vec) {

    std::cout<<"\[";
    for(const auto& v:vec)
        std::cout<<v<<" ";
    std::cout<<"]\n";
}

void test1() {  
    std::cout<<"\n============================\n";
    std::vector<int>nums{1,2,3,4,5};
    auto it=nums.begin();           // point to first element 
    std::cout<<*it<<'\n';           
    
    ++it;                          // points the next element
    std::cout<<*it<<'\n';
    
    std::cout<<*(it+1)+3<<'\n';
    
    it=nums.end()-1;
    std::cout<<*it<<'\n';
    
    nums.insert(nums.begin()+2, {10,20,30});  //Inserts a copy of all elements of the 
                                              //initializer list initlist before 
                                              // iterator position pos and returns the 
                                              //position of the first new element 
                                              // (or pos if there is no new element; since C++11)
    
    display(nums);
    
    std::cout<<"Capacity: "<<nums.capacity()<<'\n';   //the maximum possible number of elements 
                                                      //without reallocation
                                                      
    std::cout<<"Max size: "<<nums.max_size()<<'\n';   //maximum number of elements possible
    
    nums.reserve(100);
    std::cout<<"Capacity after reserve(100): "<<nums.capacity()<<'\n';
    
    nums.shrink_to_fit();
    std::cout<<"Capacity after .shrink_to_fit(): "<<nums.capacity()<<'\n';
    
 }

void test2() {
    std::cout<<"\n=============Test 2==============\n";
    
    std::vector<int>nums1{1,2,3,4,5};
    
    std::vector<int>::iterator it=nums1.begin();
    while(it!=nums1.end()) {
        std::cout<<*it<<" ";
        ++it;
    }
    std::cout<<'\n';
    
    
    for(it=nums1.begin(); it!=nums1.end(); ++it)
        *it=0;
    
    display(nums1);
    
    
}

void test3() {
    std::cout<<"\n=========Test 3===========\n";
    
    std::vector<int>nums1{1,2,3,4,5};
    
    // auto it1=nums1.cbegin();                         // alternative way for a const iterator
    std::vector<int>::const_iterator it1=nums1.begin();
    
    while(it1!=nums1.end()) {
        std::cout<<*it1<<'\n';
        ++it1;
    }
    
//    Compile error; it1 is a pointer to const; the value cannot be changed 
//    for(it1=nums1.begin(); it1!=nums1.end(); ++it1)
//        *it1=0; 
//        
    
}

void test4() {
    std::cout<<"\n=========Test 4===========\n";
    
    std::vector<int>nums1{1,2,3,4};
    
   for(auto it2=nums1.rbegin(); it2!=nums1.rend(); ++it2)       // reverse iterator
       std::cout<<*it2<<" "<<'\n';
   std::cout<<'\n';
   
   std::list<std::string>names{"Salim", "Didem", "Sema", "Demir"};
   
   for(auto it3=names.crbegin(); it3!=names.crend(); ++it3)       // const reverse iterator; pointer to a const element 
        std::cout<<*it3<<'\n';
    std::cout<<'\n';
    
    std::map<std::string, std::string> favorites {              // map sorts the elements; no duplicates allowed
        {"Salim", "C++"},                                       // multimaps allows duplicate elements
        {"Demir", "Gamer"},
        {"Sema", "Mom"},
        {"Didem", "Awsome"}
    };
    
    for(auto it4=favorites.begin(); it4!=favorites.end(); ++it4)
        std::cout<<it4->first<<" "<<it4->second<<'\n';
    std::cout<<'\n';    
        
}

void test5() {
    std::cout<<"\n=========Test 5===========\n";
    std::vector<int>nums1{1,2,3,4,5,6,7,8,9, 10};    
    
    // iterate over a substrate of the container
    auto start=nums1.begin()+2;
    auto finish=nums1.end()-2;

    while(start!=finish) {
        std::cout<<*start<<'\n';
        ++start;
    }
    std::copy(start, finish, 
              std::ostream_iterator<int>(std::cout, "\n") );   // ostream,-iterator
    
}

int main()
{
//   test1();
//   test2();
//   test3();
//   test4();
     test5();

 return 0;
}