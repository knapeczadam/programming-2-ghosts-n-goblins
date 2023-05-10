#pragma once
#include <map>
#include <string>
#include "game/Game.h"
#include "game/IManager.h"

class Texture;

class TextureManager final : public IManager
{
public:
    explicit TextureManager(GameController* pGameController);
    virtual ~TextureManager() override;
    TextureManager(const TextureManager& other) = delete;
    TextureManager(TextureManager&& other) noexcept = delete;
    TextureManager& operator=(const TextureManager& other) = delete;
    TextureManager& operator=(TextureManager&& other) noexcept = delete;

    void LoadTextures();
    Texture* GetTexture(Game::Label label);

protected:
    virtual void Initialize() override;

private:
    void DeleteTextures();

private:
    std::map<Game::Label, Texture*> m_Textures;
    std::vector<Texture*> m_pTextures;
    const std::string m_Path;
};
