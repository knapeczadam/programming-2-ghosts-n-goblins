#pragma once

#include "Game.h"
#include "IManager.h"

#include <vector>

class GameObject;
class Player;

class PlayerManager final : public IManager
{
public:
    explicit PlayerManager(GameController* pGameController);
    virtual ~PlayerManager() override;
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager(PlayerManager&&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;
    PlayerManager& operator=(PlayerManager&&) = delete;

    std::vector<GameObject*>& GetThrowables();
    Player* GetPlayer() const;

    virtual void Update(float elapsedSec) override;
    virtual void Reset(bool fromCheckpoint = false) override;
    
    void DrawPlayer() const;
    void DrawThrowables() const;
    void UpdateColliders();
    void LateUpdate(float elapsedSec);

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    Player* m_pPlayer;
    const Point2f m_SpawnPos;
    const Point2f m_CheckpointPos;
    std::vector<GameObject*> m_Throwables;
    int m_PrevLives;
    int m_PrevScore;
    Game::Label m_PrevWeapon;
};
