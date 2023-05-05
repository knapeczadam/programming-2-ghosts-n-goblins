#pragma once

class ICollectible
{
public:
    explicit ICollectible();
    virtual ~ICollectible() = default;
    ICollectible(const ICollectible& other) = delete;
    ICollectible(ICollectible&& other) noexcept = delete;
    ICollectible& operator=(const ICollectible& other) = delete;
    ICollectible& operator=(ICollectible&& other) noexcept = delete;

    int GetScore() const;
    void SetScore(int score);

protected:
    int m_Score;
};
