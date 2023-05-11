﻿#pragma once
#include "IEnemy.h"

/**
 * \brief 
 * Also known as Forest Ghosts, these ethereal beings float about at various points along stages 1, 3, 5, and 6.
 * They fly about, making an eerie sound as they do.
 * They carry with them a spear made of green onion.
 * They can launch it forward at you, or drop it down like a bomb.
 * They only take one hit to destroy, are worth 100 points, and can carry a pot, but their motion can be hard to predict.
 * Be especially careful when they are just above the height of your head.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Woody_Pigs">StrategyWiki</a>
 */
class WoodyPig final : public IEnemy
{
public:
    explicit WoodyPig(const Point2f& pos, GameController* pGameController);
    virtual ~WoodyPig() override = default;
    WoodyPig(const WoodyPig& other) = delete;
    WoodyPig(WoodyPig&& other) noexcept = delete;
    WoodyPig& operator=(const WoodyPig& other) = delete;
    WoodyPig& operator=(WoodyPig&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;

protected:
    virtual void Shoot(float elapsedSec) override;
    virtual void Fly(float elapsedSec) override;
};
