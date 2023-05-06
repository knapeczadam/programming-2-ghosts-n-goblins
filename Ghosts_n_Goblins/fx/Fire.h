#pragma once
#include "game/GameObject.h"

class Fire : public GameObject
{
public:
    explicit Fire(Game::Label label, const Point2f& pos, GameController* pGameController);
    virtual ~Fire() override = default;
    Fire(const Fire& other) = delete;
    Fire(Fire&& other) noexcept = delete;
    Fire& operator=(const Fire& other) = delete;
    Fire& operator=(Fire&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
};
