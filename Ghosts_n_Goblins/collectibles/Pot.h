#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Items
 * Throughout the game, you will encounter some enemies that carry pots with them.
 * If you shoot an enemy carrying a pot, the pot will fall to the ground and break, revealing the contents inside.
 * It can be one of three things: a weapon, a doll, or one of the princess' accessories.
 * Any weapon can appear, although certain weapons will only appear after certain levels.
 * The axe will only appear from stage 2 on, and the shield (or cross) will only appear from stage 3 on.
 * The doll or accessory that can appear depends on the stage that you're on.
 *
 * Items appear in a particular order, as follows:
 * Doll → Weapon → Doll → Accessory → Doll → Weapon → Doll → repeat
 *
 * Every fourth time this cycle initiates itself, the first doll encountered will always be the 10,000 point King doll.
 */ 
class Pot : public GameObject, public ICollectible
{
public:
    explicit Pot(const Point2f& pos, GameController* pGameController);
    virtual ~Pot() override = default;
    Pot(const Pot& other) = delete;
    Pot(Pot&& other) noexcept = delete;
    Pot& operator=(const Pot& other) = delete;
    Pot& operator=(Pot&& other) noexcept = delete;
};
