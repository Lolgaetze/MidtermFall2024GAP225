#pragma once

// Some basic utilities for handling movement.

// Later I would replace this with an enum.
#define MoveOutcome int
constexpr MoveOutcome kMoveAllowed = 0;
constexpr MoveOutcome kMoveBlocked = 1;

// A request to move pMover dX, dY spaces.
struct PendingMovement
{
    class GameObject* pMover;
    int dX;
    int dY;
};