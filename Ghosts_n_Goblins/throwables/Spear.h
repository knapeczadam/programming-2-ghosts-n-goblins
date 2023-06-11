#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Spear final : public GameObject, public IThrowable
{
public:
    explicit Spear(const Point2f& pos, const Vector2f& direction, bool down, GameController* pGameController);
    virtual ~Spear() override = default;
    Spear(const Spear& other) = delete;
    Spear(Spear&& other) noexcept = delete;
    Spear& operator=(const Spear& other) = delete;
    Spear& operator=(Spear&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void Awake(float elapsedSec) override;

    void SetDown(bool down);
private:
    bool m_Down;
};
