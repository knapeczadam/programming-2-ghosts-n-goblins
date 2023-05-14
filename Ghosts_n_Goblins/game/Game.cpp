// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"

#include "BootManager.h"
#include "Camera.h"
#include "CameraManager.h"
#include "CollectibleManager.h"
#include "CutsceneManager.h"
#include "EnemyManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "PlayerManager.h"
#include "Texture.h"
#include "UIManager.h"
#include "utils.h"
#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "characters/Zombie.h"
#include "engine/Clock.h"
#include "engine/json.hpp"
#include "engine/SoundManager.h"
#include "engine/SpriteFactory.h"
#include "engine/TextureManager.h"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/Macros.h"
#include "level/Level.h"
#include "ui/CreditManager.h"
#include "ui/HUD.h"
#include "ui/InitialSaver.h"
#include "ui/ScoreManager.h"

#include <fstream>
#include <iostream>
#include <ranges>


std::random_device Game::rd;
std::mt19937 Game::mt{rd()};


Game::Game(const Window& window)
    : BaseGame{window}
      , m_Data{nullptr}
      , m_DataPath{"data.json"}
      , m_Labels{}
      , m_State{State::BOOT}
      , m_pBootManager{nullptr}
      , m_pCameraManager{nullptr}
      , m_pCutsceneManager{nullptr}
      , m_pCollectibleManager{nullptr}
      , m_pEnemyManager{nullptr}
      , m_pFXManager{nullptr}
      , m_pGameController{nullptr}
      , m_pInputManager{nullptr}
      , m_pLevelManager{nullptr}
      , m_pMenuManager{nullptr}
      , m_pPlayerManager{nullptr}
      , m_pSoundManager{nullptr}
      , m_pSpriteFactory{nullptr}
      , m_pTextureManager{nullptr}
      , m_pUIManager{nullptr}
#if TEST_OBJECT
      , m_pTestObject{nullptr}
#endif
{
    Initialize();
}

void Game::Initialize()
{
    InitLabels();
    // Loading data from JSON
    LoadData();

    // GAME CONTROLLER
    m_pGameController = new GameController{m_Labels, m_Data, GetViewPort()};

    // Order of initialization is important
    // 1. TEXTURE MANAGER
    // 2. SPRITE FACTORY
    m_pSpriteFactory = new SpriteFactory{m_pGameController};
    m_pTextureManager = new TextureManager{m_pGameController};

    m_pSoundManager = new SoundManager{m_pGameController};
    m_pFXManager = new FXManager{m_pGameController};
    m_pInputManager = new InputManager{m_pGameController};
    m_pBootManager = new BootManager{m_pGameController};
    m_pCollectibleManager = new CollectibleManager{m_pGameController};
    m_pCutsceneManager = new CutsceneManager{m_pGameController};
    m_pEnemyManager = new EnemyManager{m_pGameController};
    m_pLevelManager = new LevelManager{m_pGameController};
    m_pMenuManager = new MenuManager{m_pGameController};
    m_pPlayerManager = new PlayerManager{m_pGameController};
    m_pUIManager = new UIManager{m_pGameController};

    // CAMERA - has to be after level and player initialization
    m_pCameraManager = new CameraManager{m_pGameController};
#if TEST_OBJECT
    m_pTestObject = new Zombie{Point2f{-32.f, 62.f}, m_pGameController};
    m_pTestObject->SetActive(false);
    m_pTestObject->SetVisible(false);
#endif

    m_pGameController->Test();
}

Game::~Game()
{
    delete m_pCameraManager;
    delete m_pUIManager;
    delete m_pPlayerManager;
    delete m_pLevelManager;
    delete m_pMenuManager;
    delete m_pEnemyManager;
    delete m_pCutsceneManager;
    delete m_pCollectibleManager;
    delete m_pBootManager;
    delete m_pInputManager;
    delete m_pFXManager;
    delete m_pSoundManager;
    delete m_pTextureManager;
    delete m_pSpriteFactory;
    delete m_pGameController;
#if TEST_OBJECT
    delete m_pTestObject;
#endif
}

void Game::InitLabels()
{
    // --- IMAGES ---

    // Boot
    m_Labels["b_black"] = Label::B_BLACK;
    m_Labels["b_01"] = Label::B_01;
    m_Labels["b_02"] = Label::B_02;
    m_Labels["b_03"] = Label::B_03;
    m_Labels["b_04"] = Label::B_04;
    m_Labels["b_05"] = Label::B_05;
    m_Labels["b_06"] = Label::B_06;
    m_Labels["b_07"] = Label::B_07;
    m_Labels["b_08"] = Label::B_08;
    m_Labels["b_09"] = Label::B_09;
    m_Labels["b_10"] = Label::B_10;
    m_Labels["b_11"] = Label::B_11;
    m_Labels["b_12"] = Label::B_12;
    m_Labels["b_13"] = Label::B_13;
    m_Labels["b_14"] = Label::B_14;
    m_Labels["b_15"] = Label::B_15;
    m_Labels["b_16"] = Label::B_16;
    m_Labels["b_17"] = Label::B_17;
    m_Labels["b_18"] = Label::B_18;
    m_Labels["b_19"] = Label::B_19;
    m_Labels["b_20"] = Label::B_20;
    m_Labels["b_21"] = Label::B_21;
    m_Labels["b_22"] = Label::B_22;
    m_Labels["b_23"] = Label::B_23;
    m_Labels["b_24"] = Label::B_24;
    m_Labels["b_25"] = Label::B_25;

    // Cutscene
    m_Labels["n_01"] = Label::N_01;
    m_Labels["n_02"] = Label::N_02;
    m_Labels["n_03"] = Label::N_03;
    m_Labels["n_04"] = Label::N_04;
    m_Labels["n_05"] = Label::N_05;
    m_Labels["n_06"] = Label::N_06;
    m_Labels["n_07"] = Label::N_07;
    m_Labels["n_08"] = Label::N_08;
    m_Labels["n_09"] = Label::N_09;
    m_Labels["n_10"] = Label::N_10;
    m_Labels["n_11"] = Label::N_11;
    m_Labels["n_12"] = Label::N_12;
    m_Labels["n_13"] = Label::N_13;
    m_Labels["n_14"] = Label::N_14;
    m_Labels["n_15"] = Label::N_15;
    m_Labels["n_16"] = Label::N_16;
    m_Labels["n_17"] = Label::N_17;
    m_Labels["n_18"] = Label::N_18;
    m_Labels["n_19"] = Label::N_19;
    m_Labels["n_20"] = Label::N_20;
    m_Labels["n_21"] = Label::N_21;
    m_Labels["n_22"] = Label::N_22;
    m_Labels["n_23"] = Label::N_23;
    m_Labels["n_24"] = Label::N_24;
    m_Labels["n_25"] = Label::N_25;
    m_Labels["n_26"] = Label::N_26;
    m_Labels["n_27"] = Label::N_27;
    m_Labels["n_28"] = Label::N_28;
    m_Labels["n_29"] = Label::N_29;
    m_Labels["n_30"] = Label::N_30;
    m_Labels["n_31"] = Label::N_31;
    m_Labels["n_32"] = Label::N_32;
    m_Labels["n_33"] = Label::N_33;

    // Characters
    m_Labels["c_arthur"] = Label::C_ARTHUR;
    m_Labels["c_crow"] = Label::C_CROW;
    m_Labels["c_flying_knight"] = Label::C_FLYING_KNIGHT;
    m_Labels["c_green_monster"] = Label::C_GREEN_MONSTER;
    m_Labels["c_magician"] = Label::C_MAGICIAN;
    m_Labels["c_princess"] = Label::C_PRINCESS;
    m_Labels["c_red_arremer"] = Label::C_RED_ARREMER;
    m_Labels["c_satan"] = Label::C_SATAN;
    m_Labels["c_unicorn"] = Label::C_UNICORN;
    m_Labels["c_woody_pig"] = Label::C_WOODY_PIG;
    m_Labels["c_zombie"] = Label::C_ZOMBIE;

    // Collectibles
    m_Labels["o_armor"] = Label::O_ARMOR;
    m_Labels["o_coin"] = Label::O_COIN;
    m_Labels["o_doll"] = Label::O_DOLL;
    m_Labels["o_key"] = Label::O_KEY;
    m_Labels["o_king"] = Label::O_KING;
    m_Labels["o_money_bag"] = Label::O_MONEY_BAG;
    m_Labels["o_necklace"] = Label::O_NECKLACE;
    m_Labels["o_pot"] = Label::O_POT;
    m_Labels["o_yashichi"] = Label::O_YASHICHI;

    // Fx
    m_Labels["f_fire_boss"] = Label::F_FIRE_BOSS;
    m_Labels["f_fire_enemy"] = Label::F_FIRE_ENEMY;
    m_Labels["f_fire_torch"] = Label::F_FIRE_TORCH;
    m_Labels["f_projectile_block_boss"] = Label::F_PROJECTILE_BLOCK_BOSS;
    m_Labels["f_projectile_block_enemy"] = Label::F_PROJECTILE_BLOCK_ENEMY;
    m_Labels["f_projectile_death"] = Label::F_PROJECTILE_DEATH;
    m_Labels["f_score"] = Label::F_SCORE;
    m_Labels["f_vanish"] = Label::F_VANISH;

    // Level
    m_Labels["l_door"] = Label::L_DOOR;
    m_Labels["l_foreground"] = Label::L_FOREGROUND;
    m_Labels["l_level"] = Label::L_LEVEL;
    m_Labels["l_platform"] = Label::L_PLATFORM;
    m_Labels["l_water"] = Label::L_WATER;

    // Throwables
    m_Labels["t_dagger"] = Label::T_DAGGER;
    m_Labels["t_eyeball"] = Label::T_EYEBALL;
    m_Labels["t_fireball_red_arremer"] = Label::T_FIREBALL_RED_ARREMER;
    m_Labels["t_fireball_unicorn"] = Label::T_FIREBALL_UNICORN;
    m_Labels["t_lance"] = Label::T_LANCE;
    m_Labels["t_spear"] = Label::T_SPEAR;
    m_Labels["t_spell"] = Label::T_SPELL;
    m_Labels["t_torch"] = Label::T_TORCH;

    // Ui
    m_Labels["u_abc"] = Label::U_ABC;
    m_Labels["u_frame"] = Label::U_FRAME;
    m_Labels["u_life"] = Label::U_LIFE;
    m_Labels["u_map"] = Label::U_MAP;
    m_Labels["u_menu_background_1"] = Label::U_MENU_BACKGROUND_1;
    m_Labels["u_menu_background_2"] = Label::U_MENU_BACKGROUND_2;
    m_Labels["u_menu_background_3"] = Label::U_MENU_BACKGROUND_3;
    m_Labels["u_menu_background_4"] = Label::U_MENU_BACKGROUND_4;
    m_Labels["u_numbers"] = Label::U_NUMBERS;
    m_Labels["u_pin"] = Label::U_PIN;
    m_Labels["u_text_bonus"] = Label::U_TEXT_BONUS;
    m_Labels["u_text_bonus_key"] = Label::U_TEXT_BONUS_KEY;
    m_Labels["u_text_bottom_row"] = Label::U_TEXT_BOTTOM_ROW;
    m_Labels["u_text_continue"] = Label::U_TEXT_CONTINUE;
    m_Labels["u_text_deposit"] = Label::U_TEXT_DEPOSIT;
    m_Labels["u_text_game_over"] = Label::U_TEXT_GAME_OVER;
    m_Labels["u_text_game_over_player_one"] = Label::U_TEXT_GAME_OVER_PLAYER_ONE;
    m_Labels["u_text_initial"] = Label::U_TEXT_INITIAL;
    m_Labels["u_text_key"] = Label::U_TEXT_KEY;
    m_Labels["u_text_player_one_ready"] = Label::U_TEXT_PLAYER_ONE_READY;
    m_Labels["u_text_ranking"] = Label::U_TEXT_RANKING;
    m_Labels["u_text_time"] = Label::U_TEXT_TIME;
    m_Labels["u_text_title"] = Label::U_TEXT_TITLE;
    m_Labels["u_text_top_row"] = Label::U_TEXT_TOP_ROW;
    m_Labels["u_weapons"] = Label::U_WEAPONS;

    // --- SOUNDS ---

    // Effects
    m_Labels["e_armor_pickup"] = Label::E_ARMOR_PICKUP;
    m_Labels["e_arthur_hit"] = Label::E_ARTHUR_HIT;
    m_Labels["e_arthur_jump"] = Label::E_ARTHUR_JUMP;
    m_Labels["e_arthur_jump_frog"] = Label::E_ARTHUR_JUMP_FROG;
    m_Labels["e_arthur_land"] = Label::E_ARTHUR_LAND;
    m_Labels["e_arthur_throw"] = Label::E_ARTHUR_THROW;
    m_Labels["e_arthur_transform"] = Label::E_ARTHUR_TRANSFORM;
    m_Labels["e_big_enemy_walk"] = Label::E_BIG_ENEMY_WALK;
    m_Labels["e_boss_death"] = Label::E_BOSS_DEATH;
    m_Labels["e_boss_hit"] = Label::E_BOSS_HIT;
    m_Labels["e_crow"] = Label::E_CROW;
    m_Labels["e_door_open"] = Label::E_DOOR_OPEN;
    m_Labels["e_enemy_death"] = Label::E_ENEMY_DEATH;
    m_Labels["e_enemy_hit"] = Label::E_ENEMY_HIT;
    m_Labels["e_extra_life"] = Label::E_EXTRA_LIFE;
    m_Labels["e_flying_knight"] = Label::E_FLYING_KNIGHT;
    m_Labels["e_magician"] = Label::E_MAGICIAN;
    m_Labels["e_projectile_block"] = Label::E_PROJECTILE_BLOCK;
    m_Labels["e_red_arremer_attack"] = Label::E_RED_ARREMER_ATTACK;
    m_Labels["e_torch"] = Label::E_TORCH;
    m_Labels["e_treasure_pickup"] = Label::E_TREASURE_PICKUP;
    m_Labels["e_weapon_pickup"] = Label::E_WEAPON_PICKUP;
    m_Labels["e_woody_pig"] = Label::E_WOODY_PIG;
    m_Labels["e_zombie_spawn"] = Label::E_ZOMBIE_SPAWN;

    // Streams
    m_Labels["s_01_credit"] = Label::S_01_CREDIT;
    m_Labels["s_02_start_demo"] = Label::S_02_START_DEMO;
    m_Labels["s_03_stage_introduction_map"] = Label::S_03_STAGE_INTRODUCTION_MAP;
    m_Labels["s_04_ground_bgm"] = Label::S_04_GROUND_BGM;
    m_Labels["s_05_hurry_up"] = Label::S_05_HURRY_UP;
    m_Labels["s_06_player_out"] = Label::S_06_PLAYER_OUT;
    m_Labels["s_07_game_over"] = Label::S_07_GAME_OVER;
    m_Labels["s_08_boss"] = Label::S_08_BOSS;
    m_Labels["s_09_stage_clear"] = Label::S_09_STAGE_CLEAR;
    m_Labels["s_10_1st_place_name_registration"] = Label::S_10_1ST_PLACE_NAME_REGISTRATION;
    m_Labels["s_11_1st_place_entry_end"] = Label::S_11_1ST_PLACE_ENTRY_END;
    m_Labels["s_12_below_2nd_place_name_registration"] = Label::S_12_BELOW_2ND_PLACE_NAME_REGISTRATION;
    m_Labels["s_13_below_2nd_place_entry_end"] = Label::S_13_BELOW_2ND_PLACE_ENTRY_END;
    m_Labels["s_14_unused_jingle"] = Label::S_14_UNUSED_JINGLE;

    // --- DEBUG --- 
    m_Labels["d_level_debug"] = Label::D_LEVEL_DEBUG;
    m_Labels["d_fallback"] = Label::D_FALLBACK;

    // MINIGAME
    m_Labels["avatar"] = Label::AVATAR;
}

/*
 * Load data from the data.json file located in the Resource folder
 * Only works with version 3.8.0 of nlohmann::json : https://github.com/nlohmann/json/tree/v3.8.0
 * Closing the file is done automatically by the destructor of the ifstream object
 */
void Game::LoadData()
{
    std::ifstream file{m_DataPath};
    if (file)
    {
        m_Data = json::parse(file, nullptr, false);
    }
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawBoot() const
{
    m_pBootManager->Draw();
}

void Game::Draw() const
{
    ClearBackground();

    switch (m_State)
    {
    case State::BOOT:
        DrawBoot();
        break;
    case State::MENU:
    case State::CREDIT:
        DrawMenu();
        break;
    case State::INTRO:
        DrawIntro();
        break;
    case State::END:
        DrawEnd();
        break;
    case State::HURRY_UP:
    case State::GAME:
    case State::GAME_OVER:
    case State::FROZEN:
    case State::BOSS:
    case State::STAGE_CLEAR:
        DrawGame();
        break;
    case State::SAVE_SCORE:
    case State::SAVE_END:
        DrawSaveScore();
        break;
    case State::MAP:
        DrawMap();
        break;
    case State::CONTINUE:
        DrawContinue();
        break;
    case State::RANKING:
        DrawRanking();
        break;
    case State::OUTRO:
        DrawOutro();
        break;
    }

#if DRAW_CENTER_GUIDE
    utils::SetColor(Color4f{1.0f, 1.0f, 1.0f, 0.5f});
    utils::DrawLine(Point2f{GetViewPort().width / 2, 0}, Point2f{GetViewPort().width / 2, GetViewPort().height});
    utils::DrawLine(Point2f{0, GetViewPort().height / 2}, Point2f{GetViewPort().width, GetViewPort().height / 2});
#endif
}

void Game::Update(float elapsedSec)
{
    Clock::Update(elapsedSec);

    switch (m_State)
    {
    case State::BOOT:
        UpdateBoot(elapsedSec);
        break;
    case State::MENU:
    case State::CREDIT:
        UpdateMenu(elapsedSec);
        break;
    case State::INTRO:
        UpdateIntro(elapsedSec);
        break;
    case State::HURRY_UP:
    case State::GAME:
    case State::BOSS:
    case State::STAGE_CLEAR:
        UpdateGame(elapsedSec);
        break;
    case State::MAP:
        UpdateMap(elapsedSec);
        break;
    case State::GAME_OVER:
        UpdateGameOver(elapsedSec);
        break;
    case State::CONTINUE:
        UpdateContinue(elapsedSec);
        break;
    case State::RANKING:
        UpdateRanking(elapsedSec);
        break;
    case State::OUTRO:
        UpdateOutro(elapsedSec);
        break;
    case State::SAVE_SCORE:
        UpdateSaveScore(elapsedSec);
        break;
    }

    UpdateState();
    PlayStream();
}

void Game::LateUpdate(float elapsedSec)
{
    switch (m_State)
    {
    case State::HURRY_UP:
    case State::GAME:
    case State::BOSS:
    case State::STAGE_CLEAR:
        LateUpdateGame(elapsedSec);
        break;
    }
}

void Game::UpdateState()
{
    switch (m_State)
    {
    case State::BOOT:
        if (m_pBootManager->GetState() == Label::B_END)
        {
            m_pBootManager->Reset();
            m_State = State::MENU;
        }
        break;
    case State::MENU:
        if (m_pUIManager->m_pCreditManager->GetCredits() and m_pGameController->m_pInputManager->IsPressed(
            Label::I_SELECT))
        {
            m_State = State::INTRO;
        }
        else if (m_pUIManager->m_pCreditManager->GetCredits() and not m_pUIManager->m_pCreditManager->CreditInserted())
        {
            ResetTimer();
            m_State = State::CREDIT;
        }
        break;
    case State::CREDIT:
        if (m_pGameController->m_pInputManager->IsPressed(Label::I_SELECT))
        {
            m_pUIManager->m_pCreditManager->ActivateGame();
            m_State = State::INTRO;
        }
        StartTimer(4);
        if (IsTimerFinished())
        {
            m_pUIManager->m_pCreditManager->ActivateGame();
            m_State = State::MENU;
        }
        break;
    case State::INTRO:
        if (m_pCutsceneManager->GetState() == Label::N_END)
        {
            ResetGame();
            m_State = State::GAME;
        }
        break;
    case State::GAME:
    case State::HURRY_UP:
    case State::BOSS:
    case State::STAGE_CLEAR:
        if (m_pPlayerManager->GetPlayer()->GetLives() == 0)
        {
            ResetTimer();
            m_State = State::GAME_OVER;
        }
        else if (m_pPlayerManager->GetPlayer()->GetState() == Player::State::DEAD and not m_pPlayerManager->GetPlayer()
            ->
            IsActive())
        {
            ResetTimer();
            m_State = State::FROZEN;
        }
        else if (m_pLevelManager->IsBossFight())
        {
            m_State = State::BOSS;
        }
        else if (m_pLevelManager->EndReached())
        {
            ResetTimer();
            m_State = State::END;
        }
        else if (m_pLevelManager->StageCleared())
        {
            m_State = State::STAGE_CLEAR;
        }
        break;
    case State::MAP:
        StartTimer(5);
        if (IsTimerFinished())
        {
            ResetTimer();
            m_State = State::GAME;
        }
        break;
    case State::END:
    case State::GAME_OVER:
        StartTimer(7);
        if (IsTimerFinished())
        {
            if (m_pGameController->m_pUIManager->m_pScoreManager->IsOnScoreboard())
            {
                m_State = State::SAVE_SCORE;
            }
            else
            {
                m_State = State::CONTINUE;
            }
        }
        break;
    case State::CONTINUE:
        StartTimer(10);
        if (m_pInputManager->IsPressed(Label::I_SELECT))
        {
            ResetGame();
            m_State = State::MAP;
        }
        else if (IsTimerFinished())
        {
            ResetGame();
            m_State = State::MENU;
        }
        break;
    case State::RANKING:
        break;
    case State::OUTRO:
        break;
    case State::SAVE_SCORE:
        if (m_pGameController->m_pUIManager->m_pInitialSaver->IsInitialSaved())
        {
            m_State = State::SAVE_END;
        }
        break;
    case State::SAVE_END:
        StartTimer(8);
        if (IsTimerFinished())
        {
            m_State = State::CONTINUE;
        }
        break;
    case State::FROZEN:
        StartTimer(4);
        if (IsTimerFinished())
        {
            ResetGame(true);
            m_State = State::MAP;
        }
        break;
    }
}

void Game::HandleCollisions()
{
    GameObject* pPlayer{m_pPlayerManager->GetPlayer()};
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto playerHandleCollision{[&](GameObject* pGameObject) { pPlayer->HandleCollision(pGameObject); }};
    static const auto objectHandleCollision{[&](GameObject* pGameObject) { pGameObject->HandleCollision(pPlayer); }};


    if (pPlayer->IsActive()) m_pLevelManager->GetKillZone()->HandleCollision(pPlayer);
    if (pPlayer->IsActive()) m_pLevelManager->GetLevel()->HandleCollision(pPlayer);

    // Player on enemies
    std::ranges::for_each(m_pEnemyManager->GetEnemies() | std::views::filter(isActive), playerHandleCollision);
    std::ranges::for_each(m_pEnemyManager->GetThrowables() | std::views::filter(isActive), playerHandleCollision);

    // Weapons on enemies and tombstones
    for (GameObject* weapon : m_pPlayerManager->GetThrowables())
    {
        if (weapon->IsActive())
        {
            for (GameObject* enemy : m_pEnemyManager->GetEnemies())
            {
                if (enemy->IsActive()) enemy->HandleCollision(weapon);
            }
            for (GameObject* pTombstone : m_pLevelManager->GetTombstones())
            {
                if (pTombstone->IsActive()) pTombstone->HandleCollision(weapon);
            }
#if TEST_OBJECT
            IEnemy* pTestEnemy{dynamic_cast<IEnemy*>(m_pTestObject)};
            if (pTestEnemy) pTestEnemy->HandleCollision(weapon);
#endif
        }
    }

    std::ranges::for_each(m_pCollectibleManager->GetCollectibles() | std::views::filter(isActive),
                          playerHandleCollision);
    std::ranges::for_each(m_pLevelManager->GetColliders() | std::views::filter(isActive), objectHandleCollision);

#if TEST_OBJECT
    if (m_pTestObject->IsActive()) pPlayer->HandleCollision(m_pTestObject);
#endif
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    m_pInputManager->ProcessKeyDownEvent(e);

    if (m_pInputManager->IsPressed(Label::I_QUIT))
    {
        std::exit(0); // Function is not thread-safe
    }
    if (m_pInputManager->IsPressed(Label::I_INFO))
    {
        PrintInfo();
    }
    if (m_pInputManager->IsPressed(Label::I_DEBUG))
    {
        Debug();
    }
    if (m_pInputManager->IsPressed(Label::I_INCREASE_VOLUME))
    {
        m_pSoundManager->IncreaseEffectMasterVolume();
        m_pSoundManager->IncreaseStreamMasterVolume();
    }
    if (m_pInputManager->IsPressed(Label::I_DECREASE_VOLUME))
    {
        m_pSoundManager->DecreaseEffectMasterVolume();
        m_pSoundManager->DecreaseStreamMasterVolume();
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    m_pInputManager->ProcessKeyUpEvent(e);
}

void Game::DrawGame() const
{
    glPushMatrix();
    m_pCameraManager->Transform(Label::C_ARTHUR);
    m_pLevelManager->DrawLevel();
    m_pLevelManager->DrawDoor();
    m_pLevelManager->DrawPlatform();
    m_pEnemyManager->DrawEnemies();
    m_pPlayerManager->DrawThrowables();
    m_pCollectibleManager->Draw();
    m_pPlayerManager->DrawPlayer();
    m_pLevelManager->DrawWaters();
    m_pLevelManager->DrawForeGround();
    m_pFXManager->Draw();
    m_pEnemyManager->DrawThrowables();
#if TEST_OBJECT
    if (m_pTestObject->IsVisible()) m_pTestObject->Draw();
#endif
#if DEBUG_COLLIDER
    m_pLevelManager->DrawKillZone();
    m_pLevelManager->DrawTombstones();
    m_pLevelManager->DrawLadders();
    m_pLevelManager->DrawColliders();
    m_pUIManager->m_pUI->DrawTextBonusKey();
#endif
    glPopMatrix();

    m_pUIManager->m_pHUD->Draw();
    m_pUIManager->m_pUI->DrawTextKey();

    if (m_State == State::GAME_OVER)
    {
        DrawGameOver();
    }
    // else if (m_State == State::SAVE_SCORE)
    // {
    //     DrawSaveScore();
    // }
}

void Game::DrawMenu() const
{
    m_pMenuManager->DrawMenu();
}

void Game::DrawIntro() const
{
    m_pCutsceneManager->DrawIntro();
}

void Game::DrawMap() const
{
    m_pMenuManager->DrawMap();
}

void Game::DrawGameOver() const
{
    m_pMenuManager->DrawGameOver();
}

void Game::DrawContinue() const
{
    m_pMenuManager->DrawContinue();
}

void Game::DrawEnd() const
{
    glPushMatrix();
    m_pCameraManager->Transform(Label::C_ARTHUR);
    m_pLevelManager->DrawLevel();
    m_pLevelManager->DrawDoor();
    m_pLevelManager->DrawForeGround();
    glPopMatrix();

    m_pUIManager->m_pUI->DrawTextTopRow();
    m_pUIManager->m_pUI->DrawPlayerScore();
    m_pUIManager->m_pUI->DrawTopScore();
}

void Game::DrawRanking() const
{
    m_pMenuManager->DrawRanking();
}

void Game::DrawOutro() const
{
}

void Game::DrawSaveScore() const
{
    glPushMatrix();
    m_pCameraManager->Transform(Label::C_ARTHUR);
    m_pLevelManager->DrawLevel();
    m_pLevelManager->DrawDoor();
    m_pLevelManager->DrawWaters();
    m_pLevelManager->DrawForeGround();
    glPopMatrix();

    m_pUIManager->m_pUI->DrawTextTopRow();
    m_pUIManager->m_pUI->DrawPlayerScore();
    m_pUIManager->m_pUI->DrawTopScore();
    m_pMenuManager->DrawSaveScore();
}

void Game::UpdateBoot(float elapsedSec)
{
    m_pBootManager->Update(elapsedSec);
}

void Game::UpdateGame(float elapsedSec)
{
    m_pGameController->m_pCameraManager->GetCamera()->SetBoundaries(
        m_pGameController->m_pLevelManager->GetLevel()->GetBoundaries());
    m_pLevelManager->Update(elapsedSec);
    m_pPlayerManager->Update(elapsedSec);
    m_pEnemyManager->SpawnEnemies();
    m_pEnemyManager->Update(elapsedSec);
    m_pCollectibleManager->Update(elapsedSec);
    m_pFXManager->Update(elapsedSec);
    m_pUIManager->m_pHUD->Update(elapsedSec);
    m_pUIManager->m_pScoreManager->Update(elapsedSec);

#if TEST_OBJECT
    if (m_pTestObject->IsActive())m_pTestObject->Update(elapsedSec);
#endif

    HandleCollisions();
    m_pCameraManager->DoFrustumCulling();
}

void Game::UpdateMenu(float elapsedSec)
{
    m_pMenuManager->UpdateMenu(elapsedSec);
}

void Game::UpdateIntro(float elapsedSec)
{
    m_pCutsceneManager->Update(elapsedSec);
}

void Game::UpdateMap(float elapsedSec)
{
    m_pMenuManager->UpdateMap(elapsedSec);
}

void Game::UpdateGameOver(float elapsedSec)
{
    m_pMenuManager->UpdateGameOver(elapsedSec);
}

void Game::UpdateContinue(float elapsedSec)
{
    m_pMenuManager->UpdateContinue(elapsedSec);
}

void Game::UpdateRanking(float elapsedSec)
{
    m_pMenuManager->UpdateRanking(elapsedSec);
}

void Game::UpdateOutro(float elapsedSec)
{
}

void Game::UpdateSaveScore(float elapsedSec)
{
    m_pMenuManager->UpdateSaveScore(elapsedSec);
}

void Game::LateUpdateGame(float elapsedSec)
{
    m_pLevelManager->LateUpdate(elapsedSec);
    m_pPlayerManager->LateUpdate(elapsedSec);
    m_pEnemyManager->LateUpdate(elapsedSec);
    m_pCollectibleManager->LateUpdate(elapsedSec);
    m_pFXManager->LateUpdate(elapsedSec);
    UpdateRemainingTime(121);
#if TEST_OBJECT
    m_pTestObject->LateUpdate(elapsedSec);
#endif
}

void Game::UpdateRemainingTime(int time)
{
    m_pGameController->m_pUIManager->m_pHUD->SetDigits(GetRemainingTimeDigits(time));
    if (GetRemainingTime() <= 15.0f)
    {
        m_State = State::HURRY_UP;
    }
    if (IsTimerFinished())
    {
        std::cout << "Time is up!\n";
        m_pPlayerManager->GetPlayer()->Die();
    }
}

void Game::PlayStream()
{
    switch (m_State)
    {
    case State::CREDIT:
        m_pGameController->m_pSoundManager->PlayStream(Game::Label::S_01_CREDIT, false);
        break;
    case State::INTRO:
        m_pSoundManager->PlayStream(Label::S_02_START_DEMO, false);
        break;
    case State::MAP:
        m_pSoundManager->PlayStream(Label::S_03_STAGE_INTRODUCTION_MAP, false);
        break;
    case State::MENU:
    case State::GAME:
        m_pSoundManager->PlayStream(Label::S_04_GROUND_BGM, true);
        break;
    case State::HURRY_UP:
        m_pGameController->m_pSoundManager->PlayStream(Label::S_05_HURRY_UP, false);
        break;
    case State::FROZEN:
        m_pSoundManager->PlayStream(Game::Label::S_06_PLAYER_OUT, false);
        break;
    case State::GAME_OVER:
        m_pSoundManager->PlayStream(Label::S_07_GAME_OVER, false);
        break;
    case State::BOSS:
        m_pSoundManager->PlayStream(Label::S_08_BOSS, true);
        break;
    case State::STAGE_CLEAR:
        m_pSoundManager->PlayStream(Label::S_09_STAGE_CLEAR, false);
        break;
    case State::SAVE_SCORE:
        if (m_pGameController->m_pUIManager->m_pScoreManager->HasTopScore())
        {
            m_pSoundManager->PlayStream(Label::S_10_1ST_PLACE_NAME_REGISTRATION, false);
        }
        else if (m_pGameController->m_pUIManager->m_pScoreManager->HasBelowTopScore())
        {
            m_pSoundManager->PlayStream(Label::S_12_BELOW_2ND_PLACE_NAME_REGISTRATION, false);
        }
        break;
    case State::SAVE_END:
        if (m_pGameController->m_pUIManager->m_pScoreManager->HasTopScore())
        {
           m_pGameController->m_pSoundManager->PlayStream(Game::Label::S_11_1ST_PLACE_ENTRY_END, false); 
        }
        else
        {
           m_pGameController->m_pSoundManager->PlayStream(Game::Label::S_13_BELOW_2ND_PLACE_ENTRY_END, false); 
        }
        break;
    case State::END:
        m_pSoundManager->PlayStream(Label::S_14_UNUSED_JINGLE, false);
        break;
    }
}

void Game::ResetGame(bool fromCheckpoint)
{
    m_pCutsceneManager->Reset();
    m_pCollectibleManager->Reset(fromCheckpoint);
    m_pEnemyManager->Reset(fromCheckpoint);
    m_pPlayerManager->Reset(fromCheckpoint);
    m_pLevelManager->Reset(fromCheckpoint);
    m_pMenuManager->Reset(fromCheckpoint);
    m_pCameraManager->Reset(fromCheckpoint);
    ResetTimer();
}

void Game::PrintInfo() const
{
    std::cout << "--- Controls ---" << std::endl;
    std::cout << " * Insert coin: " << m_pInputManager->ToString(Label::I_INSERT) << std::endl;
    std::cout << " * Start/Select: " << m_pInputManager->ToString(Label::I_SELECT) << std::endl;
    std::cout << " * Up: " << m_pInputManager->ToString(Label::I_UP) << std::endl;
    std::cout << " * Down: " << m_pInputManager->ToString(Label::I_DOWN) << std::endl;
    std::cout << " * Left: " << m_pInputManager->ToString(Label::I_LEFT) << std::endl;
    std::cout << " * Right: " << m_pInputManager->ToString(Label::I_RIGHT) << std::endl;
    std::cout << " * Jump: " << m_pInputManager->ToString(Label::I_JUMP) << std::endl;
    std::cout << " * Attack: " << m_pInputManager->ToString(Label::I_ATTACK) << std::endl;
    std::cout << " * Save state: " << m_pInputManager->ToString(Label::I_SAVE) << std::endl;
    std::cout << " * Load state: " << m_pInputManager->ToString(Label::I_LOAD) << std::endl;
    std::cout << " * Increase volume: " << m_pInputManager->ToString(Label::I_INCREASE_VOLUME) << std::endl;
    std::cout << " * Decrease volume: " << m_pInputManager->ToString(Label::I_DECREASE_VOLUME) << std::endl;
    std::cout << " * Debug: " << m_pInputManager->ToString(Label::I_DEBUG) << std::endl;
    std::cout << std::endl;
}

Game::State Game::GetState() const
{
    return m_State;
}

void Game::Debug() const
{
    const Player* pPlayer{m_pPlayerManager->GetPlayer()};
    std::cout << " -- PLAYER --" << std::endl;
    std::cout << " * Active: " << std::boolalpha << pPlayer->IsActive() << std::endl;
    std::cout << " * Visible: " << std::boolalpha << pPlayer->IsVisible() << std::endl;
    std::cout << " * Position: x - " << pPlayer->GetPosition<Point2f>() << std::endl;
    std::cout << " * Lives: " << pPlayer->GetLives() << std::endl;
    std::cout << " * HP: " << pPlayer->GetHP() << std::endl;
    std::cout << " * State: " << static_cast<int>(pPlayer->GetState()) << std::endl;
    std::cout << " * Weapon: " << static_cast<int>(pPlayer->GetWeapon()) << std::endl;
    std::cout << " * Score: " << pPlayer->GetScore() << std::endl;
    std::cout << " * Velocity: " << pPlayer->GetVelocity() << std::endl;
    std::cout << " * Shape: " << pPlayer->GetShape() << std::endl;
    std::cout << " * Collision box: " << pPlayer->GetCollider() << std::endl;
    std::cout << std::endl;
    std::cout << " --- GAME ---" << std::endl;
    std::cout << " * Game state: ";
    switch (m_State)
    {
    case State::BOOT: std::cout << "BOOT";
        break;
    case State::GAME: std::cout << "GAME";
        break;
    case State::MENU: std::cout << "MENU";
        break;
    case State::INTRO: std::cout << "INTRO";
        break;
    case State::MAP: std::cout << "MAP";
        break;
    case State::GAME_OVER: std::cout << "GAME_OVER";
        break;
    case State::CONTINUE: std::cout << "CONTINUE";
        break;
    case State::RANKING: std::cout << "RANKING";
        break;
    case State::OUTRO: std::cout << "OUTRO";
        break;
    case State::SAVE_SCORE: std::cout << "SAVE_SCORE";
        break;
    case State::SAVE_END: std::cout << "SAVE_END";
        break;
    case State::END: std::cout << "END";
        break;
    case State::BOSS: std::cout << "BOSS";
        break;
    case State::STAGE_CLEAR: std::cout << "STAGE_CLEAR";
        break;
    case State::CREDIT: std::cout << "CREDIT";
        break;
    case State::FROZEN: std::cout << "FROZEN";
        break;
    case State::HURRY_UP: std::cout << "HURRY_UP";
        break;
    }
    std::cout << std::endl;
    std::cout << " * Volume: " << m_pSoundManager->GetVolume() << std::endl;
    std::cout << std::endl;
}
