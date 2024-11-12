#pragma once
#include "ECS.h"
#include "Vector2D.h"

class Transform : public Component
{
public:
	Transform() 
	{
		Position.Zero();
		scale.One();
		rotation = 0.0f;
	}	

	Transform(float x, float y)
	{
		Position.X = x;
		Position.Y = y;
		scale.One();
		rotation = 0.0f;
	}

	virtual ~Transform() {}

	void Translate(Vector2Df v)
	{
		Position += v;		
	}

	void Translate(float x, float y)
	{
		Position.X += x;
		Position.Y += y;
	}

	void TranslateX(float x)
	{
		Position.X += x;
	}

	void TranslateY(float y)
	{
		Position.Y += y;
	}	

	Vector2Df Position = Vector2Df();
	Vector2Df scale = {1.0f, 1.0f};

	float rotation = 0.0f;
private:
};