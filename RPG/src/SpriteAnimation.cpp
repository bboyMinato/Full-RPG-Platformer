#include "..\include\SpriteAnimation.h"
#include "../include/TextureManager.h"
#include <iostream>

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat)
{
}

void SpriteAnimation::Update()
{
	_currentFrame = (SDL_GetTicks() / _animSpeed) % _frameCount;
}

void SpriteAnimation::Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, SDL_RendererFlip flip)
{
	TextureManager::GetInstance()->DrawFrame(_textureID, x, y, spriteWidth, spriteHeight, _spriteRow, _currentFrame, 3, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
	_textureID = textureID;
	_spriteRow = spriteRow;
	_frameCount = frameCount;
	_animSpeed = animSpeed;
}