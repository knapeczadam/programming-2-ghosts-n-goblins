#include "pch.h"
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager(json data, std::map<std::string, Game::Label> labels)
    : m_Data(std::move(data))
      , m_Labels(std::move(labels))
      , m_EffectPath{"sounds/effects/"}
      , m_StreamPath{"sounds/streams/"}
{
    LoadSounds();
}

SoundManager::~SoundManager()
{
    DeleteSounds();
}

SoundEffect* SoundManager::GetEffect(Game::Label label) const
{
    return m_Effects.at(label);
}

SoundStream* SoundManager::GetStream(Game::Label label) const
{
    return m_Streams.at(label);
}

void SoundManager::LoadSounds()
{
    for (const auto& sound : m_Data["effects"])
    {
        const std::string label{sound["label"]};
        const std::string path{sound["path"]};
        auto it = m_Labels.find(label);
        if (it == m_Labels.end())
        {
            std::cerr << "SoundManager::LoadSounds() - ERROR: label (" << label <<") found in data.json/effects is not in the label map!" << std::endl;
            std::abort();
        }
        auto* pEffect = new SoundEffect{m_EffectPath + path};
        m_Effects[m_Labels[label]] = pEffect;
        m_pEffects.push_back(pEffect);
    }
    for (const auto& sound : m_Data["streams"])
    {
        const std::string label{sound["label"]};
        const std::string path{sound["path"]};
        auto it = m_Labels.find(label);
        if (it == m_Labels.end())
        {
            std::cerr << "SoundManager::LoadSounds() - ERROR: label (" << label <<") found in data.json/streams is not in the label map!" << std::endl;
            std::abort();
        }
        auto* pStream = new SoundStream{m_StreamPath + path};
        m_Streams[m_Labels[label]] = pStream;
        m_pStreams.push_back(pStream);
    }
}

void SoundManager::DeleteSounds()
{
    for (const SoundEffect* sound : m_pEffects)
    {
        delete sound;
    }
    for (const SoundStream* sound : m_pStreams)
    {
        delete sound;
    }
}
