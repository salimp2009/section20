#include "Movie.hpp"
//#include <iostream>

// constructor
Movie:: Movie(std::string name, Rating r, std::size_t num):
                name{std::move(name)}, rating{r}, num_watched{num} {std::cout<<"Movie constructor...\n"; }
// copy constructor                
Movie::Movie(const Movie& other):Movie{other.name, other.rating, other.num_watched} 
                                { std::cout<<"Movie Copy constructor....\n";}
// move constructor
Movie::Movie(Movie&& other) noexcept : 
        name{std::move(other.name)}, rating{std::move(other.rating)}, num_watched{std::move(other.num_watched)}
        { std::cout<<"Movie Move constructor....\n";}
        
        
Movie::~Movie() { }
       

std::ostream& operator<<(std::ostream& os, const Rating& rating) {
    switch(rating) {
        case G:     return os<<'G';
        case PG:    return os<<"PG"; 
        case PG13:  return os<<"PG13"; 
        case R:     return os<<'R';
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Movie& mov) {
    return os<<"["<<mov.name<<", "<<mov.rating<<", "<<mov.num_watched<<"] ";
}

