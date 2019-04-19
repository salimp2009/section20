#include <iostream>
#include <thread>
#include <shared_mutex>
#include <map>
#include <string>

std::map<std::string, int> teleBook {
    {"Dijkstra", 1972}, {"Scott", 1976}, {"Ritchie", 1983} 
    };

std::shared_timed_mutex teleBookMutex;

// writer
void addToTelebook(const std::string& name, int phone) {
    std::lock_guard<std::shared_timed_mutex> writerLock(teleBookMutex);
    std::cout<<"\nStarting Update-------->"<<name<<'\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    teleBook[name]=phone;
    std::cout<<"\nEnding Update---------->"<<name<<'\n';
}

// reader
void printNumber(const std::string& name) {
    std::shared_lock<std::shared_timed_mutex> readerLock(teleBookMutex);
    auto search=teleBook.find(name);
    if(search!=teleBook.end()) {
        std::cout<<"\nName: "<<search->first<<" Phone: "<<search->second<<'\n';
    } else {
        std::cout<<name<<" not found in the phone book....\n";
    }
}

int main()
{
    std::cout<<'\n';
    
    std::thread reader1(printNumber, "Scott");
    std::thread reader2([](){printNumber("Ritchie");});
    std::thread writer1(addToTelebook, "Scott", 1968);
    
    
    reader1.join();
    reader2.join();
    writer1.join(); 
    
 
 
 return 0;
}