#include "..\include\Engine.h"
#include "..\include\TextureManager.h"
#include "..\include\Input.h"
#include "..\include\SplashState.h"
#include "..\include\OptionsState.h"
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
	
	_data->_window = SDL_CreateWindow("RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1024, 0);

	if (_data->_window == nullptr)
		std::cout << "Window has failed to initialize! Error: " << SDL_GetError() << std::endl;

	_renderer = SDL_CreateRenderer(_data->_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr)
		std::cout << "Renderer has failed to initialize! Error: " << SDL_GetError() << std::endl;	
	
	_data->_text.LoadFont("Anime Kids", "assets\\Fonts\\Anime Kids\\Anime Kids.otf", 85);		

	_data->_stateManager.AddState(CGameStateRef(new SplashState(_data)));	
}

void Engine::Clean()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_data->_window);
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
	Uint32 currentTime, newTime;
	float frameTime, interpolation;

	currentTime = SDL_GetTicks();
	float accumlator = 0.0f;

	while (_isRunning)
	{
		_data->_stateManager.ProccessStateChange();

		newTime = SDL_GetTicks();

		frameTime = newTime - currentTime;		

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumlator += frameTime;		

		while (accumlator >= dt)
		{
			_data->_stateManager.GetCurrentState()->HandleEvents();
			_data->_stateManager.GetCurrentState()->Update(dt);

			accumlator -= dt;
		}

		interpolation = accumlator / dt;
		_data->_stateManager.GetCurrentState()->Render(interpolation);
	}	
}

void Engine::OpenOptions()
{
	_data->_stateManager.AddState(CGameStateRef(new OptionsState(_data)), true);
}