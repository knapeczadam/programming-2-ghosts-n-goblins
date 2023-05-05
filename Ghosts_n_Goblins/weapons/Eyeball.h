#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Eyeball : public GameObject, public IThrowable
{
public:
    Eyeball(Sprite* pSprite, const Point2f& pos);
    virtual ~Eyeball() override = default;
    Eyeball(const Eyeball& other) = delete;
    Eyeball(Eyeball&& other) noexcept = delete;
    Eyeball& operator=(const Eyeball& other) = delete;
};
