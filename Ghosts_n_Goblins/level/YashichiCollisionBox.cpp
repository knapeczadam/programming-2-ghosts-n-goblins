#include "pch.h"
#include "YashichiCollisionBox.h"
#include "game/GameController.h"
#include "characters/Player.h"
#include "collectibles/Pot.h"

YashichiCollisionBox::YashichiCollisionBox(const Rectf& shape, GameController* pGameController)
    : CollisionBox(Game::Label::L_YASHICHI, shape, pGameController)
    , m_PotPos{ 6123.0f, 448.0f }
{
}

void YashichiCollisionBox::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer{ static_cast<Player*>(other) };
    if (pPlayer->GetState() == Player::State::jumping_standing)
    {
        m_Active = false;
        for (GameObject* pCollectible : m_pGameController->m_Collectibles)
        {
            if (pCollectible->GetLabel() == Game::Label::O_POT)
            {
                static_cast<Pot*>(pCollectible)->Fall(Game::Label::O_YASHICHI, m_PotPos);
                break;
            }
        }
    }
}
