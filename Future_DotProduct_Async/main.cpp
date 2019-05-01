#include <iostream>
#include <future>
#include <vector>
#include <numeric>
#include <random>

static constexpr std::size_t NUM {100'000'000};

long long getDotProduct(std::vector<int>&v, std::vector<int>& w) {
    
    std::size_t v_size=v.size();
    
    std::future<long long>future1=std::async(std::launch::async, [&]
                            {return std::inner_product(&v[0], &v[v_size/4], &w[0], 0LL);});
                                        
    std::future<long long>future2=std::async(std::launch::async, [&]
                            {return std::inner_product(&v[v_size/4], &v[v_size/2], &w[v_size/4], 0LL);});
    
    std::future<long long>future3=std::async(std::launch::async, [&]
                            {return std::inner_product(&v[v_size/2], &v[v_size*3/4], &w[v_size/2], 0LL);});
    
    std::future<long long>future4=std::async(std::launch::async, [&]
                            {return std::inner_product(&v[v_size*3/4], &v[v_size], &w[v_size*3/4], 0LL);});
                            
    return future1.get()+future2.get()+future3.get()+future4.get();
}

int main()
{
    std::cout<<'\n';
    
    std::random_device seed;
    
    // generator
    std::mt19937 engine(seed());
    
    // distribution
    std::uniform_int_distribution<int>dist(0,100);
    
    //create, reserve & fill the vectors
    std::vector<int>v, w;
    v.reserve(NUM);
    w.reserve(NUM);
    
    for(std::size_t i{0}; i<NUM; ++i) {
        v.push_back(dist(engine));
        w.push_back(dist(engine));
    }
    
    std::cout<<"\nDot Product(v,w): "<<getDotProduct(v, w)<<'\n';
    
    std::cout<<'\n';
 
 return 0;
}