#pragma once

#include <vector>

#include "game/Game.h"

class Sprite;
class TextureManager;

class SpriteFactory final
{
public:
    SpriteFactory(json data, TextureManager* pTextureManager);
    SpriteFactory(json data, TextureManager* pTextureManager, std::map<std::string, Game::Label> labels);
    ~SpriteFactory();
    SpriteFactory(const SpriteFactory& other) = delete;
    SpriteFactory(SpriteFactory&& other) noexcept = delete;
    SpriteFactory& operator=(const SpriteFactory& other) = delete;
    SpriteFactory& operator=(SpriteFactory&& other) noexcept = delete;

    Sprite* CreateSprite(Game::Label label);
    void SetLabels(const std::map<std::string, Game::Label>& labels);

private:
    std::vector<Sprite*> m_pSprites;
    json m_Data;
    TextureManager* m_pTextureManager;
    std::map<std::string, Game::Label> m_Labels;
};
