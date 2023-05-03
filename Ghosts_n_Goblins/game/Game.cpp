// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Texture.h"
#include "utils.h"
#include "characters/Player.h"
#include "weapons/IThrowable.h"
#include "engine/json.hpp"
#include "engine/SpriteFactory.h"
#include "engine/TextureManager.h"
#include "level/Level.h"
#include "level/KillZone.h"
#include "level/Platform.h"
#include "level/Tombstone.h"
#include "level/IClimable.h"
#include "ui/HUD.h"
#include "game/Macros.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "characters/IEnemy.h"
#include "engine/Clock.h"
#include "engine/SoundManager.h"
#include "engine/Sprite.h"
#include "level/Ladder.h"
#include "level/Water.h"
#include "weapons/Dagger.h"
#include "weapons/Lance.h"
#include "weapons/Torch.h"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_Enemies{}
      , m_Throwables{}
      , m_Waters{}
      , m_Tombstones{}
      , m_Collectibles{}
      , m_Ladders{}
      , m_pSpriteFactory{}
      , m_pTextureManager{}
      , m_pSoundManager{}
      , m_pPlayer{}
      , m_pForeground{}
      , m_pLevel{}
      , m_pKillZone{}
      , m_pPlatform{}
      , m_pCamera{}
      , m_pHUD{}
      , m_pTestGameObject{}
      , m_Data{}
      , m_DataPath{"../../Resources/data.json"}
      , m_Labels{}
      , m_AttackKeyReleased{true}
      , m_JumpKeyReleased{true}
      , m_BootIntervals{}
      , m_BootCounter{1}
      , m_MaxBootCount{20}
      , m_Boot{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Cleanup()
{
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
    delete m_pTestGameObject;

    std::ranges::for_each(m_Waters, [](const Water* pWater) { delete pWater; });
    std::ranges::for_each(m_Throwables, [](const IThrowable* pThrowable) { delete pThrowable; });
    std::ranges::for_each(m_Enemies, [](const IEnemy* pEnemy) { delete pEnemy; });
    std::ranges::for_each(m_Tombstones, [](const Tombstone* pTombstone) { delete pTombstone; });
    std::ranges::for_each(m_Collectibles, [](const ICollectible* pCollectible) { delete pCollectible; });
    std::ranges::for_each(m_Ladders, [](const IClimable* pLadder) { delete pLadder; });
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

    // LEVEL
    m_pPlatform = new Platform{m_pSpriteFactory->CreateSprite(Label::L_PLATFORM), Point2f{3295.0f, 26.0f}};
    m_pForeground = new GameObject{Label::L_FOREGROUND, m_pSpriteFactory->CreateSprite(Label::L_FOREGROUND), false};
    m_pKillZone = new KillZone{m_pTextureManager->GetTexture(Label::L_LEVEL)->GetWidth(), 20.0f};
    m_pLevel = new Level{m_pSpriteFactory->CreateSprite(Label::L_LEVEL), m_pPlatform};
    InitWaters();
    InitTombstones();
    InitLadders();

    // CAMERA - has to be after level initialization
    m_pCamera = new Camera{};
    InitCamera();

    // PLAYER
    m_pPlayer = new Player{m_pSpriteFactory->CreateSprite(Label::C_ARTHUR), Player::GetSpawnPos(), m_pLevel};

    // HUD
    m_pHUD = new HUD{m_pSpriteFactory->CreateSprite(Label::U_HUD), m_pPlayer, GetViewPort()};

    // TEST GAME OBJECT
    m_pTestGameObject = new Lance{m_pSpriteFactory->CreateSprite(Label::W_LANCE), Point2f{260.f, 65.f}, false, true};

    // GAME OBJECTS
    //m_Enemies.push_back();

    // SOUND
    m_pSoundManager = new SoundManager{m_Data, m_Labels};
    //m_pSoundManager->PlayStream(Label::S_04_GROUND_BGM, true);
}

void Game::InitLabels()
{
    // CHARACTERS
    m_Labels["c_arthur"] = Label::C_ARTHUR;
    m_Labels["c_big_man"] = Label::C_BIG_MAN;
    m_Labels["c_crow"] = Label::C_CROW;
    m_Labels["c_flying_knight"] = Label::C_FLYING_KNIGHT;
    m_Labels["c_green_monster"] = Label::C_GREEN_MONSTER;
    m_Labels["c_magician"] = Label::C_MAGICIAN;
    m_Labels["c_princess"] = Label::C_PRINCESS;
    m_Labels["c_red_arremer"] = Label::C_RED_ARREMER;
    m_Labels["c_satan"] = Label::C_SATAN;
    m_Labels["c_woody_pig"] = Label::C_WOODY_PIG;
    m_Labels["c_zombie"] = Label::C_ZOMBIE;

    // COLLECTIBLES
    m_Labels["o_basket"] = Label::O_BASKET;
    m_Labels["o_bust"] = Label::O_BUST;
    m_Labels["o_coin"] = Label::O_COIN;
    m_Labels["o_key"] = Label::O_KEY;
    m_Labels["o_money_bag"] = Label::O_MONEY_BAG;
    m_Labels["o_necklace"] = Label::O_NECKLACE;
    m_Labels["o_shield"] = Label::O_SHIELD;
    m_Labels["o_star"] = Label::O_STAR;

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
    m_Labels["w_lance"] = Label::W_LANCE;
    m_Labels["w_spear"] = Label::W_SPEAR;
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

void Game::InitWaters()
{
    Water* water1 = new Water{m_pSpriteFactory->CreateSprite(Label::L_WATER), Point2f{3295.0f, 0.0f}};
    Water* water2 = new Water{m_pSpriteFactory->CreateSprite(Label::L_WATER), Point2f{3903.0f, 0.0f}, 64.0f};
    Water* water3 = new Water{m_pSpriteFactory->CreateSprite(Label::L_WATER), Point2f{4031.0f, 0.0f}, 64.0f};
    Water* water4 = new Water{m_pSpriteFactory->CreateSprite(Label::L_WATER), Point2f{4927.0f, 0.0f}, 64.0f};
    Water* water5 = new Water{m_pSpriteFactory->CreateSprite(Label::L_WATER), Point2f{5566.0f, 0.0f}, 64.0f};
    m_Waters.push_back(water1);
    m_Waters.push_back(water2);
    m_Waters.push_back(water3);
    m_Waters.push_back(water4);
    m_Waters.push_back(water5);
}

void Game::InitTombstones()
{
    // BOTTOM
    Tombstone* tombstone2 = new Tombstone{Rectf{83.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone3 = new Tombstone{Rectf{499.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone4 = new Tombstone{Rectf{817.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone5 = new Tombstone{Rectf{1044.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone6 = new Tombstone{Rectf{1490.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone7 = new Tombstone{Rectf{1903.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone8 = new Tombstone{Rectf{2191.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone9 = new Tombstone{Rectf{2516.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone10 = new Tombstone{Rectf{3028.0f, 66.0f, 30.0f, 30.0f}};

    // TOP
    Tombstone* tombstone11 = new Tombstone{Rectf{1519.0f, 221.0f, 30.0f, 30.0f}};
    Tombstone* tombstone12 = new Tombstone{Rectf{1716.0f, 221.0f, 30.0f, 30.0f}};
    Tombstone* tombstone13 = new Tombstone{Rectf{1909.0f, 221.0f, 30.0f, 30.0f}};

    m_Tombstones.push_back(tombstone2);
    m_Tombstones.push_back(tombstone3);
    m_Tombstones.push_back(tombstone4);
    m_Tombstones.push_back(tombstone5);
    m_Tombstones.push_back(tombstone6);
    m_Tombstones.push_back(tombstone7);
    m_Tombstones.push_back(tombstone8);
    m_Tombstones.push_back(tombstone9);
    m_Tombstones.push_back(tombstone10);
    m_Tombstones.push_back(tombstone11);
    m_Tombstones.push_back(tombstone12);
    m_Tombstones.push_back(tombstone13);
}

void Game::InitCamera() const
{
    m_pCamera->SetLevelBoundaries(m_pLevel->GetBoundaries());
    m_pCamera->SetWidth(GetViewPort().width);
    m_pCamera->SetHeight(GetViewPort().height);
}

void Game::InitBootIntervals()
{
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
    m_BootIntervals.push(0.5f);
}

void Game::InitLadders()
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
    static auto throwableToGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto enemyToGameObject{[](IEnemy* pEnemy) { return dynamic_cast<GameObject*>(pEnemy); }};
    static auto collectibleToGameObject{
        [](ICollectible* pCollectible) { return dynamic_cast<GameObject*>(pCollectible); }
    };
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};

    // CLEAR
    ClearBackground();

    // BOOT
    if (m_Boot)
    {
        DrawBoot();
        if (m_BootCounter < m_MaxBootCount) return;
    }

    glPushMatrix();
    m_pCamera->Transform(m_pPlayer->GetShape());
    m_pLevel->Draw();
    std::ranges::for_each(m_Enemies | std::views::transform(enemyToGameObject) | std::views::filter(isVisible), draw);
    std::ranges::for_each(m_Throwables | std::views::transform(throwableToGameObject) | std::views::filter(isVisible),
                          draw);
    std::ranges::for_each(
        m_Collectibles | std::views::transform(collectibleToGameObject) | std::views::filter(isVisible), draw);
    m_pPlayer->Draw();
    std::ranges::for_each(m_Waters, [](const Water* pWater) { pWater->Draw(); });
    m_pForeground->Draw();
    // Test object
    if (m_pTestGameObject->IsVisible()) m_pTestGameObject->Draw();
#if DEBUG_COLLISION
    m_pKillZone->Draw();
    std::ranges::for_each(m_Tombstones, [](const Tombstone* pTombstone) { pTombstone->Draw(); });
#endif
    glPopMatrix();

    // HUD
    m_pHUD->Draw();
}

void Game::Update(float elapsedSec)
{
    // static lambda functions
    static auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static auto throwableToGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto enemyToGameObject{[](IEnemy* pEnemy) { return dynamic_cast<GameObject*>(pEnemy); }};
    static auto collectibleToGameObject{
        [](ICollectible* pCollectible) { return dynamic_cast<GameObject*>(pCollectible); }
    };
    static auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};

    Clock::Update(elapsedSec);

    // BOOT
    if (m_Boot)
    {
        Boot();
        if (m_BootCounter < m_MaxBootCount) return;
    }

    // LEVEL
    m_pLevel->Update(elapsedSec);
    std::ranges::for_each(m_Waters, [&](Water* pWater) { pWater->Update(elapsedSec); });

    // PLAYER
    if (m_pPlayer->IsActive()) m_pPlayer->Update(elapsedSec);

    // EMENIES
    // TODO set target
    std::ranges::for_each(m_Enemies | std::views::transform(enemyToGameObject) | std::views::filter(isActive), update);

    // THROWABLES
    std::ranges::for_each(m_Throwables | std::views::transform(throwableToGameObject) | std::views::filter(isActive),
                          update);

    // COLLECTIBLES
    std::ranges::for_each(
        m_Collectibles | std::views::transform(collectibleToGameObject) | std::views::filter(isActive), update);

    m_pHUD->Update(elapsedSec);

    // Test object
    if (m_pTestGameObject->IsActive())m_pTestGameObject->Update(elapsedSec);

    // Do collision
    DoCollisionTests();
}

void Game::DoCollisionTests()
{
    // kill-z continuous collision detection
    m_pKillZone->HandleCollision(m_pPlayer);

    if (m_pPlayer->IsActive()) m_pLevel->HandleCollision(m_pPlayer);

    // Player on enemies
    for (IEnemy* pGameObject : m_Enemies)
    {
        GameObject* enemy = dynamic_cast<GameObject*>(pGameObject);
        if (enemy->IsActive())
        {
            m_pPlayer->HandleCollision(enemy);
        }
    }

    // Weapons on game enemies and tombstones
    for (IThrowable* pThrowable : m_Throwables)
    {
        GameObject* weapon = dynamic_cast<GameObject*>(pThrowable);
        if (weapon->IsActive())
        {
            // ENEMIES
            for (IEnemy* pGameObject : m_Enemies)
            {
                GameObject* enemy = dynamic_cast<GameObject*>(pGameObject);
                if (enemy->IsActive()) weapon->HandleCollision(enemy);
            }
            // TOMBSTONE
            for (Tombstone* pTombstone : m_Tombstones)
            {
                if (weapon->IsActive()) pTombstone->HandleCollision(weapon);
            }
        }
    }
    for (IClimable* pClimable : m_Ladders)
    {
        Ladder* ladder = dynamic_cast<Ladder*>(pClimable);
        m_pPlayer->HandleCollision(ladder);
    }

    // Test object
    m_pPlayer->HandleCollision(m_pTestGameObject);
}

void Game::LateUpdate(float elapsedSec)
{
    // static lambda functions
    static auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    static auto throwableToGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto enemyToGameObject{[](IEnemy* pEnemy) { return dynamic_cast<GameObject*>(pEnemy); }};
    static auto collectibleToGameObject{
        [](ICollectible* pCollectible) { return dynamic_cast<GameObject*>(pCollectible); }
    };

    m_pPlayer->LateUpdate(elapsedSec);

    std::ranges::for_each(m_Waters, [&](Water* pWater) { pWater->LateUpdate(elapsedSec); });
    std::ranges::for_each(m_Enemies | std::views::transform(enemyToGameObject), lateUpdate);
    std::ranges::for_each(m_Throwables | std::views::transform(throwableToGameObject), lateUpdate);
    std::ranges::for_each(m_Collectibles | std::views::transform(collectibleToGameObject), lateUpdate);

    // Test object
    m_pTestGameObject->LateUpdate(elapsedSec);
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
    if (m_BootCounter > m_MaxBootCount) return;
    std::string prefix{"b_"};
    if (m_BootCounter < 10) prefix += "0";
    Label label{m_Labels.at(prefix + std::to_string(m_BootCounter))};
    m_pSpriteFactory->CreateSprite(label)->Draw();
}

void Game::Boot()
{
    if (m_BootCounter > m_MaxBootCount) return;
    StartTimer(m_BootIntervals.front());
    if (IsTimerFinished())
    {
        m_BootIntervals.pop();
        ++m_BootCounter;
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
