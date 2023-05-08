#include "pch.h"
#include "Pot.h"

#include "game/GameController.h"
#include "level/Level.h"

Pot::Pot(const Point2f& pos, GameController* pGameController)
    : GameObject{Game::Label::O_POT, pos, true, pGameController}
    , m_ContentLabel(Game::Label::D_DUMMY)
{
}

void Pot::Update(float elapsedSec)
{
    m_Shape.bottom += m_Gravity * elapsedSec;
    UpdateCollisionBox();
    if (m_pGameController->m_pLevel->IsOnGround(this))
    {
        m_Active = false;
        m_Visible = false;
        for (GameObject* pCollectible : m_pGameController->m_Collectibles)
        {
            if (pCollectible->GetLabel() == m_ContentLabel)
            {
                pCollectible->SetActive(true);
                pCollectible->SetVisible(true);
                pCollectible->SetPosition(GetPosition<Point2f>());
                return;
            }
        }
    }
}

void Pot::Fall(Game::Label contentLabel, const Point2f& pos)
{
    m_Shape.left = pos.x;
    m_Shape.bottom = pos.y;
    m_Active = true;
    m_Visible = true;
    m_ContentLabel = contentLabel;
}
