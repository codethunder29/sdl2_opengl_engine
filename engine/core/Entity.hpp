#ifndef __ENTITY__
#define __ENTITY__

#include <SDL2/SDL.h>
#include "ComponentManager.hpp"
#include <bitset>

class Entity
{
private:
    Uint32 id;
    std::bitset<32> signature;
    ComponentManager* cm;

public:
    Entity(ComponentManager* cm, Uint32 id)
    {
        this->cm = cm;
        this->id = id;
    }

    template <typename T>
    void addComponent(T* component)
    {
        signature[T::getId()] = 1;
        cm->addComponent<T>(component, id);
    }

    template <typename T>
    void removeComponent()
    {
        signature[T::getId()] = 0;
        cm->removeComponent<T>(id);
    }

    template <typename T>
    T* getComponent()
    {
        return cm->getComponent<T>(id);
    }

    bool checkComponents(std::bitset<32> sign)
    {
        return (signature & sign) == sign;
    }

    Uint32 getId()
    {
        return id;
    }

    virtual void update() {}
};

#endif