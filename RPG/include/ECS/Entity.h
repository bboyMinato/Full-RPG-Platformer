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
		T* component(new T(std::forward<TArgs>(args)...));
		component->entity = this;
		std::unique_ptr<Component> uptr { component };
		_components.emplace_back(std::move(uptr));	

		if (component->Init())
		{
			_componentArray[GetComponentTypeID<T>()] = component;
			_componentBitset[GetComponentTypeID<T>()] = true;
			
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

	/*inline bool IsAlive() const
	{
		return active;
	}

	inline void Destroy()
	{
		active = false;
	}*/

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
	//bool active = true;
	ComponentArray _componentArray;
	ComponentBitset _componentBitset;
	std::vector<std::unique_ptr<Component>> _components;
};