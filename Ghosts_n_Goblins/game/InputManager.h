#pragma once
#include <map>

#include "Game.h"
#include "IManager.h"

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

/**
 * \par Joystick or Direction Pad
 * Use this control to direct Arthur throughout each stage. You can make him run to the left or to the right by pushing the control in either direction. Hold the controller down to make Arthur crouch underneath high attacks. There is a delayed recovery to crouching, which can be canceled by tapping up. Use up or down to instruct Arthur to climb ladders. In the Famicom/NES-based versions of the game, there is no recovery to crouching. However, crouching and immediately pressing left or right will lock Arthur in the crouching position. To release crouch, you must either allow the controller to come to a neutral position, or press up to cancel it. Be aware of ladders if you choose the latter option.
 * \par Fire
 * Press the fire button to shoot your weapon. You can place up to either two or three instances of your weapon on-screen at once, depending on which you have equipped. Press fire while crouching to throw a weapon low to the ground. Rapidly tap the direction you are facing, while standing, in tandem with the fire button to increase your rate of fire.
 * \par Jump
 * Press the jump button to make Arthur leap into the air. Use in conjunction with left or right to make Arthur jump in a particular direction. Note that a Jump in this game is a 100% commitment; there is no reversing or manipulating a mid-air jump.
 * <a href="https://strategywiki.org/wiki/Ghosts_%27n_Goblins/How_to_play#Controls">StrategyWiki</a>
 */
class InputManager final : public IManager
{
public:
    explicit InputManager(GameController* pGameController);
    virtual ~InputManager() override;
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

    std::string ToString(Game::Label control) const;

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    void InitControls();
    void InitScancodeToString();

private:
    std::map<Game::Label, std::vector<SDL_Scancode>> m_Controls;
    std::map<Game::Label, std::pair<bool, bool>> m_Keys; // first = pressed, second = triggered
    std::map<SDL_Scancode, std::string> m_ScancodeToString;
};
