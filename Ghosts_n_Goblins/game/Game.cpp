// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Texture.h"
#include "utils.h"
#include "characters/GreenMonster.h"
#include "characters/IEnemy.h"
#include "characters/Player.h"
#include "collectibles/Coin.h"
#include "collectibles/MoneyBag.h"
#include "engine/Clock.h"
#include "engine/json.hpp"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "engine/TextureManager.h"
#include "game/Macros.h"
#include "level/KillZone.h"
#include "level/Ladder.h"
#include "level/Level.h"
#include "level/Platform.h"
#include "level/Tombstone.h"
#include "level/Water.h"
#include "ui/HUD.h"
#include "weapons/IThrowable.h"
#include "weapons/Lance.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "characters/Crow.h"


Game::Game(const Window& window)
    : BaseGame{window}
      , m_Enemies{}
      , m_Throwables{}
      , m_Waters{}
      , m_Tombstones{}
      , m_Collectibles{}
      , m_Ladders{}
      , m_pSpriteFactory{nullptr}
      , m_pTextureManager{nullptr}
      , m_pSoundManager{nullptr}
      , m_pPlayer{nullptr}
      , m_pForeground{nullptr}
      , m_pLevel{nullptr}
      , m_pKillZone{nullptr}
      , m_pPlatform{nullptr}
      , m_pCamera{nullptr}
      , m_pHUD{nullptr}
#if TEST_OBJECT
      , m_pTestObject{nullptr}
#endif
      , m_Data{nullptr}
      , m_DataPath{"../../Resources/data.json"}
      , m_Labels{}
      , m_AttackKeyReleased{true}
      , m_JumpKeyReleased{true}
      , m_BootIntervals{}
      , m_CurrBoot{Label::B_01}
      , m_Boot{false}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Cleanup()
{
    auto deleteGameObject = [](const GameObject* pGameObject) { delete pGameObject; };
    delete m_pCamera;
    delete m_pHUD;
    delete m_pForeground;
    delete m_pLevel;
    delete m_pKillZone;
    delete m_pPlatform;
    delete m_pSpriteFactory;
    delete m_pTextureManager;
    delete m_pPlayer;
    delete m_pSoundManager;
#if TEST_OBJECT
    delete m_pTestObject;
#endif

    std::ranges::for_each(m_Waters, deleteGameObject);
    std::ranges::for_each(m_Throwables, deleteGameObject);
    std::ranges::for_each(m_Enemies, deleteGameObject);
    std::ranges::for_each(m_Tombstones, deleteGameObject);
    std::ranges::for_each(m_Collectibles, deleteGameObject);
    std::ranges::for_each(m_Ladders, deleteGameObject);
}

void Game::Initialize()
{
    InitLabels();
    // Loading data from JSON
    LoadData();
    InitBootIntervals();

    // Order of initialization is important
    // 1. TEXTURE MANAGER
    // 2. SPRITE FACTORY
    m_pTextureManager = new TextureManager{m_Data, m_Labels};
    m_pSpriteFactory = new SpriteFactory{m_Data, m_pTextureManager, m_Labels};

    // SOUND
    m_pSoundManager = new SoundManager{m_Data, m_Labels};
    //m_pSoundManager->PlayStream(Label::S_04_GROUND_BGM, true);

    // LEVEL
    InitLevel();

    // COLLECTIBLES
    InitCollectibles();

    // PLAYER
    m_pPlayer = new Player{Player::GetSpawnPos(), m_pLevel, m_pSpriteFactory, m_pSoundManager};

    // CAMERA - has to be after level and player initialization
    InitCamera();

    // HUD
    m_pHUD = new HUD{m_pSpriteFactory->CreateSprite(Label::U_HUD), m_pPlayer, GetViewPort(), m_pSoundManager};

    // ENEMIES
    InitEnemies();

#if TEST_OBJECT
    m_pTestObject = new Crow{Point2f{600.f, 65.f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager};
#endif
}

void Game::InitLabels()
{
    // CHARACTERS
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

    // COLLECTIBLES
    m_Labels["o_coin"] = Label::O_COIN;
    m_Labels["o_key"] = Label::O_KEY;
    m_Labels["o_money_bag"] = Label::O_MONEY_BAG;
    m_Labels["o_necklace"] = Label::O_NECKLACE;
    m_Labels["o_pot"] = Label::O_POT;
    m_Labels["o_shield"] = Label::O_SHIELD;
    m_Labels["o_statue"] = Label::O_STATUE;
    m_Labels["o_yashichi"] = Label::O_YASHICHI;

    // FX
    m_Labels["f_fire"] = Label::F_FIRE;
    m_Labels["f_fx"] = Label::F_FX;
    m_Labels["f_vanish"] = Label::F_VANISH;

    // LEVEL
    m_Labels["l_door"] = Label::L_DOOR;
    m_Labels["l_foreground"] = Label::L_FOREGROUND;
    m_Labels["l_level"] = Label::L_LEVEL;
    m_Labels["l_platform"] = Label::L_PLATFORM;
    m_Labels["l_water"] = Label::L_WATER;

    // UI
    m_Labels["u_hud"] = Label::U_HUD;
    m_Labels["u_map"] = Label::U_MAP;
    m_Labels["u_pin"] = Label::U_PIN;

    // WEAPONS
    m_Labels["w_dagger"] = Label::W_DAGGER;
    m_Labels["w_eyeball"] = Label::W_EYEBALL;
    m_Labels["w_fireball_red_arremer"] = Label::W_FIREBALL_RED_ARREMER;
    m_Labels["w_fireball_unicorn"] = Label::W_FIREBALL_UNICORN;
    m_Labels["w_lance"] = Label::W_LANCE;
    m_Labels["w_spear"] = Label::W_SPEAR;
    m_Labels["w_spell"] = Label::W_SPELL;
    m_Labels["w_torch"] = Label::W_TORCH;

    // DEBUG
    m_Labels["d_level_debug"] = Label::D_LEVEL_DEBUG;
    m_Labels["d_fallback"] = Label::D_FALLBACK;

    // EFFECTS
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

    // STREAMS
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

    // BOOT
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
    m_pCamera = new Camera{GetViewPort(), m_pLevel, m_pPlayer};
}

void Game::InitBootIntervals()
{
    m_BootIntervals.push({Label::B_01, 1.16f});
    m_BootIntervals.push({Label::B_BLACK, 0.192f});
    m_BootIntervals.push({Label::B_02, 0.09613f});
    m_BootIntervals.push({Label::B_BLACK, 0.0961f});
    m_BootIntervals.push({Label::B_03, 0.08f});
    m_BootIntervals.push({Label::B_BLACK, 0.064f});
    m_BootIntervals.push({Label::B_04, 0.0961f});
    m_BootIntervals.push({Label::B_BLACK, 0.08f});
    m_BootIntervals.push({Label::B_05, 0.016f});
    m_BootIntervals.push({Label::B_06, 0.064f});
    m_BootIntervals.push({Label::B_BLACK, 0.08f});
    m_BootIntervals.push({Label::B_07, 0.07956f});
    m_BootIntervals.push({Label::B_BLACK, 0.38445f});
    m_BootIntervals.push({Label::B_08, 0.03201f});
    m_BootIntervals.push({Label::B_09, 0.01f});
    m_BootIntervals.push({Label::B_10, 0.016f});
    m_BootIntervals.push({Label::B_11, 0.016f});
    m_BootIntervals.push({Label::B_12, 0.016f});
    m_BootIntervals.push({Label::B_13, 0.016f});
    m_BootIntervals.push({Label::B_14, 0.016f});
    m_BootIntervals.push({Label::B_15, 0.032f});
    m_BootIntervals.push({Label::B_BLACK, 0.016f});
    m_BootIntervals.push({Label::B_09, 0.016f});
    m_BootIntervals.push({Label::B_BLACK, 0.16f});
    m_BootIntervals.push({Label::B_16, 0.096f});
    m_BootIntervals.push({Label::B_17, 0.14401f});
    m_BootIntervals.push({Label::B_18, 1.016f});
    m_BootIntervals.push({Label::B_19, 0.048f});
    m_BootIntervals.push({Label::B_20, 0.032f}); // edit
    m_BootIntervals.push({Label::B_21, 3.0f}); // blue
    m_BootIntervals.push({Label::B_22, 0.016f}); // blue
    m_BootIntervals.push({Label::B_23, 4.016f}); // blue
    m_BootIntervals.push({Label::B_24, 5.0f}); // best ranking
    m_BootIntervals.push({Label::B_25, 0.033f});
    m_BootIntervals.push({Label::B_END, 0.0f});
}

void Game::InitLevel()
{
    m_pPlatform = new Platform{Point2f{3295.0f, 28.0f}, m_pSpriteFactory, m_pSoundManager};
    m_pForeground = new GameObject{Label::L_FOREGROUND, m_pSpriteFactory};
    m_pKillZone = new KillZone{m_pTextureManager->GetTexture(Label::L_LEVEL)->GetWidth(), 20.0f};
    m_pLevel = new Level{m_pPlatform, m_Ladders, m_pSpriteFactory, m_pSoundManager};

    InitLadders();
    InitTombstones();
    InitWaters();
}

void Game::InitLadders()
{
    m_Ladders.insert(m_Ladders.end(), {
                         new Ladder{Rectf{1424.0f, 62.0f, 32.0f, 158.0f}},
                         new Ladder{Rectf{1808.0f, 62.0f, 32.0f, 158.0f}},
                         new Ladder{Rectf{2128.0f, 62.0f, 32.0f, 158.0f}},
                     });
}

void Game::InitTombstones()
{
    // BOTTOM
    m_Tombstones.insert(m_Tombstones.end(), {
                            new Tombstone{Rectf{83.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{499.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{817.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{1044.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{1490.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{1903.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{2191.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{2516.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{3028.0f, 66.0f, 30.0f, 30.0f}, m_pSoundManager},

                        });

    // TOP
    m_Tombstones.insert(m_Tombstones.end(), {
                            new Tombstone{Rectf{1519.0f, 221.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{1716.0f, 221.0f, 30.0f, 30.0f}, m_pSoundManager},
                            new Tombstone{Rectf{1909.0f, 221.0f, 30.0f, 30.0f}, m_pSoundManager},
                        });
}

void Game::InitWaters()
{
    m_Waters.insert(m_Waters.end(), {
                        new Water{Point2f{3295.0f, 0.0f}, m_pSpriteFactory},
                        new Water{Point2f{3903.0f, 0.0f}, 64.0f, m_pSpriteFactory},
                        new Water{Point2f{4031.0f, 0.0f}, 64.0f, m_pSpriteFactory},
                        new Water{Point2f{4927.0f, 0.0f}, 64.0f, m_pSpriteFactory},
                        new Water{Point2f{5566.0f, 0.0f}, 64.0f, m_pSpriteFactory},
                    });
}

void Game::InitCollectibles()
{
    InitCoins();
    InitMoneyBags();
}

void Game::InitCoins()
{
    m_Collectibles.insert(m_Collectibles.end(), {
                              new Coin{Point2f{720.0f, 62.0f}, m_pSpriteFactory},
                              new Coin{Point2f{6190.0f, 72.0f}, m_pSpriteFactory},
                              new Coin{Point2f{1232.0f, 223.0f}, m_pSpriteFactory},
                              new Coin{Point2f{1616.0f, 223.0f}, m_pSpriteFactory},
                              new Coin{Point2f{2158.0f, 223.0f}, m_pSpriteFactory}
                          });
}

void Game::InitMoneyBags()
{
    m_Collectibles.insert(m_Collectibles.end(), {
                              new MoneyBag{Point2f{2799.0f, 63.0f}, m_pSpriteFactory},
                              new MoneyBag{Point2f{4814.0f, 63.0f}, m_pSpriteFactory}
                          });
}

void Game::InitEnemies()
{
    InitBigMan();
    InitCrows();
    InitFlyingKnights();
    InitGreenMonsters();
    InitMagicians();
    InitRedArremer();
    InitWoodyPigs();
    InitZombies();
}

void Game::InitBigMan()
{
}

void Game::InitCrows()
{
    m_Enemies.insert(m_Enemies.end(), {
                         new Crow{Point2f{1505.0f, 100.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new Crow{Point2f{2210.0f, 100.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new Crow{Point2f{2526.0f, 100.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new Crow{Point2f{3035.0f, 102.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new Crow{Point2f{1724.0f, 262.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                     });
}

void Game::InitFlyingKnights()
{
}

void Game::InitGreenMonsters()
{
    // GREEN MONSTERS
    m_Enemies.insert(m_Enemies.end(), {
                         new GreenMonster{Point2f{4622.0f, 54.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new GreenMonster{Point2f{6190.0f, 54.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new GreenMonster{Point2f{1615.0f, 213.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                         new GreenMonster{Point2f{2191.0f, 213.0f}, m_pPlayer, m_pSpriteFactory, m_pSoundManager},
                     });
}

void Game::InitMagicians()
{
}

void Game::InitRedArremer()
{
}

void Game::InitWoodyPigs()
{
}

void Game::InitZombies()
{
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Draw() const
{
    // static lambda functions
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};

    // CLEAR
    ClearBackground();

    // BOOT
    if (m_Boot)
    {
        DrawBoot();
        return;
    }

    glPushMatrix();
    m_pCamera->Transform();
    m_pLevel->Draw();
    std::ranges::for_each(m_Enemies | std::views::filter(isVisible), draw);
    std::ranges::for_each(m_Throwables | std::views::filter(isVisible), draw);
    std::ranges::for_each(m_Collectibles | std::views::filter(isVisible), draw);
    m_pPlayer->Draw();
    std::ranges::for_each(m_Waters, draw);
    m_pForeground->Draw();
#if TEST_OBJECT
    if (m_pTestObject->IsVisible()) m_pTestObject->Draw();
#endif
#if DEBUG_COLLISION
    m_pKillZone->Draw();
    std::ranges::for_each(m_Tombstones, draw);
    std::ranges::for_each(m_Ladders, draw);
#endif
    glPopMatrix();

    // HUD
    m_pHUD->Draw();
}

void Game::Update(float elapsedSec)
{
    // static lambda functions
    static auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};

    Clock::Update(elapsedSec);

    // BOOT
    if (m_Boot)
    {
        Boot();
        return;
    }

    // LEVEL
    m_pLevel->Update(elapsedSec);
    std::ranges::for_each(m_Waters, update);

    // PLAYER
    if (m_pPlayer->IsActive()) m_pPlayer->Update(elapsedSec);

    // EMENIES
    // TODO set target
    std::ranges::for_each(m_Enemies | std::views::filter(isActive), update);

    // THROWABLES
    std::ranges::for_each(m_Throwables | std::views::filter(isActive), update);

    // COLLECTIBLES
    std::ranges::for_each(m_Collectibles | std::views::filter(isActive), update);

    m_pHUD->Update(elapsedSec);

#if TEST_OBJECT
    if (m_pTestObject->IsActive())m_pTestObject->Update(elapsedSec);
#endif

    // Do collision
    DoCollisionTests();
}

void Game::DoCollisionTests()
{
    // kill-z continuous collision detection
    m_pKillZone->HandleCollision(m_pPlayer);

    if (m_pPlayer->IsActive()) m_pLevel->HandleCollision(m_pPlayer);

    // Player on enemies
    for (GameObject* enemy : m_Enemies)
    {
        if (enemy->IsActive())
        {
            m_pPlayer->HandleCollision(enemy);
        }
    }

    // Weapons on game enemies and tombstones
    for (GameObject* weapon : m_Throwables)
    {
        if (weapon->IsActive())
        {
            // ENEMIES
            for (GameObject* enemy : m_Enemies)
            {
                if (enemy->IsActive()) enemy->HandleCollision(weapon);
            }
            // TOMBSTONE
            for (GameObject* pTombstone : m_Tombstones)
            {
                if (weapon->IsActive()) pTombstone->HandleCollision(weapon);
            }
        }
    }

    for (GameObject* pCollectible : m_Collectibles)
    {
        if (pCollectible->IsActive()) m_pPlayer->HandleCollision(pCollectible);
    }

    const bool canClimb{
        std::ranges::any_of(m_Ladders, [&](const GameObject* pLadder) { return pLadder->IsOverlapping(m_pPlayer); })
    };
    m_pPlayer->CanClimb(canClimb);
    std::ranges::for_each(m_Ladders, [&](GameObject* pLadder) { pLadder->HandleCollision(m_pPlayer); });

#if TEST_OBJECT
    if (m_pTestObject->IsActive()) m_pPlayer->HandleCollision(m_pTestObject);
#endif
}

void Game::LateUpdate(float elapsedSec)
{
    // static lambda functions
    static auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};

    m_pPlayer->LateUpdate(elapsedSec);

    std::ranges::for_each(m_Waters, lateUpdate);
    std::ranges::for_each(m_Enemies, lateUpdate);
    std::ranges::for_each(m_Throwables, lateUpdate);
    std::ranges::for_each(m_Collectibles, lateUpdate);

    DeactivateEnemiesOutOfView();
    DeactivateThrowablesOutOfView();

    UpdateRemainingTime();

#if TEST_OBJECT
    m_pTestObject->LateUpdate(elapsedSec);
#endif
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
    case SDLK_x:
        if (m_AttackKeyReleased)
        {
            m_pPlayer->Attack(m_Throwables, m_pSpriteFactory);
            m_AttackKeyReleased = false;
        }
        break;
    case SDLK_s:
        if (m_JumpKeyReleased)
        {
            m_pPlayer->CanJump(true);
            m_JumpKeyReleased = false;
        }
        break;
    case SDLK_ESCAPE:
        Cleanup();
        std::exit(0); // Function is not thread-safe
        break;
    case SDLK_i:
        PrintInfo();
        break;
    case SDLK_d:
        Debug();
        break;
    case SDLK_u:
        SoundStream::SetVolume(SoundStream::GetVolume() + 1);
        break;
    case SDLK_j:
        SoundStream::SetVolume(SoundStream::GetVolume() - 1);
        break;
    }
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    switch (e.keysym.sym)
    {
    case SDLK_x:
        m_AttackKeyReleased = true;
        break;
    case SDLK_s:
        m_JumpKeyReleased = true;
        break;
    }
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::DrawBoot() const
{
    if (m_CurrBoot == Label::B_END) return;
    m_pSpriteFactory->CreateSprite(m_CurrBoot)->Draw();
}

void Game::Boot()
{
    StartTimer(m_BootIntervals.front().second);
    m_CurrBoot = m_BootIntervals.front().first;
    if (m_CurrBoot == Label::B_END)
    {
        m_Boot = false;
        return;
    }
    if (IsTimerFinished())
    {
        m_BootIntervals.pop();
    }
}

// TODO
void Game::PrintInfo() const
{
    std::cout << "Game info:" << std::endl;
}

void Game::Debug() const
{
    std::cout << "Game debug:" << std::endl;
    std::cout << " -- Player --" << std::endl;
    std::cout << "Position: x - " << m_pPlayer->GetPosition<Point2f>().x << " y - " << m_pPlayer->GetPosition<Point2f>()
        .y << std::endl;
}

void Game::DeactivateEnemiesOutOfView()
{
    for (GameObject* pEnemy : m_Enemies)
    {
        IEnemy* pIEnemy{dynamic_cast<IEnemy*>(pEnemy)};
        if (pIEnemy->IsAwake() and m_pCamera->IsOutOfWindow(pEnemy))
        {
            pEnemy->SetActive(false);
        }
    }
}

void Game::DeactivateThrowablesOutOfView()
{
    for (GameObject* weapon : m_Throwables)
    {
        if (weapon->IsActive() and not m_pCamera->IsOutOfWindow(weapon))
        {
            weapon->SetActive(false);
            weapon->SetVisible(false);
        }
    }
}

void Game::UpdateRemainingTime()
{
    StartTimer(120);
    const int seconds{GetSeconds()};
    const int minutes{GetMinutes()};

    int firstDigit, secondDigit, thirdDigit;
    firstDigit = minutes;
    if (seconds > 9)
    {
        secondDigit = seconds / 10;
        thirdDigit = seconds % 10;
    }
    else
    {
        secondDigit = 0;
        thirdDigit = seconds;
    }
    if (GetRemainingTime() <= 15.0f)
    {
        m_pSoundManager->PlayStream(Game::Label::S_05_HURRY_UP, false);
    }
    m_pHUD->SetFirstDigit(firstDigit);
    m_pHUD->SetSecondDigit(secondDigit);
    m_pHUD->SetThirdDigit(thirdDigit);

    if (IsTimerFinished())
    {
        std::cout << "Time is up!\n";
        // TODO: Game over
    }
}
