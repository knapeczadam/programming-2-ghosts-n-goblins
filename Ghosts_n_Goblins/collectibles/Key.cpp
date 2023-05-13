#include "pch.h"
#include "Key.h"

#include "game/GameController.h"
#include "game/LevelManager.h"
#include "level/Level.h"

Key::Key(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_KEY, pos, true, pGameController}
    , m_Speed{50.0f}
{
    m_Score = 1000;
    
}

void Key::Update(float elapsedSec)
{
    if (m_pGameController->m_pLevelManager->GetLevel()->IsOnGround(this))
    {
        m_Speed = 0.0f;
        m_Awake = true;
    }
    m_Shape.bottom -= m_Speed * elapsedSec;
    UpdateCollider();
}
