#include "Player.h"
#include "MazeGame.h"
#include "RpgCharacter.h"

#include <conio.h>
#include <iostream>

/////////////////////////////////////////////////////////
// This object performs active behavior, such as moving.
/////////////////////////////////////////////////////////
void Player::TakeTurn()
{
    // Takes user input to move or quit.
    char input = _getch();
    switch (input)
    {
    case 'w': m_pGame->Move(this, 0, -1); break;
    case 's': m_pGame->Move(this, 0, +1); break;
    case 'a': m_pGame->Move(this, -1, 0); break;
    case 'd': m_pGame->Move(this, +1, 0); break;
    case 'q': m_pGame->Quit();
    }
}


MoveOutcome Player::OnCollide(GameObject* pMover)
{
    return kMoveAllowed;
}

void Player::Draw()
{
    std::cout << '@';
}


/////////////////////////////////////////////////////////
// Calculate the chance to encounter a monster while moving
/////////////////////////////////////////////////////////
void Player::EncounterMonster()
{
    int chance = rand() % 100; 
    if (chance < 20) { // 20% chance to encounter a monster
        std::cout << "A wild monster appears!\n";
        std::cout << "Press any key to continue...";
        _getch(); // Waits for any key press
        Fight();
    }
}


///////////////////////////////////////////////////////////
//// Character selection
///////////////////////////////////////////////////////////
void Player::ChooseCharacter()
{
    std::cout << "Player, choose your fighter:\n";
    m_players[0] = ChooseFighter();
    std::cout << std::endl;
}


/////////////////////////////////////////////////////////
// Character selection with options printed
/////////////////////////////////////////////////////////
RpgCharacter* Player::ChooseFighter()
{
    RpgCharacter* premadeFighter[3] = {
        new RpgCharacter("Rogier", 100, 20, 70),
        new RpgCharacter("Alice", 80, 25, 80),
        new RpgCharacter("Barats", 125, 15, 70)
    };

    // show list of fighter & repeat if invalid choice
    for (int i = 0; i < 3; ++i) {
        std::cout << i + 1 << ". ";
        premadeFighter[i]->PrintStats();
    }

    while (true)
    {
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
        case 2:
        case 3:
            return premadeFighter[choice - 1];
        default:
            std::cout << "Invalid choice. Choose again:\n";
            continue;
        }
        break;
    }
}


/////////////////////////////////////////////////////////
// Where encounter take place "for now"
// want to move this but scared it breaks
/////////////////////////////////////////////////////////
void Player::Fight()
{
    RpgCharacter* enemy[4] = {
        new RpgCharacter("Goblin", 30, 15, 60),
        new RpgCharacter("Slime", 50, 5, 80),
        new RpgCharacter("Skeleton", 20, 20, 70),
        new RpgCharacter("Ork", 80, 30, 40)
    };

    int chance = rand() % 100;
    if (chance <= 30)
    {
        m_players[1] = enemy[0];
    }
    else if (chance >= 31 && chance <= 60)
    {
        m_players[1] = enemy[1];
    }
    else if (chance >= 61 && chance <= 90)
    {
        m_players[1] = enemy[2];
    }
    else if (chance >= 91 && chance <= 100) // lower chance for higher stats enemy
    {
        m_players[1] = enemy[3];
    }

    // assigning for easier to call
    RpgCharacter* player = m_players[0];
    RpgCharacter* opponent = m_players[1];

    // enemy reveal
    std::cout << "\nIt's ";
    if (m_players[1] == enemy[3])
        std::cout << "an ";
    else
        std::cout << "a ";
    std::cout<< opponent->GetName() << std::endl;

    std::cout << "Press any key to continue...";
    _getch(); // Waits for any key press

    // Fighting loop
    while (player->IsAlive() && opponent->IsAlive()) {
        system("cls");
        std::cout << player->GetName() << "'s turn. Choose your action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Defend\n";

        int action;
        std::cin >> action;
        std::cin.ignore();

        switch (action) {
        case 1:
            player->Attack(*opponent);
            break;
        case 2:
            player->Defend();
            break;
        default:
            std::cout << "Invalid choice, you will attack by default.\n";
            player->Attack(*opponent);
            break;
        }
        std::cout << std::endl;


        // this just to make it look good
        std::cout << "Press any key to continue...";
        _getch(); // Waits for any key press
        std::cout << std::endl;
        std::cout << std::endl;

        if (opponent->IsDead()) // no enemy turn if enemy died
            break;

        // enemy attack in random pattern
        std::cout << opponent->GetName() << "'s turn.\n";
        int chance = rand() % 100;
        if (chance < 60)
            opponent->Attack(*player);
        else
            opponent->Defend();
        std::cout << "Press any key to continue...";
        _getch(); // Waits for any key press
        std::cout << std::endl;
    }

    // Determine the winner
    if (player->IsAlive()) {
        std::cout << player->GetName() << " wins!\n";
    }
    else {
        std::cout << " You died, Game Over\n";
        m_pGame->Quit(); // Quit after you died
    }

    std::cout << "Press any key to continue...";
    _getch(); // Waits for any key press
    std::cout << std::endl;

    delete m_players[1]; // Freeing space for next enemy, I think it works
}
