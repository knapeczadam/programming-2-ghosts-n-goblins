#include "pch.h"
#include "Map.h"

#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "engine/Sprite.h"

Map::Map(GameController* pGameController)
    : UI{Game::Label::U_MAP, pGameController}
      , m_pPin{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_PIN)}
      , m_pMap{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MAP)}
      , m_pText{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_PLAYER_ONE_READY)}
      , pDummy{new GameObject{}}
      , m_Speed{100}
      , m_PinPos{58.0f, 66.0f}
      , m_TextPos{112.0f, 224.0f}
{
    m_Blinking = true;
    m_BlinkingTime = 0.2f;

    m_pPin->SetPosition(m_PinPos);
    m_pText->SetPosition(m_TextPos);
}

Map::~Map()
{
    delete pDummy;
}

void Map::Draw() const
{
    m_pMap->Draw();
    if (m_Blinking)
    {
        m_pPin->Draw();
        m_pText->Draw();
    }
}

void Map::Update(float elapsedSec)
{
    UI::Update(elapsedSec);
    pDummy->SetPosition(pDummy->GetPosition<Point2f>() + Vector2f{m_Speed * elapsedSec, 0});
}

void Map::Reset() const
{
    pDummy->SetPosition(Point2f{});
    // pDummy->SetPosition(
        // Point2f{m_pGameController->m_ViewPort.width / 2.0f, m_pGameController->m_ViewPort.height / 2.0f});
}

Rectf Map::GetBoundaries() const
{
    
    return Rectf{0.0f, 0.0f, m_pMap->GetScaledClipWidth(), m_pMap->GetScaledClipHeight()};
}

GameObject* Map::GetDummy() const
{
    return pDummy;
}
