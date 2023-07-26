#include "..\include\GameState.h"
#include "..\include\OptionsState.h"
#include "..\include\TextureManager.h"
#include "..\include\Input.h"
#include "..\include\MapParser.h"
#include "..\include\Transform.h"
#include "..\include\Sprite.h"
#include <iostream>

GameState::GameState(GameDataRef data) : _data(data)
{	

}

void GameState::Init()
{
	_animation = new SpriteAnimation();
	_animation->SetProps("EnchantressIdle", 0, 5, 60);

	if (!MapParser::GetInstance()->Load())
		std::cout << "Failed to load the map!" << std::endl;

	_levelMap = MapParser::GetInstance()->GetMap("Level");

	_data->_soundManager.LoadMusic("Rising Sun", "assets\\SFX\\Rising Sun.mp3");
	_data->_soundManager.SetMusicVolume(20);
	_data->_soundManager.PlayMusic(-1);

	manager = new EntityManager();

	Entity* player = new Entity();
	manager->AddEntity(player);
			
	player->GetComponent<Transform>().position = Vector2Df(1000, 100);	
	player->AddComponent<Sprite>(Engine::GetInstance()->GetRenderer(), "ExitButton");	
}

void GameState::HandleEvents()
{
	Input::GetInstance()->HandleEvents();

	if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		_data->_stateManager.AddState(CGameStateRef(new OptionsState(_data)));
}

void GameState::Update(float dt)
{
	_animation->Update();
	_levelMap->Update();
}

void GameState::Render(float dt)
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
			
	_levelMap->Render();	
	_animation->Draw(100, 100, 128, 70, 1, 1);
	manager->Draw();

	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}

