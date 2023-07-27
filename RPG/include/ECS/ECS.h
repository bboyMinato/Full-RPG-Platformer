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