// Knapecz, Adam - 1DAE11
#pragma once
#include "BaseGame.h"
#include "engine/json.hpp"

#include <string>

using json = nlohmann::json;

class HUD;
class Level;
class KillZone;
class Platform;
class Tombstone;
class Water;
class Player;
class Camera;
class TextureManager;
class SpriteFactory;
class GameObject;
class PowerUpManager;

class IThrowable;


class Game : public BaseGame
{
public:
    enum class Label
    {
        // CHARACTERS
        ARTHUR,
        BIG_MAN,
        CROW,
        FLYING_KNIGHT,
        GREEN_MONSTER,
        MAGICIAN,
        PRINCESS,
        RED_ARREMER,
        SATAN,
        WOODY_PIG,
        ZOMBIE,

        // COLLECTIBLES
        BASKET,
        COINS,
        MONEY_BAG,
        NECKLACE,
        SHIELD,

        // FX
        FIRE,
        FX,
        VANISH,

        // LEVEL
        DOOR,
        KILLZONE,
        LEVEL,
        PLATFORM,
        TOMBSTONE,
        WATER,

        // UI
        MAP,
        PIN,

        // WEAPONS
        DAGGER,
        LANCE,
        SPEAR,
        TORCH,

        // DEBUG
        LEVEL_DEBUG,
        FALLBACK,
        MISSING,
        DUMMY,

        // MINIGAME
        AVATAR
    };

public:
    explicit Game(const Window& window);
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;
    virtual ~Game() override;

    virtual void Update(float elapsedSec) override;
    virtual void Draw() const override;

    // Event handling
    virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;

private:
    // FUNCTIONS
    void Initialize();
    void InitWaters();
    void InitTombstones();
    void Cleanup();
    void ClearBackground() const;
    void PrintInfo() const;
    void Debug() const;
    void DoCollisionTests();

    void LoadData();
    void InitLabels();
    void InitCamera() const;
    
    // DATA MEMBERS
    
    std::vector<GameObject*> m_GameObjects;
    std::vector<IThrowable*> m_Throwables;
    std::vector<Water*> m_Waters;
    std::vector<Tombstone*> m_Tombstones;
    
    SpriteFactory* m_pSpriteFactory;
    TextureManager* m_pTextureManager;
    Player* m_pPlayer;
    Level* m_pLevel;
    KillZone* m_pKillZone;
    Platform* m_pPlatform;
    Camera* m_pCamera;
    HUD* m_pHUD;
    GameObject* m_pTestGameObject;
    
    json m_Data;
    const std::string m_DataPath;
    std::map<std::string, Label> m_Labels;

    bool m_AttackKeyReleased;

};
