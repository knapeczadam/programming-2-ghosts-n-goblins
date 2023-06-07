#include "pch.h"
#include "YashichiCollider.h"

#include "characters/Player.h"
#include "collectibles/Pot.h"
#include "game/CollectibleManager.h"
#include "game/GameController.h"

YashichiCollider::YashichiCollider(const Rectf& shape, GameController* pGameController)
    : ICollider(Game::Label::L_YASHICHI, shape, pGameController)
      , m_PotPos{6123.0f, 448.0f}
{
}

void YashichiCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer{static_cast<Player*>(other)};
    if (pPlayer->GetState() == Player::State::JUMPING_STANDING)
    {
        m_Active = false;
        for (GameObject* pCollectible : m_pGameController->m_pCollectibleManager->GetCollectibles())
        {
            if (pCollectible->GetLabel() == Game::Label::O_POT)
            {
                static_cast<Pot*>(pCollectible)->Fall(Game::Label::O_YASHICHI, m_PotPos);
                break;
            }
        }
    }
}
