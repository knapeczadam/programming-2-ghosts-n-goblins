#pragma once
#include "UI.h"

class Sprite;

class HighScoreLister : public UI
{
public:
    explicit HighScoreLister(GameController* pGameController);
    virtual ~HighScoreLister() override = default;
    HighScoreLister(const HighScoreLister& other) = delete;
    HighScoreLister(HighScoreLister&& other) noexcept = delete;
    HighScoreLister& operator=(const HighScoreLister& other) = delete;
    HighScoreLister& operator=(HighScoreLister&& other) noexcept = delete;

    virtual void Draw() const override;

private:
    void DrawPlayers() const;
    void DrawScores() const;
private:
    Sprite* m_pBackground;
    Sprite* m_pAbc;
};
