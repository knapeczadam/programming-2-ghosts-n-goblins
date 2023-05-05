#pragma once
#include "GameObject.h"

class CollisionBox :  public GameObject
{
public:
    explicit CollisionBox(Game::Label label, const Rectf& shape, const Color4f& color = Color4f{0.0f, 1.0f, 1.0f, 1.0f});
    virtual ~CollisionBox() override = default;
    CollisionBox(const CollisionBox& other) = delete;
    CollisionBox(CollisionBox&& other) noexcept = delete;
    CollisionBox& operator=(const CollisionBox& other) = delete;
    CollisionBox& operator=(CollisionBox&& other) noexcept = delete;
};
