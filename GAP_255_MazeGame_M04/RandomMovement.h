#pragma once

#include "Movement.h"
#include "MazeGame.h"
#include "GameObject.h"

#include <cstdlib>

class RandomMovement
{
private:
    MazeGame* m_pGame;
    GameObject* m_pOwner;

public:
    RandomMovement(MazeGame* pGame, GameObject* pOwner)
        : m_pGame(pGame), m_pOwner(pOwner)
    {}

    void MoveRandomly()
    {
        // Randomly choose a direction: up, down, left, right
        int direction = rand() % 4;
        switch (direction)
        {
        case 0: m_pGame->Move(m_pOwner, 0, -1); break; // Up
        case 1: m_pGame->Move(m_pOwner, 0, 1); break;  // Down
        case 2: m_pGame->Move(m_pOwner, -1, 0); break; // Left
        case 3: m_pGame->Move(m_pOwner, 1, 0); break;  // Right
        }
    }
};
