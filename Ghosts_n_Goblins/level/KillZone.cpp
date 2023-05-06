#include "pch.h"
#include "KillZone.h"
#include <iostream>

#include "characters/Player.h"

KillZone::KillZone(float width, float height)
    : GameObject{Game::Label::L_KILLZONE, Rectf{0, 0, width, height}, true, false, Color4f{1.0f, 0.0f, 0.0f, 1.0f}}
{
    m_HasSprite = false;
}

void KillZone::HandleCollision(GameObject* other)
{
    if (not IsOverlapping(other)) return;
    other->SetActive(false);
    StartTimer(5.0f);
    if (IsTimerFinished())
    {
        // TODO: valami érdekes történik, amikor a platform utáni vizbe esik, nem teleportál vissza a kezdőpontra
        other->SetPosition(Player::GetSpawnPos());
        other->SetActive(true);
    }
}
