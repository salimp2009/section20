#include "Move.hpp"
#include <iostream>

// Static members are initialized in  erate cpp file
// unless they are const or constexpr; if they are they can be initialized
// in the class definition

int Move::num_players=0;

// constructor
Move::Move(int n): data{new int}
                {*data=n;
                  ++num_players;
                   std::cout<<"Constructor for data: "<<*data<<'\n';  
                }

// copy constructor
Move::Move(const Move& source): Move{*source.data} 
                { 
                    std::cout<<"Copy Constructor....\n"; 
                }
                
// move constructor:               
Move::Move(Move&& source) noexcept: data{source.data} 
                {
                    source.data=nullptr;
                    ++num_players;
                    std::cout<<"Move Constructor; moving resources, data: "<<*data<<'\n'; 
                }

// destructor
Move::~Move() {
          if(data!=nullptr)
                std::cout<<"Deleting data: "<<*data<<'\n';
            else
                std::cout<<"Deleting data: nullptr...\n";
           --num_players;
           delete data;
        }