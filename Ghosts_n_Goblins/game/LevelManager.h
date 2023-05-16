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

    std::vector<GameObject*>& GetColliders();
    std::vector<GameObject*>& GetTombstones();
    std::vector<GameObject*>& GetWaters();

    Level* GetLevel() const;
    GameObject* GetDoor();
    Platform* GetPlatform() const;
    GameObject* GetKillZone() const;

    void DrawColliders() const;
    void DrawForeGround() const;
    void DrawKillZone() const;
    void DrawLevel() const;
    void DrawPlatform() const;
    void DrawTombstones() const;
    void DrawWaters() const;
    void DrawDoor() const;

    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    virtual void Reset(bool fromCheckpoint = false) override;
    bool CheckpointReached();
    bool IsBossFight() const;
    bool StageCleared() const;
    bool EndReached();

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    void InitColliders(bool fromCheckpoint);
    void InitLadders();
    void InitTombstones();
    void InitWaters();
    void InitDoor();
    void InitKillZone();

public:
    static float GetHillHeight();
    static float GetGroundHeight();
private:
    std::vector<GameObject*> m_Colliders;
    std::vector<GameObject*> m_Tombstones;
    std::vector<GameObject*> m_Waters;

    GameObject* m_pForeground;
    GameObject* m_pKillZone;
    Level* m_pLevel;
    Platform* m_pPlatform;
    GameObject* m_pDoor;
    bool m_CheckpointReached;
private:
    static float s_HillHeight;
    static float s_GroundHeight;
};
