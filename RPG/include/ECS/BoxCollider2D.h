#pragma once
#include "Entity.h"
#include "Transform.h"
#include "TextureManager.h"
#include <iostream>
#include "Vector2D.h"
#include <string>

class BoxCollider2D : public Component
{
public:
	BoxCollider2D(int width, int height)
		: Box{ 0, 0, width, height } {}

	BoxCollider2D(int width, int height, const std::string& tag)
		: Box{ 0, 0, width, height }, CollisionTag(tag) {}

	~BoxCollider2D() = default;

	bool Init() override final
	{
		if (!entity->HasComponent<Transform>())
		{
			entity->AddComponent<Transform>(); 
		}

		transform = &entity->GetComponent<Transform>();

		return true;
	}

	void Draw(float dt) override final
	{
		TextureManager::GetInstance()->Draw(Box);		
	}

	void Update(float dt) override final
	{
		Box.x = static_cast<int>(transform->Position.X);
		Box.y = static_cast<int>(transform->Position.Y);			
	}

	inline const std::string& GetCollisionTag() const 
	{ 
		return CollisionTag; 
	}	

	inline const SDL_Rect& GetBoxCollider() const
	{ 
		return Box; 
	}

	void SetDimensions(int width, int height)
	{
		Box.w = width;
		Box.h = height;
	}

	void SetPosition(float x, float y)
	{
		Box.x = static_cast<int>(x);
		Box.y = static_cast<int>(y);
	}

private:
	std::string CollisionTag = "";
	Transform* transform = nullptr;

	SDL_Rect Box = { 0,0,0,0 };
};