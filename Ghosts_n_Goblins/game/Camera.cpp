// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Camera.h"
#include "utils.h"
#include "characters/Player.h"
#include "level/Level.h"
#include "game/GameObject.h"

#include <iostream>

#include "GameController.h"

Camera::Camera(GameController* pGameController)
    : m_pGameController{pGameController}
    , m_LevelBoundaries{m_pGameController->m_pLevel->GetBoundaries()}
    , m_Width(m_pGameController->m_ViewPort.width)
    , m_Height(m_pGameController->m_ViewPort.height)
    , m_Pos{0.0f, 0.0f}
    , m_OutOfWindowOffset{50.0f}
{
}

/*
Positions the camera in such a way that the given rectangle target is in the
center (use Track) and then adjusts this new camera position to the level
boundaries (use Clamp) and draws a blue rectangle at that position with the
dimensions of the camera.
 */
void Camera::Draw() const
{
    utils::SetColor(Color4f{0.0f, 0.0f, 1.0f, 1.0f});
    utils::DrawRect(m_Pos.x, m_Pos.y, m_Width, m_Height);
}

void Camera::Transform()
{
    Track();
    Clamp();
    glTranslatef(-m_Pos.x, -m_Pos.y, 0.0f);
}

bool Camera::IsOutOfWindow(const GameObject* pGameObject) const
{
    const float left{pGameObject->GetCollisionBox().left};
    const float right{pGameObject->GetCollisionBox().left + pGameObject->GetCollisionBox().width};
    const float top{pGameObject->GetCollisionBox().bottom + pGameObject->GetCollisionBox().height};
    const float bottom{pGameObject->GetCollisionBox().bottom};

    const bool horizontal{right + m_OutOfWindowOffset < m_Pos.x or left - m_OutOfWindowOffset > m_Pos.x + m_Width};
    const bool vertical{bottom > m_Height or top < 0.0f};
    return horizontal or vertical;
}

/*
 A helper function that positions the camera around the given rectangle
 target and returns this new position.
 */
void Camera::Track()
{
    const Point2f targetCenter{m_pGameController->m_pPlayer->GetShapeCenter()};
    m_Pos.x = targetCenter.x - m_Width / 2.0f;
    m_Pos.y = targetCenter.y - m_Height / 2.0f;
}

/*
 A helper function that corrects the given camera position so that it
 does not leave the level boundaries.
 */
void Camera::Clamp()
{
    if (m_Pos.x < m_LevelBoundaries.left)
    {
        m_Pos.x = m_LevelBoundaries.left;
    }
    if (m_Pos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
    {
        m_Pos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
    }
    if (m_Pos.y < m_LevelBoundaries.bottom)
    {
        m_Pos.y = m_LevelBoundaries.bottom;
    }
    if (m_Pos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
    {
        m_Pos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
    }
}
