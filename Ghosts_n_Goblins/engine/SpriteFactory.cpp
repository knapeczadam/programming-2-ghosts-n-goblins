#include "pch.h"
#include "SpriteFactory.h"

#include <iostream>
#include <engine/Sprite.h>

#include "TextureManager.h"

SpriteFactory::SpriteFactory(json data, TextureManager* pTextureManager)
    : m_pSprites{}
      , m_Data(std::move(data))
      , m_pTextureManager{pTextureManager}
{
}

SpriteFactory::SpriteFactory(json data, TextureManager* pTextureManager,
                             std::map<std::string, Game::Label> labels)
    : m_pSprites{}
      , m_Data(std::move(data))
      , m_pTextureManager{pTextureManager}
      , m_Labels{std::move(labels)}
{
}

SpriteFactory::~SpriteFactory()
{
    for (const Sprite* sprite : m_pSprites)
    {
        delete sprite;
    }
}

Sprite* SpriteFactory::CreateSprite(Game::Label label)
{
    Sprite* pSprite{};
    for (const auto& sprite : m_Data["sprites"])
    {
        const std::string jsonLabel{sprite["label"]};
        if (not m_Labels.contains(jsonLabel))
        {
            std::cerr << "SpriteFactory::CreateSprite() - ERROR: label (" << jsonLabel << ") found in data/json/sprites is not in the label map!" << std::endl;
            std::abort();
        }
        if (m_Labels[jsonLabel] == label)
        {
            pSprite = new Sprite{m_pTextureManager->GetTexture(label)};

            const int rows{sprite.contains("rows") ? static_cast<int>(sprite["rows"]) : 1};
            pSprite->SetRows(rows);
            const int columns{sprite.contains("columns") ? static_cast<int>(sprite["columns"]) : 1};
            pSprite->SetCols(columns);
            const int subRows{sprite.contains("sub_rows") ? static_cast<int>(sprite["sub_rows"]) : 0};
            pSprite->SetSubRows(subRows);
            const int subColumns{sprite.contains("sub_columns") ? static_cast<int>(sprite["sub_columns"]) : 0};
            pSprite->SetSubCols(subColumns);
            const int framesPerSec{
                sprite.contains("frames_per_second") ? static_cast<int>(sprite["frames_per_second"]) : 0
            };
            pSprite->SetFramesPerSec(framesPerSec);
            const float scale{sprite.contains("scale") ? static_cast<float>(sprite["scale"]) : 1.0f};
            pSprite->SetScale(scale);
            const float leftOffsetPx{
                sprite.contains("left_offset_pixel") ? static_cast<float>(sprite["left_offset_pixel"]) : 0.0f
            };
            pSprite->SetLeftOffsetPx(leftOffsetPx);
            const float topOffsetPx{
                sprite.contains("top_offset_pixel") ? static_cast<float>(sprite["top_offset_pixel"]) : 0.0f
            };
            pSprite->SetTopOffsetPx(topOffsetPx);
            const int leftOffsetCols{
                sprite.contains("left_offset_columns") ? static_cast<int>(sprite["left_offset_columns"]) : 0
            };
            pSprite->SetLeftOffsetCols(leftOffsetCols);
            const int topOffsetRows{
                sprite.contains("top_offset_rows") ? static_cast<int>(sprite["top_offset_rows"]) : 0
            };
            pSprite->SetTopOffsetRows(topOffsetRows);
            const float clipWidth{sprite.contains("clip_width") ? static_cast<float>(sprite["clip_width"]) : 0.0f};
            pSprite->SetClipWidth(clipWidth);
            const float clipHeight{sprite.contains("clip_height") ? static_cast<float>(sprite["clip_height"]) : 0.0f};
            pSprite->SetClipHeight(clipHeight);

            pSprite->Init();

            m_pSprites.push_back(pSprite);

            return pSprite;
        }
    }
    if (pSprite == nullptr)
    {
        std::cerr << "SpriteFactory::CreateSprite() - ERROR: label (" << static_cast<int>(label) << ") not found in data.json/sprites!" << std::endl;
        std::abort();
    }
    return pSprite;
}

void SpriteFactory::SetLabels(const std::map<std::string, Game::Label>& labels)
{
    m_Labels = labels;
}
