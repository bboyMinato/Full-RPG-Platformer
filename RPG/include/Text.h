#pragma once
#include <iostream>
#include <string>
#include <map>
#include "SDL_ttf.h"
#include "SDL.h"

class Text
{
public:	
	Text() {}

	TTF_Font* LoadFont(std::string id, std::string filepath, int fontSize);
	TTF_Font* GetFont(std::string id);
	SDL_Texture* CreateText(std::string id, std::string text, TTF_Font* font, SDL_Color color);

	void Render(std::string id, int x, int y);
	void Clean();

private:		
	TTF_Font* _font = nullptr;
	SDL_Texture* _textTexture = nullptr;
	SDL_Rect _dst = { 0,0,0,0 };

	std::map<std::string, TTF_Font*> _fontMap;
	std::map<std::string, SDL_Texture*> _fontTextureMap;
};

