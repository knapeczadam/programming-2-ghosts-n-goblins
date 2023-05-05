#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Eyeball : public GameObject, public IThrowable
{
public:
    Eyeball(const Point2f& pos, SpriteFactory* pSpriteFactory);
    virtual ~Eyeball() override = default;
    Eyeball(const Eyeball& other) = delete;
    Eyeball(Eyeball&& other) noexcept = delete;
    Eyeball& operator=(const Eyeball& other) = delete;
};
