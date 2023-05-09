#include "pch.h"
#include "HighScoreLister.h"

#include "engine/SpriteFactory.h"
#include "game/GameController.h"

HighScoreLister::HighScoreLister(GameController* pGameController)
    : UI{Game::Label::U_HIGH_SCORE_LISTER, pGameController}
    , m_pBackground{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_RANKING)}
    , m_pAbc{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
{
}

void HighScoreLister::Draw() const
{
    DrawPlayers();
    DrawScores();
}

void HighScoreLister::DrawPlayers() const
{
}

void HighScoreLister::DrawScores() const
{
}
