#pragma once
#include "UI.h"

#include <map>
# include <string>

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

    virtual void Update(float elapsedSec) override;
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
    std::multimap<int, std::string, std::greater<>> m_Scores;
    const int m_FirstBonusThreshold;
    const int m_SecondBonusThreshold;
    int m_ThirdBonusThreshold;
    bool m_FirstBonus;
    bool m_SecondBonus;
};
