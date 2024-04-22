#pragma once
#include <bitset>
#include <vector>

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

class Registry {
    private:
        int entitiesCount = 0;

    public: 
        Registry() = default;

        ~Registry() = default;

        
};