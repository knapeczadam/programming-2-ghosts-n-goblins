// Knapecz, Adam - 1DAE11
#pragma once
#include "game/GameObject.h"

#include <vector>

class Level final : public GameObject
{
public:
    explicit Level(GameController* pGameController);
    virtual ~Level() override = default;
    Level(const Level& other) = delete;
    Level(Level&& other) noexcept = delete;
    Level& operator=(const Level& other) = delete;
    Level& operator=(Level&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void HandleCollision(GameObject* other) override;

    bool IsOnGround(GameObject* pGameObject) const;
    Rectf GetBoundaries() const;
    void SetBoundaries(const Rectf& boundaries);
    bool HasReachedEnd(const Rectf& collider) const;

private:
    void SetVertices();

private:
    std::vector<std::vector<Point2f>> m_Vertices;
    Rectf m_Boundaries;
};
