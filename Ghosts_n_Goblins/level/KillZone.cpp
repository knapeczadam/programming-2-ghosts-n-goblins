#include "pch.h"
#include "KillZone.h"
#include <iostream>

#include "characters/Player.h"

KillZone::KillZone(float width, float height)
    : GameObject{Game::Label::KILLZONE, Rectf{0, 0, width, height}}
{
}

void KillZone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    other->SetActive(false);
    StartTimer(5.0f);
    if (IsTimerFinished())
    {
        other->SetActive(true);
        other->SetPosition(Player::GetSpawnPos());
    }
}
