#include "pch.h"
#include "InitialDrawer.h"

#include "engine/Sprite.h"
#include "engine/SpriteFactory.h"
#include "game/GameController.h"

InitialDrawer::InitialDrawer(GameController* pGameController)
    : UI(Game::Label::U_CHARACTER_DRAWER, pGameController)
    , m_Characters{}
    , m_NrCols{13}
    , m_pSprite{pGameController->m_pSpriteFactory->CreateSprite(Game::Label::U_ABC)}
{
    InitLookup();
    m_pSprite->SetLeftOffsetPx(4);
    m_pSprite->SetTopOffsetPx(4);
}

/*
 * color: 0 = sky blue, 1 = red, 2 = tan
 */
void InitialDrawer::DrawInitial(Point2f pos, const std::string& initial, Color color) const
{
    pos.y -= m_pSprite->GetScaledClipHeight() / 2;
    const float offset{m_pSprite->GetScaledClipWidth() / 2};
    for (char c : initial)
    {
        m_pSprite->SetTopOffsetRows(int(color) + GetRowIdx(c));
        m_pSprite->SetLeftOffsetCols(GetColIdx(c));
        m_pSprite->SetPosition(pos);
        m_pSprite->UpdateSourceRect();
        m_pSprite->UpdateDestinationRect();
        m_pSprite->Draw();
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
}

char InitialDrawer::GetCharacter(int rowIdx, int colIdx) const
{
    return m_Characters[rowIdx * m_NrCols + colIdx];
}

