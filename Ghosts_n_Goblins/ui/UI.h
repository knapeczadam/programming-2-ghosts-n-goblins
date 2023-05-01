#pragma once
#include "game/Game.h"

class Sprite;

class UI : public Timer
{
public:
    explicit UI(Game::Label label, Sprite* pSprite);
    virtual ~UI() override = default;
    UI(const UI& other) = delete;
    UI(UI&& other) noexcept = delete;
    UI& operator=(const UI& other) = delete;
    UI& operator=(UI&& other) noexcept = delete;

    virtual void Draw();
    virtual void Draw() const;
    virtual void Reset() const;
    virtual void Update(float elapsedSec);
protected:
    Game::Label m_Label;
    Sprite* m_pSprite;
};
