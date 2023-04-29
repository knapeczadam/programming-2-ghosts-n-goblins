// Knapecz, Adam - 1DAE11

#pragma once
class Texture;

class PowerUp final
{
public:
    enum class Type
    {
        green = 1,
        brown = 2
    };

public:
    explicit PowerUp(const Point2f& center, PowerUp::Type type);
    ~PowerUp();
    PowerUp(const PowerUp& other) = delete;
    PowerUp(PowerUp&& other) noexcept = delete;
    PowerUp& operator=(const PowerUp& other) = delete;
    PowerUp& operator=(PowerUp&& other) noexcept = delete;

    void Update(float elapsedSec);
    void Draw() const;
    bool IsOverlapping(const Rectf& rect) const;

private:
    void SetRadius(float radius);

private:
    const Type m_Type;
    const Texture* m_pTexture;
    const float m_RotSpeed;
    Rectf m_TextClip;
    Circlef m_Shape;
    float m_Angle;
    const char* m_Path;
};
