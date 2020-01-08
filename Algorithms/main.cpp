#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cctype>
#include <string>
#include <iterator>


class Person {
    std::string name;
    int age;
    
public:
    Person()=default;
    Person(std::string name, int age):name{std::move(name)}, age{age} { }
    bool operator<(const Person& rhs) const {
        return this->age<rhs.age;
    }
    
    bool operator==(const Person& rhs) const {
        return this->name==rhs.name && this->age==rhs.age;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p)
    {
         os<<"Name: "<<p.name<<" Age: "<<p.age<<'\n';
         return os;
    }
};

void find_test() {
    std::cout<<"\n==============find_test=============\n";
    
    std::vector<int> vec{1,2,3,4,5};
    
    std::cout<< *begin(vec)<<'\n'; // std::begin(vec) and begin(vec) both compiles
                                   // C++ has a feature argument dependant lookup
                                   // which looks up the namespace of the surroundings and argument
                                   // this may also cause calling a function of same within a different namespace
                                  
    auto pos=std::find(vec.begin(), vec.end(), 1);
    
    if(pos!=vec.end())
        std::cout<<"\n Found the number: "<<*pos<<'\n';
    else
        std::cout<<"\n The number not found...\n";
        
    std::cout<<'\n';
    
    std::list<Person> players{
        {"Salim",46},
        {"Didem",45},
        {"Sema", 65}
    };
    
    auto pos1=std::find(players.begin(), players.end(), Person{"Sema", 65});
    if(pos1!=players.end())
        std::cout<<"\nFound player..."<<*pos1<<'\n';
    else
        std::cout<<"\nPlayer not found...\n";
    
    std::cout<<'\n';
}

void count_test() {
    std::cout<<"\n==============count_test=============\n";
    std::vector<int>vec{1,2,3,4,5,1,2,1};
    
    int num=std::count(vec.begin(), vec.end(), 1);  // counts the number of occurences
                                                    // of a given number within the range
    std::cout<<"\nNumber of 1 in vec: "<<num<<'\n';
}

void count_if_test() {
     std::cout<<"\n==============count_if_test=============\n";
     std::vector<int>vec{1,2,3,4,5,1,2,1, 100};
     int even_num=std::count_if(vec.begin(), vec.end(), 
                         [](int x) { return x%2==0; } );
                         
     int odd_num=std::count_if(vec.begin(), vec.end(),
                                [](int x){ return x%2!=0;});
                                
    std::cout<<"\nTotal Even numbers: "<<even_num
             <<"\nTotal Odd numbers: "<<odd_num<<'\n';
             
   int num=5;
   int greater_num=std::count_if(vec.begin(), vec.end(),
                                 [num](int x) {return x>=num;});  // lambda captures local variable num by value
                                                                  // if capture by reference is needed; use &num
   std::cout<<greater_num<<" occurences greater/equal than "<<num<<'\n';
   
   std::cout<<'\n';
}

void replace_test() {
    std::cout<<"\n==============replace_test=============\n";
    std::vector<int>vec{1,2,3,4,5,1,2,1, 100};
    
    for(const auto& v: vec)
        std::cout<<v<<" ";
    std::cout<<'\n';
    
    std::replace(vec.begin(), vec.end(), 1, 300);  // replace all elements==1 with 300 within the range
    for(const auto& v: vec)
        std::cout<<v<<" ";
    std::cout<<'\n';
    
    std::replace_if(vec.begin(), vec.end(),
                    [](int x){ return x>=5;}, 250);   // replace all elements>=5 with 250 within range
    for(const auto& v: vec)
        std::cout<<v<<" ";
    std::cout<<'\n';
    
}

void all_of_test() {
    std::cout<<"\n==============all_of_test=============\n";
    std::vector<int>vec1{1,3,5,7,10,1,3,15,17,5};
    if(std::all_of(vec1.begin(), vec1.end(), [](int x){return x>=10;}) )
        std::cout<<"\nAll elements are >=10\n";
    else 
        std::cout<<"\nNot all elements are >=10\n";
    
    if(std::all_of(vec1.begin(), vec1.end(), [](int x){return x<20;}) )
        std::cout<<"\nAll elements are <20\n";
    else
        std::cout<<"\nNot all elements are <20\n";
    
    std::cout<<'\n';
}

void      string_transform_test() {
    std::cout<<"\n==============all_of_test=============\n";
    std::string s1{"this is a test"};
    
    std::transform(s1.begin(), s1.end(),
                    s1.begin(),
                   ::toupper);  //::toupper is same as using [](unsigned char s) {return std::toupper(s);}
                                // :: is a global scope resolution
    std::cout<<s1<<'\n'; 
}

int main()
{
//    find_test();
//    count_test();
//    count_if_test();
//    replace_test();
//    all_of_test();
 //  string_transform_test();
 
// Example for C style array iterators
 int array1[5]={5,2,1,4,5};
 
 // iterator pointers to the beginning and pass the end of array 
 // std::sort() uses end iterator pass behing the last element
 int *pbegin = &array1[0];
 int *pend   = &array1[5];
 
 // pointer to pointer example; needed this specific example
 // to see if std::sort() will work passing array and 
 // custom predicate sort function thru lambda
 int **pbegin_alt=&pbegin;
 int **pend_alt=&pend;
          

// std::sort(std::begin(array1), std::end(array1), [](int x, int y){ return x<y; });  // works OK
// std::sort(pbegin, pend, [](int x, int y){ return x<y; });  
std::sort(*pbegin_alt, *pend_alt, [](int x, int y){ return x>y; });                               // alternative way to do it
 
 for(const auto& x: array1)
     std::cout<<"x: "<<x<<", ";
 std::cout<<'\n';
 

 return 0;
}