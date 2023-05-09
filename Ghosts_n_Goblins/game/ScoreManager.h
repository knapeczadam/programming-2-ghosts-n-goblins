#pragma once

#include <map>
# include <string>

class ScoreManager final
{
public:
    ScoreManager();
    ~ScoreManager() = default;
    ScoreManager(const ScoreManager& other) = delete;
    ScoreManager(ScoreManager&& other) noexcept = delete;
    ScoreManager& operator=(const ScoreManager& other) = delete;
    ScoreManager& operator=(ScoreManager&& other) noexcept = delete;

    void LoadHighScores();
    void SaveHighScores();
    void SetScore(std::string name, int score);
    int GetHighScore() const;

private:
    const std::string m_Path;
    int m_HighScore;
    std::map<std::string, int, std::greater<>> m_Scores;
};
