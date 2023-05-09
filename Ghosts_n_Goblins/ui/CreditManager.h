#pragma once
#include "UI.h"

class CreditManager : public UI
{
public:
    CreditManager(GameController* pGameController);
    virtual ~CreditManager() override = default;
    CreditManager(const CreditManager& other) = delete;
    CreditManager(CreditManager&& other) noexcept = delete;
    CreditManager& operator=(const CreditManager& other) = delete;
    CreditManager& operator=(CreditManager&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;
private:
    int m_Credits;
    const int m_MaxCredits;
};
