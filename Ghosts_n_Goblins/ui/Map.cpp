#include "pch.h"
#include "Map.h"

#include <iostream>

#include "engine/SpriteFactory.h"
#include "game/GameController.h"
#include "engine/Sprite.h"
#include "game/UIManager.h"

Map::Map(GameController* pGameController)
    : UI{Game::Label::U_MAP, pGameController}
      , m_pPin{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_PIN)}
      , m_pMap{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_MAP)}
      , m_pTextPlayerOneReady{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_TEXT_PLAYER_ONE_READY)}
      , pDummy{new GameObject{Game::Label::D_DUMMY, Rectf{0, 0, 30.0f, 30.0f}, false}}
      , m_Speed{120}
      , m_PinPos1{58.0f, 66.0f}
      , m_PinPos2{122.0f, 66.0f}
      , m_TextPos{112.0f, 224.0f}
{
    m_pPin->SetPosition(m_PinPos1);
    m_pTextPlayerOneReady->SetPosition(m_TextPos);
}

Map::~Map()
{
    delete pDummy;
}

void Map::Draw() const
{
    m_pMap->Draw();
    m_pPin->Draw();
}

void Map::Update(float elapsedSec)
{
    m_pPin->Update(elapsedSec);
    m_pTextPlayerOneReady->Update(elapsedSec);
    
    const float x = pDummy->GetPosition<Point2f>().x + m_Speed * elapsedSec;
    pDummy->SetPosition(Point2f{x, 0});
}

void Map::Reset()
{
    pDummy->SetPosition(Point2f{});
    m_pPin->SetPosition(m_PinPos1);
    pDummy->SetPosition(Point2f{0, m_pGameController->m_ViewPort.height / 2});
}

void Map::DrawTextPlayerOneReady() const
{
    m_pTextPlayerOneReady->Draw();
}

Rectf Map::GetBoundaries() const
{
    return Rectf{0.0f, 0.0f, m_pMap->GetScaledClipWidth(), m_pMap->GetScaledClipHeight()};
}

GameObject* Map::GetDummy() const
{
    return pDummy;
}
