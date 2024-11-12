#pragma once
#include "ECS.h"
#include "Transform.h"
#include "BoxCollider2D.h"

class CollisionSystem
{
public:
    CollisionSystem() {}

    void Update(const std::vector<Entity*>& entities)
    {
        // Loop through each pair of entities
        for (size_t i = 0; i < entities.size(); ++i)
        {
            auto* entityA = entities[i];
            if (!entityA->HasComponent<Transform>() || !entityA->HasComponent<BoxCollider2D>())
                continue;

            auto& transformA = entityA->GetComponent<Transform>();
            auto& colliderA = entityA->GetComponent<BoxCollider2D>();
            colliderA.SetPosition(transformA.Position.X, transformA.Position.Y);

            for (size_t j = i + 1; j < entities.size(); ++j)
            {
                auto* entityB = entities[j];
                if (!entityB->HasComponent<Transform>() || !entityB->HasComponent<BoxCollider2D>())
                    continue;

                auto& transformB = entityB->GetComponent<Transform>();
                auto& colliderB = entityB->GetComponent<BoxCollider2D>();
                colliderB.SetPosition(transformB.Position.X, transformB.Position.Y);

                // Check for collision
                if (IsColliding(colliderA, colliderB))
                {
                    HandleCollision(entityA, entityB);
                }
            }
        }
    }

private:
    bool IsColliding(const BoxCollider2D& colliderA, const BoxCollider2D& colliderB)
    {
        return SDL_HasIntersection(&colliderA.GetBoxCollider(), &colliderB.GetBoxCollider());
    }

    void HandleCollision(Entity* entityA, Entity* entityB)
    {
        auto& transformA = entityA->GetComponent<Transform>();
        auto& colliderA = entityA->GetComponent<BoxCollider2D>();
        auto& transformB = entityB->GetComponent<Transform>();
        auto& colliderB = entityB->GetComponent<BoxCollider2D>();

        SDL_Rect boxA = colliderA.GetBoxCollider();
        SDL_Rect boxB = colliderB.GetBoxCollider();

        // Calculate overlaps
        int overlapX = (boxA.x + boxA.w) - boxB.x; // Right edge of A - Left edge of B
        int overlapY = (boxA.y + boxA.h) - boxB.y; // Bottom edge of A - Top edge of B

        // If overlap is negative, there's no collision
        if (overlapX < 0 || overlapY < 0)
            return;

        // Adjust for potential continued movement
        // This ensures that entities are not pushed further into one another
        if (overlapX < overlapY)
        {
            // If we resolved horizontally, we need to reset the vertical velocity if applicable
            transformA.Position.Y = (transformA.Position.Y < transformB.Position.Y)
                ? transformB.Position.Y - boxA.h // Position above the other entity
                : transformB.Position.Y + boxB.h; // Position below the other entity
        }
        else
        {
            // If we resolved vertically, we need to reset the horizontal velocity if applicable
            transformA.Position.X = (transformA.Position.X < transformB.Position.X)
                ? transformB.Position.X - boxA.w // Position to the left of the other entity
                : transformB.Position.X + boxB.w; // Position to the right of the other entity
        }

        // Optionally: Reset velocities if needed, or handle other collision responses
        std::cout << "Collision resolved between Entity A and Entity B\n";
    }
};