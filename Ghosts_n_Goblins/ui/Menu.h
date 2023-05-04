#pragma once
#include "UI.h"

class Menu : public UI
{
public:
    Menu();
    virtual ~Menu() override = default;
    Menu(const Menu& other) = delete;
    Menu(Menu&& other) noexcept = delete;
    Menu& operator=(const Menu& other) = delete;
    Menu& operator=(Menu&& other) noexcept = delete;
};
