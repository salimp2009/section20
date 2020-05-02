//#ifndef MY_COMPONENT_H_
//#define MY_COMPONENT_H_
#pragma once


#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>
#include <type_traits>


namespace CompositionArkonoid 
{
    
    struct Component;
    class Entity;
    class Manager;
    
    using ComponentID=std::size_t;
    using Group      =std::size_t;             
    
    namespace Internal {
        inline ComponentID getUniqueComponentID() noexcept 
        {
           static ComponentID lastID{0u};
           return lastID++;
        }  
    }
    
    template<typename T> inline ComponentID getComponentID() noexcept
    {
        // type T should be derived from Component
        static_assert(std::is_base_of<Component, T>::value, "T");
        
        // for each type T we will assign a typeID
        static ComponentID typeID{Internal::getUniqueComponentID()};
        return typeID;
    }
    
    // max number of components
    constexpr std::size_t maxComponents{32};
    
    // aliases for component type identifiers
    using ComponentBitset= std::bitset<maxComponents>;
    // storage for Components
    using ComponentArray=std::array<Component*, maxComponents>;
    
    constexpr std::size_t maxGroups{32};
    using GroupBitset = std::bitset<maxGroups>;

    struct Component    {
        Entity* entity;
        
        // init will be called after component is added to an Entity
        virtual void init() {}
        virtual void update(float mFT) {}
        virtual void draw() {}
        
        virtual ~Component() {}
    };
    
    class Entity {
    private:
        Manager& manager;
    
        bool alive{true};
        // components of an entity will stored in std::vector as pointers
        std::vector<std::unique_ptr<Component>> components;
 
        // array components and component ID will be used to
        // check the  components with specific IDs quickly, which is an optimization
        ComponentArray componentArray;
        ComponentBitset componentBitset;
        
        // bitset to identify the group it belongs to
        GroupBitset groupBitset;
        
    public:
       Entity(Manager& mManager): manager{mManager} {}
       
        void update(float mFT)  { for(auto& c:components) c->update(mFT);}
        void draw()             { for(auto& c:components) c->draw();}
        
        bool isAlive() const    { return alive; }
        void destroy()          { alive=false;}

        // to check if entity has  component
        template<typename T> 
        bool hasComponent() const 
        {
            // access to bitset using unique ComponentID
            return componentBitset[getComponentID<T>()];
        }
        
        // Groups handled runtime therefore passed as an argument to function
        // where as components are handled compile time therefore typeinfo with a template
        bool hasGroup(Group mGroup) const noexcept
        {
            return groupBitset[mGroup];           // mGroup is the Group ID;
        }
        
        // addGroup will impplemented later and uses Manager::addtogroup
        // and notifies the manager about the change
        void addGroup(Group mGroup) noexcept;
        
        // delGroup does not notify the manager; manager checks its Group
        // during refresh and remove entities that dont belong to Group anymore
        void delGroup(Group mGroup) noexcept
        {
            groupBitset[mGroup]=false;
        }
      
        template<typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs)
        {
            // check if the component does not exist already
            assert(!hasComponent<T>());
            // create a raw pointer on the heap and pass the arguments of the components
            T* c(new T(std::forward<TArgs>(mArgs)...));
            
            // assign entity to the component
            c->entity=this;
            
            // wrap the raw pointer into unique_ptr
            std::unique_ptr<Component>uPtr{c};
            
            // add the component entity's component container (std::vector is used)
            components.push_back(std::move(uPtr));
            
            // add the the raw pointer component and component ID into array & bitset 
            componentArray[getComponentID<T>()]=c;
            componentBitset[getComponentID<T>()]=true;
            
            // initialize c by calling Component::init()
            c->init();
            
            return *c; // safe to return since it is owned by the unique_ptr that is added to the container to entity
        }
        
        template<typename T> T& getComponent() const 
        {
            // to get a specific component we use the array for faster/optimized access
            // check if entity has components
            assert(hasComponent<T>());
            
           auto ptr(componentArray[getComponentID<T>()]);
           return *static_cast<T*>(ptr);        //  to make sure we get right type, cast to variable to T* and dereference it to access to variable
        }
    };
    
    class Manager
    {
    private:
        std::vector<std::unique_ptr<Entity>> entities;
        
        // Manager uses a bucket to store different groups of entities
        // std::array is the bucket and the group of pointer to the Entities are stored in the vector
        // this provides a contigous storage of references to group and group stores
        // pointers to the arrays to be as efficient as possible
        std::array<std::vector<Entity*>, maxGroups> groupedEntities;
        
    public:
        void update(float mFT)  {for(auto& e:entities) e->update(mFT);}
        void draw()             {for(auto& e:entities) e->draw();}
        
        void addToGroup(Entity* mEntity, Group mGroup)
        {
            // adding an assert and using set to avoid duplicates
            // to be implemented later 
            groupedEntities[mGroup].emplace_back(mEntity);
        }
        
        std::vector<Entity*>& getEntitiesByGroup(Group mGroup)
        {
            // the receiver need to check if the returned value exists
            // cause operator[] can access to memory that does not belong to that vector
            // cant use at() cause it throws and exception and slower 
            return groupedEntities[mGroup];
        }
        
        void refresh()
        {
            // cleaning the groups inside the bucket from entities that 
            // that does not belong to that group or if the entity is not alive() 
            for(auto i(0u); i<maxGroups; ++i) 
            {
                auto& v(groupedEntities[i]);
                
                v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity) 
                                      { return !mEntity->isAlive() || mEntity->hasGroup(i);}),
                        std::end(v) );
            }
            
            // clean Managers container from entities that are not alive()
            entities.erase(
                    std::remove_if(std::begin(entities), std::end(entities),
                    [](const std::unique_ptr<Entity>& mEntity) { return !mEntity->isAlive(); }),
                    std::end(entities));   
        }
        
        Entity& addEntity() 
        {
            Entity* e{new Entity(*this)};
            std::unique_ptr<Entity> uPtr(e);
            entities.emplace_back(std::move(uPtr));
            return *e;
        }
    };
    
    // implement Entity's addGroup which was declared only in the Entity class 
    void Entity::addGroup(Group mGroup) noexcept 
    {
        // add the group into Entities group index
        groupBitset[mGroup]=true;
        
        // use managers method so that it is added to that Manager's group directly  
        manager.addToGroup(this, mGroup);
    }

} // end of namespace CompositionArkonoid 


using namespace CompositionArkonoid;

struct CounterComponent: Component
{
    float counter;
    
   void update(float mFT) override 
   {
       counter+=mFT;
       std::cout<<counter<<'\n';
   }  
};

struct KillComponent:Component
{
  CounterComponent* cCounter{nullptr};

  // the base class Component has a variable pointer to entity
  // we will use entity to acces the CounterComponent and initialize it
  
  void init() override
  {
      cCounter=&entity->getComponent<CounterComponent>();
  }
  
  void update(float mFT) override
  {
      if(cCounter->counter >=100) entity->destroy();
  }
};

//#endif // MY_COMPONENT_H_
