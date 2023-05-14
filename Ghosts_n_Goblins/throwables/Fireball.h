#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Fireball final : public GameObject, public IThrowable
{
public:
    explicit Fireball(Game::Label label, const Point2f& pos, const Vector2f& direction, GameController* pGameController);
    virtual ~Fireball() override = default;
    Fireball(const Fireball& other) = delete;
    Fireball(Fireball&& other) noexcept = delete;
    Fireball& operator=(const Fireball& other) = delete;
    Fireball& operator=(Fireball&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;
};
