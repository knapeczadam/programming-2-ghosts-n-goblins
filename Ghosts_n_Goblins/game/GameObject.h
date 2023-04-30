#pragma once
#include "Game.h"
#include "utils.h"

class Sprite;

class GameObject
{
public:
    // CONSTRUCTORS & DESTRUCTOR
    explicit GameObject();
    explicit GameObject(Game::Label label);
    explicit GameObject(Game::Label label, Sprite* pSprite);
    explicit GameObject(Game::Label label, const Rectf& shape);
    explicit GameObject(Game::Label label, Sprite* pSprite, const Point2f& pos);
    virtual ~GameObject() = default;
    GameObject(const GameObject& other) = delete;
    GameObject(GameObject&& other) noexcept = delete;
    GameObject& operator=(const GameObject& other) = delete;
    GameObject& operator=(GameObject&& other) noexcept = delete;

    virtual void Draw() const;
    virtual void Update(float elapsedSec);
    virtual void HandleCollision(GameObject* other);

    // GETTERS & SETTERS
    Game::Label GetLabel() const;
    void SetLabel(Game::Label label);

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
    virtual Rectf GetShape() const final;
    virtual Point2f GetCenter() const final;
    virtual void SetBottom(float bottom) final;
    virtual void SetLeft(float left) final;

protected:
    virtual bool IsOverlapping(GameObject* other) const final;

private:
    void InitShape();
    void InitShape(const Point2f& pos);

protected:
    Game::Label m_Label;
    Sprite* m_pSprite;
    Rectf m_Shape;
    bool m_IsActive;
    bool m_IsFlipped;
};
