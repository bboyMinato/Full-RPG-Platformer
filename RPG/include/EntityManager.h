#pragma once
#include <vector>
#include <memory>

class Entity;

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	void Draw();
	void Update();
	void Refresh();

	void AddEntity(Entity* entity);
	void EraseEntity(Entity* entity);
	Entity* CloneEntity(Entity* entity);

private:
	std::vector<std::unique_ptr<Entity>> entities;
};