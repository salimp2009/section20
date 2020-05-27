#include <iostream>
#include <functional>

// Example of use std::function and lambdas

struct Foo {
  
    int number;
};

      int start_time()
        {
            return 5;
        }
        int end_timer()
        {
            return start_time()+7;
        }
        
        int my_algorithm(int a, int b)
        {
            return a*b;
        }
        
        int add(int a, int b) { return a+b;}
        int sub(int a, int b) {return a-b;}
        
        void execute_operation(int(*q)(int, int), int a, int b)
        {
            std::cout<<q(a,b)<<'\n';
        }

int main()
{
    execute_operation(add, 10, 20);
    execute_operation(sub, 30, 40);
    execute_operation([](int a, int b ) {return a*b;}, 4, 5 );
   
    auto l0=[] { std::cout<<"\nl0..\n"; };  // 
    auto l1=[] { std::cout<<"\nl1= "<<'\n';};
    auto l2=+[] { std::cout<<"function pointer..."<<'\n';};  // + sign in front of lambda expression converts 
                                                            // to a function pointer; no need to use another function pointer
    
    void(*p0)()=l0;             // p0 is a pointer to a function which is  the lambda function l0
                                // the lambda sohuld not be capturing anything from outside
                                
    p0();                       // we can call the function pointer as a regular function call
    
    p0=l1;                      // we can use the same pointer to point to another functions address as well 
    p0();                       // calling the reassigned pointer will call the new assigned function
    
    std::cout<<std::is_same<decltype(l0), decltype(l1)>::value<<'\n';   // checking if the type of lambda functions are same or not; they are not eqaul
                                                                        // even if both lambda function signatures are same the function assignment by auto will be different
                                                                        // this is because lambdas are created as anonymous structs by the compiler
    l2();
    
    std::cout<<std::is_same<decltype(l2), void(*)()>::value<<'\n';      // checking the type of l2 lambda expression with a function pointer
                                                                        // it gives both ar equal since we used + operator in front of lambda expression l2
 
    std::function<int(int, int)> f;      // std::function is a function wrapper; it can be assigned to any callable object 
                                        // as long as the signature of wrapper and object are same
    f=[](int a, int b) {return a/b;};    // in this example object should return an int and take two int arguments
    
    std::cout<<f(20,5)<<'\n';
    
    std::function<int(const Foo&)>g=&Foo::number; // function wrapper can also access a member function or data of any custom data types
    
    Foo foo{10};
    
    std::cout<<g(foo)<<'\n';                    // an instance of Foo is passed to g which will access to any member or member function

    std::cout<<g(Foo{5})<<'\n';                 // an instance of Foo can be directly constructed but the function argument should be const   

    g=nullptr;                                  // a function wrapper can be assigned to nullptr because it is a function pointer under the hood
                                                // std::function is not a zero overhead tool
    
    // Higher order functions taking functions                                           
    const auto call_twice=[](auto f)            // we can pass a function inside a lamda as an argument and call that function
    { f(); f();};                               // in the body of the lambda then assign the lamba to a variable with auto
                                                // to create a callable object and call that object by passing a function as an argument
    
    call_twice([](){std::cout<<"\ncalled twice...\n";});
    
    // Higher order functions returning functions
    const auto less_than=[](int x) 
    {
        return [x](int y) { return y<x;};
    };
    
    auto less_than_five=less_than(5);
    
    std::cout<<std::boolalpha;
    
    std::cout<<"\nis 3 less than 5: "<<less_than_five(3)<<'\n';
    std::cout<<"\nis 7 less than 5: "<<less_than_five(7)<<'\n';
    std::cout<<"is -5 less than 3: "<<less_than(3)(-5)<<'\n';
 
    // passing a function inside a lambda to test the time to execute that function
    const auto benchmark=[](auto f)
    {
        start_time();
        f();
        std::cout<<end_timer()<<'\n';
    };
    
    benchmark([]() {my_algorithm(100,200);} );          // passing algorithm into a stateless lambda
                                                        // the lambda inside benchmark is pass into another lambda as f
                                                        // where the timer starts first and the lambda with the algorithm is executed
                                                        // finally the timer is stopped
    std::function<int(int,int)>func=my_algorithm;                                                
   // benchmark(func(120,130));                         // error; the signature type of f inside benchmarks and function wrapper func does not match
    
    std::cout<<func(100, 150)<<'\n'; 
                                        
                                                        
 return 0;                              
                                
}