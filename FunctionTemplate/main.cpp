#include <iostream>
#include <string>

// Function Templates

template<typename T>
T min(T a, T b) {
    return (a<b) ? a:b;
}

template<typename T1, typename T2> 
void funct(T1 a, T2 b) {
    std::cout<<a<<" "<<b<<'\n';
}


struct Person {
    std::string name{};
    int age{};  
    bool operator<(const Person& rhs) {
        return this->age < rhs.age;
    }
    
};

 std::ostream& operator<<(std::ostream& os, const Person& p) {
         os<<p.name<<" "<<p.age;
         return os;
 }  

template<typename T>
void my_swap(T& a, T& b) {
    T temp{std::move(a)};
    a=std::move(b);
    b=std::move(temp);
}      


int main()
{
    int x{100};
    int y{50};
    my_swap(x,y);
    std::cout<<"\nx: "<<x<<" y: "<<y<<'\n';
    
    Person p1{"Salim", 46};
    Person p2{"Demir", 12};
    
    Person p3=min(p1, p2);
    
    std::cout<<p3.name<<" "<<p3.age<<'\n';
    
    funct(p1, p2);
    
    std::cout<<min<int>(2,3)<<'\n';
    std::cout<<min(2,3)<<'\n';
    std::cout<<min('A','B')<<'\n';
    std::cout<<min(12.5, 9.2)<<'\n';
    std::cout<<min(5+2*2, 7+40)<<'\n';
    
    funct(10, 20);
    funct<int, int>(20,20);
    funct<char, double>('A', 12.4);
    funct('A',12.4);
    funct(1000,"Testing");
    funct(2000, std::string{"Frank"});
    

 
 return 0;
}