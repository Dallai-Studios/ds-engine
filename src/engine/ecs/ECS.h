#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include "../../tools/logger/Logger.h"

#define MAX_COMPONENTS 32

// In using a bitset, to keep track of witch components an entity has,
// and also helps keep track of wich entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity {
    private:
        int id;

    public:
        Entity(int id) : id(id) {};
        int GetId() const;

    public: 
        bool operator == (const Entity& other) const { return this->id == other.GetId(); }
        bool operator != (const Entity& other) const { return this->id != other.GetId(); } 
        bool operator > (const Entity& other) const { return id > other.id; }
        bool operator < (const Entity& other) const { return id < other.id; }
};

// This IComponent works like an interface fore every component created in the game
// every component will have a nextId value that will be used to identify the component.
// also, the component will be a generic template class so this will help to keep things
// a little less verbose.
struct IComponent {
    protected:
        static int nextId;
};

template <typename TComponent> 
class Component : public IComponent {
    /**
     * @brief Returns the current id of the component.
    */
    static int GetId() { //this is already defined to make things more convinient
        static int id = nextId++;
        return id;
    }
};

// The system processes entities that contains a specific signature
class System {
    private: 
        // Signature of the components the system is interested in
        Signature componentSignature;

        std::vector<Entity> entities;

    public:
        System() = default;
        virtual ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetEntities() const;
        const Signature& GetComponentSignature() const;
        template <typename TComponent> void RequireComponent();
};

template <typename TComponent> 
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(this->componentSignature.set(componentId));
}

// this interface is just here because I want to have a vector of pools
// and I need a way to store all the pools in the same vector
// using some Pool default class I cant do that; So I created this interface
// to be able to use the a Pool class as template
class IPool { 
    public: 
        virtual ~IPool() = default;
};

// Just the template class to be used as a pool for the components
template <typename T> 
class Pool : public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(unsigned int size) { data.resize(size); }
        virtual ~Pool() { this->Clear(); }
        
        /**
         * @brief Function that return if the current data pool is empty or not
        */
        bool IsEmpty() const { 
            return data.empty(); 
        }

        /**
         * @brief Returns the size o the current data pool
        */
        int GetSize() const { 
            return data.size(); 
        }

        void Resize(int newSize) { data.resize(newSize); }
        
        void Clear() { data.clear(); }
        
        void Add(T object) { data.push_back(object); }
        
        void Set(int index, T object) { data[index] = object; }
        
        T& Get(int index) { return static_cast<T&>(data[index]); }

    public:
        T& operator [] (unsigned int index) { return data[index]; }
};


// this is the most important class of the ECS cus it will handle all the entities, components and systems.
// in matter of fact, this class will be the one that will create the entities, add components to them, 
// add systems to the game.
class Registry {
    private:
        // Keep track of how many entities were added to the scene
        int entitiesCount = 0;

        // I need I way to keep track of everything that will be added or destroyed
        // but at the same time no entity can be added or destroyed during the update loop
        // so this sets of entities will be use to store the entities that will be added or destroyed 
        // at the end of the update life cycle
        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeDestroyed;
 
        // vector of component pools
        // each pool contains all the data for a certain component type
        // [vector index = compontentId], [pool index = entityId]
        std::vector<std::shared_ptr<IPool>> componentPools;

        // vector of component signatures
        // the signature let me know wich component is turned "on" or "off" for a given entity
        // [vector index = entityId]
        std::vector<Signature> entityComponentSignatures; 

        // map of active systems
        // [index = system typeId]
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

        template <typename TSystem> std::type_index GetSystemTypeIndex() const;
 
    public:
        Registry() = default;

        //Entity Management
        Entity CreateEntity();

        // Component Management
        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename TComponent> bool HasComponent(Entity entity) const;
        // template <typename TComponent> TComponent& GetComponent(Entity entity);
        template <typename TComponent> void RemoveComponent(Entity entity);

        // System management
        template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename TSystem> void RemoveSystem();
        template <typename TSystem> bool HasSystem() const;
        template <typename TSystem> TSystem& GetSystem() const;

        void AddEntityToSystem(Entity entity);

        /**
         * @brief This function must be called to commit all the entities that were added or destroyed.
         * since you can't directly add or destroy entities during the update loop, you must use this function
         * to commit all the entities that were added or destroyed.
        */
        void Update();
};

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args) {
    const auto already_has_component = this->HasComponent<TComponent>(entity);

    if (already_has_component) {
        Logger::Error("There is already a component like that inside the provided entity");
        return;
    }

    const auto entity_id = entity.GetId();
    const auto component_id = Component<TComponent>::GetId();

    if (component_id >= this->componentPools.size()) {
        this->componentPools.resize(component_id + 1, nullptr);
    }

    if (!this->componentPools[component_id]) {
        std::shared_ptr<Pool<TComponent>> new_component_pool = std::make_shared<Pool<TComponent>>();
        this->componentPools[component_id] = new_component_pool;
    }

    std::shared_ptr<Pool<TComponent>> pool = 
        std::static_pointer_cast<Pool<TComponent>>(this->componentPools[component_id]);
    
    if (entity_id >= pool->GetSize()) pool->Resize(this->entitiesCount);

    TComponent new_component(std::forward<TArgs>(args)...);

    this->entityComponentSignatures[entity_id].set(component_id);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const auto entity_id = entity.GetId();
    const auto component_id = Component<TComponent>::GetId();

    return this->entityComponentSignatures[entity_id].test(component_id);
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const auto entity_id = entity.GetId();
    const auto component_id = Component<TComponent>::GetId();

    if (!this->HasComponent<TComponent>()) {
        Logger::Error("Trying to remove a component that does not exist");
        return;
    }

    this->entityComponentSignatures[entity_id].set(component_id, false);
}

template <typename TSystem> 
std::type_index Registry::GetSystemTypeIndex() const { 
    const auto system_typeid = typeid(TSystem);
    const auto system_type_index = std::type_index(system_typeid);
    return system_type_index;
}

template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs &&...args) {
    std::shared_ptr<TSystem> new_system = std::make_shared<TSystem>(std::forward<TArgs>(args)...);

    const auto system_type_index = this->GetSystemTypeIndex<TSystem>();
    const auto key_pair = std::make_pair(system_type_index, new_system);

    this->systems.insert(key_pair);
}

template <typename TSystem> 
bool Registry::HasSystem() const {
    const auto system_type_index = this->GetSystemTypeIndex<TSystem>();
    auto found_system = this->systems.find(system_type_index);
    return found_system != this->systems.end();
}

template <typename TSystem> 
TSystem& Registry::GetSystem() const {
    const bool has_system = this->HasSystem<TSystem>();
    
    if (!has_system) {
        Logger::Error("Trying to get a system that does not exist");
        return NULL;
    }

    const auto system_type_index = this->GetSystemTypeIndex<TSystem>();
    const auto system = this->systems.find(system_type_index);
    return *std::static_pointer_cast<TSystem>(system->second);
}

template <typename TSystem> 
void Registry::RemoveSystem() {
    const bool has_system = this->HasSystem<TSystem>();
    
    if (!has_system) {
        Logger::Warn("Trying to remove a system that does not exists");
        return;
    }

    const auto system_type_index = this->GetSystemTypeIndex<TSystem>();

    this->systems.erase(system_type_index);
}