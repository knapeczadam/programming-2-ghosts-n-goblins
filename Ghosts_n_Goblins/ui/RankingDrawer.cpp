#include "pch.h"
#include "RankingDrawer.h"

#include "InitialDrawer.h"
#include "ScoreManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"

RankingDrawer::RankingDrawer(GameController* pGameController)
    : UI{Game::Label::U_RANKING_DRAWER, pGameController}
    , m_pBackground{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_BEST_RANKING)}
    , m_pAbc{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
{
}

void RankingDrawer::Draw() const
{
    m_pBackground->Draw();
    DrawPlayers();
    DrawScores();
}

void RankingDrawer::DrawPlayers() const
{
    Point2f pos{172.0f, 368.0f};
    const float offset{32.0f};
    for (const auto& result : m_pGameController->m_pScoreManager->GetScores())
    {
        m_pGameController->m_pInitialDrawer->DrawInitial(pos, result.first, InitialDrawer::Color::TAN);
        pos.y -= offset;
    }
}

void RankingDrawer::DrawScores() const
{
    Point2f pos{352.0f, 368.0f};
    const float offset{32.0f};
    for (const auto& result : m_pGameController->m_pScoreManager->GetScores())
    {
        m_pGameController->m_pScoreManager->DrawNumber(pos, result.second, ScoreManager::Color::WHITE_TAN);
        pos.y -= offset;
    }
}
