#include "EntityManager.hpp"

EntityManager::EntityManager()
{
    cm = nullptr;
    nextId = 0;
}

void EntityManager::init(ComponentManager* cm)
{
    this->cm = cm;
}

Entity* EntityManager::createEntity()
{
    if(deletedIds.size() > 0)
    {
        Entity* entity = new Entity(cm, deletedIds[0]);
        deletedIds.pop_front();
        return entity;
    }

    return new Entity(cm, nextId++);  // creating entity and then increasing nextId by 1
}

void EntityManager::deleteEntity(Entity* entity)
{
    deletedIds.push_back(entity->getId());
    cm->removeEntity(entity->getId());
    delete entity;
}