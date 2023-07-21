#pragma once
#include "ECS.h"
#include "Vector2D.h"

class Transform : public Component
{
public:
	Transform() {}
	virtual ~Transform() {}

	Transform(float x, float y)
	{
		position.X = x;
		position.Y = y;
		rotation = 0.0f;
	}

	Vector2Df position;
	Vector2Df scale;

	float rotation = 0.0f;
private:
};