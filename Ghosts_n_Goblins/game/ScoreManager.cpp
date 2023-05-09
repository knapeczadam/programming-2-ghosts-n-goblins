#include "pch.h"
#include "ScoreManager.h"

#include <fstream>
#include <sstream>

ScoreManager::ScoreManager()
    : m_Path{"highscores.txt"}
    , m_HighScore{0}
{
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
