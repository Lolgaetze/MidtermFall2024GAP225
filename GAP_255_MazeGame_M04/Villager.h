#pragma once

#include "GameObject.h"
#include "RandomMovement.h"

class Villager : public GameObject
{
private:
    RandomMovement m_mover;

public:
    Villager(MazeGame* pGame, size_t x, size_t y)
        : GameObject(pGame, x, y), m_mover(pGame, this)
    {}

    virtual void TakeTurn() override;

    virtual MoveOutcome OnCollide(GameObject* pOther) override;

    virtual void Draw() override;
    
};
