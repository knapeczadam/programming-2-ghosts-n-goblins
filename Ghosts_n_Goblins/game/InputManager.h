#pragma once
#include <map>

#include "Game.h"

struct KeyState
{
    bool m_LeftKeyPressed{false};
    bool m_RightKeyPressed{false};
    bool m_UpKeyPressed{false};
    bool m_DownKeyPressed{false};
    bool m_AttackKeyPressed{false};
    bool m_JumpKeyPressed{false};

    bool m_LeftKeyTriggered{false};
    bool m_RightKeyTriggered{false};
    bool m_UpKeyTriggered{false};
    bool m_DownKeyTriggered{false};
    bool m_AttackKeyTriggered{false};
    bool m_JumpKeyTriggered{false};
};

class InputManager final
{
public:
    explicit InputManager();
    ~InputManager() = default;
    InputManager(const InputManager& other) = delete;
    InputManager(InputManager&& other) noexcept = delete;
    InputManager& operator=(const InputManager& other) = delete;
    InputManager& operator=(InputManager&& other) noexcept = delete;

    bool IsTriggered(Game::Label label) const;
    void SetTriggered(Game::Label label, bool triggered);
    bool IsPressed(Game::Label label) const;
    void SetPressed(Game::Label label, bool pressed);

    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
    
private:
    void InitControls();
private:
    std::map<Game::Label, std::vector<SDL_Scancode>> m_Controls;
    std::map<Game::Label, std::pair<bool, bool>> m_Keys; // first = pressed, second = triggered
};
