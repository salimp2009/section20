#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>


// partition_copy divides the collection into towo part as defined in the predicate option
// and copies into two seperate containers

int main()
{
    
    std::vector<int>numbers{1,255,65,13,4,6,12,24,5,2,7,8,9,24,46,55};
    
    std::vector<int>even_numbers{};
    std::vector<int>odd_numbers{};
    
    std::partition_copy(numbers.begin(), numbers.end(),                                     // the original container/collection
                      std::back_inserter(even_numbers), std::back_inserter(odd_numbers),    // the destination containers    
                      [](int i){ return i%2==0;});                                          // partitioning criteria
                       
   
    //Printing the partioned collection in the desitination containers
    std::cout<<"Even numbers\n";
    for(const auto& num:even_numbers) 
        std::cout<<num<<" ";
    
    std::cout<<"\nOdd numbers\n";
    for(const auto& num:odd_numbers) 
        std::cout<<num<<" ";
    std::cout<<'\n';
    return 0;
}
