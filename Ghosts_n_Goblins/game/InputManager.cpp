#include "pch.h"
#include "InputManager.h"

#include "GameController.h"

InputManager::InputManager(GameController* pGameController)
    : IManager{pGameController}
    , m_Controls{}
    , m_Keys{}
    , m_ScancodeToString{}
{
    m_pGameController->m_pInputManager = this;
    Initialize();
}

InputManager::~InputManager()
{
    CleanUp();
}

void InputManager::Initialize(bool fromCheckpoint)
{
    InitControls();
    InitScancodeToString();
}

void InputManager::CleanUp()
{
}

void InputManager::InitControls()
{
    m_Controls[Game::Label::I_UP] = {SDL_SCANCODE_UP};
    m_Controls[Game::Label::I_DOWN] = {SDL_SCANCODE_DOWN};
    m_Controls[Game::Label::I_LEFT] = {SDL_SCANCODE_LEFT};
    m_Controls[Game::Label::I_RIGHT] = {SDL_SCANCODE_RIGHT};
    m_Controls[Game::Label::I_JUMP] = {SDL_SCANCODE_X, SDL_SCANCODE_SPACE};
    m_Controls[Game::Label::I_ATTACK] = {SDL_SCANCODE_S};
    m_Controls[Game::Label::I_SELECT] = {SDL_SCANCODE_LSHIFT};
    m_Controls[Game::Label::I_START] = {SDL_SCANCODE_RETURN};
    m_Controls[Game::Label::I_SAVE] = {SDL_SCANCODE_F2};
    m_Controls[Game::Label::I_LOAD] = {SDL_SCANCODE_F5};
    m_Controls[Game::Label::I_INFO] = {SDL_SCANCODE_I};
    m_Controls[Game::Label::I_DEBUG] = {SDL_SCANCODE_D};
    m_Controls[Game::Label::I_QUIT] = {SDL_SCANCODE_ESCAPE};
    m_Controls[Game::Label::I_INCREASE_VOLUME] = {SDL_SCANCODE_O} ;
    m_Controls[Game::Label::I_DECREASE_VOLUME] = {SDL_SCANCODE_L};

    for (const auto& control : m_Controls)
    {
        m_Keys[control.first] = {false, false};
    }
}

void InputManager::InitScancodeToString()
{
    m_ScancodeToString[SDL_SCANCODE_UP] = "Up arrow";
    m_ScancodeToString[SDL_SCANCODE_DOWN] = "Down arrow";
    m_ScancodeToString[SDL_SCANCODE_LEFT] = "Left arrow";
    m_ScancodeToString[SDL_SCANCODE_RIGHT] = "Right arrow";
    m_ScancodeToString[SDL_SCANCODE_A] = "a";
    m_ScancodeToString[SDL_SCANCODE_B] = "b";
    m_ScancodeToString[SDL_SCANCODE_C] = "c";
    m_ScancodeToString[SDL_SCANCODE_D] = "d";
    m_ScancodeToString[SDL_SCANCODE_E] = "e";
    m_ScancodeToString[SDL_SCANCODE_F] = "f";
    m_ScancodeToString[SDL_SCANCODE_G] = "g";
    m_ScancodeToString[SDL_SCANCODE_H] = "h";
    m_ScancodeToString[SDL_SCANCODE_I] = "i";
    m_ScancodeToString[SDL_SCANCODE_J] = "j";
    m_ScancodeToString[SDL_SCANCODE_K] = "k";
    m_ScancodeToString[SDL_SCANCODE_L] = "l";
    m_ScancodeToString[SDL_SCANCODE_M] = "m";
    m_ScancodeToString[SDL_SCANCODE_N] = "n";
    m_ScancodeToString[SDL_SCANCODE_O] = "o";
    m_ScancodeToString[SDL_SCANCODE_P] = "p";
    m_ScancodeToString[SDL_SCANCODE_Q] = "q";
    m_ScancodeToString[SDL_SCANCODE_R] = "r";
    m_ScancodeToString[SDL_SCANCODE_S] = "s";
    m_ScancodeToString[SDL_SCANCODE_T] = "t";
    m_ScancodeToString[SDL_SCANCODE_U] = "u";
    m_ScancodeToString[SDL_SCANCODE_V] = "v";
    m_ScancodeToString[SDL_SCANCODE_W] = "w";
    m_ScancodeToString[SDL_SCANCODE_X] = "x";
    m_ScancodeToString[SDL_SCANCODE_Y] = "y";
    m_ScancodeToString[SDL_SCANCODE_Z] = "z";
    m_ScancodeToString[SDL_SCANCODE_F1] = "F1";
    m_ScancodeToString[SDL_SCANCODE_F2] = "F2";
    m_ScancodeToString[SDL_SCANCODE_F3] = "F3";
    m_ScancodeToString[SDL_SCANCODE_F4] = "F4";
    m_ScancodeToString[SDL_SCANCODE_F5] = "F5";
    m_ScancodeToString[SDL_SCANCODE_F6] = "F6";
    m_ScancodeToString[SDL_SCANCODE_F7] = "F7";
    m_ScancodeToString[SDL_SCANCODE_F8] = "F8";
    m_ScancodeToString[SDL_SCANCODE_F9] = "F9";
    m_ScancodeToString[SDL_SCANCODE_F10] = "F10";
    m_ScancodeToString[SDL_SCANCODE_F11] = "F11";
    m_ScancodeToString[SDL_SCANCODE_F12] = "F12";
    m_ScancodeToString[SDL_SCANCODE_0] = "0";
    m_ScancodeToString[SDL_SCANCODE_1] = "1";
    m_ScancodeToString[SDL_SCANCODE_2] = "2";
    m_ScancodeToString[SDL_SCANCODE_3] = "3";
    m_ScancodeToString[SDL_SCANCODE_4] = "4";
    m_ScancodeToString[SDL_SCANCODE_5] = "5";
    m_ScancodeToString[SDL_SCANCODE_6] = "6";
    m_ScancodeToString[SDL_SCANCODE_7] = "7";
    m_ScancodeToString[SDL_SCANCODE_8] = "8";
    m_ScancodeToString[SDL_SCANCODE_9] = "9";
    m_ScancodeToString[SDL_SCANCODE_SPACE] = "Space";
    m_ScancodeToString[SDL_SCANCODE_LSHIFT] = "Left shift";
    m_ScancodeToString[SDL_SCANCODE_RSHIFT] = "Right shift";
    m_ScancodeToString[SDL_SCANCODE_RETURN] = "Enter";
    m_ScancodeToString[SDL_SCANCODE_ESCAPE] = "Esc";
}

bool InputManager::IsTriggered(Game::Label label) const
{
    return m_Keys.at(label).second;
}

void InputManager::SetTriggered(Game::Label label, bool triggered)
{
    m_Keys[label].second = triggered;
}

bool InputManager::IsPressed(Game::Label label) const
{
    return m_Keys.at(label).first;
}

void InputManager::SetPressed(Game::Label label, bool pressed)
{
    m_Keys[label].first = pressed;
}

void InputManager::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    for (const auto& control : m_Controls)
    {
        if (std::find(control.second.begin(), control.second.end(), e.keysym.scancode) != control.second.end())
        {
            m_Keys[control.first].first = true;
        }
    }
}

void InputManager::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    for (const auto& control : m_Controls)
    {
        if (std::find(control.second.begin(), control.second.end(), e.keysym.scancode) != control.second.end())
        {
            m_Keys[control.first].first = false;
            m_Keys[control.first].second = false;
        }
    }
}

std::string InputManager::ToString(Game::Label control) const
{
    std::string tos;
    int idx{};
    for (SDL_Scancode scancode : m_Controls.at(control))
    {
        if (idx)
        {
            tos += ", ";    
        }
        tos += m_ScancodeToString.at(scancode);
        ++idx;
    }
    return tos;
}