#pragma once
#include "CGameState.h"
#include "Engine.h"
#include "Vector2D.h"
#include "ECS.h"

class MainMenuState : public CGameState
{
public:
	MainMenuState(GameDataRef data);

	void Init();

	void HandleEvents();
	void Update(float dt);
	void Render(float dt);

	void Clean() {}


private:
	GameDataRef _data;	
	Vector2D<int> mousepos;
	Button* playButton = nullptr;
	Button* optionsButton = nullptr;
	Button* exitButton = nullptr;

	Button* test = nullptr;

	Uint32 x = 0, y = 0;
};

