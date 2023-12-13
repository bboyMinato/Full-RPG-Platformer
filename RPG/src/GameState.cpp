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

	_data->_soundManager.LoadMusic("Rising Sun", "assets\\SFX\\Rising Sun.mp3");
	_data->_soundManager.SetMusicVolume(20);
	_data->_soundManager.PlayMusic(-1);
	
	manager = new EntityManager();

	Player = new Entity();
	manager->AddEntity(Player);

	Test = new Entity(); 
	manager->AddEntity(Test);
	
	Player->GetComponent<Transform>().position = Vector2Df(1000, 500);
	SpriteAnimation sprite = Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Player->AddComponent<RigidBody>(0.0f);
	Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Player->AddComponent<BoxCollider2D>(sprite.GetWidth(), sprite.GetHeight());
	Player->AddComponent<PlayerController>();

	Test->GetComponent<Transform>().position = Vector2Df(500, 100);
	SpriteAnimation TestSprite = Test->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);	
	Test->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	//Test->AddComponent<BoxCollider2D>(TestSprite.GetWidth(), TestSprite.GetHeight());
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