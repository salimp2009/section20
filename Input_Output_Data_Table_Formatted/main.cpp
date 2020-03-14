#include <iostream>
#include <ios>
#include <iomanip>
#include <bitset>
#include <string>
#include <vector>
#include <algorithm>


struct City {
    std::string name;
    long population;
    double cost;
};

struct Country {
  std::string name;
  std::vector<City>cities;
};

struct Tours {
  std::string title;
  std::vector<Country>countries;
};

int main()
{
    Tours tours 
    {"Tour Ticket Prices from Miami",   // the title of the tours struct
        {                               // initialize countries vector
          {
            "Colombia", {         // name of the country
          // Cities       
            {"Bogota",    877000,  400.98}, // city name, population & cost
            {"Cali",      2401000, 424.14},
            {"Medelin",   2640000, 350.98},
            {"Cartegana", 9720000, 345.34}
          },
        },
        {
            
            "Brazil", {        // name of the country
                
            {"Rio   ",    877000,  400.98}, // city name, population & cost
            {"Cali",      2401000, 424.14},
            {"Medelin",   2640000, 350.98},
            {"Cartegana", 9720000, 345.34}
          },
        },
      {
           "Colombia", {         // name of the country
            {"Bogota",    877000,  400.98}, // city name, population & cost
            {"Cali",      2401000, 424.14},
            {"Medelin",   2640000, 350.98},
            {"Cartegana", 9720000, 345.34}
          },
        }
      }
    };
    
    
        std::cout<<std::setw(10)<<std::right<<" "<<tours.title<<'\n';
        for(const auto& country:tours.countries) {
            std::cout<<country.name<<'\n';
            for(const auto& city:country.cities) {
                std::cout<<std::setw(15)<<std::left<<city.name
                               <<std::setw(20)<<std::left<<city.population
                               <<std::setw(10)<<std::right<<city.cost<<'\n';
            }
            std::cout<<'\n';
        }
        
        
        // the same example using C++17 structured bindings
        // need to find a better solution instead of for loops
        // std::for_each()
        auto& [title, countries]=tours;
        std::cout<<std::setw(10)<<std::right<<" "<<title<<'\n';
        
        for (const auto& [name, cities]:countries) {
            std::cout<<name<<'\n';
            for(const auto& [name, population, cost]: cities) {
                std::cout<<std::setw(15)<<std::left<<name
                               <<std::setw(20)<<std::left<<population
                               <<std::setw(10)<<std::right<<cost<<'\n';
            }
            std::cout<<'\n';
        }
        
    return 0;
}
