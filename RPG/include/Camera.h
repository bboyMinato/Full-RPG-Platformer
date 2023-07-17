#pragma once
#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"
#include "SDL.h"

class Camera
{
public:
	void Update(float dt);

	inline static Camera* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Camera(); }

	inline SDL_Rect GetViewBox() { return _viewBox; }
	inline Vector2D<int> GetPosition() { return _position; }
	inline void SetTarget(Point* target) { _target = target; }

private:
	Camera() { _viewBox = { 0, 0, 1280, 980 }; }

	Point* _target = nullptr;
	Vector2D<int> _position;
	SDL_Rect _viewBox;

	static Camera* _instance;
};