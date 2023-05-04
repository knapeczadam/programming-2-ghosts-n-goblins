// Knapecz, Adam - 1DAE11
#pragma once

class Level;
class Player;
class GameObject;

class Camera final
{
public:
    explicit Camera(const Rectf& viewPort, Level* pLevel, Player* pPlayer);
    ~Camera() = default;
    Camera(const Camera& other) = delete;
    Camera(Camera&& other) noexcept = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera& operator=(Camera&& other) noexcept = delete;
    
    void Draw() const;
    void Transform();

    bool IsOutOfWindow(const GameObject* pGameObject) const;

private:
    void Track();
    void Clamp();

private:
    Rectf m_ViewPort;
    Level* m_pLevel;
    Player* m_pPlayer;
    Rectf m_LevelBoundaries;
    float m_Width;
    float m_Height;
    Point2f m_Pos;
    const float m_OutOfWindowOffset;
};
