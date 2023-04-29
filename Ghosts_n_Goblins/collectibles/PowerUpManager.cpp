// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "PowerUpManager.h"
#include <algorithm>
#include "SoundEffect.h"

PowerUpManager::PowerUpManager()
    : m_pPowerUpSoundEffect(new SoundEffect("sounds/minigame/powerUp.mp3"))
{
}

PowerUpManager::~PowerUpManager()
{
    std::ranges::for_each(m_pItems, [](const PowerUp* e) { delete e; });
    delete m_pPowerUpSoundEffect;
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
    PowerUp* powerUp{new PowerUp{center, type}};
    m_pItems.push_back(powerUp);
    return powerUp;
}

void PowerUpManager::Update(float elapsedSec)
{
    std::ranges::for_each(m_pItems, [=](PowerUp* e) { e->Update(elapsedSec); });
}

void PowerUpManager::Draw() const
{
    std::ranges::for_each(m_pItems, [](PowerUp* e) { e->Draw(); });
}

size_t PowerUpManager::Size() const
{
    return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
    const auto isHit{std::erase_if(m_pItems, [&](PowerUp* e) { return e->IsOverlapping(rect); })};
    if (isHit)
    {
        m_pPowerUpSoundEffect->Play(0);
    }
    return isHit;
}
