#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Eyeball : public GameObject, public IThrowable
{
public:
    Eyeball(const Point2f& pos, const Vector2f& direction, SpriteFactory* pSpriteFactory);
    virtual ~Eyeball() override = default;
    Eyeball(const Eyeball& other) = delete;
    Eyeball(Eyeball&& other) noexcept = delete;
    Eyeball& operator=(const Eyeball& other) = delete;

    virtual void Update(float elapsedSec) override;

private:
    Vector2f m_Direction;
    const float m_Speed;
};
