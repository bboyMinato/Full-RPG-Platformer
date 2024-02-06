#pragma once
#include "Entity.h"
#include "Transform.h"
#include "Input.h"

class PlayerController : public Component
{
public:
	bool Init() override final
	{
		transform = &entity->GetComponent<Transform>();

		if (transform != nullptr)
		{
			return true;
		}

		return false;
	}

	void Update() override final
	{
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
		{
			entity->GetComponent<RigidBody>().SetForceX(1);
		}

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
		{
			entity->GetComponent<RigidBody>().SetForceX(-1);
		}

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && entity->GetComponent<RigidBody>().IsGrounded())
		{
			entity->GetComponent<RigidBody>().Jump();		
		}		
	}
	
private:
	Transform* transform = nullptr;	
};