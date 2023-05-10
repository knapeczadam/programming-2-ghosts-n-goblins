#pragma once
#include "Game.h"
#include "IManager.h"

#include <queue>

class BootManager final : public IManager
{
public:
    explicit BootManager(GameController* pGameController);
    virtual ~BootManager() override = default;
    BootManager(const BootManager& other) = delete;
    BootManager(BootManager&& other) noexcept = delete;
    BootManager& operator=(const BootManager& other) = delete;
    BootManager& operator=(BootManager&& other) noexcept = delete;

    virtual void Reset() override;
    void Draw() const;
    void Update(float elapsedSec);

    Game::Label GetState() const;

protected:
    virtual void Initialize() override;
private:
    std::queue<std::pair<Game::Label, float>> m_Intervals;
    Game::Label m_State;
};
