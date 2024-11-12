#pragma once
#include "CGameState.h"
#include "Engine.h"
#include "SpriteAnimation.h"
#include "GameMap.h"
#include "ECS.h"
#include "EntityManager.h"
#include "CollisionSystem.h"
#include "KeyMapping.h"

class GameState : public CGameState
{
public:
	GameState() {};
	GameState(GameDataRef data);
	~GameState();

	void Init();

	void HandleEvents();
	void Update(float dt);
	void Render(float dt);
	
	void Clean() {}
	
	GameMap* GetMap() { return _levelMap; }
	
private:
	GameDataRef _data;
	EntityManager* manager = nullptr;
	CollisionSystem* collisionSystem = nullptr;
	SpriteAnimation* _animation = nullptr;
	GameMap* _levelMap = nullptr;
	
	Entity* Player = nullptr;
	Entity* Enemy = nullptr; 

	KeyMapping keyMapping;
};

