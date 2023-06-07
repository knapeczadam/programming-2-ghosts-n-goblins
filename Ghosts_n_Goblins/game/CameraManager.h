#pragma once
#include "Game.h"
#include "IManager.h"

class Camera;

class CameraManager final : public IManager
{
public:
    explicit CameraManager(GameController* pGameController);
    virtual ~CameraManager() override;
    CameraManager(const CameraManager& other) = delete;
    CameraManager(CameraManager&& other) noexcept = delete;
    CameraManager& operator=(const CameraManager& other) = delete;
    CameraManager& operator=(CameraManager&& other) noexcept = delete;

    void DoFrustumCulling();
    void ShrinkBoundaries();
    void Transform(Game::Label label);
    Camera* GetCamera() const;
    virtual void Update(float elapsedSec) override;
    virtual void Reset(bool fromCheckpoint) override;

protected:
    virtual void Initialize(bool fromCheckpoint = false) override;
    virtual void CleanUp() override;

private:
    Camera* m_pCamera;
    float m_ShrinkSteps;
    int m_ShrinkStepsCounter;
    bool m_InitBoundaries;
};
