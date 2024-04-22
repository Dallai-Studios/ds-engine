#pragma once
#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>

#define MAX_COMPONENTS 32

// In using a bitset, to keep track of witch components an entity has,
// and also helps keep track of wich entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

class Entity {
    private:
        int id;

    public:
        Entity(int id) : id(id) {};
        int GetId() const;

    // Operators overloading
    public: 
        bool operator == (const Entity& other) const { return this->id == other.GetId(); }
        bool operator != (const Entity& other) const { return this->id != other.GetId(); } 
};

template <typename T> 
class Component : public IComponent {
    static int GetId() {
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
        template <typename T> void RequireComponent();
};

template <typename T> 
void System::RequireComponent() {
    const auto componentId = Component<T>::GetId();
    componentSignature.set(this->componentSignature.set(componentId));
}

class IPool { 
    public: 
        virtual ~IPool() = default;
};

template <typename T> 
class Pool : public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(unsigned int size) { data.resize(size); }
        virtual ~Pool() { this->Clear(); }

        bool IsEmpty() const { return data.empty(); }
        int GetSize() const { return data.size(); }
        void Resize(int newSize) { data.resize(newSize); }
        void Clear() { data.clear(); }
        void Add(T object) { data.push_back(object); }
        void Set(int index, T object) { data[index] = object; }
        T& Get(int index) { return static_cast<T&>(data[index]); }
        T& operator [] (unsigned int index) { return data[index]; }
};

class Registry {
    private:
        // Keep track of how many entities were added to the scene
        int entitiesCount = 0;

        // vector of component pools
        // each pool contains all the data for a certain component type
        // [vector index = compontentId], [pool index = entityId]
        std::vector<IPool*> componentPools;

        // vector of component signatures
        // the signature lets us know wich component is turned "on" or "off" for an entity
        // [vector index = entityId]
        std::vector<Signature> entityComponentSignatures; 

        // map of active systems
        // [index = system typeId]
        std::unordered_map<std::type_index, System*> systems;
 

};