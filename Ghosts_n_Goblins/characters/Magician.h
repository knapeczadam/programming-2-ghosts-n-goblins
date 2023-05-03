#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

class Magician : public GameObject, public IEnemy
{
public:
    Magician(Sprite* pSprite, const Point2f& pos);
    virtual ~Magician() override = default;
    Magician(const Magician& other) = delete;
    Magician(Magician&& other) noexcept = delete;
    Magician& operator=(const Magician& other) = delete;
    Magician& operator=(Magician&& other) noexcept = delete;
};
