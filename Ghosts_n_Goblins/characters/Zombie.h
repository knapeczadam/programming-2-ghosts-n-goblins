﻿#pragma once
#include "IEnemy.h"
#include "game/GameObject.h"

/*
 * Zombies are the first enemies that you will ever encounter.
 * They climb out of the graveyard soil, and march unerringly in your direction.
 * They only take one shot to destroy, and they are worth 200 points.
 * They are the bearers of pots, and you will only ever see three above ground at one time.
 * You will encounter them on Stage 3 in addition to the first stage.
 */
class Zombie : public IEnemy
{
public:
    Zombie(Sprite* pSprite, const Point2f& pos, Player* pPlayer,Sprite* pFX, SoundManager* pSoundManager);
    virtual ~Zombie() override = default;
    Zombie(const Zombie& other) = delete;
    Zombie(Zombie&& other) noexcept = delete;
    Zombie& operator=(const Zombie& other) = delete;
    Zombie& operator=(Zombie&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Walk(float elapsedSec) override;
    virtual void Spawn() override;
};
