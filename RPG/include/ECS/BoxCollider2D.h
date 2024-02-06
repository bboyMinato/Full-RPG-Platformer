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
	BoxCollider2D(int Width, int Height)
	{
		Box.w = Width;
		Box.h = Height;
	}

	BoxCollider2D(int Width, int Height, std::string Tag) : CollisionTag(Tag)
	{
		Box.w = Width;
		Box.h = Height;
	}

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

	void Draw() override final
	{
		TextureManager::GetInstance()->Draw(Box);		
	}

	void Update() override final
	{
		Box.x = static_cast<int>(transform->Position.X);
		Box.y = static_cast<int>(transform->Position.Y);			
	}

	inline std::string GetCollisionTag() const 
	{ 
		return CollisionTag; 
	}	

	inline SDL_Rect GetBoxCollider() const
	{ 
		return Box; 
	}

private:
	std::string CollisionTag = "";
	Transform* transform = nullptr;

	SDL_Rect Box = { 0,0,0,0 };
};