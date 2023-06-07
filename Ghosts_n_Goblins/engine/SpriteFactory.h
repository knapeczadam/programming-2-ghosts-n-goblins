#pragma once

#include <vector>

#include "game/Game.h"

class Sprite;

class SpriteFactory final
{
public:
    explicit SpriteFactory(GameController* pGameController);
    ~SpriteFactory();
    SpriteFactory(const SpriteFactory& other) = delete;
    SpriteFactory(SpriteFactory&& other) noexcept = delete;
    SpriteFactory& operator=(const SpriteFactory& other) = delete;
    SpriteFactory& operator=(SpriteFactory&& other) noexcept = delete;

    Sprite* CreateSprite(Game::Label label);

private:
    GameController* m_pGameController;
    std::vector<Sprite*> m_pSprites;
};
