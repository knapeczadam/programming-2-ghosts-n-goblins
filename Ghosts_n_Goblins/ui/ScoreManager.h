#pragma once

#include <map>
# include <string>

#include "UI.h"

class Sprite;
class GameController;

class ScoreManager final : public UI
{
public:
    explicit ScoreManager(GameController* pGameController);
    virtual ~ScoreManager() override = default;
    ScoreManager(const ScoreManager& other) = delete;
    ScoreManager(ScoreManager&& other) noexcept = delete;
    ScoreManager& operator=(const ScoreManager& other) = delete;
    ScoreManager& operator=(ScoreManager&& other) noexcept = delete;

    void LoadRanking();
    void SaveRanking();
    void SetScore(int score, const std::string& initial);
    int GetTopScore() const;
    int GetLowestScore() const;
    bool HasTopScore() const;
    bool HasBelowTopScore() const;
    bool IsOnScoreboard() const;
    std::multimap<int, std::string, std::greater<>> GetScores() const;

private:
    const std::string m_Path;
    int m_TopScore;
    std::multimap<int, std::string, std::greater<>> m_Scores;
};
