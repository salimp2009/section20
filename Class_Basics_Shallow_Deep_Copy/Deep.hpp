#ifndef _DEEP_COPY_
#define _DEEP_COPY_

class Deep
{
public:
 public:
    //constructor
    Deep(int n);
    //copy constructor-Deep Copy
    Deep(const Deep& source);
    ~Deep();
    void set_data(int d) {*data=d;}
    int get_data() const { return *data;}
    
private:
    int* data;  
};

// constructor
Deep::Deep(int n): data{new int} {*data=n;}

// copy constructor:Deep Copy
Deep::Deep(const Deep& source): Deep{*source.data} 
                { 
                    std::cout<<"Deep Copy Constructor....\n"; 
                }

// destructor
Deep::~Deep()
        {   delete data;
            std::cout<<"Destructor-Deep...\n";}

#endif // _DEEP_COPY_
