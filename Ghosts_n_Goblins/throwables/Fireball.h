#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Fireball : public GameObject, public IThrowable
{
public:
    explicit Fireball(Game::Label label, const Point2f& pos, GameController* pGameController);
    virtual ~Fireball() override = default;
    Fireball(const Fireball& other) = delete;
    Fireball(Fireball&& other) noexcept = delete;
    Fireball& operator=(const Fireball& other) = delete;
    Fireball& operator=(Fireball&& other) noexcept = delete;
};
