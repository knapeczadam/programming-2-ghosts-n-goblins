#pragma once
#include "IManager.h"

#include <vector>

class GameObject;

class FlyingKnightSpawner;
class WoodyPigSpawner;
class ZombieSpawner;

class EnemyManager final : public IManager
{
public:
    explicit EnemyManager(GameController* pGameController);
    virtual ~EnemyManager() override;
    EnemyManager(const EnemyManager& other) = delete;
    EnemyManager(EnemyManager&& other) noexcept = delete;
    EnemyManager& operator=(const EnemyManager& other) = delete;
    EnemyManager& operator=(EnemyManager&& other) noexcept = delete;
    
    virtual void Reset(bool fromCheckpoint = false) override;
    void DrawEnemies() const;
    void DrawThrowables() const;
    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    void SpawnEnemies();

    std::vector<GameObject*>& GetEnemies();
    std::vector<GameObject*>& GetThrowables();
    std::vector<GameObject*>& GetFlyingKnights();
    std::vector<GameObject*>& GetWoodyPigs();
    std::vector<GameObject*>& GetZombies();

protected:
    virtual void Initialize() override;

private:
    void InitCrows();
    void InitFlyingKnights();
    void InitGreenMonsters();
    void InitMagician();
    void InitRedArremer();
    void InitUnicorn();
    void InitWoodyPigs();
    void InitZombies();

    void InitSpawners();
private:
    std::vector<GameObject*> m_Enemies;
    std::vector<GameObject*> m_Throwables;
    std::vector<GameObject*> m_FlyingKnights;
    std::vector<GameObject*> m_WoodyPigs;
    std::vector<GameObject*> m_Zombies;

    FlyingKnightSpawner* m_pFlyingKnightSpawner;
    WoodyPigSpawner* m_pWoodyPigSpawner;
    ZombieSpawner* m_pZombieSpawner;
};
