#include <iostream>
#include <string>


// Non type template parameters;
// Floating-point numbers and class-type objects 
// are not allowed as nontype template parameters:

// nontype template parameters carry some restrictions. 
// In general, they can be only constant integral values (including enumerations), 
// pointers to objects/functions/members, lvalue references to objects or functions, 
// or std::nullptr_t (the type of nullptr)

template<typename T, int N>
class Array {
    int size{N};          // size of array; known at compile time
    T values[N];          // create an array with N elements on the stack at compile time

friend std::ostream& operator<<(std::ostream& os, const Array<T,N> &arr) {
    os<<"[";
    for(const auto& val: arr.values)
        os<<val<<" ";
    os<<"]";
    return os;
}

public:
    Array()=default;
    Array(T init_val) {
        for(auto &item:values)
            item=init_val;
    }
    
    void fill(T val) {
        for(auto &item:values)
            item=val ;
    }
    
    int get_size() const {
        return size;
    }
    
    // overloaded subscript operator
    T& operator[](int index) {
        return values[index];
    }
};


int main()
{
    Array<int, 5>nums;
    std::cout<<"\nThe size of nums is "<<nums.get_size()<<'\n';
    std::cout<<nums<<'\n';
    
    nums.fill(0);
    std::cout<<"\nThe size of nums is "<<nums.get_size()<<'\n';
    std::cout<<nums<<'\n';
    
    nums.fill(10);
    std::cout<<nums<<'\n';
    
    nums[0]=200;
    nums[3]=300;
    std::cout<<nums<<'\n';
    
    Array<int, 100>nums2{1};
    std::cout<<"\nThe size of nums2 is"<<nums2.get_size()<<'\n';
    std::cout<<nums2<<'\n';
    
    Array<std::string, 10>strings(std::string("Salim"));
    std::cout<<"\nThe size of strings is "<<strings.get_size()<<'\n';
    std::cout<<strings<<'\n';
 
    strings[0]=std::string{"Sema"};
    std::cout<<strings<<'\n';
    
    strings.fill(std::string{"X"});
    std::cout<<strings<<'\n';

 
 return 0;
}