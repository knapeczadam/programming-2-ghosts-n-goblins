#pragma once
#include "game/Game.h"

class Sprite;

class UI : public ITimer
{
public:
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
    
protected:
    Game::Label m_Label;
    GameController* m_pGameController;
    bool m_Active;
    bool m_Visible;
};
