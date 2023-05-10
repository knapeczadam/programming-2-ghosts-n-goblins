#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Eyeball final : public GameObject, public IThrowable
{
public:
    explicit Eyeball(const Point2f& pos, const Vector2f& direction, GameController* pGameController);
    virtual ~Eyeball() override = default;
    Eyeball(const Eyeball& other) = delete;
    Eyeball(Eyeball&& other) noexcept = delete;
    Eyeball& operator=(const Eyeball& other) = delete;
    Eyeball& operator=(Eyeball&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    void SetDirection(const Vector2f& direction);

private:
    Vector2f m_Direction;
    const float m_Speed;
};
