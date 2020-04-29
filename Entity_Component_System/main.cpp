#include <iostream>
#include "Component.hpp"



int main()
{
    using namespace CompositionArkonoid;
    
    CompositionArkonoid::Component comp01;
    
    Manager manager;
   
   // to create an entity we will use the manager
    auto& entity(manager.addEntity());
   
   entity.addComponent<CounterComponent>();
   entity.addComponent<KillComponent>();
   
for(auto i(0u); i<1000; ++i)
{
    manager.refresh();
    manager.update(1.0f);
    manager.draw();
} 
   
    return 0;
}
