#pragma once
#include "Entity.h"
#include "Transform.h"
#include "Input.h"
#include "KeyMapping.h"
#include "RigidBody.h"

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

	void Update(float dt) override final
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		if (keyMapping.IsActionPressed(GameAction::MoveRight, keystate))
		{
			entity->GetComponent<RigidBody>().SetForceX(400);
		}
		else if (keyMapping.IsActionPressed(GameAction::MoveLeft, keystate))
		{
			entity->GetComponent<RigidBody>().SetForceX(-400);
		}
		else
		{
			entity->GetComponent<RigidBody>().SetForce(0);
		}

		if (keyMapping.IsActionPressed(GameAction::Jump, keystate))
		{
			entity->GetComponent<RigidBody>().Jump();		
		}
	}
	
	void SetKeyMapping(KeyMapping& keyMapping)
	{
		this->keyMapping = keyMapping;
	}

private:
	Transform* transform = nullptr;	
	KeyMapping keyMapping;
};