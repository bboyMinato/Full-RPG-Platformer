#pragma once
#include <SDL.h>
#include "GameMap.h"
#include "TileLayer.h"
#include "Vector2D.h"

class Collision
{
public:

	static Collision* GetInstance() { return _instance = (_instance != nullptr) ? _instance : new Collision(); }

	bool AABB(const SDL_Rect rectA, const SDL_Rect rectB);
	bool MapCollision(SDL_Rect rectA, Vector2Df interpolation);


private:
	Collision();

	static Collision* _instance; 
	TileMap _collisionTileMap;
	TileLayer* _collisionLayer = nullptr;
};