#include "pch.h"
#include "SoundManager.h"
#include <iostream>

#include "game/GameController.h"

SoundManager::SoundManager(GameController* pGameController)
    : m_pGameController{pGameController}
      , m_EffectPath{"sounds/effects/"}
      , m_StreamPath{"sounds/streams/"}
      , m_Effects{}
      , m_Streams{}
      , m_pEffects{}
      , m_pStreams{}
{
    LoadSounds();
}

SoundManager::~SoundManager()
{
    DeleteSounds();
}

void SoundManager::PlayEffect(Game::Label label) const
{
    if (GetEffect(label)->IsLoaded())
    {
        GetEffect(label)->Play(0);
    }
}

void SoundManager::PlayStream(Game::Label label, bool repeat) const
{
    if (GetStream(label)->IsLoaded())
    {
        if (SoundStream::IsPlaying()) return;
        GetStream(label)->Play(repeat);
    }
}

void SoundManager::StopStream() const
{
    SoundStream::Stop();
}

void SoundManager::StopAllEffects() const
{
    SoundEffect::StopAll();
}

void SoundManager::PauseStream() const
{
    SoundStream::Pause();
}

void SoundManager::ResumeStream() const
{
    SoundStream::Resume();
}

void SoundManager::PauseAllEffects() const
{
    SoundEffect::PauseAll();
}

void SoundManager::ResumeAllEffects() const
{
    SoundEffect::ResumeAll();
}

void SoundManager::SetStreamVolume(int volume) const
{
    SoundStream::SetVolume(volume);
}

void SoundManager::SetEffectVolume(Game::Label label, int volume) const
{
    GetEffect(label)->SetVolume(volume);
}

SoundEffect* SoundManager::GetEffect(Game::Label label) const
{
    return m_Effects.at(label);
}

SoundStream* SoundManager::GetStream(Game::Label label) const
{
    return m_Streams.at(label);
}

void SoundManager::IncreaseMasterVolume()
{
    SoundStream::SetVolume(SoundStream::GetVolume() + 1);
}

void SoundManager::DecreaseMasterVolume()
{
    SoundStream::SetVolume(SoundStream::GetVolume() - 1);
}

void SoundManager::LoadSounds()
{
    for (const auto& sound : m_pGameController->m_Data["effects"])
    {
        const std::string label{sound["label"]};
        const std::string path{sound["path"]};
        auto it = m_pGameController->m_Labels.find(label);
        if (it == m_pGameController->m_Labels.end())
        {
            std::cerr << "SoundManager::LoadSounds() - ERROR: label (" << label <<
                ") found in data.json/effects is not in the label map!" << std::endl;
            std::abort();
        }
        SoundEffect* pEffect = new SoundEffect{m_EffectPath + path};
        m_Effects[m_pGameController->m_Labels[label]] = pEffect;
        m_pEffects.push_back(pEffect);
    }
    for (const auto& sound : m_pGameController->m_Data["streams"])
    {
        const std::string label{sound["label"]};
        const std::string path{sound["path"]};
        auto it = m_pGameController->m_Labels.find(label);
        if (it == m_pGameController->m_Labels.end())
        {
            std::cerr << "SoundManager::LoadSounds() - ERROR: label (" << label <<
                ") found in data.json/streams is not in the label map!" << std::endl;
            std::abort();
        }
        SoundStream* pStream = new SoundStream{m_StreamPath + path};
        m_Streams[m_pGameController->m_Labels[label]] = pStream;
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
