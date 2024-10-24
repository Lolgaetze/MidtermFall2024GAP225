#pragma once

#include "Movement.h"

#include <iostream>

class MazeGame;

// Base class for each object in the grid.
class GameObject
{
public:
    // I decided to make these public because we're reading
    // and writing them from MazeGame anyway.
    size_t x;
    size_t y;

protected:
    // The game that the object belongs to. Used to call
    // functions of MazeGame.
    MazeGame* m_pGame;

public:
    GameObject(MazeGame* pGame, size_t x, size_t y);
    virtual ~GameObject() = default;

    // This object performs active behavior, such as moving.
    virtual void TakeTurn() {}

    // handle object effect on contact with player
    virtual MoveOutcome OnCollide(GameObject* pMover) { return kMoveAllowed; }

    // draw object
    virtual void Draw() { std::cout << '.'; } // default empty space
};