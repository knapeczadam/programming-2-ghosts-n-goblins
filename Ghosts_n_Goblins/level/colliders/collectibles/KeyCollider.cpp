﻿#include "pch.h"
#include "KeyCollider.h"

#include "characters/Player.h"
#include "engine/SoundManager.h"
#include "game/CollectibleManager.h"
#include "game/EnemyManager.h"
#include "game/GameController.h"

KeyCollider::KeyCollider(const Rectf& shape, GameController* pGameController)
    : ICollider{Game::Label::L_KEY, shape, pGameController}
{
    m_ColliderColor = Color4f{0.84f, 0.73f, 0.0f, 1.0f};
}

void KeyCollider::HandleCollision(GameObject* other)
{
    for (GameObject* pEnemy : m_pGameController->m_pEnemyManager->GetEnemies())
    {
        if (pEnemy->GetLabel() == Game::Label::C_UNICORN and pEnemy->IsActive())
        {
            return;
        }
    }

    if (not IsOverlapping(other)) return;
    for (GameObject* pCollectible : m_pGameController->m_pCollectibleManager->GetCollectibles())
    {
        if (pCollectible->GetLabel() == Game::Label::O_KEY)
        {
            pCollectible->SetActive(true);
            pCollectible->SetVisible(true);
            pCollectible->SetAwake(true);
            m_Active = false;
        }
    }
}