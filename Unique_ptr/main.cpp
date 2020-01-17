#include <iostream>
#include <memory>
#include <string>
#include <memory>

// Unique_ptr own the object that it refers ; does not share ownership

std::unique_ptr<int> source(int i)
{
    
  //  return std::make_unique<int>(i);
      return std::unique_ptr<int>{new int(i)}; 
}

//template<typename T>
//struct custom_deleter
//{
//    void operator()(T* p)
//    {
//            delete[] p;
//            std::cout<<"templated custom_deleter deleting pointer....\n";
//    }
//};



int main()
{
    std::unique_ptr<std::string>up1{new std::string{"salim"}};
    
    std::cout<<"up1 value: "<<*up1<<'\n';
    
    (*up1)[0]='S';                          // unique_ptr interface allows [] operator (not possible for shared_ptr)
    up1->append(" Pamukcu");                // unique_ptr allows to access object's functions         
    std::cout<<"up1 value: "<<*up1<<'\n';   
    
    std::unique_ptr<std::string>up2{std::move(up1)}; // copying is not allowed but std::move gives the ownership to another
   // std::cout<<"up1 value: "<<*up1<<'\n';          // after std::move the pointer is no more valid; undefined behaviour
    std::cout<<"up2 value: "<<*up2<<'\n';
    
    std::unique_ptr<int>up3;
    
    up3=std::make_unique<int>(42);
    std::cout<<"up3: "<<*up3<<'\n';
    // up3=std::unique_ptr<int>{new int(4)};        // alternative to way to assign a new unique_ptr to an existing unique ptr
    // up3=new int(42)                              // Not valid; compile error; it has to be a unique_ptr not ordinary ptr
    
    std::unique_ptr<int>up4;                        // unique_ptr=nullptr
    for(int n{0}; n<10; ++n) {
        up4=source(n);                              // function returns a unique_ptr therefore the calling ptr
        std::cout<<"up4: "<<*up4<<'\n';
    }                                                // gets the ownership of the returned unique_ptr
    
    std::unique_ptr<std::string[]>up5{new std::string[10]{"salim", "demir"}}; // unique_ptr template the [] in the type declaration
                                                            // and the new has to specify the size of the array
                                                            // this method created also a default delete []
                                                            // custome deleter can be use if the it is declared in the 
                                                            // template type
    std::cout<<"up5: "<<up5[0]<<", "<<up5[1]<<'\n';
    
    up5[0]="sema";
    up5[1]="didem";
    std::cout<<"up5: "<<up5[0]<<", "<<up5[1]<<'\n';
    
    // Assigning a custom deleter
    // we need to specify the type info at unique_ptr template
    // you can either use a lambda, function or function object
    //std::unique_ptr<int[], void(*)(int*)>up6{new int[5], [](int* p)
//                                            { delete[]p; std::cout<<"Deleting Unique_ptr to array..."<<'\n';} };
    
    // Alternative way to define and implement deleter thru a genericlambda
    auto l=[](auto* p){ delete[]p; std::cout<<"Deleting Unique_ptr to array..."<<'\n';};
    
    std::unique_ptr<int[], decltype(l)>up6{new int[5], l};
      
    up6.get()[0]=1;
    up6.get()[1]=45;
    std::cout<<"up6: "<<up6[0]<<", "<<up6[1]<<'\n';
                                                    
    std::cout<<'\n'; 
    return 0;
}
