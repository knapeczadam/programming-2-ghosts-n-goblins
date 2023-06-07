#include "pch.h"
#include "Score.h"

#include "engine/Sprite.h"

Score::Score(const Point2f& pos, int score, GameController* pGameController)
    : GameObject(Game::Label::F_SCORE, pos, false, pGameController)
    , m_Score{score}
    , m_Shown{false}
{
    m_Shape.left = pos.x - m_pSprite->GetScaledClipWidth() / 2;
    m_Shape.bottom = pos.y - m_pSprite->GetScaledClipHeight() / 2;
    m_Visible = false;
    SetScore(score);
}

void Score::Update(float elapsedSec)
{
    float time{SetTimme()};
    if (m_Shown)
    {
        time = 0.5f;
        StartTimer(time);
        if (IsTimerFinished())
        {
            m_Active = false;
            m_Visible = false;
            m_Shown = false;
            return;
        }
    }
    StartTimer(time);
    if (IsTimerFinished())
    {
        m_Visible = true;
        m_Shown = true;
    }
}

void Score::SetScore(int score)
{
    m_Score = score;

    switch (m_Score)
    {
    case 200:
        m_pSprite->SetTopOffsetRows(0);
        break;
    case 500:
        m_pSprite->SetTopOffsetRows(1);
        break;
    case 1000:
        m_pSprite->SetTopOffsetRows(2);
        break;
    case 2000:
        m_pSprite->SetTopOffsetRows(3);
        break;
    case 10000:
        m_pSprite->SetTopOffsetRows(4);
        break;
    }
    m_pSprite->UpdateSourceRect();
}

float Score::SetTimme() const
{
    float time{};
    switch (m_Score)
    {
    case 200:
    case 500:
    case 10000:
        break;
    case 1000:
    case 2000:
        time = 0.8f;
        break;
    }
    return time;
}
