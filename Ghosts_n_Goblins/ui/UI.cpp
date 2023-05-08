#include "pch.h"
#include "UI.h"

#include "engine/Sprite.h"

UI::UI(Game::Label label, GameController* pGameController)
    : m_Label{label}
    , m_pGameController{pGameController}
{
}

void UI::Draw()
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
