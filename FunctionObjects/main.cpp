#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

class AddValue
{
private:
    int value{};
public:
    // constructor
    AddValue(int value): value{value} {}
    
    // function call to add Value to argument passed on by the iterator
    void operator() (int& elem) const {
      elem+=value;
    }
    ~AddValue()=default;
};

int main()
{

    
    std::list<int> ls{1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    std::cout<<"\nOriginal list: \n";
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';
    
    std::for_each(ls.begin(), ls.end(),
                  AddValue(20));
    
    std::cout<<"\nRevised list: Added value ;\n";              
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';
    
     
     std::for_each(ls.begin(), ls.end(),
                  AddValue(*ls.begin()));
    
    std::cout<<"\nRevised list: Added first element;\n";              
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';
 
 
    std::for_each(ls.begin(), ls.end(),
                  AddValue(*(--ls.end())));             // ls.end(); referes to position past the last element
                                                        // if we need to access the last element than we need
                                                        // position before ls.end(); --ls.end() 
                                                        // or we can use ls.rbegin() ; reverse begin which is the last element
    std::cout<<"\nRevised list: Added last element; --ls.end()\n";              
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';
    
    std::for_each(ls.begin(), ls.end(),
                  AddValue(*ls.rbegin()));            // or we can use ls.rbegin() ; reverse begin which is the last element
    
     std::cout<<"\nRevised list: Added last element ls.rbegin() ;\n";              
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';

    AddValue addx{25};
    AddValue addy{30};
  
    std::for_each(ls.begin(), ls.end(),
                  addx);
    
    std::for_each(ls.begin(), ls.end(),
                  addy);              
    
    std::cout<<"\nRevised list: Added addx{25} and addy{30} objects of class AddValue ;\n";              
    for(const auto& l:ls)
        std::cout<<l<<" ";
    std::cout<<'\n';
    
 return 0;
}