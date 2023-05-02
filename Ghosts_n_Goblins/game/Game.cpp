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
#include "ui/HUD.h"
#include "game/Macros.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "characters/IEnemy.h"
#include "engine/Clock.h"
#include "level/Water.h"
#include "weapons/Dagger.h"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_GameObjects{}
      , m_Throwables{}
      , m_Waters{}
      , m_pSpriteFactory{}
      , m_pTextureManager{}
      , m_pPlayer{}
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

    std::ranges::for_each(m_Waters, [](const Water* pWater) { delete pWater; });
    std::ranges::for_each(m_Throwables, [](const IThrowable* pThrowable) { delete pThrowable; });
    std::ranges::for_each(m_GameObjects, [](const GameObject* pGameObject) { delete pGameObject; });
    std::ranges::for_each(m_Tombstones, [](const Tombstone* pTombstone) { delete pTombstone; });
}

void Game::Initialize()
{
    InitLabels();
    // Loading data from JSON
    LoadData();

    // Order of initialization is important
    // 1. TEXTURE MANAGER
    // 2. SPRITE FACTORY
    m_pTextureManager = new TextureManager{m_Data, m_Labels};
    m_pSpriteFactory = new SpriteFactory{m_Data, m_pTextureManager, m_Labels};

    // LEVEL
    m_pPlatform = new Platform{m_pSpriteFactory->CreateSprite(Label::PLATFORM), Point2f{3555.0f, 30.0f}};
    m_pForeground = new GameObject{Label::FOREGROUND, m_pSpriteFactory->CreateSprite(Label::FOREGROUND), false};
    m_pKillZone = new KillZone{m_pTextureManager->GetTexture(Label::LEVEL)->GetWidth(), 20.0f};
    m_pLevel = new Level{m_pSpriteFactory->CreateSprite(Label::LEVEL), m_pPlatform};
    InitWaters();
    InitTombstones();

    // CAMERA - has to be after level initialization
    m_pCamera = new Camera{};
    InitCamera();

    // PLAYER
    m_pPlayer = new Player{m_pSpriteFactory->CreateSprite(Label::ARTHUR), Player::GetSpawnPos(), m_pLevel};

    // HUD
    m_pHUD = new HUD{m_pSpriteFactory->CreateSprite(Label::HUD), m_pPlayer, GetViewPort()};

    // TEST GAME OBJECT
    m_pTestGameObject = new Dagger{m_pSpriteFactory->CreateSprite(Label::DAGGER), Point2f{218.f, 65.f}, false};
    m_pTestGameObject->SetActive(false);

    // GAME OBJECTS
    m_GameObjects.push_back(m_pTestGameObject);
}

void Game::InitLabels()
{
    // CHARACTERS
    m_Labels["arthur"] = Label::ARTHUR;
    m_Labels["big_man"] = Label::BIG_MAN;
    m_Labels["crow"] = Label::CROW;
    m_Labels["flying_knight"] = Label::FLYING_KNIGHT;
    m_Labels["green_monster"] = Label::GREEN_MONSTER;
    m_Labels["magician"] = Label::MAGICIAN;
    m_Labels["princess"] = Label::PRINCESS;
    m_Labels["red_arremer"] = Label::RED_ARREMER;
    m_Labels["satan"] = Label::SATAN;
    m_Labels["woody_pig"] = Label::WOODY_PIG;
    m_Labels["zombie"] = Label::ZOMBIE;

    // COLLECTIBLES
    m_Labels["basket"] = Label::BASKET;
    m_Labels["coins"] = Label::COINS;
    m_Labels["money_bag"] = Label::MONEY_BAG;
    m_Labels["necklace"] = Label::NECKLACE;
    m_Labels["shield"] = Label::SHIELD;

    // FX
    m_Labels["fire"] = Label::FIRE;
    m_Labels["fx"] = Label::FX;
    m_Labels["vanish"] = Label::VANISH;

    // LEVEL
    m_Labels["door"] = Label::DOOR;
    m_Labels["foreground"] = Label::FOREGROUND;
    m_Labels["level"] = Label::LEVEL;
    m_Labels["platform"] = Label::PLATFORM;
    m_Labels["water"] = Label::WATER;

    // UI
    m_Labels["hud"] = Label::HUD;
    m_Labels["map"] = Label::MAP;
    m_Labels["pin"] = Label::PIN;

    // WEAPONS
    m_Labels["dagger"] = Label::DAGGER;
    m_Labels["lance"] = Label::LANCE;
    m_Labels["spear"] = Label::SPEAR;
    m_Labels["torch"] = Label::TORCH;

    // DEBUG
    m_Labels["level_debug"] = Label::LEVEL_DEBUG;
    m_Labels["fallback"] = Label::FALLBACK;

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
    Water* water1 = new Water{m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{3550.0f, 0.0f}};
    Water* water2 = new Water{m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{4205.0f, 0.0f}, 64.0f};
    Water* water3 = new Water{m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{4343.0f, 0.0f}, 64.0f};
    Water* water4 = new Water{m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{5308.0f, 0.0f}, 64.0f};
    Water* water5 = new Water{m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{5997.0f, 0.0f}, 64.0f};
    m_Waters.push_back(water1);
    m_Waters.push_back(water2);
    m_Waters.push_back(water3);
    m_Waters.push_back(water4);
    m_Waters.push_back(water5);
}

void Game::InitTombstones()
{
    // BOTTOM
    // Tombstone* tombstone1 = new Tombstone{Rectf{86.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone2 = new Tombstone{Rectf{90.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone3 = new Tombstone{Rectf{535.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone4 = new Tombstone{Rectf{884.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone5 = new Tombstone{Rectf{1124.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone6 = new Tombstone{Rectf{1608.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone7 = new Tombstone{Rectf{2056.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone8 = new Tombstone{Rectf{2365.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone9 = new Tombstone{Rectf{2707.0f, 66.0f, 30.0f, 30.0f}};
    Tombstone* tombstone10 = new Tombstone{Rectf{3261.0f, 66.0f, 30.0f, 30.0f}};

    // TOP
    Tombstone* tombstone11 = new Tombstone{Rectf{1643.0f, 238.0f, 30.0f, 30.0f}};
    Tombstone* tombstone12 = new Tombstone{Rectf{1849.0f, 238.0f, 30.0f, 30.0f}};
    Tombstone* tombstone13 = new Tombstone{Rectf{2056.0f, 238.0f, 30.0f, 30.0f}};

    // m_Tombstones.push_back(tombstone1);
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

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Draw() const
{
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto toGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto isVisible{[](const GameObject* pGameObject) { return pGameObject->IsVisible(); }};

    ClearBackground();

    glPushMatrix();
    m_pCamera->Transform(m_pPlayer->GetShape());
    m_pLevel->Draw();
    std::ranges::for_each(m_GameObjects | std::views::filter(isVisible), draw);
    std::ranges::for_each(m_Throwables | std::views::transform(toGameObject) | std::views::filter(isVisible), draw);
    m_pPlayer->Draw();
    std::ranges::for_each(m_Waters, [](const Water* pWater) { pWater->Draw(); });
    m_pForeground->Draw();
#if DEBUG_COLLISION
    m_pKillZone->Draw();
    std::ranges::for_each(m_Tombstones, [](const Tombstone* pTombstone) { pTombstone->Draw(); });
#endif
    glPopMatrix();

    m_pHUD->Draw();
}

void Game::Update(float elapsedSec)
{
    Clock::Update(elapsedSec);

    // Update game objects
    m_pLevel->Update(elapsedSec);
    std::ranges::for_each(m_Waters, [&](Water* pWater) { pWater->Update(elapsedSec); });
    if (m_pPlayer->IsActive()) m_pPlayer->Update(elapsedSec);

    static auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static auto toGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto update{[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    std::ranges::for_each(m_GameObjects | std::views::filter(isActive), update);
    std::ranges::for_each(m_Throwables | std::views::transform(toGameObject) | std::views::filter(isActive), update);

    m_pHUD->Update(elapsedSec);
    // TODO set target

    // Do collision
    DoCollisionTests();
}

void Game::DoCollisionTests()
{
    m_pKillZone->HandleCollision(m_pPlayer);
    if (m_pPlayer->IsActive()) m_pLevel->HandleCollision(m_pPlayer);

    // Game objects on player
    for (GameObject* pGameObject : m_GameObjects)
    {
        if (pGameObject->IsActive())
        {
            m_pPlayer->HandleCollision(pGameObject);
        }
    }

    // Weapons on game objects and tombstones
    for (IThrowable* pThrowable : m_Throwables)
    {
        GameObject* weapon = dynamic_cast<GameObject*>(pThrowable);
        if (weapon->IsActive())
        {
            // GAME OBJECTS
            for (GameObject* pGameObject : m_GameObjects)
            {
                if (pGameObject->IsActive()) weapon->HandleCollision(pGameObject);
            }
            // TOMBSTONE
            for (Tombstone* pTombstone : m_Tombstones)
            {
                if (weapon->IsActive()) pTombstone->HandleCollision(weapon);
            }
        }
    }
}

void Game::LateUpdate(float elapsedSec)
{
    std::ranges::for_each(m_Waters, [&](Water* pWater) { pWater->LateUpdate(elapsedSec); });
    m_pPlayer->LateUpdate(elapsedSec);

    static auto lateUpdate{[&](GameObject* pGameObject) { pGameObject->LateUpdate(elapsedSec); }};
    static auto toGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};

    std::ranges::for_each(m_GameObjects, lateUpdate);
    std::ranges::for_each(m_Throwables | std::views::transform(toGameObject), lateUpdate);
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
