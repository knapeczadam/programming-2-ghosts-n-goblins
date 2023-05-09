#pragma once

#include <vector>

#include "level/Platform.h"

class Level;
class Platform;
class SpriteFactory;
class SoundManager;
class Player;
class GameObject;
class TextureManager;
class FXManager;
class Magician;
class InputManager;
class InitialDrawer;


class GameController final
{
public:
    explicit GameController(
        std::map<std::string, Game::Label>& labels,
        json& data,
        const Rectf& viewPort,
        std::vector<GameObject*>& playerThrowables,
        std::vector<GameObject*>& enemyThrowables,
        std::vector<GameObject*>& effects,
        std::vector<GameObject*>& zombies,
        std::vector<GameObject*>& flyingKnights,
        std::vector<GameObject*>& woodyPigs,
        std::vector<GameObject*>& collectibles
        );
    
    ~GameController() = default;
    GameController(const GameController& other) = delete;
    GameController(GameController&& other) noexcept = delete;
    GameController& operator=(const GameController& other) = delete;
    GameController& operator=(GameController&& other) noexcept = delete;

    std::map<std::string, Game::Label>& m_Labels;
    json& m_Data;
    Rectf m_ViewPort;
    std::vector<GameObject*>& m_PlayerThrowables;
    std::vector<GameObject*>& m_EnemyThrowables;
    std::vector<GameObject*>& m_Effects;
    std::vector<GameObject*>& m_Zombies;
    std::vector<GameObject*>& m_FlyingKnights;
    std::vector<GameObject*>& m_WoodyPigs;
    std::vector<GameObject*>& m_Collectibles;

    TextureManager* m_pTextureManager;
    SpriteFactory* m_pSpriteFactory;
    SoundManager* m_pSoundManager;
    Player* m_pPlayer;
    Level* m_pLevel;
    Platform* m_pPlatform;
    FXManager* m_pFXManager;
    Magician* m_pMagician;
    InputManager* m_pInputManager;
    ScoreManager* m_pScoreManager;
    InitialDrawer* m_pInitialDrawer;
};
