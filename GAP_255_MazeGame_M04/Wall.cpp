#include "Wall.h"
#include "MazeGame.h"

#include <iostream>

MoveOutcome Wall::OnCollide(GameObject* pMover)
{
    return kMoveBlocked; // block movement
}

void Wall::Draw()
{
    std::cout << '#';
}
