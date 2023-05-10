#pragma once
#include "IManager.h"

#include <vector>

class MenuManager final : public IManager
{
public:
    explicit MenuManager(GameController* pGameController);
    virtual ~MenuManager() override = default ;
    MenuManager(const MenuManager&) = delete;
    MenuManager(MenuManager&&) = delete;
    MenuManager& operator=(const MenuManager&) = delete;
    MenuManager& operator=(MenuManager&&) = delete;

    void Draw() const;
    void Update(float elapsedSec);
    virtual void Reset() override;

protected:
    virtual void Initialize() override;
private:
    const int m_MaxIdx; 
    int m_Idx;
    std::vector<int> m_Intervals;
    bool m_CreditInserted;
};
