#include "GameState.h"
#include "OptionsState.h"
#include "TextureManager.h"
#include "Input.h"
#include "MapParser.h"
#include "Transform.h"
#include "Sprite.h"
#include "RigidBody.h"
#include "PlayerController.h"
#include "BoxCollider2D.h"
#include <iostream>
#include "Collision.h"

GameState::GameState(GameDataRef data) : _data(data)
{	

}

void GameState::Init()
{
	if (!MapParser::GetInstance()->Load())
		std::cout << "Failed to load the map!" << std::endl;

	_levelMap = MapParser::GetInstance()->GetMap("Level");	
	Engine::GetInstance()->SetMap(_levelMap);

	_data->_soundManager.LoadMusic("Ambient 1", "assets\\SFX\\Ambient 1.mp3");
	_data->_soundManager.SetMusicVolume(20);
	_data->_soundManager.PlayMusic(-1);
	
	manager = new EntityManager();

	Player = new Entity();
	manager->AddEntity(Player);
	
	Player->GetComponent<Transform>().Position = Vector2Df(1000, 500);
	SpriteAnimation PlayerSprite = Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Player->AddComponent<RigidBody>(0.05f);
	Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Player->AddComponent<BoxCollider2D>(PlayerSprite.GetWidth(), PlayerSprite.GetHeight());
	Player->AddComponent<PlayerController>();
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