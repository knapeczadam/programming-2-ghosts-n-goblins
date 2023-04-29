#pragma once

class PickUpManager final
{
public:
    PickUpManager() = default;
    ~PickUpManager() = default;
    PickUpManager(const PickUpManager& other) = delete;
    PickUpManager(PickUpManager&& other) noexcept = delete;
    PickUpManager& operator=(const PickUpManager& other) = delete;
    PickUpManager& operator=(PickUpManager&& other) noexcept = delete;
};
