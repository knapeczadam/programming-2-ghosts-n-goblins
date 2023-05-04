#include "pch.h"
#include "BigMan.h"
#include "engine/SoundManager.h"

BigMan::BigMan(Sprite* pSprite, const Point2f& pos, Player* pPlayer, SoundManager* pSoundManager)
    : IEnemy{Game::Label::C_BIG_MAN, pSprite, pos, pPlayer, pSoundManager}
{
    m_Score = 2000;
}

void BigMan::Draw() const
{
    GameObject::Draw();
}

void BigMan::Update(float elapsedSec)
{
    GameObject::Update(elapsedSec);
}

void BigMan::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    m_pSoundManager->PlayEffect(Game::Label::E_BOSS_HIT);
    --m_Health;
    if (m_Health == 0)
    {
        m_pSoundManager->PlayEffect(Game::Label::E_BOSS_DEATH);
    }
}

void BigMan::Wait()
{
    IEnemy::Wait();
}

void BigMan::Walk()
{
    IEnemy::Walk();
    m_pSoundManager->PlayEffect(Game::Label::E_BIG_ENEMY_WALK);
}

void BigMan::Jump()
{
    IEnemy::Jump();
}

void BigMan::Shoot()
{
    IEnemy::Shoot();
}
