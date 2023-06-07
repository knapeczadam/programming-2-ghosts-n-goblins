#pragma once

#include "game/Game.h"
#include "game/IManager.h"

class GameController;
class GameObject;

class FXManager final : public IManager
{
public:
    explicit FXManager(GameController* pGameController);
    virtual ~FXManager() override;
    FXManager(const FXManager& other) = delete;
    FXManager(FXManager&& other) noexcept = delete;
    FXManager& operator=(const FXManager& other) = delete;
    FXManager& operator=(FXManager&& other) noexcept = delete;

    void Draw() const;
    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    std::vector<GameObject*>& GetEffects();

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

public:
    void PlayEffect(Game::Label label, const Point2f& pos, bool flipped, GameObject* other = nullptr);

private:
    std::vector<GameObject*> m_Effects;
};
