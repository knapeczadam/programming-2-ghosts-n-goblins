// Knapecz, Adam - 1DAE11
#pragma once

class Texture;

class HUD final
{
public:
    HUD(const Point2f& bottomLeft, int totalPowerUps);
    ~HUD();
    HUD(const HUD& other) = delete;
    HUD(HUD&& other) noexcept = delete;
    HUD& operator=(const HUD& other) = delete;
    HUD& operator=(HUD&& other) noexcept = delete;
    void Draw() const;
    void PowerUpHit();

private:
    void DrawLeft() const;
    void DrawRight() const;
    void DrawPowerUps() const;
    Point2f m_BottomLeft;
    int m_TotalPowerUps;
    int m_HitPowerUps;
    Texture* m_pLeftTexture;
    Texture* m_pRightTexture;
    Texture* m_pPowerUpTexture;
};
