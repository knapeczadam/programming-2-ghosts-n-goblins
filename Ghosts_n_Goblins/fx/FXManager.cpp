#include "pch.h"
#include "FXManager.h"

#include "ProjectileBlock.h"
#include "ProjectileDeath.h"
#include "engine/Sprite.h"
#include "game/GameController.h"
#include "engine/SpriteFactory.h"

FXManager::FXManager(GameController* pGameController)
    : m_pGameController{pGameController}
{
}

void FXManager::PlayEffect(Game::Label label, const Point2f& contactPoint, bool flipped)
{
    for (GameObject* pEffect : m_pGameController->m_Effects)
    {
        if (pEffect->GetLabel() == label and not pEffect->IsActive())
        {
            Point2f pos{contactPoint};
            pos.x -= pEffect->GetSprite()->GetScaledClipWidth() / 2.f;
            pos.y -= pEffect->GetSprite()->GetScaledClipHeight() / 2.f;
            pEffect->SetPosition(pos);
            pEffect->SetFlipped(flipped);
            pEffect->SetActive(true);
            pEffect->SetVisible(true);
            return;
        }
    }
    switch (label)
    {
        case Game::Label::F_PROJECTILE_BLOCK:
            m_pGameController->m_Effects.push_back(new ProjectileBlock{contactPoint,flipped, m_pGameController});
            break;
        case Game::Label::F_PROJECTILE_DEATH:
            m_pGameController->m_Effects.push_back(new ProjectileDeath{contactPoint, flipped, m_pGameController});
            break;
    }
}
