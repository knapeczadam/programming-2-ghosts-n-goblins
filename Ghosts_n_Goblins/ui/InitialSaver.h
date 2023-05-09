#pragma once
#include "UI.h"

class InitialSaver : public UI
{
public:
    InitialSaver(GameController* pGameController);
    virtual ~InitialSaver() override = default;
    InitialSaver(const InitialSaver& other) = delete;
    InitialSaver(InitialSaver&& other) noexcept = delete;
    InitialSaver& operator=(const InitialSaver& other) = delete;
    InitialSaver& operator=(InitialSaver&& other) noexcept = delete;

    virtual void Draw() const override;
    virtual void Update(float elapsedSec) override;

private:
    void DrawAbc() const;
    auto DrawInitial() const -> void;
    void FlickerCharacter() const;
    void OnEnter();
    void SaveInitial();
    
private:
    Sprite* m_pBlueChar;
    Sprite* m_pRedChar;
    Sprite* m_pTextInitial;
    const Point2f m_BlueCharPos;
    const Point2f m_RedCharPos;
    const Point2f m_TextInitialPos;
    const int m_NrRows;
    const int m_NrCols;
    int m_RowIdx;
    int m_ColIdx;
    std::string m_Initial;
    const size_t m_MaxLength;
};

