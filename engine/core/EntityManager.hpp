#ifndef __ENTITY_MANAGER__
#define __ENTITY_MANAGER__

#include "Entity.hpp"
#include <deque>

class EntityManager
{
private:
    Uint32 nextId;
    std::deque<Uint32> deletedIds;
    ComponentManager* cm;

public:
    EntityManager();

    void init(ComponentManager* cm);
    Entity* createEntity();
    void deleteEntity(Entity* entity);
};

#endif