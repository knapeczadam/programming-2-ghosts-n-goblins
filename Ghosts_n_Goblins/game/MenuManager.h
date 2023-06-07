#pragma once
#include "IManager.h"

#include <vector>

class Sprite;

class MenuManager final : public IManager
{
public:
    explicit MenuManager(GameController* pGameController);
    virtual ~MenuManager() override;
    MenuManager(const MenuManager&) = delete;
    MenuManager(MenuManager&&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;
    MenuManager& operator=(MenuManager&&) = delete;

    void DrawContinue() const;
    void DrawGameOver() const;
    void DrawMap() const;
    void DrawMenu() const;
    void DrawRanking() const;
    void DrawSaveScore() const;

    void UpdateContinue(float elapsedSec);
    void UpdateGameOver(float elapsedSec);
    void UpdateMap(float elapsedSec);
    void UpdateMenu(float elapsedSec);
    void UpdateRanking(float elapsedSec);
    void UpdateSaveScore(float elapsedSec);

    virtual void Reset(bool fromCheckpoint = false) override;

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    const int m_MaxIdx;
    int m_Idx;
    std::vector<float> m_Intervals;
    bool m_CreditInserted;
    Sprite* m_pBackground1;
    Sprite* m_pBackground2;
    Sprite* m_pBackground3;
    Sprite* m_pBackground4;
    Time m_Time;
};
