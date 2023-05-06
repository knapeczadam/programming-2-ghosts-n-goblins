#pragma once
#include <vector>

#include "game/Game.h"

class GameController;
class GameObject;

class FXManager final
{
public:
    explicit FXManager(GameController* pGameController);
    ~FXManager() = default;
    FXManager(const FXManager& other) = delete;
    FXManager(FXManager&& other) noexcept = delete;
    FXManager& operator=(const FXManager& other) = delete;
    FXManager& operator=(FXManager&& other) noexcept = delete;

    void PlayEffect(Game::Label label, const Point2f& contactPoint, bool flipped);
private:
    GameController* m_pGameController;
};
