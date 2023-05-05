#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Fireball : public GameObject, public IThrowable
{
public:
    Fireball(Game::Label label, Sprite* pSprite, const Point2f& pos);
    virtual ~Fireball() override = default;
    Fireball(const Fireball& other) = delete;
    Fireball(Fireball&& other) noexcept = delete;
    Fireball& operator=(const Fireball& other) = delete;
    Fireball& operator=(Fireball&& other) noexcept = delete;
};
