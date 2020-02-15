#ifndef _MOVE_CONSTRUCTOR_
#define _MOVE_CONSTRUCTOR_

// example for a typical class with copy and move constructor
// typically if you dont use a copy constructor, copy assignment and destructor
// compiler will assign a move constructor
// to use a compiler generated move operation we need to use std::move()
// to move a class rather than being copied
class Move
{
public:
 public:
    //constructor
    Move(int n);
    
    //copy constructor
    Move(const Move& source);
    
    // move constructor
    Move(Move&& source) noexcept;     // noexcept means no throwing; this was required for vectors      
    ~Move();                          // if you use the move assingment while push_back in vectors
                                      // when the vector does interior reallocation it may use copy-constructor
                                      // since the move constructor does not guarantee "no throwing"
    void set_data(int d) {*data=d;}
    int  get_data() const { return *data;} 
    
    // static member function has access to static members only
    static int get_player_num() {return num_players;}  // static member functions canot be const
                                                       // unless the static member is defined as const   
private:
    int* data;  
    static int num_players;
};

#endif // _MOVE_CONSTRUCTOR_
