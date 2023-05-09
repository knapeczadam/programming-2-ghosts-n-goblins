#pragma once
#include "game/GameObject.h"

class CollisionBox :  public GameObject
{
public:
    explicit CollisionBox(Game::Label label, const Rectf& shape, GameController* pGameController);
    virtual ~CollisionBox() override = default;
    CollisionBox(const CollisionBox& other) = delete;
    CollisionBox(CollisionBox&& other) noexcept = delete;
    CollisionBox& operator=(const CollisionBox& other) = delete;
    CollisionBox& operator=(CollisionBox&& other) noexcept = delete;
};
