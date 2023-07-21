#pragma once
#include "SDL.h"
#include "Engine.h"
#include "Vector2D.h"
#include <string>
#include <vector>

class Button
{
public:
	Button(std::string id, int x, int y);
	Button(std::string id, std::string filepath, int x, int y, void (*callback)());
	Button() {}
	~Button();
	
	void Render(std::string id);
	void Update();

	inline SDL_Rect& GetRect() { return _rect; }
	void SetPosition(int x, int y);
	std::vector<Button*> GetButtons();

private:	
	SDL_Rect _rect = { 0, 0, 0, 0 };
	std::vector<Button*> _buttons;
	Vector2D<int> _mousepos;

	void (*_callback)() = nullptr;
};

