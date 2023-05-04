#pragma once
#include "game/Game.h"

class Sprite;

class UI : public ITimer
{
public:
    explicit UI(Game::Label label, Sprite* pSprite, const Rectf& viewPort, SoundManager* pSoundManager);
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
    Rectf m_ViewPort;
    SoundManager* m_pSoundManager;
};
