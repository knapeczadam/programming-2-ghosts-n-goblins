#pragma once
#include "UI.h"

class InitialDrawer final : public UI
{
public:
    enum class Color
    {
        SKY_BLUE = 0,
        RED = 5,
        TAN = 10
    };
    explicit InitialDrawer(GameController* pGameController);
    virtual ~InitialDrawer() override = default;
    InitialDrawer(const InitialDrawer& other) = delete;
    InitialDrawer(InitialDrawer&& other) noexcept = delete;
    InitialDrawer& operator=(const InitialDrawer& other) = delete;
    InitialDrawer& operator=(InitialDrawer&& other) noexcept = delete;

    void DrawInitial(Point2f pos, const std::string& initial, Color color) const;
    void InitLookup();
    int GetRowIdx(char character) const;
    int GetColIdx(char character) const;
    char GetCharacter(int rowIdx, int colIdx) const;

private:
    std::vector<char> m_Characters;
    const int m_NrCols;
    Sprite* m_pAbc;
};
