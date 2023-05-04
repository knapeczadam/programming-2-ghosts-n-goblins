// Knapecz, Adam - 1DAE11
#pragma once

class Level;
class Player;

class Camera final
{
public:
    explicit Camera(const Rectf& viewPort, Level* pLevel, Player* pPlayer);
    ~Camera() = default;
    Camera(const Camera& other) = delete;
    Camera(Camera&& other) noexcept = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera& operator=(Camera&& other) noexcept = delete;
    
    void Draw(const Rectf& target) const;
    void Transform(const Rectf& target) const;

private:
    Point2f Track(const Rectf& target) const;
    void Clamp(Point2f& bottomLeftPos) const;

private:
    Rectf m_ViewPort;
    Level* m_pLevel;
    Player* m_pPlayer;
    Rectf m_LevelBoundaries;
    float m_Width;
    float m_Height;
};
