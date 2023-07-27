#pragma once
#include <string>
#include "SDL.h"
#include "Entity.h"
#include "Transform.h"
#include "TextureManager.h"

class SpriteAnimation : public Component
{
public:
	SpriteAnimation() = default;
	SpriteAnimation(std::string texture, int animspeed, int spriterow, int framecount, bool repeatanim)
	{
		repeat = repeatanim;
		textureID = texture;
		animSpeed = animspeed;
		spriteRow = spriterow;
		frameCount = framecount;
	}

	virtual ~SpriteAnimation() = default;

	bool Init() override final
	{
		transform = &entity->GetComponent<Transform>();

		texture = TextureManager::GetInstance()->GetTexture(textureID);
		SDL_QueryTexture(texture, NULL, NULL, &width, &height);

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = width / frameCount;
		srcRect.h = height;

		dstRect.x = static_cast<int>(transform->position.X);
		dstRect.y = static_cast<int>(transform->position.Y);
		dstRect.w = static_cast<int>(width * transform->scale.X);
		dstRect.h = static_cast<int>(height * transform->scale.Y);

		return true;
	}

	void Update() override final
	{
		currentFrame = (SDL_GetTicks() / animSpeed) % frameCount;

		dstRect.x = static_cast<int>(transform->position.X);
		dstRect.y = static_cast<int>(transform->position.Y);
		dstRect.w = static_cast<int>(width * transform->scale.X);
		dstRect.h = static_cast<int>(height * transform->scale.Y);
	}

	void Draw() override final
	{		
		TextureManager::GetInstance()->DrawFrame(textureID, dstRect.x, dstRect.y, srcRect.w, srcRect.h, spriteRow, currentFrame);
	}

	void SetProps(std::string texture, int animspeed, int spriterow, int framecount)
	{
		textureID = texture;
		animSpeed = animspeed;
		spriteRow = spriterow;
		frameCount = framecount;
	}

private:
	bool repeat = true;
	int width = 0;
	int height = 0;
	int animSpeed = 0;
	int spriteRow = 0;
	int frameCount = 0;
	int currentFrame = 0;
	std::string textureID = "";
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

	Transform* transform = nullptr;
	SDL_Texture* texture = nullptr;
};