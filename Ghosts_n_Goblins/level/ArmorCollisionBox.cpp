#include "pch.h"
#include "ArmorCollisionBox.h"

#include "characters/Player.h"
#include "collectibles/Pot.h"
#include "game/CollectibleManager.h"
#include "game/GameController.h"

ArmorCollisionBox::ArmorCollisionBox(const Rectf& shape, GameController* pGameController)
    : CollisionBox{Game::Label::L_ARMOR, shape,  pGameController}
    , m_PotPos{3068.0f, 144.0f}
{
}

void ArmorCollisionBox::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    Player* pPlayer{static_cast<Player*>(other)};
    if (pPlayer->GetState() == Player::State::JUMPING_STANDING and pPlayer->GetHP() == 1)
    {
        m_Active = false;
        for (GameObject* pCollectible : m_pGameController->m_pCollectibleManager->GetCollectibles())
        {
            if (pCollectible->GetLabel() == Game::Label::O_POT)
            {
                static_cast<Pot*>(pCollectible)->Fall(Game::Label::O_ARMOR, m_PotPos);
                break;
            }
        }
    }
    
}
