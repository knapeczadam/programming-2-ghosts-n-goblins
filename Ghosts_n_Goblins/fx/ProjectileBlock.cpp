#include "pch.h"
#include "ProjectileBlock.h"

ProjectileBlock::ProjectileBlock(const Point2f& pos, bool flipped, GameController* pGameController)
    : GameObject{Game::Label::F_PROJECTILE_BLOCK, pos, false, pGameController}
{
    m_Flipped = flipped;
}

void ProjectileBlock::Update(float elapsedSec)
{
    float time{0.3f};
    StartTimer(time);
    if (IsTimerFinished())
    {
        m_Active = false;
        m_Visible = false;
    }
}
