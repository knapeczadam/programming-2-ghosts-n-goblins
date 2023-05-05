#pragma once

class IClimable
{
public:
    explicit IClimable() = default;
    virtual ~IClimable() = default;
    IClimable(const IClimable& other) = delete;
    IClimable(IClimable&& other) noexcept = delete;
    IClimable& operator=(const IClimable& other) = delete;
    IClimable& operator=(IClimable&& other) noexcept = delete;
};