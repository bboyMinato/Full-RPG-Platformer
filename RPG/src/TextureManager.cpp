#include "..\include\TextureManager.h"
#include "..\include\Engine.h"
#include "../include/Vector2D.h"
#include "../include/Camera.h"

TextureManager* TextureManager::_instance = nullptr;

SDL_Texture* TextureManager::LoadTexture(std::string id, std::string filepath)
{
	_texture = IMG_LoadTexture(Engine::GetInstance()->GetRenderer(), filepath.c_str());

	if (_texture == nullptr)
		std::cout << "Failed to load the texture. Error: " << SDL_GetError() << " " << id << std::endl;

	_textureMap[id] = _texture;

	return _texture;
}

SDL_Texture* TextureManager::GetTexture(std::string id)
{
	return _textureMap[id];
}

bool TextureManager::ParseTexture(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cout << "Failed to load the texture: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("texture"))
		{
			std::string id = e->Attribute("id");
			std::string source = e->Attribute("source");
			LoadTexture(id, source);
		}
	}

	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height)
{
	SDL_Rect src = { 0, 0, width, height };
	SDL_Rect dst = { x, y, width, height };

	SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), _textureMap[id], &src, &dst);
}

void TextureManager::Draw(SDL_Rect box)
{		
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, float scale, SDL_RendererFlip flip)
{
	Vector2D<int> cam = Camera::GetInstance()->GetPosition();
	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect dstRect = { x - cam.X, y - cam.Y, width * scale, height * scale };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), _textureMap[id], &srcRect, &dstRect, 0, NULL, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int col, SDL_RendererFlip flip)
{
	Vector2D<int> cam = Camera::GetInstance()->GetPosition();
	SDL_Rect srcRect = { col * tileSize, row * tileSize, tileSize, tileSize };
	SDL_Rect dstRect = { x - cam.X, y - cam.Y , tileSize, tileSize };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), _textureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::Clean()
{
	for (auto it = _textureMap.begin(); it != _textureMap.end(); it++)
		SDL_DestroyTexture(it->second);

	SDL_DestroyTexture(_texture);

	_textureMap.clear();
}