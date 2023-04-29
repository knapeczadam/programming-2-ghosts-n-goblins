#pragma once
#include <map>
#include <string>
#include "game/Game.h"

class Texture;

class TextureManager final
{
public:
    explicit TextureManager();
    explicit TextureManager(json data);
    explicit TextureManager(json data, std::map<std::string, Game::Label> labels);
    ~TextureManager();
    TextureManager(const TextureManager& other) = delete;
    TextureManager(TextureManager&& other) noexcept = delete;
    TextureManager& operator=(const TextureManager& other) = delete;
    TextureManager& operator=(TextureManager&& other) noexcept = delete;

    void LoadTextures();
    void SetData(const json& data);
    Texture* GetTexture(Game::Label label);
    void SetTexture(Game::Label label, Texture* pTexture);
    void SetLabels(const std::map<std::string, Game::Label>& labels);

private:
    void DeleteTextures();

private:
    json m_Data;
    std::map<Game::Label, Texture*> m_Textures;
    std::map<std::string, Game::Label> m_Labels;
    std::vector<Texture*> m_pTextures;
    const std::string m_Path;
};
