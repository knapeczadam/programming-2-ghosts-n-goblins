// Knapecz, Adam - 1DAE11
#pragma once


class Camera final
{
public:
    explicit Camera();
    explicit Camera(float width, float height);
    ~Camera() = default;
    Camera(const Camera& other) = delete;
    Camera(Camera&& other) noexcept = delete;
    Camera& operator=(const Camera& other) = delete;
    Camera& operator=(Camera&& other) noexcept = delete;
    void SetLevelBoundaries(const Rectf& levelBoundaries);
    void Draw(const Rectf& target) const;
    void Transform(const Rectf& target) const;
    void SetWidth(float width);
    void SetHeight(float height);

private:
    Point2f Track(const Rectf& target) const;
    void Clamp(Point2f& bottomLeftPos) const;

private:
    float m_Width;
    float m_Height;
    Rectf m_LevelBoundaries;
};
