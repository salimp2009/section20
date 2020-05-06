#include <iostream>
#include <type_traits>
#include <functional>
#include <unordered_set>
#include <string_view>

template<typename...Bases>
struct Merged:Bases...
{
    template<typename... T>
    Merged(T&&... t):Bases(std::forward<T>(t))... {}
    using Bases::operator()... ;
};

template<typename... T>
Merged(T...) -> Merged<std::decay_t<T>...>;

class Customer
{
private:
    std::string name;
public:
    Customer(std::string nm): name{std::move(nm)} {}
    
    std::string getName() && {return std::move(name);}      // when we no longer need the object or the value we steal and return by value
    const std::string& getName() const& {return name;}      // normal access to member name; if the object is not about to die this is used safer & fast
};

struct CustomerEq
{
    bool operator() (Customer const& c1, Customer const& c2) const
    {
        return c1.getName() == c2.getName();
    }
};

struct CustomerHash
{
    std::size_t operator() (Customer const& c) const
    {
        return std::hash<std::string_view>{}(c.getName());
    }
};

template<typename... Bases>
struct Overloader:Bases...
{
    using Bases::operator()...;    // valid since C++17
};


int main()
{
    
    using CustomerOP=Overloader<CustomerEq, CustomerHash>;
    
    std::unordered_set<Customer, CustomerOP, CustomerOP> uset1{ {"Salim"}, {"Didem"}};
    
    for(const auto& p: uset1)
       // std::cout<<p.getName()<<" ";
       // printf("name: %s ", p.getName().data());        // getName() returns std::string printf( %s) gets pointer to an array of char*; options are to use data() or c_str()
        printf("name: %s ", p.getName().c_str()); 
    std::cout<<'\n';
    
    auto l1=[]() { return 45;};
    auto l2=[](const int i) {return i*10;};

    Merged merged {l1, l2, [](const double d) {return d*10.0;}};
    
    std::cout<<merged()<<'\n';
    printf("merged= %d\n", merged());
    
    printf("merged= %0.2f\n",  merged(10.0));
    printf("merged= %a\n", merged(10.0));
    
    return 0;
}
