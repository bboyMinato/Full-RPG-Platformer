#pragma once

class CGameState
{
public:
	CGameState() {}
	~CGameState() {}

	virtual void Init() = 0;
	virtual void Clean() = 0;

	virtual void Pause() {}
	virtual void Resume() {}

	virtual void HandleEvents() = 0;
	virtual void Render(float dt) = 0;
	virtual void Update(float dt) = 0;
};