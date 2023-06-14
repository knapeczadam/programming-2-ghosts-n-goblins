#include "pch.h"
#include "EndCollider.h"

#include "characters/Player.h"
#include "game/GameController.h"
#include "game/LevelManager.h"

EndCollider::EndCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_END, shape, pGameController}
{
    m_ColliderColor = Color4f{1.0f, 1.0f, 0.0f, 1.0f};
}

void EndCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    for (GameObject* collider : m_pGameController->m_pLevelManager->GetColliders())
    {
        if (collider->GetLabel() == Game::Label::L_BONUS and not collider->IsActive())
        {
            m_Active = false;
        }
    }
    Player* pPlayer{static_cast<Player*>(other)};
    pPlayer->SetState(Player::State::WINNING);
}
