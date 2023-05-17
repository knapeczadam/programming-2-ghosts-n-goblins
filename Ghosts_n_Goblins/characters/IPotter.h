#pragma once

class GameObject;

class IPotter
{
public:
    explicit IPotter();
    virtual ~IPotter() = default;
    IPotter(const IPotter& other) = delete;
    IPotter(IPotter&& other) noexcept = delete;
    IPotter& operator=(const IPotter& other) = delete;
    IPotter& operator=(IPotter&& other) noexcept = delete;

    GameObject* GetPot() const;
    void SetPot(GameObject* pPot);
protected:
    virtual void Update(float elapsedSec);
    void ActivatePot();
    void HidePot();
    void ShowPot();

protected:
    GameObject* m_pPot;
    
};
