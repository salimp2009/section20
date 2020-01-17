#include <iostream>
#include <vector>



int main()
{
    std::vector<int>vec1{1,2,3,4};
    
    std::vector<int>vec2{};
    
    //vec2.assign(vec1.begin(), vec1.end());  // assign value of a container to another container
    
    // vectors can be copied
    vec2 = vec1;
    
    // add element to vector 2 to the back;
    // alternative; emplace_back
    // insert or emplace() can be used to add element to a specific position
    vec2.push_back(5);
    
    for(const auto& elem:vec2)
        std::cout<<elem<<(elem==*(vec2.end()-1) ? " ":", ");        // better to use iterator for the last condition it fails to put comma 
    std::cout<<'\n';                                                // if the value of any element is same as the value at the end then
    
    // two dimensional vector 
    std::vector<std::vector<int>>movie_ratings {
                    {4,5,6,7}, {2,3,7,3}, {5,6,2,4}};
    for(const auto& reviewer: movie_ratings) {
        for(const auto& rating:reviewer)
            std::cout<<rating<<" ";
        std::cout<<'\n';
    }
    
    std::cout<<'\n';
    
    std::vector<int>vec3{10,20};
    std::vector<int>vec4{100,200};
    
    // std::vector<std::vector<int>>vec_2d{std::move(vec3), std::move(vec4)};
    std::vector<std::vector<int>>vec_2d;
    vec_2d.push_back(std::move(vec3));
    vec_2d.push_back(std::move(vec4));
    
    for(const auto& reviewer: vec_2d) {
        for(const auto& rating:reviewer)
            std::cout<<rating<<" ";
        std::cout<<'\n';
    }
    
    
    // the content of the vec3 is moved into vec_2d therefore vec3 is empty and 
    // should not be used ; undefined behaviour 
//    for(auto& elem:vec3)
//        std::cout<<elem<<" ";
//    std::cout<<'\n';
    
    return 0;
}
