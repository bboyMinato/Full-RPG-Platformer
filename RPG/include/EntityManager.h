#pragma once
#include <vector>
#include <memory>

class Entity;

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	void Draw(float dt);
	void Update(float dt);
	void Refresh();

	void AddEntity(Entity* entity);
	void EraseEntity(Entity* entity);
	Entity* CloneEntity(Entity* entity);

	const std::vector<Entity*>& GetEntites() { return entities; }

private:
	std::vector<Entity*> entities;
};