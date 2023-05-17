#include "pch.h"
#include "IPotter.h"

#include "game/GameObject.h"

IPotter::IPotter()
    : m_pPot{nullptr}
{
}

GameObject* IPotter::GetPot() const
{
    return m_pPot;
}

void IPotter::SetPot(GameObject* pPot)
{
    m_pPot = pPot;
}

void IPotter::Update(float elapsedSec)
{
    if (m_pPot)
    {
        GameObject* pEnemy {dynamic_cast<GameObject*>(this)};
        m_pPot->SetPosition(pEnemy->GetPosition<Point2f>());
        m_pPot->UpdateCollider();
    }
}

void IPotter::ActivatePot()
{
    if (m_pPot)
    {
        m_pPot->SetActive(true);
        m_pPot->SetVisible(true);
        m_pPot = nullptr;
    }
}

void IPotter::HidePot()
{
    if (m_pPot)
    {
        m_pPot->SetVisible(false);
    }
}

void IPotter::ShowPot()
{
    if (m_pPot)
    {
        m_pPot->SetVisible(true);
    }
}
