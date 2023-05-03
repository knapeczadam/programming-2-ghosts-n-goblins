// Knapecz, Adam - 1DAE11
#pragma once
#include <queue>

#include "BaseGame.h"
#include "engine/json.hpp"
#include "engine/Timer.h"

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
class SoundManager;

class IThrowable;
class IEnemy;
class ICollectible;
class IClimable;


class Game : public BaseGame, public Timer
{
public:
    enum class Label
    {
        // CHARACTERS
        C_ARTHUR,
        C_BIG_MAN,
        C_CROW,
        C_FLYING_KNIGHT,
        C_GREEN_MONSTER,
        C_MAGICIAN,
        C_PRINCESS,
        C_RED_ARREMER,
        C_SATAN,
        C_WOODY_PIG,
        C_ZOMBIE,

        // COLLECTIBLES
        O_BASKET,
        O_BUST,
        O_COIN,
        O_KEY,
        O_MONEY_BAG,
        O_NECKLACE,
        O_SHIELD,
        O_STAR,

        // FX
        F_FIRE,
        F_FX,
        F_VANISH,

        // LEVEL
        L_DOOR,
        L_FOREGROUND,
        L_KILLZONE,
        L_LADDER,
        L_LEVEL,
        L_PLATFORM,
        L_TOMBSTONE,
        L_WATER,

        // UI
        U_HUD,
        U_MAP,
        U_PIN,

        // WEAPONS
        W_DAGGER,
        W_LANCE,
        W_SPEAR,
        W_TORCH,

        // DEBUG
        D_LEVEL_DEBUG,
        D_FALLBACK,
        D_MISSING,
        D_DUMMY,

        // EFFECTS
        E_ARMOR_PICKUP,
        E_ARTHUR_HIT,
        E_ARTHUR_JUMP,
        E_ARTHUR_JUMP_FROG,
        E_ARTHUR_LAND,
        E_ARTHUR_THROW,
        E_ARTHUR_TRANSFORM,
        E_BIG_ENEMY_WALK,
        E_BOSS_DEATH,
        E_BOSS_HIT,
        E_CROW,
        E_DOOR_OPEN,
        E_ENEMY_DEATH,
        E_ENEMY_HIT,
        E_EXTRA_LIFE,
        E_FLYING_KNIGHT,
        E_MAGICIAN,
        E_PROJECTILE_BLOCK,
        E_RED_ARREMER_ATTACK,
        E_TORCH,
        E_TREASURE_PICKUP,
        E_WEAPON_PICKUP,
        E_WOODY_PIG,
        E_ZOMBIE_SPAWN,
        
        // STREAMS
        S_01_CREDIT,
        S_02_START_DEMO,
        S_03_STAGE_INTRODUCTION_MAP,
        S_04_GROUND_BGM,
        S_05_HURRY_UP,
        S_06_PLAYER_OUT,
        S_07_GAME_OVER,
        S_08_BOSS,
        S_09_STAGE_CLEAR,
        S_10_1ST_PLACE_NAME_REGISTRATION,
        S_11_1ST_PLACE_ENTRY_END,
        S_12_BELOW_2ND_PLACE_NAME_REGISTRATION,
        S_13_BELOW_2ND_PLACE_ENTRY_END,

        // BOOT
        B_01,
        B_02,
        B_03,
        B_04,
        B_05,
        B_06,
        B_07,
        B_08,
        B_09,
        B_10,
        B_11,
        B_12,
        B_13,
        B_14,
        B_15,
        B_16,
        B_17,
        B_18,
        B_19,
        B_20,
        
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
    virtual void LateUpdate(float elapsedSec) override;
    virtual void Draw() const override;

    // Event handling
    virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;

private:
    // FUNCTIONS
    void DrawBoot() const;
    void Boot();
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
    void InitBootIntervals();
    void InitLadders();
    void InitCoins();
    void InitMoneyBags();
    void InitGreenMonsters();
    
    // DATA MEMBERS
    
    std::vector<IEnemy*> m_Enemies;
    std::vector<IThrowable*> m_Throwables;
    std::vector<Water*> m_Waters;
    std::vector<Tombstone*> m_Tombstones;
    std::vector<ICollectible*> m_Collectibles;
    std::vector<IClimable*> m_Ladders;
    
    SpriteFactory* m_pSpriteFactory;
    TextureManager* m_pTextureManager;
    SoundManager* m_pSoundManager;
    Player* m_pPlayer;
    GameObject* m_pForeground;
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
    bool m_JumpKeyReleased;

    std::queue<float> m_BootIntervals;
    int m_BootCounter;
    const int m_MaxBootCount;
    bool m_Boot;

};
