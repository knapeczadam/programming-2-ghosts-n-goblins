﻿#pragma once

class Texture;

class Sprite final
{
public:
    void Init();
    explicit Sprite(Texture* pTexture);
    ~Sprite() = default;
    Sprite(const Sprite& other) = delete;
    Sprite(Sprite&& other) noexcept = delete;
    Sprite& operator=(const Sprite& other) = delete;
    Sprite& operator=(Sprite&& other) noexcept = delete;

    // SPRITE RELATED FUNCTIONS
    void Draw() const;
    void Update(float elapsedSec);
    void SetCurrRowsCols();

    void SetFrameTime();
    void InitSourceRect();
    void UpdateSourceRect();
    void InitDestinationRect();
    void UpdateDestinationRect();
    void DrawFlipped() const;
    void ResetOriginalClipSize();

    // GETTERS & SETTERS
    float GetLeftOffsetPx() const;
    void SetLeftOffsetPx(float left);
    float GetTopOffsetPx() const;
    void SetTopOffsetPx(float top);
    int GetLeftOffsetCols() const;
    void SetLeftOffsetCols(int left);
    int GetTopOffsetRows() const;
    void SetTopOffsetRows(int top);
    float GetWidth() const;
    void SetWidth(float width);
    float GetHeight() const;
    void SetHeight(float height);
    int GetRows() const;
    void SetRows(int rows);
    int GetCols() const;
    void SetCols(int cols);
    int GetSubRows() const;
    void SetSubRows(int subRows);
    int GetSubCols() const;
    void SetSubCols(int subCols);
    int GetFramesPerSec() const;
    void SetFramesPerSec(int framesPerSec);
    float GetScale() const;
    void SetScale(float scale);
    Point2f GetPosition() const;
    void SetPosition(const Point2f& pos);
    float GetClipWidth() const;
    float GetScaledClipWidth() const;
    void SetClipWidth(float clipWidth);
    float GetClipHeight() const;
    float GetScaledClipHeight() const;
    void SetClipHeight(float clipHeight);
    float GetCollisionWidth() const;
    void SetCollisionWidth(float collisionWidth);
    float GetCollisionHeight() const;
    void SetCollisionHeight(float collisionHeight);
    

private:
    // SPRITE PROPERTIES
    Texture* m_pTexture;
    float m_LeftOffsetPx;
    float m_TopOffsetPx;
    int m_LeftOffsetCols;
    int m_TopOffsetRows;
    float m_Width;
    float m_Height;
    int m_Rows;
    int m_Cols;
    int m_SubRows;
    int m_SubCols;
    int m_CurrRows;
    int m_CurrCols;
    int m_FramesPerSec;
    float m_FrameTime;
    float m_Scale;

    // SPRITE RELATED DATA MEMBERS
    float m_AccuSec;
    int m_CurrFrame;
    Rectf m_SrcRect;
    Rectf m_DstRect;
    float m_OriginalClipWidth;
    float m_OriginalClipHeight;
    float m_CurrClipWidth;
    float m_CurrClipHeight;
    float m_CollisionWidth;
    float m_CollisionHeight;
};