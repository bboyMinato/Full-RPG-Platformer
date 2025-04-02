#include "../include/Camera.h"
#include "Globals.h"
Camera* Camera::_instance = nullptr;

void Camera::Update(float dt)
{
	if (_target == nullptr)
	{
		std::cout << "_target not initialized!" << std::endl;
	}
	else
	{
		_viewBox.x = static_cast<int>(_target->X) - Globals::SCREEN_WIDTH / 2;
		_viewBox.y = static_cast<int>(_target->Y) - Globals::SCREEN_HEIGHT / 2;

		if (_viewBox.x < 0)
			_viewBox.x = 0;

		if (_viewBox.y < 0)
			_viewBox.y = 0;

		if (_viewBox.x > (2 * Globals::SCREEN_WIDTH - _viewBox.w))
			_viewBox.x = (2 * Globals::SCREEN_WIDTH - _viewBox.w);

		if (_viewBox.y > (Globals::SCREEN_HEIGHT - _viewBox.h))
			_viewBox.y = (Globals::SCREEN_HEIGHT - _viewBox.h);

		_position = Vector2D<int>(_viewBox.x, _viewBox.y);
	}
}