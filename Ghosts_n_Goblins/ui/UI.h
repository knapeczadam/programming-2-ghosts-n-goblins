﻿#pragma once
#include "game/Game.h"

class Sprite;

class UI : public ITimer
{
public:
    enum class Color
    {
        WHITE_TAN = 0,
        SKY_BLUE = 1,
        DARK_TAN = 2
    };
    
    explicit UI(Game::Label label, GameController* pGameController);
    virtual ~UI() override = default;
    UI(const UI& other) = delete;
    UI(UI&& other) noexcept = delete;
    UI& operator=(const UI& other) = delete;
    UI& operator=(UI&& other) noexcept = delete;

    virtual void Draw() const;
    virtual void Reset() const;
    virtual void Update(float elapsedSec);
    virtual bool IsActive() const final;
    virtual bool IsVisible() const final;
    
    virtual void DrawPlayerScore() const final;
    virtual void DrawHighScore() const final;
    virtual void DrawTextBottomRow() const final;
    virtual void DrawTextDeposit() const final;
    virtual void DrawTextGameOver() const final;
    virtual void DrawTextTitle() const final;
    virtual void DrawTextTopRow() const final;

protected:
    virtual void DrawNumber(Point2f& pos, int number, Color color) const final;

protected:
    Game::Label m_Label;
    GameController* m_pGameController;
    bool m_Active;
    bool m_Visible;
    bool m_Blinking;
    float m_BlinkingTime;
private:
    Sprite* m_pNumbers;
    Sprite* m_pTextBottomRow;
    Sprite* m_pTextDeposit;
    Sprite* m_pTextGameOver;
    Sprite* m_pTextTitle;
    Sprite* m_pTextTopRow;
};
