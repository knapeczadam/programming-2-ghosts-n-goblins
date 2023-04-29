#pragma once

class SoundManager final
{
public:
    SoundManager() = default;
    ~SoundManager() = default;
    SoundManager(const SoundManager& other) = delete;
    SoundManager(SoundManager&& other) noexcept = delete;
    SoundManager& operator=(const SoundManager& other) = delete;
    SoundManager& operator=(SoundManager&& other) noexcept = delete;
};
