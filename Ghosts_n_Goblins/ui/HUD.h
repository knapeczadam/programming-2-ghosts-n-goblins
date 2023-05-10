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
    void DrawTextTime() const;
    void DrawRemainingTime() const;
private:
    void DrawLives() const;
    void DrawWeapon() const;
    void DrawFrame() const;
    
private:
    Sprite* m_pFrame;
    Sprite* m_pLife;
    Sprite* m_pNumbers;
    Sprite* m_pTextTime;
    Sprite* m_pWeapons;
    int m_FirstDigit;
    int m_SecondDigit;
    int m_ThirdDigit;
};
