// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Camera.h"
#include "utils.h"
#include "characters/Player.h"
#include "level/Level.h"

Camera::Camera(const Rectf& viewPort, Level* pLevel, Player* pPlayer)
    : m_ViewPort{viewPort}
      , m_pLevel{pLevel}
      , m_pPlayer{pPlayer}
      , m_LevelBoundaries{pLevel->GetBoundaries()}
      , m_Width(viewPort.width)
      , m_Height(viewPort.height)
{
}

/*
Positions the camera in such a way that the given rectangle target is in the
center (use Track) and then adjusts this new camera position to the level
boundaries (use Clamp) and draws a blue rectangle at that position with the
dimensions of the camera.
 */
void Camera::Draw(const Rectf& target) const
{
    Point2f cameraPos{Track(target)};
    Clamp(cameraPos);
    utils::SetColor(Color4f{0.0f, 0.0f, 1.0f, 1.0f});
    utils::DrawRect(cameraPos.x, cameraPos.y, m_Width, m_Height);
}

void Camera::Transform(const Rectf& target) const
{
    Point2f cameraPos{Track(target)};
    Clamp(cameraPos);
    glTranslatef(-cameraPos.x, -cameraPos.y, 0.0f);
}

/*
 A helper function that positions the camera around the given rectangle
 target and returns this new position.
 */
Point2f Camera::Track(const Rectf& target) const
{
    const Point2f targetCenter{target.left + target.width / 2.0f, target.bottom + target.height / 2.0f};
    Point2f cameraPos{};
    cameraPos.x = targetCenter.x - m_Width / 2.0f;
    cameraPos.y = targetCenter.y - m_Height / 2.0f;
    return cameraPos;
}

/*
 A helper function that corrects the given camera position so that it
 does not leave the level boundaries.
 */
void Camera::Clamp(Point2f& bottomLeftPos) const
{
    if (bottomLeftPos.x < m_LevelBoundaries.left)
    {
        bottomLeftPos.x = m_LevelBoundaries.left;
    }
    if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
    {
        bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
    }
    if (bottomLeftPos.y < m_LevelBoundaries.bottom)
    {
        bottomLeftPos.y = m_LevelBoundaries.bottom;
    }
    if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
    {
        bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
    }
}
