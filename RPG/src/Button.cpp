#include "..\include\Button.h"
#include "..\include\TextureManager.h"
#include "..\include\SplashState.h"
#include "..\include\Input.h"

Button::Button(std::string id, int x, int y) 
{	
	_rect.x = x;
	_rect.y = y;
	SDL_QueryTexture(TextureManager::GetInstance()->GetTexture(id), NULL, NULL, &_rect.w, &_rect.h);
}

Button::Button(std::string id, std::string filepath, int x, int y, void(*callback)())
{
	TextureManager::GetInstance()->LoadTexture(id, filepath);

	_rect.x = x;
	_rect.y = y;
	SDL_QueryTexture(TextureManager::GetInstance()->GetTexture(id), NULL, NULL, &_rect.w, &_rect.h);

	_callback = callback;
}

Button::~Button()
{
}

void Button::Render(std::string id)
{
	TextureManager::GetInstance()->Draw(id, _rect.x, _rect.y, _rect.w, _rect.h);
}

void Button::Update()
{
	_mousepos = Input::GetInstance()->GetMousePosition();
	SDL_Point point = { _mousepos.X, _mousepos.Y };

	if (SDL_PointInRect(&point, &_rect))
	{
		if (Input::GetInstance()->GetMouseDown(SDL_BUTTON_LEFT))
		{
			_callback();
		}
	}
}

void Button::SetPosition(int x, int y)
{
	_rect.x = x;
	_rect.y = y;
}

std::vector<Button*> Button::GetButtons()
{
	return std::vector<Button*>();
}
