#pragma once
#include "UI.h"

class Menu : public UI
{
public:
    Menu(GameController* pGameController);
    virtual ~Menu() override = default;
    Menu(const Menu& other) = delete;
    Menu(Menu&& other) noexcept = delete;
    Menu& operator=(const Menu& other) = delete;
    Menu& operator=(Menu&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

private:
    void DrawAbc() const;
    void InitCharacterLookup();
    void FlickerCharacter() const;
    char GetCharacter() const;
    void OnEnter();
    void SaveInitial();
    
private:
    Sprite* m_pBlueChar;
    Sprite* m_pRedChar;
    const Point2f m_BlueCharPos;
    const Point2f m_RedCharPos;
    const int m_NrRows;
    const int m_NrCols;
    std::vector<char> m_Characters;
    int m_RowIdx;
    int m_ColIdx;
    bool m_Flicker;
    std::string m_Initial;
    const size_t m_MaxLength;
};

