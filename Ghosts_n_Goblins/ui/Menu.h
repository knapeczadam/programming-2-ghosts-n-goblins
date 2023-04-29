#pragma once

class Menu final
{
public:
    Menu() = default;
    ~Menu() = default;
    Menu(const Menu& other) = delete;
    Menu(Menu&& other) noexcept = delete;
    Menu& operator=(const Menu& other) = delete;
    Menu& operator=(Menu&& other) noexcept = delete;
};
