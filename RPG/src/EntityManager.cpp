#include "..\include\EntityManager.h"
#include "..\include\Entity.h"

void EntityManager::Draw()
{
	for (auto& entity : entities)
		entity->Draw();
}

void EntityManager::Update()
{
	for (auto& entity : entities)
		entity->Update();
}

void EntityManager::Refresh()
{
}

void EntityManager::AddEntity(Entity* entity)
{
	std::unique_ptr<Entity> uniquePtr{entity};
	entities.emplace_back(std::move(uniquePtr));
}

void EntityManager::EraseEntity(Entity* entity)
{
}

Entity* EntityManager::CloneEntity(Entity* entity)
{
	return nullptr;
}