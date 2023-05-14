#include "pch.h"
#include "Sprite.h"

#include "Texture.h"
#include "utils.h"
#include "game/Macros.h"

#include <cmath>
#include <numeric>

Sprite::Sprite(Texture* pTexture)
    : m_pTexture{pTexture}
      , m_LeftOffsetPx{0.0f}
      , m_TopOffsetPx{0.0f}
      , m_LeftOffsetCols{0}
      , m_TopOffsetRows{0}
      , m_Width{pTexture->GetWidth()}
      , m_Height{pTexture->GetHeight()}
      , m_Rows{0}
      , m_Cols{0}
      , m_SubRows{0}
      , m_SubCols{0}
      , m_CurrRows{0}
      , m_CurrCols{0}
      , m_FramesPerSec{0}
      , m_FrameTime{0.0f}
      , m_Scale{0.0f}
      , m_AccuSec{0.0f}
      , m_CurrFrame{0}
      , m_SrcRect{0.0f, 0.0f, 0.0f, 0.0f}
      , m_DstRect{0.0f, 0.0f, 0.0f, 0.0f}
      , m_OriginalClipWidth{0.0f}
      , m_OriginalClipHeight{0.0f}
      , m_CurrClipWidth{0.0f}
      , m_CurrClipHeight{0.0f}
      , m_ColliderWidth{0.0f}
      , m_ColliderHeight{0.0f}
      , m_ColliderHorizontalOffset{0.0f}
      , m_ColliderVerticalOffset{0.0f}
        , m_IterCount{0}
{
}

void Sprite::Init()
{
    CalculateFrameTime();
    SetCurrRowsCols();
    InitSourceRect();
    InitDestinationRect();
}

void Sprite::Draw() const
{
    m_pTexture->Draw(m_DstRect, m_SrcRect);
#if DEBUG_SPRITE
    utils::SetColor(Color4f{1, 1, 1, 1});
    utils::DrawRect(m_DstRect);
#endif
}

void Sprite::Update(float elapsedSec)
{
    // If the sprite is static, no need to update
    if (std::isinf(m_FrameTime))
    {
        UpdateDestinationRect();
        return;
    }
    // If there is only one frame, no need to update
    if (m_CurrRows * m_CurrCols == 1)
    {
        UpdateDestinationRect();
        m_CurrFrame = 0;
        return;
    }
    m_AccuSec += elapsedSec;
    if (m_AccuSec > m_FrameTime)
    {
        ++m_CurrFrame %= (m_CurrRows * m_CurrCols);
        if (m_CurrFrame == 0)
        {
            ++m_IterCount;
        }
        m_AccuSec -= m_FrameTime;
        UpdateSourceRect();
    }
    UpdateDestinationRect();
}

void Sprite::SetCurrRowsCols()
{
    if (m_SubRows == 0 or m_SubCols == 0)
    {
        m_CurrRows = m_Rows;
        m_CurrCols = m_Cols;
    }
    else
    {
        m_CurrRows = m_SubRows;
        m_CurrCols = m_SubCols;
    }
}

void Sprite::CalculateFrameTime()
{
    if (m_FramesPerSec == 0.0f)
    {
        m_FrameTime = std::numeric_limits<float>::infinity();
        return;
    }
    m_FrameTime = 1.0f / m_FramesPerSec;
}

void Sprite::InitSourceRect()
{
    if (m_CurrClipWidth > 0.0f and m_CurrClipHeight > 0.0f)
    {
        m_SrcRect.width = m_CurrClipWidth;
        m_SrcRect.height = m_CurrClipHeight;
    }
    else
    {
        m_SrcRect.width = m_Width / m_Cols;
        m_SrcRect.height = m_Height / m_Rows;

        m_OriginalClipWidth = m_SrcRect.width;
        m_OriginalClipHeight = m_SrcRect.height;

        m_CurrClipWidth = m_SrcRect.width;
        m_CurrClipHeight = m_SrcRect.height;
    }
}

void Sprite::UpdateSourceRect()
{
    m_SrcRect.width = m_CurrClipWidth;
    m_SrcRect.height = m_CurrClipHeight;
    m_SrcRect.left = m_LeftOffsetPx + m_LeftOffsetCols * m_CurrClipWidth + m_CurrFrame % m_CurrCols * m_CurrClipWidth;
    m_SrcRect.bottom = m_TopOffsetPx + m_TopOffsetRows * m_CurrClipHeight + (m_CurrFrame / m_CurrCols + 1) *
        m_CurrClipHeight;
}

void Sprite::InitDestinationRect()
{
    m_DstRect.width = m_SrcRect.width * m_Scale;
    m_DstRect.height = m_SrcRect.height * m_Scale;
}

void Sprite::UpdateDestinationRect()
{
    m_DstRect.width = m_SrcRect.width * m_Scale;
    m_DstRect.height = m_SrcRect.height * m_Scale;
}

void Sprite::DrawFlipped() const
{
    glPushMatrix();
    glTranslatef(m_DstRect.left, m_DstRect.bottom, 0);
    glTranslatef(m_DstRect.width / 2, m_DstRect.height / 2, 0);
    glScalef(-1, 1, 1);
    glTranslatef(-m_DstRect.width / 2, -m_DstRect.height / 2, 0);
    glTranslatef(-m_DstRect.left, -m_DstRect.bottom, 0);
    m_pTexture->Draw(m_DstRect, m_SrcRect);
#if DEBUG_SPRITE
    utils::SetColor(Color4f{1, 1, 1, 1});
    utils::DrawRect(m_DstRect);
#endif
    glPopMatrix();
}

void Sprite::ResetOriginalClipSize()
{
    m_CurrClipWidth = m_OriginalClipWidth;
    m_CurrClipHeight = m_OriginalClipHeight;
}

void Sprite::ResetCurrFrame()
{
    m_CurrFrame = 0;
}

float Sprite::GetLeftOffsetPx() const
{
    return m_LeftOffsetPx;
}

void Sprite::SetLeftOffsetPx(float left)
{
    m_LeftOffsetPx = left;
}

float Sprite::GetTopOffsetPx() const
{
    return m_TopOffsetPx;
}

void Sprite::SetTopOffsetPx(float top)
{
    m_TopOffsetPx = top;
}

int Sprite::GetLeftOffsetCols() const
{
    return m_LeftOffsetCols;
}

void Sprite::SetLeftOffsetCols(int left)
{
    m_LeftOffsetCols = left;
}

int Sprite::GetTopOffsetRows() const
{
    return m_TopOffsetRows;
}

void Sprite::SetTopOffsetRows(int top)
{
    m_TopOffsetRows = top;
}

float Sprite::GetWidth() const
{
    return m_Width;
}

void Sprite::SetWidth(float width)
{
    m_Width = width;
}

float Sprite::GetHeight() const
{
    return m_Height;
}

void Sprite::SetHeight(float height)
{
    m_Height = height;
}

int Sprite::GetRows() const
{
    return m_Rows;
}

void Sprite::SetRows(int rows)
{
    m_Rows = rows;
}

int Sprite::GetCols() const
{
    return m_Cols;
}

void Sprite::SetCols(int cols)
{
    m_Cols = cols;
}

int Sprite::GetSubRows() const
{
    return m_SubRows;
}

void Sprite::SetSubRows(int subRows)
{
    m_SubRows = subRows;
}

int Sprite::GetSubCols() const
{
    return m_SubCols;
}

void Sprite::SetSubCols(int subCols)
{
    m_SubCols = subCols;
}


float Sprite::GetFramesPerSec() const
{
    return m_FramesPerSec;
}

void Sprite::SetFramesPerSec(float framesPerSec)
{
    m_FramesPerSec = framesPerSec;
}

float Sprite::GetScale() const
{
    return m_Scale;
}

void Sprite::SetScale(float scale)
{
    m_Scale = scale;
}

Point2f Sprite::GetPosition() const
{
    Point2f pos;
    pos.x = m_DstRect.left;
    pos.y = m_DstRect.bottom;
    return pos;
}

void Sprite::SetPosition(const Point2f& pos)
{
    m_DstRect.left = pos.x;
    m_DstRect.bottom = pos.y;
}

float Sprite::GetClipWidth() const
{
    return m_CurrClipWidth;
}

float Sprite::GetScaledClipWidth() const
{
    return m_CurrClipWidth * m_Scale;
}

void Sprite::SetClipWidth(float clipWidth)
{
    m_CurrClipWidth = clipWidth;
}

float Sprite::GetClipHeight() const
{
    return m_CurrClipHeight;
}

float Sprite::GetScaledClipHeight() const
{
    return m_CurrClipHeight * m_Scale;
}

void Sprite::SetClipHeight(float clipHeight)
{
    m_CurrClipHeight = clipHeight;
}

float Sprite::GetColliderWidth() const
{
    if (m_ColliderWidth == 0.0f)
    {
        return m_CurrClipWidth * m_Scale;
    }
    return m_ColliderWidth * m_Scale;
}

void Sprite::SetColliderWidth(float colliderWidth)
{
    m_ColliderWidth = colliderWidth;
}

float Sprite::GetColliderHeight() const
{
    if (m_ColliderHeight == 0.0f)
    {
        return m_CurrClipHeight * m_Scale;
    }
    return m_ColliderHeight * m_Scale;
}

void Sprite::SetColliderHeight(float colliderHeight)
{
    m_ColliderHeight = colliderHeight;
}

float Sprite::GetColliderHorizontalOffset() const
{
    return m_ColliderHorizontalOffset * m_Scale;
}

void Sprite::SetColliderHorizontalOffset(float colliderHorizontalOffset)
{
    m_ColliderHorizontalOffset = colliderHorizontalOffset;
}

float Sprite::GetColliderVerticalOffset() const
{
    return m_ColliderVerticalOffset * m_Scale;
}

void Sprite::SetColliderVerticalOffset(float colliderVerticalOffset)
{
    m_ColliderVerticalOffset = colliderVerticalOffset;
}

int Sprite::GetIterCount() const
{
    return m_IterCount;
}

void Sprite::ResetIterCount()
{
    m_IterCount = 0;
}

bool Sprite::IsLastFrame() const
{
    return m_CurrFrame == m_CurrRows * m_CurrCols - 1;
}
