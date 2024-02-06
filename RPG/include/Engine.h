#pragma once
#include <iostream>
#include <chrono>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "SoundManager.h"
#include "Button.h"
#include "Mouse.h"
#include "Text.h"
#include "GameMap.h"

struct GameData
{
	CStateManager _stateManager;	
	SoundManager _soundManager;
	SDL_Window* _window = nullptr;	
	Text _text;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Engine
{
public:
	static Engine* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Engine(); }
	SDL_Renderer* GetRenderer() { return _renderer; }
	inline bool IsRunning() { return _isRunning; }

	void Init();
	void Clean();
	void Quit();

	void Events();
	void Update();	

	GameMap* GetMap() { return _levelMap; }
	void SetMap(GameMap* Map) { _levelMap = Map; }
	inline float GetDeltaTime() { return deltaTime; }

private:
	Engine() {};
	static Engine* _instance;

	GameDataRef _data = std::make_shared<GameData>();
	SDL_Renderer* _renderer = nullptr;
	GameMap* _levelMap = nullptr;

	bool _isRunning = false;	
	float deltaTime = 0; 


	void FrameRateTest();
};