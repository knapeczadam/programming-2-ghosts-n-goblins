// Knapecz, Adam - 1DAE11
#pragma once

class Level;
class Player;
class GameObject;
class GameController;

class Camera final
{
public:
    explicit Camera(GameController* pGameController);
    ~Camera() = default;
    Camera(const Camera& other) = delete;
    Camera(Camera&& other) noexcept = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera& operator=(Camera&& other) noexcept = delete;

    void Draw() const;
    void Transform(const GameObject* pGameObject);
    Rectf GetBoundaries() const;
    void SetBoundaries(const Rectf& boundaries);
    bool IsOutOfWindow(const GameObject* pGameObject) const;

private:
    void Track(const GameObject* pGameObject);
    void Clamp();

private:
    GameController* m_pGameController;
    Rectf m_Boundaries;
    float m_Width;
    float m_Height;
    Point2f m_Pos;
    const float m_OutOfWindowOffset;
};
