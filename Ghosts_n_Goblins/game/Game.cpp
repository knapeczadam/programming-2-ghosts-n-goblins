// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"

#include "BootManager.h"
#include "Camera.h"
#include "CollectibleManager.h"
#include "EnemyManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "PlayerManager.h"
#include "Texture.h"
#include "UIManager.h"
#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "characters/Zombie.h"
#include "engine/Clock.h"
#include "engine/SoundManager.h"
#include "engine/SpriteFactory.h"
#include "engine/TextureManager.h"
#include "engine/json.hpp"
#include "fx/FXManager.h"
#include "game/GameController.h"
#include "game/Macros.h"
#include "level/Level.h"
#include "ui/CreditManager.h"
#include "ui/HUD.h"
#include "ui/ScoreManager.h"
#include "utils.h"

#include <fstream>
#include <iostream>
#include <ranges>


Game::Game(const Window& window)
    : BaseGame{window}
      , m_Data{nullptr}
      , m_DataPath{"data.json"}
      , m_Labels{}
      , m_State{State::BOOT}
      , m_pBootManager{nullptr}
      , m_pCamera{nullptr}
      , m_pCollectibleManager{nullptr}
      , m_pEnemyManager{nullptr}
      , m_pFXManager{nullptr}
      , m_pGameController{nullptr}
      , m_pInputManager{nullptr}
      , m_pLevelManager{nullptr}
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
    m_pEnemyManager = new EnemyManager{m_pGameController};
    m_pLevelManager = new LevelManager{m_pGameController};
    m_pPlayerManager = new PlayerManager{m_pGameController};
    m_pUIManager = new UIManager{m_pGameController};

    // CAMERA - has to be after level and player initialization
    InitCamera();
#if TEST_OBJECT
    m_pTestObject = new Zombie{Point2f{200.f, 62.f}, m_pGameController};
#endif
}

Game::~Game()
{
    delete m_pCamera;

    delete m_pUIManager;
    delete m_pPlayerManager;
    delete m_pLevelManager;
    delete m_pEnemyManager;
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
    m_Labels["u_numbers"] = Label::U_NUMBERS;
    m_Labels["u_pin"] = Label::U_PIN;
    m_Labels["u_best_ranking"] = Label::U_BEST_RANKING;
    m_Labels["u_text_credit"] = Label::U_TEXT_CREDIT;
    m_Labels["u_text_game_over"] = Label::U_TEXT_GAME_OVER;
    m_Labels["u_text_initial"] = Label::U_TEXT_INITIAL;
    m_Labels["u_text_player_one_ready"] = Label::U_TEXT_PLAYER_ONE_READY;
    m_Labels["u_text_title"] = Label::U_TEXT_TITLE;
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

void Game::InitCamera()
{
    m_pCamera = new Camera{m_pGameController};
    m_pCamera->SetBoundaries(m_pLevelManager->GetLevel()->GetBoundaries());
}


void Game::UpdateState()
{
    if (m_pBootManager->GetState() == Label::B_END)
    {
        m_State = State::GAME;
    }
    else if (m_pUIManager->m_pCreditManager->GetCredits() and m_pGameController->m_pInputManager->IsPressed(
        Label::I_START))
    {
        m_State = State::INTRO;
    }
    // else if first cutscene is over -> game
    else if (m_pPlayerManager->GetPlayer()->GetLives() == 0 and m_pPlayerManager->GetPlayer()->GetScore() < m_pUIManager
        ->m_pScoreManager->GetHighScore())
    {
        m_State = State::GAME_OVER;
    }
    else if (m_pPlayerManager->GetPlayer()->GetLives() == 0 and m_pPlayerManager->GetPlayer()->GetScore() >=
        m_pUIManager->m_pScoreManager->GetHighScore())
    {
        m_State = State::SAVE_SCORE;
    }
    else if (m_pPlayerManager->GetPlayer()->GetLives() and m_pPlayerManager->GetPlayer()->GetHP() == 0)
    {
        m_State = State::MAP;
    }
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Draw() const
{
    // CLEAR
    ClearBackground();

    switch (m_State)
    {
    case State::BOOT:
        m_pBootManager->Draw();
        break;
    case State::MENU:
        DrawMenu();
        break;
    case State::INTRO:
        DrawIntro();
        break;
    case State::GAME:
        DrawGame();
        break;
    case State::MAP:
        DrawMap();
        break;
    case State::GAME_OVER:
        DrawGameOver();
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
    case State::SAVE_SCORE:
        DrawSaveScore();
        break;
    }
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
        UpdateMenu(elapsedSec);
        break;
    case State::INTRO:
        UpdateIntro(elapsedSec);
        break;
    case State::GAME:
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
}

void Game::DoCollisionTests()
{
    GameObject* pPlayer{m_pPlayerManager->GetPlayer()};
    static const auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static const auto playerHandleCollision{[&](GameObject* pGameObject) { pPlayer->HandleCollision(pGameObject); }};
    static const auto objectHandleCollision{[&](GameObject* pGameObject) { pGameObject->HandleCollision(pPlayer); }};


    // kill-z continuous collision detection
    m_pLevelManager->GetKillZone()->HandleCollision(pPlayer);

    if (pPlayer->IsActive()) m_pLevelManager->GetLevel()->HandleCollision(pPlayer);

    // Player on enemies
    std::ranges::for_each(m_pEnemyManager->GetEnemies() | std::views::filter(isActive), playerHandleCollision);
    std::ranges::for_each(m_pEnemyManager->GetThrowables() | std::views::filter(isActive), playerHandleCollision);

    // Weapons on game enemies and tombstones
    for (GameObject* weapon : m_pPlayerManager->GetThrowables())
    {
        if (weapon->IsActive())
        {
            // ENEMIES
            for (GameObject* enemy : m_pEnemyManager->GetEnemies())
            {
                if (enemy->IsActive()) enemy->HandleCollision(weapon);
            }
            // TOMBSTONE
            for (GameObject* pTombstone : m_pLevelManager->GetTombstones())
            {
                if (weapon->IsActive()) pTombstone->HandleCollision(weapon);
            }
#if TEST_OBJECT
            IEnemy* pTestEnemy{dynamic_cast<IEnemy*>(m_pTestObject)};
            if (pTestEnemy) pTestEnemy->HandleCollision(weapon);
#endif
        }
    }

    std::ranges::for_each(m_pCollectibleManager->GetCollectibles() | std::views::filter(isActive),
                          playerHandleCollision);
    std::ranges::for_each(m_pLevelManager->GetCollisionBoxes() | std::views::filter(isActive), objectHandleCollision);

    // const bool canClimb{
    //     std::ranges::any_of(m_Ladders, [&](const GameObject* pLadder) { return pLadder->IsOverlapping(pPlayer); })
    // };
    // pPlayer->CanClimb(canClimb);
    // std::ranges::for_each(m_Ladders, objectHandleCollision);

#if TEST_OBJECT
    if (m_pTestObject->IsActive()) pPlayer->HandleCollision(m_pTestObject);
#endif
}

void Game::LateUpdate(float elapsedSec)
{
    switch (m_State)
    {
    case State::GAME:
        LateUpdateGame(elapsedSec);
        break;
    }
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
        SoundManager::IncreaseMasterVolume();
    }
    if (m_pInputManager->IsPressed(Label::I_DECREASE_VOLUME))
    {
        SoundManager::DecreaseMasterVolume();
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    m_pInputManager->ProcessKeyUpEvent(e);
}

void Game::DrawGame() const
{
    // static lambda functions
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};


    glPushMatrix();
    m_pCamera->Transform(m_pPlayerManager->GetPlayer());
    m_pLevelManager->DrawLevel();
    m_pLevelManager->DrawPlatform();
    m_pEnemyManager->DrawEnemies();
    m_pPlayerManager->DrawThrowables();
    m_pCollectibleManager->Draw();
    m_pPlayerManager->DrawPlayer();
    m_pLevelManager->DrawWaters();
    m_pLevelManager->DrawForeGround();
    std::ranges::for_each(m_pFXManager->GetEffects() | std::views::filter(isVisible), draw);
    m_pEnemyManager->DrawThrowables();
#if TEST_OBJECT
    if (m_pTestObject->IsVisible()) m_pTestObject->Draw();
#endif
#if DEBUG_COLLISION
    m_pLevelManager->DrawKillZone();
    m_pLevelManager->DrawTombstones();
    m_pLevelManager->DrawLadders();
    m_pLevelManager->DrawCollisionBoxes();
#endif
    glPopMatrix();

#if DRAW_CENTER_GUIDE
    utils::SetColor(Color4f{1.0f, 1.0f, 1.0f, 0.5f});
    utils::DrawLine(Point2f{GetViewPort().width / 2, 0}, Point2f{GetViewPort().width / 2, GetViewPort().height});
    utils::DrawLine(Point2f{0, GetViewPort().height / 2}, Point2f{GetViewPort().width, GetViewPort().height / 2});
#endif
}

void Game::DrawMenu() const
{
}

void Game::DrawIntro() const
{
}

void Game::DrawMap() const
{
}

void Game::DrawGameOver() const
{
}

void Game::DrawContinue() const
{
}

void Game::DrawRanking() const
{
}

void Game::DrawOutro() const
{
}

void Game::DrawSaveScore() const
{
}

void Game::DrawDebug() const
{
}

void Game::UpdateBoot(float elapsedSec)
{
    m_pBootManager->Update(elapsedSec);
}

void Game::UpdateGame(float elapsedSec)
{
    m_pLevelManager->Update(elapsedSec);
    m_pPlayerManager->Update(elapsedSec);
    m_pEnemyManager->SpawnEnemies();
    m_pEnemyManager->Update(elapsedSec);
    m_pCollectibleManager->Update(elapsedSec);
    m_pFXManager->Update(elapsedSec);
    m_pUIManager->m_pHUD->Update(elapsedSec);

#if TEST_OBJECT
    if (m_pTestObject->IsActive())m_pTestObject->Update(elapsedSec);
#endif

    DoCollisionTests();
}

void Game::UpdateMenu(float elapsedSec)
{
}

void Game::UpdateIntro(float elapsedSec)
{
}

void Game::UpdateMap(float elapsedSec)
{
}

void Game::UpdateGameOver(float elapsedSec)
{
}

void Game::UpdateContinue(float elapsedSec)
{
}

void Game::UpdateRanking(float elapsedSec)
{
}

void Game::UpdateOutro(float elapsedSec)
{
}

void Game::UpdateSaveScore(float elapsedSec)
{
}

void Game::LateUpdateGame(float elapsedSec)
{
    switch (m_State)
    {
    case State::GAME:
        m_pPlayerManager->LateUpdate(elapsedSec);
        m_pEnemyManager->LateUpdate(elapsedSec);
        m_pCollectibleManager->LateUpdate(elapsedSec);
        m_pFXManager->LateUpdate(elapsedSec);
        m_pUIManager->UpdateRemainingTime();
        DoFrustumCulling();
        break;
    }
#if TEST_OBJECT
    m_pTestObject->LateUpdate(elapsedSec);
#endif
}

// TODO
void Game::PrintInfo() const
{
    std::cout << "--- Controls ---" << std::endl;
    std::cout << " * Insert coin: " << m_pInputManager->ToString(Label::I_SELECT) << std::endl;
    std::cout << " * Start: " << m_pInputManager->ToString(Label::I_START) << std::endl;
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

void Game::Debug() const
{
    const Player* pPlayer{m_pPlayerManager->GetPlayer()};
    std::cout << " -- Debug --" << std::endl;
    std::cout << " * Position: x - " << pPlayer->GetPosition<Point2f>() << std::endl;
    std::cout << " * Lives: " << pPlayer->GetLives() << std::endl;
    std::cout << " * HP: " << pPlayer->GetHP() << std::endl;
    std::cout << " * State: " << static_cast<int>(pPlayer->GetState()) << std::endl;
    std::cout << " * Weapon: " << static_cast<int>(pPlayer->GetWeapon()) << std::endl;
    std::cout << " * Score: " << pPlayer->GetScore() << std::endl;
    std::cout << " * Velocity: " << pPlayer->GetVelocity() << std::endl;
    std::cout << " * Shape: " << pPlayer->GetShape() << std::endl;
    std::cout << " * Collision box: " << pPlayer->GetCollisionBox() << std::endl;
    std::cout << std::endl;
}

void Game::DoFrustumCulling()
{
    static const auto isOutOfWindow{
        [&](const GameObject* pGameObject) { return m_pCamera->IsOutOfWindow(pGameObject); }
    };
    static const auto isAwake{[&](const IEnemy* pEnemy) { return pEnemy->IsAwake(); }};
    static const auto deactivate{
        [&](GameObject* pGameObject)
        {
            pGameObject->SetVisible(false);
            pGameObject->SetActive(false);
        }
    };

    std::ranges::for_each(m_pPlayerManager->GetThrowables() | std::views::filter(isOutOfWindow), deactivate);
    std::ranges::for_each(m_pEnemyManager->GetThrowables() | std::views::filter(isOutOfWindow), deactivate);

    for (GameObject* pGameObject : m_pEnemyManager->GetEnemies())
    {
        IEnemy* pEnemy{dynamic_cast<IEnemy*>(pGameObject)};
        if (pEnemy)
        {
            switch (pEnemy->GetLabel())
            {
            case Label::C_GREEN_MONSTER:
                pEnemy->SetAwake(false);
                break;
            }
        }
    }
#if TEST_OBJECT
    // if (isOutOfWindow(m_pTestObject)) deactivate(m_pTestObject);
#endif
}
