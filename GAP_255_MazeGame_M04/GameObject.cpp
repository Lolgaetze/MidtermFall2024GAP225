#include "GameObject.h"

#include <iostream>

GameObject::GameObject(MazeGame* pGame, size_t x, size_t y)
    : x{x}
    , y{y}
    , m_pGame{pGame}
{
}