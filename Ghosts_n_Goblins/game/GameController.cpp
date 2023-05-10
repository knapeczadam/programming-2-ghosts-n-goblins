#include "pch.h"
#include "GameController.h"

GameController::GameController(
    std::map<std::string, Game::Label>& labels,
    json& data,
    const Rectf& viewPort
)
    : m_Labels{labels}
      , m_Data(data) // doesn't work with brace initialization
      , m_ViewPort{viewPort} 
      , m_pBootManager{nullptr}
      , m_pCollectibleManager{nullptr}
      , m_pEnemyManager{nullptr}
      , m_pFXManager{nullptr}
      , m_pInitialDrawer{nullptr}
      , m_pInputManager{nullptr}
      , m_pLevelManager{nullptr}
      , m_pPlayerManager{nullptr}
      , m_pScoreManager{nullptr}
      , m_pSoundManager{nullptr}
      , m_pSpriteFactory{nullptr}
      , m_pTextureManager{nullptr}
      , m_pUIManager{nullptr}
{
}
