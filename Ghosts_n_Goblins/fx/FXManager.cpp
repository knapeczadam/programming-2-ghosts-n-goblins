#include "pch.h"
#include "FXManager.h"

#include "Fire.h"
#include "ProjectileBlock.h"
#include "ProjectileDeath.h"
#include "Score.h"
#include "engine/Sprite.h"
#include "game/GameController.h"
#include "engine/SpriteFactory.h"
#include "fx/Fire.h"
#include "characters/IEnemy.h"
#include "collectibles/ICollectible.h"

FXManager::FXManager(GameController* pGameController)
    : m_pGameController{pGameController}
{
}

void FXManager::PlayEffect(Game::Label label, const Point2f& pos, bool flipped, GameObject* other)
{
    for (GameObject* pEffect : m_pGameController->m_Effects)
    {
        if (pEffect->GetLabel() == label and not pEffect->IsActive())
        {
            Point2f newPos{pos};
            newPos.x -= pEffect->GetSprite()->GetScaledClipWidth() / 2.f;
            newPos.y -= pEffect->GetSprite()->GetScaledClipHeight() / 2.f;
            pEffect->SetPosition(newPos);
            pEffect->SetFlipped(flipped);
            pEffect->SetActive(true);
            pEffect->SetVisible(true);
            Score* pScore{dynamic_cast<Score*>(pEffect)};
            if (pScore)
            {
                pEffect->SetVisible(false);
                const IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
                const ICollectible* pCollectible{dynamic_cast<ICollectible*>(other)};
                const int score{pEnemy ? pEnemy->GetScore() : pCollectible->GetScore()};
                pScore->SetScore(score);
            }
            return;
        }
    }
    switch (label)
    {
    case Game::Label::F_FIRE_BOSS:
    case Game::Label::F_FIRE_ENEMY:
    case Game::Label::F_FIRE_TORCH:
        m_pGameController->m_Effects.push_back(new Fire{label, pos, m_pGameController});
        break;
    case Game::Label::F_PROJECTILE_BLOCK_ENEMY:
    case Game::Label::F_PROJECTILE_BLOCK_BOSS:
        m_pGameController->m_Effects.push_back(new ProjectileBlock{label, pos, flipped, m_pGameController});
        break;
    case Game::Label::F_PROJECTILE_DEATH:
        m_pGameController->m_Effects.push_back(new ProjectileDeath{pos, flipped, m_pGameController});
        break;
    case Game::Label::F_SCORE:
        const IEnemy* pEnemy{dynamic_cast<IEnemy*>(other)};
        const ICollectible* pCollectible{dynamic_cast<ICollectible*>(other)};
        const int score{pEnemy ? pEnemy->GetScore() : pCollectible->GetScore()};
        m_pGameController->m_Effects.push_back(new Score{other->GetCollisionBoxCenter(), score, m_pGameController});
        break;
    }
}
