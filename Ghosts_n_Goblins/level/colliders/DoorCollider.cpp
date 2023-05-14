#include "pch.h"
#include "DoorCollider.h"

#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "game/GameController.h"
#include "game/LevelManager.h"
#include "game/PlayerManager.h"

DoorCollider::DoorCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_OPEN, shape, pGameController}
{
    m_ColliderColor = Color4f{0.62f, 0.35f, 0.02f, 1.f};
}

void DoorCollider::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    if (m_pGameController->m_pPlayerManager->GetPlayer()->HasKey())
    {
        m_pGameController->m_pLevelManager->GetDoor()->SetActive(true);
        m_pGameController->m_pLevelManager->GetDoor()->SetVisible(true);
        m_pGameController->m_pSoundManager->PlayEffect(Game::Label::E_DOOR_OPEN);
        m_Active = false;
    }
}
