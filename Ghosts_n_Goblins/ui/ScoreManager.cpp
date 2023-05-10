#include "pch.h"
#include "ScoreManager.h"

#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"

#include <fstream>
#include <sstream>

ScoreManager::ScoreManager(GameController* pGameController)
    : UI{Game::Label::U_SCORE_MANAGER, pGameController}
    , m_Path{"highscores.txt"}
    , m_HighScore{0}
    , m_Scores{}
{
    m_pGameController->m_pScoreManager = this;
    m_pSprite = pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_NUMBERS);
}

void ScoreManager::LoadHighScores()
{
    std::fstream file{m_Path};
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::string name;
            int score;
            std::stringstream ss{line};
            ss >> name >> score;
            m_Scores[name] = score;
        }
        m_HighScore = m_Scores.begin()->second; 
    }
}

void ScoreManager::SaveHighScores()
{
    std::fstream file{m_Path, std::ios::out};
    if (file)
    {
        for (const auto& [name, score] : m_Scores)
        {
            file << name << " " << score << '\n';
        }
    }
}

void ScoreManager::SetScore(std::string name, int score)
{
    m_Scores[name] = score;
    m_Scores.erase(std::prev(m_Scores.end()));
}


int ScoreManager::GetHighScore() const
{
    return m_HighScore;
}
/*
 * color: 0 = white tan, 1 = sky blue, 2 = dark tan
 */
void ScoreManager::DrawNumber(Point2f pos, int score, Color color) const
{
    const float offset{m_pSprite->GetScaledClipWidth()};
    m_pSprite->SetTopOffsetRows(int(color));
    if (score == 0)
    {
        m_pSprite->SetLeftOffsetCols(0);
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
    }
    for (int tempScore = score; tempScore > 0; tempScore /= 10)
    {
        const int digit{tempScore % 10};
        m_pSprite->SetLeftOffsetCols(digit);
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
        pos.x -= offset;
    }
    
}

std::map<std::string, int, std::greater<>> ScoreManager::GetScores() const
{
    return m_Scores;
}
