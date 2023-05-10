#include "pch.h"
#include "InitialDrawer.h"

#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"

InitialDrawer::InitialDrawer(GameController* pGameController)
    : UI(Game::Label::U_CHARACTER_DRAWER, pGameController)
    , m_Characters{}
    , m_NrCols{13}
{
    m_pAbc = pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC);
    InitLookup();
    m_pAbc->SetLeftOffsetPx(4);
    m_pAbc->SetTopOffsetPx(4);
}

void InitialDrawer::DrawInitial(Point2f pos, const std::string& initial, Color color) const
{
    pos.y -= m_pAbc->GetScaledClipHeight() / 2;
    const float offset{m_pAbc->GetScaledClipWidth() / 2};
    for (char c : initial)
    {
        m_pAbc->SetTopOffsetRows(int(color) + GetRowIdx(c));
        m_pAbc->SetLeftOffsetCols(GetColIdx(c));
        m_pAbc->SetPosition(pos);
        m_pAbc->UpdateSourceRect();
        m_pAbc->UpdateDestinationRect();
        m_pAbc->Draw();
        pos.x += offset;
    }
}
void InitialDrawer::InitLookup()
{
    m_Characters.insert(m_Characters.end(), {
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                            '!', '?', '&', ',', '.', '(', ')', '/', ':', '*', ' ', ' ', ' '
                        });
}

int InitialDrawer::GetRowIdx(char character) const
{
    for (size_t idx{}; idx < m_Characters.size(); ++idx)
    {
        if (m_Characters[idx] == character)
        {
            return int(idx) / m_NrCols;
        }
    }
    return 0;
}

int InitialDrawer::GetColIdx(char character) const
{
    for (size_t idx{}; idx < m_Characters.size(); ++idx)
    {
        if (m_Characters[idx] == character)
        {
            return int(idx) % m_NrCols;
        }
    }
    return 0;
}

char InitialDrawer::GetCharacter(int rowIdx, int colIdx) const
{
    return m_Characters[rowIdx * m_NrCols + colIdx];
}

