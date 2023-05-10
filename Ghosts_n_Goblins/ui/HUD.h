// Knapecz, Adam - 1DAE11
#pragma once
#include "UI.h"

class HUD final : public UI
{
public:
    explicit HUD(GameController* pGameController);
    virtual ~HUD() override = default;
    HUD(const HUD& other) = delete;
    HUD(HUD&& other) noexcept = delete;
    HUD& operator=(const HUD& other) = delete;
    HUD& operator=(HUD&& other) noexcept = delete;

    virtual void Draw() const override;
    void SetFirstDigit(int digit);
    void SetSecondDigit(int digit);
    void SetThirdDigit(int digit); 
private:
    void DrawLives() const;
    void DrawPlayerScore() const;
    void DrawHighScore() const;
    void DrawRemainingTime() const;
    void DrawTextTime() const;
    void DrawTextTopRow() const;
    void DrawWeapon() const;
    void DrawFrame() const;
    
private:
    Sprite* m_pTextTopRow;
    Sprite* m_pLife;
    Sprite* m_pNumbers;
    Sprite* m_pWeapons;
    Sprite* m_pTextTime;
    Sprite* m_pFrame;
    int m_FirstDigit;
    int m_SecondDigit;
    int m_ThirdDigit;
};
