#include "Exit.h"
#include "MazeGame.h"

#include <iostream>

MoveOutcome Exit::OnCollide(GameObject* pMover)
{
    m_pGame->Quit();
    return kMoveAllowed; // Allow movement
}

void Exit::Draw()
{
    std::cout << 'x';
}
