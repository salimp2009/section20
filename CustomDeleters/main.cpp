#include <iostream>
#include <memory>

class Test
{
private:
    int data{};
public:
    Test(): data{0} 
            {std::cout<<"\nTest constructor ("<<data<<")\n";}
    Test(int data): data{data}
            {std::cout<<"\nTest constructor ("<<data<<")\n";}
    int get_data() const{return data;}
    ~Test() {std::cout<<"\nTest destructor ("<<data<<")\n";}
};

void my_deleter(Test* ptr)
{
    std::cout<<"\tTesting my custom deleter with function..\n";
    delete ptr;
}

int main()
{
    {
        std::shared_ptr<Test>ptr1{new Test{100}, my_deleter};
    }
    
    std::shared_ptr<Test>ptr2 {new Test{200}, [](Test*ptr) {
       std::cout<<"\tTesting my custom deleter with lambda..\n";
       delete ptr;}
       };

 
 return 0;
}