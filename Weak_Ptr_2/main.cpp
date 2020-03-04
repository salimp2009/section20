#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Person
{
public:
    
    std::string name;
    std::shared_ptr<Person>mother;
    std::shared_ptr<Person>father;
    std::vector<std::weak_ptr<Person>>kids;         // kids will have mom and dad ; those are Person too
                                                    // so each mom and dad will have kid and kids is a person and will be
                                                    // linked to their mom and dad; if we use shared_ptr it will be a circular reference
    Person(const std::string& n, std::shared_ptr<Person>m=nullptr, std::shared_ptr<Person>f=nullptr)
                :name{n}, mother{m}, father{f} { }
    
    ~Person() {std::cout<<" deleting "<<name<<'\n';
            }
  
};

std::shared_ptr<Person>  initFamily(const std::string& name)
{
    std::shared_ptr<Person>mom(new Person{name + "'s mom"});
    std::shared_ptr<Person>dad(new Person{name + "'s dad"});
    std::shared_ptr<Person>kid(new Person{name, mom, dad});
    
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

class Test {
private:
    int data;
public:
    Test():data{0} {std::cout<<"\t test constructor...\n";}
    Test(int num):data{num} {std::cout<<"\t test constructor...\n";}
    int get_data() const { return data;}
    ~Test() {std::cout<<"\t test destructor for data: "<<data<<'\n';} 
};

using UniqueVec = std::unique_ptr<std::vector<std::shared_ptr<Test>>>;

UniqueVec make() {
    
    return std::make_unique<std::vector<std::shared_ptr<Test>>>();
}

using VecShrPtr = std::vector<std::shared_ptr<Test>>;

void fill(VecShrPtr& vec, int num) 
{
    int value{0};
    for(int i{0}; i<num; ++i) {
        std::cout<<"please enter the number you want to insert: ";
        std::cin>>value;
        vec.emplace_back(std::make_shared<Test>(value));
    }
}

template<typename Cont>
void display(const Cont& vec) 
{
    for(const typename Cont::value_type& elem:vec)
        std::cout<<elem->get_data()<<(elem!=*(vec.end()-1) ? " ":"\n");
}


int main()
{
    std::shared_ptr<Person>p=initFamily("salim");
    
    std::cout<<p->name<<"'s family created....\n";
    std::cout<<p->name<<" is shared "<<p.use_count()<<'\n';
    std::cout<<"name of 1st kid of "<<
            p->mother->name<<": "<<p->mother->kids[0].lock()->name<<'\n';  // lock() is used for weak_ptr to access the share_ptr
                                                                           // data and it creates a temporary sha 
    
    p=initFamily("didem");
    std::cout<<p->name<<"'s family created....\n";
    std::cout<<p->name<<"'s family created....\n";
    std::cout<<p->name<<" is shared "<<p.use_count()<<'\n';
    std::cout<<"name of 1st kid of "<<
            p->mother->name<<": "<<p->mother->kids[0].lock()->name<<'\n';
   
    int *pointer=new int(42);
    std::shared_ptr<int>sp1(pointer, [](int* p){ 
                                                std::cout<<"Deleting Shared Pointer Data..."<<p<<", value: "<<*p<<'\n';
                                                delete p; });
   // std::shared_ptr<int>sp2(pointer);     // this will cause an Error since raw pointer is owned by the other pointer
    std::shared_ptr<int>sp2(sp1);           // this is OK since the owner is still sp1 and sp2 shares it 
    
    std::cout<<"pointer is shared: "<<sp1.use_count()<<'\n';
    std::weak_ptr<int>wptr1{sp1};
    std::cout<<"pointer is shared (after weak pointer): "<<sp1.use_count()<<'\n';
//    std::cout<<"weak pointer point to: "<<*wptr1<<'\n';           // compiler error; weak_ptr can access data by lock() helper function
    std::cout<<"weak pointer use count: "<<sp1.use_count()<<'\n';
    
    std::cout<<"weak pointer point to: "<<*(wptr1.lock())<<'\n';     // works ok
      

// Test Class example using Unique and shared pointers; basics

    std::unique_ptr<std::vector<std::shared_ptr<Test>>>vec_ptr;
    
    vec_ptr=make();
    
    std::cout<<"How many data points you want to enter: ";
    int num;
    std::cin>>num;
    
    fill(*vec_ptr, num);
    display(*vec_ptr);
    
    return 0;
}
