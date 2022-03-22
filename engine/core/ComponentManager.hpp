#ifndef __COMPONENT_MANAGER__
#define __COMPONENT_MANAGER__

#include "Component.hpp"
#include <vector>
#include <map>

class ComponentManager
{
private:
    std::map<Uint32,Component*> components[32];  // the structue is like this: arr[Comp Id] -> {EntityId, Comp}

public:
    ~ComponentManager()
    {
       for(int i=0; i<32; i++)
       {
           for(auto comp : components[i])
               delete comp.second;

           components[i].clear();
       }
    }

    template <typename T>
    void addComponent(T* comp, Uint32 entityId)
    {
        std::map<Uint32,Component*> comps = components[T::getId()];

        if(comps.find(entityId) != comps.end())
            return;

        components[T::getId()].insert({entityId, static_cast<Component*>(comp)});
    }

    template <typename T>
    void removeComponent(Uint32 entityId)
    {
        std::map<Uint32,Component*>* comps = &components[T::getId()];

        if(comps->find(entityId) != comps->end())
        {
            delete comps->find(entityId)->second;
            comps->erase(comps->find(entityId));
        }
    }

    void removeEntity(Uint32 entityId)
    {
        for(int i=0; i<32; i++)
        {
            std::map<Uint32,Component*>* comps = &components[i];
            if(comps->find(entityId) != comps->end())
            {
                delete comps->find(entityId)->second;
                comps->erase(comps->find(entityId));
            }
        }
    }

    template <typename T>
    T* getComponent(Uint32 entityId)
    {
        std::map<Uint32,Component*> comps = components[T::getId()];

        if(comps.find(entityId) != comps.end())
            return static_cast<T*>(comps.find(entityId)->second);

        return nullptr;
    }
};

#endif