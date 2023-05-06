#include "pch.h"
#include "ProjectileBlock.h"

#include "engine/Sprite.h"

ProjectileBlock::ProjectileBlock(const Point2f& pos, bool flipped, GameController* pGameController)
    : GameObject{Game::Label::F_PROJECTILE_BLOCK, pos, false, pGameController}
{
    m_Flipped = flipped;
    m_Shape.left = pos.x - m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom = pos.y - m_pSprite->GetScaledClipHeight() / 2;
}

void ProjectileBlock::Update(float elapsedSec)
{
    float time{0.2f}; // 1 / (200/3) * 1000
    StartTimer(time);
    if (IsTimerFinished())
    {
        m_Active = false;
        m_Visible = false;
    }
}
