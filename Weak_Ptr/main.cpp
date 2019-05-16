#include <iostream>
#include <memory>

void print(int *list[], int size) {
    
    for(int i{0}; i<size; ++i) {
        std::cout<<*list<<'\n';
    }
}

int main()
{
    std::shared_ptr<int>shrd_ptr=std::make_shared<int>(45);
    
    std::weak_ptr<int>wk_ptr=shrd_ptr;
    
    std::cout<<*shrd_ptr<<'\n';
    std::cout<<*wk_ptr.lock()<<'\n';
    
    std::cout<<shrd_ptr.use_count()<<'\n';
    std::cout<<wk_ptr.use_count()<<'\n';
    
 
 return 0;
}