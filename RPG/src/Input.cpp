#include "..\include\Input.h"
#include <iostream>
Input* Input::_instance = nullptr;

Input::Input()
{
    
    _keystates = SDL_GetKeyboardState(nullptr);   
    _buttonstates = SDL_GetMouseState(nullptr, nullptr);    
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    if (_keystates[key] == 1)
        return true;

    return false;
}

bool Input::GetMouseDown(int button) const
{
    if (_buttonstates == button)
        return true;

    return false;
}

void Input::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            break;
        case SDL_KEYDOWN:
            KeyDown();
            break;
        case SDL_KEYUP:
            KeyUp();
            break;    
        case SDL_MOUSEBUTTONDOWN:
            ButtonDown();
            break;
        case SDL_MOUSEBUTTONUP:
            ButtonUp();
            break;
        default:
            break;
        }
    }
}

Vector2D<int> Input::GetMousePosition()
{
   SDL_GetMouseState(&_mousepos.X, &_mousepos.Y);  
   
   return _mousepos;
}

void Input::KeyDown()
{
    _keystates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyUp()
{
    _keystates = SDL_GetKeyboardState(nullptr);
}

void Input::ButtonDown()
{
    _buttonstates = SDL_GetMouseState(nullptr, nullptr);
}

void Input::ButtonUp()
{
    _buttonstates = SDL_GetMouseState(nullptr, nullptr);
}
