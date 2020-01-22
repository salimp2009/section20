#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <algorithm>

// lambda's are function object that are anonymous types
// if the type of the lambda is required than decltype can be used such as in 
// sorting criterion in associative containers
// when they are assigned to an object they are assigned with unique names
// a typical lambda has a similar structh like the class below
class My_lambda
{
private: 
    int id;             // this is the same as if lambda captures from outside by value
public:
    My_lambda(int n): id{n} { }
    void operator()(int x, int y)  {            // if a lambda is mutable (if not there should const specifier)
        std::cout<<"\n....Printing My_lambda.....\n";
        std::cout<<"id: "<<id<<", x: "<<x<<", y: "<<y<<'\n';
        ++id;
    }

};

// Example to try capturing the class member
// capturing a member either by value or reference will give a compiler error
// class member can be captured by this 
// Before C++17 capturing by value using *this was not possible
// C11 and C14 you had to use =, & which captures the pointer either by value or ref but this means
// that you have direct access class member not a copy therefore not recommended
// to capture by value in C++11 or 14 the only way is [mycopy=*this] 
struct MyBase
{
    MyBase(const std::string& str): s{str} { }
    void foo() {
        auto lam=[*this](){std::cout<<"Print class member: "<<s<<'\n';};
        lam();
    }
    
    std::string s;
};


int my_global{45};

// for example lambdas converted to a function pointer if they donot capture
// and the return-parameter types match
void print10(void(*bar)(int x))
{
    bar(10);
}

void print10_50(std::function<void(int x)> bar)
{

    bar(10);
}

// if these two overloads are passed into STL algorithm as predicate
// then we get compiler error; to pass we can use a generic lambda
// that will forward the passed argument to foo and compiler will decide which one to use than 
void foo(int x){ std::cout<<"foo_int x: "<<x<<'\n';}
void foo(double x){ std::cout<<"foo_double x: "<<x<<'\n';}

// Alternative to solve above problem : Macro for Generic Lambda w/ std::forward
// this solution is called as full LIFT
#define LIFT(foo) \
    [](auto&&...x) \
     noexcept(noexcept(foo(std::forward<decltype(x)>(x)...))) \
     ->decltype(foo(std::forward<decltype(x)>(x)...)) \
     {return foo(std::forward<decltype(x)>(x)...);}


int main()
{
    // Example two overloads in STL example w/ generic lambda
    std::vector<int>vec_int{10,20,35,66};
    
    // this gives compiler error due to two overloads cannot be resolved
    //std::for_each(vec_int.begin(), vec_int.end(), foo);
    
    // solution to above proble; use a lambda to returns foo() so overloading will work
    // Alternative way is to write a generic macro with lambda & std::forward
    std::for_each(vec_int.begin(), vec_int.end(), [](auto x){return foo(x);});
    
    std::for_each(vec_int.begin(), vec_int.end(), LIFT(foo));
    
    //example lambdas converted to a function pointer if they donot capture
    print10([](int x){ std::cout<<"Print_10 Lambda x: "<<x<<'\n';});
   
    // if capture is used 
    print10_50([=](int x){ std::cout<<"Print10_50 Lambda x: "<<x<<'\n';});
    
    MyBase("Salim").foo();
    
    My_lambda l(5);
    l(2,3);
    l(2,3);
    
    // you can specify return type by -> operator
    auto l1=[]()->double{ return 42;};
    
    std::cout<<l1()<<'\n';
    
    // typical lambda options and struct
    // [=, &] (T x, T y) mutable throw -> { };
    // = means outer scope is passed to lambda by value
    // & means outer scope is passed to lambda by reference
    // the T x, T y are temporary values that can be passed from the functions
    // thru operator()(T x, T y)
    
    // a lambda can be passed to an object or can be called directly 
    [](){std::cout<<" i am the lamda function :)\n";}();
    
    int x{0};
    int y{42};
    
    // x is captured by calue and y is captured by reference
    // mutable allows lambda to change the variable captured by value
    // if catpured by value variable is changed in lambda 
    // it will only effecct the value inside the lambda, the variable 
    // in the main function remains unchanged since it is captured by value only
    // if mutable is not used lambda cannot change the variable capturef by value
    auto l2=[x, &y]()mutable{ 
                      std::cout<<"x: "<<x<<", y: "<<y<<'\n';
                        ++y; ++x;};
    // changing the values after the lambda captured
    x=y=77;
    
    // call lambda twice 
    l2();                                               // prints x=0, y=78
    l2();                                               // print  x=1, y=79
    
    std::cout<<"final y: "<<y<<", final x: "<<x<<'\n';  // prints x=77, y=79     
    
    // Example for attempting to capture a Global Value but give compiler error
    // Lambdas can capture only automatic storage object ; no static no global values possible
    
//    auto l3=[my_global](int x){std::cout<<"Capturing Global value: "<<my_global<<", x: "<<x<<'\n';};
//    l3(5);

    // Example for capturing a movable only object in a lambda
    // unique ptr cannot be copied the only way to capture is by reference
    // when captured by reference the ownership is not transferred unless 
    // returned with std::move() then the ownership is transferred
    std::unique_ptr<int>u_ptr{new int(10)};
    auto l4=[&u_ptr](int x){ 
                        std::cout<<" Printing unique pointer value: "<<*u_ptr<<'\n';        // pthe original value of the pointer
                        *u_ptr=x;                                                           // changing the value of pointer (captured by reference)
                        std::cout<<" Printing unique pointer value: "<<*u_ptr<<'\n';        // revised value of the pointer
                        return std::move(u_ptr);};                                          // unique_ptr can be moved only  
    
    auto u2_ptr=l4(20);
    std::cout<<" Printing unique pointer value: "<<*u2_ptr<<'\n'; 
    *u2_ptr=456;                                                                            // the owner ship of original ptr is moved to new one
    std::cout<<" Printing unique pointer value: "<<*u2_ptr<<'\n'; 
 //   std::cout<<" Printing unique pointer value: "<<u_ptr<<'\n';                             // original ptr is no more valid ; Dont use it
   
    int xx{25};
    int yy{50};
    
    // we can capture-initialize parameter; xx & yy are captured by value to initialize a new
    // variable z; notice the type info of z is not specified (if you want to specify compiler give error)
    auto l6=[z=xx+yy](){std::cout<<"Capture_initialize z: "<<z<<'\n';};
    
    // we create z variable with an initial value 20 and 
    // also the passed argument (int x) has a default value of 10; if not given any value it uses 10
    auto l5=[z=20](int x=10){std::cout<<"Capture_initialize x+z: "<<x+z<<'\n';};
    
    l5();
    l5(60);
    l6();
    return 0;
}
