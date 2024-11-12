#pragma once
#include "SDL.h"
#include <string>
#include <unordered_map>
#include <fstream>

enum class GameAction 
{
	MoveLeft,
	MoveRight,
	Jump,
	Crouch,
	Attack
};

class KeyMapping 
{
public:
	KeyMapping() {}

	// Get SDL_Scancode for action
	SDL_Scancode GetKeyForAction(GameAction action) const
	{
		auto it = keyBindings.find(action);
		if (it != keyBindings.end())
		{
			return it->second;
		}

		return SDL_SCANCODE_UNKNOWN;
	}

	// Check if a specific action is currently being pressed
	bool IsActionPressed(GameAction action, const Uint8* keystate) const
	{
		SDL_Scancode key = GetKeyForAction(action);
		return keystate[key];
	}

	// Rebind specific action to a new key
	void RebindKey(GameAction action, SDL_Scancode newKey)
	{
		keyBindings[action] = newKey;
	}

	void RebindAction(KeyMapping& keyMapping, GameAction action)
	{
		SDL_Event e;
		bool keySet = false;

		while (!keySet)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_KEYDOWN)
				{
					SDL_Scancode newKey = e.key.keysym.scancode;
					keyMapping.RebindKey(action, newKey);
					keySet = true;
				}
			}
		}
	}

	void LoadKeyBindings(KeyMapping& keyMapping, const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cerr << "Error: Could not open file: " << filename << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			size_t delimiterPos = line.find('=');
			if (delimiterPos == std::string::npos)
			{
				std::cerr << "Warning: Malformed line: " << line << std::endl;
				continue;
			}

			std::string actionStr = line.substr(0, delimiterPos);
			std::string keyStr = line.substr(delimiterPos + 1);

			GameAction action;
			if (actionStr == "MoveLeft") action = GameAction::MoveLeft;
			else if (actionStr == "MoveRight") action = GameAction::MoveRight;
			else if (actionStr == "Jump") action = GameAction::Jump;
			else if (actionStr == "Crouch") action = GameAction::Crouch;
			else if (actionStr == "Attack") action = GameAction::Attack;
			else
			{
				std::cerr << "Warning: Unknown action: " << actionStr << std::endl;
				continue;
			}

			SDL_Scancode key = SDL_GetScancodeFromName(keyStr.c_str());
			if (key == SDL_SCANCODE_UNKNOWN)
			{
				std::cerr << "Warning: Unknown key: " << keyStr << std::endl;
				continue;
			}

			RebindKey(action, key);
		}

		file.close();
	}

private:
	std::unordered_map<GameAction, SDL_Scancode> keyBindings;
};