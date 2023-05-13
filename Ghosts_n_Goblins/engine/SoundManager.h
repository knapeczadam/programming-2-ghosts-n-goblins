#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"
#include "game/Game.h"
#include "game/IManager.h"

class SoundManager final : public IManager
{
public:
    explicit SoundManager(GameController* pGameController);
    virtual ~SoundManager() override;
    SoundManager(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) noexcept = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager& operator=(SoundManager&& other) noexcept = delete;


public:
    void PlayEffect(Game::Label label) const;
    void PlayStream(Game::Label label, bool repeat) const;
    void StopStream() const;
    void StopAllEffects() const;
    void PauseStream() const;
    void ResumeStream() const;
    void PauseAllEffects() const;
    void ResumeAllEffects() const;
    void SetStreamVolume(int volume) const;
    void IncreaseStreamMasterVolume();
    void DecreaseStreamMasterVolume();
    void IncreaseEffectMasterVolume() const;
    void DecreaseEffectMasterVolume() const;
    void SetEffectVolume(Game::Label label, int volume) const;

    SoundEffect* GetEffect(Game::Label label) const;
    SoundStream* GetStream(Game::Label label) const;
    
protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    void LoadSounds();
    void DeleteSounds();

private:
    const std::string m_EffectPath;
    const std::string m_StreamPath;
    std::map<Game::Label, SoundEffect*> m_Effects;
    std::map<Game::Label, SoundStream*> m_Streams;
    std::vector<SoundEffect*> m_pEffects;
    std::vector<SoundStream*> m_pStreams;
};
