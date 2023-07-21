#include "..\include\OptionsState.h"
#include "..\include\MainMenuState.h"
#include "..\include\TextureManager.h"
#include "..\include\Input.h"

OptionsState::OptionsState(GameDataRef data) : _data(data)
{
}

void OptionsState::Init()
{
	
}

void OptionsState::HandleEvents()
{
	Input::GetInstance()->HandleEvents();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F1))
		_data->_stateManager.PopCurrentState();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5))
	{
		_data->_stateManager.PopCurrentState();
		_data->_stateManager.AddState(CGameStateRef(new MainMenuState(_data)), true);
	}
}

void OptionsState::Update(float dt)
{
}

void OptionsState::Render(float dt)
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
	
	TextureManager::GetInstance()->Draw("OptionsMenuBackground", 0, 0, 1920, 1080);

	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}
