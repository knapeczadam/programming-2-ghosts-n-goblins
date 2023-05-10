#pragma once
#include <vector>

#include "IManager.h"
class GameObject;
class Player;

class PlayerManager final : public IManager
{
public:
    explicit PlayerManager(GameController* pGameController);
    virtual ~PlayerManager() override;
    PlayerManager(const PlayerManager&) = delete;
    PlayerManager& operator=(const PlayerManager&) = delete;
    PlayerManager(PlayerManager&&) = delete;
    PlayerManager& operator=(PlayerManager&&) = delete;

    std::vector<GameObject*>& GetThrowables();
    Player* GetPlayer() const;

    virtual void Reset() override;
    void DrawPlayer() const;
    void DrawThrowables() const;
    void Update(float elapsedSec);
    void LateUpdate(float elapsedSec);
    
protected:
    virtual void Initialize() override;

private:
    Player* m_pPlayer;
    std::vector<GameObject*> m_Throwables;
};
