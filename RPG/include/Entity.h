#pragma once
#include "SDL.h"
#include <string>
#include "../include/Transform.h"

struct Properties
{
public:
	Properties(std::string textureID, float x, float y, int width, int height)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_textureID = textureID;
	}

	float _x, _y;
	int _width, _height;
	std::string _textureID;
};

class Entity
{
public:
	Entity() {}

	Entity(Properties* props) : _textureID(props->_textureID), _width(props->_width), _height(props->_height)
	{
		_transform = new Transform(props->_x, props->_y);
	}

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

	SDL_Rect _box = { 0, 0, 0, 0, };

protected:
	Transform* _transform = nullptr;

	int _width = 50;
	int _height = 50;
	std::string _textureID;
};