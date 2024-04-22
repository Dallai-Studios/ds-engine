#include "ECS.h"

#include <algorithm>
#include "../../tools/logger/Logger.h"

int IComponent::nextId = 0;


// Entity class implementation
int Entity::GetId() const {
    return this->id;
}


// System class implementation
void System::AddEntityToSystem(Entity entity) {
    this->entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    this->entities.erase(std::remove_if(this->entities.begin(), this->entities.end(), [&entity](Entity entityToCompare) {
        return entity == entityToCompare; 
    }), this->entities.end());
}

std::vector<Entity> System::GetEntities() const {
    return this->entities;
}

const Signature& System::GetComponentSignature() const {
    return this->componentSignature;
}

// Registry class implementation
Entity Registry::CreateEntity()
{
    int entityId = this->entitiesCount++;
    Entity entity(entityId);
    // this->entitiesToBeAdded.insert(entity);

    Logger::Info("New Entity created with id: " + std::to_string(entityId));

    return entity;
}

void Registry::Update()
{

}