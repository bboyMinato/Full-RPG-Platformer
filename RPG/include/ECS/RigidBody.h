#pragma once
#include "ECS.h"
#include "Entity.h"
#include "Vector2D.h"
#include "BoxCollider2D.h"
#include "Collision.h"

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
		LastSafePosition.X = transform->position.X;
		LastSafePosition.Y = transform->position.Y;

		Vector2Df interpolated;
		interpolated.X = LastSafePosition.X;
		interpolated.Y = LastSafePosition.Y;		

		velocity.X = force.X - drag.X;
		velocity.Y = force.Y + drag.Y + gravityScale * GRAVITY;

		const float ccdTimeStep = 0.01f;
		float remainingTime = 1.f;

		
		while (remainingTime > 0.f)
		{
			interpolated.X = LastSafePosition.X + velocity.X * remainingTime;
			interpolated.Y = LastSafePosition.Y + velocity.Y * remainingTime;

			// Check for collision at the interpolated position
			if (Collision::GetInstance()->MapCollision(entity->GetComponent<BoxCollider2D>().GetBoxCollider(), interpolated)) 
			{
				// Handle the collision response
				transform->position.X = interpolated.X;
				transform->position.Y = interpolated.Y;

				// Break the loop since we've handled the collision
				break;
			}

			// Reduce remaining time
			remainingTime -= ccdTimeStep;
		}			

		// If no collision is detected, update the position normally
		if (remainingTime <= 0.0f) {
			transform->Translate(velocity);
		}
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

	void UnsetForce()
	{
		force = Vector2Df(0, 0);
	}

private:
	float gravityScale = 1.0f;
	Vector2Df drag = Vector2Df();
	Vector2Df force = Vector2Df();
	Vector2Df velocity = Vector2Df();
	Vector2Df LastSafePosition = Vector2Df();

	Transform* transform = nullptr;	
};

