#include "pch.h"
#include "RankingDrawer.h"

#include "InitialDrawer.h"
#include "ScoreManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "game/UIManager.h"

RankingDrawer::RankingDrawer(GameController* pGameController)
    : UI{Game::Label::U_RANKING_DRAWER, pGameController}
    , m_pTextBestRanking{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_BEST_RANKING)}
    , m_pAbc{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
{
    m_pTextBestRanking->SetPosition(Point2f{102.0f, 80.0f});
}

void RankingDrawer::Draw() const
{
    m_pTextBestRanking->Draw();
    DrawPlayers();
    DrawScores();
}

void RankingDrawer::DrawPlayers() const
{
    Point2f pos{172.0f, 368.0f};
    const float offset{32.0f};
    for (const auto& result : m_pGameController->m_pUIManager->m_pScoreManager->GetScores())
    {
        m_pGameController->m_pUIManager->m_pInitialDrawer->DrawInitial(pos, result.second, InitialDrawer::Color::TAN);
        pos.y -= offset;
    }
}

void RankingDrawer::DrawScores() const
{
    float y {368.0f};
    const float offset{32.0f};
    for (const auto& result : m_pGameController->m_pUIManager->m_pScoreManager->GetScores())
    {
        Point2f pos{352.0f, y};
        DrawNumber(pos, result.first, ScoreManager::Color::WHITE_TAN);
        y -= offset;
    }
}
