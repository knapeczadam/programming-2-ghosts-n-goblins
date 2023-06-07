#include "pch.h"
#include "TextureManager.h"

#include "Texture.h"
#include "game/GameController.h"

#include <iostream>


TextureManager::TextureManager(GameController* pGameController)
    : IManager(pGameController)
    , m_Textures{}
    , m_pTextures{}
    , m_Path{"images/"}
{
    pGameController->m_pTextureManager = this;
    Initialize();
}

TextureManager::~TextureManager()
{
    CleanUp();
}

void TextureManager::Initialize(bool fromCheckpoint)
{
    LoadTextures();
}

void TextureManager::CleanUp()
{
    DeleteTextures();
}

void TextureManager::LoadTextures()
{
    for (const auto& texture : m_pGameController->m_Data["images"])
    {
        const std::string label{texture["label"]};
        const std::string path{texture["path"]};
        auto it = m_pGameController->m_Labels.find(label);
        if (it == m_pGameController->m_Labels.end())
        {
            std::cerr << "TextureManager::LoadTextures() - ERROR: label (" << label <<
                ") found in data.json/images is not in the label map!" << std::endl;
            std::abort();
        }
        //m_Textures.emplace(std::make_pair(m_Labels[label], new Texture{m_Path + path}));
        //m_Textures.emplace(m_Labels[label], new Texture{m_Path + path});
        Texture* pTexture = new Texture{m_Path + path};
        m_Textures[m_pGameController->m_Labels[label]] = pTexture;
        m_pTextures.push_back(pTexture);
    }
}

void TextureManager::DeleteTextures()
{
    for (const Texture* texture : m_pTextures)
    {
        delete texture;
    }
    // somehow memory leak occurs when using map instead of vector
    // C++20
    // for (auto& texture : m_Textures | std::views::values)
    // {
    //     delete texture;
    //     texture = nullptr;
    // }
    // for (const auto& texture : m_Textures)
    // {
    //     delete texture.second;
    // }
    //m_Textures.clear();
}

Texture* TextureManager::GetTexture(Game::Label label)
{
    const auto it = m_Textures.find(label);
    if (it != m_Textures.end())
    {
        return it->second;
    }
    // FALLBACK
    return m_Textures[Game::Label::D_FALLBACK];
}
