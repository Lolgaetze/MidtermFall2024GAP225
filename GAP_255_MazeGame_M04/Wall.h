#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
public:
	using GameObject::GameObject; // ctor

	virtual MoveOutcome OnCollide(GameObject* pMover) override; // block movement

	virtual void Draw() override; // display wall character
};