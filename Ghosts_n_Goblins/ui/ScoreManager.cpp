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
    , m_Path{"highscores.txt"}
    , m_HighScore{0}
    , m_Scores{}
{
    LoadHighScores();
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
            m_Scores.insert({score, name});
        }
        m_HighScore = m_Scores.begin()->first; 
    }
}

void ScoreManager::SaveHighScores()
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
    m_Scores.insert({score, initial});
    m_Scores.erase(std::prev(m_Scores.end()));
}


int ScoreManager::GetHighScore() const
{
    Player* pPlayer{m_pGameController->m_pPlayerManager->GetPlayer()};
    return m_HighScore > pPlayer->GetScore() ? m_HighScore : pPlayer->GetScore();
}

std::multimap<int, std::string, std::greater<>> ScoreManager::GetScores() const
{
    return m_Scores;
}
