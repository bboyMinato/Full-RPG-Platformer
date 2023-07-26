#pragma once
#include <vector>
#include <bitset>
#include <memory>
#include <algorithm>
#include <array>
#include <cassert>

class Component;
class Entity;

using ComponentTypeID = std::size_t;

inline ComponentTypeID GetComponentID()
{
	static ComponentTypeID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentTypeID GetComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "Type not based on component!");
	static const ComponentTypeID typeID = GetComponentID();
	return typeID;
}

constexpr std::size_t MAX_ENTITIES = 5000;
constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;


class Component
{
public:
	Entity* entity = nullptr;

	virtual bool Init() { return true; }
	virtual void Draw() {}
	virtual void Update() {}
private:

};

class Entity
{
public:
	Entity() 
	{
		
	}

	virtual ~Entity() {}

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args)
	{
		T* component(new T(std::forward<TArgs>(args)...));
		std::unique_ptr<Component> uptr { component };
		_components.emplace_back(std::move(uptr));

		if (component->Init())
		{
			_componentArray[GetComponentTypeID<T>()] = component;
			_componentBitset[GetComponentTypeID<T>()] = true;
			component->entity = this;
			return *component;
		}

		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	inline T& GetComponent() const
	{				
		auto ptr(_componentArray[GetComponentTypeID<T>()]);
		return *reinterpret_cast<T*>(ptr);
	}

	template<typename T>
	inline bool  HasComponent() const
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

	inline void Draw()
	{
		for (auto& component : _components)
			component->Draw();
	}

	inline void Update()
	{
		for (auto& component : _components)
			component->Update();
	}

private:
	bool active = true;
	ComponentArray _componentArray;
	ComponentBitset _componentBitset;
	std::vector<std::unique_ptr<Component>> _components;
};
