#pragma once
#include "CGameState.h" 
#include "Engine.h"
#include "Input.h"
#include "TextureManager.h"
#include <iostream>

class SplashState : public CGameState
{
public:
	SplashState(GameDataRef data);

	void Init();

	void HandleEvents();
	void Update(float dt);
	void Render(float dt);

	void Clean() {}

private:
	GameDataRef _data;	
	Uint32 timer = 0;
};

