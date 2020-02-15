#include <iostream>
#include "Movie.hpp"
#include "Movies.hpp"
#include "Movies_Ptr.hpp"
#include <string>
#include <functional>

template<typename T>
void add_movies(Movies& movies, T&& name, Rating r, std::size_t num_watched) {
    if(movies.add_movies(std::forward<T>(name), r, num_watched))
        std::cout<<"Movie Added..\n";
    else
        std::cout<<"Sorry:Movie exists..."<<'\n';
}

template<typename T>
void increment_watched(Movies& movies, T&& name)
{
   if(movies.increment_watched(std::forward<T>(name)))
        std::cout<<"Watch count increased....\n";
    else
        std::cout<<"Sorry...\n";
}


int main()
{
    Movie mv1{"Star Wars", G, 100};
    Movie mv2;
    
    mv2=mv1;            
    
    mv1.display();
    mv2.display();
    
    Movies my_movies{};
    std::string s1{"toy story"};
    my_movies.add_movies(s1, G, 1);                 // s1 Lvalue is passed as Lvalue and forwarded as Lvalue
    my_movies.add_movies(std::move(s1), G, 1);      // s1 is moved to and R value into function and it is forwared as Rvalue 
    std::cout<<"s1: "<<s1<<'\n';                    // the value of s1 is undefined since it was moved; but it is OK to assign a new value if needed
    
    my_movies.add_movies(std::string{"Toy Story"}, G, 1);
   
    add_movies(my_movies, "Star Wars", G, 10);
    add_movies(my_movies, "Joker", PG13, 1);
    add_movies(my_movies, "Iron Man3", PG13, 10);
    add_movies(my_movies, "Terminator", G, 10);
    
    my_movies.display();
 
    add_movies(my_movies, "Terminator", G, 10);
    
    my_movies.display();
    
    increment_watched(my_movies, "Terminator");
    increment_watched(my_movies, "Joker");
    
    my_movies.display();
    
    std::cout<<"\n------------Movies_Ptr Version----------------------\n";
    Movies_ptr better_movies{};
    better_movies.add_movies("cars", G, 2);
    better_movies.add_movies("Avengers", PG13, 5);
    better_movies.add_movies("X-Men", PG13, 5);
    
    better_movies.display();
    better_movies.add_movies("X-Men", PG13, 5);
    better_movies.increment_watched("X-Men");
    
    better_movies.display();
    
    auto new_movies=better_movies;
    return 0;
}
