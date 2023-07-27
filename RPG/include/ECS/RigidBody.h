#pragma once
#include "ECS.h"
#include "Entity.h"
#include "Vector2D.h"

constexpr float GRAVITY = 9.81f;

class RigidBody : public Component
{
public:
	RigidBody() = default;	
	virtual ~RigidBody() = default;

	RigidBody(float gravity_scale) : gravityScale(gravity_scale) {}

	bool Init() override final
	{
		transform = &entity->GetComponent<Transform>();
		return true;
	}

	void Update() override final
	{
		velocity.X = force.X - drag.X;
		velocity.Y = force.Y + drag.Y + gravityScale * GRAVITY;
		transform->Translate(velocity);		
	}

	void SetForce(const Vector2Df f)
	{
		force = f; 
	}

	void SetForceX(const float f)
	{
		force.X = f;
	}

	void SetForceY(const float f)
	{
		force.Y = f;
	}

private:
	float gravityScale = 1.0f;
	Vector2Df drag = Vector2Df();
	Vector2Df force = Vector2Df();
	Vector2Df velocity = Vector2Df();

	Transform* transform = nullptr;
};