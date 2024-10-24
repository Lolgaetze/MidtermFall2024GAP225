#include "Villager.h"
#include "Player.h"
#include "MazeGame.h"

void Villager::TakeTurn()
{
    m_mover.MoveRandomly();
}

MoveOutcome Villager::OnCollide(GameObject* pOther)
{
    // Check if the colliding object is the player
    Player* pPlayer = dynamic_cast<Player*>(pOther);
    if (pPlayer)
    {
        pPlayer->IncrementScore();
        // Remove this villager from the game
        m_pGame->RemoveGameObject(this);
        return kMoveAllowed;
    }
    return kMoveAllowed;
}

void Villager::Draw()
{
    std::cout << 'V';
}
