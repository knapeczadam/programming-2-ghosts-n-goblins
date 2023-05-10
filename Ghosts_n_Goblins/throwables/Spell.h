#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Spell final : public GameObject, public IThrowable
{
public:
    explicit Spell(const Point2f& pos, GameController* pGameController);
    virtual ~Spell() override = default;
    Spell(const Spell& other) = delete;
    Spell(Spell&& other) noexcept = delete;
    Spell& operator=(const Spell& other) = delete;
};
