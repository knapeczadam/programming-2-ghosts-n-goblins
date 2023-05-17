#pragma once
#include "IManager.h"

#include <vector>

class GameObject;

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

    std::vector<GameObject*>& GetCrows();
    std::vector<GameObject*>& GetEnemies();
    std::vector<GameObject*>& GetFlyingKnights();
    std::vector<GameObject*>& GetGreenMonsters();
    std::vector<GameObject*>& GetThrowables();
    std::vector<GameObject*>& GetWoodyPigs();
    std::vector<GameObject*>& GetZombies();
    
    GameObject* GetMagician() const;

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    void InitCrows();
    void InitFlyingKnights();
    void InitGreenMonsters();
    void InitMagician();
    void InitRedArremer();
    void InitUnicorn();
    void InitWoodyPigs();
    void InitZombies();

private:
    std::vector<GameObject*> m_Crows;
    std::vector<GameObject*> m_Enemies;
    std::vector<GameObject*> m_GreenMonsters;
    std::vector<GameObject*> m_Throwables;
    std::vector<GameObject*> m_FlyingKnights;
    std::vector<GameObject*> m_WoodyPigs;
    std::vector<GameObject*> m_Zombies;
    GameObject* m_pMagician;
};
