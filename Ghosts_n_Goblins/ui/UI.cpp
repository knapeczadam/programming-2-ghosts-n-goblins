#include "pch.h"
#include "UI.h"

#include "engine/Sprite.h"

UI::UI(Game::Label label, Sprite* pSprite, const Rectf& viewPort, SoundManager* pSoundManager)
    : m_Label{label}
    , m_pSprite{pSprite}
    , m_ViewPort{viewPort}
    , m_pSoundManager{pSoundManager}
{
}

void UI::Draw()
{
}

void UI::Draw() const
{
    m_pSprite->Draw();
}

void UI::Reset() const
{
}

void UI::Update(float elapsedSec)
{
    m_pSprite->Update(elapsedSec);
}
