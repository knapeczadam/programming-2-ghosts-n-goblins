#pragma once
#include <queue>

#include "Game.h"
#include "IManager.h"

class CutsceneManager final : public IManager
{
public:
    explicit CutsceneManager(GameController* gameController);
    virtual ~CutsceneManager() override = default;
    CutsceneManager(const CutsceneManager& other) = delete;
    CutsceneManager(CutsceneManager&& other) noexcept = delete;
    CutsceneManager& operator=(const CutsceneManager& other) = delete;
    CutsceneManager& operator=(CutsceneManager&& other) noexcept = delete;

    void DrawIntro() const;
    void Update(float elapsedSec);
    virtual void Reset() override;
    Game::Label GetState() const;

protected:
    virtual void Initialize() override;
private:
    std::queue<std::pair<Game::Label, float>> m_Intervals;
    Game::Label m_State;
};
