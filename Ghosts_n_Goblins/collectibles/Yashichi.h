#pragma once
#include "ICollectible.h"
#include "game/GameObject.h"

/*
 * https://ghostsngoblins.fandom.com/wiki/Yashichi
 * Yashichi (ヤシチ) is a pinwheel-like object found in many Capcom video games.
 * In Ghosts 'n Goblins it is a secret item that gives 10000 points (5000 in the NES version).
 * The NES version also has two extra flashing varieties:
 * The Yashichi flashing white and red gives 60 extra seconds to the player, while the one flashing orange reduces 30 seconds from the remaining time.
 * Both give 100 points.
 */
class Yashichi : public GameObject, public ICollectible
{
public:
    explicit Yashichi(const Point2f& pos, GameController* pGameController);
    virtual ~Yashichi() override = default;
    Yashichi(const Yashichi& other) = delete;
    Yashichi(Yashichi&& other) noexcept = delete;
    Yashichi& operator=(const Yashichi& other) = delete;
    Yashichi& operator=(Yashichi&& other) noexcept = delete;
};
