#pragma once
#include "IEnemy.h"

class BigMan : public IEnemy
{
public:
    BigMan(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager);
    virtual ~BigMan() override = default;
    BigMan(const BigMan& other) = delete;
    BigMan(BigMan&& other) noexcept = delete;
    BigMan& operator=(const BigMan& other) = delete;
    BigMan& operator=(BigMan&& other) noexcept = delete;
    
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
protected:
    virtual void Wait() override;
    virtual void Walk() override;
    virtual void Jump() override;
    virtual void Shoot() override;

private:
};
