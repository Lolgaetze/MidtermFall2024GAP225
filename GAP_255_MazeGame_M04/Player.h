#pragma once

#include "GameObject.h"

class RpgCharacter;
class Arena;

// The player object
class Player : public GameObject
{
public:
    RpgCharacter* m_players[2];

private:
    int m_score = 0;


public:
    // This magic statement makes an identical ctor to the
    // one used by GameObject.
    using GameObject::GameObject;

    // Increment the player's score
    void IncrementScore() { ++m_score; }

    // Get the current score
    int GetScore() const { return m_score; }

    // This object performs active behavior, such as moving.
    virtual void TakeTurn() override;

    virtual MoveOutcome OnCollide(GameObject* pMover) override;

    virtual void Draw() override;

    void EncounterMonster();
    
    void ChooseCharacter();
private:

    RpgCharacter* ChooseFighter();
    
    void Fight();
};