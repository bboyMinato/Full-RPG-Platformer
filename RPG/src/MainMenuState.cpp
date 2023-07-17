#include "..\include\MainMenuState.h"
#include "..\include\OptionsState.h"
#include "..\include\GameState.h"
#include "..\include\TextureManager.h"
#include "..\include\Input.h"
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{		
}

void MainMenuState::Init()
{
	TextureManager::GetInstance()->LoadTexture("Main Menu Background", "assets\\faith-spark-background1.jpg");

	_data->_soundManager.LoadMusic("Main Menu Music", "assets\\SFX\\Ambient 1.mp3");	
	_data->_soundManager.SetMusicVolume(20);
	_data->_soundManager.PlayMusic(-1);	

	std::string MainMenuText = "RPG Platformer";
	SDL_Color red = { 255, 0, 0, 0 };
	_data->_text.CreateText("Main Menu Text", MainMenuText, _data->_text.GetFont("Anime Kids"), red);

	playButton = new Button("Play Button", "assets\\Button1.png", 850, 400);
	optionsButton = new Button("Options Button", "assets\\OptionsButton.png", 850, 600);
	exitButton = new Button("Exit Button", "assets\\ExitButton.png", 850, 800);

	test = new Button("Test Button", "assets\\Button1.png", 100, 100, Engine::GetInstance()->OpenOptions());
}

void MainMenuState::HandleEvents()
{	
	Input::GetInstance()->HandleEvents();	

	SDL_Point point = { mousepos.X, mousepos.Y };

	if (Input::GetInstance()->GetMouseDown(SDL_BUTTON_LEFT) && SDL_PointInRect(&point, &playButton->GetRect()))
		_data->_stateManager.AddState(CGameStateRef(new GameState(_data)), true);	

	if (Input::GetInstance()->GetMouseDown(SDL_BUTTON_LEFT) && SDL_PointInRect(&point, &optionsButton->GetRect()))
		_data->_stateManager.AddState(CGameStateRef(new OptionsState(_data)), true);

	if (Input::GetInstance()->GetMouseDown(SDL_BUTTON_LEFT) && SDL_PointInRect(&point, &exitButton->GetRect()))
		SDL_Quit();	
}

void MainMenuState::Update(float dt)
{	
	mousepos = Input::GetInstance()->GetMousePosition();
}

void MainMenuState::Render(float dt)
{	
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 200, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Engine::GetInstance()->GetRenderer());

	TextureManager::GetInstance()->Draw("Main Menu Background", 0, 0, 1920, 1080);		
	TextureManager::GetInstance()->Draw("Play Button", playButton->GetRect().x, playButton->GetRect().y, playButton->GetRect().w, playButton->GetRect().h);
	TextureManager::GetInstance()->Draw("Options Button", optionsButton->GetRect().x, optionsButton->GetRect().y, optionsButton->GetRect().w, optionsButton->GetRect().h);
	TextureManager::GetInstance()->Draw("Exit Button", exitButton->GetRect().x, exitButton->GetRect().y, exitButton->GetRect().w, exitButton->GetRect().h);

	_data->_text.Render("Main Menu Text", 800, 200);

	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}   