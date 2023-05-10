#pragma once
#include "UI.h"

class Sprite;
class GameObject;

class Map final : public UI
{
public:
    explicit Map(GameController* pGameController);
    virtual ~Map() override;
    Map(const Map& other) = delete;
    Map(Map&& other) noexcept = delete;
    Map& operator=(const Map& other) = delete;
    Map& operator=(Map&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void Reset() const override;

    Rectf GetBoundaries() const;

    GameObject* GetDummy() const;

private:
    Sprite* m_pPin;
    Sprite* m_pMap;
    Sprite* m_pText;
    GameObject* pDummy;
    const float m_Speed;
    const Point2f m_PinPos;
    const Point2f m_TextPos;
};
