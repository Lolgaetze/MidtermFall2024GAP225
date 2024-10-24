#pragma once

#include "GameObject.h"

class Exit : public GameObject
{
public:
    using GameObject::GameObject; // ctor

    virtual MoveOutcome OnCollide(GameObject* pMover) override; // allow quit game

    virtual void Draw() override; // display exit character
};
