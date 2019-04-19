#include <iostream>
#include <set>
#include <deque>
#include <functional>
#include <algorithm>
#include <iterator>

// STL Binders & Rotate Algorithm

int main()
{
    std::set<int, std::greater<int>>coll1 {1,2,3,4,5,6,7,8,9};                  // greater<> predefined function used to list from larger value to small
    std::deque<int>coll2;                                                       // the default sort for set is less<>; from smaller to larger 
    
     std::copy(coll1.cbegin(), coll1.cend(),
             std::ostream_iterator<int>(std::cout<<"\nCollection1: ", " ") );   // ostream_iterator<>() used to send the input from coll1 to output stream
 
    std::cout<<'\n';

    // multiply coll1 by a given number(e.g; 10) and insert it into coll2
    std::transform(coll1.begin(), coll1.end(),
                    std::back_inserter(coll2),
                    std::bind(std::multiplies<int>(), std::placeholders::_1, 10)
                    );

    for(const auto& c:coll2)
        std::cout<<"\n\tCollection2: "<<c<<" ";

    // replace value 70 with 42    
    std::replace_if(coll2.begin(), coll2.end(),
                    std::bind(std::equal_to<int>(),std::placeholders::_1, 70), // std::placeholders::_1 is used to indicate the value is expected; from iterator 
                    42 );                                                      // then the value is passed into equal_to<>() function with the other value to be compared     
     std::cout<<"\nCollection2 replaced 70 with 42: ";               
    for(const auto& c:coll2) 
        std::cout<<c<<" ";
  
    std::cout<<'\n';
   
    // remove values between 50 & 80 and return new end position to erased the removed data
    // Note: remove_if does not erase the data, it removed from collection but needs to be erased
    // erase and remove_if can be combined or seperatered by using auto pos= remove_if(....) which gives the new end
    // erase deletes removed data starting from the new end (pos) to old end coll2.end()
    coll2.erase(std::remove_if(coll2.begin(), coll2.end(),
                    std::bind(std::logical_and<bool>(),                                         // the outer bind is used to to bind a function with the results of the other binds
                        std::bind(std::greater_equal<int>(), std::placeholders::_1, 50),        // to provide a predicate for remove_if algorithm
                        std::bind(std::less_equal<int>(), std::placeholders::_1, 80) ) ), 
                coll2.end() );
      
    std::cout<<"\nValues including between 50 & 80 removed...\n";    
    std::copy(coll2.cbegin(), coll2.cend(),
            std::ostream_iterator<int>(std::cout<<"\nCollection 2: ", " ") );
 
    // Rotating 
    std::rotate(coll2.begin(),                                    // old begin
              coll2.begin()+2,                                  // new begin
              coll2.end() );                                    // end 
    std::cout<<"\nValues rotated from old begin+2...\n";    
    std::copy(coll2.cbegin(), coll2.cend(),
            std::ostream_iterator<int>(std::cout<<"\nCollection 2 rotated : ", " ") );
 
    // Rotating  from the end           
    std::rotate(coll2.begin(),                                 // old begin
              coll2.end()-2,                                   // new begin= old end-2
              coll2.end() );                                   // end 
    std::cout<<"\nValues rotated from old end-2...\n";    
    std::copy(coll2.cbegin(), coll2.cend(),
            std::ostream_iterator<int>(std::cout<<"\nCollection 2 re-rotated : ", " ") );
  
    // Rotating  using find for the new begin           
    std::rotate(coll2.begin(),                                  // old begin
              std::find(coll2.begin(), coll2.end(), 20),        // the new begin is from the position of the value 20;  find returns position of 20                           // new begin= old end-2
              coll2.end() );                                    // end 
    std::cout<<"\nValues rotated from value 20 using find algo";    
    std::copy(coll2.cbegin(), coll2.cend(),
            std::ostream_iterator<int>(std::cout<<"\nCollection 2 re-rotated : ", " ") );

    return 0;
}