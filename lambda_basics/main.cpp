#include <iostream>
#include <functional>

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

int main()
{
    
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
    
    
    return 0;
}
