﻿#pragma once
#include <vector>

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
};
