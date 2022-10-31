// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file    ECS.h
 * @brief   Declares all the necessary tools used for
 *          Entity->Component->System pattern
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved. @
 *
 ******************************************************************************
 */

#ifndef ECS_H
#define ECS_H

#include "../Logger/Logger.h"
#include <vector>
#include <bitset>
#include <set>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <deque>

const unsigned int MAX_COMPONENTS = 32;

/**
////////////////////////////////////////////////////////////////////////////////
//@category Signature
////////////////////////////////////////////////////////////////////////////////
//@brief    We use a bitset (1s and 0s) to keep track of which components an
//          entity has, and also helps keep track of which entities a
//          system is interested in.
////////////////////////////////////////////////////////////////////////////////
 */
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
    static int nextId;
};

template <typename T>
class Component : public IComponent
{
public:
    // Returns the unique id of Component<T>
    static int GetId()
    {
        static auto id = nextId++;
        return id;
    }
};

/**
////////////////////////////////////////////////////////////////////////////////
//@class    Entity
////////////////////////////////////////////////////////////////////////////////
//@brief    The entity is what all componenets and systems integrate with
////////////////////////////////////////////////////////////////////////////////
 */
class Entity
{
private:
    int id;

public:
    Entity(int id) : id(id){};
    Entity(const Entity &entity) = default;

    int GetId() const;
    void Kill();
    Entity &operator=(const Entity &other) = default;
    bool operator==(const Entity &other) const { return id == other.id; };
    bool operator!=(const Entity &other) const { return id != other.id; };
    bool operator>(const Entity &other) const { return id > other.id; };
    bool operator<(const Entity &other) const { return id < other.id; };

    template <typename TComponent, typename... TArgs>
    Entity AddComponent(TArgs &&...args) const;

    template <typename TComponent>
    Entity RemoveComponent() const;

    template <typename TComponent>
    bool HasComponent() const;

    template <typename TComponent>
    TComponent &GetComponent() const;

    class Registry *registry;
};

/**
////////////////////////////////////////////////////////////////////////////////
//@class    System
////////////////////////////////////////////////////////////////////////////////
//@brief    The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
 */
class System
{
private:
    Signature componentSignature;
    std::vector<Entity> entities;

public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEnitityfromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    const Signature &GetComponentSignature() const;

    // Defines the component type that entities must have to be considered by the system
    template <typename TComponent>
    void RequireComponent();
};

/**
////////////////////////////////////////////////////////////////////////////////
// @class  Pool
////////////////////////////////////////////////////////////////////////////////
// @brief  A pool is just a vector (contiguous data) of objects of type T
////////////////////////////////////////////////////////////////////////////////
 */
class IPool
{
public:
    virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;

public:
    Pool(int size = 100) { data.resize(size); }
    virtual ~Pool() = default;

    bool isEmpty() const { return data.empty(); }

    int GetSize() const { return data.size(); }

    void Resize(int n) { data.resize(n); }

    void Clear() { data.clear(); }

    void Add(T object) { data.push_back(object); }

    void Set(int index, T object) { data[index] = object; }

    T &Get(int index) { return static_cast<T &>(data[index]); }

    T &operator[](unsigned int index) { return data[index]; }
};

/**
////////////////////////////////////////////////////////////////////////////////
//@class    Registry
////////////////////////////////////////////////////////////////////////////////
//@brief    The registry manages the creation and destruction of entities,
//          add systems, and components.
////////////////////////////////////////////////////////////////////////////////
 */
class Registry
{
private:
    int numEntities = 0;

    // Vector of component pools, each pool contains all the data for a certain component type
    // [Vector index = component type id]
    // [Pool index = entity id]
    std::vector<std::shared_ptr<IPool>> componentPools;

    // Vector of component signatures per entity, saying which component is turned "on" for a given entity
    // [Vector index = entity id]
    std::vector<Signature> entityComponentSignatures;

    // Map of active systems
    // [Map key = system type id]
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

    // Set of entities that are flagged to be added or removed in the next registry Update()
    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

    std::deque<int> freeIds;

public:
    Registry()
    {
        Logger::Log("Registry created");
    };

    ~Registry()
    {
        Logger::Log("Registry Destroyed");
    };

    // The Registry Update() finally processes the entities that are waiting to be created or killed to the systems
    void Update();

    // Entity management
    Entity CreateEntity();

    void KillEntity(Entity entity);

    /**
     ////////////////////////////////////////////////////////////////////////////////
     // @name Component management.
     ////////////////////////////////////////////////////////////////////////////////
     // @brief Methods used for component managment in the Registry
     ////////////////////////////////////////////////////////////////////////////////
     @{
     */
    /**
     // @brief Add a component to the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TComponent, typename... TArgs>
    Registry *AddComponent(Entity entity, TArgs &&...args);

    /**
     // @brief Remove a component from the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TComponent>
    Registry *RemoveComponent(Entity entity);

    /**
     // @brief Check wether the Registry has a component
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TComponent>
    bool HasComponent(Entity entity) const;

    /**
     // @brief Retrieve a component from the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TComponent>
    TComponent &GetComponent(Entity entity) const;
    /**
     @}
     ////////////////////////////////////////////////////////////////////////////////
    */

    /**
     ////////////////////////////////////////////////////////////////////////////////
     // @name System management.
     ////////////////////////////////////////////////////////////////////////////////
     // @brief Methods used for system managment in the Registry
     ////////////////////////////////////////////////////////////////////////////////
     @{
     */
    /**
     // @brief Add a system to the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TSystem, typename... TArgs>
    Registry *AddSystem(TArgs &&...args);

    /**
     // @brief Remove a system from the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TSystem>
    Registry *RemoveSystem();

    /**
     // @brief Check to see if Registry has the system
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TSystem>
    bool HasSystem() const;

    /**
     // @brief Retrieve the system from the Registry
     ////////////////////////////////////////////////////////////////////////////////
     */
    template <typename TSystem>
    TSystem &GetSystem() const;

    /**
     // @brief Checks the component signature of an entity and adds the entity to the systems
     //        that are interested in it
     ////////////////////////////////////////////////////////////////////////////////
     */
    void AddEntityToSystems(Entity entity);

    /**
     // @brief Checks the component signature of an entity and removes the entity from the systems
     //        that are interested in it
     ////////////////////////////////////////////////////////////////////////////////
     */
    void RemoveEntityFromSystems(Entity entity);
    /**
     @}
     ////////////////////////////////////////////////////////////////////////////////
    */
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
};

template <typename TComponent, typename... TArgs>
Registry *Registry::AddComponent(Entity entity, TArgs &&...args)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size())
        componentPools.resize(componentId + 1, nullptr);

    if (!componentPools[componentId])
        componentPools[componentId] = std::make_shared<Pool<TComponent>>();

    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if (entityId >= componentPool->GetSize())
        componentPool->Resize(numEntities);

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);

    entityComponentSignatures[entityId].set(componentId);

    Logger::Log("Component id = " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
    return this;
};

template <typename TComponent>
Registry *Registry::RemoveComponent(Entity entity)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();
    entityComponentSignatures[entityId].set(componentId, false);

    Logger::Log("Component id = " + std::to_string(componentId) + " was removed from entity id " + std::to_string(entityId));
    
    return this;
};

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const
{
    return entityComponentSignatures[entity.GetId()]
        .test(Component<TComponent>::GetId());
};

template <typename TComponent>
TComponent &Registry::GetComponent(Entity entity) const
{
    return std::static_pointer_cast<Pool<TComponent>>(
               componentPools[Component<TComponent>::GetId()])
        ->Get(entity.GetId());
};

template <typename TSystem, typename... TArgs>
Registry *Registry::AddSystem(TArgs &&...args)
{
    systems.insert(
        std::make_pair(
            std::type_index(typeid(TSystem)),
            std::make_shared<TSystem>(std::forward<TArgs>(args)...)));
    return this;
};

template <typename TSystem>
Registry *Registry::RemoveSystem()
{
    systems.erase(
        systems.find(
            std::type_index(typeid(TSystem))));
    return this;
};

template <typename TSystem>
bool Registry::HasSystem() const
{
    return systems.find(std::type_index(typeid(TSystem))) != systems.end();
};

template <typename TSystem>
TSystem &Registry::GetSystem() const
{
    return *(
        std::static_pointer_cast<TSystem>(
            systems.find(std::type_index(typeid(TSystem)))->second));
};

template <typename TComponent, typename... TArgs>
Entity Entity::AddComponent(TArgs &&...args) const
{
    registry->AddComponent<TComponent>(
        *this,
        std::forward<TArgs>(args)...);
    return *this;
};

template <typename TComponent>
Entity Entity::RemoveComponent() const
{
    registry->RemoveComponent<TComponent>(*this);
    return *this;
};

template <typename TComponent>
bool Entity::HasComponent() const
{
    return registry->HasComponent<TComponent>(*this);
};

template <typename TComponent>
TComponent &Entity::GetComponent() const
{
    return registry->GetComponent<TComponent>(*this);
};

#endif /* __ECS_H__ */