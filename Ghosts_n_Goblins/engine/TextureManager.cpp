#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

#include <fstream>
#include <iostream>
#include <ranges>

TextureManager::TextureManager()
    : m_Data{}
      , m_Textures{}
      , m_Path{"images/"}
{
}

TextureManager::TextureManager(json data)
    : m_Data(std::move(data)) // doesn't work with brace initialization
      , m_Textures{}
      , m_Path{"images/"}
{
    LoadTextures();
}

TextureManager::TextureManager(json data, std::map<std::string, Game::Label> labels)
    : m_Data(std::move(data)) // doesn't work with brace initialization
      , m_Textures{}
      , m_Labels{std::move(labels)}
      , m_Path{"images/"}
{
    LoadTextures();
}

TextureManager::~TextureManager()
{
    DeleteTextures();
}

void TextureManager::LoadTextures()
{
    for (const auto& texture : m_Data["images"])
    {
        const std::string label{texture["label"]};
        const std::string path{texture["path"]};
        auto it = m_Labels.find(label);
        if (it == m_Labels.end())
        {
            std::cerr << "TextureManager::LoadTextures() - ERROR: label not found: " << label << std::endl;
            std::abort();
        }
        //m_Textures.emplace(std::make_pair(m_Labels[label], new Texture{m_Path + path}));
        //m_Textures.emplace(m_Labels[label], new Texture{m_Path + path});
        auto* pTexture = new Texture{m_Path + path};
        m_Textures[m_Labels[label]] = pTexture;
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

void TextureManager::SetData(const json& data)
{
    m_Data = data;
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

void TextureManager::SetTexture(Game::Label label, Texture* pTexture)
{
    m_Textures[label] = pTexture;
}

void TextureManager::SetLabels(const std::map<std::string, Game::Label>& labels)
{
    m_Labels = labels;
}
