#pragma once
#include "Game.h"
#include "utils.h"
#include "engine/Timer.h"

class Sprite;

class GameObject : public Timer
{
public:
    // CONSTRUCTORS & DESTRUCTOR
    explicit GameObject();
    explicit GameObject(Game::Label label, bool collisionEnabled = true);
    explicit GameObject(Game::Label label, Sprite* pSprite, bool collisionEnabled = true);
    explicit GameObject(Game::Label label, const Rectf& shape, bool collisionEnabled = true, const Color4f& color = Color4f{0.f, 1.f, 1.f, 1.f});
    explicit GameObject(Game::Label label, Sprite* pSprite, const Point2f& pos, bool collisionEnabled = true);
    virtual ~GameObject() override = default;
    GameObject(const GameObject& other) = delete;
    GameObject(GameObject&& other) noexcept = delete;
    GameObject& operator=(const GameObject& other) = delete;
    GameObject& operator=(GameObject&& other) noexcept = delete;

    virtual void Draw() const;
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


    // FINAL METHODS
public:
    virtual bool IsActive() const final;
    virtual void SetActive(bool isActive) final;
    virtual bool IsVisible() const final;
    virtual void SetVisible(bool isVisible) final;
    virtual Rectf GetShape() const final;
    virtual Point2f GetShapeCenter() const final;
    virtual Rectf GetCollisionBox() const final;
    virtual Point2f GetCollisionBoxCenter() const final;
    virtual void SetBottom(float bottom) final;
    virtual void SetLeft(float left) final;
    virtual bool IsOverlapping(GameObject* other) const final;

protected:
    virtual void InitCollisionBox() final;
    virtual void UpdateCollisionBox() final;
    virtual std::vector<Point2f> GetCollisionBoxVertices() const final;

private:
    void InitShape();
    void InitShape(const Point2f& pos);

protected:
    Game::Label m_Label;
    Sprite* m_pSprite;
    Rectf m_Shape;
    Rectf m_CollisionBox;
    bool m_CollisionEnabled;
    bool m_Active;
    bool m_Visible;
    bool m_Flipped;
    Color4f m_Color;
};
