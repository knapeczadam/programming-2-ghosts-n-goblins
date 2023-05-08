// Knapecz, Adam - 1DAE11
#pragma once
#include "UI.h"

class HUD : public UI
{
public:
    explicit HUD(GameController* pGameController);
    virtual ~HUD() override = default;
    HUD(const HUD& other) = delete;
    HUD(HUD&& other) noexcept = delete;
    HUD& operator=(const HUD& other) = delete;
    HUD& operator=(HUD&& other) noexcept = delete;

    virtual void Draw() override;
    virtual void SetFirstDigit(int digit) final;
    virtual void SetSecondDigit(int digit) final;
    virtual void SetThirdDigit(int digit) final;
    
private:
    void DrawLives();
    void DrawPlayerScore();
    void DrawHighScore();
    void DrawTime();
    void DrawFrame() const;
    void DrawWeapon() const;
    
private:
    Sprite* m_pFrame;
    Sprite* m_pLife;
    Sprite* m_pNumbers;
    Sprite* m_pWeapons;
    int m_FirstDigit;
    int m_SecondDigit;
    int m_ThirdDigit;
};
