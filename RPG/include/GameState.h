#pragma once
#include "CGameState.h"
#include "Engine.h"
#include "SpriteAnimation.h"
#include "GameMap.h"

class GameState : public CGameState
{
public:
	GameState(GameDataRef data);

	void Init();

	void HandleEvents();
	void Update(float dt);
	void Render(float dt);

	void Clean() {}

private:
	GameDataRef _data;
	SpriteAnimation* _animation = nullptr;
	GameMap* _levelMap = nullptr;
};

