#include "Arena.h"
#include "MazeGame.h"
#include "RpgCharacter.h"
#include "Player.h"


#include <conio.h>
#include <iostream>
#include <vector>

Arena::~Arena()
{
    for (int i = 0; i < 2; ++i) {
        delete m_players[i];
    }
}
/////////////////////////////////////////////////////////
// Character selection
/////////////////////////////////////////////////////////
void Arena::ChooseCharacter()
{
    std::cout << "Player, choose your fighter:\n";
    player = ChooseFighter();
    std::cout << std::endl;
}

/////////////////////////////////////////////////////////
// Calculate the chance to encounter a monster while moving
/////////////////////////////////////////////////////////
void Arena::EncounterMonster()
{
    int chance = rand() % 100;
    if (chance < 20) { // 20% chance to encounter a monster
        std::cout << "A wild monster appears!\n";
        std::cout << "Press any key to continue...";
        _getch(); // Waits for any key press
        Fight();
    }
}


/////////////////////////////////////////////////////////
// list of characters with options printed
/////////////////////////////////////////////////////////

RpgCharacter* Arena::ChooseFighter()
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
void Arena::Fight()
{
    std::vector<RpgCharacter*> enemies = {
       new RpgCharacter("Goblin", 30, 15, 60),
       new RpgCharacter("Slime", 50, 5, 80),
       new RpgCharacter("Skeleton", 20, 20, 70),
       new RpgCharacter("Ork", 80, 30, 40)
};

int chance = rand() % 100;
if (chance <= 30) {
    opponent = enemies[0];
}
else if (chance <= 60) {
    opponent = enemies[1];
}
else if (chance <= 90) {
    opponent = enemies[2];
}
else {
    opponent = enemies[3];
}

// assigning for easier to call
//RpgCharacter* player = m_players[0];
//RpgCharacter* opponent = m_players[1];

// enemy reveal
std::cout << "\nIt's ";
if (m_players[1] == enemies[3])
std::cout << "an ";
else
std::cout << "a ";
std::cout << opponent->GetName() << std::endl;

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
    GameObject Quit();
    //quit.Quit(); // Quit after you died
}

std::cout << "Press any key to continue...";
_getch(); // Waits for any key press
std::cout << std::endl;

delete m_players[1]; // Freeing space for next enemy, I think it works

}
