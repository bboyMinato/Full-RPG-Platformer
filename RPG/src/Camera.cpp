#include "../include/Camera.h"
Camera* Camera::_instance = nullptr;

void Camera::Update(float dt)
{
	if (_target == nullptr)
		std::cout << "_target not initialized!" << std::endl;

	else
	{
		_viewBox.x = static_cast<int>(_target->X) - 1920 / 2;
		_viewBox.y = static_cast<int>(_target->Y) - 1080 / 2;

		if (_viewBox.x < 0)
			_viewBox.x = 0;

		if (_viewBox.y < 0)
			_viewBox.y = 0;

		if (_viewBox.x > (2 * 1920 - _viewBox.w))
			_viewBox.x = (2 * 1920 - _viewBox.w);

		if (_viewBox.y > (1080 - _viewBox.h))
			_viewBox.y = (1080 - _viewBox.h);

		_position = Vector2D<int>(_viewBox.x, _viewBox.y);
	}
}