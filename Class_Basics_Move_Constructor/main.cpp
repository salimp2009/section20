#include <iostream>
#include "Move.hpp"
#include <vector>

// includes examples for move constructors  & static class members

// getting static member
void display_active_players() 
{
    std::cout<<"Number of Active Players: "<<Move::get_player_num()<<'\n';
}


int main()
{
//   {
   std::cout<<"Active players before any object created: \n";
   display_active_players();
   
   Move obj1{100};
   display_active_players(); 
    
    std::vector<Move>vec1;
    vec1.reserve(100);
    
    vec1.push_back(Move{300});
//  vec1.push_back(Move{200});
    display_active_players(); 

//    vec1.push_back(Move{500});
//    vec1.push_back(Move{500});
    vec1.push_back(std::move(obj1));        // once the obj1 is moved it should not be used anymore 
                                            // because the obj1's resources is moved so it will be undefined behaviour
    
     vec1.emplace_back(900);                // emplace constructs the data in place therefore very efficient
     display_active_players(); 
 
 //  std::cout<<"check obj1 data after the move: "<<obj1.get_data()<<'\n';
    
//    }  // forcing to destructors activated and see the effect on static member
    
    // deleting elements inside the vector to see the effect
    // although this clears the all elements one of the elements
    // was moved but the original object will be deleted once main() returns
    
    vec1.clear();
    std::cout<<"Active players after all object created: \n";
    display_active_players();                   // display zero as expected  if create the element
                                                // inside nested area in the main
                                                // display1 if we clear the vector 
                                                // but one element stays in main 
    return 0;
}
