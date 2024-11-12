#include "EntityManager.h"
#include "Entity.h"

void EntityManager::Draw(float dt)
{
	for (auto& entity : entities)
		entity->Draw(dt);
}

void EntityManager::Update(float dt)
{
	for (auto& entity : entities)
		entity->Update(dt);
}

void EntityManager::Refresh()
{
}

void EntityManager::AddEntity(Entity* entity)
{
	entities.emplace_back(entity);
}

void EntityManager::EraseEntity(Entity* entity)
{
}

Entity* EntityManager::CloneEntity(Entity* entity)
{
	return nullptr;
}