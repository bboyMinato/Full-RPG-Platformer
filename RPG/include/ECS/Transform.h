#pragma once
#include "ECS.h"
#include "Vector2D.h"

class Transform : public Component
{
public:
	Transform() 
	{
		position.Zero();
		scale.One();
		rotation = 0.0f;
	}	

	Transform(float x, float y)
	{
		position.X = x;
		position.Y = y;
		scale.One();
		rotation = 0.0f;
	}

	virtual ~Transform() {}

	void Translate(Vector2Df v)
	{
		position += v;		
	}

	void Translate(float x, float y)
	{
		position.X += x;
		position.Y += y; 
	}

	Vector2Df position = Vector2Df();
	Vector2Df scale = {1.0f, 1.0f};

	float rotation = 0.0f;
private:
};