// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "Texture.h"
#include "utils.h"
#include "characters/Player.h"
#include "collectibles/PowerUpManager.h"
#include "weapons/IThrowable.h"
#include "engine/json.hpp"
#include "engine/SpriteFactory.h"
#include "engine/TextureManager.h"
#include "level/Level.h"
#include "level/Platform.h"
#include "ui/HUD.h"

#include <fstream>
#include <iostream>
#include <ranges>

#include "characters/IEnemy.h"
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
      , m_pPlatform{}
      , m_pCamera{}
      , m_pHUD{}
      , m_pTestGameObject{}
      , m_Data{}
      , m_DataPath{"../../Resources/data.json"}
      , m_Labels{}
      , m_AttackKeyReleased{true}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
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
    m_pLevel = new Level{m_pSpriteFactory->CreateSprite(Label::LEVEL), m_pPlatform};
    //m_pWater = new GameObject{Label::WATER, m_pSpriteFactory->CreateSprite(Label::WATER), Point2f{3550.0f, 0.0f}};
    // CAMERA - has to be after level initialization
    m_pCamera = new Camera{};
    InitCamera();
    // PLAYER
    Sprite* pPlayerSprite{m_pSpriteFactory->CreateSprite(Label::ARTHUR)};
    m_pPlayer = new Player{pPlayerSprite, Point2f{3520, 200}, m_pLevel};
    // HUD
    m_pHUD = new HUD{Point2f{20.0f, 200.0f}, 3};

    // TEST GAME OBJECT
    m_pTestGameObject = new Dagger{m_pSpriteFactory->CreateSprite(Label::DAGGER), Point2f{218.f, 65.f}};

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
    m_Labels["level"] = Label::LEVEL;
    m_Labels["platform"] = Label::PLATFORM;
    m_Labels["water"] = Label::WATER;

    // UI
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

void Game::InitCamera() const
{
    m_pCamera->SetLevelBoundaries(m_pLevel->GetBoundaries());
    m_pCamera->SetWidth(GetViewPort().width);
    m_pCamera->SetHeight(GetViewPort().height);
}


void Game::Cleanup()
{
    delete m_pCamera;
    delete m_pHUD;
    delete m_pLevel;
    delete m_pPlatform;
    delete m_pSpriteFactory;
    delete m_pTextureManager;
    delete m_pPlayer;

    for (const GameObject* pGameObject : m_GameObjects)
    {
        delete pGameObject;
    }

    for (const IThrowable* pThrowable : m_Throwables)
    {
        delete pThrowable;
    }
}

void Game::Draw() const
{
    ClearBackground();

    glPushMatrix();
    m_pCamera->Transform(m_pPlayer->GetShape());
    m_pLevel->Draw();
    // C++20 ranges for loop with condition
    static auto draw{[](const GameObject* pGameObject) { pGameObject->Draw(); }};
    static auto toGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    std::ranges::for_each(m_GameObjects | std::views::filter(isActive), draw);
    std::ranges::for_each(m_Throwables | std::views::transform(toGameObject) | std::views::filter(isActive), draw);
    m_pPlayer->Draw();
    glPopMatrix();

    // m_pHUD->Draw();
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::Update(float elapsedSec)
{
    // Update game objects
    m_pLevel->Update(elapsedSec);
    m_pPlayer->Update(elapsedSec);

    static auto isActive{[](const GameObject* pGameObject) { return pGameObject->IsActive(); }};
    static auto toGameObject{[](IThrowable* pThrowable) { return dynamic_cast<GameObject*>(pThrowable); }};
    static auto update {[&](GameObject* pGameObject) { pGameObject->Update(elapsedSec); }};
    std::ranges::for_each(m_GameObjects | std::views::filter(isActive), update);
    std::ranges::for_each(m_Throwables | std::views::transform(toGameObject) | std::views::filter(isActive), update);
    
    // for (GameObject* pGameObject : m_GameObjects)
    // {
    //     if (pGameObject->IsActive())
    //     {
    //         pGameObject->Update(elapsedSec);
            // IEnemy* pEnemy{dynamic_cast<IEnemy*>(pGameObject)};
            // if (pEnemy)
            // {
            //     pEnemy->SetTarget(m_pPlayer->GetPosition<Point2f>());
            // }
    //     }
    // }

    // Do collision
    DoCollisionTests();
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
    }
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}


void Game::PrintInfo() const
{
    std::cout << "Game info:" << std::endl;
}

void Game::DoCollisionTests()
{
    m_pLevel->HandleCollision(m_pPlayer);
    // ENEMIES, PICKUPS
    for (GameObject* pGameObject : m_GameObjects)
    {
        if (pGameObject->IsActive())
        {
            // PLAYER
            m_pPlayer->HandleCollision(pGameObject);

            // WEAPONS
            for (IThrowable* pThrowable : m_Throwables)
            {
                GameObject* weapon = dynamic_cast<GameObject*>(pThrowable);
                pGameObject->HandleCollision(weapon);
            }
        }
    }
}

void Game::Debug() const
{
    std::cout << "Game debug:" << std::endl;
    std::cout << " -- Player --" << std::endl;
    std::cout << "Position: x - " << m_pPlayer->GetPosition<Point2f>().x << " y - " << m_pPlayer->GetPosition<Point2f>()
        .y << std::endl;
}
