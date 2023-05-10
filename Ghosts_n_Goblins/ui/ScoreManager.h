#pragma once

#include <map>
# include <string>

#include "UI.h"

class Sprite;
class GameController;

class ScoreManager final : public UI
{
public:
    enum class Color
    {
        WHITE_TAN = 0,
        SKY_BLUE = 1,
        DARK_TAN = 2
    };
    explicit ScoreManager(GameController* pGameController);
    virtual ~ScoreManager() override = default;
    ScoreManager(const ScoreManager& other) = delete;
    ScoreManager(ScoreManager&& other) noexcept = delete;
    ScoreManager& operator=(const ScoreManager& other) = delete;
    ScoreManager& operator=(ScoreManager&& other) noexcept = delete;

    void LoadHighScores();
    void SaveHighScores();
    void SetScore(std::string name, int score);
    int GetHighScore() const;
    void DrawNumber(Point2f pos, int score, Color color) const;
    std::map<std::string, int, std::greater<>> GetScores() const;

private:
    const std::string m_Path;
    int m_HighScore;
    std::map<std::string, int, std::greater<>> m_Scores;
};
