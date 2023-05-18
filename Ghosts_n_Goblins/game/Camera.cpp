// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Camera.h"

#include "GameController.h"
#include "utils.h"
#include "characters/Player.h"
#include "game/GameObject.h"

Camera::Camera(GameController* pGameController)
    : m_pGameController{pGameController}
    , m_Boundaries{0.0f, 0.0f, 0.0f, 0.0f}
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

void Camera::Transform(const GameObject* pGameObject)
{
    Track(pGameObject);
    Clamp();
    glTranslatef(-m_Pos.x, -m_Pos.y, 0.0f);
}

Rectf Camera::GetBoundaries() const
{
    return m_Boundaries;
}

void Camera::SetBoundaries(const Rectf& boundaries)
{
    m_Boundaries = boundaries;
}

bool Camera::IsOutOfWindow(const GameObject* pGameObject) const
{
    const float left{pGameObject->GetCollider().left};
    const float right{pGameObject->GetCollider().left + pGameObject->GetCollider().width};
    const float top{pGameObject->GetCollider().bottom + pGameObject->GetCollider().height};
    const float bottom{pGameObject->GetCollider().bottom};

    const bool horizontal{right + m_OutOfWindowOffset < m_Pos.x or left - m_OutOfWindowOffset > m_Pos.x + m_Width};
    const bool vertical{bottom > m_Height or top < 0.0f};
    return horizontal or vertical;
}

/*
 A helper function that positions the camera around the given rectangle
 target and returns this new position.
 */
void Camera::Track(const GameObject* pGameObject)
{
    const Point2f targetCenter{pGameObject->GetShapeCenter()};
    m_Pos.x = targetCenter.x - m_Width / 2.0f;
    m_Pos.y = targetCenter.y - m_Height / 2.0f;
}

/*
 A helper function that corrects the given camera position so that it
 does not leave the level boundaries.
 */
void Camera::Clamp()
{
    if (m_Pos.x < m_Boundaries.left)
    {
        m_Pos.x = m_Boundaries.left;
    }
    if (m_Pos.x + m_Width > m_Boundaries.left + m_Boundaries.width)
    {
        m_Pos.x = m_Boundaries.left + m_Boundaries.width - m_Width;
    }
    if (m_Pos.y < m_Boundaries.bottom)
    {
        m_Pos.y = m_Boundaries.bottom;
    }
    if (m_Pos.y + m_Height > m_Boundaries.bottom + m_Boundaries.height)
    {
        m_Pos.y = m_Boundaries.bottom + m_Boundaries.height - m_Height;
    }
}
