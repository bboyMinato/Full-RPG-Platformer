#pragma once
#include "ECS.h"
#include "Entity.h"
#include "Vector2D.h"
#include "BoxCollider2D.h"
#include "Collision.h"
#include "Engine.h"

constexpr float GRAVITY = 300.f;
constexpr float JUMP_FORCE = -380.f; 
constexpr float MAX_JUMP_HEIGHT = 200.f;
constexpr float DEFAULT_MASS = 1.0f;
constexpr float DEFAULT_GRAVITY_SCALE = 1.0f;

class RigidBody : public Component
{
public:
	RigidBody() = default;	
	virtual ~RigidBody() = default;

	explicit RigidBody(float gravity_scale) : gravityScale(gravity_scale), mass(DEFAULT_MASS) {}

	bool Init() override final
	{
		transform = &entity->GetComponent<Transform>();
		return true;
	}

	void Update(float dt) override final
	{	
		SDL_Rect playerCollider = entity->GetComponent<BoxCollider2D>().GetBoxCollider();

		ApplyForces();

		// Handle horizontal movement and collision
		HandleMovement(playerCollider, true);

		// Handle vertical movement and collision
		HandleMovement(playerCollider, false);

		 //Update jump if the character is jumping
		UpdateJump();

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
	
	void SetVelocityY(const float v)
	{
		velocity.Y = v; 
	}

	void SetVelocityX(const float v)
	{
		velocity.X = v;
	}

	void Jump()
	{			
		if (!isJumping) 
		{
			isJumping = true;			
			jumpVelocity = JUMP_FORCE;			
		}
	}

	void UpdateAnimState()
	{

	}

	inline bool IsJumping() const { return isJumping; }
	inline bool IsGrounded() const { return isGrounded; }

private:
	void ApplyForces()
	{
		velocity.X = (force.X - drag.X) * Engine::GetInstance()->GetDeltaTime();
		if (!isGrounded)
		{
			velocity.Y = (force.Y + drag.Y + gravityScale * GRAVITY) * Engine::GetInstance()->GetDeltaTime();
		}
	}

	void HandleMovement(SDL_Rect& playerCollider, bool isHorizontal)
	{
		if (isHorizontal)
		{
			LastSafePosition.X = transform->Position.X;
			transform->TranslateX(velocity.X);
			playerCollider.x = transform->Position.X;
		}
		else
		{
			LastSafePosition.Y = transform->Position.Y;
			transform->TranslateY(velocity.Y);
			playerCollider.y = transform->Position.Y;
		}

		if (Collision::GetInstance()->CollisionWithMap(playerCollider))
		{
			if (isHorizontal)
			{
				transform->Position.X = LastSafePosition.X;
				velocity.X = 0.0f;
			}
			else
			{
				transform->Position.Y = LastSafePosition.Y;
				velocity.Y = 0.0f;
				isGrounded = true;
				heightCheck = transform->Position.Y - MAX_JUMP_HEIGHT; // Update height check for jumping
			}
		}
		else if (!isHorizontal) // If no vertical collision
		{
			isGrounded = false;
		}
	}

	void UpdateJump()
	{
		if (isJumping)
		{
			if (transform->Position.Y > heightCheck)
			{
				velocity.Y += jumpVelocity * Engine::GetInstance()->GetDeltaTime();
			}
			else
			{
				// Stop the jump after reaching the maximum jump height
				isJumping = false;
				velocity.Y = gravityScale * GRAVITY * Engine::GetInstance()->GetDeltaTime();
			}

			transform->TranslateY(velocity.Y);
		}
	}

	float gravityScale = DEFAULT_GRAVITY_SCALE;
	float mass = DEFAULT_MASS;
	Vector2Df drag = Vector2Df();
	Vector2Df force = Vector2Df();
	Vector2Df velocity = Vector2Df();
	Vector2Df LastSafePosition = Vector2Df();	

	Transform* transform = nullptr;		

	bool isGrounded = false;			 // Flag to track if the character is on the ground
	bool isJumping = false;				 // Flag to track if the character is jumping
	float jumpVelocity = 0.0f;			 // Initial jump velocity		
	float heightCheck = 0.0f; 
};