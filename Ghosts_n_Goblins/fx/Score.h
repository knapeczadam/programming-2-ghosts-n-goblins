#pragma once
#include "game/GameObject.h"

class Score : public GameObject
{
public:
    Score(const Point2f& pos, int score, GameController* pGameController);
    virtual ~Score() override = default;
    Score(const Score& other) = delete;
    Score(Score&& other) noexcept = delete;
    Score& operator=(const Score& other) = delete;
    Score& operator=(Score&& other) noexcept = delete;

    virtual void Update(float elapsedSec) override;
    virtual void SetScore(int score) final;
private:
    virtual float SetTimme() const final;

    int m_Score;
    bool m_Shown;
};
