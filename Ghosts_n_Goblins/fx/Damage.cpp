#include "pch.h"
#include "Damage.h"

#include "engine/Sprite.h"

Damage::Damage(const Point2f& pos, bool flipped, GameController* pGameController)
    : GameObject(Game::Label::F_DAMAGE, pos, false, pGameController)
{
    m_Shape.left = pos.x - m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom = pos.y - m_pSprite->GetScaledClipHeight() / 2;
    m_Flipped = flipped;
}

void Damage::Update(float elapsedSec)
{
    const float time{1.0f};
    StartTimer(time);
    if (m_pSprite->GetIterCount() == 1)
    {
        m_Active = false;
        m_Visible = false;
        m_pSprite->ResetIterCount();
    }
}
