#include "MazeGame.h"
#include "Movement.h"
#include "Player.h"
#include "Wall.h"
#include "Exit.h"
#include "Villager.h"
#include "Monster.h"
#include "RpgCharacter.h"
#include "Arena.h"


#include <iostream>

/////////////////////////////////////////////////////
// Takes in a char array representing the level map.
// See Main.cpp for how this is called.
/////////////////////////////////////////////////////
MazeGame::MazeGame(char map[], size_t width, size_t height)
    : m_gameObjects{ width * height }
    , m_pendingMoves{ width * height }
    , m_width{ width }
    , m_height{ height }
    , m_pPlayer{ nullptr }
    , m_quit{ false }
    , m_pArena{ nullptr }
{
    // This loops through the char map and creates corresponding
    // objects. Each square in the map represents an object.
    size_t index = 0;
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            GameObject* pNewObject = nullptr;
            switch (map[index])
            {
            case '@':
                m_pPlayer = new Player{ this, x, y };
                pNewObject = m_pPlayer;
                break;
            case '#':   //TODO: Create a wall and assign it to pNewObject
                pNewObject = new Wall{ this, x, y };
                break;
            case 'x':   //TODO: Create an exit and assign it to pNewObject
                pNewObject = new Exit{ this, x, y };
                break;
            case 'V':
                pNewObject = new Villager{ this, x, y };
                break;
            case 'M':
                pNewObject = new Monster{ this, x, y };
                break;
            case '.':
            default:
                // Default gameObject, which is suitable for empty space
                pNewObject = new GameObject{this, x, y};
                break;
            }
            // Each GameObject is added to the grid array.
            m_gameObjects.Add(pNewObject);
            ++index;
        }
    }
}

/////////////////////////////////////////////////////
// Deletes GameObjects.
/////////////////////////////////////////////////////
MazeGame::~MazeGame()
{
    // Note: we are deleting each *individual* GameObject, because each
    // *individual* GameObject was created dynamically.
    // The array itself is completely managed by the DynamicArray classes,
    // so we don't have to worry about it.
    for (size_t i = 0; i < m_width * m_height; ++i)
    {
        delete m_gameObjects.At(i);
    }
}

/////////////////////////////////////////////////////
// Runs the game.
/////////////////////////////////////////////////////
void MazeGame::Play()
{
    m_pPlayer->ChooseCharacter();
    //m_pArena->ChooseCharacter();
    while (!m_quit)
    {
        Draw();
        TakeTurns();
        ApplyMovements();
        CheckForEncounters(); // randomize encounter
    }

    if (m_pPlayer)
    {
        std::cout << "Final Score: " << m_pPlayer->GetScore() << "\n";
    }
    std::cout << "Game Over!\n";
}

/////////////////////////////////////////////////////
// Adds a request to move pMover dX,dY spaces.
/////////////////////////////////////////////////////
void MazeGame::Move(GameObject* pMover, int dX, int dY)
{
    // Movement doesn't actually happen yet.
    m_pendingMoves.Add(PendingMovement{ pMover, dX, dY});
}

/////////////////////////////////////////////////////
// Removing villagers or monsters
/////////////////////////////////////////////////////

void MazeGame::RemoveGameObject(GameObject* pObject)
{
    for (size_t i = 0; i < m_gameObjects.GetSize(); ++i)
    {
        if (m_gameObjects.At(i) == pObject)
        {
            delete m_gameObjects.At(i);
            m_gameObjects.At(i) = new GameObject(this, pObject->x, pObject->y);
            break;
        }
    }
}


/////////////////////////////////////////////////////
// Draws the grid.
/////////////////////////////////////////////////////
void MazeGame::Draw()
{
    system("cls");
    size_t index = 0;
    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            GameObject* pObject = m_gameObjects.At(index);
            //    //TODO: Define a virtual function named Draw.
            //    // Each GameObject should use it to draw itself.
            //    // Then call it here.
            //    //pObject->Draw();
            if (pObject != nullptr)
            {
                pObject->Draw();
                std::cout << ' ';
            }
            else
            {
                std::cout << ". "; // Empty space
            }
            ++index;
        }
        std::cout << '\n';
    }
    std::cout << "save the villagers, Watchout there's monster nearby\n";
    std::cout << "Use wasd to move\n";
    std::cout << "Press q to quit\n";
}

/////////////////////////////////////////////////////
// Lets every object take its turn.
/////////////////////////////////////////////////////
void MazeGame::TakeTurns()
{
    // Loops through every element of the dynamic array.
    for (size_t i = 0; i < m_gameObjects.GetSize(); ++i)
    {
        if (m_gameObjects.At(i) != nullptr)
        {
            m_gameObjects.At(i)->TakeTurn();
        }
    }
}

/////////////////////////////////////////////////////
// Applies all movements from the current round.
/////////////////////////////////////////////////////
void MazeGame::ApplyMovements()
{
    // Loops through every element of the dynamic array.
    for(size_t i = 0; i < m_pendingMoves.GetSize(); ++i)
    {
        PendingMovement& move = m_pendingMoves.At(i);

        // This is mostly unpacking the info from the PendingMovement object.
        size_t fromX = move.pMover->x;
        size_t fromY = move.pMover->y;
        size_t fromIndex = fromX + fromY * m_width;
        GameObject* pMover = move.pMover;       // moving object


        size_t toX = fromX + move.dX;
        size_t toY = fromY + move.dY;                   
        size_t toIndex = toX + toY * m_width;   // object occupying the target space
        GameObject* pMovee = m_gameObjects.At(toIndex);

        MoveOutcome outcome = pMovee->OnCollide(pMover);
        if (outcome == kMoveBlocked)
            continue; 

        // Perform the move by switching the two objects
        std::swap(m_gameObjects.At(fromIndex), m_gameObjects.At(toIndex));

        // Update each object's internal x,y.
        pMover->x = toX;
        pMover->y = toY;
        pMovee->x = fromX;
        pMovee->y = fromY;
    }

    // After all moves are processed, we clear them and start over for the next round.
    m_pendingMoves.Clear();
}

void MazeGame::CheckForEncounters()
{
    //m_pArena->EncounterMonster();
    m_pPlayer->EncounterMonster();
}
