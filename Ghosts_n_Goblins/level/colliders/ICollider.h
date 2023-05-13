#pragma once
#include "game/GameObject.h"

class ICollider :  public GameObject
{
public:
    explicit ICollider(Game::Label label, const Rectf& shape, GameController* pGameController);
    virtual ~ICollider() override = default;
    ICollider(const ICollider& other) = delete;
    ICollider(ICollider&& other) noexcept = delete;
    ICollider& operator=(const ICollider& other) = delete;
    ICollider& operator=(ICollider&& other) noexcept = delete;
};
