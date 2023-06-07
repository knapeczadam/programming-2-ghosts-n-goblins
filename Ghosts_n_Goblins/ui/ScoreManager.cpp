#include "pch.h"
#include "ScoreManager.h"

#include "engine/SpriteFactory.h"
#include "game/GameController.h"

#include <fstream>
#include <sstream>

#include "game/PlayerManager.h"
#include "characters/Player.h"

ScoreManager::ScoreManager(GameController* pGameController)
    : UI{Game::Label::U_SCORE_MANAGER, pGameController}
    , m_Path{"ranking.txt"}
    , m_TopScore{0}
    , m_Scores{}
    , m_FirstBonusThreshold{20000}
    , m_SecondBonusThreshold{70000}
    , m_ThirdBonusThreshold{ 2 * m_SecondBonusThreshold}
    , m_FirstBonus{false}
    , m_SecondBonus{false}
{
    LoadRanking();
}

void ScoreManager::Update(float elapsedSec)
{
    Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
    const int score{pPlayer->GetScore()};
    if (score >= m_FirstBonusThreshold and not m_FirstBonus)
    {
        pPlayer->IncreaseLives();
        m_FirstBonus = true;
    }
    else if (score >= m_SecondBonusThreshold and not m_SecondBonus)
    {
        pPlayer->IncreaseLives();
        m_SecondBonus = true;
    }
    else if (score >= m_ThirdBonusThreshold)
    {
        pPlayer->IncreaseLives();
        m_ThirdBonusThreshold += m_SecondBonusThreshold;
    }
}

void ScoreManager::LoadRanking()
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
            m_Scores.insert({score, name});
        }
    }
}

void ScoreManager::SaveRanking()
{
    std::fstream file{m_Path, std::ios::out};
    if (file)
    {
        for (const auto& [score, initial] : m_Scores)
        {
            file << initial << " " << score << '\n';
        }
    }
}

void ScoreManager::SetScore(int score, const std::string& initial)
{
    m_Scores.erase(std::prev(m_Scores.end()));
    m_Scores.insert({score, initial});
}


int ScoreManager::GetTopScore() const
{
    Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
    return m_Scores.begin()->first > pPlayer->GetScore() ? m_Scores.begin()->first : pPlayer->GetScore();
}

int ScoreManager::GetLowestScore() const
{
    return m_Scores.rbegin()->first;
}

bool ScoreManager::HasTopScore() const
{
    const int playerScore{m_pGameController->m_pPlayerManager->GetPlayer()->GetScore()};
    return playerScore >= GetTopScore();
}

bool ScoreManager::HasBelowTopScore() const
{
    const int playerScore{m_pGameController->m_pPlayerManager->GetPlayer()->GetScore()};
    return playerScore < GetTopScore() and playerScore >= GetLowestScore();
}

bool ScoreManager::IsOnScoreboard() const
{
    return HasTopScore() or HasBelowTopScore();
}

std::multimap<int, std::string, std::greater<>> ScoreManager::GetScores() const
{
    return m_Scores;
}
