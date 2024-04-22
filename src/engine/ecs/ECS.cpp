#include "ECS.h"
#include <algorithm>
#include "../../tools/logger/Logger.h"

// ------------------------------------------
// Entity Class Implementation
// ------------------------------------------
int Entity::GetId() const {
    return this->id;
}

// ------------------------------------------
// Component Class Implementation
// ------------------------------------------
int IComponent::nextId = 0;


// ------------------------------------------
// System Class Implementation
// ------------------------------------------
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


// ------------------------------------------
// Registry Class Implementation
// ------------------------------------------
Entity Registry::CreateEntity() {
    int entity_id;
    entity_id = this->entitiesCount++;

    Entity entity(entity_id);
    this->entitiesToBeAdded.insert(entity);

    if ((unsigned) entity_id >= this->entityComponentSignatures.size()) {
        this->entityComponentSignatures.resize(entity_id + 1);
    }

    Logger::Info("New Entity created with id: " + std::to_string(entity_id));

    return entity;
}

void Registry::AddEntityToSystem(Entity entity) {
    const auto entity_id = entity.GetId();
    const auto& entity_component_signature = this->entityComponentSignatures[entity_id];

    for (auto& system : this->systems) {
        const auto& system_component_signature = system.second->GetComponentSignature();

        bool is_interested = (entity_component_signature & system_component_signature) == system_component_signature;

        if (is_interested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update() {
    for (auto entity : this->entitiesToBeAdded) {
        this->AddEntityToSystem(entity);
    }

    this->entitiesToBeAdded.clear();
}