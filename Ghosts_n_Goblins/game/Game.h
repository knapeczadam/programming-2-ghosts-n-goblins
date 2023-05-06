// Knapecz, Adam - 1DAE11
#pragma once

#include <queue>

#include "BaseGame.h"
#include "engine/json.hpp"
#include "engine/ITimer.h"
#include "Macros.h"


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
class Ladder;
class FXManager;

class IThrowable;
class IEnemy;
class ICollectible;
class IClimable;

class GameController;


/*
 * https://strategywiki.org/wiki/Ghosts_%27n_Goblins#Story
 * One storm filled evening, Arthur and his love, Princess Prin Prin were enjoying a quiet night in the cemetery together, when they were beset upon by a winged Satan.
 * The Satan dove and captured the princess, and disappeared with her before Arthur's eyes.
 * Without a moment's hesitation, Arthur donned his knight armor and picked up his lance, and set forth to Astaroth's castle where he knew he would find his abducted love.
 */
class Game : public BaseGame, public ITimer
{
public:
    enum class Label
    {
        // CHARACTERS
        C_ARTHUR,
        C_CROW,
        C_FLYING_KNIGHT,
        C_GREEN_MONSTER,
        C_MAGICIAN,
        C_PRINCESS,
        C_RED_ARREMER,
        C_SATAN,
        C_UNICORN,
        C_WOODY_PIG,
        C_ZOMBIE,

        // COLLECTIBLES
        O_COIN,
        O_DOLL,
        O_KEY,
        O_MONEY_BAG,
        O_NECKLACE,
        O_POT,
        O_SHIELD,
        O_YASHICHI,

        // FX
        F_FIRE_ENEMY,
        F_FIRE_TORCH,
        F_FX,
        F_PROJECTILE_BLOCK,
        F_PROJECTILE_DEATH,
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
        U_MENU,
        U_PIN,

        // THROWABLES
        T_DAGGER,
        T_EYEBALL,
        T_FIREBALL_RED_ARREMER,
        T_FIREBALL_UNICORN,
        T_LANCE,
        T_SPEAR,
        T_SPELL,
        T_TORCH,

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
        B_BLACK,
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
        B_21,
        B_22,
        B_23,
        B_24,
        B_25,
        B_END,
        
        // MINIGAME
        AVATAR
    };

public:
    explicit Game(const Window& window);
    virtual ~Game() override;
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;

    virtual void Update(float elapsedSec) override;
    virtual void LateUpdate(float elapsedSec) override;
    virtual void Draw() const override;

    // Event handling
    virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;

private:
    void Cleanup();
    void ClearBackground() const;
    void DrawBoot() const;
    void Boot();
    void PrintInfo() const;
    void DoCollisionTests();
    void Debug() const;
    void DoFrustumCulling();
    void DeactivateThrowablesOutOfView();
    void UpdateRemainingTime();

    
    void Initialize();
    
    void InitLabels();
    void LoadData();
    void InitBootIntervals();
    void InitCamera();

    // LEVEL
    void InitLevel();
    void InitLadders();
    void InitTombstones();
    void InitWaters();

    // COLLECTIBLES
    void InitCollectibles();
    void InitCoins();
    void InitMoneyBags();

    // ENEMIES
    void InitEnemies();
    void InitUnicorn();
    void InitCrows();
    void InitFlyingKnights();
    void InitGreenMonsters();
    void InitMagician();
    void InitRedArremer();
    void InitWoodyPigs();
    void InitZombies();
    
    // DATA MEMBERS
    
    std::vector<GameObject*> m_Enemies;
    std::vector<GameObject*> m_PlayerThrowables;
    std::vector<GameObject*> m_EnemyThrowables;
    std::vector<GameObject*> m_Waters;
    std::vector<GameObject*> m_Tombstones;
    std::vector<GameObject*> m_Collectibles;
    std::vector<GameObject*> m_Ladders;
    std::vector<GameObject*> m_Effects;
    
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
    GameController* m_pGameController;
    FXManager* m_pFXManager;
#if TEST_OBJECT
    GameObject* m_pTestObject;
#endif
    
    
    json m_Data;
    const std::string m_DataPath;
    std::map<std::string, Label> m_Labels;

    bool m_AttackKeyReleased;
    bool m_JumpKeyReleased;

    std::queue<std::pair<Label, float>> m_BootIntervals;
    Label m_CurrBoot;
    bool m_Boot;

};
