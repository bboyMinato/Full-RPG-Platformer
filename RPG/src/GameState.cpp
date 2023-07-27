#include "GameState.h"
#include "OptionsState.h"
#include "TextureManager.h"
#include "Input.h"
#include "MapParser.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include <iostream>

GameState::GameState(GameDataRef data) : _data(data)
{	

}

void GameState::Init()
{
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
	player->AddComponent<RigidBody>(0.0);
	player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
}

void GameState::HandleEvents()
{
	Input::GetInstance()->HandleEvents();

	if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		_data->_stateManager.AddState(CGameStateRef(new OptionsState(_data)));
}

void GameState::Update(float dt)
{	
	_levelMap->Update();
	manager->Update();
}

void GameState::Render(float dt)
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
			
	_levelMap->Render();		
	manager->Draw();

	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}