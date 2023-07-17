#pragma once
#include "CGameState.h"
#include "Engine.h"

class OptionsState : public CGameState
{
public:
	OptionsState(GameDataRef data);

	void Init();

	void HandleEvents();
	void Update(float dt);
	void Render(float dt);

	void Clean() {}

private:
	GameDataRef _data;
};

