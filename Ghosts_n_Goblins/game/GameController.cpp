#include "pch.h"
#include "GameController.h"

GameController::GameController(
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
)
    : m_Labels{labels}
      , m_Data(data)
      , m_ViewPort{viewPort} // doesn't work with brace initialization
      , m_PlayerThrowables{playerThrowables}
      , m_EnemyThrowables{enemyThrowables}
      , m_Effects{effects}
      , m_Zombies{zombies}
      , m_FlyingKnights{flyingKnights}
      , m_WoodyPigs{woodyPigs}
      , m_Collectibles{collectibles}
      , m_pTextureManager{nullptr}
      , m_pSpriteFactory{nullptr}
      , m_pSoundManager{nullptr}
      , m_pPlayer{nullptr}
      , m_pLevel{nullptr}
      , m_pPlatform{nullptr}
      , m_pFXManager{nullptr}
      , m_pMagician{nullptr}
{
}
