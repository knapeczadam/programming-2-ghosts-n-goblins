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
    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    std::vector<GameObject*>& GetCollectibles();

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;
private:
    void InitCoins();
    void InitKey();
    void InitMoneyBags();
    void InitArmor();
    void InitPot();
    void InitNecklace();
    void InitYashichi();
private:
    std::vector<GameObject*> m_Collectibles;
public:
    static Game::Label GetNextContent();
    static bool IsContentActive();
    static void ActivateContent();
    static void DeactivateContent();
    static void SetContentId(int id);
    static int GetContentId();
private:
    static Game::Label s_CurrContent;
    static int s_ContentCount;
    static int s_WeaponCount;
    static bool s_ContentActive;
    static int s_ContentId;
};
