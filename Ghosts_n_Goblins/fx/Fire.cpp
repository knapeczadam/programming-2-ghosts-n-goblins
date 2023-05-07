#include "pch.h"
#include "Fire.h"

#include "engine/Sprite.h"

Fire::Fire(Game::Label label, const Point2f& pos, GameController* pGameController)
    : GameObject{label, pos, true, pGameController}
{
    m_Shape.left = pos.x - m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom = pos.y - m_pSprite->GetScaledClipHeight() / 2;
}

void Fire::Update(float elapsedSec)
{
    float time{};
    if (m_Label == Game::Label::F_FIRE_ENEMY or m_Label == Game::Label::F_FIRE_BOSS)
    {
        time = 0.8f;
    }
    else if (m_Label == Game::Label::F_FIRE_TORCH)
    {
        time = 0.4f;
    }
    StartTimer(time);
    if (IsTimerFinished())
    {
        m_Active = false;
        m_Visible = false;
    }
}
