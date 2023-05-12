#pragma once
#include "IManager.h"

#include <vector>

class GameObject;
class Level;
class Platform;

class LevelManager final : public IManager
{
public:
    explicit LevelManager(GameController* pGameController);
    virtual ~LevelManager() override;
    LevelManager(const LevelManager&) = delete;
    LevelManager(LevelManager&&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;
    LevelManager& operator=(LevelManager&&) = delete;

    std::vector<GameObject*>& GetCollisionBoxes();
    std::vector<GameObject*>& GetLadders();
    std::vector<GameObject*>& GetTombstones();
    std::vector<GameObject*>& GetWaters();

    Level* GetLevel() const;
    Platform* GetPlatform() const;
    GameObject* GetKillZone() const;

    void DrawCollisionBoxes() const;
    void DrawForeGround() const;
    void DrawKillZone() const;
    void DrawLadders() const;
    void DrawLevel() const;
    void DrawPlatform() const;
    void DrawTombstones() const;
    void DrawWaters() const;

    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    virtual void Reset(bool fromCheckpoint = false) override;
    bool CheckpointReached();

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    void InitCollisionBoxes(bool fromCheckpoint);
    void InitLadders();
    void InitTombstones();
    void InitWaters();

private:
    std::vector<GameObject*> m_CollisionBoxes;
    std::vector<GameObject*> m_Ladders;
    std::vector<GameObject*> m_Tombstones;
    std::vector<GameObject*> m_Waters;

    GameObject* m_pForeground;
    GameObject* m_pKillZone;
    Level* m_pLevel;
    Platform* m_pPlatform;
    bool m_CheckpointReached;
};
