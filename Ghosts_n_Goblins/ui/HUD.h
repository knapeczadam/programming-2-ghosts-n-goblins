// Knapecz, Adam - 1DAE11
#pragma once
#include "UI.h"

class Player;

class HUD : public UI
{
public:
    explicit HUD(Sprite* pSprite, Player* pPlayer, const Rectf& viewPort, SoundManager* pSoundManager);
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
    void DrawTopScore();
    void DrawTime();
    void DrawRemainingTime();
    void DrawFrame() const;
    void DrawWeapon() const;
    void DrawPlayer1() const;
    
    void ResetSprite() const;

private:
    Player* m_pPlayer;
    int m_FirstDigit;
    int m_SecondDigit;
    int m_ThirdDigit;
};
