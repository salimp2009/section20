#include <iostream>
#include "Deep.hpp"
#include <utility>

// basic example for shallow versus deep copy

class Shallow
{
public:
    //constructor
    Shallow(int n);
    //copy constructor-Shallow Copy
    Shallow(const Shallow& source);
    ~Shallow();
    void set_data(int d) {*data=d;}
    int get_data() const { return *data;}
    
private:
    int* data;  
};

// constructor
Shallow::Shallow(int n): data{new int} {*data=n;}

// copy constructor:Shallow Copy
Shallow::Shallow(const Shallow& source): data{source.data} 
                { 
                    std::cout<<"Shallow Copy Constructor....\n"; 
                }

// destructor
Shallow::~Shallow()
        {   delete data;
            std::cout<<"Destructor-Shallow...\n";}
             


/* when the data of the passed object is copied, it copies the pointer only
// the data that the source pointer is not copied so the new object's
// pointer refers to the same data as the source
// if one of the objects gets deleted or revised or goes out of scope it
// will delete or change the data that the other object is referring
// also if you pass one of the objects to a function and even though the function
// does not change the object it has to make a copy and that copy will refer to the 
// same data of the original object and when the function goes out of scope the copy will be
// destroyed so as the data this will cause a crash of the program
*/

/* this does not crash because the object is a reference
////// so the function refers to the object in the main function
////// therefore does not call destructor once the function goes out of scope
////*/
//template<typename T>
//void display(const T& s1)
//{
//    std::cout<<"object data: "<<s1.get_data()<<'\n';
//}

/* crashing copy due to shallow copy
// the function makes a copy of the object and it refers
// to the same data on the heap due to shallow copy constructor
// when the function goes out of scope it deletes its own copy
// calling the destructor and that deletes the pointer and the data on heap
// the data on heap is the same data that original object in main
// so the program crashes either when the destructor tries to delete
// or the when the original object tries to access to the data that does not exist
*/
 
//template<typename T> 
//void display(T s1)
//{
//    std::cout<<"object data: "<<s1.get_data()<<'\n';
//}

template<typename T>
void display(T&& s1)
{
    std::cout<<"object data: "<<s1.get_data()<<'\n';
}



int main()
{
    Shallow obj1{100};
    display(obj1);                                // even shallow version does not crash with r-value version of display 
    display(std::forward<Shallow>(obj1));         // alternative perfect forwarding no crash 
    obj1.set_data(1000);
    
    Deep obj2{200};
    display(obj2);                               // no crashing in any case cause the data of the copied 
    display(std::forward<Deep>(obj2));           // perfect forwarding                                 
    obj2.set_data(1500);
    
    
    return 0;
}
