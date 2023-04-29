// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "PowerUp.h"

#include "Texture.h"
#include "utils.h"

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
    : m_Type{type}
      , m_pTexture{nullptr}
      , m_RotSpeed{360.0f}
      , m_TextClip{}
      , m_Shape{}
      , m_Angle{0}
      , m_Path{"images/minigame/PowerUp.png"}
{
    m_pTexture = new Texture{m_Path};


    m_TextClip.width = m_pTexture->GetWidth();
    m_TextClip.height = m_pTexture->GetHeight() / 2;
    m_TextClip.left = 0.0f;
    m_TextClip.bottom = 0.0f;

    m_Shape.center = center;
    m_Shape.radius = m_TextClip.width / 2;
}

PowerUp::~PowerUp()
{
    delete m_pTexture;
}

void PowerUp::Update(float elapsedSec)
{
    m_Angle += m_RotSpeed * elapsedSec;
}

void PowerUp::Draw() const
{
    Rectf src;
    if (m_Type == Type::green)
    {
        src.bottom = m_pTexture->GetHeight() - m_TextClip.height;
    }
    src.left = m_TextClip.left;
    src.width = m_TextClip.width;
    src.height = m_TextClip.height;

    Rectf dst;
    dst.width = m_TextClip.width;
    dst.height = m_TextClip.height;
    dst.left = m_Shape.center.x - m_Shape.radius;
    dst.bottom = m_Shape.center.y - m_Shape.radius;

    glPushMatrix();
    glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
    glRotatef(m_Angle, 0, 0, 1);
    glTranslatef(-m_Shape.center.x, -m_Shape.center.y, 0);
    m_pTexture->Draw(dst, src);
    glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
    return utils::IsOverlapping(rect, m_Shape);
}

void PowerUp::SetRadius(float radius)
{
    m_Shape.radius = radius;
}
