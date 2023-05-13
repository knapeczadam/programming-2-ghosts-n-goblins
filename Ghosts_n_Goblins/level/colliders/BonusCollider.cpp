#include "pch.h"
#include "BonusCollider.h"

#include "characters/Player.h"
#include "game/GameController.h"
#include "game/PlayerManager.h"

BonusCollider::BonusCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_BONUS, shape, pGameController}
    , m_Bonus{5000}
{
}

void BonusCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_pGameController->m_pPlayerManager->GetPlayer()->AddScore(m_Bonus);
    m_Active = false;
}
