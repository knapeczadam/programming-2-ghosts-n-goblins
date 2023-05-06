#pragma once
#include <map>
#include <string>
#include "game/Game.h"

class Texture;

class TextureManager final
{
public:
    explicit TextureManager(GameController* pGameController);
    ~TextureManager();
    TextureManager(const TextureManager& other) = delete;
    TextureManager(TextureManager&& other) noexcept = delete;
    TextureManager& operator=(const TextureManager& other) = delete;
    TextureManager& operator=(TextureManager&& other) noexcept = delete;

    void LoadTextures();
    Texture* GetTexture(Game::Label label);

private:
    void DeleteTextures();

private:
    GameController* m_pGameController;
    std::map<Game::Label, Texture*> m_Textures;
    std::vector<Texture*> m_pTextures;
    const std::string m_Path;
};
