#include "..\include\SplashState.h"
#include "..\include\Input.h"
#include "..\include\MainMenuState.h"

SplashState::SplashState(GameDataRef data) : _data(data)
{
	
}

void SplashState::Init()
{
	
}

void SplashState::HandleEvents()
{
	Input::GetInstance()->HandleEvents();	
}

void SplashState::Update(float dt)
{
	timer = SDL_GetTicks() / 1000.f;

	if (timer > 3 || Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
	{		
		_data->_stateManager.AddState(CGameStateRef(new MainMenuState(_data)), true);
	}
}

void SplashState::Render(float dt)
{	
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	TextureManager::GetInstance()->Draw("SplashScreenBackground", 0, 0, 1920, 1080);

	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}
