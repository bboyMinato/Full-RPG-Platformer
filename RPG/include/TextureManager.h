#pragma once
#include "SDL_image.h"
#include <string>
#include <iostream>
#include <map>

class TextureManager
{
public:
	static TextureManager* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new TextureManager(); }
		
	SDL_Texture* LoadTexture(std::string id, std::string filepath);
	SDL_Texture* GetTexture(std::string id);

	void Draw(std::string id, int x, int y, int width, int height);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void Clean();

private:
	TextureManager() {}

	static TextureManager* _instance;
	SDL_Texture* _texture = nullptr;
	std::map<std::string, SDL_Texture*> _textureMap;
};