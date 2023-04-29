// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "HUD.h"
#include "Texture.h"

HUD::HUD(const Point2f& bottomLeft, int totalPowerUps)
    : m_BottomLeft{bottomLeft.x, bottomLeft.y}
      , m_TotalPowerUps{totalPowerUps}
      , m_HitPowerUps{}
      , m_pLeftTexture{new Texture{"images/minigame/HudLeft.png"}}
      , m_pRightTexture{new Texture{"images/minigame/HudRight.png"}}
      , m_pPowerUpTexture{new Texture{"images/minigame/HudPowerUp.png"}}
{
}

HUD::~HUD()
{
    delete m_pLeftTexture;
    delete m_pRightTexture;
    delete m_pPowerUpTexture;
}

void HUD::Draw() const
{
    DrawLeft();
    DrawPowerUps();
    DrawRight();
}

void HUD::PowerUpHit()
{
    if (m_HitPowerUps < m_TotalPowerUps)
    {
        ++m_HitPowerUps;
    }
}

void HUD::DrawLeft() const
{
    m_pLeftTexture->Draw(m_BottomLeft);
}

void HUD::DrawRight() const
{
    Point2f bottomLeft{m_BottomLeft.x + m_pLeftTexture->GetWidth(), m_BottomLeft.y};
    bottomLeft.x += m_TotalPowerUps * (m_pPowerUpTexture->GetWidth() / 2);
    m_pRightTexture->Draw(bottomLeft);
}

void HUD::DrawPowerUps() const
{
    for (int i{}; i < m_TotalPowerUps; ++i)
    {
        Point2f bottomLeft{m_BottomLeft.x + m_pLeftTexture->GetWidth(), m_BottomLeft.y};
        bottomLeft.x += i * (m_pPowerUpTexture->GetWidth() / 2);
        Rectf src;
        if (i < m_HitPowerUps)
        {
            src.left = 0;
        }
        else
        {
            src.left = m_pPowerUpTexture->GetWidth() / 2;
        }
        src.width = m_pPowerUpTexture->GetWidth() / 2;
        src.height = m_pPowerUpTexture->GetHeight();
        m_pPowerUpTexture->Draw(bottomLeft, src);
    }
}
