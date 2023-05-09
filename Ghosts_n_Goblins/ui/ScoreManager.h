#pragma once

#include <map>
# include <string>

class Sprite;
class GameController;

class ScoreManager final
{
public:
    enum class Color
    {
        WHITE_TAN = 0,
        SKY_BLUE = 1,
        DARK_TAN = 2
    };
    explicit ScoreManager(GameController* pGameController);
    ~ScoreManager() = default;
    ScoreManager(const ScoreManager& other) = delete;
    ScoreManager(ScoreManager&& other) noexcept = delete;
    ScoreManager& operator=(const ScoreManager& other) = delete;
    ScoreManager& operator=(ScoreManager&& other) noexcept = delete;

    void LoadHighScores();
    void SaveHighScores();
    void SetScore(std::string name, int score);
    int GetHighScore() const;
    void DrawScore(Point2f pos, int score, Color color) const;
    std::map<std::string, int, std::greater<>> GetScores() const;

private:
    const std::string m_Path;
    int m_HighScore;
    std::map<std::string, int, std::greater<>> m_Scores;
    Sprite* m_pSprite;
    GameController* m_pGameController;
};
