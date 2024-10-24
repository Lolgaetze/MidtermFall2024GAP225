#pragma once

#include "DynamicArray.h"

// Generates the class DynamicArray_GameObject
class GameObject;
DYNAMIC_ARRAY(GameObject, *);

// Generates the class DynamicArray_PendingMovement
#include "Movement.h"
#include "Arena.h"
DYNAMIC_ARRAY(PendingMovement);

class GameObject;
class PendingMovement;
class Player;
class Villager;
class Monster;
class RpgCharacter;

// Main game logic.
class MazeGame
{
public:


private:

    // The grid of objects
    DynamicArray_GameObject m_gameObjects;

    // All moves from the current round
    DynamicArray_PendingMovement m_pendingMoves;

    // Whether it is time to quit the game
    bool m_quit;

    size_t m_width;
    size_t m_height;
    Player* m_pPlayer;
    Arena* m_pArena;

public:
    // Takes in a char array representing the level map.
    // See Main.cpp for how this is called.
    MazeGame(char map[], size_t width, size_t height);

    // Deletes GameObjects.
    ~MazeGame();

    // Runs the game.
    void Play();

    // Adds a request to move pMover dX,dY spaces.
    void Move(GameObject* pMover, int dX, int dY);

    // Quits the game.
    void Quit() { m_quit = true; }

    // Removes a GameObject from the grid
    void RemoveGameObject(GameObject* pObject);

private:
    //RpgCharacter* ChooseCharacter();

    // Draws the grid.
    void Draw();

    // Lets every object take its turn.
    void TakeTurns();

    // Applies all movements from the current round.
    void ApplyMovements();

    void CheckForEncounters();
};