#pragma once
#include <string>
#include "SDL.h"
#include "EntityManager.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Entity.h"

class Sprite : public Component
{
public:
	Sprite() = default;
	Sprite(SDL_Renderer* target, std::string textureid) : rTarget(target), textureID(textureid) {}
	virtual ~Sprite() = default;

	bool Init() override final
	{	
		transform = &entity->GetComponent<Transform>();			
		
		texture = TextureManager::GetInstance()->GetTexture(textureID);
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		dstRect.x = transform->position.X;
		dstRect.y = transform->position.Y;
		dstRect.w = width * transform->scale.X;
		dstRect.h = height * transform->scale.Y;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = width;
		srcRect.h = height;	

		return true;
	}
	
	void Draw() override final
	{
		SDL_RenderCopyEx(rTarget, texture, &srcRect, &dstRect, transform->rotation, NULL, flip);
	}

	void Update() override final
	{
		dstRect.x = static_cast<int>(transform->position.X);
		dstRect.y = static_cast<int>(transform->position.Y);
		dstRect.w = static_cast<int>(width * transform->scale.X);
		dstRect.h = static_cast<int>(height * transform->scale.Y);
	}

private:
	int width = 0;
	int height = 0;
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

	Transform* transform = nullptr;
	std::string textureID = "";
	SDL_Texture* texture = nullptr;
	SDL_Renderer* rTarget = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};