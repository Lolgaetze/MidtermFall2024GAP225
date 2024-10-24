#pragma once
#include "GameObject.h"

class Player;
class RpgCharacter;

class Arena
{
private:
	RpgCharacter* m_players[2] = { nullptr, nullptr };
	RpgCharacter* player = {};
	RpgCharacter* opponent;
public:
	~Arena();

	void ChooseCharacter();

	void EncounterMonster();

private:
	RpgCharacter* ChooseFighter();

	void Fight();
};
