#include <iostream>
#include <thread>
#include <map>
#include <shared_mutex>
#include <string>
#include <string_view>

std::map<std::string, int>teleBook{ {"Dikstra", 1972}, {"Scott", 1976}, {"Ritchie", 1983} };

std::shared_timed_mutex teleBookMutex;


void addToTelebook(const std::string& name, int value) 
{
    std::unique_lock<std::shared_timed_mutex>writerLock(teleBookMutex);
    std::cout<<"\nSTARTING UPDATE PHONEBOOK "<<name<<'\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    teleBook[name]=value;
    std::cout<<"...ENDING UPDATE: "<<name<<'\n';  
}

void printNumber(const std::string& name)
{
    std::shared_lock<std::shared_timed_mutex>readerLock(teleBookMutex);
    auto search=teleBook.find(name);
    if(search!=teleBook.end())
        std::cout<<search->first<<": "<<search->second<<'\n';
    else
        std::cout<<name<<": Not found....\n";
    
}


int main()
{
    std::cout<<'\n';
    
    std::thread t1([]{printNumber("Scott");});
    std::thread t2([]{printNumber("Ritchie");});
    
    std::thread w1([]{addToTelebook("Salim", 1972);});
    std::thread w2([]{addToTelebook("Sema", 1953);});
    
    std::thread t3([]{printNumber("Salim");});
    std::thread t4([]{printNumber("Sema");});
  
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    w1.join();
    w2.join();
    
    return 0;
}
