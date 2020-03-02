#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <filesystem>

// study file for smart pointers

struct X
{
  int a; 
  int b;
};

class FileDeleter
{
private:
  std::string filename;
public:
  FileDeleter(std::string fnm):filename{std::move(fnm)} { }
  
  bool operator()(std::ofstream* f) {
      f->close(); // close the file
      std::cout<<"deleting file: "<<filename<<'\n';
      return std::__fs::filesystem::remove(filename);           // filesystem should be under std:: namespace
  }                                                             // but compiler gives an error and directs to macro
                                                                // std::__fs::filesytem instead; might be an Apple Clang implemantation
};


int main()
{
    
    std::shared_ptr<std::ofstream>spf{new std::ofstream{"../tempfile.txt"}, 
                                        FileDeleter("../tempfile.txt")};
                                        
    auto spf2=spf;
    std::cout<<spf.use_count()<<'\n';

    
    // classic pointer way to create a shared pointer
    // assignment initialization is not allowed there new expression has to be in paranthesis
    // classic way creates two allocations one for data and one for the pointer
    // therefore not efficient & safe as std::make_shared helper function
    std::shared_ptr<std::string>pSalim{new std::string{"salim"}};
    std::shared_ptr<std::string>pDemir{new std::string{"demir"}};
    
    std::cout<<*pSalim<<" and "<<*pDemir<<'\n';
    
    pSalim.reset(new std::string{"salo"});
    std::cout<<*pSalim<<'\n';
    
    *pDemir="iron_man";
    std::cout<<*pDemir<<'\n';
    
    // alternative way; std::make_shared<>(); uses one allocation and safer
    // shared pointers can be copied, moved and shared
    // when copied the original one tracks the copies
    std::shared_ptr<std::string>pDidem=std::make_shared<std::string>("didem");
    std::shared_ptr<std::string>pSema=std::make_shared<std::string>("sema");
    
    std::cout<<*pDidem<<" and "<<*pSema<<'\n';
    
    // -> gives access to the object that the pointer points
    // * can be used as alternative
    std::copy((*pDidem).begin(), pDidem->end(),
             std::ostream_iterator<char>(std::cout, ""));  // char has to be used for ostream_iterator 
    std::cout<<'\n';                                        // to display the character in the string
                                                            // if string used then gives error but  
                                                            // if the container is a vector<string> then
                                                            // ostream_iterator<std::string> is OK
    (*pDidem)[0]='D';
    pSema->at(0)='S';
    (*pSema)[1]='E';
    std::cout<<*pDidem<<" and "<<*pSema<<'\n';
    
    
    std::vector<std::shared_ptr<std::string>>family;
    
    family.push_back(pSema);
    family.push_back(pDidem);
    family.push_back(pSema);
    family.push_back(pDidem);
    family.push_back(pSema);
    
    for(auto& dudes:family)
        std::cout<<*dudes<<" ";
    std::cout<<'\n';

    std::cout<<*family.at(0)<<": "<<family.at(0).use_count()<<'\n';
    std::cout<<*family.at(1)<<": "<<family.at(1).use_count()<<'\n';
    *pSema="Semos";
    
    std::cout<<*family.at(0)<<'\n';
    
    pDidem.reset();                                                       // the original was reset and released the object
    pDidem=std::make_shared<std::string>("Didos");                        // after resetting the original pointer hold another object
    std::cout<<*pDidem<<'\n';                                             // this will not effect the other copies
    
    std::cout<<pDidem.use_count()<<'\n';                                  // therefore it does not hold any object; use_count=0
    
    std::cout<<*family.at(1) <<": "<<family.at(1).use_count()<<'\n';      // However, the copies of pDidem in the Vector still holds the object
        
    std::shared_ptr<int>pArray(new int[10]{5,2,3}, [](int* p){ delete [] p; });  // if an array pointer is created then a custom deleter  
                                                                         // must be specified; either passing a deleter function or thru lambda   
                                                                         // or call the standart deleter function specificied 
   std::cout<<"1st element of the array: "<<*pArray<<'\n';                                                                    // for unique_ptr,  e.g. std::default_deleter<int[]>()
                                                                         
                                                                         
    *pArray=1;
    pArray.get()[1]=8;                  
    // to access elements of the array we have to use get() function
    // to access to the pointer; *pArray[] is not valid for array version
    std::cout<<"1st element of the array: "<<*pArray<<'\n';
    std::cout<<"2nd element of the array: "<<*(pArray.get()+1)<<'\n';
    
/*    
The access to shared_pointer to an array explanation from C++ STL Book; 
"Note that shared_ptrs provide only operators * and ->. Pointer arithmetic and operator [ ] are not provided. Thus, to access the memory, you have to use get(), which yields the internal pointer wrapped by shared_ptr to provide the full pointer semantics:
smp.get()[i] = i*42;
Thus, get() provides an alternative of calling:
(&*smp)[i] = i*42;"
*/

    
    // Pointer can refer to a specific member of the object they point to
    // Pointer can share it with another pointer and points either the whole object
    // or a specific member of the object
    std::shared_ptr<X>px(new X{2,3});                   // px points to whole object of type X
    std::shared_ptr<int>pi(px, &px->b);                 // create another pointer from px but refer to only one of the members
    
    std::cout<<"px use count: "<<px.use_count()<<'\n';
    std::cout<<"px value: "<<px->a<<", "<<px->b<<'\n';
    px.reset();
    
    std::cout<<"pi use count: "<<pi.use_count()<<'\n'; // even if the owner of the object has released it the other pointer 
    std::cout<<"pi value: "<<*pi<<'\n';                // hold the object but refers to only one of the members

    std::cout<<'\n';
    return 0;
}                                                           
