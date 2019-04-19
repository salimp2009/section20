#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

// Example for Memory Order without waiting
// if we have one reader and one write, there is no data race
//  due to relation atom.store & atom.fetch_sub

// if we add another reader thread there may be data race 
// since because there is no lock on the reader; each thread might read the same data
// as long as condition in the while loop readShared satisfies so DONT DO IT...!!! 
//
// atom.fetch_sub(1, std::memory_order_acquire) is a ready-modify-write operation 
// without a std::memory_order_release tag. 


std::atomic<int>atom{0};
int somethingShared{0};

void writeShared() {
    somethingShared=2011;
    atom.store(2, std::memory_order_release);
}

void readShared() {
    while(!(atom.fetch_sub(1, std::memory_order_acquire)>0) ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
    std::cout<<"\nsomethingShared: "<<somethingShared<<'\n';
}


int main()
{
    std::thread w1(writeShared);
    std::thread r1(readShared);
   //  std::thread r2(readShared);
  
  std::cout<<"\nMain program is also working...\n";
  
  w1.join();
  r1.join();
  //r2.join();
 
 std::cout<<"\natom: "<<atom<<'\n';
 std::cout<<"\nFinishing program....\n";
    
 
 
 return 0;
}