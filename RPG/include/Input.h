#pragma once
#include "SDL.h"
#include "Vector2D.h"

class Input
{
public:
	static Input* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Input(); }

	bool GetKeyDown(SDL_Scancode key);		
	bool GetMouseDown(int button);
	void HandleEvents();
	Vector2D<int> GetMousePosition();
	
private:
	static Input* _instance;
	const Uint8* _keystates;
	Uint32 _buttonstates;
	Vector2D<int> _mousepos;

	Input();
	void KeyDown();
	void KeyUp();	
	void ButtonDown();
	void ButtonUp();
};

