#pragma once
#include <vector>

#include "Game.h"
#include "IManager.h"

class GameObject;

class CollectibleManager final : public IManager
{
public:
    explicit CollectibleManager(GameController* pGameController);
    virtual ~CollectibleManager() override;
    CollectibleManager(const CollectibleManager&) = delete;
    CollectibleManager(CollectibleManager&&) = delete;
    CollectibleManager& operator=(const CollectibleManager&) = delete;
    CollectibleManager& operator=(CollectibleManager&&) = delete;

    void Draw() const;
    virtual void Update(float elapsedSec) override;
    void UpdateColliders();
    virtual void Reset(bool fromCheckpoint = false) override;
    void LateUpdate(float elapsedSec);
    std::vector<GameObject*>& GetCollectibles();

    Game::Label GetNextContent();
    bool IsContentActive();
    void ActivateContent();
    void DeactivateContent();

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;
    void UpdatePot();

private:
    void InitCoins();
    void InitKey();
    void InitMoneyBags();
    void InitArmor();
    void InitPot();
    void InitNecklace();
    void InitDoll();
    void InitKing();
    void InitYashichi();
    void InitWeapons();
    void AssignPot(GameObject* pEnemy);

private:
    std::vector<GameObject*> m_Collectibles;
    GameObject* m_pPot;
    Game::Label m_CurrContent;
    int m_ContentCount;
    int m_WeaponCount;
    bool m_ContentActive;
};
