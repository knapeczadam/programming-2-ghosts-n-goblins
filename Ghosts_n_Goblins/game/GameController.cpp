#include "pch.h"
#include "GameController.h"

GameController::GameController(
    const Rectf& viewPort,
    SpriteFactory* pSpriteFactory,
    SoundManager* pSoundManager,
    std::vector<GameObject*>& playerThrowables,
    std::vector<GameObject*>& enemyThrowables)
    : m_ViewPort{viewPort}
      , m_pSpriteFactory{pSpriteFactory}
      , m_pSoundManager{pSoundManager}
      , m_PlayerThrowables{playerThrowables}
      , m_EnemyThrowables{enemyThrowables}
      , m_pPlayer{nullptr}
      , m_pLevel{nullptr}
      , m_pPlatform{nullptr}
{
}
