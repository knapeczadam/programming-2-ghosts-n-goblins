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
    void Transform(Game::Label label);
    Camera* GetCamera() const;

protected:
    virtual void Initialize() override;
private:
    Camera* m_pCamera;
};
