#include "pch.h"
#include "UI.h"

#include "engine/Sprite.h"

UI::UI(Game::Label label, GameController* pGameController)
    : m_Label{label}
    , m_pGameController{pGameController}
    , m_Active{true}
    , m_Visible{true}
    , m_Blinking{false}
    , m_BlinkingTime{0.0f}
{
}

void UI::Draw() const
{
}

void UI::Reset() const
{
}

void UI::Update(float elapsedSec)
{
    if (m_BlinkingTime > 0.0f)
    {
        StartTimer(m_BlinkingTime);
        if (IsTimerFinished())
        {
            m_Blinking = not m_Blinking;
        }
    }
}

bool UI::IsActive() const
{
    return m_Active;
}

bool UI::IsVisible() const
{
    return m_Visible;
}
