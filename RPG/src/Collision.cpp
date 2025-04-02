#include "Collision.h"
#include "GameState.h"
Collision* Collision::_instance = nullptr;

Collision::Collision()
{
    _collisionObjects = Engine::GetInstance()->GetMap()->GetCollisionObjects();
}

bool Collision::AABB(const SDL_Rect rectA, const SDL_Rect rectB)
{
    bool x_overlaps = (rectA.x <= rectB.x + rectB.w) && (rectA.x + rectA.w >= rectB.x);
    bool y_overlaps = (rectA.y <= rectB.y + rectB.h) && (rectA.y + rectA.h >= rectB.y);

    return (x_overlaps && y_overlaps);
}

bool Collision::CollisionWithMap(SDL_Rect rectA)
{
    for (const auto& box : _collisionObjects)
    {
        SDL_Rect collisionRect = { box.x, box.y, box.w, box.h };
        if (AABB(rectA, collisionRect))
        {
            return true;  // Stop checking after first collision
        }
    }

    return false;
}