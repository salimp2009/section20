#ifndef MOVIES_PTR_HPP
#define MOVIES_PTR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Movie.hpp"

class Movies_ptr
{
public:
// Movies_ptr():movies{new std::vector<Movie>} { }                  
// Movies_ptr():movies{std::make_unique<std::vector<Movie>>() } 
//                {std::cout<<"Movies_Ptr Constructor....\n"; }

   Movies_ptr():movies{std::make_shared<std::vector<Movie>>() }     // shared pointer version
                {std::cout<<"Movies_Ptr Constructor....\n"; }
    
    bool add_movies(std::string&& name, Rating r, std::size_t num_watch) 
    {       
       for(const auto& movie: *movies) {
           if(movie.get_name()==name) {
               std::cout<<"Movie exist...\n";
               return false;
           }
       }
       //movies.push_back(Movie{std::move(name), r, num_watch});
       movies->emplace_back(std::move(name), r, num_watch);
       return true;    
    }
    
    void display() {
        if(movies->empty()) std::cout<<"No movies....\n";
        for(const auto& movie:*movies)
            std::cout<<movie<<'\n';
        std::cout<<'\n';
    }
    
    template<typename T>
    bool increment_watched(T&& name) {
        for(auto& movie:*movies) 
        {
            if(movie.get_name()==name) 
            {
                movie.increment_watched();
                return true;
            }
        }
        std::cout<<"Movie not found...\n";
        return false;
    }
    
private:
  //  std::unique_ptr<std::vector<Movie>>movies;   // class Movies_ptr cannot be copied because unique_ptr does not allow it
    std::shared_ptr<std::vector<Movie>>movies;     // shared_ptr version makes it possible to share the class     
};

#endif // MOVIES_PTR_HPP
