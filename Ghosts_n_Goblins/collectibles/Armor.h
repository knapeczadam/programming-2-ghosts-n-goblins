#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Items
 * There are five extra sets of armor hidden in the game, particularly after difficult sections when you are likely to need them.
 * You must walk, jump, or fall through the proper place to make them appear, and they will only appear if you are not wearing armor at the time.
 */
class Armor : public GameObject, public ICollectible
{
public:
    explicit Armor(const Point2f& pos, GameController* pGameController);
    virtual ~Armor() override = default;
    Armor(const Armor& other) = delete;
    Armor(Armor&& other) noexcept = delete;
    Armor& operator=(const Armor& other) = delete;
    Armor& operator=(Armor&& other) noexcept = delete;
};
