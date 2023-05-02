// Knapecz, Adam - 1DAE11
#pragma once

#include "Vector2f.h"
#include <vector>

#include "game/GameObject.h"


class Platform;

class Level : public GameObject
{
public:
    explicit Level(Sprite* pSprite, Platform* pPlatform);
    virtual ~Level() override = default;
    Level(const Level& other) = delete;
    Level(Level&& other) noexcept = delete;
    Level& operator=(const Level& other) = delete;
    Level& operator=(Level&& other) noexcept = delete;
    
    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void HandleCollision(GameObject* other) override;
    
    bool IsOnGround(GameObject* pGameObject) const;
    Rectf GetBoundaries() const;
    bool HasReachedEnd(const Rectf& collisionBox) const;

    Platform* GetPlatform() const;

private:
    void SetVertices();

private:
    Platform* m_pPlatform;
    std::vector<std::vector<Point2f>> m_Vertices;
    const float topMargin;
    Rectf m_Boundaries;
    GameObject* m_pPlayer;
};