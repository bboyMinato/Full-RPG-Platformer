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
		entity->GetComponent<RigidBody>().UnsetForce();

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
		{
			entity->GetComponent<RigidBody>().SetForceX(0.1);
		}

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
		{
			entity->GetComponent<RigidBody>().SetForceX(-0.1);
		}

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
		{
			entity->GetComponent<RigidBody>().SetForceY(-0.1);
		}

		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
		{
			entity->GetComponent<RigidBody>().SetForceY(0.1);
		}
	}

private:
	Transform* transform = nullptr;	
};