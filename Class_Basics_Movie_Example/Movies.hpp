#ifndef _MOVIES_H_
#define _MOVIES_H_

#include <iostream>
#include <string>
#include <vector>
#include "Movie.hpp"

class Movies
{
public:
    Movies():movies{} {movies.reserve(100);}
    
    template<typename T>
    bool add_movies(T&& name, Rating r, std::size_t num_watch) 
    {       
       auto pos=std::find_if(movies.begin(), movies.end(), 
                            [name](const auto& movie){ return movie.get_name()==name;});
        if(pos!=movies.end()) return false;
        
//        for(const auto& movie: movies) {
//           if(movie.get_name()==name) {
//               std::cout<<"Movie exist...\n";
//               return false;
//           }
//       }
       //movies.push_back(Movie{std::move(name), r, num_watch});
       movies.emplace_back(std::forward<T>(name), r, num_watch);
       return true;    
    }
    
    void display() {
        if(movies.empty()) std::cout<<"No movies....\n";
        for(const auto& movie:movies)
            std::cout<<movie<<'\n';
        std::cout<<'\n';
    }
    
    template<typename T>
    bool increment_watched(T&& name) {
        for(auto& movie:movies) 
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
    std::vector<Movie>movies;

};

#endif // _MOVIES_H_
