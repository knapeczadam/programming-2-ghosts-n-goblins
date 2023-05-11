// Knapecz, Adam - 1DAE11
#pragma once

#include "BaseGame.h"
#include "engine/json.hpp"
#include "engine/ITimer.h"
#include "Macros.h"

using json = nlohmann::json;

class BootManager;
class CameraManager;
class CutsceneManager;
class CollectibleManager;
class EnemyManager;
class FXManager;
class GameController;
class GameObject;
class InputManager;
class LevelManager;
class MenuManager;
class PlayerManager;
class SoundManager;
class SpriteFactory;
class TextureManager;
class UIManager;

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
        // --- IMAGES ---
        
        // Boot
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

        // Cutscene, narration
        N_01,
        N_02,
        N_03,
        N_04,
        N_05,
        N_06,
        N_07,
        N_08,
        N_09,
        N_10,
        N_11,
        N_12,
        N_13,
        N_14,
        N_15,
        N_16,
        N_17,
        N_18,
        N_19,
        N_20,
        N_21,
        N_22,
        N_23,
        N_24,
        N_25,
        N_26,
        N_27,
        N_28,
        N_29,
        N_30,
        N_31,
        N_32,
        N_33,
        N_END,
        
        // Characters
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

        // Collectibles
        O_ARMOR,
        O_COIN,
        O_DOLL,
        O_KEY,
        O_KING,
        O_MONEY_BAG,
        O_NECKLACE,
        O_POT,
        O_YASHICHI,

        // Fx
        F_FIRE_BOSS,
        F_FIRE_ENEMY,
        F_FIRE_TORCH,
        F_PROJECTILE_BLOCK_BOSS,
        F_PROJECTILE_BLOCK_ENEMY,
        F_PROJECTILE_DEATH,
        F_SCORE,
        F_VANISH,

        // Level
        L_ARMOR,
        L_DOOR,
        L_FOREGROUND,
        L_KILLZONE,
        L_LADDER,
        L_LEVEL,
        L_PLATFORM,
        L_TOMBSTONE,
        L_WATER,
        L_YASHICHI,

        // Throwables
        T_DAGGER,
        T_EYEBALL,
        T_FIREBALL_RED_ARREMER,
        T_FIREBALL_UNICORN,
        T_LANCE,
        T_SPEAR,
        T_SPELL,
        T_TORCH,
        
        // Ui
        U_ABC,
        U_TEXT_BEST_RANKING,
        U_TEXT_BONUS,
        U_CHARACTER_DRAWER,
        U_CREDIT_MANAGER,
        U_FRAME,
        U_HUD,
        U_LIFE,
        U_MAP,
        U_MENU_BACKGROUND_1,
        U_MENU_BACKGROUND_2,
        U_MENU_BACKGROUND_3,
        U_MENU_BACKGROUND_4,
        U_MENU,
        U_NUMBERS,
        U_PIN,
        U_RANKING_DRAWER,
        U_SCORE_MANAGER,
        U_TEXT_BOTTOM_ROW,
        U_TEXT_DEPOSIT,
        U_TEXT_GAME_OVER,
        U_TEXT_GAME_OVER_PLAYER_ONE,
        U_TEXT_INITIAL,
        U_TEXT_PLAYER_ONE_READY,
        U_TEXT_TIME,
        U_TEXT_TITLE,
        U_TEXT_TOP_ROW,
        U_UI,
        U_WEAPONS,

        // --- SOUNDS ---
        
        // Effects
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

        // Streams
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

        // --- DEBUG ---
        
        D_DUMMY,
        D_FALLBACK,
        D_LEVEL_DEBUG,
        D_MISSING,

        // --- INPUT ---
        
        I_LEFT,
        I_RIGHT,
        I_UP,
        I_DOWN,
        I_JUMP,
        I_ATTACK,
        I_SELECT,
        I_START,
        I_SAVE,
        I_LOAD,
        I_INFO,
        I_DEBUG,
        I_QUIT,
        I_INCREASE_VOLUME,
        I_DECREASE_VOLUME,
        
        // MINIGAME
        AVATAR,
    };

    enum class State
    {
        BOOT,
        MENU,
        INTRO,
        GAME,
        MAP,
        GAME_OVER,
        CONTINUE,
        RANKING,
        OUTRO,
        SAVE_SCORE
    };

public:
    explicit Game(const Window& window);
    virtual ~Game() override;
    Game(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game& operator=(Game&& other) = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
    virtual void LateUpdate(float elapsedSec) override;

    virtual void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    virtual void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;

private:
    void Initialize();
    void InitLabels();
    void LoadData();
    
    void ClearBackground() const;
    
    void DrawContinue() const;
    void DrawDebug() const;
    void DrawGame() const;
    void DrawGameOver() const;
    void DrawIntro() const;
    void DrawMap() const;
    void DrawMenu() const;
    void DrawOutro() const;
    void DrawRanking() const;
    void DrawSaveScore() const;
    
    void UpdateBoot(float elapsedSec);
    void UpdateContinue(float elapsedSec);
    void UpdateGame(float elapsedSec);
    void UpdateGameOver(float elapsedSec);
    void UpdateIntro(float elapsedSec);
    void UpdateMap(float elapsedSec);
    void UpdateMenu(float elapsedSec);
    void UpdateOutro(float elapsedSec);
    void UpdateRanking(float elapsedSec);
    void UpdateSaveScore(float elapsedSec);

    void UpdateState();
    void LateUpdateGame(float elapsedSec);
    void UpdateRemainingTime();
    
    void HandleCollisions();
    void Debug() const;
    void PrintInfo() const;

private:
    json m_Data;
    const std::string m_DataPath;
    std::map<std::string, Label> m_Labels;
    State m_State;
    
    BootManager* m_pBootManager;
    CameraManager* m_pCameraManager;
    CutsceneManager* m_pCutsceneManager;
    CollectibleManager* m_pCollectibleManager;
    EnemyManager* m_pEnemyManager;
    FXManager* m_pFXManager;
    GameController* m_pGameController;
    InputManager* m_pInputManager;
    LevelManager* m_pLevelManager;
    MenuManager* m_pMenuManager;
    PlayerManager* m_pPlayerManager;
    SoundManager* m_pSoundManager;
    SpriteFactory* m_pSpriteFactory;
    TextureManager* m_pTextureManager;
    UIManager* m_pUIManager;
    
#if TEST_OBJECT
    GameObject* m_pTestObject;
#endif
};
