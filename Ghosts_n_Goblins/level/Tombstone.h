#pragma once
#include "game/GameObject.h"

class Tombstone : public GameObject
{
public:
    explicit Tombstone(const Rectf& shape, GameController* pGameController);
    virtual ~Tombstone() override = default;
    Tombstone(const Tombstone& other) = delete;
    Tombstone(Tombstone&& other) noexcept = delete;
    Tombstone& operator=(const Tombstone& other) = delete;
    Tombstone& operator=(Tombstone&& other) noexcept = delete;

    virtual void HandleCollision(GameObject* other) override;
private:
    int m_HitCount;
    const int m_MaxHitCount;
};
