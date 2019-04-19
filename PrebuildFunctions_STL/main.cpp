#include <iostream>
#include <deque>
#include <functional>
#include <algorithm>
#include <iterator>
#include <set>

// PreBuild STL Functions

int main()
{
    std::deque<int> coll{1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    std::cout<<"\n=========Coll Original===============\n";
    
    
    std::copy(coll.cbegin(), coll.cend(),
              std::ostream_iterator<int>(std::cout, " ") );     // ostream iterator to print
              
    std::cout<<"\n=========Coll Negated===============\n";
    
    std::transform(coll.begin(), coll.end(),                   // source collection
                    coll.begin(),                              // target collection
                    std::negate<int>() );                      // prebuild function; each element negated 
                                                               // and result returned to iterator to write it in source collection
                 
    std::copy(coll.cbegin(), coll.cend(),
              std::ostream_iterator<int>(std::cout, " ") );
              
    std::cout<<"\n=========Coll Multiplied===============\n";
              
    std::transform(coll.begin(), coll.end(),                // source collection
                    coll.begin(),                           // second collection
                    coll.begin(),                           // target collection
                    std::multiplies<int>() );               // each element of source and second multiplied  
                                                            // and sent to iterator to write to target 
                    
    std::copy(coll.cbegin(), coll.cend(),
              std::ostream_iterator<int>(std::cout, " ") );
                    
    std::cout<<'\n';
                      
 return 0;
}