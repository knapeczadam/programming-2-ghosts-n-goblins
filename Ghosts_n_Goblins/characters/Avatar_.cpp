// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Avatar.h"
#include "utils.h"
#include <iostream>
#include "level/Level.h"
#include "Texture.h"
#include "engine/Macros.h"
#include "engine/Sprite.h"

Avatar::Avatar()
    : m_Shape{50.0f, 280.0f, 36.0f, 97.0f}
      , m_HorSpeed{200.0f}
      , m_JumpSpeed{800.0f}
      , m_Velocity{0.f, 0.f}
      , m_Acceleration{0, -981.0f}
      , m_ActionState{ActionState::moving}
      , m_AccuTransformSec{}
      , m_MaxTransformSec{1.0f}
      , m_MaxPower{3}
      , m_Power{}
      , m_pSpritesTexture{new Texture{"images/minigame/AvatarSheet.png"}}
      , m_ClipHeight{97.0f}
      , m_ClipWidth{72.0f}
      , m_NrOfFrames{10}
      , m_NrFramesPerSec{10}
      , m_AnimTime{}
      , m_AnimFrame{}
      , m_IsFlipped{}
      , m_pSprite{}
{
    m_Shape.width = m_ClipWidth;
}

Avatar::Avatar(Texture* pTexture)
    : m_Shape{50.0f, 280.0f, 36.0f, 97.0f}
      , m_HorSpeed{200.0f}
      , m_JumpSpeed{800.0f}
      , m_Velocity{0.f, 0.f}
      , m_Acceleration{0, -981.0f}
      , m_ActionState{ActionState::moving}
      , m_AccuTransformSec{}
      , m_MaxTransformSec{1.0f}
      , m_MaxPower{3}
      , m_Power{}
      , m_pSpritesTexture{pTexture}
      , m_ClipHeight{97.0f}
      , m_ClipWidth{72.0f}
      , m_NrOfFrames{10}
      , m_NrFramesPerSec{10}
      , m_AnimTime{}
      , m_AnimFrame{}
      , m_IsFlipped{}
      , m_pSprite{}
{
    m_Shape.width = m_ClipWidth;
}

Avatar::Avatar(Sprite* pSprite)
    : m_Shape{50.0f, 280.0f, 36.0f, 97.0f}
      , m_HorSpeed{200.0f}
      , m_JumpSpeed{800.0f}
      , m_Velocity{0.f, 0.f}
      , m_Acceleration{0, -981.0f}
      , m_ActionState{ActionState::moving}
      , m_AccuTransformSec{}
      , m_MaxTransformSec{1.0f}
      , m_MaxPower{3}
      , m_Power{}
      , m_pSpritesTexture{}
      , m_ClipHeight{pSprite->GetClipHeight()}
      , m_ClipWidth{pSprite->GetClipWidth()}
      , m_NrOfFrames{pSprite->GetRows() * pSprite->GetCols()}
      , m_NrFramesPerSec{pSprite->GetFramesPerSec()}
      , m_AnimTime{}
      , m_AnimFrame{}
      , m_IsFlipped{}
      , m_pSprite{pSprite}
{
    m_Shape.width = m_ClipWidth;
}


Avatar::~Avatar()
{
    //delete m_pSpritesTexture;
}


void Avatar::MoveHorizontal(const Uint8* pState, float elapsedSec)
{
    if (pState[SDL_SCANCODE_LEFT])
    {
        m_Velocity.x = -m_HorSpeed;
        m_IsFlipped = true;
    }
    else if (pState[SDL_SCANCODE_RIGHT])
    {
        m_Velocity.x = m_HorSpeed;
        m_IsFlipped = false;
    }
    else
    {
        m_Velocity.x = 0;
    }
}

void Avatar::MoveVertical(const Uint8* pState, float elapsedSec)
{
    if (pState[SDL_SCANCODE_UP])
    {
        m_Velocity.y = m_JumpSpeed;
    }
    else
    {
        m_Velocity.y = 0;
    }
}

void Avatar::ApplyGravity(float elapsedSec)
{
    m_Velocity += m_Acceleration * elapsedSec;
}

void Avatar::MoveAvatar(float elapsedSec, const Uint8* pState)
{
    MoveHorizontal(pState, elapsedSec);
    MoveVertical(pState, elapsedSec);
}

void Avatar::Update(float elapsedSec, const Level& level)
{
    m_pSprite->Update(elapsedSec);
    //UpdateAnimation(elapsedSec);

    switch (m_ActionState)
    {
    case ActionState::moving:
    case ActionState::waiting:
        UpdatePosition(elapsedSec, level);
        break;
    case ActionState::transforming:
        Transform(elapsedSec);
        break;
    }
    level.HandleCollision(m_Shape, m_Velocity);
}

void Avatar::UpdateAnimation(float elapsedSec)
{
    m_AnimTime += elapsedSec;
    if (m_AnimTime >= 1.0f / m_NrFramesPerSec)
    {
        m_AnimFrame = (m_AnimFrame + 1) % m_NrOfFrames;
        m_AnimTime = 0;
    }
}

void Avatar::UpdatePosition(float elapsedSec, const Level& level)
{
    if (level.IsOnGround(m_Shape, m_Velocity))
    {
        const Uint8* pState{SDL_GetKeyboardState(nullptr)};
        MoveAvatar(elapsedSec, pState);
    }
    UpdateState();

    ApplyGravity(elapsedSec);

    m_Shape.left += m_Velocity.x * elapsedSec;
    m_Shape.bottom += m_Velocity.y * elapsedSec;

    CheckForBoundaries(level.GetBoundaries());
}

void Avatar::UpdateState()
{
    if (m_Velocity == Vector2f{})
    {
        m_ActionState = ActionState::waiting;
    }
    else
    {
        m_ActionState = ActionState::moving;
    }
}

void Avatar::DrawRect() const
{
    SetStateColor();
    utils::FillRect(m_Shape);
    DrawPower();
}

void Avatar::Draw() const
{
    //m_pSprite->Draw();
    DrawSprite();
}

void Avatar::DrawSprite() const
{
    Rectf src;
    src.width = m_ClipWidth;
    src.height = m_ClipHeight;
    src.left = m_AnimFrame * m_ClipWidth;
    src.bottom = 3 * m_ClipHeight * m_Power;

    switch (m_ActionState)
    {
    case ActionState::waiting:
        src.bottom += m_ClipHeight;
        //m_pSprite->SetSpriteSheetHeight(m_ClipHeight);
        m_pSprite->SetSpriteSheetTop(0 + 3 * m_ClipHeight * m_Power);
        break;
    case ActionState::moving:
        src.bottom += 2 * m_ClipHeight;
        m_pSprite->SetSpriteSheetTop(m_ClipHeight +  3 * m_ClipHeight* m_Power);
        break;
    case ActionState::transforming:
        src.bottom += 3 * m_ClipHeight;
        m_pSprite->SetSpriteSheetTop(2 * m_ClipHeight + 3 * m_ClipHeight * m_Power);
        break;
    }

    Rectf dst;
    dst.width = src.width;
    dst.height = src.height;
    dst.left = m_Shape.left; // pos.x
    dst.bottom = m_Shape.bottom; // pos.y
    
    //m_pSprite->SetSrcRect(src);
    // m_pSprite->SetDstRect(dst);
    m_pSprite->SetPosition(Point2f{dst.left, dst.bottom});
    if (m_IsFlipped)
    {
        m_pSprite->Flip();
        // FlipSrpite(dst, src);
    }
    else
    {
        //m_pSpritesTexture->Draw(dst, src);
        m_pSprite->Draw();
    }
#if DEBUG_SPRITE_BOUNDARIES
    utils::DrawRect(dst);
#endif
}

void Avatar::SetStateColor() const
{
    switch (m_ActionState)
    {
    case ActionState::moving:
        utils::SetColor(Color4f{1.0f, 0, 0, 1.0f});
        break;
    case ActionState::transforming:
        utils::SetColor(Color4f{0, 0, 1.0f, 1.0f});
        break;
    case ActionState::waiting:
        utils::SetColor(Color4f{1.0f, 1.0f, 0, 1.0f});
        break;
    }
}

void Avatar::CheckForBoundaries(const Rectf& boundaries)
{
    if (m_Shape.left < boundaries.left)
    {
        m_Shape.left = boundaries.left;
    }
    else if (m_Shape.left + m_Shape.width > boundaries.left + boundaries.width)
    {
        m_Shape.left = boundaries.left + boundaries.width - m_Shape.width;
    }
}

void Avatar::FlipSrpite(const Rectf& dst, const Rectf& src) const
{
    glPushMatrix();
    glTranslatef(dst.left, dst.bottom, 0);
    glTranslatef(dst.width / 2, dst.height / 2, 0);
    glScalef(-1, 1, 1);
    glTranslatef(-dst.width / 2, -dst.height / 2, 0);
    glTranslatef(-dst.left, -dst.bottom, 0);
    m_pSpritesTexture->Draw(dst, src);
    glPopMatrix();
}


/*
Tells the avatar that it hit a power-up.
 */
void Avatar::PowerUpHit()
{
    m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
    return m_Shape;
}

void Avatar::Transform(float elapsedSec)
{
    m_AccuTransformSec += elapsedSec;
    if (m_AccuTransformSec >= m_MaxTransformSec)
    {
        IncreasePower();
        m_AccuTransformSec = 0;
        m_ActionState = ActionState::moving;
    }
}

void Avatar::IncreasePower()
{
    if (m_Power < m_MaxPower)
    {
        ++m_Power;
    }
}

void Avatar::DrawPower() const
{
    const float size{5.0f};
    const float offset{size};
    utils::SetColor(Color4f{});
    for (int i{}; i < m_Power; ++i)
    {
        utils::FillRect(Rectf{m_Shape.left + offset + (i * 2 * offset), m_Shape.bottom + offset, size, size});
    }
}
