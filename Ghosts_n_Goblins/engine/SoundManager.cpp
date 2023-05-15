#include "pch.h"
#include "SoundManager.h"

#include <iostream>
#include <ranges>

#include "game/GameController.h"

SoundManager::SoundManager(GameController* pGameController)
    : IManager(pGameController)
      , m_EffectPath{"sounds/effects/"}
      , m_StreamPath{"sounds/streams/"}
      , m_Effects{}
      , m_Streams{}
      , m_pEffects{}
      , m_pStreams{}
        , m_CurrentStream{Game::Label::S_NONE}
{
    m_pGameController->m_pSoundManager = this;
    Initialize();
}

SoundManager::~SoundManager()
{
    CleanUp();
}

void SoundManager::Initialize(bool fromCheckpoint)
{
    LoadSounds();
    SetMasterVolume(1);
}

void SoundManager::CleanUp()
{
    DeleteSounds();
}

bool SoundManager::PlayEffect(Game::Label label) const
{
    if (GetEffect(label)->IsLoaded())
    {
        return GetEffect(label)->Play(0);
    }
    return false;
}

bool SoundManager::PlayStream(Game::Label label, bool repeat)
{
    if (GetStream(label)->IsLoaded())
    {
        if (label != m_CurrentStream)
        {
            if (SoundStream::IsPlaying())
            {
                StopStream();
            }
            m_CurrentStream = label;
            return GetStream(label)->Play(repeat);
        }
    }
    return false;
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

void SoundManager::IncreaseEffectMasterVolume() const
{
    for (const auto& effect : m_Effects | std::views::values)
    {
        effect->SetVolume(effect->GetVolume() + 1);
    }
}

void SoundManager::DecreaseEffectMasterVolume() const
{
    for (const auto& effect : m_Effects | std::views::values)
    {
        effect->SetVolume(effect->GetVolume() - 1);
    }
}

void SoundManager::SetMasterVolume(int volume) const
{
    SoundStream::SetVolume(volume);
    for (const auto& effect : m_Effects | std::views::values)
    {
        effect->SetVolume(volume);
    }
}

void SoundManager::SetEffectVolume(Game::Label label, int volume) const
{
    GetEffect(label)->SetVolume(volume);
}

int SoundManager::GetVolume() const
{
    return SoundStream::GetVolume();
}

SoundEffect* SoundManager::GetEffect(Game::Label label) const
{
    return m_Effects.at(label);
}

SoundStream* SoundManager::GetStream(Game::Label label) const
{
    return m_Streams.at(label);
}

void SoundManager::IncreaseStreamMasterVolume()
{
    SoundStream::SetVolume(SoundStream::GetVolume() + 1);
}

void SoundManager::DecreaseStreamMasterVolume()
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
