#pragma once
#include "ECS.h"
#include "Transform.h"

class Entity
{
public:
	Entity()
	{
		AddComponent<Transform>(0, 0);
	}

	virtual ~Entity() {}

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args)
	{
		auto component = std::make_unique<T>(std::forward<TArgs>(args)...);
		component->entity = this;

		const auto typeID = GetComponentTypeID<T>();
		if (component->Init())
		{
			_componentArray[typeID] = component.get();
			_componentBitset[typeID] = true;
			_components.emplace_back(std::move(component));
			return *static_cast<T*>(_componentArray[typeID]);
		}

		throw std::runtime_error("Failed to initialize component");
	}

	template<typename T>
	inline T& GetComponent() const
	{
		const auto typeID = GetComponentTypeID<T>();
        auto ptr = _componentArray[typeID];
        
        if (!ptr) 
            throw std::runtime_error("Component not found");
        
        return *static_cast<T*>(ptr);
	}

	template<typename T>
	inline bool HasComponent() const
	{
		return _componentBitset[GetComponentTypeID<T>()];
	}

	inline bool IsAlive() const
	{
		return active;
	}

	inline void Destroy()
	{
		active = false;
	}

	inline void Draw(float dt)
	{
		for (const auto& component : _components)
			component->Draw(dt);
	}

	inline void Update(float dt)
	{
		for (auto& component : _components)
			component->Update(dt);
	}

private:
	bool active = true;
	ComponentArray _componentArray;
	ComponentBitset _componentBitset;
	std::vector<std::unique_ptr<Component>> _components;
};