#pragma once
#include <string>
#include "SDL.h"

class Animation
{
public:
	Animation(bool repeat = true) : _repeat(repeat) { _isEnded = false; }

	virtual void Update() = 0;
	inline bool isEnded() { return _isEnded; }

protected:
	bool _repeat = false;
	bool _isEnded = false;
	int _currentFrame = 0;
};