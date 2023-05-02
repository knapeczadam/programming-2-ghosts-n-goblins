#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"
#include "game/Game.h"

class SoundManager final
{
public:
    explicit SoundManager(json data, std::map<std::string, Game::Label> labels);
    ~SoundManager();
    SoundManager(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) noexcept = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager& operator=(SoundManager&& other) noexcept = delete;

    SoundEffect* GetEffect(Game::Label label) const;
    SoundStream* GetStream(Game::Label label) const;
private:
    void LoadSounds();
    void DeleteSounds();
private:
    json m_Data;
    std::map<std::string, Game::Label> m_Labels;
    const std::string m_EffectPath;
    const std::string m_StreamPath;
    std::map<Game::Label, SoundEffect*> m_Effects;
    std::map<Game::Label, SoundStream*> m_Streams;
    std::vector<SoundEffect*> m_pEffects;
    std::vector<SoundStream*> m_pStreams;
};
