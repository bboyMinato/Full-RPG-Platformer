#include "Collision.h"
#include "GameState.h"
Collision* Collision::_instance = nullptr;

Collision::Collision()
{
    _collisionLayer = (TileLayer*)Engine::GetInstance()->GetMap()->GetMapLayers().back();
    _collisionTileMap = _collisionLayer->GetTileMap();
}

bool Collision::AABB(const SDL_Rect rectA, const SDL_Rect rectB)
{
    bool x_overlaps = (rectA.x <= rectB.x + rectB.w) && (rectA.x + rectA.w >= rectB.x);
    bool y_overlaps = (rectA.y <= rectB.y + rectB.h) && (rectA.y + rectA.h >= rectB.y);

    return (x_overlaps && y_overlaps);
}

bool Collision::CollisionWithMap(SDL_Rect rectA)
{
    const int tileSize = 16;
    const int rowCount = 62;
    const int colCount = 90;

    int left_tile = rectA.x / tileSize;
    int right_tile = (rectA.x + rectA.w) / tileSize;

    int top_tile = rectA.y / tileSize;
    int bottom_tile = (rectA.y + rectA.h) / tileSize;

    // Clamp tile indices to avoid accessing outside the array bounds
    left_tile = std::max(0, left_tile);
    right_tile = std::min(colCount - 1, right_tile);
    top_tile = std::max(0, top_tile);
    bottom_tile = std::min(rowCount - 1, bottom_tile);

    // Iterate over the tiles within the specified range
    for (int i = left_tile; i <= right_tile; i++)
    {
        for (int j = top_tile; j <= bottom_tile; j++)
        {
            if (_collisionTileMap[j][i] > 0)
                return true;  // Collision detected
        }
    }

    return false;  // No collision detected
}