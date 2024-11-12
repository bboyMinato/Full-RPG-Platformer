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

GameState::~GameState()
{
	delete manager;
	manager = nullptr; 

	delete collisionSystem;
	collisionSystem = nullptr;

	delete _animation;
	_animation = nullptr;

	delete _levelMap;
	_levelMap = nullptr;

	delete Player;
	Player = nullptr;

	delete Enemy;
	Enemy = nullptr;
}

void GameState::Init()
{
	const std::string keyBindingsFile = "config/keybinds.ini";
	std::ifstream file(keyBindingsFile);

	if (file.good())
	{
		keyMapping.LoadKeyBindings(keyMapping, keyBindingsFile);
		std::cout << "Key bindings successfully loaded." << std::endl;
	}
	else
	{
		throw std::runtime_error("Error: Could not open file " + keyBindingsFile);
	}

	file.close();

	if (!MapParser::GetInstance()->Load())
		std::cout << "Failed to load the map!" << std::endl;

	_levelMap = MapParser::GetInstance()->GetMap("Level");	
	Engine::GetInstance()->SetMap(_levelMap);

	_data->_soundManager.LoadMusic("Ambient 1", "assets\\SFX\\Ambient 1.mp3");
	_data->_soundManager.SetMusicVolume(20);
	_data->_soundManager.PlayMusic(-1);
	
	_data->_soundManager.SetMusicVolume(0);

	manager = new EntityManager();
	collisionSystem = new CollisionSystem();

	Player = new Entity();
	manager->AddEntity(Player);

	Enemy = new Entity(); 
	manager->AddEntity(Enemy);
	
	Player->GetComponent<Transform>().Position = Vector2Df(1000, 500);
	Player->GetComponent<Transform>().scale.X = 5;
	SpriteAnimation PlayerSprite = Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);	
	Player->AddComponent<RigidBody>(1.f);
	Player->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Player->AddComponent<BoxCollider2D>(PlayerSprite.GetWidth(), PlayerSprite.GetHeight(), "Character");
	Player->AddComponent<PlayerController>().SetKeyMapping(keyMapping);

	Enemy->GetComponent<Transform>().Position = Vector2Df(300, 500);
	Enemy->GetComponent<Transform>().scale.X = 5;
	SpriteAnimation EnemySprite = Enemy->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Enemy->AddComponent<RigidBody>(1.f);
	Enemy->AddComponent<SpriteAnimation>("EnchantressIdle", 60, 0, 5, true);
	Enemy->AddComponent<BoxCollider2D>(PlayerSprite.GetWidth(), PlayerSprite.GetHeight(), "Character");
}

void GameState::HandleEvents()
{
	Input::GetInstance()->HandleEvents();

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		_data->_stateManager.AddState(CGameStateRef(new OptionsState(_data)));
	}
}

void GameState::Update(float dt)
{	
	_levelMap->Update();
	manager->Update(dt);	
	collisionSystem->Update(manager->GetEntites());
}

void GameState::Render(float dt)
{
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());
		
	_levelMap->Render();		
	manager->Draw(dt);
	
	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}