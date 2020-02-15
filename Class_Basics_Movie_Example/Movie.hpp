#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <string>
#include <iostream>

enum Rating {G, PG, PG13, R};

std::ostream& operator<<(std::ostream& os, const Rating& rating);

class Movie
{
public:
    // constructor
    Movie(std::string name="", Rating r=G, std::size_t num=0 );
    
    // copy constructor
    Movie(const Movie& other);
    
    // move constructor
    Movie(Movie&& other) noexcept;

    // assignment operators(copy & move)
    Movie& operator=(const Movie& other) {
                        if(this!=&other) {
                            name=other.name;
                            rating=other.rating;
                            num_watched=other.num_watched;
                        }
                        std::cout<<"Movie Copy assignment....\n";
                        return *this;
    }
    
    Movie& operator=(Movie&& other)=default;
    
    // destructor
    ~Movie();
    
    // setters
    void set_name(std::string _name) {name=std::move(_name);}
    void set_rating(Rating r) {rating=r;}
    void set_num_watched(int n) { num_watched=n;}
    void increment_watched() {++num_watched;}

    // getters
    const std::string& get_name() const& {return name;}
    Rating get_rating() const {return rating;}
    std::size_t get_num_watched() const {return num_watched;}
    
    void display() const {std::cout<<*this<<'\n';}

    friend std::ostream& operator<<(std::ostream& os, const Movie& mov);
 
private:
    std::string name;
    Rating rating;
    std::size_t num_watched;

};

#endif // _MOVIE_H_
