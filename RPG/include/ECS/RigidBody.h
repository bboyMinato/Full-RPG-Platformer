#pragma once
#include "ECS.h"
#include "Entity.h"
#include "Vector2D.h"
#include "BoxCollider2D.h"
#include "Collision.h"
#include "Engine.h"
#include "Globals.h"

constexpr float GRAVITY = 180.f;
constexpr float JUMP_FORCE = -550.f;
constexpr float MAX_JUMP_HEIGHT = 80.f;
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

		//Update jump if the character is jumping
		UpdateJump(dt);

		ApplyForces(dt);

		// Handle horizontal movement and collision
		HandleMovement(playerCollider, true, dt);

		// Handle vertical movement and collision
		HandleMovement(playerCollider, false, dt);

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
		if (isGrounded)
		{
			isJumping = true;
			heightCheck = transform->Position.Y - MAX_JUMP_HEIGHT; // Update height check for jumping
		}
	}

	void UpdateAnimState()
	{

	}

	inline bool IsJumping() const { return isJumping; }
	inline bool IsGrounded() const { return isGrounded; }

private:
	void ApplyForces(float dt)
	{
		velocity.X = (force.X - drag.X) * dt * 2;
		if (!isGrounded)
		{
			SetInitialVelocityY(dt);
		}
	}

	void SetInitialVelocityY(float dt)
	{
		velocity.Y += (force.Y + drag.Y + gravityScale * GRAVITY) * dt;
	}

	void UpdateJump(float dt)
	{
		if (isJumping && !isGrounded)
		{
			if (transform->Position.Y > heightCheck)
			{
				force.Y += JUMP_FORCE;
			}
			else
			{
				isJumping = false;
				SetInitialVelocityY(dt);
			}
		}
	}

	void HandleMovement(SDL_Rect& playerCollider, bool isHorizontal, float dt)
	{
		// Apply movement
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

		// collider to check collision for next frame
		SDL_Rect nextCollider = playerCollider;

		// update collider for the next frame
		nextCollider.x += static_cast<int>(velocity.X * dt);
		nextCollider.y += static_cast<int>(velocity.Y * dt);

		// Check for collision after applying movement
		bool isCollidingWithMap = Collision::GetInstance()->CollisionWithMap(nextCollider);

		if (isCollidingWithMap)
		{
			if (isHorizontal)
			{
				// Move just enough to resolve collision instead of snapping back
				while (Collision::GetInstance()->CollisionWithMap(playerCollider))
				{
					transform->Position.X -= (velocity.X > 0) ? 1 : -1;
					playerCollider.x = transform->Position.X;
				}

				velocity.X = 0.0f;
			}
			else
			{
				// Move just enough to resolve collision instead of snapping back
				while (Collision::GetInstance()->CollisionWithMap(playerCollider))
				{
					transform->Position.Y -= (velocity.Y > 0) ? 1 : -1;
					playerCollider.y = transform->Position.Y;
				}

				velocity.Y = 0.0f;

				if (LastSafePosition.Y < transform->Position.Y) // Landing on a platform
				{
					isGrounded = true;
					isJumping = false;
				}
				else // Hitting ceiling
				{
					// Stop upward movement but don't set isJumping to true
					force.Y = 0.0f;
					velocity.Y = 0.0f;
					isJumping = false;
				}
			}
		}
		else if (!isHorizontal) // If no vertical collision
		{
			isGrounded = false;
		}		
	}

private:
	float gravityScale = DEFAULT_GRAVITY_SCALE;
	float mass = DEFAULT_MASS;
	Vector2Df drag = Vector2Df();
	Vector2Df force = Vector2Df();
	Vector2Df velocity = Vector2Df();
	Vector2Df LastSafePosition = Vector2Df();

	Transform* transform = nullptr;
	BoxCollider2D* box = nullptr;

	bool isGrounded = false;			 // Flag to track if the character is on the ground
	bool isJumping = false;				 // Flag to track if the character is jumping	
	float heightCheck = 0.0f;			 // Flag to track how high can character jump
};