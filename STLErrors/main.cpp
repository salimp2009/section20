#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    
    std::vector<int>coll1 {1,2,3,4,5};
    std::vector<int>::iterator pos=coll1.begin();
    std::reverse(++pos, --coll1.end());               // start reversing from past the beginning to befor the end
                                                      // result is= 1, 4, 3, 2, 5 ; first and last element not reversed
    std::cout<<"\nCollection1: \n";                  // in the STL book this is given as Runtime error but it did not ??
    for(const auto& c:coll1)
        std::cout<<c<<" ";
        

    std::cout<<"\nPlease enter the values for v2: ";
    
//    std::vector<int>v2 ((std::istream_iterator<int>(std::cin)),  // if () is used to initialize then extra paranth.() needed aroud istream..
//                        (std::istream_iterator<int>()) );
    
    std::vector<int>v2 {std::istream_iterator<int>(std::cin),   // if {} initializer list is used; no need for parant
                        std::istream_iterator<int>() };
    
    std::cout<<"\nValues for v2: ";
    for(const auto& v:v2)
        std::cout<<v<<" ";
    
    std::cout<<'\n';
    

 
 return 0;
}