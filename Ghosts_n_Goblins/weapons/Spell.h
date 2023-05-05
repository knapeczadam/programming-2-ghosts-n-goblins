#pragma once
#include "IThrowable.h"
#include "game/GameObject.h"

class Spell : public GameObject, public IThrowable
{
public:
    Spell(Sprite* pSprite, const Point2f& pos);
    virtual ~Spell() override = default;
    Spell(const Spell& other) = delete;
    Spell(Spell&& other) noexcept = delete;
    Spell& operator=(const Spell& other) = delete;
};
