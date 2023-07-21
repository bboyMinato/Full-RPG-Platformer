#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "CStateManager.h"
#include "SoundManager.h"
#include "Button.h"
#include "Mouse.h"
#include "Text.h"

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

	static void OpenOptions();

private:
	Engine() {};
	static Engine* _instance;

	GameDataRef _data = std::make_shared<GameData>();

	bool _isRunning = false;
	const float dt = 1.f / 60.f;
			
	SDL_Renderer* _renderer = nullptr;	
};