#pragma once

#include <vector>

#include "level/Platform.h"

class Level;
class Platform;
class SpriteFactory;
class SoundManager;
class Player;
class GameObject;

class GameController final
{
public:
    explicit GameController(
        const Rectf& viewPort,
        SpriteFactory* pSpriteFactory,
        SoundManager* pSoundManager,
        std::vector<GameObject*>& playerThrowables,
        std::vector<GameObject*>& enemyThrowables);
    
    ~GameController() = default;
    GameController(const GameController& other) = delete;
    GameController(GameController&& other) noexcept = delete;
    GameController& operator=(const GameController& other) = delete;
    GameController& operator=(GameController&& other) noexcept = delete;

    Rectf m_ViewPort;
    SpriteFactory* m_pSpriteFactory;
    SoundManager* m_pSoundManager;
    std::vector<GameObject*>& m_PlayerThrowables;
    std::vector<GameObject*>& m_EnemyThrowables;
    Player* m_pPlayer;
    Level* m_pLevel;
    Platform* m_pPlatform;
};
