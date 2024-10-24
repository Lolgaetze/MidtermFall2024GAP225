#pragma once

#include "GameObject.h"
#include "RandomMovement.h"

class Monster : public GameObject
{
private:
    RandomMovement m_movement;

public:
    Monster(MazeGame* pGame, size_t x, size_t y)
        : GameObject(pGame, x, y), m_movement(pGame, this)
    {}

    virtual void TakeTurn() override;

    virtual MoveOutcome OnCollide(GameObject* pOther) override;

    virtual void Draw() override;
};
