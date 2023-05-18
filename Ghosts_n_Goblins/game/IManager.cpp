#include "pch.h"
#include "IManager.h"

#include "GameController.h"

IManager::IManager(GameController* pGameController)
    : m_pGameController{pGameController}
{
}

void IManager::Update(float elapsedSec)
{
    
}

void IManager::Reset(bool fromCheckpoint)
{
    CleanUp();
    Initialize(fromCheckpoint);
}
