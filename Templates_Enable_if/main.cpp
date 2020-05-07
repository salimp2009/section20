#include <iostream>
//
//// sum for integers
//template<typename T, typename=std::enable_if_t<std::is_integral_v<T>>>
//void sum(T a, T b) {
//    std::cout<<"Integer sum: "<<a<<" + "<<b<<"= "<<a+b<<'\n';
//}
//
//// will be used for float / double
//void sum(double a, double b) {
//    std::cout<<"Float sum: "<<a<<" + "<<b<<"= "<<a+b<<'\n';
//}


 //Alternative way to declare

template<typename Tint, 
         std::enable_if_t<std::is_integral<Tint>::value, int> = 0 >
void sum(Tint a, Tint b) {
    std::cout<<"Integer sum: "<<a<<" + "<<b<<"= "<<a+b<<'\n';
}

template<typename Tfloat, 
        std::enable_if_t<std::is_floating_point<Tfloat>::value, int> = 0 >
void sum(Tfloat a, Tfloat b) {
    std::cout<<"Floating sum: "<<a<<" + "<<b<<"= "<<a+b<<'\n';
}




int main()
{
    ::sum(3,4);
    ::sum(3.2, 3.4);
    
    return 0;
}
