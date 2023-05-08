#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
    InitControls();
}

void InputManager::InitControls()
{
    m_Controls[Game::Label::I_UP] = {SDL_SCANCODE_UP};
    m_Controls[Game::Label::I_DOWN] = {SDL_SCANCODE_DOWN};
    m_Controls[Game::Label::I_LEFT] = {SDL_SCANCODE_LEFT};
    m_Controls[Game::Label::I_RIGHT] = {SDL_SCANCODE_RIGHT};
    m_Controls[Game::Label::I_JUMP] = {SDL_SCANCODE_X};
    m_Controls[Game::Label::I_ATTACK] = {SDL_SCANCODE_S};
    m_Controls[Game::Label::I_SELECT] = {SDL_SCANCODE_LSHIFT};
    m_Controls[Game::Label::I_START] = {SDL_SCANCODE_RETURN};
    m_Controls[Game::Label::I_SAVE] = {SDL_SCANCODE_F2};
    m_Controls[Game::Label::I_LOAD] = {SDL_SCANCODE_F5};
    m_Controls[Game::Label::I_PRINT] = {SDL_SCANCODE_P};
    m_Controls[Game::Label::I_DEBUG] = {SDL_SCANCODE_D};
    m_Controls[Game::Label::I_QUIT] = {SDL_SCANCODE_ESCAPE};
    m_Controls[Game::Label::I_INCREASE_VOLUME] = {SDL_SCANCODE_O};
    m_Controls[Game::Label::I_DECREASE_VOLUME] = {SDL_SCANCODE_L};

    for (const auto& control : m_Controls)
    {
        m_Keys[control.first] = {false, false};
    }
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

