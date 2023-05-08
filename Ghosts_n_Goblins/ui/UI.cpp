#include "pch.h"
#include "UI.h"

#include "engine/Sprite.h"

UI::UI(Game::Label label, GameController* pGameController)
    : m_Label{label}
    , m_pGameController{pGameController}
    , m_Active{true}
    , m_Visible{true}
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
}

bool UI::IsActive() const
{
    return m_Active;
}

bool UI::IsVisible() const
{
    return m_Visible;
}
