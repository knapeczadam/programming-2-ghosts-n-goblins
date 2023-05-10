#pragma once

#include "level/Platform.h"

#include <cassert>

#include "MenuManager.h"

class BootManager;
class CameraManager;
class CollectibleManager;
class EnemyManager;
class FXManager;
class InputManager;
class LevelManager;
class PlayerManager;
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

    inline void Test() const
    {
        assert(m_pBootManager != nullptr and "GameController::Test() m_pBootManager is nullptr");
        assert(m_pCameraManager != nullptr and "GameController::Test() m_pCameraManager is nullptr");
        assert(m_pCollectibleManager != nullptr and "GameController::Test() m_pCollectibleManager is nullptr");
        assert(m_pEnemyManager != nullptr and "GameController::Test() m_pEnemyManager is nullptr");
        assert(m_pFXManager != nullptr and "GameController::Test() m_pFXManager is nullptr");
        assert(m_pInputManager != nullptr and "GameController::Test() m_pInputManager is nullptr");
        assert(m_pLevelManager != nullptr and "GameController::Test() m_pLevelManager is nullptr");
        assert(m_pMenuManager != nullptr and "GameController::Test() m_pMenuManager is nullptr");
        assert(m_pPlayerManager != nullptr and "GameController::Test() m_pPlayerManager is nullptr");
        assert(m_pSoundManager != nullptr and "GameController::Test() m_pSoundManager is nullptr");
        assert(m_pSpriteFactory != nullptr and "GameController::Test() m_pSpriteFactory is nullptr");
        assert(m_pTextureManager != nullptr and "GameController::Test() m_pTextureManager is nullptr");
        assert(m_pUIManager != nullptr and "GameController::Test() m_pUIManager is nullptr");
    }

    std::map<std::string, Game::Label>& m_Labels;
    json& m_Data;
    Rectf m_ViewPort;

    BootManager* m_pBootManager;
    CameraManager* m_pCameraManager;
    CollectibleManager* m_pCollectibleManager;
    EnemyManager* m_pEnemyManager;
    FXManager* m_pFXManager;
    InputManager* m_pInputManager;
    LevelManager* m_pLevelManager;
    MenuManager* m_pMenuManager;
    PlayerManager* m_pPlayerManager;
    SoundManager* m_pSoundManager;
    SpriteFactory* m_pSpriteFactory;
    TextureManager* m_pTextureManager;
    UIManager* m_pUIManager;
};
