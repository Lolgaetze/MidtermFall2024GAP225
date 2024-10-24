#include "Monster.h"
#include "Player.h"
#include "Villager.h"
#include "MazeGame.h"

void Monster::TakeTurn()
{
    m_movement.MoveRandomly();
}

MoveOutcome Monster::OnCollide(GameObject* pOther)
{
    Player* pPlayer = dynamic_cast<Player*>(pOther);
    if (pPlayer)
    {
        // Monster touched player, player loses
        m_pGame->Quit();
        return kMoveAllowed;
    }

    Villager* pVillager = dynamic_cast<Villager*>(pOther);
    if (pVillager)
    {
        // Monster touched a villager, remove villager
        m_pGame->RemoveGameObject(pVillager);
        return kMoveAllowed;
    }

    return kMoveAllowed;
}

void Monster::Draw()
{
    std::cout << 'M';
}
