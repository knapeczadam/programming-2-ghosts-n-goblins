#pragma once

class IThrowable
{
public:
    explicit IThrowable() = default;
    virtual ~IThrowable() = default;
    IThrowable(const IThrowable& other) = delete;
    IThrowable(IThrowable&& other) noexcept = delete;
    IThrowable& operator=(const IThrowable& other) = delete;
    IThrowable& operator=(IThrowable&& other) noexcept = delete;
};
