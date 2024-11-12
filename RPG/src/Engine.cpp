#include "Engine.h"
#include "TextureManager.h"
#include "Input.h"
#include "SplashState.h"
#include "OptionsState.h"
#include "GameState.h"
Engine* Engine::_instance = nullptr;

void Engine::Init()
{
	_isRunning = true;

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)))
		std::cout << "IMG_Init has failed: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "TTF library not initialized! Error: " << TTF_GetError() << std::endl;
	
	_window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1024, 0);

	if (_window == nullptr)
		std::cout << "Window has failed to initialize! Error: " << SDL_GetError() << std::endl;

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr)
		std::cout << "Renderer has failed to initialize! Error: " << SDL_GetError() << std::endl;	
	
	_data->_text.LoadFont("Anime Kids", "assets\\Fonts\\Anime Kids\\Anime Kids.otf", 85);		
	
	TextureManager::GetInstance()->ParseTexture("assets\\img\\textures.xml");

	//_data->_stateManager.AddState(CGameStateRef(new SplashState(_data)));	
	_data->_stateManager.AddState(CGameStateRef(new GameState(_data)), true);
}

void Engine::Clean()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	TextureManager::GetInstance()->Clean();
	_data->_text.Clean();
}

void Engine::Quit()
{
}

void Engine::Events()
{
	Input::GetInstance()->HandleEvents();
}

void Engine::Update()
{		
	Uint64 lastCounter = SDL_GetPerformanceCounter();
	float freq = (float)SDL_GetPerformanceFrequency();
	const float maxDeltaTime = 0.1f; // Cap deltaTime to 0.1s (10 FPS)
	const float targetDeltaTime = 1.0f / 60.0f; // Target ~60 FPS

	while (_isRunning)
	{
		Uint64 currentCounter = SDL_GetPerformanceCounter();
		deltaTime = (float)(currentCounter - lastCounter) / freq;
		lastCounter = currentCounter;

		if (deltaTime > maxDeltaTime)
		{
			deltaTime = maxDeltaTime;
		}

		_data->_stateManager.ProccessStateChange();
		_data->_stateManager.GetCurrentState()->HandleEvents();
		_data->_stateManager.GetCurrentState()->Update(deltaTime);
		_data->_stateManager.GetCurrentState()->Render(deltaTime);

		// Calculate delay to maintain target frame rate
		Uint64 frameEndCounter = SDL_GetPerformanceCounter();
		float frameTime = (float)(frameEndCounter - currentCounter) / freq;
		if (frameTime < targetDeltaTime) {
			SDL_Delay((Uint32)((targetDeltaTime - frameTime) * 1000.0f));
		}
	}
}