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
    virtual void Update(float elapsedSec) override;
    void UpdateColliders();
    void LateUpdate(float elapsedSec);
    std::vector<GameObject*>& GetEffects();
    void PlayEffect(Game::Label label, const Point2f& pos, bool flipped, GameObject* other = nullptr);

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;
    
private:
    std::vector<GameObject*> m_Effects;
};
