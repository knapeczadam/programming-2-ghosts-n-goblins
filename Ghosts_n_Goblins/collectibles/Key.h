#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

class Key : public GameObject, public ICollectible
{
public:
    Key(const Point2f& pos, SpriteFactory* pSpriteFactory);
    virtual ~Key() override = default;
    Key(const Key& other) = delete;
    Key(Key&& other) noexcept = delete;
    Key& operator=(const Key& other) = delete;
    Key& operator=(Key&& other) noexcept = delete;
};
