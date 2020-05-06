#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <memory>
#include <experimental/memory_resource>
#include <cstddef>
#include <cstdlib>
#include <cstdint>  // for uint32_t
//#include "tracknew.hpp"
//#include "overloadednew.hpp"

static int count{0}; 
static int totalMemoryAllocated{0};

struct AllocationMetrics
{
    std::uint32_t TotalAllocated{0};
    std::uint32_t TotalFreed{0};
    
    std::uint32_t Currentusage() {return TotalAllocated-TotalFreed;}
};

AllocationMetrics s_AllocationMetrics;

 void* operator new(std::size_t size)
{
    ++count;
    totalMemoryAllocated+=size;
    s_AllocationMetrics.TotalAllocated+=size;
    //printf("Allocating: %lu\n", size * sizeof(char));
    return malloc(size);
}

void operator delete(void* p, std::size_t size) noexcept
{
    --count;
    totalMemoryAllocated-=size;
    s_AllocationMetrics.TotalFreed+=size;
    //printf("De-allocating: size= %lu\n", size * sizeof(char)); 
    free(p);
   
}

struct Object {
    int x,y,z;
};

static void PrintMemoryUsage()
{
    printf("Memory usage: %d bytes\n", s_AllocationMetrics.Currentusage());
}

int main()
{
    PrintMemoryUsage();
    
    std::string name="Chernos";
    PrintMemoryUsage();
    {
        std::unique_ptr<Object>uptr=std::make_unique<Object>();
    }

    PrintMemoryUsage(); 

    std::cout<<sizeof(std::string)<<'\n';
    
//    TrackNew::reset();
//{
//    std::vector<std::string>coll;
//    
//    for(int i{0}; i<1000; ++i)
//        coll.emplace_back("just a SFSDFSDFSDFSDFF non-SSO string");
//    
//    printf("Total Allocation Count= %d\n Total Memory Allocated= %d\n", count, totalMemoryAllocated);
////   TrackNew::status();
//}
//    // reset memory data
//    count=0; 
//    totalMemoryAllocated=0;
//    
//    // check the status of the beginning;
//    printf("Total Allocation Count= %d\n Total Memory Allocated= %d\n", count, totalMemoryAllocated);

// Not std::pmr not implemented in Mac, Xcode libs
//    std::array<std::byte, 200000>buf;
//    std::experimental::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};
//    std::experimental::pmr::vector<std::string>coll2{&pool};
//    
//        for(int i{0}; i<1000; ++i)
//            coll2.emplace_back("just a SFSDFSDFSDFSDFF non-SSO string");
    PrintMemoryUsage();
    return 0;
}
