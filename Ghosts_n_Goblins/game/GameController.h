#pragma once

#include "level/Platform.h"

class BootManager;
class CollectibleManager;
class EnemyManager;
class FXManager;
class InitialDrawer;
class InputManager;
class LevelManager;
class PlayerManager;
class ScoreManager;
class SoundManager;
class SpriteFactory;
class TextureManager;
class UIManager;

class GameController final
{
public:
    explicit GameController(
        std::map<std::string, Game::Label>& labels,
        json& data,
        const Rectf& viewPort
        );
    
    ~GameController() = default;
    GameController(const GameController& other) = delete;
    GameController(GameController&& other) noexcept = delete;
    GameController& operator=(const GameController& other) = delete;
    GameController& operator=(GameController&& other) noexcept = delete;

    std::map<std::string, Game::Label>& m_Labels;
    json& m_Data;
    Rectf m_ViewPort;

    BootManager* m_pBootManager;
    CollectibleManager* m_pCollectibleManager;
    EnemyManager* m_pEnemyManager;
    FXManager* m_pFXManager;
    InitialDrawer* m_pInitialDrawer;
    InputManager* m_pInputManager;
    LevelManager* m_pLevelManager;
    PlayerManager* m_pPlayerManager;
    ScoreManager* m_pScoreManager;
    SoundManager* m_pSoundManager;
    SpriteFactory* m_pSpriteFactory;
    TextureManager* m_pTextureManager;
    UIManager* m_pUIManager;
};
