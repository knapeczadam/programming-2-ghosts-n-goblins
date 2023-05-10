#pragma once
#include "IEnemy.h"

/* https://strategywiki.org/wiki/Ghosts_%27n_Goblins/Enemies#Crows
 * There are two types of crows in Arthur's land. 
 * They are found in stages 1 and 2, are destroyed in one hit, and are worth 100 points.
 * Blue crows launch themselves straight forward whenever Arthur gets close to one of them.
 * Red crows are only found in stage 2, towards the end of the stage.
 * They differ from blue crows in that they won't only travel horizontally.
 * They will take a diagonal flight path in order to attack you.
 */
class Crow final : public IEnemy
{
public:
    explicit Crow(const Point2f& pos, GameController* pGameController);
    virtual ~Crow() override = default;
    Crow(const Crow& other) = delete;
    Crow(Crow&& other) noexcept = delete;
    Crow& operator=(const Crow& other) = delete;
    Crow& operator=(Crow&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;

protected:
    virtual void Awake(float elapsedSec) override;
    virtual void Wait(float elapsedSec) override;
    virtual void Fly(float elapsedSec) override;

    virtual void Ping() override;
    virtual void Pong() override;

private:
    const float m_Amplitude;
};
