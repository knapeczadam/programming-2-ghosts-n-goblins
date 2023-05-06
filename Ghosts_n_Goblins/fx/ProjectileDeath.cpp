#include "pch.h"
#include "ProjectileDeath.h"

#include "engine/Sprite.h"

ProjectileDeath::ProjectileDeath(const Point2f& pos, bool flipped, GameController* pGameController)
    : GameObject{Game::Label::F_PROJECTILE_DEATH, pos, false, pGameController}
{
    m_Flipped = flipped;
    m_Shape.left = pos.x - m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom = pos.y - m_pSprite->GetScaledClipHeight() / 2;
}

void ProjectileDeath::Update(float elapsedSec)
{
    const float time{0.2f};
    StartTimer(time);
    if (IsTimerFinished())
    {
        m_Active = false;
        m_Visible = false;
    }
}
