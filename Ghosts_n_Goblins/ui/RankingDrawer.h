#pragma once
#include "UI.h"

class Sprite;

class RankingDrawer final : public UI
{
public:
    explicit RankingDrawer(GameController* pGameController);
    virtual ~RankingDrawer() override = default;
    RankingDrawer(const RankingDrawer& other) = delete;
    RankingDrawer(RankingDrawer&& other) noexcept = delete;
    RankingDrawer& operator=(const RankingDrawer& other) = delete;
    RankingDrawer& operator=(RankingDrawer&& other) noexcept = delete;

    virtual void Draw() const override;

private:
    void DrawPlayers() const;
    void DrawScores() const;
private:
    Sprite* m_pBackground;
    Sprite* m_pAbc;
};
