#include "ECS.h"

#include <algorithm>

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