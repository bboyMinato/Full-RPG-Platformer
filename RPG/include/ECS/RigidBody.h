#pragma once
#include "ECS.h"
#include "Entity.h"
#include "Vector2D.h"
#include "BoxCollider2D.h"
#include "Collision.h"
#include "Engine.h"

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
		SDL_Rect playerCollider = entity->GetComponent<BoxCollider2D>().GetBoxCollider();

		velocity.X = force.X - drag.X;
		velocity.Y = force.Y + drag.Y + gravityScale * GRAVITY;		

		LastSafePosition.X = transform->Position.X;
		transform->TranslateX(velocity.X);
		playerCollider.x = transform->Position.X;
		if (Collision::GetInstance()->CollisionWithMap(playerCollider))
		{
			transform->Position.X = LastSafePosition.X;
			isGrounded = false; 
		}

		LastSafePosition.Y = transform->Position.Y;
		transform->TranslateY(velocity.Y);
		playerCollider.y = transform->Position.Y;
		if (Collision::GetInstance()->CollisionWithMap(playerCollider))
		{
			isGrounded = true; 
			transform->Position.Y = LastSafePosition.Y;
		}			

		UnsetForce();
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


	inline bool IsGrounded() const
	{
		return isGrounded;
	}

	void Jump()
	{	
		isGrounded = false; 			
		jumpTime = 5.f;
		float jumpTimeStep = 0.5f;

		while (jumpTime > 0)
		{
			jumpTime -= jumpTimeStep;	
			velocity.Y += -5.5f + gravityScale * GRAVITY;
			transform->TranslateY(velocity.Y);			
		}
	}

private:
	float gravityScale = 1.0f;
	float mass = 1.0f;
	Vector2Df drag = Vector2Df();
	Vector2Df force = Vector2Df();
	Vector2Df velocity = Vector2Df();
	Vector2Df LastSafePosition = Vector2Df();	

	Transform* transform = nullptr;		

	bool isGrounded = false;
	float jumpTime = 1.f; 
};

