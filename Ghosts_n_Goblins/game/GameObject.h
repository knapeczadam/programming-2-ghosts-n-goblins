#pragma once
#include "Game.h"
#include "utils.h"
#include "engine/ITimer.h"

class Sprite;

class GameObject : public ITimer
{
public:
    // CONSTRUCTORS & DESTRUCTOR
    explicit GameObject(GameController* pGameController);
    explicit GameObject(Game::Label label, GameController* pGameController);
    explicit GameObject(Game::Label label, const Rectf& shape, bool collisionEnabled = true, bool hasSprite = false, const Color4f& color = Color4f{0, 0, 0, 1.0f}, GameController* pGameController = nullptr);
    explicit GameObject(Game::Label label, const Point2f& pos,  bool collisionEnabled = true, GameController* pGameController = nullptr);
    virtual ~GameObject() override = default;
    GameObject(const GameObject& other) = delete;
    GameObject(GameObject&& other) noexcept = delete;
    GameObject& operator=(const GameObject& other) = delete;
    GameObject& operator=(GameObject&& other) noexcept = delete;

    virtual void Draw() const;
    virtual void Awake(float elapsedSec);
    virtual void Update(float elapsedSec);
    virtual void LateUpdate(float elapsedSec);
    virtual void HandleCollision(GameObject* other);

    // GETTERS & SETTERS
    Game::Label GetLabel() const;

    template <typename T>
    T GetPosition() const
    {
        T t;
        t.x = m_Shape.left;
        t.y = m_Shape.bottom;
        return t;
    }

    void SetPosition(const Point2f& position);
    Sprite* GetSprite() const;
    void SetSprite(Sprite* pSprite);
    virtual bool IsFlipped() const;


    // FINAL METHODS
public:
    virtual int GetId() const final;
    virtual bool IsActive() const final;
    virtual void SetActive(bool isActive) final;
    virtual bool IsVisible() const final;
    virtual void SetVisible(bool isVisible) final;
    virtual bool IsAwake() const final;
    virtual void SetAwake(bool awake) final;
    virtual Rectf GetShape() const final;
    virtual Point2f GetShapeCenter() const final;
    virtual Rectf GetCollider() const final;
    virtual Point2f GetColliderCenter() const final;
    virtual void SetBottom(float bottom) final;
    virtual void SetLeft(float left) final;
    virtual bool IsOverlapping(GameObject* other) const final;
    virtual void SetFlipped(bool flipped) final;
    
    virtual void Reset();
    virtual void UpdateCollider();

protected:
    virtual void InitCollider() final;
    virtual std::vector<Point2f> GetColliderVertices() const final;
    virtual void SetColliderHeight(float height) final;
    virtual void ResetCollider() final;
    virtual Point2f GetContactPoint(const GameObject* other) const final;

private:
    void InitShape();
    void InitShape(const Point2f& pos);

protected:
    const int m_Id;
    Game::Label m_Label;
    bool m_HasSprite;
    GameController* m_pGameController;
    Sprite* m_pSprite;
    Rectf m_Shape;
    Rectf m_Collider;
    Rectf m_OriginalCollider;
    bool m_CollisionEnabled;
    bool m_Active;
    bool m_Visible;
    bool m_Awake;
    bool m_AwakeFired;
    float m_AwakeDistance;
    bool m_Flipped;
    Color4f m_ColliderColor;

public:
    static int s_IdCounter;
};
